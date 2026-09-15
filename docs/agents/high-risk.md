# 高危入口与变更风险

← 返回 [`AGENTS.md`](../../AGENTS.md)

---

## 高危入口

改动以下位置，事故等级最高，改动前按 [`AGENTS.md`](../../AGENTS.md)「必须停下来找人确认的改动」标注。

### 等级 A

| 入口 | 位置 | 风险 |
|---|---|---|
| 紧急号码判定 | `EmergencyUtils::IsEmergencyCall`、`IsEmergencyCallProcessing` | 误判为非紧急号码会导致紧急呼叫走普通流程或被拦截；误判为紧急号码会产生错误的紧急呼叫 |
| 紧急号码列表维护 | `CellularCallConfig::UpdateEccNumberList` 及其数据来源处理 | 列表错误或为空时影响所有紧急号码判定 |
| 通道选择 | `CellularCallService::Dial`、`DialNormalCall`、`IsNeedIms`、`UseImsForEmergency` | 选错通道导致拨号失败，紧急呼叫尤甚 |
| 权限关口 | `CellularCallStub::OnRemoteRequest` | 放宽即越权控制通话 |
| call_manager 退出处理 | `HandleCallManagerException` | 影响全部进行中通话 |

紧急号码判定的输入包括：卡槽的紧急号码列表（来自数据库、SIM 与 modem）、卡的 MCC、网络国家码、设备形态参数。**改动判定逻辑时，用例必须覆盖输入组合矩阵：**

| 紧急号码列表 | 网络国家码 | 号码 |
|---|---|---|
| 空 | 空 | 常见紧急号码、普通号码 |
| 空 | 非空 | 常见紧急号码、该国紧急号码、普通号码 |
| 非空 | 任意 | 列表内且 MCC 匹配、列表内但 MCC 不匹配、列表外 |

这类用例需要 `mockNetworkSearch` 等替身，目标的 `BUILD.gn` 必须包含 `test/mock` 与 gmock 依赖，见 [`build-and-test.md`](build-and-test.md)「测试替身的可用性」。

### 等级 B

| 入口 | 位置 | 风险 |
|---|---|---|
| 连接表对比 | `CSControl::ReportCallsData`、`IMSControl::ReportImsCallsData` | 来电不报、挂断不报、残留连接 |
| IMS 开关与 VoNR 开关 | `CellularCallConfig` 的开关读写、`persist.telephony.imsswitch`、`persist.telephony.vonrswitch` | 用户设置丢失或与 modem 不一致 |
| 运营商配置解析 | `ParseAndCacheOperatorConfigs` | 静态配置跨卡槽共享，解析错误影响两张卡 |
| 配置锁 | `operatorMutex_`、`plmnMutex_`、`modeMutex_` | 锁类型或范围错误导致崩溃与死锁 |
| SRVCC 状态 | `srvccState_` 与相关处理 | 切换期间状态丢失 |
| IMS 服务连接 | `ImsCallClient` 重连 | IMS 服务重启后通话能力不恢复 |

---

## 高危配置项

### feature 宏

| `cellularcall.gni` 变量 | 默认 | 宏或影响 |
|---|---|---|
| `cellular_call_dynamic_start` | `false` | 使用 `4006_dynamic.json` 按需启停 |
| `cellular_call_tel_power_mode` | `false` | `BASE_POWER_IMPROVEMENT_FEATURE` |
| `cellular_call_support_UT` | `true` | 引入 `security_guard`，定义 `SECURITY_GUARDE_ENABLE` |
| `cellular_call_satellite` | `false` | `CELLULAR_CALL_SATELLITE`，同时控制卫星测试目标是否构建 |
| `cellular_call_support_rtt` | `false` | `SUPPORT_RTT_CALL` |
| `cellular_call_redcap_ability` | `false` | `CELLULAR_CALL_REDCAP_ABILITY` |

由产品或外部部件推导的宏：

| 宏 | 条件 |
|---|---|
| `CALL_MANAGER_AUTO_START_OPTIMIZE` | `device_name == "rk3568"` |
| `OHOS_BUILD_ENABLE_TELEPHONY_EXT` | `telephony_telephony_enhanced` 为真 |

新增 feature 宏清单：`cellularcall.gni` 的 `declare_args` 与 `global_defines`、`bundle.json` 的 `features`、测试 `test/cellular_call_test.gni` 的 `cellular_call_defines`。宏关闭时必须能编过。

### 系统参数

参数表见 [`observability.md`](observability.md)「系统参数」。删除、重命名参数或改变取值含义，影响产品配置与升级后的用户设置，属于需要人工确认的改动。

---

## 高危事件序列

| 序列 | 关注点 |
|---|---|
| 插卡或换卡 → 卡记录加载 → 网络注册 → 运营商配置变更 | 事件顺序不固定；依赖网络注册的动作不能在注册前执行并清除标志 |
| modem 重启或 Radio 关再开 | IMS 开关、VoNR 开关需要重新下发；连接表需要清理 |
| IMS 服务进程重启 | `ImsCallClient` 重连后，开关与能力状态是否重新同步 |
| call_manager 进程重启 | 回调指针为空期间的回报丢失；`HandleCallManagerException` 挂断全部通话 |
| 通话中 SRVCC | CS 上报被忽略的窗口；切换失败时的状态恢复 |
| 双卡同时有事件 | 静态配置跨卡槽共享，锁竞争集中在 `CellularCallConfig` |

---

## 变更风险矩阵

| 改动模块 | 回归面 | 最低验证 |
|---|---|---|
| `cellular_call_config.cpp` 锁 | 所有配置读写路径、并发事件 | `cellular_call_ims2_test`、`cellular_call_ims_zero_branch1_test`、`cellular_call_ims_config_request_test` |
| `cellular_call_config.cpp` 时序与标志 | 插卡、换卡、网络注册、开关同步 | 同上，并新增覆盖前提成立与不成立两种情况的用例 |
| `emergency_utils.cpp` | 所有紧急呼叫 | `cellular_call_ims_emergency_utils_test`，覆盖「高危入口」中的输入组合矩阵 |
| `cellular_call_service.cpp` 拨号 | CS、IMS、卫星、紧急呼叫 | `cellular_call_cs1_test`、`cellular_call_ims1_test` |
| `control/` 回报 | 来电、挂断、会议、保持 | `cellular_call_cs_calloperation_test`、`cellular_call_ims_zero_branch_test` |
| `cellular_call_supplement.cpp` | 呼转、呼限、呼等、CLIP、CLIR | `cellular_call_ims_cellular_call_supplement_test` |
| `cellular_call_stub.cpp` | 所有下行接口 | `cellular_call_ims_cellular_call_stub_test`、相关 fuzzer |
| `ims_service_interaction/` | IMS 通话全部路径 | `cellular_call_ims_callback_stub_test`、`cellular_call_ims_call_callback_stub_test` |
| feature 宏 | 宏打开与关闭两种构建 | 两种配置各编译一次 |
