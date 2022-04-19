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

#include "ims_call_callback_stub.h"

#include "cellular_call_register.h"
#include "cellular_call_service.h"
#include "telephony_log_wrapper.h"
#include "telephony_errors.h"
#include "radio_event.h"

namespace OHOS {
namespace Telephony {
ImsCallCallbackStub::ImsCallCallbackStub()
{
    TELEPHONY_LOGI("ImsCallCallbackStub");
    InitFuncMap();
}

void ImsCallCallbackStub::InitFuncMap()
{
    InitCallBasicFuncMap();
    InitConfigFuncMap();
    InitVedioFuncMap();
    InitSupplementFuncMap();
}

void ImsCallCallbackStub::InitCallBasicFuncMap()
{
    /****************** call basic ******************/
    requestFuncMap_[IMS_DIAL] = &ImsCallCallbackStub::OnDialResponseInner;
    requestFuncMap_[IMS_HANG_UP] = &ImsCallCallbackStub::OnHangUpResponseInner;
    requestFuncMap_[IMS_REJECT] = &ImsCallCallbackStub::OnRejectResponseInner;
    requestFuncMap_[IMS_ANSWER] = &ImsCallCallbackStub::OnAnswerResponseInner;
    requestFuncMap_[IMS_HOLD] = &ImsCallCallbackStub::OnHoldResponseInner;
    requestFuncMap_[IMS_UN_HOLD] = &ImsCallCallbackStub::OnUnHoldResponseInner;
    requestFuncMap_[IMS_SWITCH] = &ImsCallCallbackStub::OnSwitchResponseInner;
    requestFuncMap_[IMS_COMBINE_CONFERENCE] = &ImsCallCallbackStub::OnCombineConferenceResponseInner;
    requestFuncMap_[IMS_INVITE_TO_CONFERENCE] = &ImsCallCallbackStub::OnInviteToConferenceResponseInner;
    requestFuncMap_[IMS_KICK_OUT_CONFERENCE] = &ImsCallCallbackStub::OnKickOutFromConferenceResponseInner;
    requestFuncMap_[IMS_UPDATE_CALL_MEDIA_MODE] = &ImsCallCallbackStub::OnCallMediaModeResponseInner;
    requestFuncMap_[IMS_EMERGENCY_CALL] = &ImsCallCallbackStub::OnIsEmergencyNumberResponseInner;
    requestFuncMap_[IMS_CALL_STATE_CHANGE] = &ImsCallCallbackStub::OnCallStateChangeReportInner;
    requestFuncMap_[IMS_SERVICE_STATUS] = &ImsCallCallbackStub::OnServiceStatusResponseInner;
    requestFuncMap_[IMS_LAST_CALL_FAIL_REASON] = &ImsCallCallbackStub::OnLastCallFailReasonResponseInner;
    requestFuncMap_[IMS_SRVCC_STATE] = &ImsCallCallbackStub::OnSrvccStateReportInner;
    requestFuncMap_[IMS_VT_OR_WFC] = &ImsCallCallbackStub::OnVtWfcReportInner;
    requestFuncMap_[IMS_CALL_CRING] = &ImsCallCallbackStub::OnCallRingBackResponseInner;
}

void ImsCallCallbackStub::InitConfigFuncMap()
{
    /****************** dtmf、rtt ******************/
    requestFuncMap_[IMS_START_DTMF] = &ImsCallCallbackStub::OnStartDtmfResponseInner;
    requestFuncMap_[IMS_SEND_DTMF] = &ImsCallCallbackStub::OnSendDtmfResponseInner;
    requestFuncMap_[IMS_STOP_DTMF] = &ImsCallCallbackStub::OnStopDtmfResponseInner;
    requestFuncMap_[IMS_START_RTT] = &ImsCallCallbackStub::OnStartRttResponseInner;
    requestFuncMap_[IMS_STOP_RTT] = &ImsCallCallbackStub::OnStopRttResponseInner;

    /****************** ims config ******************/
    requestFuncMap_[IMS_SET_PRE_MODE] = &ImsCallCallbackStub::OnSetPreModeResponseInner;
    requestFuncMap_[IMS_GET_PRE_MODE] = &ImsCallCallbackStub::OnGetPreModeResponseInner;
    requestFuncMap_[IMS_SET_LTE_SWITCH_STATUS] = &ImsCallCallbackStub::OnSetImsSwitchResponseInner;
    requestFuncMap_[IMS_GET_LTE_SWITCH_STATUS] = &ImsCallCallbackStub::OnGetImsSwitchResponseInner;
    requestFuncMap_[IMS_GET_CALLS_DATA] = &ImsCallCallbackStub::OnImsCallsDataResponseInner;
    requestFuncMap_[IMS_SET_CONFIG] = &ImsCallCallbackStub::OnSetImsConfigResponseInner;
    requestFuncMap_[IMS_GET_CONFIG] = &ImsCallCallbackStub::OnGetImsConfigResponseInner;
    requestFuncMap_[IMS_SET_FEATURE] = &ImsCallCallbackStub::OnSetImsFeatureResponseInner;
    requestFuncMap_[IMS_GET_FEATURE] = &ImsCallCallbackStub::OnGetImsFeatureResponseInner;
    requestFuncMap_[IMS_SET_LTE_SWITCH_ENHANCE_MODE_STATUS] =
        &ImsCallCallbackStub::OnSetImsSwitchEnhanceModeResponseInner;
    requestFuncMap_[IMS_GET_LTE_SWITCH_ENHANCE_MODE_STATUS] =
        &ImsCallCallbackStub::OnGetImsSwitchEnhanceModeResponseInner;
    requestFuncMap_[IMS_SET_MUTE] = &ImsCallCallbackStub::OnSetMuteResponseInner;
    requestFuncMap_[IMS_GET_MUTE] = &ImsCallCallbackStub::OnGetMuteResponseInner;
    requestFuncMap_[IMS_GET_EMERGENCY_CALL_LIST] = &ImsCallCallbackStub::OnGetEccListResponseInner;
}

void ImsCallCallbackStub::InitVedioFuncMap()
{
    /****************** video settings ******************/
    requestFuncMap_[IMS_CONTROL_CAMERA] = &ImsCallCallbackStub::OnCtrlCameraResponseInner;
    requestFuncMap_[IMS_SET_PREVIEW_WINDOW] = &ImsCallCallbackStub::OnSetPreviewWindowResponseInner;
    requestFuncMap_[IMS_SET_DISPLAY_WINDOW] = &ImsCallCallbackStub::OnSetDisplayWindowResponseInner;
    requestFuncMap_[IMS_SET_CAMERA_ZOOM] = &ImsCallCallbackStub::OnSetCameraZoomResponseInner;
    requestFuncMap_[IMS_SET_PAUSE_IMAGE] = &ImsCallCallbackStub::OnSetPauseImageResponseInner;
    requestFuncMap_[IMS_SET_DEVICE_DIRECTION] = &ImsCallCallbackStub::OnSetDeviceDirectionResponseInner;
}

void ImsCallCallbackStub::InitSupplementFuncMap()
{
    /****************** supplement ******************/
    requestFuncMap_[IMS_GET_CALL_CLIP] = &ImsCallCallbackStub::OnGetClipResponseInner;
    requestFuncMap_[IMS_GET_CALL_CLIR] = &ImsCallCallbackStub::OnGetClirResponseInner;
    requestFuncMap_[IMS_SET_CALL_CLIR] = &ImsCallCallbackStub::OnSetClirResponseInner;
    requestFuncMap_[IMS_GET_CALL_FORWARD] = &ImsCallCallbackStub::OnGetCallTransferResponseInner;
    requestFuncMap_[IMS_SET_CALL_FORWARD] = &ImsCallCallbackStub::OnSetCallTransferResponseInner;
    requestFuncMap_[IMS_GET_CALL_RESTRICTION] = &ImsCallCallbackStub::OnGetCallRestrictionResponseInner;
    requestFuncMap_[IMS_SET_CALL_RESTRICTION] = &ImsCallCallbackStub::OnSetCallRestrictionResponseInner;
    requestFuncMap_[IMS_GET_CALL_WAIT] = &ImsCallCallbackStub::OnGetCallWaitingResponseInner;
    requestFuncMap_[IMS_SET_CALL_WAIT] = &ImsCallCallbackStub::OnSetCallWaitingResponseInner;
}

ImsCallCallbackStub::~ImsCallCallbackStub()
{
    requestFuncMap_.clear();
}

int32_t ImsCallCallbackStub::OnRemoteRequest(
    uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    std::u16string myDescriptor = ImsCallCallbackStub::GetDescriptor();
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
    TELEPHONY_LOGI("ImsCallCallbackStub::OnRemoteRequest, default case, need check.");
    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

int32_t ImsCallCallbackStub::OnDialResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnDialResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnDialResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(DialResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnHangUpResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnHangUpResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnHangUpResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(HangUpResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnRejectResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnRejectResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnRejectResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(RejectResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnAnswerResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnAnswerResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnAnswerResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(AnswerResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnHoldResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnHoldResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnHoldResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(HoldResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnUnHoldResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnUnHoldResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUnHoldResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UnHoldResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSwitchResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSwitchResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSwitchResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SwitchResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnCombineConferenceResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnCombineConferenceResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnCombineConferenceResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(CombineConferenceResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnInviteToConferenceResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnInviteToConferenceResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnInviteToConferenceResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(InviteToConferenceResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnKickOutFromConferenceResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnKickOutFromConferenceResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnKickOutFromConferenceResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(KickOutFromConferenceResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnCallMediaModeResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnCallMediaModeResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnCallMediaModeResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(CallMediaModeResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnIsEmergencyNumberResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnIsEmergencyNumberResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGI("OnIsEmergencyNumberResponseInner, can not to get info.");
        bool value = data.ReadBool();
        reply.WriteInt32(IsEmergencyPhoneNumberResponse(value));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(IsEmergencyPhoneNumberResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnStartDtmfResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnStartDtmfResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnStartDtmfResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(StartDtmfResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSendDtmfResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSendDtmfResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSendDtmfResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SendDtmfResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnStopDtmfResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnStopDtmfResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnStopDtmfResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(StopDtmfResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnStartRttResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnStartRttResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnStartRttResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(StartRttResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnStopRttResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnStopRttResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnStopRttResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(StopRttResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnCallStateChangeReportInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnCallStateChangeReportInner entry");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(CallStateChangeReport(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnServiceStatusResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnServiceStatusResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (CallImsServiceStatus *)data.ReadRawData(sizeof(CallImsServiceStatus));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnServiceStatusResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(ServiceStatusResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetPreModeResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetPreModeResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetPreModeResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetPreModeResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetPreModeResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetPreModeResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetPreModeResponseInner, info is nullptr.");
        int32_t slotId = data.ReadInt32();
        int32_t mode = data.ReadInt32();
        reply.WriteInt32(GetPreModeResponse(slotId, mode));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(GetPreModeResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetImsSwitchResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetImsSwitchResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetImsSwitchResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetImsSwitchResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetImsSwitchResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetImsSwitchResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetImsSwitchResponseInner, info is nullptr.");
        int32_t slotId = data.ReadInt32();
        int32_t active = data.ReadInt32();
        reply.WriteInt32(GetImsSwitchResponse(slotId, active));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(GetImsSwitchResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnImsCallsDataResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnImsCallsDataResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnImsCallsDataResponseInner, info is nullptr.");
        int32_t slotId = data.ReadInt32();
        auto callList = (ImsCurrentCallList *)data.ReadRawData(sizeof(ImsCurrentCallList));
        if (callList == nullptr) {
            TELEPHONY_LOGE("OnImsCallsDataResponseInner, callList is nullptr.");
            return TELEPHONY_ERR_ARGUMENT_INVALID;
        }
        reply.WriteInt32(ImsCallsDataResponse(slotId, *callList));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(ImsCallsDataResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetImsConfigResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetImsConfigResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetImsConfigResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetImsConfigResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetImsConfigResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetImsConfigResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetImsConfigResponseInner, info is nullptr.");
        int32_t value = data.ReadInt32();
        reply.WriteInt32(GetImsConfigResponse(value));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(GetImsConfigResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetImsFeatureResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetImsFeatureResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetImsFeatureResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetImsFeatureValueResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetImsFeatureResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetImsFeatureResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetImsFeatureResponseInner, info is nullptr.");
        int32_t value = data.ReadInt32();
        reply.WriteInt32(GetImsFeatureValueResponse(value));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(GetImsFeatureValueResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetImsSwitchEnhanceModeResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetImsSwitchEnhanceModeResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetImsSwitchEnhanceModeResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetImsSwitchEnhanceModeResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetImsSwitchEnhanceModeResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetImsSwitchEnhanceModeResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetImsSwitchEnhanceModeResponseInner, info is nullptr.");
        int32_t value = data.ReadInt32();
        reply.WriteInt32(GetImsSwitchEnhanceModeResponse(value));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(GetImsSwitchEnhanceModeResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnCtrlCameraResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnCtrlCameraResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnCtrlCameraResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(CtrlCameraResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetPreviewWindowResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetPreviewWindowResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetPreviewWindowResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetPreviewWindowResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetDisplayWindowResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetDisplayWindowResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetDisplayWindowResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetDisplayWindowResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetCameraZoomResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetCameraZoomResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetCameraZoomResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetCameraZoomResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetPauseImageResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetPauseImageResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetPauseImageResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetPauseImageResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetDeviceDirectionResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetDeviceDirectionResponseInner entry");
    auto info = (ImsResponseInfo *)data.ReadRawData(sizeof(ImsResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetDeviceDirectionResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetDeviceDirectionResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSrvccStateReportInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSrvccStateReportInner entry");
    int32_t slotId = data.ReadInt32();
    auto srvccState = static_cast<SrvccState>(data.ReadInt32());
    reply.WriteInt32(SrvccStateReport(slotId, srvccState));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnVtWfcReportInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnVtWfcReportInner entry");
    int32_t slotId = data.ReadInt32();
    auto transferState = static_cast<TransferState>(data.ReadInt32());
    reply.WriteInt32(VtWfcReport(slotId, transferState));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetMuteResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetMuteResponseInner entry");
    auto info = (MuteControlResponse *)data.ReadRawData(sizeof(MuteControlResponse));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetMuteResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetMuteResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetMuteResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetMuteResponseInner entry");
    auto info = (MuteControlResponse *)data.ReadRawData(sizeof(MuteControlResponse));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetMuteResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetMuteResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnCallRingBackResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnCallRingBackResponseInner entry");
    auto info = (RingbackVoice *)data.ReadRawData(sizeof(RingbackVoice));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnCallRingBackResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(CallRingBackResponse(*info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetEccListResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetEccListResponseInner entry");
    auto list = (EmergencyInfoList *)data.ReadRawData(sizeof(EmergencyInfoList));
    if (list == nullptr) {
        TELEPHONY_LOGE("OnGetEccListResponseInner return, list is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetEccCallListResponse(*list));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnLastCallFailReasonResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnLastCallFailReasonResponseInner entry");
    int32_t reason = data.ReadInt32();
    reply.WriteInt32(LastCallFailReasonResponse(reason));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetClipResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetClipResponseInner entry");
    auto response = (ClipResponse *)data.ReadRawData(sizeof(ClipResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnGetClipResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetClipResponse(*response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetClirResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetClirResponseInner entry");
    auto response = (ClirResponse *)data.ReadRawData(sizeof(ClirResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnGetClirResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetClirResponse(*response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetClirResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetClirResponseInner entry");
    auto errType = static_cast<HRilErrType>(data.ReadInt32());
    reply.WriteInt32(SetClirResponse(errType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetCallTransferResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetCallTransferResponseInner entry");
    auto response = (CallTransferResponse *)data.ReadRawData(sizeof(CallTransferResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnGetCallTransferResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetCallTransferResponse(*response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetCallTransferResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetCallTransferResponseInner entry");
    auto errType = static_cast<HRilErrType>(data.ReadInt32());
    reply.WriteInt32(SetCallTransferResponse(errType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetCallRestrictionResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetCallRestrictionResponseInner entry");
    auto response = (CallRestrictionResponse *)data.ReadRawData(sizeof(CallRestrictionResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnGetCallRestrictionResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetCallRestrictionResponse(*response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetCallRestrictionResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetCallRestrictionResponseInner entry");
    auto errType = static_cast<HRilErrType>(data.ReadInt32());
    reply.WriteInt32(SetCallRestrictionResponse(errType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetCallWaitingResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetCallWaitingResponseInner entry");
    auto response = (CallWaitResponse *)data.ReadRawData(sizeof(CallWaitResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnGetCallWaitingResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetCallWaitingResponse(*response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetCallWaitingResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetCallWaitingResponseInner entry");
    auto errType = static_cast<HRilErrType>(data.ReadInt32());
    reply.WriteInt32(SetCallWaitingResponse(errType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::DialResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::DialResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::HangUpResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::HangUpResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::RejectResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::RejectResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::AnswerResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::AnswerResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::HoldResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::HoldResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::UnHoldResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::UnHoldResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SwitchResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SwitchResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::CombineConferenceResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::CombineConferenceResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::InviteToConferenceResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::InviteToConferenceResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::KickOutFromConferenceResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::KickOutFromConferenceResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::CallMediaModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::CallMediaModeResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::IsEmergencyPhoneNumberResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::IsEmergencyPhoneNumberResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::IsEmergencyPhoneNumberResponse(bool value)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::IsEmergencyPhoneNumberResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::StartDtmfResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::StartDtmfResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SendDtmfResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SendDtmfResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::StopDtmfResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::StopDtmfResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::StartRttResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::StartRttResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::StopRttResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::StopRttResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::CallStateChangeReport(int32_t slotId)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::CallStateChangeReport entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::ServiceStatusResponse(int32_t slotId, const CallImsServiceStatus &callImsServiceStatus)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::ServiceStatusResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetPreModeResponse(int32_t slotId, const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetPreModeResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetPreModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetPreModeResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetPreModeResponse(int32_t slotId, int32_t mode)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetPreModeResponse entry mode:%{public}d", mode);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetImsSwitchResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetImsSwitchResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetImsSwitchResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsSwitchResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetImsSwitchResponse(int32_t slotId, int32_t active)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsSwitchResponse entry active:%{public}d", active);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::ImsCallsDataResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::ImsCallsDataResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::ImsCallsDataResponse(int32_t slotId, const ImsCurrentCallList &callList)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::ImsCallsDataResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetImsConfigResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetImsConfigResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetImsConfigResponse(int32_t value)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsConfigResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetImsConfigResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsConfigResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetImsFeatureValueResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetImsFeatureValueResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetImsFeatureValueResponse(int32_t value)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsFeatureValueResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetImsFeatureValueResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsFeatureValueResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetImsSwitchEnhanceModeResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetImsSwitchEnhanceModeResponse(int32_t value)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsSwitchEnhanceModeResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsSwitchEnhanceModeResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::CtrlCameraResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::CtrlCameraResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetPreviewWindowResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetPreviewWindowResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetDisplayWindowResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetDisplayWindowResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetCameraZoomResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetCameraZoomResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetPauseImageResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetPauseImageResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetDeviceDirectionResponse(const ImsResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetDeviceDirectionResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SrvccStateReport(int32_t slotId, SrvccState srvccState)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SrvccStateReport entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::VtWfcReport(int32_t slotId, TransferState transferState)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::VtWfcReport entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetMuteResponse(const MuteControlResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetMuteResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetMuteResponse(const MuteControlResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetMuteResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetEccCallListResponse(const EmergencyInfoList &callList)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetEccCallListResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::CallRingBackResponse(const RingbackVoice &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::CallRingBackResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::LastCallFailReasonResponse(int32_t reason)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::LastCallFailReasonResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetClipResponse(const ClipResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetClipResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetClirResponse(const ClirResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetClirResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetClirResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetClirResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetCallTransferResponse(const CallTransferResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetCallTransferResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetCallTransferResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetCallTransferResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetCallRestrictionResponse(const CallRestrictionResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetCallRestrictionResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetCallRestrictionResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetCallRestrictionResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetCallWaitingResponse(const CallWaitResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetCallWaitingResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetCallWaitingResponse(HRilErrType errType)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetCallWaitingResponse entry");
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS
