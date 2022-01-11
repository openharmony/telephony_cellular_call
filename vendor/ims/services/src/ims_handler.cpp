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

#include "ims_handler.h"
#include "securec.h"

#include "hril_call_parcel.h"
#include "hril_types.h"
#include "ims_ril_request.h"
#include "ims_register.h"
#include "observer_handler.h"

namespace OHOS {
namespace Telephony {
ImsHandler::ImsHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner) : AppExecFwk::EventHandler(runner)
{
    requestFuncMap_[ASYNCHRONOUS_REGISTER_ID] = &ImsHandler::AsynchronousRegister;
    requestFuncMap_[ObserverHandler::RADIO_CALL_WAITING] = &ImsHandler::CallWaitingResponse;
    requestFuncMap_[ObserverHandler::RADIO_CALL_CONNECT] = &ImsHandler::CallConnectResponse;
    requestFuncMap_[ObserverHandler::RADIO_CALL_END] = &ImsHandler::CallEndResponse;
    requestFuncMap_[ObserverHandler::RADIO_CALL_STATUS_INFO] = &ImsHandler::CallStatusInfoResponse;
    requestFuncMap_[ObserverHandler::RADIO_CALL_IMS_SERVICE_STATUS] = &ImsHandler::CallImsServiceStatusResponse;
    requestFuncMap_[ObserverHandler::RADIO_SET_CALL_PREFERENCE_MODE] = &ImsHandler::SetCallPreferenceModeResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_CALL_PREFERENCE_MODE] = &ImsHandler::GetCallPreferenceModeResponse;
    requestFuncMap_[ObserverHandler::RADIO_SET_LTE_IMS_SWITCH_STATUS] = &ImsHandler::SetLteImsSwitchStatusResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_LTE_IMS_SWITCH_STATUS] = &ImsHandler::GetLteImsSwitchStatusResponse;
    requestFuncMap_[ObserverHandler::RADIO_DIAL] = &ImsHandler::DialResponse;
    requestFuncMap_[ObserverHandler::RADIO_HANGUP_CONNECT] = &ImsHandler::HangUpResponse;
    requestFuncMap_[ObserverHandler::RADIO_REJECT_CALL] = &ImsHandler::RejectResponse;
    requestFuncMap_[ObserverHandler::RADIO_ACCEPT_CALL] = &ImsHandler::AnswerResponse;
    requestFuncMap_[ObserverHandler::RADIO_HOLD_CALL] = &ImsHandler::HoldCallResponse;
    requestFuncMap_[ObserverHandler::RADIO_ACTIVE_CALL] = &ImsHandler::UnHoldCallResponse;
    requestFuncMap_[ObserverHandler::RADIO_SWAP_CALL] = &ImsHandler::SwitchCallResponse;
    requestFuncMap_[ObserverHandler::RADIO_SEND_DTMF] = &ImsHandler::SendDtmfResponse;
    requestFuncMap_[ObserverHandler::RADIO_START_DTMF] = &ImsHandler::StartDtmfResponse;
    requestFuncMap_[ObserverHandler::RADIO_STOP_DTMF] = &ImsHandler::StopDtmfResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_IMS_CALL_LIST] = &ImsHandler::GetImsCallsDataResponse;
    requestFuncMap_[ObserverHandler::RADIO_CALL_RINGBACK_VOICE] = &ImsHandler::CallRingBackVoiceResponse;
    requestFuncMap_[ObserverHandler::RADIO_SET_CMUT] = &ImsHandler::SetMuteResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_CMUT] = &ImsHandler::GetMuteResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_EMERGENCY_CALL_LIST] = &ImsHandler::GetEmergencyCallListResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_CALL_FAIL_REASON] = &ImsHandler::GetCallFailReasonResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_CALL_CLIP] = &ImsHandler::GetClipResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_CALL_CLIR] = &ImsHandler::GetClirResponse;
    requestFuncMap_[ObserverHandler::RADIO_SET_CALL_CLIR] = &ImsHandler::SetClirResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_CALL_FORWARD] = &ImsHandler::GetCallTransferResponse;
    requestFuncMap_[ObserverHandler::RADIO_SET_CALL_FORWARD] = &ImsHandler::SetCallTransferResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_CALL_RESTRICTION] = &ImsHandler::GetCallRestrictionResponse;
    requestFuncMap_[ObserverHandler::RADIO_SET_CALL_RESTRICTION] = &ImsHandler::SetCallRestrictionResponse;
    requestFuncMap_[ObserverHandler::RADIO_GET_CALL_WAIT] = &ImsHandler::GetCallWaitingResponse;
    requestFuncMap_[ObserverHandler::RADIO_SET_CALL_WAIT] = &ImsHandler::SetCallWaitingResponse;
}

void ImsHandler::ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("ImsHandler::ProcessEvent, event is nullptr");
        return;
    }
    auto itFunc = requestFuncMap_.find(event->GetInnerEventId());
    if (itFunc != requestFuncMap_.end()) {
        auto requestFunc = itFunc->second;
        if (requestFunc != nullptr) {
            return (this->*requestFunc)(event);
        }
    }
    TELEPHONY_LOGI("ImsHandler::ProcessEvent, default case, need check.");
}

void ImsHandler::AsynchronousRegister(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::AsynchronousRegister entry.");
    ImsRilRequest request;
    request.AsynchronousRegister();
}

void ImsHandler::CallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CallWaitingResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("CallWaitingResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<ImsResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("CallWaitingResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CallWaitingResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateCallWaitingResponse(*result);
}

void ImsHandler::CallConnectResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CallConnectResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("CallConnectResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<ImsResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("CallConnectResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CallConnectResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateCallConnectResponse(*result);
}

void ImsHandler::CallEndResponse(const AppExecFwk::InnerEvent::Pointer &event)
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
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CallEndResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateCallEndResponse(slotId_, *callEndInfo);

    ImsRilRequest rilRequest;
    rilRequest.GetCallFailReasonRequest(slotId_);
}

void ImsHandler::CallStatusInfoResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CallStatusInfoResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("CallStatusInfoResponse return, event is nullptr");
        return;
    }
    auto info = event->GetSharedObject<CallStatusInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("CallStatusInfoResponse return, info is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CallStatusInfoResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateCallStatusResponse(slotId_, *info);

    int64_t time =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    ImsRilRequest rilRequest;
    rilRequest.GetImsCallsDataRequest(slotId_, time);
}

void ImsHandler::CallImsServiceStatusResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("CallImsServiceStatusResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("CallImsServiceStatusResponse return, event is nullptr");
        return;
    }
    auto status = event->GetSharedObject<CallImsServiceStatus>();
    if (status == nullptr) {
        TELEPHONY_LOGE("CallImsServiceStatusResponse return, status is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CallImsServiceStatusResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateServiceStatusResponse(slotId_, *status);
}

void ImsHandler::SetCallPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("SetCallPreferenceModeResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallPreferenceModeResponse return, event is nullptr");
        return;
    }
    auto info = event->GetSharedObject<HRilRadioResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetCallPreferenceModeResponse return, info is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetCallPreferenceModeResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo responseInfo;
    responseInfo.slotId = slotId_;
    responseInfo.error = static_cast<ImsErrType>(info->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetPreModeResponse(responseInfo);
}

void ImsHandler::GetCallPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGE("GetCallPreferenceModeResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallPreferenceModeResponse return, event is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetCallPreferenceModeResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    auto mode = event->GetSharedObject<int32_t>();
    if (mode == nullptr) {
        TELEPHONY_LOGI("GetCallPreferenceModeResponse return, mode is nullptr");
        auto info = event->GetSharedObject<HRilRadioResponseInfo>();
        if (info == nullptr) {
            TELEPHONY_LOGE("GetCallPreferenceModeResponse return, info is nullptr");
            return;
        }
        ImsResponseInfo responseInfo;
        responseInfo.slotId = slotId_;
        responseInfo.error = static_cast<ImsErrType>(info->error);
        DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetPreModeResponse(responseInfo);
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetPreModeResponse(slotId_, *mode);
}

void ImsHandler::SetLteImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event)
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
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetLteImsSwitchStatusResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo responseInfo;
    responseInfo.slotId = slotId_;
    responseInfo.error = static_cast<ImsErrType>(info->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetImsSwitchResponse(responseInfo);
}

void ImsHandler::GetLteImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("GetLteImsSwitchStatusResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetLteImsSwitchStatusResponse return, event is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetLteImsSwitchStatusResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    auto active = event->GetSharedObject<int32_t>();
    if (active == nullptr) {
        TELEPHONY_LOGI("GetLteImsSwitchStatusResponse return, active is nullptr");
        auto info = event->GetSharedObject<HRilRadioResponseInfo>();
        if (info == nullptr) {
            TELEPHONY_LOGE("GetLteImsSwitchStatusResponse return, info is nullptr");
            return;
        }
        ImsResponseInfo responseInfo;
        responseInfo.slotId = slotId_;
        responseInfo.error = static_cast<ImsErrType>(info->error);
        DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetImsSwitchResponse(responseInfo);
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetImsSwitchResponse(slotId_, *active);
}

void ImsHandler::DialResponse(const AppExecFwk::InnerEvent::Pointer &event)
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
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("DialResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo responseInfo;
    responseInfo.slotId = slotId_;
    responseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateDialResponse(responseInfo);
}

void ImsHandler::HangUpResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("HangUpResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("HangUpResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("HangUpResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo responseInfo;
    responseInfo.slotId = slotId_;
    responseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateHangUpResponse(responseInfo);
}

void ImsHandler::RejectResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("RejectResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("RejectResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("RejectResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo responseInfo;
    responseInfo.slotId = slotId_;
    responseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateRejectResponse(responseInfo);
}

void ImsHandler::AnswerResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("AcceptResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("AcceptResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("AnswerResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo responseInfo;
    responseInfo.slotId = slotId_;
    responseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateAnswerResponse(responseInfo);
}

void ImsHandler::HoldCallResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("HoldCallResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("HoldCallResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("HoldCallResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo responseInfo;
    responseInfo.slotId = slotId_;
    responseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateHoldResponse(responseInfo);
}

void ImsHandler::UnHoldCallResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("UnHoldCallResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("UnHoldCallResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UnHoldCallResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo responseInfo;
    responseInfo.slotId = slotId_;
    responseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateUnHoldResponse(responseInfo);
}

void ImsHandler::SwitchCallResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SwitchCallResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("SwitchCallResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SwitchCallResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo responseInfo;
    responseInfo.slotId = slotId_;
    responseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSwitchResponse(responseInfo);
}

void ImsHandler::CombineConferenceResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CombineConferenceResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("CombineConferenceResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CombineConferenceResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo responseInfo;
    responseInfo.slotId = slotId_;
    responseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateCombineConferenceResponse(responseInfo);
}

void ImsHandler::InviteToConferenceResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("InviteToConferenceResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("InviteToConferenceResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("InviteToConferenceResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo responseInfo;
    responseInfo.slotId = slotId_;
    responseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateInviteToConferenceResponse(responseInfo);
}

void ImsHandler::KickOutFromConferenceResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("KickOutFromConferenceResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("KickOutFromConferenceResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("KickOutFromConferenceResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo responseInfo;
    responseInfo.slotId = slotId_;
    responseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateKickOutFromConferenceResponse(responseInfo);
}

void ImsHandler::UpdateCallMediaModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("UpdateCallMediaModeResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("UpdateCallMediaModeResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateCallMediaModeResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo imsResponseInfo;
    imsResponseInfo.slotId = slotId_;
    imsResponseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateCallMediaModeResponse(imsResponseInfo);
}

void ImsHandler::IsEmergencyPhoneNumberResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("IsEmergencyPhoneNumberResponse return, event is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("IsEmergencyPhoneNumberResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    auto value = event->GetSharedObject<int32_t>();
    if (value == nullptr) {
        TELEPHONY_LOGE("IsEmergencyPhoneNumberResponse, Cannot get the value, need to get imsResponseInfo");
        auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
        if (responseInfo == nullptr) {
            TELEPHONY_LOGE("IsEmergencyPhoneNumberResponse return, value and responseInfo is nullptr");
            return;
        }
        ImsResponseInfo imsResponseInfo;
        imsResponseInfo.slotId = slotId_;
        imsResponseInfo.error = static_cast<ImsErrType>(responseInfo->error);
        DelayedSingleton<ImsRegister>::GetInstance()->UpdateIsEmergencyPhoneNumberResponse(imsResponseInfo);
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateIsEmergencyPhoneNumberResponse(*value);
}

void ImsHandler::SendDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event)
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
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SendDtmfResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo imsResponseInfo;
    imsResponseInfo.slotId = slotId_;
    imsResponseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSendDtmfResponse(imsResponseInfo);
}

void ImsHandler::StartDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event)
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
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("StartDtmfResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo imsResponseInfo;
    imsResponseInfo.slotId = slotId_;
    imsResponseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateStartDtmfResponse(imsResponseInfo);
}

void ImsHandler::StopDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event)
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
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("StopDtmfResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo imsResponseInfo;
    imsResponseInfo.slotId = slotId_;
    imsResponseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateStopDtmfResponse(imsResponseInfo);
}

void ImsHandler::StartRttResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("StartRttResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("StartRttResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("StartRttResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo imsResponseInfo;
    imsResponseInfo.slotId = slotId_;
    imsResponseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateStartRttResponse(imsResponseInfo);
}

void ImsHandler::StopRttResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("StopRttResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("StopRttResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("StopRttResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo imsResponseInfo;
    imsResponseInfo.slotId = slotId_;
    imsResponseInfo.error = static_cast<ImsErrType>(result->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateStopRttResponse(imsResponseInfo);
}

void ImsHandler::GetImsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetImsCallsDataResponse return, event is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetImsCallsDataResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    auto imsCallInfoList = event->GetSharedObject<CallInfoList>();
    if (imsCallInfoList == nullptr) {
        TELEPHONY_LOGE("GetImsCallsDataResponse, Cannot get the imsCallInfoList, need to get imsResponseInfo");
        auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
        if (responseInfo == nullptr) {
            TELEPHONY_LOGE("GetImsCallsDataResponse return, callInfoList and responseInfo is nullptr");
            return;
        }
        ImsResponseInfo imsResponseInfo;
        imsResponseInfo.slotId = slotId_;
        imsResponseInfo.error = static_cast<ImsErrType>(responseInfo->error);
        DelayedSingleton<ImsRegister>::GetInstance()->UpdateImsCallsDataResponse(imsResponseInfo);
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateImsCallsDataResponse(slotId_, *imsCallInfoList);
}

void ImsHandler::SetImsConfigResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetImsConfigResponse return, event is nullptr");
        return;
    }
    auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
    if (responseInfo == nullptr) {
        TELEPHONY_LOGE("SetImsConfigResponse return, responseInfo is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetImsConfigResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo imsResponseInfo;
    imsResponseInfo.slotId = slotId_;
    imsResponseInfo.error = static_cast<ImsErrType>(responseInfo->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetImsConfigResponse(imsResponseInfo);
}

void ImsHandler::GetImsConfigResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetImsConfigResponse return, event is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetImsConfigResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    auto value = event->GetSharedObject<int32_t>();
    if (value == nullptr) {
        TELEPHONY_LOGE("GetImsConfigResponse, Cannot get the value, need to get imsResponseInfo");
        auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
        if (responseInfo == nullptr) {
            TELEPHONY_LOGE("GetImsConfigResponse return, value and responseInfo is nullptr");
            return;
        }
        ImsResponseInfo imsResponseInfo;
        imsResponseInfo.slotId = slotId_;
        imsResponseInfo.error = static_cast<ImsErrType>(responseInfo->error);
        DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetImsConfigResponse(imsResponseInfo);
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetImsConfigResponse(*value);
}

void ImsHandler::SetImsFeatureValueResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetImsFeatureValueResponse return, event is nullptr");
        return;
    }
    auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
    if (responseInfo == nullptr) {
        TELEPHONY_LOGE("SetImsFeatureValueResponse return, responseInfo is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetImsFeatureValueResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo imsResponseInfo;
    imsResponseInfo.slotId = slotId_;
    imsResponseInfo.error = static_cast<ImsErrType>(responseInfo->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetImsFeatureValueResponse(imsResponseInfo);
}

void ImsHandler::GetImsFeatureValueResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetImsFeatureValueResponse return, event is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetImsFeatureValueResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    auto value = event->GetSharedObject<int32_t>();
    if (value == nullptr) {
        TELEPHONY_LOGE("GetImsFeatureValueResponse, Cannot get the value, need to get imsResponseInfo");
        auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
        if (responseInfo == nullptr) {
            TELEPHONY_LOGE("GetImsFeatureValueResponse return, value and responseInfo is nullptr");
            return;
        }
        ImsResponseInfo imsResponseInfo;
        imsResponseInfo.slotId = slotId_;
        imsResponseInfo.error = static_cast<ImsErrType>(responseInfo->error);
        DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetImsFeatureValueResponse(imsResponseInfo);
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetImsFeatureValueResponse(*value);
}

void ImsHandler::SetVolteEnhanceModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetVolteEnhanceModeResponse return, event is nullptr");
        return;
    }
    auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
    if (responseInfo == nullptr) {
        TELEPHONY_LOGE("SetVolteEnhanceModeResponse return, responseInfo is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetVolteEnhanceModeResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo imsResponseInfo;
    imsResponseInfo.slotId = slotId_;
    imsResponseInfo.error = static_cast<ImsErrType>(responseInfo->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetVolteEnhanceModeResponse(imsResponseInfo);
}

void ImsHandler::GetVolteEnhanceModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetVolteEnhanceModeResponse return, event is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetVolteEnhanceModeResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    auto mode = event->GetSharedObject<int32_t>();
    if (mode == nullptr) {
        TELEPHONY_LOGE("GetVolteEnhanceModeResponse, Cannot get the mode, need to get imsResponseInfo");
        auto imsResponseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
        if (imsResponseInfo == nullptr) {
            TELEPHONY_LOGE("GetVolteEnhanceModeResponse return, mode and imsResponseInfo is nullptr");
            return;
        }
        ImsResponseInfo responseInfo;
        responseInfo.slotId = slotId_;
        responseInfo.error = static_cast<ImsErrType>(imsResponseInfo->error);
        DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetVolteEnhanceModeResponse(responseInfo);
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetVolteEnhanceModeResponse(*mode);
}

void ImsHandler::CtrlCameraResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CtrlCameraResponse return, event is nullptr");
        return;
    }
    auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
    if (responseInfo == nullptr) {
        TELEPHONY_LOGE("CtrlCameraResponse return, responseInfo is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CtrlCameraResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo info;
    info.slotId = slotId_;
    info.error = static_cast<ImsErrType>(responseInfo->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateCtrlCameraResponse(info);
}

void ImsHandler::SetPreviewWindowResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetPreviewWindowResponse return, event is nullptr");
        return;
    }
    auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
    if (responseInfo == nullptr) {
        TELEPHONY_LOGE("SetPreviewWindowResponse return, responseInfo is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetPreviewWindowResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo info;
    info.slotId = slotId_;
    info.error = static_cast<ImsErrType>(responseInfo->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetPreviewWindowResponse(info);
}

void ImsHandler::SetDisplayWindowResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetDisplayWindowResponse return, event is nullptr");
        return;
    }
    auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
    if (responseInfo == nullptr) {
        TELEPHONY_LOGE("SetDisplayWindowResponse return, responseInfo is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetDisplayWindowResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo info;
    info.slotId = slotId_;
    info.error = static_cast<ImsErrType>(responseInfo->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetDisplayWindowResponse(info);
}

void ImsHandler::SetCameraZoomResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCameraZoomResponse return, event is nullptr");
        return;
    }
    auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
    if (responseInfo == nullptr) {
        TELEPHONY_LOGE("SetCameraZoomResponse return, responseInfo is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetCameraZoomResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo info;
    info.slotId = slotId_;
    info.error = static_cast<ImsErrType>(responseInfo->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetCameraZoomResponse(info);
}

void ImsHandler::SetPauseImageResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetPauseImageResponse return, event is nullptr");
        return;
    }
    auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
    if (responseInfo == nullptr) {
        TELEPHONY_LOGE("SetPauseImageResponse return, responseInfo is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetPauseImageResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo info;
    info.slotId = slotId_;
    info.error = static_cast<ImsErrType>(responseInfo->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetPauseImageResponse(info);
}

void ImsHandler::SetDeviceDirectionResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetDeviceDirectionResponse return, event is nullptr");
        return;
    }
    auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
    if (responseInfo == nullptr) {
        TELEPHONY_LOGE("SetDeviceDirectionResponse return, responseInfo is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetDeviceDirectionResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    ImsResponseInfo info;
    info.slotId = slotId_;
    info.error = static_cast<ImsErrType>(responseInfo->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetDeviceDirectionResponse(info);
}

void ImsHandler::SetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::SetMuteResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetMuteResponse return, event is nullptr");
        return;
    }
    auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
    if (responseInfo == nullptr) {
        TELEPHONY_LOGE("SetMuteResponse return, responseInfo is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetMuteResponse return, GetInstance() is nullptr, report fail!");
        return;
    }
    MuteControlResponse response;
    response.result = static_cast<ImsErrType>(responseInfo->error);
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetMuteResponse(response);
}

void ImsHandler::GetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::GetMuteResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetMuteResponse return, event is nullptr");
        return;
    }
    MuteControlResponse response;
    auto mute = event->GetSharedObject<int32_t>();
    if (mute == nullptr) {
        auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
        if (responseInfo == nullptr) {
            TELEPHONY_LOGE("GetMuteResponse return, responseInfo is nullptr");
            return;
        }
        response.result = static_cast<ImsErrType>(responseInfo->error);
    } else {
        response.result = static_cast<int32_t>(HRilErrType::NONE);
        response.value = *mute;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetMuteResponse return, GetInstance() is nullptr, report fail!");
        return;
    }

    DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetMuteResponse(response);
}

void ImsHandler::GetEmergencyCallListResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::GetEmergencyCallListResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetEmergencyCallListResponse return, event is nullptr");
        return;
    }
    auto eccList = event->GetSharedObject<EmergencyInfoList>();
    if (eccList == nullptr) {
        TELEPHONY_LOGE("GetEmergencyCallListResponse return, eccList is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetEmergencyCallListResponse return, GetInstance is nullptr");
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetEccCallListResponse(*eccList);
}

void ImsHandler::CallRingBackVoiceResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::CallRingBackVoiceResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("CallRingBackVoiceResponse return, event is nullptr");
        return;
    }
    auto ringBackVoice = event->GetSharedObject<RingbackVoice>();
    if (ringBackVoice == nullptr) {
        TELEPHONY_LOGE("CallRingBackVoiceResponse return, ringBackVoice is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CallRingBackVoiceResponse return, GetInstance is nullptr");
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateCallRingBackResponse(*ringBackVoice);
}

void ImsHandler::GetCallFailReasonResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::GetCallFailReasonResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallFailReasonResponse return, event is nullptr");
        return;
    }
    auto reason = event->GetSharedObject<int32_t>();
    if (reason == nullptr) {
        TELEPHONY_LOGE("GetCallFailReasonResponse return, reason is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetCallFailReasonResponse return, GetInstance is nullptr");
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateCallFailReasonResponse(*reason);
}

void ImsHandler::GetClipResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::GetClipResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetClipResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<GetClipResult>();
    if (result == nullptr) {
        TELEPHONY_LOGE("GetClipResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetClipResponse return, GetInstance is nullptr");
        return;
    }
    ClipResponse response;
    response.result = (*result).result;
    response.action = (*result).action;
    response.clipStat = (*result).clipStat;
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetClipResponse(response);
}

void ImsHandler::GetClirResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::GetClirResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetClirResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<GetClirResult>();
    if (result == nullptr) {
        TELEPHONY_LOGE("GetClirResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetClirResponse return, GetInstance is nullptr");
        return;
    }
    ClirResponse response;
    response.result = (*result).result;
    response.action = (*result).action;
    response.clirStat = (*result).clirStat;
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetClirResponse(response);
}

void ImsHandler::SetClirResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::SetClirResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetClirResponse return, event is nullptr");
        return;
    }
    auto responseInfo = event->GetSharedObject<HRilRadioResponseInfo>();
    if (responseInfo == nullptr) {
        TELEPHONY_LOGE("SetClirResponse return, responseInfo is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetClirResponse return, GetInstance is nullptr");
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetClirResponse((*responseInfo).error);
}

void ImsHandler::GetCallTransferResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::GetCallTransferResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallTransferResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<CallForwardQueryResult>();
    if (result == nullptr) {
        TELEPHONY_LOGE("GetCallTransferResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetCallTransferResponse return, GetInstance is nullptr");
        return;
    }

    // 3GPP TS 27.007 V3.9.0 (2001-06) 7.11	Call forwarding number and conditions +CCFC
    CallTransferResponse response;
    if (memset_s(&response, sizeof(response), 0, sizeof(response)) != EOK) {
        TELEPHONY_LOGE("GetCallTransferResponse return, memset_s fail.");
        return;
    }

    if (strcpy_s(response.number, strlen((*result).number.c_str()) + 1, (*result).number.c_str()) != EOK) {
        TELEPHONY_LOGE("GetCallTransferResponse return, strcpy_s fail.");
        return;
    }
    response.result = (*result).result;
    response.status = (*result).status;
    response.classx = (*result).classx;
    response.type = (*result).type;
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetCallTransferResponse(response);
}

void ImsHandler::SetCallTransferResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::SetCallTransferResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallTransferResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("SetCallTransferResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetCallTransferResponse return, GetInstance is nullptr");
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetCallTransferResponse((*result).error);
}

void ImsHandler::GetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::GetCallRestrictionResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallRestrictionResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<CallRestrictionResult>();
    if (result == nullptr) {
        TELEPHONY_LOGE("GetCallRestrictionResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetCallRestrictionResponse return, GetInstance is nullptr");
        return;
    }
    CallRestrictionResponse response;
    response.result = (*result).result;
    response.status = (*result).status;
    response.classCw = (*result).classCw;
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetCallRestrictionResponse(response);
}

void ImsHandler::SetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::SetCallRestrictionResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallRestrictionResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("SetCallRestrictionResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetCallRestrictionResponse return, GetInstance is nullptr");
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetCallRestrictionResponse((*result).error);
}

void ImsHandler::GetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::GetCallWaitingResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallWaitingResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<CallWaitResult>();
    if (result == nullptr) {
        TELEPHONY_LOGE("GetCallWaitingResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetCallWaitingResponse return, GetInstance is nullptr");
        return;
    }
    CallWaitResponse response;
    response.result = (*result).result;
    response.status = (*result).status;
    response.classCw = (*result).classCw;
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateGetCallWaitingResponse(response);
}

void ImsHandler::SetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsHandler::SetCallWaitingResponse entry");
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallWaitingResponse return, event is nullptr");
        return;
    }
    auto result = event->GetSharedObject<HRilRadioResponseInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("SetCallWaitingResponse return, result is nullptr");
        return;
    }
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetCallWaitingResponse return, GetInstance is nullptr");
        return;
    }
    DelayedSingleton<ImsRegister>::GetInstance()->UpdateSetCallWaitingResponse((*result).error);
}
} // namespace Telephony
} // namespace OHOS