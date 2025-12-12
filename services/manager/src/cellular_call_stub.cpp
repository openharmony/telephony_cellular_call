/*
 * Copyright (C) 2021-2023 Huawei Device Co., Ltd.
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

#include "cellular_call_stub.h"

#include "call_manager_errors.h"
#include "call_status_callback_proxy.h"
#include "emergency_utils.h"
#include "ipc_skeleton.h"
#include "i_call_status_callback.h"
#include "telephony_log_wrapper.h"
#include "telephony_permission.h"

namespace OHOS {
namespace Telephony {
const int32_t MAX_SIZE = 10;
const int32_t MAX_ECC_SIZE = 1000;
const int32_t FOUNDATION_UID = 5523;
const int32_t MAX_CALL_NUM = 10;

int32_t CellularCallStub::OnRemoteRequest(
    uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    std::u16string myDescriptor = CellularCallStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (myDescriptor != remoteDescriptor) {
        TELEPHONY_LOGE("descriptor checked fail");
        return TELEPHONY_ERR_DESCRIPTOR_MISMATCH;
    }

    auto itFunc = requestFuncMap_.find(static_cast<CellularCallInterfaceCode>(code));
    if (itFunc != requestFuncMap_.end()) {
        auto callingUid = IPCSkeleton::GetCallingUid();
        if (callingUid != FOUNDATION_UID &&
            !TelephonyPermission::CheckPermission(Permission::CONNECT_CELLULAR_CALL_SERVICE)) {
            TELEPHONY_LOGE("Check permission failed, no CONNECT_CELLULAR_CALL_SERVICE permisson.");
            return TELEPHONY_ERR_PERMISSION_ERR;
        }
        auto requestFunc = itFunc->second;
        if (requestFunc != nullptr) {
            return requestFunc(data, reply);
        }
    }
    TELEPHONY_LOGI("CellularCallStub::OnRemoteRequest, default case, need check.");
    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

CellularCallStub::CellularCallStub()
{
    TELEPHONY_LOGI("CellularCallStub::CellularCallStub");
    InitFuncMap();
}

CellularCallStub::~CellularCallStub()
{
    TELEPHONY_LOGI("CellularCallStub::~CellularCallStub");
    requestFuncMap_.clear();
}

void CellularCallStub::InitFuncMap()
{
    InitDialFuncMap();
    InitDtmfFuncMap();
    InitConfigFuncMap();
    InitVideoFuncMap();
    InitSupplementFuncMap();
}

void CellularCallStub::InitDialFuncMap()
{
    requestFuncMap_[CellularCallInterfaceCode::DIAL] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnDialInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::HANG_UP] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnHangUpInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::REJECT] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnRejectInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::ANSWER] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnAnswerInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::EMERGENCY_CALL] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnIsEmergencyPhoneNumberInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_EMERGENCY_CALL_LIST] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetEmergencyCallList(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::HOLD_CALL] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnHoldCallInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::UN_HOLD_CALL] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnUnHoldCallInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SWITCH_CALL] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSwitchCallInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::COMBINE_CONFERENCE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnCombineConferenceInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SEPARATE_CONFERENCE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSeparateConferenceInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::INVITE_TO_CONFERENCE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnInviteToConferenceInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::KICK_OUT_CONFERENCE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnKickOutFromConferenceInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::HANG_UP_ALL_CONNECTION] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnHangUpAllConnectionInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_READY_TO_CALL] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetReadyToCallInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::CLEAR_ALL_CALLS] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnClearAllCallsInner(data, reply); };
}

void CellularCallStub::InitDtmfFuncMap()
{
    requestFuncMap_[CellularCallInterfaceCode::START_DTMF] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnStartDtmfInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::STOP_DTMF] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnStopDtmfInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::POST_DIAL_PROCEED] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnPostDialProceedInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SEND_DTMF] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSendDtmfInner(data, reply); };
#ifdef SUPPORT_RTT_CALL
    requestFuncMap_[CellularCallInterfaceCode::START_RTT] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnStartRttInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::STOP_RTT] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnStopRttInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::UPDATE_RTT_CALL_MODE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnUpdateImsRttCallModeInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::RTT_CAPABILITY_SETTING] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetRttCapabilityInner(data, reply); };
#endif
}

void CellularCallStub::InitConfigFuncMap()
{
    requestFuncMap_[CellularCallInterfaceCode::SET_DOMAIN_PREFERENCE_MODE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetDomainPreferenceModeInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::GET_DOMAIN_PREFERENCE_MODE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetDomainPreferenceModeInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_IMS_SWITCH_STATUS] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetImsSwitchStatusInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::GET_IMS_SWITCH_STATUS] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetImsSwitchStatusInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::GET_CARRIER_VT_CONFIG] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetCarrierVtConfigInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_VONR_SWITCH_STATUS] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetVoNRStateInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::GET_VONR_SWITCH_STATUS] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetVoNRStateInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_IMS_CONFIG_STRING] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetImsConfigStringInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_IMS_CONFIG_INT] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetImsConfigIntInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::GET_IMS_CONFIG] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetImsConfigInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_IMS_FEATURE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetImsFeatureValueInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::GET_IMS_FEATURE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetImsFeatureValueInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_MUTE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetMuteInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::GET_MUTE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetMuteInner(data, reply); };
}

void CellularCallStub::InitVideoFuncMap()
{
    requestFuncMap_[CellularCallInterfaceCode::CTRL_CAMERA] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnControlCameraInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_PREVIEW_WINDOW] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetPreviewWindowInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_DISPLAY_WINDOW] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetDisplayWindowInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_CAMERA_ZOOM] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetCameraZoomInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_PAUSE_IMAGE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetPausePictureInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_DEVICE_DIRECTION] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetDeviceDirectionInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SEND_CALL_MEDIA_MODE_REQUEST] =
        [this](MessageParcel &data, MessageParcel &reply) {
            return OnSendUpdateCallMediaModeRequestInner(data, reply);
        };
    requestFuncMap_[CellularCallInterfaceCode::SEND_CALL_MEDIA_MODE_RESPONSE] =
        [this](MessageParcel &data, MessageParcel &reply) {
            return OnSendUpdateCallMediaModeResponseInner(data, reply);
        };
    requestFuncMap_[CellularCallInterfaceCode::CANCEL_CALL_UPGRADE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnCancelCallUpgradeInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::REQUEST_CAMERA_CAPABILITY] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnRequestCameraCapabilitiesInner(data, reply); };
}

void CellularCallStub::InitSupplementFuncMap()
{
    requestFuncMap_[CellularCallInterfaceCode::SET_CALL_TRANSFER] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetCallTransferInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::GET_CALL_TRANSFER] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetCallTransferInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::CAN_SET_CALL_TRANSFER_TIME] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnCanSetCallTransferTimeInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_CALL_WAITING] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetCallWaitingInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::GET_CALL_WAITING] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetCallWaitingInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_CALL_RESTRICTION] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetCallRestrictionInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::GET_CALL_RESTRICTION] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetCallRestrictionInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SET_CALL_RESTRICTION_PWD] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSetCallRestrictionPasswordInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::REGISTER_CALLBACK] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnRegisterCallBackInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::UNREGISTER_CALLBACK] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnUnRegisterCallBackInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::CLOSE_UNFINISHED_USSD] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnCloseUnFinishedUssdInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::GET_VIDEO_CALL_WAITING] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnGetVideoCallWaitingInner(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::SEND_USSD_RESPONSE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnSendUssdResponse(data, reply); };
    requestFuncMap_[CellularCallInterfaceCode::IS_MMI_CODE] =
        [this](MessageParcel &data, MessageParcel &reply) { return OnIsMmiCodeInner(data, reply); };
}

int32_t CellularCallStub::OnDialInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnDialInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnRemoteRequest data size error");
        return TELEPHONY_ERR_FAIL;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnDialInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    reply.WriteInt32(Dial(*pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnIsMmiCodeInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("OnIsMmiCodeInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    std::string number = data.ReadString();
    bool result = IsMmiCode(slotId, number);
    if (!reply.WriteBool(result)) {
        TELEPHONY_LOGE("write reply failed.");
    }
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnHangUpInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnHangUpInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnRemoteRequest data size error");
        return TELEPHONY_ERR_FAIL;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnHangUpInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    auto type = static_cast<CallSupplementType>(data.ReadInt32());

    reply.WriteInt32(HangUp(*pCallInfo, type));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnRejectInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnRejectInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnRemoteRequest data size error");
        return TELEPHONY_ERR_FAIL;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnRejectInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    reply.WriteInt32(Reject(*pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnAnswerInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnAnswerInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnRemoteRequest data size error");
        return TELEPHONY_ERR_FAIL;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnAnswerInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    reply.WriteInt32(Answer(*pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnIsEmergencyPhoneNumberInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGD("CellularCallStub::OnIsEmergencyPhoneNumberInner entry.");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnIsEmergencyPhoneNumberInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    std::string phoneNum = data.ReadString();
    bool enabled = false;
    int32_t ret = IsEmergencyPhoneNumber(slotId, phoneNum, enabled);
    if (!reply.WriteInt32(ret)) {
        TELEPHONY_LOGE("fail to write ret");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!reply.WriteBool(enabled)) {
        TELEPHONY_LOGE("fail to write enabled");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetEmergencyCallList(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetEmergencyCallList entry.");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetEmergencyCallList data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t len = data.ReadInt32();
    if (len <= 0 || len >= MAX_ECC_SIZE) {
        TELEPHONY_LOGE("CellularCallStub::OnSetEmergencyCallList ecc size error");
        return TELEPHONY_ERR_FAIL;
    }
    std::vector<EmergencyCall> eccVec;
    for (int i = 0; i < len; i++) {
        EmergencyCall emergencyCall;
        emergencyCall.eccNum = data.ReadString();
        emergencyCall.mcc = data.ReadString();
        emergencyCall.eccType = static_cast<EccType>(data.ReadInt32());
        emergencyCall.simpresent = static_cast<SimpresentType>(data.ReadInt32());
        emergencyCall.abnormalService = static_cast<AbnormalServiceType>(data.ReadInt32());
        eccVec.push_back(emergencyCall);
    }
    for (auto ecc : eccVec) {
        TELEPHONY_LOGE("OnSetEmergencyCallList, data: eccNum %{public}s mcc %{public}s",
            ecc.eccNum.c_str(), ecc.mcc.c_str());
    }
    reply.WriteInt32(SetEmergencyCallList(slotId, eccVec));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnRegisterCallBackInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnRegisterCallBackInner entry.");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnRemoteRequest data size error");
        return TELEPHONY_ERR_FAIL;
    }

    int32_t result = TELEPHONY_ERR_LOCAL_PTR_NULL;
    auto remote = data.ReadRemoteObject();
    if (remote == nullptr) {
        TELEPHONY_LOGE("CellularCallStub::OnRegisterCallBackInner return, remote is nullptr.");
        reply.WriteInt32(result);
        return result;
    }
    result = RegisterCallManagerCallBack(iface_cast<ICallStatusCallback>(remote));

    reply.WriteInt32(result);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnUnRegisterCallBackInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnUnRegisterCallBackInner entry.");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnRemoteRequest data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t result = UnRegisterCallManagerCallBack();

    reply.WriteInt32(result);
    return result;
}

int32_t CellularCallStub::OnHoldCallInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnHoldCallInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnRemoteRequest data size error");
        return TELEPHONY_ERR_FAIL;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnHoldCallInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    reply.WriteInt32(HoldCall(*pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnUnHoldCallInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnUnHoldCallInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnRemoteRequest data size error");
        return TELEPHONY_ERR_FAIL;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnUnHoldCallInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    reply.WriteInt32(UnHoldCall(*pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSwitchCallInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSwitchCallInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnRemoteRequest data size error");
        return TELEPHONY_ERR_FAIL;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnSwitchCallInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    reply.WriteInt32(SwitchCall(*pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnCombineConferenceInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnCombineConferenceInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnCombineConferenceInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnCombineConferenceInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    reply.WriteInt32(CombineConference(*pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSeparateConferenceInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSeparateConferenceInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSeparateConferenceInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnSeparateConferenceInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    reply.WriteInt32(SeparateConference(*pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnInviteToConferenceInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnInviteToConferenceInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnInviteToConferenceInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

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

int32_t CellularCallStub::OnKickOutFromConferenceInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnKickOutFromConferenceInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnKickOutFromConferenceInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnKickOutFromConferenceInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(KickOutFromConference(*pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnHangUpAllConnectionInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnHangUpAllConnectionInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("OnHangUpAllConnectionInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    reply.WriteInt32(HangUpAllConnection());
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetReadyToCallInner(MessageParcel &data, MessageParcel &reply)
{
    int32_t slotId = data.ReadInt32();
    int32_t callType = data.ReadInt32();
    bool isReadyToCall = data.ReadBool();
    int32_t error = SetReadyToCall(slotId, callType, isReadyToCall);
    if (!reply.WriteInt32(error)) {
        TELEPHONY_LOGE("OnSetReadyToCallInner WriteInt32 fail");
        return TELEPHONY_ERR_WRITE_REPLY_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSendUpdateCallMediaModeRequestInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSendUpdateCallMediaModeRequestInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("OnSendUpdateCallMediaModeRequestInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnSendUpdateCallMediaModeRequestInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    auto mode = static_cast<ImsCallMode>(data.ReadInt32());

    reply.WriteInt32(SendUpdateCallMediaModeRequest(*pCallInfo, mode));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSendUpdateCallMediaModeResponseInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSendUpdateCallMediaModeResponseInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("OnSendUpdateCallMediaModeResponseInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnSendUpdateCallMediaModeResponseInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    auto mode = static_cast<ImsCallMode>(data.ReadInt32());

    reply.WriteInt32(SendUpdateCallMediaModeResponse(*pCallInfo, mode));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnCancelCallUpgradeInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnCancelCallUpgradeInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("OnCancelCallUpgradeInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t callIndex = data.ReadInt32();
    reply.WriteInt32(CancelCallUpgrade(slotId, callIndex));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnRequestCameraCapabilitiesInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnRequestCameraCapabilitiesInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("OnRequestCameraCapabilitiesInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t callIndex = data.ReadInt32();
    reply.WriteInt32(RequestCameraCapabilities(slotId, callIndex));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnStartDtmfInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnStartDtmfInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnStartDtmfInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    char pDtmf = data.ReadInt8();
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnStartDtmfInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    reply.WriteInt32(StartDtmf(pDtmf, *pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnStopDtmfInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnStopDtmfInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnStopDtmfInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnStopDtmfInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    reply.WriteInt32(StopDtmf(*pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnPostDialProceedInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnPostDialProceedInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnPostDialProceedInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    auto info = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (info == nullptr) {
        TELEPHONY_LOGE("OnStopDtmfInner return, info is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    bool proceed = data.ReadBool();

    reply.WriteInt32(PostDialProceed(*info, proceed));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSendDtmfInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSendDtmfInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSendDtmfInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    char pDtmf = data.ReadInt8();
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnSendDtmfInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    reply.WriteInt32(SendDtmf(pDtmf, *pCallInfo));
    return TELEPHONY_SUCCESS;
}

#ifdef SUPPORT_RTT_CALL
int32_t CellularCallStub::OnStartRttInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnStartRttInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnStartRttInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t callId = data.ReadInt32();

    reply.WriteInt32(StartRtt(slotId, callId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnStopRttInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnStopRttInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnStopRttInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t callId = data.ReadInt32();

    reply.WriteInt32(StopRtt(slotId, callId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnUpdateImsRttCallModeInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnRttCallModifyInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnRttCallModifyInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t callId = data.ReadInt32();
    auto mode = static_cast<ImsRTTCallMode>(data.ReadInt32());

    reply.WriteInt32(UpdateImsRttCallMode(slotId, callId, mode));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetRttCapabilityInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetRttCapabilityInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetRttCapabilityInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    bool isEnable = data.ReadBool();

    reply.WriteInt32(SetRttCapability(slotId, isEnable));
    return TELEPHONY_SUCCESS;
}
#endif

int32_t CellularCallStub::OnSetCallTransferInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetCallTransferInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetCallTransferInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    auto pCTInfo = (CallTransferInfo *)data.ReadRawData(sizeof(CallTransferInfo));
    if (pCTInfo == nullptr) {
        TELEPHONY_LOGE("OnSetCallTransferInner return, pCTInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    reply.WriteInt32(SetCallTransferInfo(slotId, *pCTInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnCanSetCallTransferTimeInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    bool result = data.ReadBool();

    int32_t callResult = CanSetCallTransferTime(slotId, result);
    reply.WriteBool(result);
    reply.WriteInt32(callResult);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetCallTransferInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetCallTransferInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetCallTransferInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    auto type = static_cast<CallTransferType>(data.ReadInt32());

    reply.WriteInt32(GetCallTransferInfo(slotId, type));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetCallWaitingInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetCallWaitingInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetCallWaitingInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    bool enable = data.ReadBool();

    reply.WriteInt32(SetCallWaiting(slotId, enable));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetCallWaitingInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetCallWaitingInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetCallWaitingInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    TELEPHONY_LOGI("CellularCallStub::OnGetCallWaitingInner data.ReadInt32()");
    reply.WriteInt32(GetCallWaiting(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetVideoCallWaitingInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetVideoCallWaitingInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetVideoCallWaitingInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    TELEPHONY_LOGI("CellularCallStub::OnGetVideoCallWaitingInner data.ReadInt32()");
    bool enable = false;
    int32_t result = GetVideoCallWaiting(slotId, enable);
    reply.WriteBool(enable);
    reply.WriteInt32(result);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetCallRestrictionInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetCallRestrictionInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetCallRestrictionInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    auto pCRInfo = (CallRestrictionInfo *)data.ReadRawData(sizeof(CallRestrictionInfo));
    if (pCRInfo == nullptr) {
        TELEPHONY_LOGE("OnSetCallRestrictionInner return, pCRInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    reply.WriteInt32(SetCallRestriction(slotId, *pCRInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetCallRestrictionInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetCallRestrictionInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetCallRestrictionInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    auto facType = static_cast<CallRestrictionType>(data.ReadInt32());

    reply.WriteInt32(GetCallRestriction(slotId, facType));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetCallRestrictionPasswordInner(MessageParcel &data, MessageParcel &reply)
{
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    auto facType = static_cast<CallRestrictionType>(data.ReadInt32());
    auto oldPassword = data.ReadCString();
    auto newPassword = data.ReadCString();

    reply.WriteInt32(SetCallRestrictionPassword(slotId, facType, oldPassword, newPassword));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetDomainPreferenceModeInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetDomainPreferenceModeInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetDomainPreferenceModeInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t mode = data.ReadInt32();

    reply.WriteInt32(SetDomainPreferenceMode(slotId, mode));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetDomainPreferenceModeInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetDomainPreferenceModeInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetDomainPreferenceModeInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();

    reply.WriteInt32(GetDomainPreferenceMode(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetImsSwitchStatusInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetImsSwitchStatusInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetImsSwitchStatusInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    bool active = data.ReadBool();

    reply.WriteInt32(SetImsSwitchStatus(slotId, active));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetImsSwitchStatusInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGD("CellularCallStub::OnGetImsSwitchStatusInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetImsSwitchStatusInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    bool enabled;
    int32_t result = GetImsSwitchStatus(slotId, enabled);
    reply.WriteBool(enabled);
    reply.WriteInt32(result);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetCarrierVtConfigInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGD("CellularCallStub::OnGetCarrierVtConfigInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetCarrierVtConfigInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    bool enabled;
    int32_t result = GetCarrierVtConfig(slotId, enabled);
    reply.WriteBool(enabled);
    reply.WriteInt32(result);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetVoNRStateInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetVoNRSwitchStatusInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetVoNRSwitchStatusInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t state = data.ReadInt32();
    reply.WriteInt32(SetVoNRState(slotId, state));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetVoNRStateInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetVoNRSwitchStatusInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetVoNRSwitchStatusInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t state;
    int32_t result = GetVoNRState(slotId, state);
    reply.WriteInt32(state);
    reply.WriteInt32(result);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetImsConfigStringInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetImsConfigStringInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetImsConfigStringInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    auto item = static_cast<ImsConfigItem>(data.ReadInt32());
    std::string value = data.ReadString();

    reply.WriteInt32(SetImsConfig(slotId, item, value));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetImsConfigIntInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetImsConfigIntInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetImsConfigIntInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    auto item = static_cast<ImsConfigItem>(data.ReadInt32());
    int32_t value = data.ReadInt32();

    reply.WriteInt32(SetImsConfig(slotId, item, value));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetImsConfigInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetImsConfigInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetImsConfigInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    auto item = static_cast<ImsConfigItem>(data.ReadInt32());

    reply.WriteInt32(GetImsConfig(slotId, item));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetImsFeatureValueInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetImsFeatureValueInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetImsFeatureValueInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    auto type = static_cast<FeatureType>(data.ReadInt32());
    int32_t value = data.ReadInt32();

    reply.WriteInt32(SetImsFeatureValue(slotId, type, value));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetImsFeatureValueInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetImsFeatureValueInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetImsFeatureValueInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    auto type = static_cast<FeatureType>(data.ReadInt32());

    reply.WriteInt32(GetImsFeatureValue(slotId, type));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnControlCameraInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnControlCameraInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnControlCameraInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t callIndex = data.ReadInt32();
    std::string cameraId = data.ReadString();
    reply.WriteInt32(ControlCamera(slotId, callIndex, cameraId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetPreviewWindowInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetPreviewWindowInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetPreviewWindowInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t callIndex = data.ReadInt32();
    const std::string surfaceID = data.ReadString();
    sptr<Surface> surface = nullptr;
    sptr<IRemoteObject> object = data.ReadRemoteObject();
    if (object != nullptr) {
        sptr<IBufferProducer> producer = iface_cast<IBufferProducer>(object);
        surface = Surface::CreateSurfaceAsProducer(producer);
    }
    TELEPHONY_LOGI("surfaceId:%{public}s", surfaceID.c_str());
    reply.WriteInt32(SetPreviewWindow(slotId, callIndex, surfaceID, surface));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetDisplayWindowInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetDisplayWindowInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetDisplayWindowInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t callIndex = data.ReadInt32();
    const std::string surfaceID = data.ReadString();
    sptr<Surface> surface = nullptr;
    sptr<IRemoteObject> object = data.ReadRemoteObject();
    if (object != nullptr) {
        sptr<IBufferProducer> producer = iface_cast<IBufferProducer>(object);
        surface = Surface::CreateSurfaceAsProducer(producer);
    }
    TELEPHONY_LOGI("surfaceId:%{public}s", surfaceID.c_str());
    reply.WriteInt32(SetDisplayWindow(slotId, callIndex, surfaceID, surface));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetCameraZoomInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetCameraZoomInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetCameraZoomInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    float zoomRatio = data.ReadFloat();

    reply.WriteInt32(SetCameraZoom(zoomRatio));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetPausePictureInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetPausePictureInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetPausePictureInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t callIndex = data.ReadInt32();
    std::string imagePath = data.ReadString();
    reply.WriteInt32(SetPausePicture(slotId, callIndex, imagePath));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetDeviceDirectionInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetDeviceDirectionInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetDeviceDirectionInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t callIndex = data.ReadInt32();
    int32_t rotation = data.ReadInt32();
    reply.WriteInt32(SetDeviceDirection(slotId, callIndex, rotation));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetMuteInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetMuteInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetMuteInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t mute = data.ReadInt32();

    reply.WriteInt32(SetMute(slotId, mute));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetMuteInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetMuteInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetMuteInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();

    reply.WriteInt32(GetMute(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnCloseUnFinishedUssdInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnCloseUnFinishedUssdInner entry");
    int32_t size = data.ReadInt32();
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnCloseUnFinishedUssdInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();

    reply.WriteInt32(CloseUnFinishedUssd(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnClearAllCallsInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnClearAllCallsInner entry");
    int32_t size = data.ReadInt32();
    if (size <= 0 || size > MAX_CALL_NUM) {
        TELEPHONY_LOGE("data size error");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    std::vector<CellularCallInfo> callInfos;
    for (int32_t i = 0; i < size; i++) {
        CellularCallInfo *callInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
        if (callInfo != nullptr) {
            callInfos.push_back(*callInfo);
        }
    }
    reply.WriteInt32(ClearAllCalls(callInfos));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSendUssdResponse(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSendUssdResponse entry");
    int32_t size = data.ReadInt32();
    if (size <= 0 || size > MAX_CALL_NUM) {
        TELEPHONY_LOGE("data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    std::string content = data.ReadString();
    bool enable = false;
    int32_t ret = SendUssdResponse(slotId, content);
    if (!reply.WriteInt32(ret)) {
        TELEPHONY_LOGE("fail to write ret");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!reply.WriteBool(enable)) {
        TELEPHONY_LOGE("fail to write enabled");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS
