# 代码地图

← 返回 [`AGENTS.md`](../../AGENTS.md)

---

## 部件定位

| 项 | 值 |
|---|---|
| 部件 | `cellular_call`，子系统 `telephony` |
| 系统服务 | SA 4006，进程 `telephony`，产物 `libtel_cellular_call.z.so`，依赖 SA 4010（core_service） |
| 启动配置 | `sa_profile/4006.json` 常驻启动；`4006_dynamic.json` 按 modem 动态上下电参数按需启停 |
| 参考 IMS 服务 | `vendor/ims/`，SA 4014，产物 `libtel_ims.z.so`，同在 `telephony` 进程 |
| 职责 | 把 call_manager 的通话请求翻译为 CS、IMS、卫星三条通道的 modem 命令，把 modem 上报的通话状态整理后回报 call_manager；管理补充业务、紧急号码、IMS 开关与运营商配置 |
| 上游 | call_manager（请求方与状态接收方） |
| 下游 | core_service 的 RIL 通道（CS）、IMS 服务 SA 4014、卫星服务 |

心智模型：本仓是**夹在 call_manager 与 modem 之间的协议翻译层**，不持有业务意义上的通话对象，只按卡槽维护「modem 侧的连接表」，并把连接表的变化报告出去。

## 非本仓维护的定义

以下接口定义在 **call_manager 仓**的 `interfaces/innerkits/` 下，修改它们属于跨仓改动，必须两仓同步：

| 定义 | 文件 |
|---|---|
| `CellularCallInterface` | `cellular_call_interface.h` |
| `CellularCallInterfaceCode` | `cellular_call_ipc_interface_code.h` |
| `ICallStatusCallback` | `i_call_status_callback.h` |

请求方的代理 `CellularCallProxy` 也在 call_manager 仓中。本仓没有面向应用的 JS 接口。

## 嵌套指引

本仓没有目录级的 `AGENTS.md`。全部任务指引经由根目录 `AGENTS.md` 路由到 `docs/agents/` 下的分层文档。

## 目录职责

```text
telephony_cellular_call/
├── BUILD.gn / cellularcall.gni     服务库 tel_cellular_call 与 feature 开关
├── bundle.json                     部件声明
├── sa_profile/                     SA 4006 启动配置
├── interfaces/innerkits/
│   ├── ims/                        IMS 服务 IPC 接口与客户端头文件（inner_kits tel_ims_call_api）
│   ├── ims_common/                 IMS 公共特性定义
│   └── satellite/                  卫星通话 IPC 接口（inner_kits tel_satellite_call_api）
├── services/
│   ├── manager/                    服务、IPC 分发、事件处理器、回报 call_manager
│   ├── control/                    CS、IMS、IMS 视频、卫星四类通话控制
│   ├── connection/                 单路通话连接对象
│   ├── common/                     请求封装、补充业务请求、数据库、HiSysEvent、MMI 消息
│   ├── utils/                      运营商配置、补充业务、紧急号码、MMI 码、模块查询、dump
│   ├── ims_service_interaction/    IMS 服务客户端、代理、回调桩
│   ├── satellite_service_interaction/  卫星服务客户端
│   └── telephony_ext_wrapper/      扩展库钩子
├── vendor/ims/                     参考 IMS 服务实现与其测试
└── test/
    ├── unittest/cstest/            CS 通道测试
    ├── unittest/imstest/           IMS 通道、配置、补充业务、紧急号码测试
    ├── unittest/satellitetest/     卫星通道测试
    ├── fuzztest/                   模糊测试
    └── mock/                       测试替身
```

## 主链路

### 下行：拨号

```text
call_manager CellularCallProxy
  └─ IPC SA 4006 → services/manager/src/cellular_call_stub.cpp
       OnRemoteRequest：校验描述符 → 非 foundation 调用方须持有 CONNECT_CELLULAR_CALL_SERVICE
       → requestFuncMap_ 分发
       └─ services/manager/src/cellular_call_service.cpp  Dial
            卡槽校验 → SRVCC 进行中则拒绝 → 紧急号码判断
            → 卫星开关打开时交给 SatelliteControl
            → DialNormalCall：IsNeedIms 或 UseImsForEmergency 为真走 IMSControl，否则走 CSControl
            └─ services/control/src/ims_control.cpp / cs_control.cpp  Dial
                 DialPreJudgment → IsNeedExecuteMMI（MMI 码转补充业务，不建立通话）
                 ├─ CS：经 core_service RIL 下发
                 └─ IMS：ImsCallClient → IPC SA 4014
```

`IsNeedIms` 的条件为：IMS 已注册、域偏好不是 `CS_VOICE_ONLY`、IMS 服务已连接，三者同时成立。

### 上行：通话状态回报

```text
RIL 或 IMS 服务上报
  └─ CellularCallHandler::ProcessEvent（按卡槽的 TelEventHandler，requestFuncMap_ 以事件号分发）
       例：CsCallStatusInfoReport（SRVCC 进行中时忽略）→ 查询当前通话列表
       └─ CSControl::ReportCsCallsData / IMSControl::ReportImsCallsData
            持 connectionMapMutex_（ffrt::recursive_mutex）对比 connectionMap_ 与上报列表
            分为来电、更新、挂断三种情形
            └─ CellularCallRegister::ReportCallsInfo → callManagerCallBack_（ICallStatusCallback）→ call_manager
```

### 配置与卡状态

```text
SIM 状态变化、卡记录加载、网络状态变化、运营商配置变更公共事件、Radio 状态变化
  └─ CellularCallHandler 对应处理函数
       └─ services/utils/src/cellular_call_config.cpp
            更新运营商配置缓存、紧急号码列表、IMS 能力，按需下发 IMS 开关与 VoNR 开关
```

### call_manager 退出

服务订阅了 call_manager 的系统能力状态。call_manager 被移除时进入 `HandleCallManagerException`，对各卡槽的 CS 与 IMS 控制执行 `HangUpAllConnection`。

## 关键类与数据

| 类或数据 | 位置 | 说明 |
|---|---|---|
| `CellularCallService` | `manager/src/cellular_call_service.cpp` | 单例服务，按卡槽持有 `handlerMap_`、`csControlMap_`、`imsControlMap_`、`satelliteControlMap_` |
| `CellularCallStub` | `manager/src/cellular_call_stub.cpp` | IPC 分发，**唯一权限关口** |
| `CellularCallHandler` | `manager/src/cellular_call_handler.cpp` | 每卡槽一个事件处理器，同时订阅公共事件 |
| `CellularCallRegister` | `manager/src/cellular_call_register.cpp` | 持有 call_manager 回调，全部上行回报的出口 |
| `ControlBase` | `control/src/control_base.cpp` | 通话控制公共逻辑，不持有连接表 |
| `CSControl`、`IMSControl`、`SatelliteControl` | `control/src/` | 各自声明类型不同的 `connectionMap_` 与 `connectionMapMutex_` |
| `BaseConnection` 及子类 | `connection/` | 单路连接，含呼叫信息、状态与后拨号串 |
| `CellularCallConfig` | `utils/src/cellular_call_config.cpp` | **成员以 static 为主**，跨卡槽共享，多把锁并存 |
| `CellularCallSupplement` | `utils/src/cellular_call_supplement.cpp` | 补充业务；IMS 服务已连接时走 UT，否则走 CS |
| `EmergencyUtils` | `utils/src/emergency_utils.cpp` | 紧急号码判定 |
| `ImsCallClient` | `ims_service_interaction/src/ims_call_client.cpp` | 连接 SA 4014，订阅其上线并自动重连 |
| `TelephonyExtWrapper` | `telephony_ext_wrapper/` | `dlsym` 加载的扩展钩子，函数指针为空时必须跳过 |

## 任务到路径

| 任务 | 首先打开 |
|---|---|
| 拨号、接听、挂断、保持等请求处理 | `manager/src/cellular_call_service.cpp`，再到 `control/src/cs_control.cpp` 或 `ims_control.cpp` |
| 通话状态回报异常 | `manager/src/cellular_call_handler.cpp` 与 `control/` 的 `ReportXxx` 函数 |
| 新增一个 modem 事件处理 | `cellular_call_handler.cpp` 的构造函数与 `requestFuncMap_` |
| 新增 IPC 接口 | 见 [`boundaries.md`](boundaries.md)「IPC 定义在 call_manager 仓」，涉及 call_manager 仓 |
| IMS 开关、VoLTE、VoNR、运营商配置 | `utils/src/cellular_call_config.cpp` 与 `utils/src/config_request.cpp` |
| 紧急号码 | `utils/src/emergency_utils.cpp` 与 `cellular_call_config.cpp` 的紧急号码列表 |
| 呼转、呼限、呼等、CLIP、CLIR | `utils/src/cellular_call_supplement.cpp` 与 `common/src/supplement_request_*.cpp` |
| MMI 码与 USSD | `utils/src/mmi_code_utils.cpp`、`control/src/control_base.cpp` 的 `IsNeedExecuteMMI` |
| IMS 服务连接 | `ims_service_interaction/` |
| 扩展钩子 | `telephony_ext_wrapper/`，新增钩子同时考虑 feature 宏 |

## 文件体量

下表为快照值，用于判断相对量级，不作为可校验断言。统计口径为含空行的行数。

| 文件 | 量级 |
|---|---|
| `services/manager/src/cellular_call_handler.cpp` | ~2200 |
| `services/manager/src/cellular_call_service.cpp` | ~1800 |
| `services/utils/src/cellular_call_supplement.cpp` | ~1750 |
| `services/ims_service_interaction/src/ims_call_callback_stub.cpp` | ~1650 |
| `services/utils/src/cellular_call_config.cpp` | ~1400 |
| `services/manager/src/cellular_call_stub.cpp` | ~1300 |
