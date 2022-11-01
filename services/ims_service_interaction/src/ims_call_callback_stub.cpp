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
#include "ims_call_client.h"
#include "radio_event.h"
#include "telephony_errors.h"
#include "telephony_log_wrapper.h"

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
    requestFuncMap_[ImsCallCallbackInterface::IMS_DIAL] = &ImsCallCallbackStub::OnDialResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_HANG_UP] = &ImsCallCallbackStub::OnHangUpResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_REJECT] = &ImsCallCallbackStub::OnRejectResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_ANSWER] = &ImsCallCallbackStub::OnAnswerResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_HOLD] = &ImsCallCallbackStub::OnHoldCallResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_UN_HOLD] = &ImsCallCallbackStub::OnUnHoldCallResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SWITCH] = &ImsCallCallbackStub::OnSwitchCallResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_COMBINE_CONFERENCE] =
        &ImsCallCallbackStub::OnCombineConferenceResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_INVITE_TO_CONFERENCE] =
        &ImsCallCallbackStub::OnInviteToConferenceResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_KICK_OUT_CONFERENCE] =
        &ImsCallCallbackStub::OnKickOutFromConferenceResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_UPDATE_CALL_MEDIA_MODE] =
        &ImsCallCallbackStub::OnCallMediaModeResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_CALL_STATE_CHANGE] =
        &ImsCallCallbackStub::OnCallStateChangeReportInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_LAST_CALL_FAIL_REASON] =
        &ImsCallCallbackStub::OnLastCallFailReasonResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SRVCC_STATE] = &ImsCallCallbackStub::OnSrvccStateReportInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_VT_OR_WFC] = &ImsCallCallbackStub::OnVtWfcReportInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_CALL_CRING] = &ImsCallCallbackStub::OnCallRingBackReportInner;
}

void ImsCallCallbackStub::InitConfigFuncMap()
{
    /****************** dtmf rtt ******************/
    requestFuncMap_[ImsCallCallbackInterface::IMS_START_DTMF] = &ImsCallCallbackStub::OnStartDtmfResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SEND_DTMF] = &ImsCallCallbackStub::OnSendDtmfResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_STOP_DTMF] = &ImsCallCallbackStub::OnStopDtmfResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_START_RTT] = &ImsCallCallbackStub::OnStartRttResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_STOP_RTT] = &ImsCallCallbackStub::OnStopRttResponseInner;

    /****************** ims config ******************/
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_PRE_MODE] = &ImsCallCallbackStub::OnSetPreModeResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_GET_PRE_MODE] = &ImsCallCallbackStub::OnGetPreModeResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_SWITCH_STATUS] =
        &ImsCallCallbackStub::OnSetImsSwitchResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_GET_SWITCH_STATUS] =
        &ImsCallCallbackStub::OnGetImsSwitchResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_GET_CALLS_DATA] =
        &ImsCallCallbackStub::OnGetImsCallsDataResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_CONFIG] = &ImsCallCallbackStub::OnSetImsConfigResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_GET_CONFIG] = &ImsCallCallbackStub::OnGetImsConfigResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_FEATURE] = &ImsCallCallbackStub::OnSetImsFeatureResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_GET_FEATURE] = &ImsCallCallbackStub::OnGetImsFeatureResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_MUTE] = &ImsCallCallbackStub::OnSetMuteResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_GET_MUTE] = &ImsCallCallbackStub::OnGetMuteResponseInner;
}

void ImsCallCallbackStub::InitVedioFuncMap()
{
    /****************** video settings ******************/
    requestFuncMap_[ImsCallCallbackInterface::IMS_CONTROL_CAMERA] = &ImsCallCallbackStub::OnCtrlCameraResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_PREVIEW_WINDOW] =
        &ImsCallCallbackStub::OnSetPreviewWindowResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_DISPLAY_WINDOW] =
        &ImsCallCallbackStub::OnSetDisplayWindowResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_CAMERA_ZOOM] = &ImsCallCallbackStub::OnSetCameraZoomResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_PAUSE_IMAGE] = &ImsCallCallbackStub::OnSetPauseImageResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_DEVICE_DIRECTION] =
        &ImsCallCallbackStub::OnSetDeviceDirectionResponseInner;
}

void ImsCallCallbackStub::InitSupplementFuncMap()
{
    /****************** supplement ******************/
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_CALL_CLIP] = &ImsCallCallbackStub::OnSetClipResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_GET_CALL_CLIP] = &ImsCallCallbackStub::OnGetClipResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_GET_CALL_CLIR] = &ImsCallCallbackStub::OnGetClirResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_CALL_CLIR] = &ImsCallCallbackStub::OnSetClirResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_GET_CALL_FORWARD] =
        &ImsCallCallbackStub::OnGetCallTransferResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_CALL_FORWARD] =
        &ImsCallCallbackStub::OnSetCallTransferResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_GET_CALL_RESTRICTION] =
        &ImsCallCallbackStub::OnGetCallRestrictionResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_CALL_RESTRICTION] =
        &ImsCallCallbackStub::OnSetCallRestrictionResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_GET_CALL_WAIT] = &ImsCallCallbackStub::OnGetCallWaitingResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_CALL_WAIT] = &ImsCallCallbackStub::OnSetCallWaitingResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_GET_CALL_COLR] = &ImsCallCallbackStub::OnGetColrResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_CALL_COLR] = &ImsCallCallbackStub::OnSetColrResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_SET_CALL_COLP] = &ImsCallCallbackStub::OnSetColpResponseInner;
    requestFuncMap_[ImsCallCallbackInterface::IMS_GET_CALL_COLP] = &ImsCallCallbackStub::OnGetColpResponseInner;
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
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnDialResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(DialResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnHangUpResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnHangUpResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnHangUpResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(HangUpResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnRejectResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnRejectResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnRejectResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(RejectWithReasonResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnAnswerResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnAnswerResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnAnswerResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(AnswerResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnHoldCallResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnHoldCallResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnHoldCallResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(HoldCallResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnUnHoldCallResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnUnHoldCallResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnUnHoldCallResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(UnHoldCallResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSwitchCallResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSwitchCallResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSwitchCallResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SwitchCallResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnCombineConferenceResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnCombineConferenceResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnCombineConferenceResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(CombineConferenceResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnInviteToConferenceResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnInviteToConferenceResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnInviteToConferenceResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(InviteToConferenceResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnKickOutFromConferenceResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnKickOutFromConferenceResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnKickOutFromConferenceResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(KickOutFromConferenceResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnCallMediaModeResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnCallMediaModeResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnCallMediaModeResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(CallMediaModeResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnStartDtmfResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnStartDtmfResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnStartDtmfResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(StartDtmfResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSendDtmfResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSendDtmfResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSendDtmfResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SendDtmfResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnStopDtmfResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnStopDtmfResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnStopDtmfResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(StopDtmfResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnStartRttResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnStartRttResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnStartRttResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(StartRttResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnStopRttResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnStopRttResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnStopRttResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(StopRttResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnCallStateChangeReportInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnCallStateChangeReportInner entry");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(CallStateChangeReport(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetPreModeResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetPreModeResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
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
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetPreModeResponseInner, info is nullptr.");
        int32_t mode = data.ReadInt32();
        reply.WriteInt32(GetPreModeResponse(slotId, mode));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(GetPreModeResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetImsSwitchResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetImsSwitchResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetImsSwitchResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetImsSwitchResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetImsSwitchResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetImsSwitchResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetImsSwitchResponseInner, info is nullptr.");
        int32_t active = data.ReadInt32();
        reply.WriteInt32(GetImsSwitchResponse(slotId, active));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(GetImsSwitchResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetImsCallsDataResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetImsCallsDataResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetImsCallsDataResponseInner, info is nullptr.");
        auto callList = (ImsCurrentCallList *)data.ReadRawData(sizeof(ImsCurrentCallList));
        if (callList == nullptr) {
            TELEPHONY_LOGE("OnGetImsCallsDataResponseInner, callList is nullptr.");
            return TELEPHONY_ERR_ARGUMENT_INVALID;
        }
        reply.WriteInt32(GetImsCallsDataResponse(slotId, *callList));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(GetImsCallsDataResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetImsConfigResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetImsConfigResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetImsConfigResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetImsConfigResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetImsConfigResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetImsConfigResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetImsConfigResponseInner, info is nullptr.");
        int32_t value = data.ReadInt32();
        reply.WriteInt32(GetImsConfigResponse(slotId, value));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(GetImsConfigResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetImsFeatureResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetImsFeatureResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetImsFeatureResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetImsFeatureValueResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetImsFeatureResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetImsFeatureResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetImsFeatureResponseInner, info is nullptr.");
        int32_t value = data.ReadInt32();
        reply.WriteInt32(GetImsFeatureValueResponse(slotId, value));
        return TELEPHONY_SUCCESS;
    }
    reply.WriteInt32(GetImsFeatureValueResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnCtrlCameraResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnCtrlCameraResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnCtrlCameraResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(CtrlCameraResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetPreviewWindowResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetPreviewWindowResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetPreviewWindowResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetPreviewWindowResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetDisplayWindowResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetDisplayWindowResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetDisplayWindowResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetDisplayWindowResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetCameraZoomResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetCameraZoomResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetCameraZoomResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetCameraZoomResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetPauseImageResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetPauseImageResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetPauseImageResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetPauseImageResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetDeviceDirectionResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetDeviceDirectionResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetDeviceDirectionResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetDeviceDirectionResponse(slotId, *info));
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
    int32_t slotId = data.ReadInt32();
    auto info = (MuteControlResponse *)data.ReadRawData(sizeof(MuteControlResponse));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetMuteResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetMuteResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetMuteResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetMuteResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (MuteControlResponse *)data.ReadRawData(sizeof(MuteControlResponse));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetMuteResponseInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetMuteResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnCallRingBackReportInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnCallRingBackReportInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (RingbackVoice *)data.ReadRawData(sizeof(RingbackVoice));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnCallRingBackReportInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(CallRingBackReport(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnLastCallFailReasonResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnLastCallFailReasonResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto details = (DisconnectedDetails *)data.ReadRawData(sizeof(DisconnectedDetails));
    reply.WriteInt32(LastCallFailReasonResponse(slotId, *details));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetClipResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetClipResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetClipResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetClipResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetClipResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetClipResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto response = (ClipResponse *)data.ReadRawData(sizeof(ClipResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnGetClipResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetClipResponse(slotId, *response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetClirResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetClirResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto response = (ClirResponse *)data.ReadRawData(sizeof(ClirResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnGetClirResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetClirResponse(slotId, *response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetClirResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetClirResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetClipResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetClirResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetCallTransferResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetCallTransferResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto response = (CallTransferResponse *)data.ReadRawData(sizeof(CallTransferResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnGetCallTransferResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetCallTransferResponse(slotId, *response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetCallTransferResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetCallTransferResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetClipResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetCallTransferResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetCallRestrictionResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetCallRestrictionResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto response = (CallRestrictionResponse *)data.ReadRawData(sizeof(CallRestrictionResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnGetCallRestrictionResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetCallRestrictionResponse(slotId, *response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetCallRestrictionResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetCallRestrictionResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetCallRestrictionResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetCallRestrictionResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetCallWaitingResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetCallWaitingResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto response = (CallWaitResponse *)data.ReadRawData(sizeof(CallWaitResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnGetCallWaitingResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetCallWaitingResponse(slotId, *response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetCallWaitingResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetCallWaitingResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnGetCallWaitingResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetCallWaitingResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetColrResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetColrResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetColrResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetColrResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetColrResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetColrResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto response = (ColrResponse *)data.ReadRawData(sizeof(ColrResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnGetColrResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetColrResponse(slotId, *response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnSetColpResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnSetColpResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto info = (HRilRadioResponseInfo *)data.ReadRawData(sizeof(HRilRadioResponseInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnSetColpResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SetColpResponse(slotId, *info));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::OnGetColpResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::OnGetColpResponseInner entry");
    int32_t slotId = data.ReadInt32();
    auto response = (ColpResponse *)data.ReadRawData(sizeof(ColpResponse));
    if (response == nullptr) {
        TELEPHONY_LOGE("OnGetColpResponseInner return, response is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(GetColpResponse(slotId, *response));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::DialResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::DialResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_DIAL, info);
}

int32_t ImsCallCallbackStub::HangUpResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::HangUpResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_HANGUP_CONNECT, info);
}

int32_t ImsCallCallbackStub::RejectWithReasonResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::RejectWithReasonResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_REJECT_CALL, info);
}

int32_t ImsCallCallbackStub::AnswerResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::AnswerResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_ACCEPT_CALL, info);
}

int32_t ImsCallCallbackStub::HoldCallResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::HoldCallResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_HOLD_CALL, info);
}

int32_t ImsCallCallbackStub::UnHoldCallResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::UnHoldCallResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_ACTIVE_CALL, info);
}

int32_t ImsCallCallbackStub::SwitchCallResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SwitchCallResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_SWAP_CALL, info);
}

int32_t ImsCallCallbackStub::CombineConferenceResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::CombineConferenceResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::InviteToConferenceResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::InviteToConferenceResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::KickOutFromConferenceResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::KickOutFromConferenceResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::CallMediaModeResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::CallMediaModeResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::StartDtmfResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::StartDtmfResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_START_DTMF, info);
}

int32_t ImsCallCallbackStub::SendDtmfResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SendDtmfResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_SEND_DTMF, info);
}

int32_t ImsCallCallbackStub::StopDtmfResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::StopDtmfResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_STOP_DTMF, info);
}

int32_t ImsCallCallbackStub::StartRttResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::StartRttResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::StopRttResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::StopRttResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::CallStateChangeReport(int32_t slotId)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::CallStateChangeReport entry");
    std::shared_ptr<AppExecFwk::EventHandler> handler =
        DelayedSingleton<ImsCallClient>::GetInstance()->GetHandler(slotId);
    if (handler.get() == nullptr) {
        TELEPHONY_LOGE("handler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    bool ret = handler->SendEvent(RadioEvent::RADIO_IMS_CALL_STATUS_INFO);
    if (!ret) {
        TELEPHONY_LOGE("SendEvent failed! status update failed, slotId:%{public}d", slotId);
        return TELEPHONY_ERR_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetImsCallsDataResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsCallsDataResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_IMS_GET_CALL_DATA, info);
}

int32_t ImsCallCallbackStub::GetImsCallsDataResponse(int32_t slotId, const ImsCurrentCallList &callList)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsCallsDataResponse entry");
    std::shared_ptr<AppExecFwk::EventHandler> handler =
        DelayedSingleton<ImsCallClient>::GetInstance()->GetHandler(slotId);
    if (handler.get() == nullptr) {
        TELEPHONY_LOGE("handler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    std::shared_ptr<ImsCurrentCallList> imsCurrentCallList = std::make_shared<ImsCurrentCallList>();
    if (imsCurrentCallList == nullptr) {
        TELEPHONY_LOGE("make_shared ImsCurrentCallList failed!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    *imsCurrentCallList = callList;
    bool ret = handler->SendEvent(RadioEvent::RADIO_IMS_GET_CALL_DATA, imsCurrentCallList);
    if (!ret) {
        TELEPHONY_LOGE("SendEvent failed! status update failed, slotId:%{public}d", slotId);
        return TELEPHONY_ERR_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetPreModeResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetPreModeResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetPreModeResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetPreModeResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetPreModeResponse(int32_t slotId, int32_t mode)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetPreModeResponse entry mode:%{public}d", mode);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetImsSwitchResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetImsSwitchResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_SET_IMS_SWITCH_STATUS, info);
}

int32_t ImsCallCallbackStub::GetImsSwitchResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsSwitchResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_GET_IMS_SWITCH_STATUS, info);
}

int32_t ImsCallCallbackStub::GetImsSwitchResponse(int32_t slotId, int32_t active)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsSwitchResponse entry active:%{public}d", active);
    DelayedSingleton<ImsCallClient>::GetInstance()->GetHandler(slotId)->SendEvent(
        RadioEvent::RADIO_GET_IMS_SWITCH_STATUS, active);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetImsConfigResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetImsConfigResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetImsConfigResponse(int32_t slotId, int32_t value)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsConfigResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetImsConfigResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsConfigResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetImsFeatureValueResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetImsFeatureValueResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetImsFeatureValueResponse(int32_t slotId, int32_t value)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsFeatureValueResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetImsFeatureValueResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetImsFeatureValueResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::CtrlCameraResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::CtrlCameraResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetPreviewWindowResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetPreviewWindowResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetDisplayWindowResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetDisplayWindowResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetCameraZoomResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetCameraZoomResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetPauseImageResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetPauseImageResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetDeviceDirectionResponse(int32_t slotId, const HRilRadioResponseInfo &info)
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

int32_t ImsCallCallbackStub::SetMuteResponse(int32_t slotId, const MuteControlResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetMuteResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetMuteResponse(int32_t slotId, const MuteControlResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetMuteResponse entry");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::CallRingBackReport(int32_t slotId, const RingbackVoice &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::CallRingBackReport entry");
    std::shared_ptr<AppExecFwk::EventHandler> handler =
        DelayedSingleton<ImsCallClient>::GetInstance()->GetHandler(slotId);
    if (handler.get() == nullptr) {
        TELEPHONY_LOGE("handler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    std::shared_ptr<RingbackVoice> ringbackVoice = std::make_shared<RingbackVoice>();
    if (ringbackVoice == nullptr) {
        TELEPHONY_LOGE("make_shared RingbackVoice failed!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    *ringbackVoice = info;
    bool ret = handler->SendEvent(RadioEvent::RADIO_CALL_RINGBACK_VOICE, ringbackVoice);
    if (!ret) {
        TELEPHONY_LOGE("SendEvent failed! status update failed, slotId:%{public}d", slotId);
        return TELEPHONY_ERR_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::LastCallFailReasonResponse(int32_t slotId, const DisconnectedDetails &details)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::LastCallFailReasonResponse entry, reason is %{public}d", details.reason);
    std::shared_ptr<AppExecFwk::EventHandler> handler =
        DelayedSingleton<ImsCallClient>::GetInstance()->GetHandler(slotId);
    if (handler.get() == nullptr) {
        TELEPHONY_LOGE("handler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    std::shared_ptr<DisconnectedDetails> detailsInfo = std::make_shared<DisconnectedDetails>();
    if (detailsInfo == nullptr) {
        TELEPHONY_LOGE("make_shared detailsInfo failed!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    detailsInfo->reason = details.reason;
    detailsInfo->message = details.message;
    CellularCallConfig config;
    auto vecReasonInfo = config.GetImsCallDisconnectResoninfoMappingConfig(slotId);
    for (auto reasonInfo : vecReasonInfo) {
        char *p = nullptr;
        char *ptr = nullptr;
        ptr = strtok_r((char *)(reasonInfo.c_str()), "|", &p);
        int32_t tmpReason = (int32_t)std::atoi(ptr);
        int flag = false;
        while (tmpReason == static_cast<int32_t>(detailsInfo->reason)) {
            ptr = strtok_r(nullptr, "|", &p);
            if (ptr == nullptr) {
                break;
            }
            if (!flag) {
                detailsInfo->message = ptr;
                flag = true;
            } else {
                detailsInfo->reason = static_cast<DisconnectedReason>(std::atoi(ptr));
            }
        }
        if (flag) {
            break;
        }
    }
    bool ret = handler->SendEvent(RadioEvent::RADIO_GET_CALL_FAIL_REASON, detailsInfo);
    if (!ret) {
        TELEPHONY_LOGE("SendEvent failed! status update failed, slotId:%{public}d", slotId);
        return TELEPHONY_ERR_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetClipResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetClipResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_IMS_SET_CLIP, info);
}

int32_t ImsCallCallbackStub::GetClipResponse(int32_t slotId, const ClipResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetClipResponse entry");
    std::shared_ptr<AppExecFwk::EventHandler> handler =
        DelayedSingleton<ImsCallClient>::GetInstance()->GetHandler(slotId);
    if (handler.get() == nullptr) {
        TELEPHONY_LOGE("handler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    std::shared_ptr<ClipResponse> clipResponse = std::make_shared<ClipResponse>();
    if (clipResponse == nullptr) {
        TELEPHONY_LOGE("make_shared ClipResponse failed!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    *clipResponse = response;
    bool ret = handler->SendEvent(RadioEvent::RADIO_GET_CALL_CLIP, clipResponse);
    if (!ret) {
        TELEPHONY_LOGE("SendEvent failed! status update failed, slotId:%{public}d", slotId);
        return TELEPHONY_ERR_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::GetClirResponse(int32_t slotId, const ClirResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetClirResponse entry");
    std::shared_ptr<AppExecFwk::EventHandler> handler =
        DelayedSingleton<ImsCallClient>::GetInstance()->GetHandler(slotId);
    if (handler.get() == nullptr) {
        TELEPHONY_LOGE("handler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    std::shared_ptr<ClirResponse> clirResponse = std::make_shared<ClirResponse>();
    if (clirResponse == nullptr) {
        TELEPHONY_LOGE("make_shared ClirResponse failed!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    *clirResponse = response;
    bool ret = handler->SendEvent(RadioEvent::RADIO_GET_CALL_CLIR, clirResponse);
    if (!ret) {
        TELEPHONY_LOGE("SendEvent failed! status update failed, slotId:%{public}d", slotId);
        return TELEPHONY_ERR_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetClirResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetClirResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_GET_CALL_CLIR, info);
}

int32_t ImsCallCallbackStub::GetCallTransferResponse(int32_t slotId, const CallTransferResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetCallTransferResponse entry");
    std::shared_ptr<AppExecFwk::EventHandler> handler =
        DelayedSingleton<ImsCallClient>::GetInstance()->GetHandler(slotId);
    if (handler.get() == nullptr) {
        TELEPHONY_LOGE("handler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    std::shared_ptr<CallTransferResponse> callTransferResponse = std::make_shared<CallTransferResponse>();
    if (callTransferResponse == nullptr) {
        TELEPHONY_LOGE("make_shared CallTransferResponse failed!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    *callTransferResponse = response;
    bool ret = handler->SendEvent(RadioEvent::RADIO_GET_CALL_FORWARD, callTransferResponse);
    if (!ret) {
        TELEPHONY_LOGE("SendEvent failed! status update failed, slotId:%{public}d", slotId);
        return TELEPHONY_ERR_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetCallTransferResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetCallTransferResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_SET_CALL_FORWARD, info);
}

int32_t ImsCallCallbackStub::GetCallRestrictionResponse(int32_t slotId, const CallRestrictionResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetCallRestrictionResponse entry");
    std::shared_ptr<AppExecFwk::EventHandler> handler =
        DelayedSingleton<ImsCallClient>::GetInstance()->GetHandler(slotId);
    if (handler.get() == nullptr) {
        TELEPHONY_LOGE("handler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    std::shared_ptr<CallRestrictionResponse> callRestrictionResponse = std::make_shared<CallRestrictionResponse>();
    if (callRestrictionResponse == nullptr) {
        TELEPHONY_LOGE("make_shared CallRestrictionResponse failed!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    *callRestrictionResponse = response;
    bool ret = handler->SendEvent(RadioEvent::RADIO_SET_CALL_RESTRICTION, callRestrictionResponse);
    if (!ret) {
        TELEPHONY_LOGE("SendEvent failed! status update failed, slotId:%{public}d", slotId);
        return TELEPHONY_ERR_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetCallRestrictionResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetCallRestrictionResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_SET_CALL_RESTRICTION, info);
}

int32_t ImsCallCallbackStub::GetCallWaitingResponse(int32_t slotId, const CallWaitResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetCallWaitingResponse entry");
    std::shared_ptr<AppExecFwk::EventHandler> handler =
        DelayedSingleton<ImsCallClient>::GetInstance()->GetHandler(slotId);
    if (handler.get() == nullptr) {
        TELEPHONY_LOGE("handler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    std::shared_ptr<CallWaitResponse> callWaitResponse = std::make_shared<CallWaitResponse>();
    if (callWaitResponse == nullptr) {
        TELEPHONY_LOGE("make_shared CallWaitResponse failed!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    *callWaitResponse = response;
    bool ret = handler->SendEvent(RadioEvent::RADIO_GET_CALL_WAIT, callWaitResponse);
    if (!ret) {
        TELEPHONY_LOGE("SendEvent failed! status update failed, slotId:%{public}d", slotId);
        return TELEPHONY_ERR_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetCallWaitingResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetCallWaitingResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_SET_CALL_WAIT, info);
}

int32_t ImsCallCallbackStub::SetColrResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetColrResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_IMS_SET_COLR, info);
}

int32_t ImsCallCallbackStub::GetColrResponse(int32_t slotId, const ColrResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetColrResponse entry");
    std::shared_ptr<AppExecFwk::EventHandler> handler =
        DelayedSingleton<ImsCallClient>::GetInstance()->GetHandler(slotId);
    if (handler.get() == nullptr) {
        TELEPHONY_LOGE("handler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    std::shared_ptr<ColrResponse> colrResponse = std::make_shared<ColrResponse>();
    if (colrResponse == nullptr) {
        TELEPHONY_LOGE("make_shared ColrResponse failed!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    *colrResponse = response;
    bool ret = handler->SendEvent(RadioEvent::RADIO_IMS_GET_COLR, colrResponse);
    if (!ret) {
        TELEPHONY_LOGE("SendEvent failed! status update failed, slotId:%{public}d", slotId);
        return TELEPHONY_ERR_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SetColpResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::SetColpResponse entry");
    return SendEvent(slotId, RadioEvent::RADIO_IMS_SET_COLP, info);
}

int32_t ImsCallCallbackStub::GetColpResponse(int32_t slotId, const ColpResponse &response)
{
    TELEPHONY_LOGI("ImsCallCallbackStub::GetColpResponse entry");
    std::shared_ptr<AppExecFwk::EventHandler> handler =
        DelayedSingleton<ImsCallClient>::GetInstance()->GetHandler(slotId);
    if (handler.get() == nullptr) {
        TELEPHONY_LOGE("handler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    std::shared_ptr<ColpResponse> colpResponse = std::make_shared<ColpResponse>();
    if (colpResponse == nullptr) {
        TELEPHONY_LOGE("make_shared ColpResponse failed!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    *colpResponse = response;
    bool ret = handler->SendEvent(RadioEvent::RADIO_IMS_GET_COLP, colpResponse);
    if (!ret) {
        TELEPHONY_LOGE("SendEvent failed! status update failed, slotId:%{public}d", slotId);
        return TELEPHONY_ERR_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackStub::SendEvent(int32_t slotId, int32_t eventId, const HRilRadioResponseInfo &info)
{
    std::shared_ptr<AppExecFwk::EventHandler> handler =
        DelayedSingleton<ImsCallClient>::GetInstance()->GetHandler(slotId);
    if (handler.get() == nullptr) {
        TELEPHONY_LOGE("handler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    std::shared_ptr<HRilRadioResponseInfo> hRilRadioResponseInfo = std::make_shared<HRilRadioResponseInfo>();
    if (hRilRadioResponseInfo == nullptr) {
        TELEPHONY_LOGE("make_shared HRilRadioResponseInfo failed!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    *hRilRadioResponseInfo = info;
    bool ret = handler->SendEvent(eventId, hRilRadioResponseInfo);
    if (!ret) {
        TELEPHONY_LOGE("SendEvent failed! status update failed, slotId:%{public}d", slotId);
        return TELEPHONY_ERR_FAIL;
    }
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS
