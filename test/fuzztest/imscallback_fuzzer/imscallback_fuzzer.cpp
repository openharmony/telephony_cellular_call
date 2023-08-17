/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "imscallback_fuzzer.h"

#include <cstddef>
#include <cstdint>
#define private public
#include "addcellularcalltoken_fuzzer.h"
#include "cellular_call_service.h"
#include "ims_call_callback_stub.h"
#include "ims_call_client.h"
#include "ims_call_proxy.h"
#include "securec.h"
#include "system_ability_definition.h"
#include "telephony_types.h"

using namespace OHOS::Telephony;
namespace OHOS {
static bool g_isInited = false;
constexpr int32_t SERVICE_STATE_RUNNING = 1;
constexpr int32_t SLOT_NUM = 2;
constexpr int32_t BOOL_NUM = 2;
constexpr int32_t SERIAL_NUM = 3;
constexpr int32_t ERROR_NUM = 15;
constexpr int32_t TYPE_NUM = 5;

bool IsServiceInited()
{
    auto service = DelayedSingleton<CellularCallService>::GetInstance();
    if (service == nullptr) {
        return g_isInited;
    }
    if (service->GetServiceRunningState() != SERVICE_STATE_RUNNING) {
        service->OnStart();
    }
    if (!g_isInited && service->GetServiceRunningState() == SERVICE_STATE_RUNNING) {
        g_isInited = true;
    }
    return g_isInited;
}

void OnRemoteRequest(const uint8_t *data, size_t size)
{
    MessageParcel dataMessageParcel;
    if (!dataMessageParcel.WriteInterfaceToken(ImsCallCallbackStub::GetDescriptor())) {
        return;
    }
    uint32_t code = static_cast<uint32_t>(size);
    MessageParcel reply;
    MessageOption option;
    DelayedSingleton<ImsCallCallbackStub>::GetInstance()->OnRemoteRequest(code, dataMessageParcel, reply, option);
}

void TestImsCallCallbackFunction(const uint8_t *data, size_t size, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = static_cast<int32_t>(size % SLOT_NUM);
    HRilRadioResponseInfo rilRadioResponse;
    rilRadioResponse.flag = static_cast<int32_t>(size % BOOL_NUM);
    rilRadioResponse.serial = static_cast<int32_t>(size % SERIAL_NUM);
    rilRadioResponse.error = static_cast<HRilErrType>(size % ERROR_NUM);
    rilRadioResponse.type = static_cast<HRilResponseTypes>(size % TYPE_NUM);
    MessageParcel answerData;
    MessageParcel answerReply;
    answerData.WriteInt32(slotId);
    answerData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo));
    stub->OnAnswerResponseInner(answerData, answerReply);

    MessageParcel dialData;
    MessageParcel dialReply;
    dialData.WriteInt32(slotId);
    dialData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo));
    stub->OnDialResponseInner(dialData, dialReply);

    MessageParcel imsCallsData;
    MessageParcel imsCallsReply;
    imsCallsData.WriteInt32(slotId);
    imsCallsData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo));
    stub->OnGetImsCallsDataResponseInner(imsCallsData, imsCallsReply);

    MessageParcel hangupData;
    MessageParcel hangupReply;
    hangupData.WriteInt32(slotId);
    hangupData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo));
    stub->OnHangUpResponseInner(hangupData, hangupReply);

    MessageParcel rejectData;
    MessageParcel rejectReply;
    rejectData.WriteInt32(slotId);
    rejectData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo));
    stub->OnRejectResponseInner(rejectData, rejectReply);

    MessageParcel sendDtmfData;
    MessageParcel sendDtmfReply;
    sendDtmfData.WriteInt32(slotId);
    sendDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo));
    stub->OnSendDtmfResponseInner(sendDtmfData, sendDtmfReply);

    MessageParcel startDtmfData;
    MessageParcel startDtmfReply;
    startDtmfData.WriteInt32(slotId);
    startDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo));
    stub->OnStartDtmfResponseInner(startDtmfData, startDtmfReply);

    MessageParcel stopDtmfData;
    MessageParcel stopDtmfReply;
    stopDtmfData.WriteInt32(slotId);
    stopDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo));
    stub->OnStopDtmfResponseInner(stopDtmfData, stopDtmfReply);
}

void TestImsCallCallbackExFunction(const uint8_t *data, size_t size, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = static_cast<int32_t>(size % SLOT_NUM);
    std::string number(reinterpret_cast<const char *>(data), size);
    MessageParcel muteData;
    MessageParcel muteReply;
    MuteControlResponse muteResponse;
    muteResponse.result = static_cast<int32_t>(size % BOOL_NUM);
    muteResponse.value = static_cast<int32_t>(size % BOOL_NUM);
    muteData.WriteInt32(slotId);
    muteData.WriteRawData((const void *)&muteResponse, sizeof(MuteControlResponse));
    stub->OnSetMuteResponseInner(muteData, muteReply);

    MessageParcel ringData;
    MessageParcel ringReply;
    RingbackVoice ringback;
    ringback.status = static_cast<int32_t>(size % BOOL_NUM);
    ringData.WriteInt32(slotId);
    ringData.WriteRawData((const void *)&ringback, sizeof(RingbackVoice));
    stub->OnCallRingBackReportInner(ringData, ringReply);

    MessageParcel callData;
    MessageParcel callReply;
    callData.WriteInt32(slotId);
    stub->OnCallStateChangeReportInner(callData, callReply);

    MessageParcel failData;
    MessageParcel failReply;
    DisconnectedDetails details;
    details.reason = static_cast<DisconnectedReason>(size);
    details.message = number;
    slotId = ERROR_NUM;
    failData.WriteInt32(slotId);
    failData.WriteInt32(static_cast<int32_t>(details.reason));
    failData.WriteString(details.message);
    stub->OnLastCallFailReasonResponseInner(failData, failReply);
}

void TestImsConfigCallbackFunction(const uint8_t *data, size_t size, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = static_cast<int32_t>(size % SLOT_NUM);
    HRilRadioResponseInfo rilRadioResponse;
    rilRadioResponse.flag = static_cast<int32_t>(size % BOOL_NUM);
    rilRadioResponse.serial = static_cast<int32_t>(size % SERIAL_NUM);
    rilRadioResponse.error = static_cast<HRilErrType>(size % ERROR_NUM);
    rilRadioResponse.type = static_cast<HRilResponseTypes>(size % TYPE_NUM);

    MessageParcel setImsSwitchData;
    MessageParcel setImsSwitchReply;
    setImsSwitchData.WriteInt32(slotId);
    setImsSwitchData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo));
    stub->OnSetImsSwitchResponseInner(setImsSwitchData, setImsSwitchReply);

    MessageParcel holdCallData;
    MessageParcel holdCallReply;
    holdCallData.WriteInt32(slotId);
    holdCallData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo));
    stub->OnHoldCallResponseInner(holdCallData, holdCallReply);

    MessageParcel switchCallData;
    MessageParcel switchCallReply;
    switchCallData.WriteInt32(slotId);
    switchCallData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo));
    stub->OnSwitchCallResponseInner(switchCallData, switchCallReply);

    MessageParcel unholdData;
    MessageParcel unholdReply;
    unholdData.WriteInt32(slotId);
    unholdData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo));
    stub->OnUnHoldCallResponseInner(unholdData, unholdReply);

    MessageParcel getImsSwitchData;
    MessageParcel getImsSwitchReply;
    getImsSwitchData.WriteInt32(slotId);
    getImsSwitchData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo));
    stub->OnGetImsSwitchResponseInner(getImsSwitchData, getImsSwitchReply);
}

void WriteSsResult(MessageParcel &in, SsBaseResult &ssResult, const int32_t action, const int32_t state, size_t size)
{
    ssResult.index = static_cast<int32_t>(size % SERIAL_NUM);
    ssResult.result = static_cast<int32_t>(size % BOOL_NUM);
    ssResult.reason = static_cast<int32_t>(size);
    in.WriteInt32(ssResult.index);
    in.WriteInt32(ssResult.result);
    in.WriteInt32(ssResult.reason);
    in.WriteString(ssResult.message);
    in.WriteInt32(action);
    in.WriteInt32(state);
}

void TestImsUTCallbackFunction(const uint8_t *data, size_t size, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = static_cast<int32_t>(size % SLOT_NUM);
    std::string number(reinterpret_cast<const char *>(data), size);

    SsBaseResult normalResult;
    normalResult.index = static_cast<int32_t>(size % SERIAL_NUM);
    normalResult.result = static_cast<int32_t>(size % BOOL_NUM);
    normalResult.reason = static_cast<int32_t>(size);
    normalResult.message = number;

    MessageParcel mData;
    MessageParcel mReply;
    mData.WriteInt32(slotId);
    mData.WriteInt32(normalResult.index);
    mData.WriteInt32(normalResult.result);
    mData.WriteInt32(normalResult.reason);
    mData.WriteString(normalResult.message);
    stub->OnSetCallRestrictionResponseInner(mData, mReply);
    stub->OnSetCallTransferResponseInner(mData, mReply);
    stub->OnSetCallWaitingResponseInner(mData, mReply);
    stub->OnSetClipResponseInner(mData, mReply);
    stub->OnSetClirResponseInner(mData, mReply);
    stub->OnSetColpResponseInner(mData, mReply);
    stub->OnSetColrResponseInner(mData, mReply);

    MessageParcel crData;
    MessageParcel crReply;
    CallRestrictionResult crResult;
    crResult.result.message = number;
    crResult.status = static_cast<int32_t>(size % BOOL_NUM);
    crResult.classCw = static_cast<int32_t>(size);
    crData.WriteInt32(slotId);
    WriteSsResult(crData, crResult.result, crResult.status, crResult.classCw, size);
    stub->OnGetCallRestrictionResponseInner(crData, crReply);

    MessageParcel cwData;
    MessageParcel cwReply;
    CallWaitResult cwResult;
    cwResult.result.message = number;
    cwResult.status = static_cast<int32_t>(size % BOOL_NUM);
    cwResult.classCw = static_cast<int32_t>(size);
    cwData.WriteInt32(slotId);
    WriteSsResult(cwData, cwResult.result, cwResult.status, cwResult.classCw, size);
    stub->OnGetCallWaitingResponseInner(cwData, cwReply);

    MessageParcel clipData;
    MessageParcel clipReply;
    GetClipResult clipResult;
    clipResult.result.message = number;
    clipResult.clipStat = static_cast<int32_t>(size);
    clipResult.action = static_cast<int32_t>(size);
    clipData.WriteInt32(slotId);
    WriteSsResult(clipData, clipResult.result, clipResult.action, clipResult.clipStat, size);
    stub->OnGetClipResponseInner(clipData, clipReply);
}

void TestUTCallbackFunction(const uint8_t *data, size_t size, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = static_cast<int32_t>(size % SLOT_NUM);
    std::string number(reinterpret_cast<const char *>(data), size);

    MessageParcel clirData;
    MessageParcel clirReply;
    GetClirResult clirResult;
    clirResult.result.message = number;
    clirResult.clirStat = static_cast<int32_t>(size);
    clirResult.action = static_cast<int32_t>(size);
    clirData.WriteInt32(slotId);
    WriteSsResult(clirData, clirResult.result, clirResult.action, clirResult.clirStat, size);
    stub->OnGetClirResponseInner(clirData, clirReply);

    MessageParcel colpData;
    MessageParcel colpReply;
    GetColpResult colpResult;
    colpResult.result.message = number;
    colpResult.colpStat = static_cast<int32_t>(size);
    colpResult.action = static_cast<int32_t>(size);
    colpData.WriteInt32(slotId);
    WriteSsResult(colpData, colpResult.result, colpResult.action, colpResult.colpStat, size);
    stub->OnGetColpResponseInner(colpData, colpReply);

    MessageParcel colrData;
    MessageParcel colrReply;
    GetColrResult colrResult;
    colrResult.result.message = number;
    colrResult.colrStat = static_cast<int32_t>(size);
    colrResult.action = static_cast<int32_t>(size);
    colrData.WriteInt32(slotId);
    WriteSsResult(colrData, colrResult.result, colrResult.action, colrResult.colrStat, size);
    stub->OnGetColrResponseInner(colrData, colrReply);
}

void TestCFCallbackFunction(const uint8_t *data, size_t size, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = static_cast<int32_t>(size % SLOT_NUM);
    std::string number(reinterpret_cast<const char *>(data), size);
    MessageParcel cfData;
    MessageParcel cfReply;
    SsBaseResult normalResult;
    CallForwardQueryResult cfCall;
    normalResult.message = number;
    int32_t callSize = 1;
    int32_t flag = static_cast<int32_t>(size % BOOL_NUM);
    cfCall.serial = static_cast<int32_t>(size % SERIAL_NUM);
    cfCall.result = static_cast<int32_t>(size % BOOL_NUM);
    cfCall.status = static_cast<int32_t>(size % BOOL_NUM);
    cfCall.classx = static_cast<int32_t>(size);
    cfCall.number = number;
    cfCall.type = static_cast<int32_t>(size);
    cfCall.reason = static_cast<int32_t>(size);

    cfData.WriteInt32(slotId);
    WriteSsResult(cfData, normalResult, callSize, flag, size);
    cfData.WriteInt32(callSize);

    if (!cfData.WriteInt32(cfCall.serial) || !cfData.WriteInt32(cfCall.result) || !cfData.WriteInt32(cfCall.status) ||
        !cfData.WriteInt32(cfCall.classx) || !cfData.WriteString(cfCall.number) || !cfData.WriteInt32(cfCall.type) ||
        !cfData.WriteInt32(cfCall.reason) || !cfData.WriteInt32(cfCall.time) || !cfData.WriteInt32(cfCall.startHour) ||
        !cfData.WriteInt32(cfCall.startMinute) || !cfData.WriteInt32(cfCall.endHour) ||
        !cfData.WriteInt32(cfCall.endMinute)) {
        return;
    }
    stub->OnGetCallTransferResponseInner(cfData, cfReply);
}

void DoSomethingInterestingWithMyAPI(const uint8_t *data, size_t size)
{
    if (data == nullptr || size == 0) {
        return;
    }

    if (!IsServiceInited()) {
        return;
    }

    sptr<ImsCallCallbackStub> stub = (std::make_unique<ImsCallCallbackStub>()).release();
    if (stub == nullptr) {
        return;
    }

    OnRemoteRequest(data, size);
    TestImsCallCallbackFunction(data, size, stub);
    TestImsCallCallbackExFunction(data, size, stub);
    TestImsConfigCallbackFunction(data, size, stub);
    TestImsUTCallbackFunction(data, size, stub);
    TestUTCallbackFunction(data, size, stub);
    TestCFCallbackFunction(data, size, stub);
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
