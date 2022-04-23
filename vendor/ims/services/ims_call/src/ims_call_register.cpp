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

#include "ims_call_register.h"
#include "telephony_errors.h"

namespace OHOS {
namespace Telephony {
ImsCallRegister::ImsCallRegister() {}

ImsCallRegister::~ImsCallRegister() {}

int32_t ImsCallRegister::UpdateDialResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->DialResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateHangUpResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->HangUpResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateRejectResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->RejectResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateAnswerResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("AnswerResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->AnswerResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateHoldResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("HoldResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->HoldResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateUnHoldResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UnHoldResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->UnHoldResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSwitchResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("SwitchResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SwitchResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateCombineConferenceResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("CombineConferenceResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->CombineConferenceResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateInviteToConferenceResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("InviteToConferenceResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->InviteToConferenceResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateKickOutFromConferenceResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("KickOutFromConferenceResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->KickOutFromConferenceResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateCallMediaModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("CallMediaModeResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->CallMediaModeResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateIsEmergencyPhoneNumberResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("IsEmergencyPhoneNumberResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->IsEmergencyPhoneNumberResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateIsEmergencyPhoneNumberResponse(bool value)
{
    TELEPHONY_LOGI("UpdateIsEmergencyPhoneNumberResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->IsEmergencyPhoneNumberResponse(value);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateStartDtmfResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("StartDtmfResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->StartDtmfResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSendDtmfResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("SendDtmfResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SendDtmfResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateStopDtmfResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("StopDtmfResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->StopDtmfResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateStartRttResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("StartRttResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->StartRttResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateStopRttResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("StopRttResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->StopRttResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateCallStateChangeReport(int32_t slotId)
{
    TELEPHONY_LOGI("UpdateCallStateChangeReport");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->CallStateChangeReport(slotId);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateServiceStatusResponse(int32_t slotId, const CallImsServiceStatus &callImsServiceStatus)
{
    TELEPHONY_LOGI("UpdateServiceStatusResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->ServiceStatusResponse(slotId, callImsServiceStatus);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetPreModeResponse(int32_t slotId, const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateSetPreModeResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetPreModeResponse(slotId, info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetPreModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("GetPreModeResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetPreModeResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetPreModeResponse(int32_t slotId, int32_t mode)
{
    TELEPHONY_LOGI("UpdateGetPreModeResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetPreModeResponse(slotId, mode);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetImsSwitchResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("SetImsSwitchResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetImsSwitchResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetImsSwitchResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("GetImsSwitchResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetImsSwitchResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetImsSwitchResponse(int32_t slotId, int32_t active)
{
    TELEPHONY_LOGI("UpdateGetImsSwitchResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetImsSwitchResponse(slotId, active);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateImsCallsDataResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallsDataResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->ImsCallsDataResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateImsCallsDataResponse(int32_t slotId, const ImsCurrentCallList &callList)
{
    TELEPHONY_LOGI("UpdateImsCallsDataResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->ImsCallsDataResponse(slotId, callList);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetImsConfigResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("SetImsConfigResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetImsConfigResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetImsConfigResponse(int32_t value)
{
    TELEPHONY_LOGI("UpdateGetImsConfigResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetImsConfigResponse(value);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetImsConfigResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("GetImsConfigResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetImsConfigResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetImsFeatureValueResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("SetImsFeatureValueResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetImsFeatureValueResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetImsFeatureValueResponse(int32_t value)
{
    TELEPHONY_LOGI("UpdateGetImsFeatureValueResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetImsFeatureValueResponse(value);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetImsFeatureValueResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("GetImsFeatureValueResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetImsFeatureValueResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("SetImsSwitchEnhanceModeResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetImsSwitchEnhanceModeResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetImsSwitchEnhanceModeResponse(int32_t value)
{
    TELEPHONY_LOGI("UpdateGetImsSwitchEnhanceModeResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetImsSwitchEnhanceModeResponse(value);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("GetImsSwitchEnhanceModeResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetImsSwitchEnhanceModeResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateCtrlCameraResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("CtrlCameraResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->CtrlCameraResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetPreviewWindowResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("SetPreviewWindowResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetPreviewWindowResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetDisplayWindowResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("SetDisplayWindowResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetDisplayWindowResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetCameraZoomResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("SetCameraZoomResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetCameraZoomResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetPauseImageResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("SetPauseImageResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetPauseImageResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetDeviceDirectionResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("SetDeviceDirectionResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetDeviceDirectionResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSrvccStateReport(int32_t slotId, SrvccState srvccState)
{
    TELEPHONY_LOGI("UpdateSrvccStateReport");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SrvccStateReport(slotId, srvccState);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateVtWfcReport(int32_t slotId, TransferState transferState)
{
    TELEPHONY_LOGI("UpdateVtWfcReport");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->VtWfcReport(slotId, transferState);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateCallRingBackResponse(const RingbackVoice &info)
{
    TELEPHONY_LOGI("CallRingBackResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->CallRingBackResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetMuteResponse(const MuteControlResponse &response)
{
    TELEPHONY_LOGI("SetMuteResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetMuteResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetMuteResponse(const MuteControlResponse &response)
{
    TELEPHONY_LOGI("GetMuteResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetMuteResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetEccCallListResponse(const EmergencyInfoList &callList)
{
    TELEPHONY_LOGI("GetEccCallListResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetEccCallListResponse(callList);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateLastCallFailReasonResponse(int32_t reason)
{
    TELEPHONY_LOGI("UpdateCallLastFailReasonResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->LastCallFailReasonResponse(reason);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetClipResponse(const ClipResponse &response)
{
    TELEPHONY_LOGI("GetClipResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetClipResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetClirResponse(const ClirResponse &response)
{
    TELEPHONY_LOGI("GetClirResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetClirResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetClirResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("SetClirResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetClirResponse(errType);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetCallTransferResponse(const CallTransferResponse &response)
{
    TELEPHONY_LOGI("GetCallTransferResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetCallTransferResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetCallTransferResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("UpdateSetCallTransferResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetCallTransferResponse(errType);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetCallRestrictionResponse(const CallRestrictionResponse &response)
{
    TELEPHONY_LOGI("GetCallRestrictionResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetCallRestrictionResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetCallRestrictionResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("SetCallRestrictionResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetCallRestrictionResponse(errType);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateGetCallWaitingResponse(const CallWaitResponse &response)
{
    TELEPHONY_LOGI("GetCallWaitingResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->GetCallWaitingResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::UpdateSetCallWaitingResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("SetCallWaitingResponse");
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("imsCallCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_->SetCallWaitingResponse(errType);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallRegister::RegisterImsCallCallBack(const sptr<ImsCallCallbackInterface> &callback)
{
    imsCallCallback_ = callback;
    return TELEPHONY_SUCCESS;
}

bool ImsCallRegister::IsCallBackExists()
{
    return imsCallCallback_ != nullptr;
}
} // namespace Telephony
} // namespace OHOS
