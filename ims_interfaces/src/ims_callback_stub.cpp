/*
 * Copyright (C) 2021-2022 Huawei Device Co., Ltd.
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

#include "ims_callback_stub.h"

#include "cellular_call_register.h"
#include "cellular_call_service.h"
#include "radio_event.h"
#include "telephony_log_wrapper.h"
#include "telephony_errors.h"

namespace OHOS {
namespace Telephony {
ImsCallbackStub::ImsCallbackStub()
{
    TELEPHONY_LOGI("ImsCallbackStub");
    InitBasicCallFuncMap();
    InitSupportCallFuncMap();
}

void ImsCallbackStub::InitBasicCallFuncMap()
{
    requestFuncMap_[UPDATE_IMS_DIAL] = &ImsCallbackStub::OnUpdateDialResponseInner;
    requestFuncMap_[UPDATE_IMS_HANG_UP] = &ImsCallbackStub::OnUpdateHangUpResponseInner;
    requestFuncMap_[UPDATE_IMS_REJECT] = &ImsCallbackStub::OnUpdateRejectResponseInner;
    requestFuncMap_[UPDATE_IMS_ANSWER] = &ImsCallbackStub::OnUpdateAnswerResponseInner;
    requestFuncMap_[UPDATE_IMS_HOLD] = &ImsCallbackStub::OnUpdateHoldResponseInner;
    requestFuncMap_[UPDATE_IMS_UN_HOLD] = &ImsCallbackStub::OnUpdateUnHoldResponseInner;
    requestFuncMap_[UPDATE_IMS_SWITCH] = &ImsCallbackStub::OnUpdateSwitchResponseInner;
    requestFuncMap_[UPDATE_IMS_COMBINE_CONFERENCE] = &ImsCallbackStub::OnUpdateCombineConferenceResponseInner;
    requestFuncMap_[UPDATE_IMS_INVITE_TO_CONFERENCE] = &ImsCallbackStub::OnUpdateInviteToConferenceResponseInner;
    requestFuncMap_[UPDATE_IMS_KICK_OUT_CONFERENCE] = &ImsCallbackStub::OnUpdateKickOutFromConferenceResponseInner;
    requestFuncMap_[UPDATE_IMS_UPDATE_CALL_MEDIA_MODE] = &ImsCallbackStub::OnUpdateCallMediaModeResponseInner;
    requestFuncMap_[UPDATE_IMS_EMERGENCY_CALL] = &ImsCallbackStub::OnUpdateIsEmergencyNumberResponseInner;
    requestFuncMap_[UPDATE_IMS_START_DTMF] = &ImsCallbackStub::OnUpdateStartDtmfResponseInner;
    requestFuncMap_[UPDATE_IMS_SEND_DTMF] = &ImsCallbackStub::OnUpdateSendDtmfResponseInner;
    requestFuncMap_[UPDATE_IMS_STOP_DTMF] = &ImsCallbackStub::OnUpdateStopDtmfResponseInner;
    requestFuncMap_[UPDATE_START_RTT] = &ImsCallbackStub::OnUpdateStartRttResponseInner;
    requestFuncMap_[UPDATE_STOP_RTT] = &ImsCallbackStub::OnUpdateStopRttResponseInner;
    requestFuncMap_[UPDATE_IMS_CALL_STATUS] = &ImsCallbackStub::OnUpdateCallStatusResponseInner;
    requestFuncMap_[UPDATE_IMS_SERVICE_STATUS] = &ImsCallbackStub::OnUpdateServiceStatusResponseInner;
}

void ImsCallbackStub::InitSupportCallFuncMap()
{
    requestFuncMap_[UPDATE_IMS_SET_PRE_MODE] = &ImsCallbackStub::OnUpdateSetPreModeResponseInner;
    requestFuncMap_[UPDATE_IMS_GET_PRE_MODE] = &ImsCallbackStub::OnUpdateGetPreModeResponseInner;
    requestFuncMap_[UPDATE_IMS_SET_LTE_SWITCH] = &ImsCallbackStub::OnUpdateSetImsSwitchResponseInner;
    requestFuncMap_[UPDATE_IMS_GET_LTE_SWITCH] = &ImsCallbackStub::OnUpdateGetImsSwitchResponseInner;
    requestFuncMap_[UPDATE_IMS_GET_CALLS_DATA] = &ImsCallbackStub::OnUpdateImsCallsDataResponseInner;
    requestFuncMap_[UPDATE_SET_CONFIG] = &ImsCallbackStub::OnUpdateSetImsConfigResponseInner;
    requestFuncMap_[UPDATE_GET_CONFIG] = &ImsCallbackStub::OnUpdateGetImsConfigResponseInner;
    requestFuncMap_[UPDATE_SET_FEATURE] = &ImsCallbackStub::OnUpdateSetImsFeatureResponseInner;
    requestFuncMap_[UPDATE_GET_FEATURE] = &ImsCallbackStub::OnUpdateGetImsFeatureResponseInner;
    requestFuncMap_[UPDATE_SET_IMS_SWITCH_ENHANCE] = &ImsCallbackStub::OnUpdateSetImsSwitchEnhanceModeResponseInner;
    requestFuncMap_[UPDATE_GET_IMS_SWITCH_ENHANCE] = &ImsCallbackStub::OnUpdateGetImsSwitchEnhanceModeResponseInner;
    requestFuncMap_[UPDATE_CONTROL_CAMERA] = &ImsCallbackStub::OnUpdateCtrlCameraResponseInner;
    requestFuncMap_[UPDATE_SET_PREVIEW_WINDOW] = &ImsCallbackStub::OnUpdateSetPreviewWindowResponseInner;
    requestFuncMap_[UPDATE_SET_DISPLAY_WINDOW] = &ImsCallbackStub::OnUpdateSetDisplayWindowResponseInner;
    requestFuncMap_[UPDATE_SET_CAMERA_ZOOM] = &ImsCallbackStub::OnUpdateSetCameraZoomResponseInner;
    requestFuncMap_[UPDATE_SET_PAUSE_IMAGE] = &ImsCallbackStub::OnUpdateSetPauseImageResponseInner;
    requestFuncMap_[UPDATE_SET_DEVICE_DIRECTION] = &ImsCallbackStub::OnUpdateSetDeviceDirectionResponseInner;
    requestFuncMap_[UPDATE_SRVCC_STATE] = &ImsCallbackStub::OnUpdateSrvccStateReportInner;
    requestFuncMap_[UPDATE_VT_OR_WFC] = &ImsCallbackStub::OnUpdateVtWfcReportInner;
    requestFuncMap_[UPDATE_CALL_CRING] = &ImsCallbackStub::OnUpdateCallRingBackResponseInner;
    requestFuncMap_[UPDATE_SET_MUTE] = &ImsCallbackStub::OnUpdateSetMuteResponseInner;
    requestFuncMap_[UPDATE_GET_MUTE] = &ImsCallbackStub::OnUpdateGetMuteResponseInner;
    requestFuncMap_[UPDATE_GET_EMERGENCY_CALL_LIST] = &ImsCallbackStub::OnUpdateGetEccListResponseInner;
    requestFuncMap_[UPDATE_CALL_FAIL_REASON] = &ImsCallbackStub::OnUpdateCallFailReasonResponseInner;
    requestFuncMap_[UPDATE_GET_CALL_CLIP] = &ImsCallbackStub::OnUpdateGetClipResponseInner;
    requestFuncMap_[UPDATE_GET_CALL_CLIR] = &ImsCallbackStub::OnUpdateGetClirResponseInner;
    requestFuncMap_[UPDATE_SET_CALL_CLIR] = &ImsCallbackStub::OnUpdateSetClirResponseInner;
    requestFuncMap_[UPDATE_GET_CALL_FORWARD] = &ImsCallbackStub::OnUpdateGetCallTransferResponseInner;
    requestFuncMap_[UPDATE_SET_CALL_FORWARD] = &ImsCallbackStub::OnUpdateSetCallTransferResponseInner;
    requestFuncMap_[UPDATE_GET_CALL_RESTRICTION] = &ImsCallbackStub::OnUpdateGetCallRestrictionResponseInner;
    requestFuncMap_[UPDATE_SET_CALL_RESTRICTION] = &ImsCallbackStub::OnUpdateSetCallRestrictionResponseInner;
    requestFuncMap_[UPDATE_GET_CALL_WAIT] = &ImsCallbackStub::OnUpdateGetCallWaitingResponseInner;
    requestFuncMap_[UPDATE_SET_CALL_WAIT] = &ImsCallbackStub::OnUpdateSetCallWaitingResponseInner;
}

ImsCallbackStub::~ImsCallbackStub()
{
    requestFuncMap_.clear();
}

int32_t ImsCallbackStub::OnRemoteRequest(
    uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    std::u16string myDescriptor = ImsCallbackStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (myDescriptor != remoteDescriptor) {
        TELEPHONY_LOGE("OnRemoteRequest return, descriptor checked fail");
        return TELEPHONY_ERR_DESCRIPTOR_MISMATCH;
    }
    auto itFunc = requestFuncMap_.find(code);
    if (itFunc != requestFuncMap_.end()) {
        auto requestFunc = itFunc->second;
        if (requestFunc != nullptr) {
            return (this->*requestFunc)(data, reply);
        }
    }
    TELEPHONY_LOGI("ImsCallbackStub::OnRemoteRequest, default case, need check.");
    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

int32_t ImsCallbackStub::OnUpdateDialResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateDialResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateDialResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateDialResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateHangUpResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateHangUpResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateHangUpResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateHangUpResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateRejectResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateRejectResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateRejectResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateRejectResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateAnswerResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateAnswerResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateAnswerResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateAnswerResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateHoldResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateHoldResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateHoldResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateHoldResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateUnHoldResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateUnHoldResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateUnHoldResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateUnHoldResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSwitchResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSwitchResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateSwitchResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateSwitchResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateCombineConferenceResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateCombineConferenceResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateCombineConferenceResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateCombineConferenceResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateInviteToConferenceResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateInviteToConferenceResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateInviteToConferenceResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateInviteToConferenceResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateKickOutFromConferenceResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateKickOutFromConferenceResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateKickOutFromConferenceResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateKickOutFromConferenceResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateCallMediaModeResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateCallMediaModeResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateCallMediaModeResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateCallMediaModeResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateIsEmergencyNumberResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateIsEmergencyNumberResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGI("OnUpdateIsEmergencyNumberResponseInner, can not to get info.");
        bool value = data.ReadBool();
        reply.WriteInt32(UpdateIsEmergencyPhoneNumberResponse(value));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(UpdateIsEmergencyPhoneNumberResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateStartDtmfResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateStartDtmfResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateStartDtmfResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateStartDtmfResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSendDtmfResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSendDtmfResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateSendDtmfResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateSendDtmfResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateStopDtmfResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateStopDtmfResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateStopDtmfResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateStopDtmfResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateStartRttResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateStartRttResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateStartRttResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateStartRttResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateStopRttResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateStopRttResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateStopRttResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateStopRttResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateCallStatusResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateCallStatusResponseInner entry");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(UpdateCallStatusResponse(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateServiceStatusResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateServiceStatusResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (CallImsServiceStatus *)data.ReadRawData(sizeof(CallImsServiceStatus));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateServiceStatusResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateServiceStatusResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetPreModeResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetPreModeResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateSetPreModeResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateSetPreModeResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateGetPreModeResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateGetPreModeResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateGetPreModeResponseInner, info is nullptr.");
        int32_t slotId = data.ReadInt32();
        int32_t mode = data.ReadInt32();
        reply.WriteInt32(UpdateGetPreModeResponse(slotId, mode));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(UpdateGetPreModeResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetImsSwitchResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetImsSwitchResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateSetImsSwitchResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateSetImsSwitchResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateGetImsSwitchResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateGetImsSwitchResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateGetImsSwitchResponseInner, info is nullptr.");
        int32_t slotId = data.ReadInt32();
        int32_t active = data.ReadInt32();
        reply.WriteInt32(UpdateGetImsSwitchResponse(slotId, active));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(UpdateGetImsSwitchResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateImsCallsDataResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateImsCallsDataResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateImsCallsDataResponseInner, info is nullptr.");
        int32_t slotId = data.ReadInt32();
        auto callList = (CallInfoList *)data.ReadRawData(sizeof(CallInfoList));
        if (callList == nullptr) {
            TELEPHONY_LOGE("OnUpdateImsCallsDataResponseInner, callList is nullptr.");
            return TELEPHONY_ERR_ARGUMENT_INVALID;
        }
        reply.WriteInt32(UpdateImsCallsDataResponse(slotId, *callList));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(UpdateImsCallsDataResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetImsConfigResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetImsConfigResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateSetImsConfigResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateSetImsConfigResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateGetImsConfigResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateGetImsConfigResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateGetImsConfigResponseInner, info is nullptr.");
        int32_t value = data.ReadInt32();
        reply.WriteInt32(UpdateGetImsConfigResponse(value));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(UpdateGetImsConfigResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetImsFeatureResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetImsFeatureResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateSetImsFeatureResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateSetImsFeatureValueResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateGetImsFeatureResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateGetImsFeatureResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateGetImsFeatureResponseInner, info is nullptr.");
        int32_t value = data.ReadInt32();
        reply.WriteInt32(UpdateGetImsFeatureValueResponse(value));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(UpdateGetImsFeatureValueResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetImsSwitchEnhanceModeResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetImsSwitchEnhanceModeResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateSetImsSwitchEnhanceModeResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateSetImsSwitchEnhanceModeResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateGetImsSwitchEnhanceModeResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateGetImsSwitchEnhanceModeResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateGetImsSwitchEnhanceModeResponseInner, info is nullptr.");
        int32_t value = data.ReadInt32();
        reply.WriteInt32(UpdateGetImsSwitchEnhanceModeResponse(value));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(UpdateGetImsSwitchEnhanceModeResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateCtrlCameraResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateCtrlCameraResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateCtrlCameraResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateCtrlCameraResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetPreviewWindowResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetPreviewWindowResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateSetPreviewWindowResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateSetPreviewWindowResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetDisplayWindowResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetDisplayWindowResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateSetDisplayWindowResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateSetDisplayWindowResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetCameraZoomResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetCameraZoomResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateSetCameraZoomResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateSetCameraZoomResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetPauseImageResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetPauseImageResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateSetPauseImageResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateSetPauseImageResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetDeviceDirectionResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetDeviceDirectionResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateSetDeviceDirectionResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateSetDeviceDirectionResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSrvccStateReportInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSrvccStateReportInner entry");
    int32_t slotId = data.ReadInt32();
    auto srvccState = static_cast<SrvccState>(data.ReadInt32());
    reply.WriteInt32(UpdateSrvccStateReport(slotId, srvccState));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateVtWfcReportInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateVtWfcReportInner entry");
    int32_t slotId = data.ReadInt32();
    auto transferState = static_cast<TransferState>(data.ReadInt32());
    reply.WriteInt32(UpdateVtWfcReport(slotId, transferState));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetMuteResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetMuteResponseInner entry");
    auto info = (MuteControlResponse *)data.ReadRawData(sizeof(MuteControlResponse));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateSetMuteResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateSetMuteResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateGetMuteResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateGetMuteResponseInner entry");
    auto info = (MuteControlResponse *)data.ReadRawData(sizeof(MuteControlResponse));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateGetMuteResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateGetMuteResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateCallRingBackResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateCallRingBackResponseInner entry");
    auto info = (RingbackVoice *)data.ReadRawData(sizeof(RingbackVoice));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUpdateCallRingBackResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateCallRingBackResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateGetEccListResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateGetEccListResponseInner entry");
    auto list = (EmergencyInfoList *)data.ReadRawData(sizeof(EmergencyInfoList));
    if (list == nullptr) {
        TELEPHONY_LOGE("OnUpdateGetEccListResponseInner return, list is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateGetEccCallListResponse(*list));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateCallFailReasonResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateCallFailReasonResponseInner entry");
    int32_t reason = data.ReadInt32();
    reply.WriteInt32(UpdateCallFailReasonResponse(reason));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateGetClipResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateGetClipResponseInner entry");
    auto response = (ClipResponse *)data.ReadRawData(sizeof(ClipResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnUpdateGetClipResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateGetClipResponse(*response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateGetClirResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateGetClirResponseInner entry");
    auto response = (ClirResponse *)data.ReadRawData(sizeof(ClirResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnUpdateGetClirResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateGetClirResponse(*response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetClirResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetClirResponseInner entry");
    auto errType = static_cast<HRilErrType>(data.ReadInt32());
    reply.WriteInt32(UpdateSetClirResponse(errType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateGetCallTransferResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateGetCallTransferResponseInner entry");
    auto response = (CallTransferResponse *)data.ReadRawData(sizeof(CallTransferResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnUpdateGetCallTransferResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateGetCallTransferResponse(*response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetCallTransferResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetCallTransferResponseInner entry");
    auto errType = static_cast<HRilErrType>(data.ReadInt32());
    reply.WriteInt32(UpdateSetCallTransferResponse(errType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateGetCallRestrictionResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateGetCallRestrictionResponseInner entry");
    auto response = (CallRestrictionResponse *)data.ReadRawData(sizeof(CallRestrictionResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnUpdateGetCallRestrictionResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateGetCallRestrictionResponse(*response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetCallRestrictionResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetCallRestrictionResponseInner entry");
    auto errType = static_cast<HRilErrType>(data.ReadInt32());
    reply.WriteInt32(UpdateSetCallRestrictionResponse(errType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateGetCallWaitingResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateGetCallWaitingResponseInner entry");
    auto response = (CallWaitResponse *)data.ReadRawData(sizeof(CallWaitResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnUpdateGetCallWaitingResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UpdateGetCallWaitingResponse(*response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::OnUpdateSetCallWaitingResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallbackStub::OnUpdateSetCallWaitingResponseInner entry");
    auto errType = static_cast<HRilErrType>(data.ReadInt32());
    reply.WriteInt32(UpdateSetCallWaitingResponse(errType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateDialResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateDialResponse entry");
    if (info.error != ImsErrType::IMS_SUCCESS) {
        TELEPHONY_LOGI("UpdateDialResponse, dial return error, report to call_manager");
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
        eventInfo.eventId = RequestResultEventId::RESULT_DIAL_SEND_FAILED;

        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("UpdateDialResponse return, GetInstance is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateHangUpResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateHangUpResponse entry");
    if (info.error != ImsErrType::IMS_SUCCESS) {
        TELEPHONY_LOGI("UpdateHangUpResponse, HangUp return error, report to call_manager");
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
        eventInfo.eventId = RequestResultEventId::RESULT_END_SEND_FAILED;

        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("UpdateHangUpResponse return, GetInstance is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateRejectResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateRejectResponse entry");
    if (info.error != ImsErrType::IMS_SUCCESS) {
        TELEPHONY_LOGI("UpdateRejectResponse, return error, report to call_manager");
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
        eventInfo.eventId = RequestResultEventId::RESULT_REJECT_SEND_FAILED;

        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("UpdateRejectResponse return, GetInstance is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateAnswerResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateAnswerResponse entry");
    if (info.error != ImsErrType::IMS_SUCCESS) {
        TELEPHONY_LOGI("UpdateAnswerResponse, return error, report to call_manager");
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
        eventInfo.eventId = RequestResultEventId::RESULT_ACCEPT_SEND_FAILED;

        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("UpdateAnswerResponse return, GetInstance is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateHoldResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateHoldResponse entry");
    if (info.error != ImsErrType::IMS_SUCCESS) {
        TELEPHONY_LOGI("UpdateHoldResponse, return error, report to call_manager");
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
        eventInfo.eventId = RequestResultEventId::RESULT_HOLD_SEND_FAILED;

        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("UpdateHoldResponse return, GetInstance is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateUnHoldResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateUnHoldResponse entry");
    if (info.error != ImsErrType::IMS_SUCCESS) {
        TELEPHONY_LOGI("UpdateUnHoldResponse, return error, report to call_manager");
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
        eventInfo.eventId = RequestResultEventId::RESULT_ACTIVE_SEND_FAILED;

        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("UpdateUnHoldResponse return, GetInstance is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSwitchResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSwitchResponse entry");
    if (info.error != ImsErrType::IMS_SUCCESS) {
        TELEPHONY_LOGI("UpdateSwitchResponse, return error, report to call_manager");
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
        eventInfo.eventId = RequestResultEventId::RESULT_SWAP_SEND_FAILED;

        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("UpdateSwitchResponse return, GetInstance is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateCombineConferenceResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateCombineConferenceResponse entry");
    if (info.error != ImsErrType::IMS_SUCCESS) {
        TELEPHONY_LOGI("UpdateCombineConferenceResponse, return error, report to call_manager");
        CellularCallEventInfo eventInfo;
        eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
        eventInfo.eventId = RequestResultEventId::RESULT_JOIN_SEND_FAILED;

        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("UpdateCombineConferenceResponse return, GetInstance is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateInviteToConferenceResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateInviteToConferenceResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateInviteToConferenceResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportInviteToConferenceResult(info.error);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateKickOutFromConferenceResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateKickOutFromConferenceResponse entry");
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (info.error != ImsErrType::IMS_SUCCESS) {
        eventInfo.eventId = RequestResultEventId::RESULT_KICK_OUT_FROM_CONFERENCE_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_KICK_OUT_FROM_CONFERENCE_SUCCESS;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateKickOutFromConferenceResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateCallMediaModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateCallMediaModeResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateCallMediaModeResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportUpdateCallMediaModeResult(info.error);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateIsEmergencyPhoneNumberResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateIsEmergencyPhoneNumberResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateIsEmergencyPhoneNumberResponse(bool value)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateIsEmergencyPhoneNumberResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateStartDtmfResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateStartDtmfResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateStartDtmfResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportStartDtmfResult(static_cast<int32_t>(info.error));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSendDtmfResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSendDtmfResponse entry");
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (info.error != ImsErrType::IMS_SUCCESS) {
        eventInfo.eventId = RequestResultEventId::RESULT_SEND_DTMF_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_SEND_DTMF_SUCCESS;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSendDtmfResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateStopDtmfResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateStopDtmfResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateStopDtmfResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportStopDtmfResult(static_cast<int32_t>(info.error));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateStartRttResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateStartRttResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateStartRttResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportStartRttResult(info.error);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateStopRttResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateStopRttResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateStopRttResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportStopRttResult(info.error);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateCallStatusResponse(int32_t slotId)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateCallStatusResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateServiceStatusResponse(int32_t slotId, const CallImsServiceStatus &callImsServiceStatus)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateServiceStatusResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetPreModeResponse(int32_t slotId, const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetPreModeResponse entry");

    auto responseInfo = std::make_shared<HRilRadioResponseInfo>();
    if (responseInfo == nullptr) {
        TELEPHONY_LOGE("ImsCallbackStub::UpdateSetPreModeResponse, UpdateSetPreModeResponse == nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    responseInfo->error = static_cast<HRilErrType>(info.error);
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetPreModeResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId) == nullptr) {
        TELEPHONY_LOGE("UpdateSetPreModeResponse return, GetHandler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    auto event = AppExecFwk::InnerEvent::Get(RadioEvent::RADIO_SET_CALL_PREFERENCE_MODE, responseInfo);
    DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId)->SetDomainPreferenceModeResponse(event);

    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (info.error != ImsErrType::IMS_SUCCESS) {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_CALL_PREFERENCE_MODE_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_CALL_PREFERENCE_MODE_SUCCESS;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetPreModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetPreModeResponse entry");
    TELEPHONY_LOGI("UpdateGetPreModeResponse return ImsResponseInfo");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetPreModeResponse(int32_t slotId, int32_t mode)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetPreModeResponse entry mode:%{public}d", mode);
    std::shared_ptr<int32_t> preferenceMode = std::make_shared<int32_t>(mode);
    if (preferenceMode == nullptr) {
        TELEPHONY_LOGE("ImsCallbackStub::UpdateGetPreModeResponse, preferenceMode == nullptr !!!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateGetPreModeResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId) == nullptr) {
        TELEPHONY_LOGE("UpdateGetPreModeResponse return, GetHandler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    auto event = AppExecFwk::InnerEvent::Get(RadioEvent::RADIO_GET_CALL_PREFERENCE_MODE, preferenceMode);
    DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId)->GetDomainPreferenceModeResponse(event);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetImsSwitchResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetImsSwitchResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetImsSwitchResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetImsSwitchResult(info.error);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetImsSwitchResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetImsSwitchResponse entry");
    if (info.error != ImsErrType::IMS_SUCCESS) {
        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("UpdateGetImsSwitchResponse return, GetInstance is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        ImsSwitchResponse response;
        response.result = info.error;
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetImsSwitchResult(response);
    } else {
        TELEPHONY_LOGI("UpdateGetImsSwitchResponse, result error");
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetImsSwitchResponse(int32_t slotId, int32_t active)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetImsSwitchResponse entry active:%{public}d", active);
    // report to cellular call
    std::shared_ptr<int32_t> imsSwitch = std::make_shared<int32_t>(active);
    if (imsSwitch == nullptr) {
        TELEPHONY_LOGE("ImsCallbackStub::UpdateGetImsSwitchResponse, imsSwitch == nullptr !!!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId) == nullptr) {
        TELEPHONY_LOGE("UpdateGetImsSwitchResponse return, GetHandler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    auto event = AppExecFwk::InnerEvent::Get(RadioEvent::RADIO_GET_IMS_SWITCH_STATUS, imsSwitch);
    DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId)->GetImsSwitchStatusResponse(event);

    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateGetImsSwitchResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    ImsSwitchResponse response;
    response.result = IMS_SUCCESS;
    response.active = active;
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetImsSwitchResult(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateImsCallsDataResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateImsCallsDataResponse entry");
    if (info.error != ImsErrType::IMS_SUCCESS) {
        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("UpdateImsCallsDataResponse return, GetInstance is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        TELEPHONY_LOGI("UpdateImsCallsDataResponse, return error, report to call_manager");
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetCallDataResult(IMS_FAILED);
    } else {
        TELEPHONY_LOGI("UpdateImsCallsDataResponse, result error");
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateImsCallsDataResponse(int32_t slotId, const CallInfoList &callList)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateImsCallsDataResponse entry");
    std::shared_ptr<CallInfoList> callInfoList = std::make_shared<CallInfoList>(callList);
    if (callInfoList == nullptr) {
        TELEPHONY_LOGE("ImsCallbackStub::UpdateImsCallsDataResponse, callInfoList == nullptr !!!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    auto event = AppExecFwk::InnerEvent::Get(RadioEvent::RADIO_GET_IMS_CALL_LIST, callInfoList);
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateImsCallsDataResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId) == nullptr) {
        TELEPHONY_LOGE("UpdateImsCallsDataResponse return, GetHandler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId)->GetImsCallsDataResponse(event);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetImsConfigResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetImsConfigResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetImsConfigResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetImsConfigResult(info.error);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetImsConfigResponse(int32_t value)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetImsConfigResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateGetImsConfigResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    GetImsConfigResponse response;
    response.result = TELEPHONY_SUCCESS;
    response.value = value;
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetImsConfigResult(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetImsConfigResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetImsConfigResponse entry");
    if (info.error != ImsErrType::IMS_SUCCESS) {
        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("UpdateGetImsConfigResponse return, GetInstance is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        GetImsConfigResponse response;
        response.result = IMS_FAILED;
        TELEPHONY_LOGI("UpdateGetImsConfigResponse, return error, report to call_manager");
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetImsConfigResult(response);
    } else {
        TELEPHONY_LOGI("UpdateGetImsConfigResponse, result error");
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetImsFeatureValueResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetImsFeatureValueResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetImsFeatureValueResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetImsFeatureResult(info.error);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetImsFeatureValueResponse(int32_t value)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetImsFeatureValueResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateGetImsFeatureValueResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    GetImsFeatureValueResponse response;
    response.result = TELEPHONY_SUCCESS;
    response.value = value;
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetImsFeatureResult(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetImsFeatureValueResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetImsFeatureValueResponse entry");
    if (info.error != ImsErrType::IMS_SUCCESS) {
        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("UpdateGetImsFeatureValueResponse return, GetInstance is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        GetImsFeatureValueResponse response;
        response.result = IMS_FAILED;
        TELEPHONY_LOGI("UpdateGetImsFeatureValueResponse, return error, report to call_manager");
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetImsFeatureResult(response);
    } else {
        TELEPHONY_LOGI("UpdateGetImsFeatureValueResponse, result error");
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetImsSwitchEnhanceModeResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetImsSwitchEnhanceModeResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetImsSwitchEnhanceModeResult(info.error);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetImsSwitchEnhanceModeResponse(int32_t value)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetImsSwitchEnhanceModeResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateGetImsSwitchEnhanceModeResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    GetLteEnhanceModeResponse response;
    response.result = TELEPHONY_SUCCESS;
    response.value = value;
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetImsSwitchEnhanceModeResult(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetImsSwitchEnhanceModeResponse entry");
    if (info.error != ImsErrType::IMS_SUCCESS) {
        if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("UpdateGetImsSwitchEnhanceModeResponse return, GetInstance is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        GetLteEnhanceModeResponse response;
        response.result = IMS_FAILED;
        TELEPHONY_LOGI("UpdateGetImsSwitchEnhanceModeResponse, return error, report to call_manager");
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetImsSwitchEnhanceModeResult(response);
    } else {
        TELEPHONY_LOGI("UpdateGetImsSwitchEnhanceModeResponse, result error");
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateCtrlCameraResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateCtrlCameraResponse entry");
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (info.error != ImsErrType::IMS_SUCCESS) {
        eventInfo.eventId = RequestResultEventId::RESULT_CTRL_CAMERA_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_CTRL_CAMERA_SUCCESS;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateCtrlCameraResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetPreviewWindowResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetPreviewWindowResponse entry");
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (info.error != ImsErrType::IMS_SUCCESS) {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_PREVIEW_WINDOW_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_PREVIEW_WINDOW_SUCCESS;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetPreviewWindowResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetDisplayWindowResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetDisplayWindowResponse entry");
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (info.error != ImsErrType::IMS_SUCCESS) {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_DISPLAY_WINDOW_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_DISPLAY_WINDOW_SUCCESS;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetDisplayWindowResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetCameraZoomResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetCameraZoomResponse entry");
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (info.error != ImsErrType::IMS_SUCCESS) {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_CAMERA_ZOOM_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_CAMERA_ZOOM_SUCCESS;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetCameraZoomResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetPauseImageResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetPauseImageResponse entry");
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (info.error != ImsErrType::IMS_SUCCESS) {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_PAUSE_IMAGE_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_PAUSE_IMAGE_SUCCESS;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetPauseImageResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetDeviceDirectionResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetDeviceDirectionResponse entry");
    CellularCallEventInfo eventInfo;
    eventInfo.eventType = CellularCallEventType::EVENT_REQUEST_RESULT_TYPE;
    if (info.error != ImsErrType::IMS_SUCCESS) {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_DEVICE_DIRECTION_FAILED;
    } else {
        eventInfo.eventId = RequestResultEventId::RESULT_SET_DEVICE_DIRECTION_SUCCESS;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetDeviceDirectionResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportEventResultInfo(eventInfo);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSrvccStateReport(int32_t slotId, SrvccState srvccState)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSrvccStateReport entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateVtWfcReport(int32_t slotId, TransferState transferState)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateVtWfcReport entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetMuteResponse(const MuteControlResponse &response)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetMuteResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetMuteResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetMuteResult(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetMuteResponse(const MuteControlResponse &response)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetMuteResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateGetMuteResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetMuteResult(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetEccCallListResponse(const EmergencyInfoList &callList)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetEccCallListResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateCallRingBackResponse(const RingbackVoice &info)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateCallRingBackResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateCallRingBackResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    TELEPHONY_LOGI("UpdateCallRingBackResponse: report to call manager");
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportCallRingBackResult(info.status);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateCallFailReasonResponse(int32_t reason)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateCallFailReasonResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateCallFailReasonResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportCallFailReason(reason);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetClipResponse(const ClipResponse &response)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetClipResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateGetClipResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetClipResult(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetClirResponse(const ClirResponse &response)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetClirResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateGetClirResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetClirResult(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetClirResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetClirResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetClirResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetClirResult(static_cast<int32_t>(errType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetCallTransferResponse(const CallTransferResponse &response)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetCallTransferResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateGetCallTransferResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetTransferResult(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetCallTransferResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetCallTransferResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetCallTransferResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetTransferResult(static_cast<int32_t>(errType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetCallRestrictionResponse(const CallRestrictionResponse &response)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetCallRestrictionResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateGetCallRestrictionResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetRestrictionResult(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetCallRestrictionResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetCallRestrictionResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetCallRestrictionResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetRestrictionResult(static_cast<int32_t>(errType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateGetCallWaitingResponse(const CallWaitResponse &response)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateGetCallWaitingResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateGetCallWaitingResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetWaitingResult(response);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallbackStub::UpdateSetCallWaitingResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("ImsCallbackStub::UpdateSetCallWaitingResponse entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UpdateSetCallWaitingResponse return, GetInstance is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetWaitingResult(static_cast<int32_t>(errType));
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS
