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

#include "ims_stub.h"

#include "call_manager_errors.h"
#include "ims_register.h"

namespace OHOS {
namespace Telephony {
ImsStub::ImsStub()
{
    TELEPHONY_LOGI("ImsStub::ImsStub entry");
    InitBasicCallFuncMap();
    InitSupportCallFuncMap();
}

void ImsStub::InitBasicCallFuncMap()
{
    requestFuncMap_[IMS_DIAL] = &ImsStub::OnDialInner;
    requestFuncMap_[IMS_HANG_UP] = &ImsStub::OnHangUpInner;
    requestFuncMap_[IMS_REJECT] = &ImsStub::OnRejectInner;
    requestFuncMap_[IMS_ANSWER] = &ImsStub::OnAnswerInner;
    requestFuncMap_[IMS_HOLD] = &ImsStub::OnHoldCallInner;
    requestFuncMap_[IMS_UN_HOLD] = &ImsStub::OnUnHoldCallInner;
    requestFuncMap_[IMS_SWITCH] = &ImsStub::OnSwitchCallInner;
    requestFuncMap_[IMS_COMBINE_CONFERENCE] = &ImsStub::OnCombineConferenceInner;
    requestFuncMap_[IMS_INVITE_TO_CONFERENCE] = &ImsStub::OnInviteToConferenceInner;
    requestFuncMap_[IMS_KICK_OUT_CONFERENCE] = &ImsStub::OnKickOutFromConferenceInner;
    requestFuncMap_[IMS_UPDATE_CALL_MEDIA_MODE] = &ImsStub::OnUpdateCallMediaModeInner;
    requestFuncMap_[IMS_EMERGENCY_CALL] = &ImsStub::OnIsEmergencyPhoneNumberInner;
    requestFuncMap_[IMS_START_DTMF] = &ImsStub::OnStartDtmfInner;
    requestFuncMap_[IMS_SEND_DTMF] = &ImsStub::OnSendDtmfInner;
    requestFuncMap_[IMS_STOP_DTMF] = &ImsStub::OnStopDtmfInner;
    requestFuncMap_[IMS_START_RTT] = &ImsStub::OnStartRttInner;
    requestFuncMap_[IMS_STOP_RTT] = &ImsStub::OnStopRttInner;
}

void ImsStub::InitSupportCallFuncMap()
{
    requestFuncMap_[IMS_SET_DOMAIN_PREFERENCE_MODE] = &ImsStub::OnSetDomainPreferenceModeInner;
    requestFuncMap_[IMS_GET_DOMAIN_PREFERENCE_MODE] = &ImsStub::OnGetDomainPreferenceModeInner;
    requestFuncMap_[IMS_SET_LTE_IMS_SWITCH_STATUS] = &ImsStub::OnSetLteImsSwitchStatusInner;
    requestFuncMap_[IMS_GET_LTE_IMS_SWITCH_STATUS] = &ImsStub::OnGetLteImsSwitchStatusInner;
    requestFuncMap_[IMS_SET_IMS_CONFIG_STRING] = &ImsStub::OnSetImsConfigStringInner;
    requestFuncMap_[IMS_SET_IMS_CONFIG_INT] = &ImsStub::OnSetImsConfigIntInner;
    requestFuncMap_[IMS_GET_IMS_CONFIG] = &ImsStub::OnGetImsConfigInner;
    requestFuncMap_[IMS_SET_IMS_FEATURE] = &ImsStub::OnSetImsFeatureValueInner;
    requestFuncMap_[IMS_GET_IMS_FEATURE] = &ImsStub::OnGetImsFeatureValueInner;
    requestFuncMap_[IMS_SET_VOLTE_ENHANCE_MODE] = &ImsStub::OnSetVolteEnhanceModeInner;
    requestFuncMap_[IMS_GET_VOLTE_ENHANCE_MODE] = &ImsStub::OnGetVolteEnhanceModeInner;
    requestFuncMap_[IMS_CTRL_CAMERA] = &ImsStub::OnCtrlCameraInner;
    requestFuncMap_[IMS_SET_PREVIEW_WINDOW] = &ImsStub::OnSetPreviewWindowInner;
    requestFuncMap_[IMS_SET_DISPLAY_WINDOW] = &ImsStub::OnSetDisplayWindowInner;
    requestFuncMap_[IMS_SET_CAMERA_ZOOM] = &ImsStub::OnSetCameraZoomInner;
    requestFuncMap_[IMS_SET_PAUSE_IMAGE] = &ImsStub::OnSetPauseImageInner;
    requestFuncMap_[IMS_SET_DEVICE_DIRECTION] = &ImsStub::OnSetDeviceDirectionInner;
    requestFuncMap_[IMS_REGISTER_CALLBACK] = &ImsStub::OnRegisterCellularCallBackInner;
    requestFuncMap_[IMS_IS_CALLBACK_EXISTS] = &ImsStub::OnIsCallBackExistsInner;
    requestFuncMap_[IMS_GET_CALL_DATA] = &ImsStub::OnGetImsCallsDataRequestInner;
    requestFuncMap_[IMS_SET_MUTE] = &ImsStub::OnSetMuteInner;
    requestFuncMap_[IMS_GET_MUTE] = &ImsStub::OnGetMuteInner;
    requestFuncMap_[IMS_GET_EMERGENCY_CALL_LIST] = &ImsStub::OnGetEmergencyCallListInner;
    requestFuncMap_[GET_CALL_FAIL_REASON] = &ImsStub::OnGetCallFailReasonInner;
    requestFuncMap_[IMS_INQUIRE_CLIP] = &ImsStub::OnInquireClipInner;
    requestFuncMap_[IMS_SET_CLIR] = &ImsStub::OnSetClirInner;
    requestFuncMap_[IMS_INQUIRE_CLIR] = &ImsStub::OnInquireClirInner;
    requestFuncMap_[IMS_SET_CALL_TRANSFER] = &ImsStub::OnSetCallTransferInner;
    requestFuncMap_[IMS_GET_CALL_TRANSFER] = &ImsStub::OnGetCallTransferInner;
    requestFuncMap_[IMS_SET_CALL_RESTRICTION] = &ImsStub::OnSetCallRestrictionInner;
    requestFuncMap_[IMS_GET_CALL_RESTRICTION] = &ImsStub::OnGetCallRestrictionInner;
    requestFuncMap_[IMS_SET_CALL_WAITING] = &ImsStub::OnSetCallWaitingInner;
    requestFuncMap_[IMS_GET_CALL_WAITING] = &ImsStub::OnGetCallWaitingInner;
}

ImsStub::~ImsStub()
{
    requestFuncMap_.clear();
}

int32_t ImsStub::OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    std::u16string myDescriptor = ImsStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (myDescriptor != remoteDescriptor) {
        TELEPHONY_LOGE("ImsStub::OnRemoteRequest return, descriptor checked fail");
        return TELEPHONY_ERR_DESCRIPTOR_MISMATCH;
    }

    auto itFunc = requestFuncMap_.find(code);
    if (itFunc != requestFuncMap_.end()) {
        auto requestFunc = itFunc->second;
        if (requestFunc != nullptr) {
            return (this->*requestFunc)(data, reply);
        }
    }
    TELEPHONY_LOGI("ImsStub::OnRemoteRequest, default case, need check.");
    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

int32_t ImsStub::OnDialInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnDialInner entry");
    auto callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("OnDialInner return, callInfo is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    auto mode = static_cast<CLIRMode>(data.ReadInt32());
    reply.WriteInt32(Dial(*callInfo, mode));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnHangUpInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnHangUpInner entry");
    auto callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("OnHangUpInner return, callInfo is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    reply.WriteInt32(HangUp(*callInfo));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnRejectInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnRejectInner entry");
    auto callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("OnRejectInner return, callInfo is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    reply.WriteInt32(Reject(*callInfo));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnAnswerInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnAnswerInner entry");
    auto callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("OnAnswerInner return, callInfo is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    reply.WriteInt32(Answer(*callInfo));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnHoldCallInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnHoldCallInner entry");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(HoldCall(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnUnHoldCallInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnUnHoldCallInner entry");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(UnHoldCall(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSwitchCallInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSwitchCallInner entry");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(SwitchCall(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnCombineConferenceInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnCombineConferenceInner entry");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(CombineConference(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnInviteToConferenceInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnInviteToConferenceInner entry");
    int32_t slotId = data.ReadInt32();
    std::vector<std::string> numberList;
    bool bRead = data.ReadStringVector(&numberList);
    if (!bRead) {
        TELEPHONY_LOGE("InviteToConferenceInner return, read fail.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(InviteToConference(slotId, numberList));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnKickOutFromConferenceInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnKickOutFromConferenceInner entry");
    int32_t slotId = data.ReadInt32();
    std::vector<std::string> numberList;
    bool bRead = data.ReadStringVector(&numberList);
    if (!bRead) {
        TELEPHONY_LOGE("OnKickOutFromConferenceInner return, read fail.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(KickOutFromConference(slotId, numberList));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnUpdateCallMediaModeInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnUpdateCallMediaModeInner entry");
    auto callInfo = (ImsCallInfo *)data.ReadRawData(sizeof(ImsCallInfo));
    if (callInfo == nullptr) {
        TELEPHONY_LOGE("OnUpdateCallMediaModeInner return, callInfo is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    auto mode = static_cast<CallMediaMode>(data.ReadInt32());
    reply.WriteInt32(UpdateCallMediaMode(*callInfo, mode));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnIsEmergencyPhoneNumberInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnIsEmergencyPhoneNumberInner entry");
    int32_t slotId = data.ReadInt32();
    std::string phoneNum = data.ReadString();
    reply.WriteInt32(IsEmergencyPhoneNumber(slotId, phoneNum));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnStartDtmfInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnStartDtmfInner entry");
    int32_t slotId = data.ReadInt32();
    char *pDtmf = (char *)(data.ReadCString());
    if (pDtmf == nullptr) {
        TELEPHONY_LOGE("OnStartDtmfInner return, pDtmf is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t index = data.ReadInt32();
    reply.WriteInt32(StartDtmf(slotId, *pDtmf, index));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSendDtmfInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSendDtmfInner entry");
    int32_t slotId = data.ReadInt32();
    char *pDtmf = (char *)(data.ReadCString());
    if (pDtmf == nullptr) {
        TELEPHONY_LOGE("OnSendDtmfInner return, pDtmf is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t index = data.ReadInt32();
    reply.WriteInt32(SendDtmf(slotId, *pDtmf, index));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnStopDtmfInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnStopDtmfInner entry");
    int32_t slotId = data.ReadInt32();
    int32_t index = data.ReadInt32();
    reply.WriteInt32(StopDtmf(slotId, index));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnStartRttInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnStartRttInner entry");
    int32_t slotId = data.ReadInt32();
    std::string msg = data.ReadString();
    reply.WriteInt32(StartRtt(slotId, msg));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnStopRttInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnStopRttInner entry");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(StopRtt(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetDomainPreferenceModeInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetDomainPreferenceModeInner entry");
    int32_t mode = data.ReadInt32();
    reply.WriteInt32(SetDomainPreferenceMode(mode));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnGetDomainPreferenceModeInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnGetDomainPreferenceModeInner entry");
    reply.WriteInt32(GetDomainPreferenceMode());
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetLteImsSwitchStatusInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetLteImsSwitchStatusInner entry");
    bool active = data.ReadBool();
    reply.WriteInt32(SetLteImsSwitchStatus(active));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnGetLteImsSwitchStatusInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnGetLteImsSwitchStatusInner entry");
    reply.WriteInt32(GetLteImsSwitchStatus());
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetImsConfigStringInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetImsConfigStringInner entry");
    auto item = static_cast<ImsConfigItem>(data.ReadInt32());
    std::string value = data.ReadString();
    reply.WriteInt32(SetImsConfig(item, value));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetImsConfigIntInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetImsConfigIntInner entry");
    auto item = static_cast<ImsConfigItem>(data.ReadInt32());
    int32_t value = data.ReadInt32();
    reply.WriteInt32(SetImsConfig(item, value));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnGetImsConfigInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnGetImsConfigInner entry");
    auto item = static_cast<ImsConfigItem>(data.ReadInt32());
    reply.WriteInt32(GetImsConfig(item));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetImsFeatureValueInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetImsFeatureValueInner entry");
    auto type = static_cast<FeatureType>(data.ReadInt32());
    int32_t value = data.ReadInt32();
    reply.WriteInt32(SetImsFeatureValue(type, value));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnGetImsFeatureValueInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnGetImsFeatureValueInner entry");
    auto type = static_cast<FeatureType>(data.ReadInt32());
    reply.WriteInt32(GetImsFeatureValue(type));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetVolteEnhanceModeInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetVolteEnhanceModeInner entry");
    bool value = data.ReadBool();
    reply.WriteInt32(SetVolteEnhanceMode(value));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnGetVolteEnhanceModeInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnGetVolteEnhanceModeInner entry");
    reply.WriteInt32(GetVolteEnhanceMode());
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnCtrlCameraInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnCtrlCameraInner entry");
    std::u16string cameraId = data.ReadString16();
    std::u16string callingPackage = data.ReadString16();
    int32_t callingUid = data.ReadInt32();
    int32_t callingPid = data.ReadInt32();
    reply.WriteInt32(CtrlCamera(cameraId, callingPackage, callingUid, callingPid));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetPreviewWindowInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetPreviewWindowInner entry");
    int32_t x = data.ReadInt32();
    int32_t y = data.ReadInt32();
    int32_t z = data.ReadInt32();
    int32_t width = data.ReadInt32();
    int32_t height = data.ReadInt32();

    reply.WriteInt32(SetPreviewWindow(x, y, z, width, height));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetDisplayWindowInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetDisplayWindowInner entry");
    int32_t x = data.ReadInt32();
    int32_t y = data.ReadInt32();
    int32_t z = data.ReadInt32();
    int32_t width = data.ReadInt32();
    int32_t height = data.ReadInt32();
    reply.WriteInt32(SetDisplayWindow(x, y, z, width, height));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetCameraZoomInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetCameraZoomInner entry");
    float zoomRatio = data.ReadFloat();
    reply.WriteInt32(SetCameraZoom(zoomRatio));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetPauseImageInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetPauseImageInner entry");
    std::u16string imagePath = data.ReadString16();
    reply.WriteInt32(SetPauseImage(imagePath));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetDeviceDirectionInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetDeviceDirectionInner entry");
    int32_t rotation = data.ReadInt32();
    reply.WriteInt32(SetDeviceDirection(rotation));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnRegisterCellularCallBackInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnRegisterCellularCallBackInner entry.");
    int32_t result = TELEPHONY_ERR_LOCAL_PTR_NULL;
    auto remote = data.ReadRemoteObject();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsStub::OnRegisterCellularCallBackInner return, remote is nullptr.");
        reply.WriteInt32(result);
        return result;
    }
    auto callback = iface_cast<ImsCallback>(remote);
    if (callback == nullptr) {
        TELEPHONY_LOGE("OnRegisterCellularCallBackInner return, callback is nullptr.");
        return result;
    }
    result = RegisterCellularCallBack(callback);
    reply.WriteInt32(result);
    return result;
}

int32_t ImsStub::OnIsCallBackExistsInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnIsCallBackExistsInner entry.");
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("OnIsCallBackExistsInner return, error type: GetInstance() is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    reply.WriteBool(IsCallBackExists());
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnGetImsCallsDataRequestInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnGetImsDataRequestInner entry.");
    int32_t slotId = data.ReadInt32();
    int64_t lastCallsDataFlag = data.ReadInt64();
    reply.WriteInt32(GetImsCallsDataRequest(slotId, lastCallsDataFlag));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetMuteInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetMuteInner entry.");
    int32_t slotId = data.ReadInt32();
    int32_t mute = data.ReadInt32();
    reply.WriteInt32(SetMute(slotId, mute));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnGetMuteInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnGetMuteInner entry.");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetMute(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnGetEmergencyCallListInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnGetEmergencyCallListInner entry.");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetEmergencyCallList(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnGetCallFailReasonInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnGetCallFailReasonInner entry.");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetCallFailReason(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnInquireClipInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnInquireClipInner entry.");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(InquireClip(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetClirInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetClirInner entry.");
    int32_t slotId = data.ReadInt32();
    int32_t action = data.ReadInt32();
    reply.WriteInt32(SetClir(slotId, action));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnInquireClirInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnInquireClirInner entry.");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(InquireClir(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetCallTransferInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetCallTransferInner entry.");
    int32_t slotId = data.ReadInt32();
    int32_t reason = data.ReadInt32();
    int32_t mode = data.ReadInt32();
    std::string transferNum = data.ReadString();
    int32_t classType = data.ReadInt32();
    reply.WriteInt32(SetCallTransfer(slotId, reason, mode, transferNum, classType));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnGetCallTransferInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnGetCallTransferInner entry.");
    int32_t slotId = data.ReadInt32();
    int32_t reason = data.ReadInt32();
    reply.WriteInt32(GetCallTransfer(slotId, reason));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetCallRestrictionInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetCallRestrictionInner entry.");
    int32_t slotId = data.ReadInt32();
    std::string fac = data.ReadString();
    int32_t mode = data.ReadInt32();
    std::string pw = data.ReadString();
    reply.WriteInt32(SetCallRestriction(slotId, fac, mode, pw));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnGetCallRestrictionInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnGetCallRestrictionInner entry.");
    int32_t slotId = data.ReadInt32();
    std::string fac = data.ReadString();
    reply.WriteInt32(GetCallRestriction(slotId, fac));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnSetCallWaitingInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnSetCallWaitingInner entry.");
    int32_t slotId = data.ReadInt32();
    bool activate = data.ReadBool();
    reply.WriteInt32(SetCallWaiting(slotId, activate));
    return TELEPHONY_SUCCESS;
}

int32_t ImsStub::OnGetCallWaitingInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("ImsStub::OnGetCallWaitingInner entry.");
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetCallWaiting(slotId));
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS
