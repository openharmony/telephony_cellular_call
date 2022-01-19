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

#include "ims_register.h"
#include "telephony_errors.h"

namespace OHOS {
namespace Telephony {
ImsRegister::ImsRegister() : cellularCallBack_(nullptr) {}
ImsRegister::~ImsRegister() = default;
int32_t ImsRegister::RegisterCellularCallBack(const sptr<ImsCallback> &callback)
{
    cellularCallBack_ = callback;
    return TELEPHONY_SUCCESS;
}

bool ImsRegister::IsCallBackExists()
{
    return cellularCallBack_ != nullptr;
}

int32_t ImsRegister::UpdateDialResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateDialResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateDialResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateDialResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateHangUpResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateHangUpResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateHangUpResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateHangUpResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateRejectResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateRejectResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateRejectResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateRejectResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateAnswerResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateAnswerResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateAnswerResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateAnswerResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateHoldResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateHoldResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateHoldResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateHoldResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateUnHoldResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateUnHoldResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateUnHoldResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateUnHoldResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSwitchResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateSwitchResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSwitchResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSwitchResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateCombineConferenceResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateCombineConferenceResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateCombineConferenceResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateCombineConferenceResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateInviteToConferenceResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateInviteToConferenceResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateInviteToConferenceResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateInviteToConferenceResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateKickOutFromConferenceResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateKickOutFromConferenceResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateKickOutFromConferenceResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateKickOutFromConferenceResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateCallMediaModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateCallMediaModeResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateCallMediaModeResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateCallMediaModeResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateIsEmergencyPhoneNumberResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateIsEmergencyPhoneNumberResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateIsEmergencyPhoneNumberResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateIsEmergencyPhoneNumberResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateIsEmergencyPhoneNumberResponse(bool value)
{
    TELEPHONY_LOGI("UpdateIsEmergencyPhoneNumberResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateIsEmergencyPhoneNumberResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateIsEmergencyPhoneNumberResponse(value);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateStartDtmfResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateStartDtmfResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateStartDtmfResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateStartDtmfResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSendDtmfResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateSendDtmfResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSendDtmfResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSendDtmfResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateStopDtmfResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateStopDtmfResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateStopDtmfResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateStopDtmfResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateStartRttResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateStartRttResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateStartRttResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateStartRttResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateStopRttResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateStopRttResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateStopRttResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateStopRttResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateCallWaitingResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateCallWaitingResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateCallWaitingResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateCallWaitingResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateCallConnectResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateCallConnectResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateCallConnectResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateCallConnectResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateCallEndResponse(int32_t slotId, const CallEndInfo &callEndInfo)
{
    TELEPHONY_LOGI("UpdateCallEndResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateCallEndResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateCallEndResponse(slotId, callEndInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateCallStatusResponse(int32_t slotId, const CallStatusInfo &callStatusInfo)
{
    TELEPHONY_LOGI("UpdateCallStatusResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateCallStatusResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateCallStatusResponse(slotId, callStatusInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateServiceStatusResponse(int32_t slotId, const CallImsServiceStatus &callImsServiceStatus)
{
    TELEPHONY_LOGI("UpdateServiceStatusResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateServiceStatusResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateServiceStatusResponse(slotId, callImsServiceStatus);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetPreModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateSetPreModeResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetPreModeResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetPreModeResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetPreModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateGetPreModeResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetPreModeResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetPreModeResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetPreModeResponse(int32_t slotId, int32_t mode)
{
    TELEPHONY_LOGI("UpdateGetPreModeResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetPreModeResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetPreModeResponse(slotId, mode);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetImsSwitchResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateSetImsSwitchResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetImsSwitchResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetImsSwitchResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetImsSwitchResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateGetImsSwitchResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetImsSwitchResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetImsSwitchResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetImsSwitchResponse(int32_t slotId, int32_t active)
{
    TELEPHONY_LOGI("UpdateGetImsSwitchResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetImsSwitchResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetImsSwitchResponse(slotId, active);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateImsCallsDataResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateImsCallsDataResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateImsCallsDataResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateImsCallsDataResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateImsCallsDataResponse(int32_t slotId, const CallInfoList &callList)
{
    TELEPHONY_LOGI("UpdateImsCallsDataResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateImsCallsDataResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateImsCallsDataResponse(slotId, callList);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetImsConfigResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateSetImsConfigResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetImsConfigResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetImsConfigResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetImsConfigResponse(int32_t value)
{
    TELEPHONY_LOGI("UpdateGetImsConfigResponse int entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetImsConfigResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetImsConfigResponse(value);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetImsConfigResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateGetImsConfigResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetImsConfigResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetImsConfigResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetImsFeatureValueResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateSetImsFeatureValueResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetImsFeatureValueResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetImsFeatureValueResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetImsFeatureValueResponse(int32_t value)
{
    TELEPHONY_LOGI("UpdateGetImsFeatureValueResponse int entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetImsFeatureValueResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetImsFeatureValueResponse(value);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetImsFeatureValueResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateGetImsFeatureValueResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetImsFeatureValueResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetImsFeatureValueResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateSetImsSwitchEnhanceModeResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetImsSwitchEnhanceModeResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetImsSwitchEnhanceModeResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetImsSwitchEnhanceModeResponse(int32_t value)
{
    TELEPHONY_LOGI("UpdateGetImsSwitchEnhanceModeResponse int entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetImsSwitchEnhanceModeResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetImsSwitchEnhanceModeResponse(value);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateGetImsSwitchEnhanceModeResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetImsSwitchEnhanceModeResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetImsSwitchEnhanceModeResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateCtrlCameraResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateCtrlCameraResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateCtrlCameraResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateCtrlCameraResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetPreviewWindowResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateSetPreviewWindowResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetPreviewWindowResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetPreviewWindowResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetDisplayWindowResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateSetDisplayWindowResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetDisplayWindowResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetDisplayWindowResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetCameraZoomResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateSetCameraZoomResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetCameraZoomResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetCameraZoomResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetPauseImageResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateSetPauseImageResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetPauseImageResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetPauseImageResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetDeviceDirectionResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("UpdateSetDeviceDirectionResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetDeviceDirectionResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetDeviceDirectionResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateCallRingBackResponse(const RingbackVoice &info)
{
    TELEPHONY_LOGI("UpdateCallRingBackResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateCallRingBackResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateCallRingBackResponse(info);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetMuteResponse(const MuteControlResponse &response)
{
    TELEPHONY_LOGI("UpdateSetMuteResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetMuteResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetMuteResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetMuteResponse(const MuteControlResponse &response)
{
    TELEPHONY_LOGI("UpdateGetMuteResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetMuteResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetMuteResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetEccCallListResponse(const EmergencyInfoList &callList)
{
    TELEPHONY_LOGI("UpdateGetEccCallListResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetEccCallListResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetEccCallListResponse(callList);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateCallFailReasonResponse(int32_t reason)
{
    TELEPHONY_LOGI("UpdateCallFailReasonResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateCallFailReasonResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateCallFailReasonResponse(reason);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetClipResponse(const ClipResponse &response)
{
    TELEPHONY_LOGI("UpdateGetClipResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetClipResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetClipResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetClirResponse(const ClirResponse &response)
{
    TELEPHONY_LOGI("UpdateGetClirResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetClirResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetClirResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetClirResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("UpdateSetClirResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetClirResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetClirResponse(errType);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetCallTransferResponse(const CallTransferResponse &response)
{
    TELEPHONY_LOGI("UpdateGetCallTransferResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetCallTransferResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetCallTransferResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetCallTransferResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("UpdateSetCallTransferResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetCallTransferResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetCallTransferResponse(errType);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetCallRestrictionResponse(const CallRestrictionResponse &response)
{
    TELEPHONY_LOGI("UpdateGetCallRestrictionResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetCallRestrictionResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetCallRestrictionResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetCallRestrictionResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("UpdateSetCallRestrictionResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetCallRestrictionResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetCallRestrictionResponse(errType);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateGetCallWaitingResponse(const CallWaitResponse &response)
{
    TELEPHONY_LOGI("UpdateGetCallWaitingResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateGetCallWaitingResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateGetCallWaitingResponse(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsRegister::UpdateSetCallWaitingResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("UpdateSetCallWaitingResponse entry");
    if (cellularCallBack_ == nullptr) {
        TELEPHONY_LOGE("UpdateSetCallWaitingResponse return, cellularCallBack_ is nullptr, report fail!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    cellularCallBack_->UpdateSetCallWaitingResponse(errType);
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS