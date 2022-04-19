/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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
#include "ims_call_handler.h"
#include "ims_radio_event.h"
#include "ims_call_register.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
ImsCallHandler::ImsCallHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner)
    : ImsBaseHandler(runner)
{
    InitRequestFuncMap();
}

ImsCallHandler::~ImsCallHandler() {}

void ImsCallHandler::ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("ImsCallHandler::ProcessEvent event is nullptr");
        return;
    }
    auto it = requestFuncMap_.find(event->GetInnerEventId());
    if (it == requestFuncMap_.end()) {
        TELEPHONY_LOGE("Can not find eventId");
        return;
    }

    auto requestFunc = it->second;
    if (requestFunc != nullptr) {
        (this->*requestFunc)(event);
    } else {
        TELEPHONY_LOGE("Request function is nullptr");
    }
}

void ImsCallHandler::DialResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("DialResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("DialResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("DialResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateDialResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::DialResponse");
}

void ImsCallHandler::HangUpResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("HangUpResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("HangUpResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("HangUpResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateHangUpResponse(*info);

    TELEPHONY_LOGI("ImsCallHandler::HangUpResponse");
}

void ImsCallHandler::RejectResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("RejectResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("RejectResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("RejectResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateHangUpResponse(*info);

    TELEPHONY_LOGI("ImsCallHandler::RejectResponse");
}

void ImsCallHandler::AnswerResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("AnswerResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("AnswerResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("AnswerResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateHangUpResponse(*info);

    TELEPHONY_LOGI("ImsCallHandler::AnswerResponse");
}

void ImsCallHandler::HoldResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("HoldResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("HoldResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("HoldResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateHoldResponse(*info);

    TELEPHONY_LOGI("ImsCallHandler::HoldResponse");
}

void ImsCallHandler::UnHoldResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("UnHoldResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("UnHoldResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("UnHoldResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateUnHoldResponse(*info);

    TELEPHONY_LOGI("ImsCallHandler::UnHoldResponse");
}

void ImsCallHandler::SwitchResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SwitchResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SwitchResponse, ImsRegister is nullptr");
        return;
    }

    TELEPHONY_LOGI("ImsCallHandler::SwitchResponse");
}

void ImsCallHandler::CombineConferenceResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CombineConferenceResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("CombineConferenceResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("CombineConferenceResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateCombineConferenceResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::CombineConferenceResponse");
}

void ImsCallHandler::InviteToConferenceResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("InviteToConferenceResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("InviteToConferenceResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("InviteToConferenceResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateInviteToConferenceResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::InviteToConferenceResponse");
}

void ImsCallHandler::KickOutFromConferenceResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("KickOutFromConferenceResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("KickOutFromConferenceResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("KickOutFromConferenceResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateKickOutFromConferenceResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::KickOutFromConferenceResponse");
}

void ImsCallHandler::CallMediaModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CallMediaModeResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("CallMediaModeResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("CallMediaModeResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateCallMediaModeResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::CallMediaModeResponse");
}

void ImsCallHandler::IsEmergencyPhoneNumberResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("IsEmergencyPhoneNumberResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("IsEmergencyPhoneNumberResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("IsEmergencyPhoneNumberResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateIsEmergencyPhoneNumberResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::IsEmergencyPhoneNumberResponse");
}

void ImsCallHandler::ImsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("ImsCallsDataResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("ImsCallsDataResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("ImsCallsDataResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateImsCallsDataResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::ImsCallsDataResponse");
}

void ImsCallHandler::CallStatusResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CallStatusResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("CallStatusResponse, ImsRegister is nullptr");
        return;
    }
    auto slotId = event->GetSharedObject<int32_t>();
    if (slotId == nullptr) {
        TELEPHONY_LOGE("CallStatusResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateCallStateChangeReport(*slotId);
    TELEPHONY_LOGI("ImsCallHandler::CallStatusResponse");
}

void ImsCallHandler::CallFailReasonResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CallFailReasonResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("DialResponse, ImsRegister is nullptr");
        return;
    }
    auto reason = event->GetSharedObject<int32_t>();
    if (reason == nullptr) {
        TELEPHONY_LOGE("CallFailgReasonResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateLastCallFailReasonResponse(*reason);
    TELEPHONY_LOGI("ImsCallHandler::CallFailReasonResponse");
}

void ImsCallHandler::CallRingBackResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CallRingBackResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("CallRingBackResponse, ImsRegister is nullptr");
        return;
    }
    auto voice = event->GetSharedObject<RingbackVoice>();
    if (voice == nullptr) {
        TELEPHONY_LOGE("CallRingBackResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateCallRingBackResponse(*voice);
    TELEPHONY_LOGI("ImsCallHandler::CallRingBackResponse");
}

void ImsCallHandler::GetEccCallListResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetEccCallListResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("GetEccCallListResponse, ImsRegister is nullptr");
        return;
    }
    auto list = event->GetSharedObject<EmergencyInfoList>();
    if (list == nullptr) {
        TELEPHONY_LOGE("GetEccCallListResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateGetEccCallListResponse(*list);
    TELEPHONY_LOGI("ImsCallHandler::GetEccCallListResponse");
}


/*  --------------  dtmf and rtt --------------- */
void ImsCallHandler::StartDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("StartDtmfResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("StartDtmfResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("StartDtmfResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateStartDtmfResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::StartDtmfResponse");
}

void ImsCallHandler::SendDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SendDtmfResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SendDtmfResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SendDtmfResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSendDtmfResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::SendDtmfResponse");
}

void ImsCallHandler::StopDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("StopDtmfResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("StopDtmfResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("StopDtmfResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateStopDtmfResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::StopDtmfResponse");
}

void ImsCallHandler::StartRttResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("StartRttResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("StartRttResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("StartRttResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateStartRttResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::StartRttResponse");
}

void ImsCallHandler::StopRttResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("StopRttResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("StopRttResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("StopRttResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateStopRttResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::StopRttResponse");
}


/* ---------------  ims config ----------------- */
void ImsCallHandler::ServiceStatusResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("ServiceStatusResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("ServiceStatusResponse, ImsRegister is nullptr");
        return;
    }
    auto slotId = event->GetSharedObject<int32_t>();
    if (slotId == nullptr) {
        TELEPHONY_LOGE("ServiceStatusResponse, result is nullptr");
        return;
    }
    auto status = event->GetSharedObject<CallImsServiceStatus>();
    if (status == nullptr) {
        TELEPHONY_LOGE("ServiceStatusResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateServiceStatusResponse(*slotId, *status);
    TELEPHONY_LOGI("ImsCallHandler::ServiceStatusResponse");
}

void ImsCallHandler::SetPreModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetPreModeResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetPreModeResponse, ImsRegister is nullptr");
        return;
    }
    auto slotId = event->GetSharedObject<int32_t>();
    if (slotId == nullptr) {
        TELEPHONY_LOGE("SetPreModeResponse, result is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetPreModeResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetPreModeResponse(*slotId, *info);
    TELEPHONY_LOGI("ImsCallHandler::SetPreModeResponse");
}

void ImsCallHandler::GetPreModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetPreModeResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("GetPreModeResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("GetPreModeResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateGetPreModeResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::GetPreModeResponse");
}

void ImsCallHandler::SetImsSwitchResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetImsSwitchResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetImsSwitchResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetImsSwitchResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetImsSwitchResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::SetImsSwitchResponse");
}

void ImsCallHandler::GetImsSwitchResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetImsSwitchResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("GetImsSwitchResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("GetImsSwitchResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateGetImsSwitchResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::GetImsSwitchResponse");
}

void ImsCallHandler::SetImsConfigResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetImsConfigResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetImsConfigResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetImsConfigResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetImsConfigResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::SetImsConfigResponse");
}

void ImsCallHandler::GetImsConfigResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetImsConfigResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("GetImsConfigResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("GetImsConfigResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateGetImsConfigResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::GetImsConfigResponse");
}

void ImsCallHandler::SetImsFeatureValueResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetImsFeatureValueResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetImsFeatureValueResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetImsFeatureValueResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetImsFeatureValueResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::SetImsFeatureValueResponse");
}

void ImsCallHandler::GetImsFeatureValueResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetImsFeatureValueResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("GetImsFeatureValueResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("GetImsFeatureValueResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateGetImsFeatureValueResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::GetImsFeatureValueResponse");
}

void ImsCallHandler::SetImsSwitchEnhanceModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetImsSwitchEnhanceModeResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetImsSwitchEnhanceModeResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetImsSwitchEnhanceModeResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetImsSwitchEnhanceModeResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::SetImsSwitchEnhanceModeResponse");
}

void ImsCallHandler::GetImsSwitchEnhanceModeResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetImsSwitchEnhanceModeResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("GetImsSwitchEnhanceModeResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("GetImsSwitchEnhanceModeResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateGetImsSwitchEnhanceModeResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::GetImsSwitchEnhanceModeResponse");
}

void ImsCallHandler::SetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetMuteResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetMuteResponse, ImsRegister is nullptr");
        return;
    }
    auto response = event->GetSharedObject<MuteControlResponse>();
    if (response == nullptr) {
        TELEPHONY_LOGE("SetMuteResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetMuteResponse(*response);
    TELEPHONY_LOGI("ImsCallHandler::SetMuteResponse");
}

void ImsCallHandler::GetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetMuteResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("GetMuteResponse, ImsRegister is nullptr");
        return;
    }
    auto response = event->GetSharedObject<MuteControlResponse>();
    if (response == nullptr) {
        TELEPHONY_LOGE("GetMuteResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateGetMuteResponse(*response);
    TELEPHONY_LOGI("ImsCallHandler::GetMuteResponse");
}

void ImsCallHandler::SrvccStateReport(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SrvccStateReport, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SrvccStateReport, ImsRegister is nullptr");
        return;
    }
    auto slotId = event->GetSharedObject<int32_t>();
    if (slotId == nullptr) {
        TELEPHONY_LOGE("SrvccStateReport, result is nullptr");
        return;
    }
    auto state = event->GetSharedObject<SrvccState>();
    if (state == nullptr) {
        TELEPHONY_LOGE("SrvccStateReport, result is nullptr");
        return;
    }
    imsRegister->UpdateSrvccStateReport(*slotId, *state);
    TELEPHONY_LOGI("ImsCallHandler::SrvccStateReport");
}


/* ---------------  video control ----------------- */
void ImsCallHandler::CtrlCameraResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("CtrlCameraResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("CtrlCameraResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("CtrlCameraResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateCtrlCameraResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::CtrlCameraResponse");
}

void ImsCallHandler::SetPreviewWindowResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetPreviewWindowResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetPreviewWindowResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetPreviewWindowResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetPreviewWindowResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::SetPreviewWindowResponse");
}

void ImsCallHandler::SetDisplayWindowResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetDisplayWindowResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetDisplayWindowResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetDisplayWindowResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetDisplayWindowResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::SetDisplayWindowResponse");
}

void ImsCallHandler::SetCameraZoomResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCameraZoomResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetCameraZoomResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetCameraZoomResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetCameraZoomResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::SetCameraZoomResponse");
}

void ImsCallHandler::SetPauseImageResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetPauseImageResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetPauseImageResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetPauseImageResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetPauseImageResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::SetPauseImageResponse");
}

void ImsCallHandler::SetDeviceDirectionResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetDeviceDirectionResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetDeviceDirectionResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("SetDeviceDirectionResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetDeviceDirectionResponse(*info);
    TELEPHONY_LOGI("ImsCallHandler::SetDeviceDirectionResponse");
}

void ImsCallHandler::VtWfcReport(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("VtWfcReport, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("VtWfcReport, ImsRegister is nullptr");
        return;
    }
    auto stotId = event->GetSharedObject<int32_t>();
    if (stotId == nullptr) {
        TELEPHONY_LOGE("VtWfcReport, result is nullptr");
        return;
    }
    auto state = event->GetSharedObject<TransferState>();
    if (state == nullptr) {
        TELEPHONY_LOGE("VtWfcReport, result is nullptr");
        return;
    }
    imsRegister->UpdateVtWfcReport(*stotId, *state);
    TELEPHONY_LOGI("ImsCallHandler::VtWfcReport");
}

/* --------------  supplyment ------------------- */
void ImsCallHandler::GetClipResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetClipResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("GetClipResponse, ImsRegister is nullptr");
        return;
    }
    auto response = event->GetSharedObject<ClipResponse>();
    if (response == nullptr) {
        TELEPHONY_LOGE("GetClipResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateGetClipResponse(*response);
    TELEPHONY_LOGI("ImsCallHandler::GetClipResponse");
}

void ImsCallHandler::GetClirResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetClirResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("GetClirResponse, ImsRegister is nullptr");
        return;
    }
    auto response = event->GetSharedObject<ClirResponse>();
    if (response == nullptr) {
        TELEPHONY_LOGE("GetClirResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateGetClirResponse(*response);
    TELEPHONY_LOGI("ImsCallHandler::GetClirResponse");
}

void ImsCallHandler::SetClirResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetClirResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetClirResponse, ImsRegister is nullptr");
        return;
    }
    auto err = event->GetSharedObject<HRilErrType>();
    if (err == nullptr) {
        TELEPHONY_LOGE("SetClirResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetClirResponse(*err);
    TELEPHONY_LOGI("ImsCallHandler::SetClirResponse");
}

void ImsCallHandler::GetCallTransferResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallTransferResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("GetCallTransferResponse, ImsRegister is nullptr");
        return;
    }
    auto response = event->GetSharedObject<CallTransferResponse>();
    if (response == nullptr) {
        TELEPHONY_LOGE("GetCallTransferResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateGetCallTransferResponse(*response);
    TELEPHONY_LOGI("ImsCallHandler::GetCallTransferResponse");
}

void ImsCallHandler::SetCallTransferResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallTransferResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetCallTransferResponse, ImsRegister is nullptr");
        return;
    }
    auto err = event->GetSharedObject<HRilErrType>();
    if (err == nullptr) {
        TELEPHONY_LOGE("SetCallTransferResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetCallTransferResponse(*err);
    TELEPHONY_LOGI("ImsCallHandler::SetCallTransferResponse");
}

void ImsCallHandler::GetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallRestrictionResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("GetCallRestrictionResponse, ImsRegister is nullptr");
        return;
    }
    auto response = event->GetSharedObject<CallRestrictionResponse>();
    if (response == nullptr) {
        TELEPHONY_LOGE("GetCallRestrictionResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateGetCallRestrictionResponse(*response);
    TELEPHONY_LOGI("ImsCallHandler::GetCallRestrictionResponse");
}

void ImsCallHandler::SetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallRestrictionResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetCallRestrictionResponse, ImsRegister is nullptr");
        return;
    }
    auto err = event->GetSharedObject<HRilErrType>();
    if (err == nullptr) {
        TELEPHONY_LOGE("SetCallRestrictionResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetCallRestrictionResponse(*err);
    TELEPHONY_LOGI("ImsCallHandler::SetCallRestrictionResponse");
}

void ImsCallHandler::GetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallWaitingResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("GetCallWaitingResponse, ImsRegister is nullptr");
        return;
    }
    auto response = event->GetSharedObject<CallWaitResponse>();
    if (response == nullptr) {
        TELEPHONY_LOGE("GetCallWaitingResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateGetCallWaitingResponse(*response);
    TELEPHONY_LOGI("ImsCallHandler::GetCallWaitingResponse");
}

void ImsCallHandler::SetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallWaitingResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("SetCallWaitingResponse, ImsRegister is nullptr");
        return;
    }
    auto err = event->GetSharedObject<HRilErrType>();
    if (err == nullptr) {
        TELEPHONY_LOGE("SetCallWaitingResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateSetCallWaitingResponse(*err);
    TELEPHONY_LOGI("ImsCallHandler::SetCallWaitingResponse");
}

void ImsCallHandler::ImsServiceStatusReport(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsCallHandler::ImsServiceStatusReport");
}

void ImsCallHandler::InitRequestFuncMap()
{
    InitDialRequestFuncMap();
    InitDtmfRequestFuncMap();
    InitConfigRequestFuncMap();
    InitVideoRequestFuncMap();
    InitSupplymentRequestFuncMap();

    requestFuncMap_[ImsRadioEvent::IMS_RAIDO_SERVICE_STATUS] = &ImsCallHandler::ImsServiceStatusReport;
}

void ImsCallHandler::InitDialRequestFuncMap()
{
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_DIAL] = &ImsCallHandler::DialResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_HANGUP] = &ImsCallHandler::HangUpResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_REJECT] = &ImsCallHandler::RejectResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_ANSWER] = &ImsCallHandler::AnswerResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_HOLD] = &ImsCallHandler::HoldResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_UN_HOLD] = &ImsCallHandler::UnHoldResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SWITCH] = &ImsCallHandler::SwitchResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_COMBINE_CONFERENCE] = &ImsCallHandler::CombineConferenceResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_INVITE_TO_CONFERENCE] = &ImsCallHandler::InviteToConferenceResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_KICK_OUT_CONFERENCE] = &ImsCallHandler::KickOutFromConferenceResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_UPDATE_CALL_MEDIA_MODE] = &ImsCallHandler::CallMediaModeResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_IS_EMERGENCY_NUMBER] = &ImsCallHandler::IsEmergencyPhoneNumberResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_CALL_STATUS] = &ImsCallHandler::CallStatusResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_CALL_DATA] = &ImsCallHandler::ImsCallsDataResponse;
    requestFuncMap_[ImsRadioEvent::IMS_GET_LAST_CALL_FAIL_REASON] = &ImsCallHandler::CallFailReasonResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_CALL_RINGBACK] = &ImsCallHandler::CallRingBackResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_ECC_CALL_LIST] = &ImsCallHandler::GetEccCallListResponse;
}

void ImsCallHandler::InitDtmfRequestFuncMap()
{
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_START_DTMF] = &ImsCallHandler::StartDtmfResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SEND_DTMF] = &ImsCallHandler::SendDtmfResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_STOP_DTMF] = &ImsCallHandler::StopDtmfResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_START_RTT] = &ImsCallHandler::StartRttResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_STOP_RTT] = &ImsCallHandler::StopRttResponse;
}

void ImsCallHandler::InitConfigRequestFuncMap()
{
    requestFuncMap_[ImsRadioEvent::IMS_RAIDO_SERVICE_STATUS] = &ImsCallHandler::ServiceStatusResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_DOMAIN_PREFERENCE_MODE] = &ImsCallHandler::SetPreModeResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_DOMAIN_PREFERENCE_MODE] = &ImsCallHandler::GetPreModeResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_LTE_SWITCH_STATUS] = &ImsCallHandler::SetImsSwitchResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_LTE_SWITCH_STATUS] = &ImsCallHandler::GetImsSwitchResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_CONFIG] = &ImsCallHandler::SetImsConfigResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_CONFIG] = &ImsCallHandler::GetImsConfigResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_FEATURE] = &ImsCallHandler::SetImsFeatureValueResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_FEATURE] = &ImsCallHandler::GetImsFeatureValueResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_SWITCH_ENHANCE_MODE] =
        &ImsCallHandler::SetImsSwitchEnhanceModeResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_SWITCH_ENHANCE_MODE] =
        &ImsCallHandler::GetImsSwitchEnhanceModeResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_MUTE] = &ImsCallHandler::SetMuteResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_MUTE] = &ImsCallHandler::GetMuteResponse;
    requestFuncMap_[ImsRadioEvent::IMS_SRVCC_STATUS] = &ImsCallHandler::SrvccStateReport;
}

void ImsCallHandler::InitVideoRequestFuncMap()
{
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_CTRL_CAMERA] = &ImsCallHandler::CtrlCameraResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_PREVIEW_WINDOW] = &ImsCallHandler::SetPreviewWindowResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_DISPLAY_WINDOW] = &ImsCallHandler::SetDisplayWindowResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_CAMERA_ZOOM] = &ImsCallHandler::SetCameraZoomResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_PAUSE_IMAGE] = &ImsCallHandler::SetPauseImageResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_DEVICE_DIRECTION] = &ImsCallHandler::SetDeviceDirectionResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_VT_WFC] = &ImsCallHandler::SetDeviceDirectionResponse;
}

void ImsCallHandler::InitSupplymentRequestFuncMap()
{
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_CLIP] = &ImsCallHandler::GetClipResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_CLIR] = &ImsCallHandler::SetClirResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_CLIR] = &ImsCallHandler::GetClirResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_CALL_TRANSFER] = &ImsCallHandler::SetCallTransferResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_CALL_TRANSFER] = &ImsCallHandler::GetCallTransferResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_CALL_RESTRICTION] = &ImsCallHandler::SetCallRestrictionResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_CALL_RESTRICTION] = &ImsCallHandler::GetCallRestrictionResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_CALL_WAITING] = &ImsCallHandler::SetCallWaitingResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_CALL_WAITING] = &ImsCallHandler::GetCallWaitingResponse;
}
} // Telephony
} // OHOS

