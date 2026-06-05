/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "setimsfeaturevalue_fuzzer.h"

#include <cstddef>
#include <cstdint>
#define private public
#include "addcellularcalltoken_fuzzer.h"
#include "cellular_call_service.h"
#include "fuzzer/FuzzedDataProvider.h"
#include "securec.h"
#include "system_ability_definition.h"

using namespace OHOS::Telephony;
namespace OHOS {
static bool g_isInited = false;
constexpr int32_t BOOL_NUM = 2;
constexpr int32_t INT_NUM = 2;
constexpr int32_t VEDIO_STATE_NUM = 2;
constexpr int32_t OFFSET_SIZE = 11;
constexpr size_t MAX_NUMBER_LEN = 99;
constexpr int32_t IMS_CONFIG_ITEM_NUM = 2;
constexpr int32_t FEATURE_TYPE_NUM = 3;
constexpr int32_t MAX_SIZE = 10;

bool IsServiceInited()
{
    if (!g_isInited) {
        DelayedSingleton<CellularCallService>::GetInstance()->OnStart();
    }
    if (!g_isInited && (static_cast<int32_t>(DelayedSingleton<CellularCallService>::GetInstance()->state_) ==
                           static_cast<int32_t>(ServiceRunningState::STATE_RUNNING))) {
        g_isInited = true;
    }
    return g_isInited;
}

void OnRemoteRequest(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    MessageParcel dataMessageParcel;
    if (!dataMessageParcel.WriteInterfaceToken(CellularCallStub::GetDescriptor())) {
        return;
    }
    int32_t maxSize = provider.ConsumeIntegral<int32_t>() + OFFSET_SIZE;
    dataMessageParcel.WriteInt32(maxSize);
    std::vector<uint8_t> remaining_data = provider.ConsumeRemainingBytes<uint8_t>();
    dataMessageParcel.WriteBuffer(static_cast<void*>(remaining_data.data()), remaining_data.size());
    dataMessageParcel.RewindRead(0);
    uint32_t code = provider.ConsumeIntegral<uint32_t>();
    MessageParcel reply;
    MessageOption option;
    DelayedSingleton<CellularCallService>::GetInstance()->OnRemoteRequest(code, dataMessageParcel, reply, option);
}

void SetDomainPreferenceMode(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t mode = provider.ConsumeIntegral<int32_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(mode);
    std::vector<uint8_t> remaining_data = provider.ConsumeRemainingBytes<uint8_t>();
    dataMessageParcel.WriteBuffer(static_cast<void*>(remaining_data.data()), remaining_data.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetDomainPreferenceModeInner(dataMessageParcel, reply);
}

void GetDomainPreferenceMode(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    MessageParcel dataMessageParcel;
    std::vector<uint8_t> remaining_data = provider.ConsumeRemainingBytes<uint8_t>();
    dataMessageParcel.WriteBuffer(static_cast<void*>(remaining_data.data()), remaining_data.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetDomainPreferenceModeInner(dataMessageParcel, reply);
}

void SetImsSwitchStatus(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t activate = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteBool(activate);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetImsSwitchStatusInner(dataMessageParcel, reply);
}

void GetImsSwitchStatus(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    MessageParcel dataMessageParcel;
    std::vector<uint8_t> remaining_data = provider.ConsumeRemainingBytes<uint8_t>();
    dataMessageParcel.WriteBuffer(static_cast<void*>(remaining_data.data()), remaining_data.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnGetImsSwitchStatusInner(dataMessageParcel, reply);
}

void SetVoNRSwitchStatus(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t state = provider.ConsumeIntegral<int32_t>() % INT_NUM;
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(state);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetVoNRStateInner(dataMessageParcel, reply);
}

void GetVoNRSwitchStatus(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    MessageParcel dataMessageParcel;
    std::vector<uint8_t> remaining_data = provider.ConsumeRemainingBytes<uint8_t>();
    dataMessageParcel.WriteBuffer(static_cast<void*>(remaining_data.data()), remaining_data.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnGetVoNRStateInner(dataMessageParcel, reply);
}

void GetImsConfig(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t item = provider.ConsumeIntegral<int32_t>() % IMS_CONFIG_ITEM_NUM;
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(MAX_SIZE);
    dataMessageParcel.WriteInt32(slotId);
    dataMessageParcel.WriteInt32(item);
    std::vector<uint8_t> remaining_data = provider.ConsumeRemainingBytes<uint8_t>();
    dataMessageParcel.WriteBuffer(static_cast<void*>(remaining_data.data()), remaining_data.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnGetImsConfigInner(dataMessageParcel, reply);
}

void SetImsConfig(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t item = provider.ConsumeIntegral<int32_t>() % IMS_CONFIG_ITEM_NUM;
    std::string value = provider.ConsumeRandomLengthString();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(MAX_SIZE);
    dataMessageParcel.WriteInt32(slotId);
    dataMessageParcel.WriteInt32(item);
    dataMessageParcel.WriteString(value);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetImsConfigStringInner(dataMessageParcel, reply);
}

void GetImsFeatureValue(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t type = provider.ConsumeIntegral<int32_t>() % FEATURE_TYPE_NUM;
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(MAX_SIZE);
    dataMessageParcel.WriteInt32(slotId);
    dataMessageParcel.WriteInt32(type);
    std::vector<uint8_t> remaining_data = provider.ConsumeRemainingBytes<uint8_t>();
    dataMessageParcel.WriteBuffer(static_cast<void*>(remaining_data.data()), remaining_data.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnGetImsFeatureValueInner(dataMessageParcel, reply);
}

void SetImsFeatureValue(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t type = provider.ConsumeIntegral<int32_t>() % FEATURE_TYPE_NUM;
    int32_t value = provider.ConsumeIntegral<int32_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(MAX_SIZE);
    dataMessageParcel.WriteInt32(slotId);
    dataMessageParcel.WriteInt32(type);
    dataMessageParcel.WriteInt32(value);
    std::vector<uint8_t> remaining_data = provider.ConsumeRemainingBytes<uint8_t>();
    dataMessageParcel.WriteBuffer(static_cast<void*>(remaining_data.data()), remaining_data.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetImsFeatureValueInner(dataMessageParcel, reply);
}

void Reject(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t callId = provider.ConsumeIntegral<int32_t>();
    int32_t accountId = provider.ConsumeIntegral<int32_t>();
    int32_t videoState = provider.ConsumeIntegral<int32_t>() % VEDIO_STATE_NUM;
    int32_t index = provider.ConsumeIntegral<int32_t>();
    std::string telNum = "000000000";
    std::string tempNum = provider.ConsumeRandomLengthString();
    if (strlen(tempNum.c_str()) <= MAX_NUMBER_LEN) {
        telNum = tempNum;
    }
    size_t length = strlen(telNum.c_str()) + 1;
    CellularCallInfo callInfo;
    callInfo.slotId = slotId;
    callInfo.callId = callId;
    callInfo.accountId = accountId;
    callInfo.videoState = videoState;
    callInfo.index = index;
    if (strcpy_s(callInfo.phoneNum, length, telNum.c_str()) != EOK) {
        return;
    }
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteRawData(static_cast<const void *>(&callInfo), sizeof(CellularCallInfo));
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnRejectInner(dataMessageParcel, reply);
}

void HangUp(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    int32_t type = provider.ConsumeIntegral<int32_t>();
    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t callId = provider.ConsumeIntegral<int32_t>();
    int32_t accountId = provider.ConsumeIntegral<int32_t>();
    int32_t videoState = provider.ConsumeIntegral<int32_t>() % VEDIO_STATE_NUM;
    int32_t index = provider.ConsumeIntegral<int32_t>();
    std::string telNum = "000000000";
    std::string tempNum = provider.ConsumeRandomLengthString();
    if (strlen(tempNum.c_str()) <= MAX_NUMBER_LEN) {
        telNum = tempNum;
    }
    size_t length = strlen(telNum.c_str()) + 1;
    CellularCallInfo callInfo;
    callInfo.slotId = slotId;
    callInfo.callId = callId;
    callInfo.accountId = accountId;
    callInfo.videoState = videoState;
    callInfo.index = index;
    if (strcpy_s(callInfo.phoneNum, length, telNum.c_str()) != EOK) {
        return;
    }
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteInt32(type);
    dataMessageParcel.WriteRawData(static_cast<const void *>(&callInfo), sizeof(CellularCallInfo));
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnHangUpInner(dataMessageParcel, reply);
}

void DoSomethingInterestingWithMyAPI(const uint8_t *data, size_t size)
{
    if (data == nullptr || size == 0) {
        return;
    }
    FuzzedDataProvider provider(data, size);
    OnRemoteRequest(provider);
    SetDomainPreferenceMode(provider);
    GetDomainPreferenceMode(provider);
    SetImsSwitchStatus(provider);
    GetImsSwitchStatus(provider);
    GetImsConfig(provider);
    SetImsConfig(provider);
    GetImsFeatureValue(provider);
    SetImsFeatureValue(provider);
    Reject(provider);
    HangUp(provider);
    SetVoNRSwitchStatus(provider);
    GetVoNRSwitchStatus(provider);
    return;
}
} // namespace OHOS

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    OHOS::AddCellularCallTokenFuzzer token;
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}
