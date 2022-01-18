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

#include "ims_ril_request.h"

#include "call_manager_errors.h"
#include "core_manager_inner.h"
#include "ims_service.h"
#include "radio_event.h"
#include "telephony_types.h"

namespace OHOS {
namespace Telephony {
// This is the logic of piling. Variables are temporarily stored.
// These temporary variables can be removed during subsequent development by the manufacturer.
bool ImsRilRequest::imsSwitchEnhanceModeTemp_ = false;
int32_t ImsRilRequest::itemVideoQualityTemp_ = 0;
int32_t ImsRilRequest::itemImsSwitchStatusTemp_ = 0;
int32_t ImsRilRequest::voiceOverLteTemp_ = 0;
int32_t ImsRilRequest::videoOverLteTemp_ = 0;

ImsRilRequest::ImsRilRequest()
{
    imsRegisterInstance_ = DelayedSingleton<ImsRegister>::GetInstance();
}

int32_t ImsRilRequest::DialRequest(const ImsCallInfo &callInfo, CLIRMode mode) const
{
    TELEPHONY_LOGI("DialRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("DialRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(callInfo.slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("DialRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().Dial(callInfo.slotId, RadioEvent::RADIO_DIAL, callInfo.phoneNum, mode, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::HangUpRequest(int32_t slotId, int32_t index) const
{
    TELEPHONY_LOGI("HangUpRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("HangUpRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("HangUpRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().Hangup(slotId, RadioEvent::RADIO_HANGUP_CONNECT, index, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::AnswerRequest(int32_t slotId, int32_t videoState) const
{
    TELEPHONY_LOGI("AnswerRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("AnswerRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("AnswerRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().Answer(slotId, RadioEvent::RADIO_ACCEPT_CALL, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::RejectRequest(int32_t slotId) const
{
    TELEPHONY_LOGI("RejectRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("RejectRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("RejectRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().Reject(slotId, RadioEvent::RADIO_REJECT_CALL, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::HoldRequest(int32_t slotId) const
{
    TELEPHONY_LOGI("HoldRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("HoldRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("HoldRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().HoldCall(slotId, RadioEvent::RADIO_HOLD_CALL, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::UnHoldCallRequest(int32_t slotId) const
{
    TELEPHONY_LOGI("ActiveRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UnHoldCallRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("UnHoldCallRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().UnHoldCall(slotId, RadioEvent::RADIO_ACTIVE_CALL, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SwitchCallRequest(int32_t slotId) const
{
    TELEPHONY_LOGI("SwapRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SwitchCallRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("SwitchCallRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().SwitchCall(slotId, RadioEvent::RADIO_SWAP_CALL, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::CombineConferenceRequest(int32_t slotId, int32_t voiceCall) const
{
    TELEPHONY_LOGI("CombineConferenceRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CombineConferenceRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("CombineConferenceRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().CombineConference(slotId, RadioEvent::RADIO_JOIN_CALL, voiceCall, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::InviteToConferenceRequest(int32_t slotId, const std::vector<std::string> &numberList) const
{
    TELEPHONY_LOGI("InviteToConferenceRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("InviteToConferenceRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateInviteToConferenceResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::KickOutFromConferenceRequest(int32_t slotId, const std::vector<std::string> &numberList) const
{
    TELEPHONY_LOGI("KickOutFromConferenceRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("KickOutFromConferenceRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateKickOutFromConferenceResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::UpdateCallMediaModeRequest(int32_t slotId, ImsCallMode mode) const
{
    TELEPHONY_LOGI("UpdateCallMediaModeRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("UpdateCallMediaModeRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateCallMediaModeResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::IsEmergencyPhoneNumberRequest(int32_t slotId, const std::string &phoneNum) const
{
    TELEPHONY_LOGI("IsEmergencyPhoneNumberRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("IsEmergencyPhoneNumberRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateIsEmergencyPhoneNumberResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SendDtmfRequest(int32_t slotId, char cDtmfCode, int32_t index) const
{
    TELEPHONY_LOGI("SendDtmfRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SendDtmfRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("SendDtmfRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().SendDTMF(slotId, RadioEvent::RADIO_SEND_DTMF, cDtmfCode, index, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::StartDtmfRequest(int32_t slotId, char cDtmfCode, int32_t index) const
{
    TELEPHONY_LOGI("StartDtmfRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("StartDtmfRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("StartDtmfRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().StartDTMF(slotId, RadioEvent::RADIO_START_DTMF, cDtmfCode, index, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::StopDtmfRequest(int32_t slotId, int32_t index) const
{
    TELEPHONY_LOGI("StopDtmfRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("StopDtmfRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("StopDtmfRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().StopDTMF(slotId, RadioEvent::RADIO_STOP_DTMF, index, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::StartRttRequest(int32_t slotId, const std::string &msg) const
{
    TELEPHONY_LOGI("StartRttRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("StartRttRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateStartRttResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::StopRttRequest(int32_t slotId) const
{
    TELEPHONY_LOGI("StopRttRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("StopRttRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateStopRttResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag) const
{
    TELEPHONY_LOGI("GetImsCallsDataRequest entry.");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetImsCallsDataRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("GetImsCallsDataRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().GetImsCallList(slotId, RadioEvent::RADIO_GET_IMS_CALL_LIST, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetDomainPreferenceModeRequest(int32_t slotId, int32_t mode) const
{
    TELEPHONY_LOGI("SetDomainPreferenceModeRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetDomainPreferenceModeRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("SetDomainPreferenceModeRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().SetCallPreferenceMode(
        slotId, RadioEvent::RADIO_SET_CALL_PREFERENCE_MODE, mode, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::GetDomainPreferenceModeRequest(int32_t slotId) const
{
    TELEPHONY_LOGI("GetDomainPreferenceModeRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetDomainPreferenceModeRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("GetDomainPreferenceModeRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().GetCallPreferenceMode(slotId, RadioEvent::RADIO_GET_CALL_PREFERENCE_MODE, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetLteImsSwitchStatusRequest(int32_t slotId, int32_t active) const
{
    TELEPHONY_LOGI("SetLteImsSwitchStatusRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetLteImsSwitchStatusRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("SetLteImsSwitchStatusRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().SetLteImsSwitchStatus(
        slotId, RadioEvent::RADIO_SET_LTE_IMS_SWITCH_STATUS, active, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::GetLteImsSwitchStatusRequest(int32_t slotId) const
{
    TELEPHONY_LOGI("GetLteImsSwitchStatusRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetLteImsSwitchStatusRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("GetLteImsSwitchStatusRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().GetLteImsSwitchStatus(slotId, RadioEvent::RADIO_GET_LTE_IMS_SWITCH_STATUS, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetImsConfigRequest(ImsConfigItem item, const std::string &value) const
{
    TELEPHONY_LOGI("SetImsConfigRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("SetImsConfigRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateSetImsConfigResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetImsConfigRequest(ImsConfigItem item, int32_t value) const
{
    TELEPHONY_LOGI("SetImsConfigRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    switch (item) {
        case ImsConfigItem::ITEM_VIDEO_QUALITY:
            itemVideoQualityTemp_ = value;
            break;
        case ImsConfigItem::ITEM_IMS_SWITCH_STATUS:
            itemImsSwitchStatusTemp_ = value;
            break;
        default:
            TELEPHONY_LOGE("SetImsConfigRequest return, item out of range!");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
    }

    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("SetImsConfigRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateSetImsConfigResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::GetImsConfigRequest(ImsConfigItem item) const
{
    TELEPHONY_LOGI("GetImsConfigRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    int32_t value = 0;
    switch (item) {
        case ImsConfigItem::ITEM_VIDEO_QUALITY:
            value = itemVideoQualityTemp_;
            break;
        case ImsConfigItem::ITEM_IMS_SWITCH_STATUS:
            value = itemImsSwitchStatusTemp_;
            break;
        default:
            TELEPHONY_LOGE("GetImsConfigRequest return, item out of range!");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
    }

    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("GetImsConfigRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateGetImsConfigResponse(value);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetImsFeatureValueRequest(FeatureType type, int32_t value) const
{
    TELEPHONY_LOGI("SetImsFeatureValueRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    switch (type) {
        case FeatureType::TYPE_VOICE_OVER_LTE:
            voiceOverLteTemp_ = value;
            break;
        case FeatureType::TYPE_VIDEO_OVER_LTE:
            videoOverLteTemp_ = value;
            break;
        default:
            TELEPHONY_LOGE("SetImsFeatureValueRequest return, type out of range!");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
    }

    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("SetImsFeatureValueRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateSetImsFeatureValueResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::GetImsFeatureValueRequest(FeatureType type) const
{
    TELEPHONY_LOGI("GetImsFeatureValueRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    int32_t value = 0;
    switch (type) {
        case FeatureType::TYPE_VOICE_OVER_LTE:
            value = voiceOverLteTemp_;
            break;
        case FeatureType::TYPE_VIDEO_OVER_LTE:
            value = videoOverLteTemp_;
            break;
        default:
            TELEPHONY_LOGE("GetImsFeatureValueRequest return, item out of range!");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
    }

    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("GetImsFeatureValueRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateGetImsFeatureValueResponse(value);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetImsSwitchEnhanceModeRequest(bool value) const
{
    TELEPHONY_LOGI("SetImsSwitchEnhanceModeRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    TELEPHONY_LOGI("SetImsSwitchEnhanceModeRequest value: %{public}d", value);
    imsSwitchEnhanceModeTemp_ = value;
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("SetImsSwitchEnhanceModeRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateSetImsSwitchEnhanceModeResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::GetImsSwitchEnhanceModeRequest() const
{
    TELEPHONY_LOGI("GetImsSwitchEnhanceModeRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("GetImsSwitchEnhanceModeRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateGetImsSwitchEnhanceModeResponse(imsSwitchEnhanceModeTemp_);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::CtrlCameraRequest(const std::u16string &cameraId, int32_t callingUid, int32_t callingPid) const
{
    TELEPHONY_LOGI("CtrlCameraRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("CtrlCameraRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateCtrlCameraResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetPreviewWindowRequest(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height) const
{
    TELEPHONY_LOGI("SetPreviewWindowRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("SetPreviewWindowRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateSetPreviewWindowResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetDisplayWindowRequest(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height) const
{
    TELEPHONY_LOGI("SetDisplayWindowRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("SetDisplayWindowRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateSetDisplayWindowResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetCameraZoomRequest(float zoomRatio) const
{
    TELEPHONY_LOGI("SetCameraZoomRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("SetCameraZoomRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateSetCameraZoomResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetPauseImageRequest(const std::u16string &path) const
{
    TELEPHONY_LOGI("SetPauseImageRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("SetPauseImageRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateSetPauseImageResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetDeviceDirectionRequest(int32_t rotation) const
{
    TELEPHONY_LOGI("SetDeviceDirectionRequest start");

    // This is the logic of piling. The result is temporarily returned to the caller, and the temporary logic
    // can be removed during subsequent development by the manufacturer.
    ImsResponseInfo responseInfo {};
    responseInfo.error = ImsErrType::IMS_SUCCESS;
    if (imsRegisterInstance_ == nullptr) {
        TELEPHONY_LOGE("SetDeviceDirectionRequest return, error type: instance is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    imsRegisterInstance_->UpdateSetDeviceDirectionResponse(responseInfo);
    return TELEPHONY_SUCCESS;
}

void ImsRilRequest::AsynchronousRegister()
{
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("AsynchronousRegister return, instance is nullptr.");
        return;
    }
    DelayedSingleton<ImsService>::GetInstance()->RegisterHandler();
}

int32_t ImsRilRequest::SetMuteRequest(int32_t slotId, int32_t mute) const
{
    TELEPHONY_LOGI("SetMuteRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetMuteRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("SetMuteRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().SetMute(slotId, RadioEvent::RADIO_SET_CMUT, mute, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::GetMuteRequest(int32_t slotId) const
{
    TELEPHONY_LOGI("GetMuteRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetMuteRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("GetMuteRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().GetMute(slotId, RadioEvent::RADIO_GET_CMUT, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::GetEmergencyCallListRequest(int32_t slotId) const
{
    TELEPHONY_LOGI("GetEmergencyCallListRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetEmergencyCallListRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("GetEmergencyCallListRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().GetEmergencyCallList(slotId, RadioEvent::RADIO_GET_EMERGENCY_CALL_LIST, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::GetCallFailReasonRequest(int32_t slotId) const
{
    TELEPHONY_LOGI("GetCallFailReasonRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetCallFailReasonRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("GetCallFailReasonRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().GetCallFailReason(slotId, RadioEvent::RADIO_GET_CALL_FAIL_REASON, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::InquireClipRequest(int32_t slotId) const
{
    TELEPHONY_LOGI("InquireClipRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("InquireClipRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("InquireClipRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().GetClip(slotId, RadioEvent::RADIO_GET_CALL_CLIP, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetClirRequest(int32_t slotId, int32_t action) const
{
    TELEPHONY_LOGI("SetClirRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetClirRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("SetClirRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().SetClir(slotId, RadioEvent::RADIO_SET_CALL_CLIR, action, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::InquireClirRequest(int32_t slotId) const
{
    TELEPHONY_LOGI("InquireClirRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("InquireClirRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("InquireClirRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().GetClir(slotId, RadioEvent::RADIO_GET_CALL_CLIR, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetCallTransferRequest(
    int32_t slotId, int32_t reason, int32_t mode, const std::string &transferNum, int32_t classType) const
{
    TELEPHONY_LOGI("SetCallTransferRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    CallTransferParam callTransferParam;
    callTransferParam.mode = mode;
    callTransferParam.classx = classType;
    callTransferParam.number = transferNum;
    callTransferParam.reason = reason;

    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetCallTransferRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("SetCallTransferRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().SetCallTransferInfo(
        slotId, RadioEvent::RADIO_SET_CALL_FORWARD, callTransferParam, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::GetCallTransferRequest(int32_t slotId, int32_t reason) const
{
    TELEPHONY_LOGI("GetCallTransferRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetCallTransferRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("GetCallTransferRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().GetCallTransferInfo(slotId, RadioEvent::RADIO_GET_CALL_FORWARD, reason, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetCallRestrictionRequest(
    int32_t slotId, const std::string &fac, int32_t mode, const std::string &pw) const
{
    TELEPHONY_LOGI("SetCallRestrictionRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    CallRestrictionParam callRestrictionParam;
    callRestrictionParam.mode = mode;
    callRestrictionParam.password = pw;
    callRestrictionParam.fac = fac;

    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetCallRestrictionRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("SetCallRestrictionRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    std::string facTemp = fac;
    std::string facPw = pw;
    CoreManagerInner::GetInstance().SetCallRestriction(
        slotId, RadioEvent::RADIO_SET_CALL_RESTRICTION, callRestrictionParam, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::GetCallRestrictionRequest(int32_t slotId, const std::string &fac) const
{
    TELEPHONY_LOGI("GetCallRestrictionRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetCallRestrictionRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("GetCallRestrictionRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    std::string facTemp = fac;
    CoreManagerInner::GetInstance().GetCallRestriction(
        slotId, RadioEvent::RADIO_GET_CALL_RESTRICTION, facTemp, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::SetCallWaitingRequest(int32_t slotId, bool activate) const
{
    TELEPHONY_LOGI("SetCallWaitingRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SetCallWaitingRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("SetCallWaitingRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().SetCallWaiting(slotId, RadioEvent::RADIO_SET_CALL_WAIT, activate, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilRequest::GetCallWaitingRequest(int32_t slotId) const
{
    TELEPHONY_LOGI("GetCallWaitingRequest start");

    // This is a sample call, the manufacturer can use this method when developing, or you can customize the call.
    if (DelayedSingleton<ImsService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetCallWaitingRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<ImsService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("GetCallWaitingRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().GetCallWaiting(slotId, RadioEvent::RADIO_GET_CALL_WAIT, handle);
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS
