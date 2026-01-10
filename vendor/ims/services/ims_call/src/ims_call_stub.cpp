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
#include "ipc_skeleton.h"

#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
const int32_t IMS_CAPABILITIES_MAX_SIZE = 10;
ImsCallStub::ImsCallStub()
{
    InitFuncMap();
}

ImsCallStub::~ImsCallStub() {}

void ImsCallStub::InitFuncMap()
{
    InitDialFuncMap();
    InitDtmfFuncMap();
    InitConfigFuncMap();
    InitVideoFuncMap();
    InitSupplementFuncMap();
}

void ImsCallStub::InitDialFuncMap()
{
    memberFuncMap_[IMS_DIAL] = [this](MessageParcel &data, MessageParcel &reply) { return OnDial(data, reply); };
    memberFuncMap_[IMS_HANG_UP] = [this](MessageParcel &data, MessageParcel &reply) { return OnHangUp(data, reply); };
    memberFuncMap_[IMS_REJECT_WITH_REASON] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnRejectWithReason(data, reply); };
    memberFuncMap_[IMS_ANSWER] = [this](MessageParcel &data, MessageParcel &reply) { return OnAnswer(data, reply); };
    memberFuncMap_[IMS_HOLD] = [this](MessageParcel &data, MessageParcel &reply) { return OnHoldCall(data, reply); };
    memberFuncMap_[IMS_UN_HOLD] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnUnHoldCall(data, reply); };
    memberFuncMap_[IMS_SWITCH] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSwitchCall(data, reply); };
    memberFuncMap_[IMS_COMBINE_CONFERENCE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnCombineConference(data, reply); };
    memberFuncMap_[IMS_INVITE_TO_CONFERENCE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnInviteToConference(data, reply); };
    memberFuncMap_[IMS_KICK_OUT_CONFERENCE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnKickOutFromConference(data, reply); };
    memberFuncMap_[IMS_UPDATE_CALL_MEDIA_MODE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnUpdateImsCallMode(data, reply); };
    memberFuncMap_[IMS_GET_CALL_DATA] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetImsCallsDataRequest(data, reply); };
    memberFuncMap_[IMS_GET_LAST_CALL_FAIL_REASON] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetLastCallFailReason(data, reply); };
}

void ImsCallStub::InitDtmfFuncMap()
{
    memberFuncMap_[IMS_START_DTMF] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnStartDtmf(data, reply); };
    memberFuncMap_[IMS_SEND_DTMF] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSendDtmf(data, reply); };
    memberFuncMap_[IMS_STOP_DTMF] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnStopDtmf(data, reply); };
#ifdef SUPPORT_RTT_CALL
    memberFuncMap_[IMS_UPDATE_RTT_CALL_MODE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnUpdateImsRttCallMode(data, reply); };
#endif
}

void ImsCallStub::InitConfigFuncMap()
{
    memberFuncMap_[IMS_SET_DOMAIN_PREFERENCE_MODE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetDomainPreferenceMode(data, reply); };
    memberFuncMap_[IMS_GET_DOMAIN_PREFERENCE_MODE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetDomainPreferenceMode(data, reply); };
    memberFuncMap_[IMS_SET_SWITCH_STATUS] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetImsSwitchStatus(data, reply); };
    memberFuncMap_[IMS_GET_SWITCH_STATUS] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetImsSwitchStatus(data, reply); };
    memberFuncMap_[IMS_SET_IMS_CONFIG_STRING] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetImsConfigString(data, reply); };
    memberFuncMap_[IMS_SET_IMS_CONFIG_INT] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetImsConfigInt(data, reply); };
    memberFuncMap_[IMS_GET_IMS_CONFIG] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetImsConfig(data, reply); };
    memberFuncMap_[IMS_SET_IMS_FEATURE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetImsFeatureValue(data, reply); };
    memberFuncMap_[IMS_GET_IMS_FEATURE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetImsFeatureValue(data, reply); };
    memberFuncMap_[IMS_SET_MUTE] = [this](MessageParcel &data, MessageParcel &reply) { return OnSetMute(data, reply); };
    memberFuncMap_[IMS_GET_MUTE] = [this](MessageParcel &data, MessageParcel &reply) { return OnGetMute(data, reply); };
    memberFuncMap_[IMS_UPDATE_CAPABILITY] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnUpdateImsCapabilities(data, reply); };
}

void ImsCallStub::InitVideoFuncMap()
{
    memberFuncMap_[IMS_CTRL_CAMERA] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnCtrlCamera(data, reply); };
    memberFuncMap_[IMS_SET_PREVIEW_WINDOW] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetPreviewWindow(data, reply); };
    memberFuncMap_[IMS_SET_DISPLAY_WINDOW] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetDisplayWindow(data, reply); };
    memberFuncMap_[IMS_SET_CAMERA_ZOOM] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetCameraZoom(data, reply); };
    memberFuncMap_[IMS_SET_PAUSE_IMAGE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetPauseImage(data, reply); };
    memberFuncMap_[IMS_SET_DEVICE_DIRECTION] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetDeviceDirection(data, reply); };
}

void ImsCallStub::InitSupplementFuncMap()
{
    memberFuncMap_[IMS_SET_CLIP] = [this](MessageParcel &data, MessageParcel &reply) { return OnGetClip(data, reply); };
    memberFuncMap_[IMS_GET_CLIP] = [this](MessageParcel &data, MessageParcel &reply) { return OnGetClip(data, reply); };
    memberFuncMap_[IMS_SET_CLIR] = [this](MessageParcel &data, MessageParcel &reply) { return OnSetClir(data, reply); };
    memberFuncMap_[IMS_GET_CLIR] = [this](MessageParcel &data, MessageParcel &reply) { return OnGetClir(data, reply); };
    memberFuncMap_[IMS_SET_CALL_TRANSFER] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetCallTransfer(data, reply); };
    memberFuncMap_[IMS_GET_CALL_TRANSFER] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetCallTransfer(data, reply); };
    memberFuncMap_[IMS_SET_CALL_RESTRICTION] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetCallRestriction(data, reply); };
    memberFuncMap_[IMS_GET_CALL_RESTRICTION] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetCallRestriction(data, reply); };
    memberFuncMap_[IMS_SET_CALL_WAITING] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetCallWaiting(data, reply); };
    memberFuncMap_[IMS_GET_CALL_WAITING] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetCallWaiting(data, reply); };
    memberFuncMap_[IMS_SET_COLR] = [this](MessageParcel &data, MessageParcel &reply) { return OnSetColr(data, reply); };
    memberFuncMap_[IMS_GET_COLR] = [this](MessageParcel &data, MessageParcel &reply) { return OnGetColr(data, reply); };
    memberFuncMap_[IMS_SET_COLP] = [this](MessageParcel &data, MessageParcel &reply) { return OnSetColp(data, reply); };
    memberFuncMap_[IMS_GET_COLP] = [this](MessageParcel &data, MessageParcel &reply) { return OnGetColp(data, reply); };

    memberFuncMap_[IMS_CALL_REGISTER_CALLBACK] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnRegisterImsCallCallback(data, reply); };
}

int32_t ImsCallStub::OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    std::u16string descriptor = ImsCallStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (descriptor != remoteDescriptor) {
        TELEPHONY_LOGE("descriptor checking fail!");
        return TELEPHONY_ERR_DESCRIPTOR_MISMATCH;
    }
    TELEPHONY_LOGI("OnReceived, cmd = %{public}u", code);
    auto itFunction = memberFuncMap_.find(code);
    if (itFunction != memberFuncMap_.end()) {
        auto memberFunc = itFunction->second;
        if (memberFunc != nullptr) {
            return memberFunc(data, reply);
        }
    }
    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

int32_t ImsCallStub::OnDial(MessageParcel &data, MessageParcel &reply)
{
    ImsCallInfo *callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    int32_t dialResult = TELEPHONY_ERR_LOCAL_PTR_NULL;
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(dialResult);
        return dialResult;
    }
    auto mode = static_cast<CLIRMode>(data.ReadInt32());

    reply.WriteInt32(Dial(*callInfo, mode));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnHangUp(MessageParcel &data, MessageParcel &reply)
{
    ImsCallInfo *callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    int32_t hangUpResult = TELEPHONY_ERR_LOCAL_PTR_NULL;
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(hangUpResult);
        return hangUpResult;
    }
    reply.WriteInt32(HangUp(*callInfo));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnRejectWithReason(MessageParcel &data, MessageParcel &reply)
{
    ImsCallInfo *callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    int32_t onRejectResult = TELEPHONY_ERR_LOCAL_PTR_NULL;
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(onRejectResult);
        return onRejectResult;
    }
    auto imsRejectReason = static_cast<ImsRejectReason>(data.ReadInt32());

    reply.WriteInt32(RejectWithReason(*callInfo, imsRejectReason));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnAnswer(MessageParcel &data, MessageParcel &reply)
{
    ImsCallInfo *callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    int32_t answerResult = TELEPHONY_ERR_LOCAL_PTR_NULL;
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(answerResult);
        return answerResult;
    }
    reply.WriteInt32(Answer(*callInfo));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnHoldCall(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t callType = data.ReadInt32();
    bool isRTT = data.ReadBool();
    reply.WriteInt32(HoldCall(slotId, callType, isRTT));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnUnHoldCall(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t callType = data.ReadInt32();
    bool isRTT = data.ReadBool();
    reply.WriteInt32(UnHoldCall(slotId, callType, isRTT));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSwitchCall(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t callType = data.ReadInt32();
    bool isRTT = data.ReadBool();
    reply.WriteInt32(SwitchCall(slotId, callType, isRTT));
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
        TELEPHONY_LOGE("Read string vector failed!");
        return TELEPHONY_ERR_FAIL;
    }
    reply.WriteInt32(InviteToConference(slotId, numberList));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnKickOutFromConference(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t kickoutCallIndex = data.ReadInt32();
    if (!IsValidSlotId(slotId)) {
        TELEPHONY_LOGE("invalid slotId[%{public}d]", slotId);
        reply.WriteInt32(TELEPHONY_ERR_FAIL);
        return TELEPHONY_ERR_SLOTID_INVALID;
    }
    reply.WriteInt32(KickOutFromConference(slotId, kickoutCallIndex));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnUpdateImsCallMode(MessageParcel &data, MessageParcel &reply)
{
    ImsCallInfo *imsCallInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    int32_t result = TELEPHONY_ERR_LOCAL_PTR_NULL;
    if (imsCallInfo == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(result);
        return result;
    }
    auto callMode = static_cast<ImsCallMode>(data.ReadInt32());

    reply.WriteInt32(UpdateImsCallMode(*imsCallInfo, callMode));
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
    const char cDtmfCode = data.ReadInt8();
    int32_t index = data.ReadInt32();

    reply.WriteInt32(StartDtmf(slotId, cDtmfCode, index));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSendDtmf(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    const char cDtmfCode = data.ReadInt8();
    int32_t index = data.ReadInt32();

    reply.WriteInt32(SendDtmf(slotId, cDtmfCode, index));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnStopDtmf(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t index = data.ReadInt32();

    reply.WriteInt32(StopDtmf(slotId, index));
    return TELEPHONY_SUCCESS;
}

#ifdef SUPPORT_RTT_CALL
int32_t ImsCallStub::OnUpdateImsRttCallMode(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t callId = data.ReadInt32();
    int32_t mode = data.ReadInt32();
    reply.WriteInt32(UpdateImsRttCallMode(slotId, callId, mode));

    return TELEPHONY_SUCCESS;
}
#endif

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

int32_t ImsCallStub::OnSetImsSwitchStatus(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t active = data.ReadInt32();

    reply.WriteInt32(SetImsSwitchStatus(slotId, active));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetImsSwitchStatus(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();

    reply.WriteInt32(GetImsSwitchStatus(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetImsConfigInt(MessageParcel &data, MessageParcel &reply)
{
    auto item = static_cast<ImsConfigItem>(data.ReadInt32());
    int32_t imsConfigValue = data.ReadInt32();

    reply.WriteInt32(SetImsConfig(item, imsConfigValue));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetImsConfigString(MessageParcel &data, MessageParcel &reply)
{
    auto imsConfigItem = static_cast<ImsConfigItem>(data.ReadInt32());
    std::string imsConfigValue = data.ReadString();

    reply.WriteInt32(SetImsConfig(imsConfigItem, imsConfigValue));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetImsConfig(MessageParcel &data, MessageParcel &reply)
{
    auto imsConfigItem = static_cast<ImsConfigItem>(data.ReadInt32());

    reply.WriteInt32(GetImsConfig(imsConfigItem));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetImsFeatureValue(MessageParcel &data, MessageParcel &reply)
{
    auto type = static_cast<FeatureType>(data.ReadInt32());
    int32_t imsFeatureValue = data.ReadInt32();

    reply.WriteInt32(SetImsFeatureValue(type, imsFeatureValue));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetImsFeatureValue(MessageParcel &data, MessageParcel &reply)
{
    auto type = static_cast<FeatureType>(data.ReadInt32());

    int32_t imsFeatureValue = ImsFeatureIntResult::IMS_FEATURE_INT_RESULT_UNKNOWN;
    reply.WriteInt32(GetImsFeatureValue(type, imsFeatureValue));
    reply.WriteInt32(imsFeatureValue);

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

int32_t ImsCallStub::OnCtrlCamera(MessageParcel &data, MessageParcel &reply)
{
    const std::u16string cameraId = data.ReadString16();
    auto callingPid = IPCSkeleton::GetCallingPid();
    auto callingUid = IPCSkeleton::GetCallingUid();
    reply.WriteInt32(CtrlCamera(cameraId, callingUid, callingPid));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetPreviewWindow(MessageParcel &data, MessageParcel &reply)
{
    int32_t previewWindowX = data.ReadInt32();
    int32_t previewWindowY = data.ReadInt32();
    int32_t previewWindowZ = data.ReadInt32();
    int32_t width = data.ReadInt32();
    int32_t height = data.ReadInt32();
    reply.WriteInt32(SetPreviewWindow(previewWindowX, previewWindowY, previewWindowZ, width, height));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetDisplayWindow(MessageParcel &data, MessageParcel &reply)
{
    int32_t displayWindowX = data.ReadInt32();
    int32_t displayWindowY = data.ReadInt32();
    int32_t displayWindowZ = data.ReadInt32();
    int32_t width = data.ReadInt32();
    int32_t height = data.ReadInt32();
    reply.WriteInt32(SetDisplayWindow(displayWindowX, displayWindowY, displayWindowZ, width, height));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetCameraZoom(MessageParcel &data, MessageParcel &reply)
{
    float cameraZoomRatio = data.ReadFloat();
    reply.WriteInt32(SetCameraZoom(cameraZoomRatio));

    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetPauseImage(MessageParcel &data, MessageParcel &reply)
{
    const std::u16string pauseImagePath = data.ReadString16();
    reply.WriteInt32(SetPauseImage(pauseImagePath));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetDeviceDirection(MessageParcel &data, MessageParcel &reply)
{
    int32_t rotation = data.ReadInt32();
    reply.WriteInt32(SetDeviceDirection(rotation));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetClip(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t action = data.ReadInt32();
    reply.WriteInt32(SetClip(slotId, action));
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
    bool activate = data.ReadBool();
    int32_t classType = data.ReadInt32();
    reply.WriteInt32(SetCallWaiting(slotId, activate, classType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetCallWaiting(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetCallWaiting(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetColr(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t presentation = data.ReadInt32();
    reply.WriteInt32(SetColr(slotId, presentation));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetColr(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetColr(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnSetColp(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t action = data.ReadInt32();
    reply.WriteInt32(SetColp(slotId, action));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnGetColp(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetColp(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnRegisterImsCallCallback(MessageParcel &data, MessageParcel &reply)
{
    auto imsCallbackRemote = data.ReadRemoteObject();
    int32_t result = TELEPHONY_ERR_LOCAL_PTR_NULL;
    if (imsCallbackRemote == nullptr) {
        TELEPHONY_LOGE("ImsCallInfo is nullptr");
        reply.WriteInt32(result);
        return result;
    }
    result = RegisterImsCallCallback(iface_cast<ImsCallCallbackInterface>(imsCallbackRemote));
    reply.WriteInt32(result);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallStub::OnUpdateImsCapabilities(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t dataSize = data.ReadInt32();
    if (dataSize < 0 || dataSize > IMS_CAPABILITIES_MAX_SIZE) {
        TELEPHONY_LOGE("OnUpdateImsCapabilities size error");
        return TELEPHONY_ERR_FAIL;
    }
    ImsCapability imsCapability;
    ImsCapabilityList imsCapabilityList;
    for (int i = 0; i < dataSize; i++) {
        imsCapability.imsCapabilityType = static_cast<const ImsCapabilityType>(data.ReadInt32());
        imsCapability.imsRadioTech = static_cast<const ImsRegTech>(data.ReadInt32());
        imsCapability.enable = data.ReadBool();
        imsCapabilityList.imsCapabilities.push_back(imsCapability);
    }
    reply.WriteInt32(UpdateImsCapabilities(slotId, imsCapabilityList));
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS
