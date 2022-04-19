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
#include "ims_call_stub.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
ImsCallStub::ImsCallStub()
{
    InitFuncMap();
}

ImsCallStub::~ImsCallStub() {}

void ImsCallStub::InitFuncMap()
{
    memberFuncMap_[IMS_DIAL] = &ImsCallStub::OnDial;
    memberFuncMap_[IMS_HANG_UP] = &ImsCallStub::OnHangUp;
    memberFuncMap_[IMS_REJECT] = &ImsCallStub::OnReject;
    memberFuncMap_[IMS_REJECT_WITH_REASON] = &ImsCallStub::OnRejectWithReason;
    memberFuncMap_[IMS_ANSWER] = &ImsCallStub::OnAnswer;
    memberFuncMap_[IMS_HOLD] = &ImsCallStub::OnHoldCall;
    memberFuncMap_[IMS_UN_HOLD] = &ImsCallStub::OnUnHoldCall;
    memberFuncMap_[IMS_SWITCH] = &ImsCallStub::OnSwitchCall;
    memberFuncMap_[IMS_COMBINE_CONFERENCE] = &ImsCallStub::OnCombineConference;
    memberFuncMap_[IMS_INVITE_TO_CONFERENCE] = &ImsCallStub::OnInviteToConference;
    memberFuncMap_[IMS_KICK_OUT_CONFERENCE] = &ImsCallStub::OnKickOutFromConference;
    memberFuncMap_[IMS_UPDATE_CALL_MEDIA_MODE] = &ImsCallStub::OnUpdateImsCallMode;
    memberFuncMap_[IMS_EMERGENCY_CALL] = &ImsCallStub::OnIsEmergencyPhoneNumber;
    memberFuncMap_[IMS_GET_CALL_DATA] = &ImsCallStub::OnGetImsCallsDataRequest;
    memberFuncMap_[IMS_GET_LAST_CALL_FAIL_REASON] = &ImsCallStub::OnGetLastCallFailReason;

    memberFuncMap_[IMS_START_DTMF] = &ImsCallStub::OnStartDtmf;
    memberFuncMap_[IMS_SEND_DTMF] = &ImsCallStub::OnSendDtmf;
    memberFuncMap_[IMS_STOP_DTMF] = &ImsCallStub::OnStopDtmf;
    memberFuncMap_[IMS_START_RTT] = &ImsCallStub::OnStartRtt;
    memberFuncMap_[IMS_STOP_RTT] = &ImsCallStub::OnStopRtt;

    memberFuncMap_[IMS_SET_DOMAIN_PREFERENCE_MODE] = &ImsCallStub::OnSetDomainPreferenceMode;
    memberFuncMap_[IMS_GET_DOMAIN_PREFERENCE_MODE] = &ImsCallStub::OnGetDomainPreferenceMode;
    memberFuncMap_[IMS_SET_LTE_SWITCH_STATUS] = &ImsCallStub::OnSetLteImsSwitchStatus;
    memberFuncMap_[IMS_GET_LTE_SWITCH_STATUS] = &ImsCallStub::OnGetLteImsSwitchStatus;
    memberFuncMap_[IMS_SET_IMS_CONFIG_STRING] = &ImsCallStub::OnSetImsConfig;
    memberFuncMap_[IMS_SET_IMS_CONFIG_INT] = &ImsCallStub::OnSetImsConfig;
    memberFuncMap_[IMS_GET_IMS_CONFIG] = &ImsCallStub::OnGetImsConfig;
    memberFuncMap_[IMS_SET_IMS_FEATURE] = &ImsCallStub::OnSetImsFeatureValue;
    memberFuncMap_[IMS_GET_IMS_FEATURE] = &ImsCallStub::OnGetImsFeatureValue;
    memberFuncMap_[IMS_SET_LTE_SWITCH_ENHANCE_MODE_STATUS] = &ImsCallStub::OnSetImsSwitchEnhanceMode;
    memberFuncMap_[IMS_GET_LTE_SWITCH_ENHANCE_MODE_STATUS] = &ImsCallStub::OnGetImsSwitchEnhanceMode;
    memberFuncMap_[IMS_SET_MUTE] = &ImsCallStub::OnSetMute;
    memberFuncMap_[IMS_GET_MUTE] = &ImsCallStub::OnGetMute;
    memberFuncMap_[IMS_GET_EMERGENCY_CALL_LIST] = &ImsCallStub::OnGetEmergencyCallList;

    memberFuncMap_[IMS_CTRL_CAMERA] = &ImsCallStub::OnCtrlCamera;
    memberFuncMap_[IMS_SET_PREVIEW_WINDOW] = &ImsCallStub::OnSetPreviewWindow;
    memberFuncMap_[IMS_SET_DISPLAY_WINDOW] = &ImsCallStub::OnSetDisplayWindow;
    memberFuncMap_[IMS_SET_CAMERA_ZOOM] = &ImsCallStub::OnSetCameraZoom;
    memberFuncMap_[IMS_SET_PAUSE_IMAGE] = &ImsCallStub::OnSetPauseImage;
    memberFuncMap_[IMS_SET_DEVICE_DIRECTION] = &ImsCallStub::OnSetDeviceDirection;

    memberFuncMap_[IMS_GET_CLIP] = &ImsCallStub::OnGetClip;
    memberFuncMap_[IMS_SET_CLIR] = &ImsCallStub::OnSetClir;
    memberFuncMap_[IMS_GET_CLIR] = &ImsCallStub::OnGetClir;
    memberFuncMap_[IMS_SET_CALL_TRANSFER] = &ImsCallStub::OnSetCallTransfer;
    memberFuncMap_[IMS_GET_CALL_TRANSFER] = &ImsCallStub::OnGetCallTransfer;
    memberFuncMap_[IMS_SET_CALL_RESTRICTION] = &ImsCallStub::OnSetCallRestriction;
    memberFuncMap_[IMS_GET_CALL_RESTRICTION] = &ImsCallStub::OnGetCallRestriction;
    memberFuncMap_[IMS_SET_CALL_WAITING] = &ImsCallStub::OnSetCallWaiting;
    memberFuncMap_[IMS_GET_CALL_WAITING] = &ImsCallStub::OnGetCallWaiting;

    memberFuncMap_[IMS_CALL_REGISTER_CALLBACK] = &ImsCallStub::OnRegisterImsCallCallback;
}

int32_t ImsCallStub::OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply,
                                     MessageOption &option)
{
    std::u16string descriptor = ImsCallStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (descriptor != remoteDescriptor) {
        TELEPHONY_LOGE("descriptor checking fail!");
        return TELEPHONY_ERR_DESCRIPTOR_MISMATCH;
    }
    TELEPHONY_LOGI("OnReceived, cmd = %{public}u", code);
    auto itFunc = memberFuncMap_.find(code);
    if (itFunc != memberFuncMap_.end()) {
        auto memberFunc = itFunc->second;
        if (memberFunc != nullptr) {
            return (this->*memberFunc)(data, reply);
        }
    }
    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

int32_t ImsCallStub::OnDial(MessageParcel &data, MessageParcel &reply)
{
    ImsCallInfo *callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    int32_t result = TELEPHONY_ERR_LOCAL_PTR_NULL;
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(result);
        return result;
    }
    CLIRMode *mode = (CLIRMode *)data.ReadRawData(sizeof(CLIRMode));
    if (mode == nullptr) {
        TELEPHONY_LOGE("CLIRMode is nullptr");
        reply.WriteInt32(result);
        return result;
    }
    reply.WriteInt32(Dial(*callInfo, *mode));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnHangUp(MessageParcel &data, MessageParcel &reply)
{
    ImsCallInfo *callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    int32_t result = TELEPHONY_ERR_LOCAL_PTR_NULL;
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(result);
        return result;
    }
    reply.WriteInt32(HangUp(*callInfo));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnReject(MessageParcel &data, MessageParcel &reply)
{
    ImsCallInfo *callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    int32_t result = TELEPHONY_ERR_LOCAL_PTR_NULL;
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(result);
        return result;
    }
    reply.WriteInt32(Reject(*callInfo));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnRejectWithReason(MessageParcel &data, MessageParcel &reply)
{
    ImsCallInfo *callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    int32_t result = TELEPHONY_ERR_LOCAL_PTR_NULL;
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(result);
        return result;
    }
    ImsRejectReason *imsRejectReason = (ImsRejectReason *)data.ReadRawData(sizeof(ImsRejectReason));
    if (imsRejectReason == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(result);
        return result;
    }
    reply.WriteInt32(RejectWithReason(*callInfo, *imsRejectReason));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnAnswer(MessageParcel &data, MessageParcel &reply)
{
    ImsCallInfo *callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    int32_t result = TELEPHONY_ERR_LOCAL_PTR_NULL;
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(result);
        return result;
    }
    reply.WriteInt32(Answer(*callInfo));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnHoldCall(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(HoldCall(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnUnHoldCall(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(UnHoldCall(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSwitchCall(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(SwitchCall(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnCombineConference(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(CombineConference(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnInviteToConference(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    std::vector<std::string> numberList;
    if (!data.ReadStringVector(&numberList)) {
        TELEPHONY_LOGE("Read string vector failed");
        return TELEPHONY_ERR_FAIL;
    }
    reply.WriteInt32(InviteToConference(slotId, numberList));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnKickOutFromConference(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    std::vector<std::string> numberList;
    if (!data.ReadStringVector(&numberList)) {
        TELEPHONY_LOGE("Read string vector failed");
        return TELEPHONY_ERR_FAIL;
    }
    reply.WriteInt32(KickOutFromConference(slotId, numberList));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnUpdateImsCallMode(MessageParcel &data, MessageParcel &reply)
{
    ImsCallInfo *callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    int32_t result = TELEPHONY_ERR_LOCAL_PTR_NULL;
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(result);
        return result;
    }
    ImsCallMode *callMode = (ImsCallMode *)data.ReadRawData(sizeof(ImsCallMode));
    if (callMode == nullptr) {
        TELEPHONY_LOGE("ImsCallMode is nullptr");
        reply.WriteInt32(result);
        return result;
    }
    reply.WriteInt32(UpdateImsCallMode(*callInfo, *callMode));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnIsEmergencyPhoneNumber(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    const std::string phoneNumber = data.ReadString();
    reply.WriteInt32(IsEmergencyPhoneNumber(slotId, phoneNumber));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetImsCallsDataRequest(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int64_t lastCallsDataFlag = data.ReadInt64();
    reply.WriteInt32(GetImsCallsDataRequest(slotId, lastCallsDataFlag));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetLastCallFailReason(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetLastCallFailReason(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnStartDtmf(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    const char *cDtmfCode = data.ReadCString();
    if (cDtmfCode == nullptr) {
        TELEPHONY_LOGE("cDtmfCode get fail");
        reply.WriteInt32(TELEPHONY_ERR_LOCAL_PTR_NULL);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t index = data.ReadInt32();

    reply.WriteInt32(StartDtmf(slotId, *cDtmfCode, index));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSendDtmf(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    const char *cDtmfCode = data.ReadCString();
    if (cDtmfCode == nullptr) {
        TELEPHONY_LOGE("cDtmfCode get fail");
        reply.WriteInt32(TELEPHONY_ERR_LOCAL_PTR_NULL);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t index = data.ReadInt32();

    reply.WriteInt32(SendDtmf(slotId, *cDtmfCode, index));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnStopDtmf(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t index = data.ReadInt32();

    reply.WriteInt32(StopDtmf(slotId, index));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnStartRtt(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    const std::string msg = data.ReadString();
    reply.WriteInt32(StartRtt(slotId, msg));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnStopRtt(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();

    reply.WriteInt32(StopRtt(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetDomainPreferenceMode(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t mode = data.ReadInt32();

    reply.WriteInt32(SetDomainPreferenceMode(slotId, mode));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetDomainPreferenceMode(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();

    reply.WriteInt32(GetDomainPreferenceMode(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetLteImsSwitchStatus(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t active = data.ReadInt32();

    reply.WriteInt32(SetLteImsSwitchStatus(slotId, active));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetLteImsSwitchStatus(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();

    reply.WriteInt32(GetLteImsSwitchStatus(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetImsConfig(MessageParcel &data, MessageParcel &reply)
{
    ImsConfigItem *item = (ImsConfigItem *)data.ReadRawData(sizeof(ImsConfigItem));
    if (item == nullptr) {
        TELEPHONY_LOGE("ImsConfigItem is nullptr");
        reply.WriteInt32(TELEPHONY_ERR_LOCAL_PTR_NULL);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t value = data.ReadInt32();

    reply.WriteInt32(SetImsConfig(*item, value));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetImsConfig(MessageParcel &data, MessageParcel &reply)
{
    ImsConfigItem *item = (ImsConfigItem *)data.ReadRawData(sizeof(ImsConfigItem));
    if (item == nullptr) {
        TELEPHONY_LOGE("ImsConfigItem is nullptr");
        reply.WriteInt32(TELEPHONY_ERR_LOCAL_PTR_NULL);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    reply.WriteInt32(GetImsConfig(*item));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetImsFeatureValue(MessageParcel &data, MessageParcel &reply)
{
    FeatureType *type = (FeatureType *)data.ReadRawData(sizeof(FeatureType));
    if (type == nullptr) {
        TELEPHONY_LOGE("FeatureType is nullptr");
        reply.WriteInt32(TELEPHONY_ERR_LOCAL_PTR_NULL);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t value = data.ReadInt32();

    reply.WriteInt32(SetImsFeatureValue(*type, value));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetImsFeatureValue(MessageParcel &data, MessageParcel &reply)
{
    FeatureType *type = (FeatureType *)data.ReadRawData(sizeof(FeatureType));
    if (type == nullptr) {
        TELEPHONY_LOGE("FeatureType is nullptr");
        reply.WriteInt32(TELEPHONY_ERR_LOCAL_PTR_NULL);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    reply.WriteInt32(GetImsFeatureValue(*type));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetImsSwitchEnhanceMode(MessageParcel &data, MessageParcel &reply)
{
    bool value = data.ReadInt32();
    reply.WriteInt32(SetImsSwitchEnhanceMode(value));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetImsSwitchEnhanceMode(MessageParcel &data, MessageParcel &reply)
{
    reply.WriteInt32(GetImsSwitchEnhanceMode());

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetMute(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t mute = data.ReadInt32();
    reply.WriteInt32(SetMute(slotId, mute));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetMute(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetMute(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetEmergencyCallList(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetEmergencyCallList(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnCtrlCamera(MessageParcel &data, MessageParcel &reply)
{
    const std::u16string cameraId = data.ReadString16();
    int32_t callingUid = data.ReadInt32();
    int32_t callingPid = data.ReadInt32();
    reply.WriteInt32(CtrlCamera(cameraId, callingUid, callingPid));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetPreviewWindow(MessageParcel &data, MessageParcel &reply)
{
    int32_t x = data.ReadInt32();
    int32_t y = data.ReadInt32();
    int32_t z = data.ReadInt32();
    int32_t width = data.ReadInt32();
    int32_t height = data.ReadInt32();
    reply.WriteInt32(SetPreviewWindow(x, y, z, width, height));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetDisplayWindow(MessageParcel &data, MessageParcel &reply)
{
    int32_t x = data.ReadInt32();
    int32_t y = data.ReadInt32();
    int32_t z = data.ReadInt32();
    int32_t width = data.ReadInt32();
    int32_t height = data.ReadInt32();
    reply.WriteInt32(SetDisplayWindow(x, y, z, width, height));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetCameraZoom(MessageParcel &data, MessageParcel &reply)
{
    float zoomRatio = data.ReadFloat();
    reply.WriteInt32(SetCameraZoom(zoomRatio));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetPauseImage(MessageParcel &data, MessageParcel &reply)
{
    const std::u16string path = data.ReadString16();
    reply.WriteInt32(SetPauseImage(path));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetDeviceDirection(MessageParcel &data, MessageParcel &reply)
{
    int32_t rotation = data.ReadInt32();
    reply.WriteInt32(SetDeviceDirection(rotation));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetClip(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetClip(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetClir(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t action = data.ReadInt32();
    reply.WriteInt32(SetClir(slotId, action));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetClir(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetClir(slotId));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetCallTransfer(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t reason = data.ReadInt32();
    int32_t mode = data.ReadInt32();
    const std::string transferNum = data.ReadString();
    int32_t classType = data.ReadInt32();
    reply.WriteInt32(SetCallTransfer(slotId, reason, mode, transferNum, classType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetCallTransfer(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t reason = data.ReadInt32();
    reply.WriteInt32(GetCallTransfer(slotId, reason));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetCallRestriction(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    const std::string fac = data.ReadString();
    int32_t mode = data.ReadInt32();
    const std::string pw = data.ReadString();
    reply.WriteInt32(SetCallRestriction(slotId, fac, mode, pw));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetCallRestriction(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    const std::string fac = data.ReadString();
    reply.WriteInt32(GetCallRestriction(slotId, fac));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetCallWaiting(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    bool activate = data.ReadInt32();
    reply.WriteInt32(SetCallWaiting(slotId, activate));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetCallWaiting(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetCallWaiting(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnRegisterImsCallCallback(MessageParcel &data, MessageParcel &reply)
{
    auto remote = data.ReadRemoteObject();
    int32_t result = TELEPHONY_ERR_LOCAL_PTR_NULL;
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(result);
        return result;
    }
    result = RegisterImsCallCallback(iface_cast<ImsCallCallbackInterface>(remote));
    reply.WriteInt32(result);
    return TELEPHONY_SUCCESS;
}
} // Telephony
} // OHOS
