# 编译与测试

← 返回 [`AGENTS.md`](../../AGENTS.md)

---

## 构建定位

本仓是 OpenHarmony 的一个部件，不能独立构建，源码树中的位置为 `<OHOS_ROOT>/base/telephony/cellular_call`。

| 项 | 值 |
|---|---|
| `part_name` | `cellular_call` |
| `subsystem_name` | `telephony` |
| 服务库 | `//base/telephony/cellular_call:tel_cellular_call` |
| SA 配置 | `//base/telephony/cellular_call/sa_profile:cellular_call_sa_profile` |
| IMS 接口库 | `//base/telephony/cellular_call/interfaces/innerkits/ims:tel_ims_call_api` |
| 卫星接口库 | `//base/telephony/cellular_call/interfaces/innerkits/satellite:tel_satellite_call_api` |
| 参考 IMS 服务 | `//base/telephony/cellular_call/vendor/ims:tel_ims` |
| 测试组 | `test:unittest`、`test/fuzztest:fuzztest` |

### 编译选项

服务库开启 `cfi`、`cfi_cross_dso`、`branch_protector_ret = "pac_ret"`，编译选项含 `-fstack-protector-all` 与 `-O2`。

`-fno-exceptions` 只出现在测试 gni 的 `cellular_call_cflags_cc` 中，服务 `BUILD.gn` 没有该选项。服务源码中没有 `try`、`catch`、`dynamic_cast`，这是编码约定而非编译器强制；新增代码保持不用，否则测试目标编译失败。

### 静态检查工具

本仓没有部件内的 lint、格式化配置或静态分析脚本（无 `.clang-format`、`.clang-tidy`、`cpplint` 配置）。代码风格与静态检查由 OpenHarmony 门禁流水线执行，本地以编译告警与本文「无构建环境时的静态自检」替代，不要查找不存在的本地 lint 命令。

### 构建命令

```shell
# 整个部件
./build.sh --product-name <product> --build-target cellular_call --ccache

# 服务库
./build.sh --product-name <product> --build-target "//base/telephony/cellular_call:tel_cellular_call"

# 全部单测
./build.sh --product-name <product> --build-target "//base/telephony/cellular_call/test:unittest"

# 单个测试目标
./build.sh --product-name <product> \
  --build-target "//base/telephony/cellular_call/test/unittest/imstest:cellular_call_ims2_test"
```

`<product>` 取决于开发板，常见 `rk3568`。

---

## 两份源文件清单

服务库与测试使用**两份独立维护**的清单：

| 清单 | 用途 |
|---|---|
| 根目录 `BUILD.gn` 的 `sources` | 服务库 `tel_cellular_call` |
| `test/cellular_call_test.gni` 的 `cellular_call_base_src` | 静态库 `cellular_call_test_base`，全部单测目标链接它 |

两份清单并不完全一致，默认配置（`cellular_call_satellite = false`）下测试清单多出 4 个文件：`ims_call_callback_proxy.cpp`、`satellite_call_callback_proxy.cpp` 两个回调代理，以及 `cellular_call_connection_satellite.cpp`、`satellite_control.cpp`。后两个在服务 `BUILD.gn` 中位于 `if (cellular_call_satellite)` 块内，在测试 gni 中无条件编译。这是现状差异，核对清单同步时不要据此判定为遗漏。宏定义同样有两份：`cellularcall.gni` 的 `global_defines` 与测试 gni 的 `cellular_call_defines`。

新增源文件清单：

1. 根目录 `BUILD.gn` 的 `sources` 加入路径；只在某个 feature 下编译的，放进对应条件块。
2. `test/cellular_call_test.gni` 的 `cellular_call_base_src` 加入同一路径。
3. 新增 include 目录时，两处都加。
4. 新增外部依赖时，`BUILD.gn`、测试 gni 的 `cellular_call_external_deps`、`bundle.json` 的 `deps.components` 都加。

漏加测试清单的表现：服务库编译正常，单测链接报未定义符号。

---

## 测试目标

`cellular_call_test_base` 是 `ohos_static_library`，关闭 CFI，链接 `core_service:ffrt_mocked`。所有单测文件以 `#define private public` 与 `#define protected public` 访问私有成员。

### 测试替身的可用性

`test/mock/` 提供 `mock_network_search.h`、`mock_sim_manager.h`、`mock_tel_ril_manager.h`，通过 `CoreManagerInner::GetInstance().OnInit(...)` 注入。**只有部分目标配置了替身所需的 include 与 gmock 依赖。** 下表是 master 的状态，在其他分支上先读目标自己的 `BUILD.gn` 确认：

| 目录 | 已配置 `test/mock` 与 gmock 的目标 | 未配置的目标 |
|---|---|---|
| `cstest` | `cellular_call_cs1_test`、`cellular_call_cs_calloperation_test` | `cellular_call_cs2_test` |
| `imstest` | `cellular_call_ims1_test`、`cellular_call_ims2_test`、`cellular_call_ims_zero_branch1_test`、`cellular_call_ims_emergency_utils_test` | 其余 11 个 |
| `satellitetest` | 无 | 全部 3 个 |

构造网络状态的写法：`NetworkState` 来自 core_service，本仓代码树中没有它的头文件实现，测试中直接 `sptr<NetworkState> state = new NetworkState();`，借助 `#define private public` 给 `csRegStatus_`、`psRegStatus_` 赋值，再让 `mockNetworkSearch` 的 `GetNetworkStatus` 返回它：

```cpp
sptr<NetworkState> state = new NetworkState();
state->csRegStatus_ = RegServiceState::REG_STATE_IN_SERVICE;
state->psRegStatus_ = RegServiceState::REG_STATE_IN_SERVICE;
EXPECT_CALL(*mockNetworkSearch, GetNetworkStatus(_, _))
    .WillRepeatedly([&](int32_t, sptr<NetworkState> &status) {
        status = state;
        return 0;
    });
```

在未配置的目标中使用 `EXPECT_CALL` 前，先在该目标的 `BUILD.gn` 中加入 `"${CELLULAR_CALL_PATH}/test/mock"` 到 `include_dirs`，加入 `googletest:gmock_main` 到 `external_deps`；或把用例写进已配置的目标。

### 目标一览

| 目录 | 目标 | 适用 |
|---|---|---|
| `cstest` | `cellular_call_cs1_test`、`cellular_call_cs2_test`、`cellular_call_cs_calloperation_test` | CS 拨号、通话操作 |
| `imstest` | `cellular_call_ims1_test`、`cellular_call_ims2_test` | IMS 通道、配置时序、处理器响应 |
| `imstest` | `cellular_call_ims_zero_branch_test`、`cellular_call_ims_zero_branch1_test` | 分支覆盖，配置与处理器 |
| `imstest` | `cellular_call_ims_config_request_test` | 配置请求 |
| `imstest` | `cellular_call_ims_emergency_utils_test` | 紧急号码判定 |
| `imstest` | `cellular_call_ims_cellular_call_supplement_test`、`cellular_call_ims_mmi_code_message_test`、`cellular_call_ims_standardize_utils_test` | 补充业务、MMI 码、号码规范化 |
| `imstest` | `cellular_call_ims_cellular_call_stub_test`、`cellular_call_ims_callback_proxy_test`、`cellular_call_ims_callback_stub_test`、`cellular_call_ims_call_callback_stub_test` | IPC 分发与回调 |
| `imstest` | `cellular_call_ims_connection_test`、`cellular_call_ims_hisysevent_test` | 连接对象、打点 |
| `satellitetest` | `cellular_call_satellite_callback_test`、`cellular_call_satellite_test`、`cellular_call_satellite_zero_branch_test` | 卫星通道，仅 `cellular_call_satellite` 为真时构建 |

注意事项：

- 新增测试目标后，必须在 `test/BUILD.gn` 的 `group("unittest")` 中登记，否则不参与构建。
- 各测试目标的 `BUILD.gn` 样板高度重复，修改单个目标时，以 `sources` 中的测试文件名作为定位锚点，改完后确认改动落在目标自己的块内。
- `vendor/ims/test/unittest/ims_service_gtest:tel_vendor_ims_service_gtest` 没有登记到 `bundle.json` 的测试组，跟随部件测试构建时不会编译。
- 模糊测试有 15 个目标，`test/fuzztest/common_fuzzer/` 只提供共用授权代码。新增 fuzzer 目录后，必须在 `test/fuzztest/BUILD.gn` 中登记。

### 运行

```shell
hdc shell /data/test/cellular_call_ims2_test
hdc shell /data/test/cellular_call_ims2_test --gtest_filter=Ims2Test.<用例名>
hdc shell /data/test/cellular_call_ims2_test --gtest_list_tests
```

### 用例编写约定

- 用例前三行注释：`@tc.number`、`@tc.name`、`@tc.desc`。
- `CellularCallConfig` 的 static 成员跨用例共享，用例修改过的 map 与标志要在用例末尾或 `TearDown` 中恢复。
- 断言被修复的具体状态，例如标志在前提成立与不成立时的取值，不要只验证不崩溃。

---

## 无构建环境时的静态自检

| # | 检查 | 方法 |
|---|---|---|
| 1 | 新增 `.cpp` 同时进入 `BUILD.gn` 与测试 gni | 两处搜索文件名 |
| 2 | 新增宏在 `cellularcall.gni`、`bundle.json`、测试 gni 中齐全 | 三处搜索 |
| 3 | 修改锁类型时，声明、定义、全部加锁点一致 | 搜索锁名 |
| 4 | 新增锁与同文件既有锁类型一致 | 核对头文件 |
| 5 | 持锁区间内没有调用加同一把锁的函数 | 搜索被调函数内部 |
| 6 | 延迟动作标志的置位、消费、清位点齐全且清位只在前提成立时发生 | 搜索标志名 |
| 7 | 每个 Service 接口先校验卡槽号 | 核对函数入口 |
| 8 | 扩展钩子调用前判空 | 搜索 `TELEPHONY_EXT_WRAPPER.` |
| 9 | 新增 IPC 接口的代理写入与 Stub 读取一致 | 两仓并排比对 |
| 10 | 使用 `EXPECT_CALL` 的目标已配置替身 include 与 gmock | 核对目标 `BUILD.gn` |
| 11 | 没有 `try`、`catch`、`dynamic_cast` | 全文搜索 |
| 12 | 日志中没有号码 | 核对新增 `TELEPHONY_LOG*` |

---

## DoD

完整 DoD 见 [`AGENTS.md`](../../AGENTS.md)「最小验证闭环」。最小要求：

- [ ] 本文静态自检全部通过。
- [ ] 有构建环境时，`cellular_call` 部件与相关测试目标编译通过并运行全绿。
- [ ] 至少一条带断言的用例覆盖改动分支。
- [ ] [`high-risk.md`](high-risk.md)「变更风险矩阵」中的对应项已确认。
