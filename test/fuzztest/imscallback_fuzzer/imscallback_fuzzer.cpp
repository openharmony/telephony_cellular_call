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
#include "fuzzer/FuzzedDataProvider.h"

using namespace OHOS::Telephony;
namespace OHOS {
static bool g_isInited = false;
constexpr int32_t SLOT_NUM = 2;
constexpr int32_t BOOL_NUM = 2;
constexpr int32_t SERIAL_NUM = 3;
constexpr int32_t ERROR_NUM = 15;
constexpr int32_t TYPE_NUM = 5;
constexpr int32_t CALL_INDEX_NUM = 8;
constexpr int32_t REQUEST_NUM = 6;
constexpr int32_t VIDEO_CALL_EVENT_NUM = 4;
constexpr int32_t DISCONNECTEDREASON_UNKNOWN = 1279;

bool IsServiceInited()
{
    auto service = DelayedSingleton<CellularCallService>::GetInstance();
    if (service == nullptr) {
        return g_isInited;
    }
    if (service->state_ != ServiceRunningState::STATE_RUNNING) {
        service->state_ = ServiceRunningState::STATE_RUNNING;
    }
    if (!g_isInited && service->state_ == ServiceRunningState::STATE_RUNNING) {
        g_isInited = true;
    }
    return g_isInited;
}

void OnRemoteRequest(FuzzedDataProvider& provider)
{
    MessageParcel dataMessageParcel;
    if (!dataMessageParcel.WriteInterfaceToken(ImsCallCallbackStub::GetDescriptor())) {
        return;
    }
    int32_t slotId = ERROR_NUM;
    dataMessageParcel.WriteInt32(slotId);
    uint32_t code = provider.ConsumeIntegral<uint32_t>();
    MessageParcel reply;
    MessageOption option;
    DelayedSingleton<ImsCallCallbackStub>::GetInstance()->OnRemoteRequest(code, dataMessageParcel, reply, option);
}

void TestImsCallCallbackFunction(FuzzedDataProvider& provider, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = ERROR_NUM;
    RadioResponseInfo rilRadioResponse;
    rilRadioResponse.flag = provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM);
    rilRadioResponse.serial = provider.ConsumeIntegralInRange<int32_t>(0, SERIAL_NUM);
    rilRadioResponse.error = static_cast<ErrType>(provider.ConsumeIntegralInRange<int32_t>(0, ERROR_NUM));
    rilRadioResponse.type = static_cast<ResponseTypes>(provider.ConsumeIntegralInRange<int32_t>(0, TYPE_NUM));
    MessageParcel answerData;
    MessageParcel answerReply;
    answerData.WriteInt32(slotId);
    stub->OnAnswerResponseInner(answerData, answerReply);

    MessageParcel dialData;
    MessageParcel dialReply;
    dialData.WriteInt32(slotId);
    stub->OnDialResponseInner(dialData, dialReply);

    MessageParcel hangupData;
    MessageParcel hangupReply;
    hangupData.WriteInt32(slotId);
    stub->OnHangUpResponseInner(hangupData, hangupReply);

    MessageParcel rejectData;
    MessageParcel rejectReply;
    rejectData.WriteInt32(slotId);
    stub->OnRejectResponseInner(rejectData, rejectReply);

    MessageParcel sendDtmfData;
    MessageParcel sendDtmfReply;
    sendDtmfData.WriteInt32(slotId);
    sendDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo));
    stub->OnSendDtmfResponseInner(sendDtmfData, sendDtmfReply);

    MessageParcel startDtmfData;
    MessageParcel startDtmfReply;
    startDtmfData.WriteInt32(slotId);
    startDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo));
    stub->OnStartDtmfResponseInner(startDtmfData, startDtmfReply);

    MessageParcel stopDtmfData;
    MessageParcel stopDtmfReply;
    stopDtmfData.WriteInt32(slotId);
    stopDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo));
    stub->OnStopDtmfResponseInner(stopDtmfData, stopDtmfReply);

    MessageParcel imsCallsData;
    MessageParcel imsCallsReply;
    slotId = ERROR_NUM;
    imsCallsData.WriteInt32(slotId);
    imsCallsData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo));
    stub->OnGetImsCallsDataResponseInner(imsCallsData, imsCallsReply);
}

void TestImsCallCallbackExFunction(FuzzedDataProvider& provider, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = ERROR_NUM;
    std::string number = provider.ConsumeRandomLengthString();
    MessageParcel muteData;
    MessageParcel muteReply;
    MuteControlResponse muteResponse;
    muteResponse.result = provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM);
    muteResponse.value = provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM);
    muteData.WriteInt32(slotId);
    muteData.WriteRawData((const void *)&muteResponse, sizeof(MuteControlResponse));
    stub->OnSetMuteResponseInner(muteData, muteReply);

    MessageParcel ringData;
    MessageParcel ringReply;
    RingbackVoice ringback;
    ringback.status = provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM);
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
    details.reason = static_cast<DisconnectedReason>(
        provider.ConsumeIntegralInRange<int32_t>(1, DISCONNECTEDREASON_UNKNOWN));
    details.message = number;
    slotId = ERROR_NUM;
    failData.WriteInt32(slotId);
    failData.WriteInt32(static_cast<int32_t>(details.reason));
    failData.WriteString(details.message);
    stub->OnLastCallFailReasonResponseInner(failData, failReply);
}

void TestImsConfigCallbackFunction(FuzzedDataProvider& provider, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = ERROR_NUM;
    RadioResponseInfo rilRadioResponse;
    rilRadioResponse.flag = provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM);
    rilRadioResponse.serial = provider.ConsumeIntegralInRange<int32_t>(0, SERIAL_NUM);
    rilRadioResponse.error = static_cast<ErrType>(provider.ConsumeIntegralInRange<int32_t>(0, ERROR_NUM));
    rilRadioResponse.type = static_cast<ResponseTypes>(provider.ConsumeIntegralInRange<int32_t>(0, TYPE_NUM));

    MessageParcel setImsSwitchData;
    MessageParcel setImsSwitchReply;
    setImsSwitchData.WriteInt32(slotId);
    setImsSwitchData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo));
    stub->OnSetImsSwitchResponseInner(setImsSwitchData, setImsSwitchReply);

    MessageParcel holdCallData;
    MessageParcel holdCallReply;
    holdCallData.WriteInt32(slotId);
    stub->OnHoldCallResponseInner(holdCallData, holdCallReply);

    MessageParcel switchCallData;
    MessageParcel switchCallReply;
    switchCallData.WriteInt32(slotId);
    stub->OnSwitchCallResponseInner(switchCallData, switchCallReply);

    MessageParcel unholdData;
    MessageParcel unholdReply;
    unholdData.WriteInt32(slotId);
    stub->OnUnHoldCallResponseInner(unholdData, unholdReply);

    MessageParcel getImsSwitchData;
    MessageParcel getImsSwitchReply;
    getImsSwitchData.WriteInt32(slotId);
    getImsSwitchData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo));
    stub->OnGetImsSwitchResponseInner(getImsSwitchData, getImsSwitchReply);
}

void WriteSsResult(MessageParcel &in, SsBaseResult &ssResult, const int32_t action, const int32_t state)
{
    ssResult.index = provider.ConsumeIntegralInRange<int32_t>(0, SERIAL_NUM);
    ssResult.result = provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM);
    ssResult.reason = provider.ConsumeIntegral<int32_t>();
    in.WriteInt32(ssResult.index);
    in.WriteInt32(ssResult.result);
    in.WriteInt32(ssResult.reason);
    in.WriteString(ssResult.message);
    in.WriteInt32(action);
    in.WriteInt32(state);
}

void TestImsUTCallbackFunction(FuzzedDataProvider& provider, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    std::string number = provider.ConsumeRandomLengthString();
    SsBaseResult normalResult;
    normalResult.index = provider.ConsumeIntegralInRange<int32_t>(0, SERIAL_NUM);
    normalResult.result = provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM);
    normalResult.reason = provider.ConsumeIntegral<int32_t>();
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
    crResult.status = provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM);
    crResult.classCw = provider.ConsumeIntegral<int32_t>();
    crData.WriteInt32(slotId);
    WriteSsResult(crData, crResult.result, crResult.status, crResult.classCw);
    stub->OnGetCallRestrictionResponseInner(crData, crReply);

    MessageParcel cwData;
    MessageParcel cwReply;
    CallWaitResult cwResult;
    cwResult.result.message = number;
    cwResult.status = provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM);
    cwResult.classCw = provider.ConsumeIntegral<int32_t>();
    cwData.WriteInt32(slotId);
    WriteSsResult(cwData, cwResult.result, cwResult.status, cwResult.classCw);
    stub->OnGetCallWaitingResponseInner(cwData, cwReply);

    MessageParcel clipData;
    MessageParcel clipReply;
    GetClipResult clipResult;
    clipResult.result.message = number;
    clipResult.clipStat = provider.ConsumeIntegral<int32_t>();
    clipResult.action = provider.ConsumeIntegral<int32_t>();
    clipData.WriteInt32(slotId);
    WriteSsResult(clipData, clipResult.result, clipResult.action, clipResult.clipStat);
    stub->OnGetClipResponseInner(clipData, clipReply);
}

void TestUTCallbackFunction(FuzzedDataProvider& provider, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    std::string number = provider.ConsumeRandomLengthString();

    MessageParcel clirData;
    MessageParcel clirReply;
    GetClirResult clirResult;
    clirResult.result.message = number;
    clirResult.clirStat = provider.ConsumeIntegral<int32_t>();
    clirResult.action = provider.ConsumeIntegral<int32_t>();
    clirData.WriteInt32(slotId);
    WriteSsResult(clirData, clirResult.result, clirResult.action, clirResult.clirStat);
    stub->OnGetClirResponseInner(clirData, clirReply);

    MessageParcel colpData;
    MessageParcel colpReply;
    GetColpResult colpResult;
    colpResult.result.message = number;
    colpResult.colpStat = provider.ConsumeIntegral<int32_t>();
    colpResult.action = provider.ConsumeIntegral<int32_t>();
    colpData.WriteInt32(slotId);
    WriteSsResult(colpData, colpResult.result, colpResult.action, colpResult.colpStat);
    stub->OnGetColpResponseInner(colpData, colpReply);

    MessageParcel colrData;
    MessageParcel colrReply;
    GetColrResult colrResult;
    colrResult.result.message = number;
    colrResult.colrStat = provider.ConsumeIntegral<int32_t>();
    colrResult.action = provider.ConsumeIntegral<int32_t>();
    colrData.WriteInt32(slotId);
    WriteSsResult(colrData, colrResult.result, colrResult.action, colrResult.colrStat);
    stub->OnGetColrResponseInner(colrData, colrReply);
}

void TestCFCallbackFunction(FuzzedDataProvider& provider, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    std::string number = provider.ConsumeRandomLengthString();
    MessageParcel cfData;
    MessageParcel cfReply;
    SsBaseResult normalResult;
    CallForwardQueryResult cfCall;
    normalResult.message = number;
    int32_t callSize = 1;
    int32_t flag = provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM);
    cfCall.serial = provider.ConsumeIntegralInRange<int32_t>(0, SERIAL_NUM);
    cfCall.result = provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM);
    cfCall.status = provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM);
    cfCall.classx = provider.ConsumeIntegral<int32_t>();
    cfCall.number = number;
    cfCall.type = provider.ConsumeIntegral<int32_t>();
    cfCall.reason = provider.ConsumeIntegral<int32_t>();

    cfData.WriteInt32(slotId);
    WriteSsResult(cfData, normalResult, callSize, flag);
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

void TestICCbWithCallMediaModeRequestReport(FuzzedDataProvider& provider, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    MessageParcel callMediaModeRequestData;
    MessageParcel callMediaModeRequestReply;
    ImsCallModeReceiveInfo callModeRequest;
    callModeRequest.callIndex = provider.ConsumeIntegralInRange<int32_t>(0, CALL_INDEX_NUM);
    callModeRequest.result = static_cast<ImsCallModeRequestResult>(
        provider.ConsumeIntegralInRange<int32_t>(0, REQUEST_NUM));
    callModeRequest.callType = static_cast<ImsCallType>(provider.ConsumeIntegralInRange<int32_t>(0, TYPE_NUM));
    callMediaModeRequestData.WriteInt32(slotId);
    callMediaModeRequestData.WriteRawData((const void *)&callModeRequest, sizeof(ImsCallModeReceiveInfo));
    stub->OnReceiveUpdateCallMediaModeRequestInner(callMediaModeRequestData, callMediaModeRequestReply);
}

void TestICCbWithCallMediaModeResponseReport(FuzzedDataProvider& provider, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    MessageParcel callMediaModeResponseData;
    MessageParcel callMediaModeResponseReply;
    ImsCallModeReceiveInfo callModeResponse;
    callModeResponse.callIndex = provider.ConsumeIntegralInRange<int32_t>(0, CALL_INDEX_NUM);
    callModeResponse.result = provider.ConsumeIntegralInRange<int32_t>(0, REQUEST_NUM);
    callModeResponse.callType = static_cast<ImsCallType>(provider.ConsumeIntegralInRange<int32_t>(0, TYPE_NUM));
    callMediaModeResponseData.WriteInt32(slotId);
    callMediaModeResponseData.WriteRawData((const void *)&callModeResponse, sizeof(ImsCallModeReceiveInfo));
    stub->OnReceiveUpdateCallMediaModeResponseInner(callMediaModeResponseData, callMediaModeResponseReply);
}

void TestICCbWithCallSessionEventChanged(FuzzedDataProvider& provider, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    MessageParcel callSessionData;
    MessageParcel callSessionReply;
    ImsCallSessionEventInfo callSessionEventInfo;
    callSessionEventInfo.callIndex = provider.ConsumeIntegralInRange<int32_t>(0, CALL_INDEX_NUM);
    callSessionEventInfo.eventType = static_cast<VideoCallEventType>(
        provider.ConsumeIntegralInRange<int32_t>(0, VIDEO_CALL_EVENT_NUM));
    callSessionData.WriteInt32(slotId);
    callSessionData.WriteRawData((const void *)&callSessionEventInfo, sizeof(ImsCallSessionEventInfo));
    stub->OnCallSessionEventChangedInner(callSessionData, callSessionReply);
}

void TestICCbWithPeerDimensionsChanged(FuzzedDataProvider& provider, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    MessageParcel callPeerDimensionsData;
    MessageParcel callPeerDimensionsReply;
    ImsCallPeerDimensionsInfo callPeerDimensionsInfo;
    callPeerDimensionsInfo.callIndex = provider.ConsumeIntegralInRange<int32_t>(0, CALL_INDEX_NUM);
    callPeerDimensionsInfo.width = provider.ConsumeIntegral<int32_t>();
    callPeerDimensionsInfo.height = provider.ConsumeIntegral<int32_t>();
    callPeerDimensionsData.WriteInt32(slotId);
    callPeerDimensionsData.WriteRawData((const void *)&callPeerDimensionsInfo, sizeof(ImsCallPeerDimensionsInfo));
    stub->OnPeerDimensionsChangedInner(callPeerDimensionsData, callPeerDimensionsReply);
}

void TestICCbWithCallDataUsageChanged(FuzzedDataProvider& provider, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    MessageParcel callDataUsageIData;
    MessageParcel callDataUsageIReply;
    ImsCallDataUsageInfo callDataUsageInfo;
    callDataUsageInfo.callIndex = provider.ConsumeIntegralInRange<int32_t>(0, CALL_INDEX_NUM);
    callDataUsageInfo.dataUsage = provider.ConsumeIntegral<int32_t>();
    callDataUsageIData.WriteInt32(slotId);
    callDataUsageIData.WriteRawData((const void *)&callDataUsageInfo, sizeof(ImsCallDataUsageInfo));
    stub->OnCallDataUsageChangedInner(callDataUsageIData, callDataUsageIReply);
}

void TestICCbWithCameraCapabilitiesChanged(FuzzedDataProvider& provider, sptr<ImsCallCallbackStub> &stub)
{
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    MessageParcel cameraCapabilitiesData;
    MessageParcel cameraCapabilitiesReply;
    CameraCapabilitiesInfo cameraCapabilitiesInfo;
    cameraCapabilitiesInfo.callIndex = provider.ConsumeIntegralInRange<int32_t>(0, CALL_INDEX_NUM);
    cameraCapabilitiesInfo.width = provider.ConsumeIntegral<int32_t>();
    cameraCapabilitiesInfo.height = provider.ConsumeIntegral<int32_t>();
    cameraCapabilitiesData.WriteInt32(slotId);
    cameraCapabilitiesData.WriteRawData((const void *)&cameraCapabilitiesInfo, sizeof(CameraCapabilitiesInfo));
    stub->OnCameraCapabilitiesChangedInner(cameraCapabilitiesData, cameraCapabilitiesReply);
}

void DoSomethingInterestingWithMyAPI(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    sptr<ImsCallCallbackStub> stub = (std::make_unique<ImsCallCallbackStub>()).release();
    if (stub == nullptr) {
        return;
    }

    OnRemoteRequest(provider);
    TestImsCallCallbackFunction(provider, stub);
    TestImsCallCallbackExFunction(provider, stub);
    TestImsConfigCallbackFunction(provider, stub);
    TestImsUTCallbackFunction(provider, stub);
    TestUTCallbackFunction(provider, stub);
    TestCFCallbackFunction(provider, stub);
    // IMS video call callback test(ICCb: ImsCallCallback)
    TestICCbWithCallMediaModeRequestReport(provider, stub);
    TestICCbWithCallMediaModeResponseReport(provider, stub);
    TestICCbWithCallSessionEventChanged(provider, stub);
    TestICCbWithPeerDimensionsChanged(provider, stub);
    TestICCbWithCallDataUsageChanged(provider, stub);
    TestICCbWithCameraCapabilitiesChanged(provider, stub);
}
} // namespace OHOS

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    OHOS::AddCellularCallTokenFuzzer token;
    if (data == nullptr || size == 0) {
        return 0;
    }
    /* Run your code on data */
    FuzzedDataProvider provider(data, size);
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}
