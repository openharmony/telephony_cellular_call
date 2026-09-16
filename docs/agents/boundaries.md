# 边界与约束

← 返回 [`AGENTS.md`](../../AGENTS.md)

---

## 模块依赖方向

```text
manager/   Stub → Service → Handler → Register
   │ 调用
control/   ControlBase → CSControl / IMSControl / SatelliteControl / ImsVideoCallControl
   │ 持有
connection/  BaseConnection 及子类
   │ 使用
utils/  common/   CellularCallConfig、Supplement、EmergencyUtils、请求封装
   │
ims_service_interaction/  satellite_service_interaction/   外部服务客户端
```

| 规则 | 说明 |
|---|---|
| Stub 只做描述符校验、权限关口、反序列化、转发 | 业务判断放在 Service 或 Control |
| 上行回报只经 `CellularCallRegister` | Control 不直接持有 call_manager 回调 |
| `utils/` 不反向依赖 `manager/` 中的 Service 状态 | 需要服务状态时由调用方传入 |
| `vendor/ims/` 是独立 SA 的参考实现 | 服务侧代码通过 `ImsCallClient` 访问，不直接包含 vendor 头文件 |

### IPC 定义在 call_manager 仓

`CellularCallInterface`、`CellularCallInterfaceCode`、`ICallStatusCallback` 与请求方代理位于 call_manager 仓 `interfaces/innerkits/`。

新增一个下行 IPC 接口的清单：

1. call_manager 仓：接口码枚举末尾追加，`CellularCallInterface` 增加纯虚函数，代理实现写入顺序。
2. 本仓 Stub：在分发表中登记处理函数，读取顺序与代理写入顺序、类型、个数一致。
3. 本仓 Service：实现接口，先校验卡槽号。
4. Control：按通道实现，CS、IMS、卫星各自判断是否支持。
5. 模糊测试：为新接口补充或扩展 fuzzer，并在 `test/fuzztest/BUILD.gn` 登记。
6. 两仓同步提交，属于需要人工确认的改动。

新增上行回报同理：call_manager 仓 `ICallStatusCallback` 追加方法，本仓 `CellularCallRegister` 增加出口。

`interfaces/innerkits/ims/` 与 `satellite/` 是本仓对 IMS 服务、卫星服务的 IPC 定义，由本仓与服务实现方共同使用，同样只能追加。

---

## 锁类型与锁范围

### 锁类型

| 位置 | 锁 | 保护对象 |
|---|---|---|
| `CellularCallConfig` | `static ffrt::mutex operatorMutex_` | 运营商配置派生的静态 map、延迟动作标志、网络服务状态缓存 |
| `CellularCallConfig` | `static ffrt::mutex plmnMutex_`、`modeMutex_` | PLMN 缓存、域偏好模式 |
| `CellularCallConfig` | `static std::shared_mutex simStateLock_`、`mutex_` | 卡状态与紧急号码列表 |
| `CSControl`、`IMSControl`、`SatelliteControl` | `ffrt::recursive_mutex connectionMapMutex_` | 连接表 |
| `CellularCallHiSysEvent` | `ffrt::mutex` | 打点状态 |
| `ControlBase` | `std::mutex` 配合 `std::condition_variable` | 挂断等待 |
| `CellularCallService`、`CellularCallHandler`、`CellularCallRegister` | `std::mutex` | 处理器表、回调指针 |

约束：

- **事件处理器与 ffrt 任务运行在 ffrt 工作线程上。** 在这些路径上阻塞 `std::mutex` 会占住工作线程而不是让出协程，与 ffrt 锁混用时，崩溃或挂起表现为栈落在加锁、解锁附近。仓内历史修复（`operatorMutex_`、`modeMutex_`、打点锁）都是把 `std::mutex` 改为 `ffrt::mutex`。
- **新增锁跟随同文件既有锁类型。** 在 `CellularCallConfig` 与 Control 中新增一律使用 ffrt 类型，加锁写法用 `std::lock_guard<ffrt::mutex>` 或 `std::unique_lock<ffrt::mutex>`。
- **修改锁类型时，同一把锁的全部加锁点一并修改。** 头文件声明、cpp 定义、每个 `lock_guard` 与 `unique_lock` 的模板参数都要一致，否则编译失败。
- 单元测试链接 `core_service:ffrt_mocked`，ffrt 锁在测试中可用，但并发时序与真机不同。

### 锁范围

- `operatorMutex_` 不可递归。已持锁的函数内，不要调用会再次获取 `operatorMutex_` 的 `GetXxxConfig` 等函数。检查方法：对被调函数名搜索，确认其内部没有加同一把锁。
- 持锁区间内不要调用会跨 IPC 回调本服务的函数。下发 modem 请求是异步的，可以在锁内发起。
- `std::map::operator[]` 对不存在的键会插入默认值。读路径优先用 `find`，并确认卡槽号已校验。

---

## 配置事件的前提与顺序

### 事件到达顺序不固定

`CellularCallHandler` 按事件号分发以下事件，它们的相对顺序随 modem 与卡的状态变化：

```text
SIM 状态变化  →  HandleSimStateChanged
SIM 记录加载  →  HandleSimRecordsLoaded
网络状态变化  →  HandleNetworkStateChange
运营商配置变更 →  HandleOperatorConfigChanged → ParseAndCacheOperatorConfigs
Radio 状态变化 →  开关机、modem 重启相关处理
```

**不要假设任一事件在另一事件之后到达。** 依赖多个前提的动作要设计成「在每个前提满足的事件里检查一次，全部满足才执行」。

### 延迟动作标志

`shouldCheckImsAfterNvUpdate_` 这类标志表示「某个动作需要在后续条件满足时补做一次」。

| 角色 | 要求 |
|---|---|
| 置位点 | 在引发需求的事件中置位，如卡状态变化、卡记录加载 |
| 消费点 | 在前提有机会被满足的事件中检查，如网络状态变化 |
| 清位点 | **只在前提成立且动作已发起后清位**；前提不成立时保留标志 |

检查方法：

1. 列出标志的全部置位、读取、清位点。
2. 确认消费点在函数中的位置不会被「状态未变化则提前返回」之类的分支跳过。
3. 确认消费条件包含了动作所需的全部前提，例如「已注册到网络」。

`HandleNetworkStateChange` 在网络注册状态与漫游状态都未变化时提前返回，放在返回之后的逻辑对重复上报不执行。

### IMS 开关查询的入口

向 modem 查询 IMS 开关状态最终都调用 `CellularCallConfig::GetImsSwitchStatusRequest`，但入口有两类，前提各不相同：

| 入口 | 触发 | 前提 |
|---|---|---|
| `CellularCallConfig::HandleNetworkStateChange` | 网络状态变化，消费延迟动作标志 | 由标志与网络注册状态控制 |
| `CellularCallHandler::GetImsSwitchStatusRequest` | Radio 状态变化、IMS 能力响应等处理器事件 | 有卡，且支持 VoLTE 或 IMS 已注册 |

修改查询时机时，两类入口都要检查，并在回复中说明另一类入口是否受影响。

---

## 下行链路约束

- `CellularCallService` 的每个接口先调用 `IsValidSlotId`。
- 拨号在 SRVCC 进行中直接拒绝。
- 通道选择顺序：卫星开关打开时走卫星；否则 `IsNeedIms` 或紧急呼叫优先 IMS 为真时走 IMS；其余走 CS。改变选择逻辑属于高危改动。
- `ControlBase::DialPreJudgment` 负责号码与状态的前置判断，`IsNeedExecuteMMI` 命中时转补充业务，不建立通话。
- 补充业务在 IMS 服务已连接时走 UT，否则走 CS，判断集中在 `CellularCallSupplement`。

## 上行回报约束

- `ReportCsCallsData` 与 `ReportImsCallsData` 在 `connectionMapMutex_` 内对比上报列表与 `connectionMap_`，分为来电、更新、挂断三类，**三类都要处理**，漏掉一类即表现为状态不回报或残留连接。
- 挂断与状态更新两种情形下，`isNeedQuery` 默认为真；连接表中存在挂断原因仍为 `DISCONNECTED_REASON_INVALID` 的连接时，先向 modem 查询挂断原因并直接返回，本次不回报，待 `RADIO_GET_CALL_FAIL_REASON` 响应后以 `isNeedQuery` 为假再回报一次。
- 基类还声明了 `ReportCallsData`，三个 Control 都有实现，但产品代码没有调用点，只有测试用例调用；排查上行回报时不要读错函数。
- SRVCC 进行中，`CsCallStatusInfoReport` 忽略 CS 状态上报，SRVCC 结束后依赖后续上报恢复。
- 回报出口 `CellularCallRegister` 在 `callManagerCallBack_` 为空时丢弃并打印日志，call_manager 重启期间的回报会丢失。
- call_manager 被移除时 `HandleCallManagerException` 挂断全部连接。

## 事件处理器约束

- 每卡槽一个 `CellularCallHandler`，事件在构造函数中登记到 `requestFuncMap_`，新增事件漏登记时日志为 `Function not found, need check.`。
- 处理函数运行在该卡槽的事件线程上，不要在其中同步等待另一卡槽的处理器。
- 处理器同时是公共事件订阅者，订阅在服务启动阶段完成，新增公共事件同步修改订阅列表。

## 扩展钩子

- `TELEPHONY_EXT_WRAPPER` 通过 `dlsym` 加载，函数指针为空表示扩展库不存在或未导出，调用前必须判空并提供默认行为。
- 钩子相关代码受 `OHOS_BUILD_ENABLE_TELEPHONY_EXT` 控制，宏关闭时仍要能编过。
