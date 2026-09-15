# telephony_cellular_call 知识库入口

本文件是本仓知识库的唯一入口，其余文档位于 `docs/agents/`，全部从这里路由进入。

使用顺序：先读「这个仓是什么」确定方向，再用「知识路由表」选中文档，修改前核对「红线」，完成前执行「最小验证闭环」。

> **说明：**
>
> 本知识库描述 master 主干的状态。文档中的不变量是主干应当成立的约束，旧分支上某条不变量尚未落地时，缺口本身往往就是待修复的缺陷。读到一条不变量后，先在当前代码中搜索它的落点；找不到落点时，结论是「这里缺了一处」，而不是「文档写错了」；找到落点但写法与不变量相反时，结论相同。描述现状的表格（测试目标配置、文件清单、已知技术债）同样以 master 为准，其他分支上以实际代码为准。

---

## 这个仓是什么

OpenHarmony 电话子系统的**蜂窝通话**部件，`part_name` 为 `cellular_call`。

- 运行形态：系统服务 SA 4006，进程 `telephony`，产物 `libtel_cellular_call.z.so`；参考 IMS 服务 SA 4014 位于 `vendor/ims/`。
- 职责：把 call_manager 的通话请求翻译为 CS、IMS、卫星三条通道的命令，把 modem 与 IMS 服务上报的通话状态整理后回报 call_manager；管理补充业务、紧急号码、IMS 开关与运营商配置。
- 上游：call_manager。下游：core_service 的 RIL 通道、IMS 服务、卫星服务。

心智模型：**夹在 call_manager 与 modem 之间的协议翻译层，加一份跨卡槽共享的静态配置。** 通话缺陷多出在「上报列表与本地连接表的对比」，配置缺陷多出在「事件到达顺序与配置前提」，崩溃类缺陷多出在「锁类型与锁范围」。

主链路的完整图示见 [`docs/agents/code-map.md`](docs/agents/code-map.md)「主链路」，骨架如下：

```text
下行：call_manager → Stub（唯一权限关口）→ Service（卡槽、SRVCC、紧急号码、通道选择）→ CS / IMS / 卫星 Control → modem 或 IMS 服务
上行：modem / IMS 服务 → CellularCallHandler（每卡槽事件处理器）→ Control::ReportXxx（对比连接表）→ CellularCallRegister → call_manager
配置：SIM、网络、运营商配置、Radio 事件 → CellularCallHandler → CellularCallConfig（static，多把锁）
```

---

## 知识路由表

### 任务触发路由

| 任务 | 先读 | 再改 |
|---|---|---|
| 崩溃栈在加锁、解锁或 map 操作处 | [`boundaries.md`](docs/agents/boundaries.md)「锁类型与锁范围」 | 崩溃点所在文件，先查锁类型 |
| IMS 开关、VoLTE、VoNR、运营商配置时序 | [`boundaries.md`](docs/agents/boundaries.md)「配置事件的前提与顺序」 | `services/utils/src/cellular_call_config.cpp` |
| 拨号、接听、挂断、保持等下行请求 | [`boundaries.md`](docs/agents/boundaries.md)「下行链路约束」 | `cellular_call_service.cpp` → `control/src/*_control.cpp` |
| 来电不报、挂断不报、状态错乱 | [`boundaries.md`](docs/agents/boundaries.md)「上行回报约束」 | `cellular_call_handler.cpp`、`control/src/*_control.cpp` |
| 紧急号码判定 | [`high-risk.md`](docs/agents/high-risk.md)「高危入口」 | `services/utils/src/emergency_utils.cpp` 与配置中的紧急号码列表 |
| 呼转、呼限、呼等、CLIP、CLIR、USSD、MMI 码 | [`code-map.md`](docs/agents/code-map.md)「任务到路径」 | `cellular_call_supplement.cpp`、`mmi_code_utils.cpp` |
| 新增或修改 IPC 接口 | [`boundaries.md`](docs/agents/boundaries.md)「IPC 定义在 call_manager 仓」 | 跨仓改动，先停下确认 |
| 新增 modem 事件处理 | [`boundaries.md`](docs/agents/boundaries.md)「事件处理器约束」 | `cellular_call_handler.cpp` |
| 新增 feature 宏或源文件 | [`build-and-test.md`](docs/agents/build-and-test.md)「两份源文件清单」 | `BUILD.gn`、`cellularcall.gni`、`test/cellular_call_test.gni`、`bundle.json` |
| 评估改动风险 | [`high-risk.md`](docs/agents/high-risk.md)「变更风险矩阵」 | 无 |
| 按现象定位根因 | [`failure-modes.md`](docs/agents/failure-modes.md)「快速分诊表」 | 无 |
| 排查线上问题 | [`observability.md`](docs/agents/observability.md) | 无 |
| 写用例、构建、验证 | [`build-and-test.md`](docs/agents/build-and-test.md) | `test/unittest/` |

### 路径触发路由

| 文件路径 | 必读知识 |
|---|---|
| `services/utils/src/cellular_call_config.cpp`、`include/cellular_call_config.h` | `boundaries.md`「锁类型与锁范围」「配置事件的前提与顺序」 |
| `services/utils/src/emergency_utils.cpp` | `high-risk.md`「高危入口」 |
| `services/manager/src/cellular_call_stub.cpp` | `boundaries.md`「IPC 定义在 call_manager 仓」 |
| `services/manager/src/cellular_call_handler.cpp` | `boundaries.md`「事件处理器约束」 |
| `services/manager/src/cellular_call_service.cpp` | `boundaries.md`「下行链路约束」 |
| `services/control/**`、`services/connection/**` | `boundaries.md`「上行回报约束」「锁类型与锁范围」 |
| `services/ims_service_interaction/**` | `high-risk.md`「高危事件序列」 |
| `services/telephony_ext_wrapper/**` | `boundaries.md`「扩展钩子」 |
| `vendor/ims/**` | `code-map.md`「部件定位」，这是独立 SA |
| `interfaces/innerkits/**` | `high-risk.md`「高危入口」 |
| `BUILD.gn`、`cellularcall.gni`、`test/*.gni` | `build-and-test.md`「两份源文件清单」 |

### 词汇触发路由

| 词 | 含义 | 落点 |
|---|---|---|
| CS / IMS | 电路域通话 / IP 多媒体子系统通话（VoLTE、VoNR） | `cs_control.cpp`、`ims_control.cpp` |
| SRVCC | IMS 通话切换到 CS 的过程，进行中时拒绝拨号并忽略 CS 状态上报 | `CellularCallService`、`CellularCallHandler` |
| UT / XCAP | 通过 IMS 数据通道执行补充业务，与 CS 补充业务二选一 | `CellularCallSupplement` |
| ECC | 紧急号码 | `EmergencyUtils`、`CellularCallConfig` 紧急号码列表 |
| MMI 码 | `*#` 开头的特服码，命中后转补充业务，不建立通话 | `IsNeedExecuteMMI` |
| NV | modem 侧非易失配置，更新后 IMS 开关需要重新同步 | `CellularCallConfig` |
| `connectionMap_` | Control 维护的 modem 侧连接表，键为通话序号 | `control/` |
| `callManagerCallBack_` | call_manager 注册的回调，全部上行回报的出口 | `CellularCallRegister` |
| `operatorMutex_` / `plmnMutex_` / `modeMutex_` | `CellularCallConfig` 的静态 ffrt 锁 | 配置头文件 |
| `FOUNDATION_UID` | call_manager 所在 foundation 进程的 uid，免权限校验 | Stub |
| `TELEPHONY_EXT_WRAPPER` | 扩展库钩子集合，函数指针为空表示未加载 | `telephony_ext_wrapper/` |
| slotId | 卡槽号，所有 static 配置 map 以它为键 | 全仓 |
| PLMN | 运营商网络标识（MCC+MNC），用于区分归属网络与当前网络 | `CellularCallConfig` 的 `curPlmn_`、紧急号码列表 |
| CLIP / CLIR | 主叫号码显示 / 主叫号码限制，补充业务的一类 | `CellularCallSupplement` |
| RTT / RedCap | 实时文本通话 / 轻量化 5G 终端能力，均为默认关闭的 feature | `high-risk.md`「高危配置项」 |

### 动手前必须先自陈

写出第一行代码改动之前，先在回复中用三行写清楚：

```text
任务类别：<「任务触发路由」表中的哪一行>
已读文档：<docs/agents/ 下实际读过的文件与小节>
命中约束：<「红线」编号 + 分层文档中找到的不变量；确认没有则写"无">
```

写不出「命中约束」时，说明尚未掌握本次改动的影响范围，不要开始修改。

---

## 红线

违反以下任一条的改动不可合入。

1. **禁止在同一份数据上混用锁类型，禁止在事件处理器或 ffrt 任务可达的路径上新增 `std::mutex`。** `CellularCallConfig` 的静态锁与 Control 的连接表锁使用 ffrt 锁类型，新增锁跟随同文件既有类型。
2. **禁止在已持有非递归锁时调用自行加同一把锁的函数。** `operatorMutex_`、`plmnMutex_`、`modeMutex_` 都不可递归。
3. **禁止用「给所有读点补锁」处理锁附近的崩溃，而不先核对锁类型与重入。** 补锁会放大锁范围并引入新的死锁。
4. **禁止清除延迟动作标志而不满足其前提。** 标志被消费时必须确认前提成立，前提不成立时保留标志等待下一次事件。
5. **禁止在 Stub 之外新增权限判断，或绕过 Stub 的权限关口。** 权限唯一收口在 `CellularCallStub::OnRemoteRequest`。
6. **禁止绕过 `CellularCallRegister` 直接回调 call_manager。**
7. **禁止不判空调用 `TELEPHONY_EXT_WRAPPER` 的函数指针。**
8. **禁止修改 IPC 接口码枚举的已有取值。** 涉及 call_manager 仓的 `CellularCallInterfaceCode`，以及本仓 `interfaces/innerkits/` 下的 `ImsCallInterfaceCode`、`ImsCallCallbackInterfaceCode`、`SatelliteCallInterfaceCode`、`SatelliteCallCallbackInterfaceCode`。枚举值即跨部件 ABI，只能追加。
9. **禁止打印号码。** 定位通话用卡槽号与通话序号。
10. **禁止新增 `.cpp` 只加入一份源文件清单。** 服务库 `BUILD.gn` 与测试 `test/cellular_call_test.gni` 各有一份。
11. **禁止使用 `try`/`catch` 与 `dynamic_cast`。**

### 必须停下来找人确认的改动

| 触发条件 | 原因 |
|---|---|
| 改动紧急号码判定的任何分支或输入来源 | 最高等级事故面，见 [`high-risk.md`](docs/agents/high-risk.md)「高危入口」 |
| 修改 call_manager 仓中的接口定义或本仓 `interfaces/innerkits/` 的已有接口 | 跨部件 ABI |
| 收紧或放宽 Stub 的权限关口 | 安全事件 |
| 修改 feature 宏默认值 | 影响所有未显式配置的产品 |
| 改变 IMS 开关、VoNR 开关的持久化参数名或取值含义 | 升级后用户设置丢失 |
| 删除或重命名系统参数 | 产品配置与其他部件依赖 |
| 修改 `HandleCallManagerException` 的挂断行为 | 影响所有进行中的通话 |
| 新增或替换外部部件依赖、第三方库（`external_deps`、`bundle.json` 的 `deps`） | 许可证与供应链合规审查，改变部件依赖关系 |

判据：这个改动的后果能不能在本仓内验证？不能，就属于本节。

---

## 最小验证闭环

详细命令见 [`docs/agents/build-and-test.md`](docs/agents/build-and-test.md)。

### 静态自检

必做，无需构建环境：

- 新增或改动的锁：类型与同文件既有锁一致，持锁区间内没有调用自行加同一把锁的函数，没有调用会回调外部的函数。
- 延迟动作标志：列出置位点、消费点、清位点，确认消费点不会被提前返回跳过，清位只在前提成立时发生。
- 新增 `.cpp` 同时进入 `BUILD.gn` 与 `test/cellular_call_test.gni`。
- 新增 feature 宏在 `cellularcall.gni`、`bundle.json`、`BUILD.gn` 与测试 gni 中齐全。
- `build-and-test.md`「无构建环境时的静态自检」逐项通过。

### 构建与测试

```shell
./build.sh --product-name <product> --build-target cellular_call
./build.sh --product-name <product> --build-target "//base/telephony/cellular_call/test:unittest"
hdc shell /data/test/cellular_call_ims2_test --gtest_filter=<用例名>*
```

### DoD 判定

- [ ] 目标行为在最小复现场景下被验证，场景写入提交说明。
- [ ] 至少一条带实际断言的用例覆盖改动分支，断言被修复的具体状态。
- [ ] 回归面已按 [`high-risk.md`](docs/agents/high-risk.md)「变更风险矩阵」确认。
- [ ] 日志中无号码。

### 最终回复必须包含

1. 改了什么：文件清单，每处一句话说明为什么改在这里。
2. 「动手前必须先自陈」中的三行。
3. DoD 逐项结果：已验证或未验证，未验证写明原因。
4. 验证边界：没有 OpenHarmony 构建环境时，明说「仅完成静态自检，未编译、未运行测试」。
5. 遗留风险：需人工复核的项、发现但未修的技术债、同一模式在其他文件中的残留。

---

## 分层文档索引

| 文档 | 内容 | 什么时候读 |
|---|---|---|
| [`docs/agents/code-map.md`](docs/agents/code-map.md) | 目录职责、主链路、关键类、任务到路径 | 第一次进入某个模块 |
| [`docs/agents/boundaries.md`](docs/agents/boundaries.md) | 依赖方向、IPC 边界、锁约定、配置时序、上下行约束 | 动手改代码前必读 |
| [`docs/agents/high-risk.md`](docs/agents/high-risk.md) | 高危入口、高危配置、高危事件序列、变更风险矩阵 | 改动涉及紧急呼叫、IPC、宏、IMS 时 |
| [`docs/agents/failure-modes.md`](docs/agents/failure-modes.md) | 快速分诊表、失效模式、根因排查方法、修复反例、回归要求 | 排查缺陷时 |
| [`docs/agents/observability.md`](docs/agents/observability.md) | 日志标识、dump、系统参数、关键日志 | 定位现场问题 |
| [`docs/agents/build-and-test.md`](docs/agents/build-and-test.md) | 构建目标、两份源文件清单、测试目标与替身、静态自检 | 验证阶段 |
