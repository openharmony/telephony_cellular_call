# 运维观测

← 返回 [`AGENTS.md`](../../AGENTS.md)

---

## 日志标识

| 项 | 值 | 定义位置 |
|---|---|---|
| 服务日志标签 | `CellularCall` | 根目录 `BUILD.gn` 的 `defines` |
| 服务日志域 | `0xD001F11` | 根目录 `BUILD.gn` |
| 进程 | `telephony` | `sa_profile/4006.json` |
| 系统服务 | 4006 | 同上 |

```shell
hdc shell hilog -D 0xD001F11
hdc shell hilog | grep -i CellularCall
```

事件处理器的日志以 `[slotN]` 开头，按卡槽过滤时搜索该前缀。

## dump

```shell
hdc shell hidumper -s 4006 -a "-cellular_call_info"
```

输出包含服务绑定与启动耗时、运行状态、SRVCC 状态，以及每个卡槽的 IMS 服务状态等信息。

## 系统参数

| 参数 | 含义 |
|---|---|
| `persist.telephony.imsswitch` | 用户侧 IMS 开关持久化值 |
| `persist.telephony.vonrswitch` | VoNR 开关持久化值 |
| `persist.telephony.last_iccid` | 上次卡的 ICCID，用于判断是否换卡 |
| `persist.telephony.volte_cap_in_chip` | 芯片侧 VoLTE 能力 |
| `const.telephony.is_use_cloud_ims_nv` | 是否使用云端 IMS NV |

```shell
hdc shell param get persist.telephony.imsswitch
```

## 关键日志

| 日志片段 | 位置 | 判读 |
|---|---|---|
| `Check permission failed, no CONNECT_CELLULAR_CALL_SERVICE` | Stub | 调用方不是 foundation 且缺少权限 |
| `descriptor checked fail` | Stub | IPC 描述符不匹配，常见于两仓接口版本不一致 |
| `Dial return, invalid slot id` | `CellularCallService::Dial` | 卡槽号非法 |
| `IsNeedIms state:` | `IsNeedIms` | 打印 IMS 注册状态、域偏好、IMS 服务连接状态，判断走 IMS 还是 CS |
| `Function not found, need check.` | `CellularCallHandler::ProcessEvent` | 收到未登记的事件号 |
| `Ignore to report cs call state change cause by srvcc started` | `CsCallStatusInfoReport` | SRVCC 进行中，CS 状态上报被忽略 |
| `callManagerCallBack_ is nullptr, report fail` | `CellularCallRegister` | call_manager 尚未注册回调或已退出，状态无法回报 |
| `GetImsSwitchStatusResponse active` | `CellularCallHandler` | modem 返回的 IMS 开关与本地 VoLTE 配置对比 |
| `HandleNetworkStateChange entry` | `CellularCallConfig` | 网络状态变化进入配置处理 |
| `reconnect service successfully` | `ImsCallClient` | IMS 服务重新上线后重连完成 |

## HiSysEvent

`services/common/src/cellular_call_hisysevent.cpp` 负责打点。拨号路径的故障通过 `WriteDialCallFaultEvent` 记录，参数包含卡槽、通话类型、视频状态、错误码与原因串。新增失败分支时应补故障打点。

## 排查顺序

1. 执行 `hidumper -s 4006 -a "-cellular_call_info"`，确认服务、SRVCC 与 IMS 状态。
2. 拨号问题搜索 `IsNeedIms state:`，确认本次走的通道。
3. 状态回报问题确认 `callManagerCallBack_` 是否为空，再看 `ProcessEvent` 是否收到对应事件。
4. IMS 开关问题结合系统参数与 `GetImsSwitchStatusResponse` 日志。
5. 定位到模块后，转到 [`failure-modes.md`](failure-modes.md) 的「快速分诊表」。
