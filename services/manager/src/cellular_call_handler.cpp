/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
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

#include "cellular_call_handler.h"

#include "hril_call_parcel.h"

#include "cellular_call_config.h"
#include "cellular_call_register.h"

namespace OHOS {
namespace Telephony {
CellularCallHandler::CellularCallHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner)
    : AppExecFwk::EventHandler(runner)
{
    requestFuncMap_[ObserverHandler::RADIO_DIAL] = &CellularCallHandler::DialResponse;
    requestFuncMap_[ObserverHandler::RADIO_HANGUP_CONNECT] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[ObserverHandler::RADIO_REJECT_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[ObserverHandler::RADIO_ACCEPT_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[ObserverHandler::RADIO_HOLD_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[ObserverHandler::RADIO_ACTIVE_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[ObserverHandler::RADIO_SWAP_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[ObserverHandler::RADIO_JOIN_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[ObserverHandler::RADIO_SPLIT_CALL] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[ObserverHandler::RADIO_CALL_SUPPLEMENT] = &CellularCallHandler::CommonResultResponse;
    requestFuncMap_[ObserverHandler::RADIO_CALL_STATE] = &CellularCallHandler::CallStateResponse;
    requestFuncMap_[ObserverHandler::RADIO_CALL_WAITING] = &CellularCallHandler::CallWaitingResponse;
    requestFuncMap_[ObserverHandler::RADIO_CALL_CONNECT] = &CellularCallHandler::CallConnectResponse;
    requestFuncMap_[ObserverHandler::RADIO_CALL_END] = &CellularCallHandler::CallEndResponse;
    requestFuncMap_[ObserverHandler::RADIO_CALL_STATUS_INFO] = &CellularCallHandler::CallStatusInfoResponse;
    requestFuncMap_[ObserverHandler::RADIO_CALL_IMS_SERVICE_STATUS] =
        &CellularCallHandler::CallImsServiceStatusResponse;
    requestFuncMap_[ObserverHandler::RADIO_AVAIL] = &CellularCallHandler::GetCsCallData;
    requestFuncMap_[ObserverHandler::RADIO_NOT_AVAIL] = &CellularCallHandler::GetCsCallData;
    requestFuncMap_[ObserverHandler::RADIO_CURRENT_CALLS] = &CellularCallHandler::GetCsCallsDataResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_IMS_CALL_LIST] = &CellularCallHandler::GetImsCallsDataResponse;
    requestFuncMap_[ObserverHandler::RADIO_SEND_DTMF] = &CellularCallHandler::SendDtmfResponse;
    requestFuncMap_[ObserverHandler::RADIO_START_DTMF] = &CellularCallHandler::StartDtmfResponse;
    requestFuncMap_[ObserverHandler::RADIO_STOP_DTMF] = &CellularCallHandler::StopDtmfResponse;
    requestFuncMap_[GET_CS_CALL_DATA_ID] = &CellularCallHandler::GetCsCallsDataRequest;
    requestFuncMap_[GET_IMS_CALL_DATA_ID] = &CellularCallHandler::GetImsCallsDataRequest;
    requestFuncMap_[REGISTER_HANDLER_ID] = &CellularCallHandler::RegisterHandler;
    requestFuncMap_[ObserverHandler::RADIO_SET_CALL_PREFERENCE_MODE] =
        &CellularCallHandler::SetCallPreferenceModeResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_CALL_PREFERENCE_MODE] =
        &CellularCallHandler::GetCallPreferenceModeResponse;
    requestFuncMap_[ObserverHandler::RADIO_SET_LTE_IMS_SWITCH_STATUS] =
        &CellularCallHandler::SetLteImsSwitchStatusResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_LTE_IMS_SWITCH_STATUS] =
        &CellularCallHandler::GetLteImsSwitchStatusResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_LTE_IMS_SWITCH_STATUS] =
        &CellularCallHandler::GetLteImsSwitchStatusResponse;
}

void CellularCallHandler::ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CellularCallHandler::ProcessEvent, event is nullptr");
        return;
    }
    auto itFunc = requestFuncMap_.find(event->GetInnerEventId());
    if (itFunc != requestFuncMap_.end()) {
        auto requestFunc = itFunc->second;
        if (requestFunc != nullptr) {
            return (this->*requestFunc)(event);
        }
    }
}

void CellularCallHandler::GetCsCallData(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCsCallData return, event is nullptr");
        return;
    }
    TELEPHONY_LOGI("GetCsCallData event id: %{public}d", event->GetInnerEventId());
    this->SendEvent(GET_CS_CALL_DATA_ID, delayTime_, Priority::HIGH);
}

void CellularCallHandler::GetImsCallData(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetImsCallData return, event is nullptr");
        return;
    }
    TELEPHONY_LOGI("GetImsCallData event id: %{public}d", event->GetInnerEventId());
    this->SendEvent(GET_IMS_CALL_DATA_ID, delayTime_, Priority::HIGH);
}

void CellularCallHandler::GetCsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCsCallsDataResponse return, event is nullptr");
        return;
    }

    // Returns list of current calls of ME. If command succeeds but no calls are available,
    // no information response is sent to TE. Refer subclause 9.2 for possible <err> values.
    auto callInfoList = event->GetSharedObject<CallInfoList>();
    if (callInfoList == nullptr) {
        TELEPHONY_LOGE("GetCsCallsDataResponse, Cannot get the callInfoList, need to get rilResponseInfo");
        auto rilResponseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
        if (rilResponseInfo == nullptr) {
            TELEPHONY_LOGE("GetCsCallsDataResponse return, callInfoList and rilResponseInfo is nullptr");
            return;
        }
        if (rilResponseInfo->error == HRilErrType::NONE) {
            TELEPHONY_LOGE("GetCsCallsDataResponse return, failed to query the call list but no reason!");
            return;
        }
        TELEPHONY_LOGE("GetCsCallsDataResponse error, report to call_manager");
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
        eventInfo.eventId = RequestResultEventId::RESULT_GET_CURRENT_CALLS_FAILED;
        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("GetCsCallsDataResponse return, GetInstance is nullptr");
            return;
        }
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
        return;
    }
    if (pCsControl_ == nullptr) {
        TELEPHONY_LOGE("GetCsCallsDataResponse return, pCsControl_ is nullptr");
        return;
    }
    if (callInfoList->callSize == 0) {
        callType_ = CallType::TYPE_ERR_CALL;
    }
    pCsControl_->ReportCallsData(*callInfoList);
}

void CellularCallHandler::GetImsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetImsCallsDataResponse return, event is nullptr");
        return;
    }
    auto imsCallInfoList = event->GetSharedObject<CallInfoList>();
    if (imsCallInfoList == nullptr) {
        TELEPHONY_LOGE("GetImsCallsDataResponse, Cannot get the imsCallInfoList, need to get rilResponseInfo");
        auto rilResponseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
        if (rilResponseInfo == nullptr) {
            TELEPHONY_LOGE("GetImsCallsDataResponse return, callInfoList and rilResponseInfo is nullptr");
            return;
        }
        if (rilResponseInfo->error == HRilErrType::NONE) {
            TELEPHONY_LOGE("GetImsCallsDataResponse return, failed to query the call list but no reason!");
            return;
        }
        TELEPHONY_LOGE("GetImsCallsDataResponse error, report to call_manager");
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
        eventInfo.eventId = RequestResultEventId::RESULT_GET_IMS_CALLS_DATA_FAILED;
        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("GetImsCallsDataResponse return, GetInstance is nullptr");
            return;
        }
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
        return;
    }
    if (pImsControl_ == nullptr) {
        TELEPHONY_LOGE("GetImsCallsDataResponse return, pImsControl_ is nullptr");
        return;
    }
    if (imsCallInfoList->callSize == 0) {
        callType_ = CallType::TYPE_ERR_CALL;
    }
    pImsControl_->ReportCallsData(*imsCallInfoList);
}

void CellularCallHandler::DialResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("DialResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("DialResponse return, result is nullptr");
        return;
    }
    if (result->error != HRilErrType::NONE) {
        TELEPHONY_LOGI("DialResponse, dial return error, report to call_manager");
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;

        /*
         * 3GPP TS 27.007 V3.9.0 (2001-06)
         * If ME has succeeded in establishing a logical link between application protocols and external interface,
         * it will send CONNECT message to the TE. Otherwise, the NO CARRIER response will be returned.
         */
        if (result->error == HRilErrType::HRIL_ERR_CMD_NO_CARRIER) {
            eventInfo.eventId = RequestResultEventId::RESULT_DIAL_NO_CARRIER;
        } else {
            eventInfo.eventId = RequestResultEventId::RESULT_DIAL_SEND_FAILED;
        }
        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("DialResponse return, GetInstance is nullptr");
            return;
        }
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    }
}

void CellularCallHandler::CommonResultResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CommonResultResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("CommonResultResponse return, result is nullptr");
        return;
    }
    if (result->error != HRilErrType::NONE) {
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
        switch (event->GetInnerEventId()) {
            case ObserverHandler::RADIO_HANGUP_CONNECT:
                eventInfo.eventId = RequestResultEventId::RESULT_END_SEND_FAILED;
                break;
            case ObserverHandler::RADIO_ACCEPT_CALL:
                eventInfo.eventId = RequestResultEventId::RESULT_ACCEPT_SEND_FAILED;
                break;
            case ObserverHandler::RADIO_HOLD_CALL:
                eventInfo.eventId = RequestResultEventId::RESULT_HOLD_SEND_FAILED;
                break;
            case ObserverHandler::RADIO_ACTIVE_CALL:
                eventInfo.eventId = RequestResultEventId::RESULT_ACTIVE_SEND_FAILED;
                break;
            case ObserverHandler::RADIO_SWAP_CALL:
                eventInfo.eventId = RequestResultEventId::RESULT_SWAP_SEND_FAILED;
                break;
            case ObserverHandler::RADIO_JOIN_CALL:
                eventInfo.eventId = RequestResultEventId::RESULT_JOIN_SEND_FAILED;
                break;
            case ObserverHandler::RADIO_SPLIT_CALL:
                eventInfo.eventId = RequestResultEventId::RESULT_SPLIT_SEND_FAILED;
                break;
            case ObserverHandler::RADIO_CALL_SUPPLEMENT:
                eventInfo.eventId = RequestResultEventId::RESULT_SUPPLEMENT_SEND_FAILED;
                break;
            default:
                break;
        }
        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("CommonResultResponse return, GetInstance is nullptr");
            return;
        }
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    }
}

void CellularCallHandler::SendDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SendDtmfResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("SendDtmfResponse return, result is nullptr");
        return;
    }
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (result->error != HRilErrType::NONE) {
        eventInfo.eventId = RequestResultEventId::RESULT_TRANSMIT_DTMF_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_TRANSMIT_DTMF_SUCCESS;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SendDtmfResponse return, GetInstance is nullptr");
        return;
    }
    TELEPHONY_LOGI("SendDtmfResponse: report to call manager");
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
}

void CellularCallHandler::StartDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("StartDtmfResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("StartDtmfResponse return, result is nullptr");
        return;
    }
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (result->error != HRilErrType::NONE) {
        eventInfo.eventId = RequestResultEventId::RESULT_INITIATE_DTMF_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_INITIATE_DTMF_SUCCESS;
    }

    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("StartDtmfResponse return, GetInstance is nullptr");
        return;
    }
    TELEPHONY_LOGI("StartDtmfResponse: report to call manager");
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
}

void CellularCallHandler::StopDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("StopDtmfResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("StopDtmfResponse return, result is nullptr");
        return;
    }
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (result->error != HRilErrType::NONE) {
        eventInfo.eventId = RequestResultEventId::RESULT_CEASE_DTMF_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_CEASE_DTMF_SUCCESS;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("StopDtmfResponse return, GetInstance is nullptr");
        return;
    }
    TELEPHONY_LOGI("StopDtmfResponse: report to call manager");
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
}

void CellularCallHandler::SetSlotId(int32_t id)
{
    slotId_ = id;
}

void CellularCallHandler::SetCsControl(std::shared_ptr<CSControl> pCsControl)
{
    pCsControl_ = std::move(pCsControl);
}

std::shared_ptr<CSControl> CellularCallHandler::GetCsControl()
{
    return pCsControl_;
}

void CellularCallHandler::SetImsControl(std::shared_ptr<IMSControl> pImsControl)
{
    pImsControl_ = std::move(pImsControl);
}

std::shared_ptr<IMSControl> CellularCallHandler::GetImsControl()
{
    return pImsControl_;
}

int64_t CellularCallHandler::CurrentTimeMillis()
{
    int64_t timems =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    return timems;
}

bool CellularCallHandler::IsCanRequestCallsData()
{
    int64_t timems = CurrentTimeMillis();
    if ((timems - lastTime_) < FAST_DELAY_TIME) {
        return false;
    }
    lastTime_ = timems;
    return true;
}

void CellularCallHandler::GetCsCallsDataRequest(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (!IsCanRequestCallsData()) {
        TELEPHONY_LOGE("GetCsCallsDataRequest return, IsCanRequestCallsData false");
    }
    lastCallsDataFlag_ = CurrentTimeMillis();
    CellularCallConnectionCS connectionCs;
    connectionCs.GetCsCallsDataRequest(slotId_, lastCallsDataFlag_);
}

void CellularCallHandler::GetImsCallsDataRequest(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (!IsCanRequestCallsData()) {
        TELEPHONY_LOGE("GetImsCallsDataRequest return, IsCanRequestCallsData false");
    }
    lastCallsDataFlag_ = CurrentTimeMillis();
    CellularCallConnectionIMS connectionIms;
    connectionIms.GetImsCallsDataRequest(slotId_, lastCallsDataFlag_);
}

void CellularCallHandler::RegisterHandler(const AppExecFwk::InnerEvent::Pointer &event)
{
    CellularCallConnectionCS connectionCs;
    connectionCs.RegisterHandler();
}

void CellularCallHandler::SetCallPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallPreferenceModeResponse return, event is nullptr");
        return;
    }
    auto info = event->GetSharedObject<HRilRadioResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetCallPreferenceModeResponse return, info is nullptr");
        return;
    }
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (info->error != HRilErrType::NONE) {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_CALL_PREFERENCE_MODE_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_CALL_PREFERENCE_MODE_SUCCESS;

        CellularCallConfig config;
        config.SetTempMode();
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetCallPreferenceModeResponse return, GetInstance is nullptr");
        return;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
}

void CellularCallHandler::GetCallPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("GetCallPreferenceModeResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallPreferenceModeResponse return, event is nullptr");
        return;
    }
    CallPreferenceResponse callPreference;
    auto mode = event->GetSharedObject<int32_t>();
    if (mode == nullptr) {
        TELEPHONY_LOGI("GetCallPreferenceModeResponse return, mode is nullptr");
        auto info = event->GetSharedObject<HRilRadioResponseInfo>();
        if (info == nullptr) {
            TELEPHONY_LOGE("GetCallPreferenceModeResponse return, info is nullptr");
            return;
        }
        callPreference.result = static_cast<int32_t>(info->error);
    } else {
        CellularCallConfig config;
        config.GetCallPreferenceModeResponse(mode);
        callPreference.result = static_cast<int32_t>(HRilErrType::NONE);
        callPreference.mode = *mode;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetCallPreferenceModeResponse return, GetInstance is nullptr");
        return;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetCallPreferenceResult(callPreference);
}

void CellularCallHandler::SetLteImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("SetLteImsSwitchStatusResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetLteImsSwitchStatusResponse return, event is nullptr");
        return;
    }
    auto info = event->GetSharedObject<HRilRadioResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetLteImsSwitchStatusResponse return, info is nullptr");
        return;
    }
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (info->error != HRilErrType::NONE) {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_LTE_IMS_SWITCH_STATUS_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_LTE_IMS_SWITCH_STATUS_SUCCESS;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetLteImsSwitchStatusResponse return, GetInstance is nullptr");
        return;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
}

void CellularCallHandler::GetLteImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("GetLteImsSwitchStatusResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetLteImsSwitchStatusResponse return, event is nullptr");
        return;
    }
    LteImsSwitchResponse lteImsSwitch;
    auto active = event->GetSharedObject<int32_t>();
    if (active == nullptr) {
        TELEPHONY_LOGI("GetLteImsSwitchStatusResponse, Cannot get the active, need to get rilResponseInfo");
        auto info = event->GetSharedObject<HRilRadioResponseInfo>();
        if (info == nullptr) {
            TELEPHONY_LOGE("GetLteImsSwitchStatusResponse return, info is nullptr");
            return;
        }
        lteImsSwitch.result = static_cast<int32_t>(info->error);
    } else {
        CellularCallConfig config;
        config.GetLteImsSwitchStatusResponse(active);
        lteImsSwitch.result = static_cast<int32_t>(HRilErrType::NONE);
        lteImsSwitch.active = *active;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetLteImsSwitchStatusResponse return, GetInstance is nullptr");
        return;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetLteImsSwitchResult(lteImsSwitch);
}

void CellularCallHandler::CallStateResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CallStateResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("CallStateResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("CallStateResponse return, result is nullptr");
        return;
    }
}

void CellularCallHandler::CallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CallWaitingResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("CallWaitingResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("CallWaitingResponse return, result is nullptr");
        return;
    }
}

void CellularCallHandler::CallConnectResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CallConnectResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("CallConnectResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("CallConnectResponse return, result is nullptr");
        return;
    }
}

void CellularCallHandler::CallEndResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CallEndResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("CallEndResponse return, event is nullptr");
        return;
    }
    auto callEndInfo = event->GetSharedObject<CallEndInfo>();
    if (callEndInfo == nullptr) {
        TELEPHONY_LOGE("CallEndResponse return, callEndInfo is nullptr");
        return;
    }
}

void CellularCallHandler::CallStatusInfoResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CallStatusInfoResponse return, event is nullptr");
        return;
    }
    auto info = event->GetSharedObject<CallStatusInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("CallStatusInfoResponse return, info is nullptr");
        return;
    }
    /**
     * 0: CS domain voice call
     * 1: IMS domain voice call
     */
    if (callType_ == CallType::TYPE_ERR_CALL) {
        TELEPHONY_LOGI("CallStatusInfoResponse TYPE_ERR_CALL");
        if (info->voiceDomain) {
            GetImsCallData(event);
        } else {
            GetCsCallData(event);
        }
    } else if (callType_ == CallType::TYPE_CS) {
        GetCsCallData(event);
    } else if (callType_ == CallType::TYPE_IMS) {
        GetImsCallData(event);
    }
}

void CellularCallHandler::CallImsServiceStatusResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CallImsServiceStatusResponse return, event is nullptr");
        return;
    }
    auto status = event->GetSharedObject<CallImsServiceStatus>();
    if (status == nullptr) {
        TELEPHONY_LOGE("CallImsServiceStatusResponse return, status is nullptr");
        return;
    }
}

void CellularCallHandler::SetCallType(CallType callType)
{
    callType_ = callType;
}
} // namespace Telephony
} // namespace OHOS