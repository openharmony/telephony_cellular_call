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

#include "getcallrestriction_fuzzer.h"

#include <cstddef>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#define private public
#include "addcellularcalltoken_fuzzer.h"
#include "cellular_call_service.h"
#include "securec.h"
#include "system_ability_definition.h"

using namespace OHOS::Telephony;
namespace OHOS {
static bool g_isInited = false;
constexpr int32_t SLOT_NUM = 2;
constexpr int32_t VEDIO_STATE_NUM = 2;
constexpr int32_t BOOL_NUM = 2;
constexpr int32_t OFFSET_SIZE = 11;
constexpr size_t MAX_NUMBER_LEN = 99;
constexpr int32_t CALL_STATE_CODE = 21;

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
    std::vector<uint8_t> remainingData = provider.ConsumeRemainingBytes<uint8_t>();
    int32_t maxSize = static_cast<int32_t>(remainingData.size()) + OFFSET_SIZE;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteBuffer(remainingData.data(), remainingData.size());
    dataMessageParcel.RewindRead(0);
    uint32_t code = provider.ConsumeIntegral<uint32_t>();
    MessageParcel reply;
    MessageOption option;
    DelayedSingleton<CellularCallService>::GetInstance()->OnRemoteRequest(code, dataMessageParcel, reply, option);
}

void UnRegisterCallManagerCallBack(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    MessageParcel dataMessageParcel;
    std::vector<uint8_t> remainingData = provider.ConsumeRemainingBytes<uint8_t>();
    int32_t maxSize = static_cast<int32_t>(remainingData.size()) + OFFSET_SIZE;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteBuffer(remainingData.data(), remainingData.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnUnRegisterCallBackInner(dataMessageParcel, reply);
}

void IsEmergencyPhoneNumber(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t errorCode = provider.ConsumeIntegral<int32_t>();
    std::string phoneNum = provider.ConsumeRadomLengthString();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(errorCode);
    dataMessageParcel.WriteString(phoneNum);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnIsEmergencyPhoneNumberInner(dataMessageParcel, reply);
}

void HangUpAllConnection(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    std::vector<uint8_t> remainingData = provider.ConsumeRemainingBytes<uint8_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteBuffer(remainingData.data(), remainingData.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnHangUpAllConnectionInner(dataMessageParcel, reply);
}

void SetReadyToCall(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    int32_t callType = provider.ConsumeIntegral<int32_t>();
    bool isReadyToCall = provider.ConsumeBool();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(slotId);
    dataMessageParcel.WriteInt32(callType);
    dataMessageParcel.WriteBool(isReadyToCall);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetReadyToCallInner(dataMessageParcel, reply);
}

#ifdef SUPPORT_RTT_CALL
void UpdateImsRttCallMode(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    std::vector<uint8_t> remainingData = provider.ConsumeRemainingBytes<uint8_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteBuffer(remainingData.data(), remainingData.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnUpdateImsRttCallModeInner(dataMessageParcel, reply);
}
#endif

void GetCallTransferInfo(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t type = provider.ConsumeIntegral<int32_t>();
    std::vector<uint8_t> remainingData = provider.ConsumeRemainingBytes<uint8_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(type);
    dataMessageParcel.WriteBuffer(remainingData.data(), remainingData.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnGetCallTransferInner(dataMessageParcel, reply);
}

void GetCallWaiting(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }
    std::vector<uint8_t> remainingData = provider.ConsumeRemainingBytes<uint8_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteBuffer(remainingData.data(), remainingData.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnGetCallWaitingInner(dataMessageParcel, reply);
}

void SetCallWaiting(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t activate = provider.ConsumeIntegral<int32_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteBool(activate);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetCallWaitingInner(dataMessageParcel, reply);
}

void GetCallRestriction(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t facType = provider.ConsumeIntegral<int32_t>();
    std::vector<uint8_t> remainingData = provider.ConsumeRemainingBytes<uint8_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(facType);
    dataMessageParcel.WriteBuffer(remainingData.data(), remainingData.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnGetCallRestrictionInner(dataMessageParcel, reply);
}

void SetCallRestrictionPassword(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    int32_t facType = provider.ConsumeIntegral<int32_t>();
    std::vector<uint8_t> remainingData = provider.ConsumeRemainingBytes<uint8_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(slotId);
    dataMessageParcel.WriteInt32(facType);
    dataMessageParcel.WriteBuffer(remainingData.data(), remainingData.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetCallRestrictionPasswordInner(dataMessageParcel, reply);
}

void Dial(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    int32_t callId = provider.ConsumeIntegral<int32_t>();
    int32_t accountId = provider.ConsumeIntegral<int32_t>();
    int32_t videoState = provider.ConsumeIntegral<int32_t>();
    int32_t index = provider.ConsumeIntegral<int32_t>();
    std::string telNum = "000000000";
    std::string tempNum = provider.ConsumeRadomLengthString();
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
    DelayedSingleton<CellularCallService>::GetInstance()->OnDialInner(dataMessageParcel, reply);
}

void InviteToConference(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    std::string number = provider.ConsumeRadomLengthString();
    std::vector<std::string> numberList;
    numberList.push_back(number);
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteStringVector(numberList);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnInviteToConferenceInner(dataMessageParcel, reply);
}

void KickOutFromConference(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    int32_t callId = provider.ConsumeIntegral<int32_t>();
    int32_t accountId = provider.ConsumeIntegral<int32_t>();
    int32_t videoState = provider.ConsumeIntegral<int32_t>();
    int32_t index = provider.ConsumeIntegral<int32_t>();
    std::string telNum = "000000000";
    std::string tempNum = provider.ConsumeRadomLengthString();
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
    DelayedSingleton<CellularCallService>::GetInstance()->OnKickOutFromConferenceInner(dataMessageParcel, reply);
}

void DoFuzzCellularCallService1(FuzzedDataProvider& provider)
{
    auto cellularCallService = DelayedSingleton<CellularCallService>::GetInstance();
    cellularCallService->OnStart();
    uint32_t code = provider.ConsumeIntegralInRange<uint32_t>(1, CALL_STATE_CODE);
    if (provider.remaining_bytes() == 0) {
        return;
    }
    std::u16string service_token = u"OHOS.Telephony.CellularCallInterface";
    MessageOption option;
    MessageParcel dataParcel;
    MessageParcel replyParcel;
    std::vector<uint8_t> subData =
        provider.ConsumeBytes<uint8_t>(provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes()));
    dataParcel.WriteInterfaceToken(service_token);
    dataParcel.WriteBuffer(subData.data(), subData.size());
    cellularCallService->OnRemoteRequest(code, dataParcel, replyParcel, option);
}

void DoFuzzCellularCallService2(FuzzedDataProvider& provider)
{
    auto cellularCallService = DelayedSingleton<CellularCallService>::GetInstance();
    cellularCallService->OnStart();
    uint32_t code = provider.ConsumeIntegralInRange<uint32_t>(100, 106);
    if (provider.remaining_bytes() == 0) {
        return;
    }
    std::u16string service_token = u"OHOS.Telephony.CellularCallInterface";
    MessageOption option;
    MessageParcel dataParcel;
    MessageParcel replyParcel;
    std::vector<uint8_t> subData =
        fdp.ConsumeBytes<uint8_t>(provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes()));
    dataParcel.WriteInterfaceToken(service_token);
    dataParcel.WriteBuffer(subData.data(), subData.size());
    cellularCallService->OnRemoteRequest(code, dataParcel, replyParcel, option);
}

void DoFuzzCellularCallService3(FuzzedDataProvider& provider)
{
    auto cellularCallService = DelayedSingleton<CellularCallService>::GetInstance();
    cellularCallService->OnStart();
    uint32_t code = fdp.ConsumeIntegralInRange<uint32_t>(200, 210);
    if (fdp.remaining_bytes() == 0) {
        return;
    }
    std::u16string service_token = u"OHOS.Telephony.CellularCallInterface";
    MessageOption option;
    MessageParcel dataParcel;
    MessageParcel replyParcel;
    std::vector<uint8_t> subData =
        fdp.ConsumeBytes<uint8_t>(provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes()));
    dataParcel.WriteInterfaceToken(service_token);
    dataParcel.WriteBuffer(subData.data(), subData.size());
    cellularCallService->OnRemoteRequest(code, dataParcel, replyParcel, option);
}

void DoFuzzCellularCallService4(FuzzedDataProvider& provider)
{
    auto cellularCallService = DelayedSingleton<CellularCallService>::GetInstance();
    cellularCallService->OnStart();
    uint32_t code = provider.ConsumeIntegralInRange<uint32_t>(300, 315);
    if (fdp.remaining_bytes() == 0) {
        return;
    }
    std::u16string service_token = u"OHOS.Telephony.CellularCallInterface";
    MessageOption option;
    MessageParcel dataParcel;
    MessageParcel replyParcel;
    std::vector<uint8_t> subData =
        fdp.ConsumeBytes<uint8_t>(provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes()));
    dataParcel.WriteInterfaceToken(service_token);
    dataParcel.WriteBuffer(subData.data(), subData.size());
    cellularCallService->OnRemoteRequest(code, dataParcel, replyParcel, option);
}

void DoFuzzCellularCallService5(FuzzedDataProvider& provider)
{
    auto cellularCallService = DelayedSingleton<CellularCallService>::GetInstance();
    cellularCallService->OnStart();
    uint32_t code = provider.ConsumeIntegralInRange<uint32_t>(400, 410);
    if (provider.remaining_bytes() == 0) {
        return;
    }
    std::u16string service_token = u"OHOS.Telephony.CellularCallInterface";
    MessageOption option;
    MessageParcel dataParcel;
    MessageParcel replyParcel;
    std::vector<uint8_t> subData =
        fdp.ConsumeBytes<uint8_t>(provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes()));
    dataParcel.WriteInterfaceToken(service_token);
    dataParcel.WriteBuffer(subData.data(), subData.size());
    cellularCallService->OnRemoteRequest(code, dataParcel, replyParcel, option);
}

void DoSomethingInterestingWithMyAPI(FuzzedDataProvider& provider)
{
    OnRemoteRequest(provider);
    UnRegisterCallManagerCallBack(provider);
    IsEmergencyPhoneNumber(provider);
    HangUpAllConnection(provider);
    SetReadyToCall(provider);
#ifdef SUPPORT_RTT_CALL
    UpdateImsRttCallMode(provider);
#endif
    GetCallTransferInfo(provider);
    GetCallWaiting(provider);
    SetCallWaiting(provider);
    GetCallRestriction(provider);
    SetCallRestrictionPassword(provider);
    Dial(provider);
    InviteToConference(provider);
    KickOutFromConference(provider);
    DoFuzzCellularCallService1(provider);
    DoFuzzCellularCallService2(provider);
    DoFuzzCellularCallService3(provider);
    DoFuzzCellularCallService4(provider);
    DoFuzzCellularCallService5(provider);
    return;
}
} // namespace OHOS

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    OHOS::AddCellularCallTokenFuzzer token;
    if (data == nullptr || size == 0) {
        return;
    }
    /* Run your code on data */
    FuzzedDataProvider provider(data, size);
    OHOS::DoSomethingInterestingWithMyAPI(provider);
    return 0;
}
