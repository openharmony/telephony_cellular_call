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

#include "registercallmanagercallback_fuzzer.h"

#include <cstddef>
#include <cstdint>
#define private public
#include "addcellularcalltoken_fuzzer.h"
#include "cellular_call_register.h"
#include "cellular_call_service.h"
#include "tel_ril_call_parcel.h"
#include "radio_event.h"
#include "securec.h"
#include "system_ability_definition.h"
#include "fuzzer/FuzzedDataProvider.h"

using namespace OHOS::Telephony;
namespace OHOS {
static bool g_isInited = false;
constexpr int32_t SLOT_NUM = 2;
constexpr int32_t BOOL_NUM = 2;
constexpr int32_t CALL_STATE_NUM = 9;
constexpr int32_t EVENT_ID_NUM = 20;
constexpr int32_t DISCONNECTEDREASON_UNKNOWN = 1279;
constexpr int32_t REQUEST_NUM = 6;

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

void ReportCallsInfo(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    std::shared_ptr<CellularCallRegister> cellularCallRegister = DelayedSingleton<CellularCallRegister>::GetInstance();
    CallsReportInfo callsReportInfo;
    callsReportInfo.slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    CallReportInfo callReportInfo;
    std::string number = provider.ConsumeRandomLengthString();
    int32_t length = number.length() > kMaxNumberLen ? kMaxNumberLen : number.length();
    if (memcpy_s(callReportInfo.accountNum, kMaxNumberLen, number.c_str(), length) != EOK) {
        return;
    }
    sptr<ICallStatusCallback> callback = nullptr;
    TelCallState callState = static_cast<TelCallState>(provider.ConsumeIntegralInRange<int32_t>(0, CALL_STATE_NUM));
    CellularCallEventInfo info;
    info.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    info.eventId = static_cast<RequestResultEventId>(provider.ConsumeIntegralInRange<int32_t>(0, CALL_STATE_NUM));
    CallWaitResponse response;
    response.classCw = provider.ConsumeIntegral<int32_t>();
    response.result = provider.ConsumeIntegral<int32_t>();
    response.status = provider.ConsumeIntegral<int32_t>();
    int32_t result = provider.ConsumeIntegral<int32_t>();
    CallRestrictionResponse callRestrictionResponse;
    callRestrictionResponse.classCw = provider.ConsumeIntegral<int32_t>();
    callRestrictionResponse.result = provider.ConsumeIntegral<int32_t>();
    callRestrictionResponse.status = provider.ConsumeIntegral<int32_t>();

    cellularCallRegister->ReportCallsInfo(callsReportInfo);
    cellularCallRegister->RegisterCallManagerCallBack(callback);
    cellularCallRegister->ReportSingleCallInfo(callReportInfo, callState);
    cellularCallRegister->UnRegisterCallManagerCallBack();
    cellularCallRegister->ReportEventResultInfo(info);
    cellularCallRegister->ReportGetWaitingResult(response);
    cellularCallRegister->ReportSetWaitingResult(result);
    cellularCallRegister->ReportGetRestrictionResult(callRestrictionResponse);
    cellularCallRegister->ReportSetBarringPasswordResult(result);
}

void ReportSetRestrictionResult(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    std::shared_ptr<CellularCallRegister> cellularCallRegister = DelayedSingleton<CellularCallRegister>::GetInstance();
    int32_t result = provider.ConsumeIntegral<int32_t>();
    CallTransferResponse callTransferResponse;
    callTransferResponse.result = provider.ConsumeIntegral<int32_t>();
    callTransferResponse.status = provider.ConsumeIntegral<int32_t>();
    callTransferResponse.classx = provider.ConsumeIntegral<int32_t>();
    callTransferResponse.type = provider.ConsumeIntegral<int32_t>();
    callTransferResponse.time = provider.ConsumeIntegral<int32_t>();
    callTransferResponse.reason = provider.ConsumeIntegral<int32_t>();
    std::string number = provider.ConsumeRandomLengthString();
    int32_t length = number.length() > kMaxNumberLen ? kMaxNumberLen : number.length();
    if (memcpy_s(callTransferResponse.number, kMaxNumberLen, number.c_str(), length) != EOK) {
        return;
    }
    ClipResponse clipResponse;
    clipResponse.action = provider.ConsumeIntegral<int32_t>();
    clipResponse.result = provider.ConsumeIntegral<int32_t>();
    clipResponse.clipStat = provider.ConsumeIntegral<int32_t>();
    ClirResponse clirResponse;
    clirResponse.clirStat = provider.ConsumeIntegral<int32_t>();
    clirResponse.action = provider.ConsumeIntegral<int32_t>();
    clirResponse.result = provider.ConsumeIntegral<int32_t>();
    GetImsConfigResponse getImsConfigResponse;
    getImsConfigResponse.result = provider.ConsumeIntegral<int32_t>();
    getImsConfigResponse.value = provider.ConsumeIntegral<int32_t>();

    cellularCallRegister->ReportSetRestrictionResult(result);
    cellularCallRegister->ReportGetTransferResult(callTransferResponse);
    cellularCallRegister->ReportSetTransferResult(result);
    cellularCallRegister->ReportGetClipResult(clipResponse);
    cellularCallRegister->ReportGetClirResult(clirResponse);
    cellularCallRegister->ReportSetClirResult(result);
    cellularCallRegister->ReportGetImsConfigResult(getImsConfigResponse);
    cellularCallRegister->ReportSetImsConfigResult(result);
    cellularCallRegister->ReportSetImsFeatureResult(result);
}

void ReportSetImsConfigResult(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    std::shared_ptr<CellularCallRegister> cellularCallRegister = DelayedSingleton<CellularCallRegister>::GetInstance();
    int32_t result = provider.ConsumeIntegral<int32_t>();
    GetImsFeatureValueResponse getImsFeatureValueResponse;
    getImsFeatureValueResponse.result = provider.ConsumeIntegral<int32_t>();
    getImsFeatureValueResponse.value = provider.ConsumeIntegral<int32_t>();
    GetLteEnhanceModeResponse getLteEnhanceModeResponse;
    getLteEnhanceModeResponse.result = provider.ConsumeIntegral<int32_t>();
    getLteEnhanceModeResponse.value = provider.ConsumeIntegral<int32_t>();
    DisconnectedDetails details;
    std::string number = provider.ConsumeRandomLengthString();
    details.message = number;
    details.reason = static_cast<DisconnectedReason>(
        provider.ConsumeIntegralInRange<int32_t>(1, DISCONNECTEDREASON_UNKNOWN));
    MuteControlResponse muteControlResponse;
    muteControlResponse.result = provider.ConsumeIntegral<int32_t>();
    muteControlResponse.value = provider.ConsumeIntegral<int32_t>();
    SetEccListResponse setEccListResponse;
    setEccListResponse.result = provider.ConsumeIntegral<int32_t>();
    setEccListResponse.value = provider.ConsumeIntegral<int32_t>();
    MmiCodeInfo mmiCodeInfo;
    mmiCodeInfo.result = provider.ConsumeIntegral<int32_t>();
    int32_t length = number.length() > kMaxNumberLen ? kMaxNumberLen : number.length();
    if (memcpy_s(mmiCodeInfo.message, kMaxNumberLen, number.c_str(), length) != EOK) {
        return;
    }

    cellularCallRegister->ReportGetImsFeatureResult(getImsFeatureValueResponse);
    cellularCallRegister->ReportCallRingBackResult(result);
    cellularCallRegister->ReportCallFailReason(details);
    cellularCallRegister->ReportGetMuteResult(muteControlResponse);
    cellularCallRegister->ReportSetMuteResult(muteControlResponse);
    cellularCallRegister->ReportInviteToConferenceResult(result);
    cellularCallRegister->ReportGetCallDataResult(result);
    cellularCallRegister->ReportStartDtmfResult(result);
    cellularCallRegister->ReportStopDtmfResult(result);
    cellularCallRegister->ReportStartRttResult(result);
    cellularCallRegister->ReportStopRttResult(result);
    cellularCallRegister->ReportSendUssdResult(result);
    cellularCallRegister->ReportMmiCodeResult(mmiCodeInfo);
    cellularCallRegister->ReportSetEmergencyCallListResponse(setEccListResponse);
    cellularCallRegister->IsCallManagerCallBackRegistered();
}

void ReportUpdateCallMediaMode(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    std::shared_ptr<CellularCallRegister> cellularCallRegister = DelayedSingleton<CellularCallRegister>::GetInstance();
    ImsCallModeReceiveInfo reportCallModeInfo;
    reportCallModeInfo.callIndex = provider.ConsumeIntegral<int32_t>();
    reportCallModeInfo.result = static_cast<ImsCallModeRequestResult>(
        provider.ConsumeIntegralInRange<int32_t>(0, REQUEST_NUM));
    reportCallModeInfo.callType = static_cast<ImsCallType>(provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM));
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    cellularCallRegister->ReceiveUpdateCallMediaModeRequest(slotId, reportCallModeInfo);
    cellularCallRegister->ReceiveUpdateCallMediaModeResponse(slotId, reportCallModeInfo);
}

void ReportCallSessionEventChanged(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    std::shared_ptr<CellularCallRegister> cellularCallRegister = DelayedSingleton<CellularCallRegister>::GetInstance();
    ImsCallSessionEventInfo reportCallSessionInfo;
    reportCallSessionInfo.callIndex = provider.ConsumeIntegral<int32_t>();
    reportCallSessionInfo.eventType = static_cast<VideoCallEventType>(
        provider.ConsumeIntegralInRange<int32_t>(0, BOOL_NUM));
    cellularCallRegister->HandleCallSessionEventChanged(reportCallSessionInfo);
}

void ReportPeerDimensionsChanged(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    std::shared_ptr<CellularCallRegister> cellularCallRegister = DelayedSingleton<CellularCallRegister>::GetInstance();
    ImsCallPeerDimensionsInfo reportCallPeerDimensionsInfo;
    reportCallPeerDimensionsInfo.callIndex = provider.ConsumeIntegral<int32_t>();
    reportCallPeerDimensionsInfo.width = provider.ConsumeIntegral<int32_t>();
    reportCallPeerDimensionsInfo.height = provider.ConsumeIntegral<int32_t>();
    cellularCallRegister->HandlePeerDimensionsChanged(reportCallPeerDimensionsInfo);
}

void ReportCallDataUsageChanged(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    std::shared_ptr<CellularCallRegister> cellularCallRegister = DelayedSingleton<CellularCallRegister>::GetInstance();
    ImsCallDataUsageInfo reportCallDataUsageInfo;
    reportCallDataUsageInfo.callIndex = provider.ConsumeIntegral<int32_t>();
    reportCallDataUsageInfo.dataUsage = provider.ConsumeIntegral<int64_t>();
    cellularCallRegister->HandleCallDataUsageChanged(reportCallDataUsageInfo);
}

void ReportCameraCapabilitiesChanged(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    std::shared_ptr<CellularCallRegister> cellularCallRegister = DelayedSingleton<CellularCallRegister>::GetInstance();
    CameraCapabilitiesInfo reportCameraCapabilitiesInfo;
    reportCameraCapabilitiesInfo.callIndex = provider.ConsumeIntegral<int32_t>();
    reportCameraCapabilitiesInfo.width = provider.ConsumeIntegral<int32_t>();
    reportCameraCapabilitiesInfo.height = provider.ConsumeIntegral<int32_t>();
    cellularCallRegister->HandleCameraCapabilitiesChanged(reportCameraCapabilitiesInfo);
}

void DoSomethingInterestingWithMyAPI(FuzzedDataProvider& provider)
{
    ReportCallsInfo(provider);
    ReportSetRestrictionResult(provider);
    ReportSetImsConfigResult(provider);
    ReportUpdateCallMediaMode(provider);
    ReportCallSessionEventChanged(provider);
    ReportPeerDimensionsChanged(provider);
    ReportCallDataUsageChanged(provider);
    ReportCameraCapabilitiesChanged(provider);
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
    OHOS::DoSomethingInterestingWithMyAPI(provider);
    return 0;
}
