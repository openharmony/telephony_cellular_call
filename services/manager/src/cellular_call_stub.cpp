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

#include "cellular_call_stub.h"
#include "cellular_call_register.h"

#include "cs_control.h"
#include "ims_control.h"
#include "emergency_utils.h"
#include "i_call_status_callback.h"
#include "module_service_utils.h"

namespace OHOS {
namespace Telephony {
int32_t CellularCallStub::OnRemoteRequest(
    uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    std::u16string myDescriptor = CellularCallStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (myDescriptor != remoteDescriptor) {
        TELEPHONY_LOGE("descriptor checked fail");
        return TELEPHONY_ERR_DESCRIPTOR_MISMATCH;
    }

    auto itFunc = requestFuncMap_.find(static_cast<OperationType>(code));
    if (itFunc != requestFuncMap_.end()) {
        auto requestFunc = itFunc->second;
        if (requestFunc != nullptr) {
            return (this->*requestFunc)(data, reply);
        }
    }
    TELEPHONY_LOGI("CellularCallStub::OnRemoteRequest, default case, need check.");
    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

CellularCallStub::CellularCallStub()
{
    Init();
    TELEPHONY_LOGI("CellularCallStub::CellularCallStub");
    requestFuncMap_[OperationType::DIAL] = &CellularCallStub::OnDialInner;
    requestFuncMap_[OperationType::HANG_UP] = &CellularCallStub::OnHangUpInner;
    requestFuncMap_[OperationType::REJECT] = &CellularCallStub::OnRejectInner;
    requestFuncMap_[OperationType::ANSWER] = &CellularCallStub::OnAnswerInner;
    requestFuncMap_[OperationType::EMERGENCY_CALL] = &CellularCallStub::OnIsEmergencyPhoneNumberInner;
    requestFuncMap_[OperationType::HOLD_CALL] = &CellularCallStub::OnHoldCallInner;
    requestFuncMap_[OperationType::UN_HOLD_CALL] = &CellularCallStub::OnUnHoldCallInner;
    requestFuncMap_[OperationType::SWITCH_CALL] = &CellularCallStub::OnSwitchCallInner;
    requestFuncMap_[OperationType::COMBINE_CONFERENCE] = &CellularCallStub::OnCombineConferenceInner;
    requestFuncMap_[OperationType::SEPARATE_CONFERENCE] = &CellularCallStub::OnSeparateConferenceInner;
    requestFuncMap_[OperationType::CALL_SUPPLEMENT] = &CellularCallStub::OnCallSupplementInner;
    requestFuncMap_[OperationType::REGISTER_CALLBACK] = &CellularCallStub::OnRegisterCallBackInner;
    requestFuncMap_[OperationType::UNREGISTER_CALLBACK] = &CellularCallStub::OnUnRegisterCallBackInner;
    requestFuncMap_[OperationType::START_DTMF] = &CellularCallStub::OnStartDtmfInner;
    requestFuncMap_[OperationType::STOP_DTMF] = &CellularCallStub::OnStopDtmfInner;
    requestFuncMap_[OperationType::SEND_DTMF] = &CellularCallStub::OnSendDtmfInner;
    requestFuncMap_[OperationType::SEND_DTMF_STRING] = &CellularCallStub::OnSendDtmfStringInner;
    requestFuncMap_[OperationType::SET_CALL_TRANSFER] = &CellularCallStub::OnSetCallTransferInner;
    requestFuncMap_[OperationType::GET_CALL_TRANSFER] = &CellularCallStub::OnGetCallTransferInner;
    requestFuncMap_[OperationType::SET_CALL_WAITING] = &CellularCallStub::OnSetCallWaitingInner;
    requestFuncMap_[OperationType::GET_CALL_WAITING] = &CellularCallStub::OnGetCallWaitingInner;
    requestFuncMap_[OperationType::SET_CALL_RESTRICTION] = &CellularCallStub::OnSetCallRestrictionInner;
    requestFuncMap_[OperationType::GET_CALL_RESTRICTION] = &CellularCallStub::OnGetCallRestrictionInner;
    requestFuncMap_[OperationType::SET_CALL_PREFERENCE_MODE] = &CellularCallStub::OnSetCallPreferenceModeInner;
    requestFuncMap_[OperationType::GET_CALL_PREFERENCE_MODE] = &CellularCallStub::OnGetCallPreferenceModeInner;
    requestFuncMap_[OperationType::SET_LTE_IMS_SWITCH_STATUS] = &CellularCallStub::OnSetLteImsSwitchStatusInner;
    requestFuncMap_[OperationType::GET_LTE_IMS_SWITCH_STATUS] = &CellularCallStub::OnGetLteImsSwitchStatusInner;
    requestFuncMap_[OperationType::CTRL_CAMERA] = &CellularCallStub::OnCtrlCameraInner;
    requestFuncMap_[OperationType::SET_PREVIEW_WINDOW] = &CellularCallStub::OnSetPreviewWindowInner;
    requestFuncMap_[OperationType::SET_DISPLAY_WINDOW] = &CellularCallStub::OnSetDisplayWindowInner;
    requestFuncMap_[OperationType::SET_CAMERA_ZOOM] = &CellularCallStub::OnSetCameraZoomInner;
    requestFuncMap_[OperationType::SET_PAUSE_IMAGE] = &CellularCallStub::OnSetPauseImageInner;
    requestFuncMap_[OperationType::SET_DEVICE_DIRECTION] = &CellularCallStub::OnSetDeviceDirectionInner;
}

CellularCallStub::~CellularCallStub()
{
    TELEPHONY_LOGI("CellularCallStub::~CellularCallStub");
    requestFuncMap_.clear();
}

int32_t CellularCallStub::OnDialInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnDialInner DIAL");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("CellularCallStub::OnDialInner:size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnDialInner data size error");
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

int32_t CellularCallStub::OnHangUpInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnHangUpInner END");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("CellularCallStub::OnHangUpInner:size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnHangUpInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnHangUpInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(HangUp(*pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnRejectInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnRejectInner REJECT");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("CellularCallStub::OnRejectInner:size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnRejectInner data size error");
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
    TELEPHONY_LOGI("CellularCallStub::OnAnswerInner ANSWER");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("CellularCallStub::OnAnswerInner:size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnAnswerInner data size error");
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
    TELEPHONY_LOGI("CellularCallStub::OnIsEmergencyPhoneNumberInner EMERGENCY_CALL entry.");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnIsEmergencyPhoneNumberInner request size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnIsEmergencyPhoneNumberInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    std::string phoneNum = data.ReadString();
    int32_t slotId = data.ReadInt32();
    int32_t errorCode = data.ReadInt32();
    reply.WriteInt32(IsEmergencyPhoneNumber(phoneNum, slotId, errorCode));
    reply.WriteInt32(errorCode);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnRegisterCallBackInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnRegisterCallBackInner REGISTER_CALLBACK entry.");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnRegisterCallBackInner:size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnRegisterCallBackInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    int32_t result = TELEPHONY_ERR_LOCAL_PTR_NULL;
    auto remote = data.ReadRemoteObject();
    if (remote == nullptr) {
        TELEPHONY_LOGE("CellularCallStub::OnRegisterCallBackInner REGISTER_CALLBACK, remote is nullptr.");
        reply.WriteInt32(result);
        return result;
    }
    auto callback = iface_cast<ICallStatusCallback>(remote);
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CellularCallStub::RegisterCallBackInner return, instance is nullptr.");
        return result;
    }
    result = DelayedSingleton<CellularCallRegister>::GetInstance()->RegisterCallManagerCallBack(callback);
    reply.WriteInt32(result);
    return result;
}

int32_t CellularCallStub::OnUnRegisterCallBackInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::UnRegisterCallBackInner entry.");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("UnRegisterCallBackInner:size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnUnRegisterCallBackInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CellularCallStub::OnUnRegisterCallBackInner return, instance is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t result = DelayedSingleton<CellularCallRegister>::GetInstance()->UnRegisterCallManagerCallBack();
    reply.WriteInt32(result);
    return result;
}

int32_t CellularCallStub::OnHoldCallInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnHoldCallInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("CellularCallStub::OnHoldCallInner:size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnHoldCallInner data size error");
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
    TELEPHONY_LOGI("CellularCallStub::OnUnHoldCallInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("CellularCallStub::OnUnHoldCallInner:size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnUnHoldCallInner data size error");
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
    TELEPHONY_LOGI("CellularCallStub::SwitchCallInner start");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("CellularCallStub::OnSwitchCallInner:size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSwitchCallInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnUnHoldCallInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SwitchCall(*pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnCombineConferenceInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnCombineConferenceInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnCombineConferenceInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
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
    TELEPHONY_LOGI("CellularCallStub::OnSeparateConferenceInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnSeparateConferenceInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
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

int32_t CellularCallStub::OnCallSupplementInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnCallSupplementInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnCallSupplementInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("OnCallSupplementInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    auto type = static_cast<CallSupplementType>(data.ReadInt32());
    reply.WriteInt32(CallSupplement(type));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnStartDtmfInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnStartDtmfInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("CellularCallStub::OnStartDtmfInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnStartDtmfInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    char *pDtmf = (char *)(data.ReadCString());
    if (pDtmf == nullptr) {
        TELEPHONY_LOGE("OnStartDtmfInner return, pDtmf is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnStartDtmfInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(StartDtmf(*pDtmf, *pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnStopDtmfInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnStopDtmfInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("CellularCallStub::OnStopDtmfInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
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

int32_t CellularCallStub::OnSendDtmfInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSendDtmfInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnSendDtmfInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSendDtmfInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    char *pDtmf = (char *)(data.ReadCString());
    if (pDtmf == nullptr) {
        TELEPHONY_LOGE("OnSendDtmfInner return, pDtmf is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    auto pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        TELEPHONY_LOGE("OnSendDtmfInner return, pCallInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    reply.WriteInt32(SendDtmf(*pDtmf, *pCallInfo));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSendDtmfStringInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSendDtmfStringInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnSendDtmfStringInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSendDtmfStringInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    std::string dtmfCodeStr = data.ReadString();
    std::string phoneNum = data.ReadString();
    int32_t switchOn = data.ReadInt32();
    int32_t switchOff = data.ReadInt32();
    reply.WriteInt32(SendDtmfString(dtmfCodeStr, phoneNum, switchOn, switchOff));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetCallTransferInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetCallTransferInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnSetCallTransferInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetCallTransferInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    auto pCTInfo = (CallTransferInfo *)data.ReadRawData(sizeof(CallTransferInfo));
    if (pCTInfo == nullptr) {
        TELEPHONY_LOGE("OnSetCallTransferInner return, pCTInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(SetCallTransferInfo(*pCTInfo, slotId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetCallTransferInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetCallTransferInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnGetCallTransferInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetCallTransferInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    auto type = static_cast<CallTransferType>(data.ReadInt32());
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetCallTransferInfo(type, slotId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetCallWaitingInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetCallWaitingInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnSetCallWaitingInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetCallWaitingInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    bool enable = data.ReadBool();
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(SetCallWaiting(enable, slotId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetCallWaitingInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetCallWaitingInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnGetCallWaitingInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
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

int32_t CellularCallStub::OnSetCallRestrictionInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetCallRestrictionInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnSetCallRestrictionInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetCallRestrictionInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    auto pCRInfo = (CallRestrictionInfo *)data.ReadRawData(sizeof(CallRestrictionInfo));
    if (pCRInfo == nullptr) {
        TELEPHONY_LOGE("OnSetCallRestrictionInner return, pCRInfo is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(SetCallRestriction(*pCRInfo, slotId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetCallRestrictionInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetCallRestrictionInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnGetCallRestrictionInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetCallRestrictionInner data size error");
        return TELEPHONY_ERR_FAIL;
    }

    auto facType = static_cast<CallRestrictionType>(data.ReadInt32());
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetCallRestriction(facType, slotId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetCallPreferenceModeInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetCallPreferenceModeInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnSetCallPreferenceModeInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetCallPreferenceModeInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    int32_t mode = data.ReadInt32();
    reply.WriteInt32(SetCallPreferenceMode(slotId, mode));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetCallPreferenceModeInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetCallPreferenceModeInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnGetCallPreferenceModeInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetCallPreferenceModeInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetCallPreferenceMode(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetLteImsSwitchStatusInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetLteImsSwitchStatusInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnSetLteImsSwitchStatusInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetLteImsSwitchStatusInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    bool active = data.ReadBool();
    reply.WriteInt32(SetLteImsSwitchStatus(slotId, active));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnGetLteImsSwitchStatusInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnGetLteImsSwitchStatusInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnGetLteImsSwitchStatusInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnGetLteImsSwitchStatusInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(GetLteImsSwitchStatus(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnCtrlCameraInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnCtrlCameraInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnCtrlCameraInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnCtrlCameraInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    std::u16string cameraId = data.ReadString16();
    std::u16string callingPackage = data.ReadString16();
    int32_t callingUid = data.ReadInt32();
    int32_t callingPid = data.ReadInt32();

    reply.WriteInt32(CtrlCamera(cameraId, callingPackage, callingUid, callingPid));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetPreviewWindowInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetPreviewWindowInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnSetPreviewWindowInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetPreviewWindowInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t x = data.ReadInt32();
    int32_t y = data.ReadInt32();
    int32_t z = data.ReadInt32();
    int32_t width = data.ReadInt32();
    int32_t height = data.ReadInt32();

    reply.WriteInt32(SetPreviewWindow(x, y, z, width, height));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetDisplayWindowInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetDisplayWindowInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnSetDisplayWindowInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetDisplayWindowInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t x = data.ReadInt32();
    int32_t y = data.ReadInt32();
    int32_t z = data.ReadInt32();
    int32_t width = data.ReadInt32();
    int32_t height = data.ReadInt32();

    reply.WriteInt32(SetDisplayWindow(x, y, z, width, height));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetCameraZoomInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetCameraZoomInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnSetCameraZoomInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetCameraZoomInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    float zoomRatio = data.ReadFloat();

    reply.WriteInt32(SetCameraZoom(zoomRatio));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetPauseImageInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetPauseImageInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnSetPauseImageInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetPauseImageInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    std::u16string imagePath = data.ReadString16();

    reply.WriteInt32(SetPauseImage(imagePath));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::OnSetDeviceDirectionInner(MessageParcel &data, MessageParcel &reply)
{
    TELEPHONY_LOGI("CellularCallStub::OnSetDeviceDirectionInner");
    int32_t size = data.ReadInt32();
    TELEPHONY_LOGI("OnSetDeviceDirectionInner size=%{public}u, MAX_SIZE=%{public}u\n", size, MAX_SIZE);
    size = ((size > MAX_SIZE) ? 0 : size);
    if (size <= 0) {
        TELEPHONY_LOGE("CellularCallStub::OnSetDeviceDirectionInner data size error");
        return TELEPHONY_ERR_FAIL;
    }
    int32_t rotation = data.ReadInt32();

    reply.WriteInt32(SetDeviceDirection(rotation));
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::Dial(const CellularCallInfo &callInfo)
{
    if (!IsValidSlotId(callInfo.slotId)) {
        TELEPHONY_LOGE("CellularCallStub::Dial return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    auto handler = GetHandler(slotId_);
    if (handler == nullptr) {
        TELEPHONY_LOGE("CellularCallStub::Dial return, handler is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    if (IsNeedIms()) {
        handler->SetCallType(CallType::TYPE_IMS);
        auto imsControl = GetImsControl(slotId_);
        if (imsControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::Dial return, imsControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return imsControl->Dial(callInfo);
    }

    handler->SetCallType(CallType::TYPE_CS);
    auto csControl = GetCsControl(slotId_);
    if (csControl == nullptr) {
        TELEPHONY_LOGE("CellularCallStub::Dial return, csControl is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    return csControl->Dial(callInfo);
}

int32_t CellularCallStub::HangUp(const CellularCallInfo &callInfo)
{
    if (!IsValidSlotId(callInfo.slotId)) {
        TELEPHONY_LOGE("CellularCallStub::HangUp return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    if (CallType::TYPE_CS == callInfo.callType) {
        auto csControl = GetCsControl(slotId_);
        if (csControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::HangUp return, csControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return csControl->HangUp(callInfo);
    } else if (CallType::TYPE_IMS == callInfo.callType) {
        auto imsControl = GetImsControl(slotId_);
        if (imsControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::HangUp return, imsControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        CallSupplementType type = CallSupplementType::TYPE_DEFAULT;
        return imsControl->HangUp(type, callInfo);
    }
    TELEPHONY_LOGE("CellularCallStub::HangUp return, call type error.");
    return TELEPHONY_ERR_ARGUMENT_INVALID;
}

int32_t CellularCallStub::Reject(const CellularCallInfo &callInfo)
{
    if (!IsValidSlotId(callInfo.slotId)) {
        TELEPHONY_LOGE("CellularCallStub::Reject return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    if (CallType::TYPE_CS == callInfo.callType) {
        auto control = GetCsControl(slotId_);
        if (control == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::Reject return, control is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return control->Reject(callInfo);
    } else if (CallType::TYPE_IMS == callInfo.callType) {
        auto imsControl = GetImsControl(slotId_);
        if (imsControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::Reject return, imsControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return imsControl->Reject(callInfo);
    }
    TELEPHONY_LOGE("CellularCallStub::Reject return, call type error.");
    return TELEPHONY_ERR_ARGUMENT_INVALID;
}

int32_t CellularCallStub::Answer(const CellularCallInfo &callInfo)
{
    if (!IsValidSlotId(callInfo.slotId)) {
        TELEPHONY_LOGE("CellularCallStub::Answer return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    if (CallType::TYPE_CS == callInfo.callType) {
        auto control = GetCsControl(slotId_);
        if (control == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::Answer return, control is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return control->Answer(callInfo);
    } else if (CallType::TYPE_IMS == callInfo.callType) {
        auto imsControl = GetImsControl(slotId_);
        if (imsControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::Answer return, imsControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return imsControl->Answer(callInfo);
    }
    TELEPHONY_LOGE("CellularCallStub::Answer return, call type error.");
    return TELEPHONY_ERR_ARGUMENT_INVALID;
}

int32_t CellularCallStub::RegisterCallManagerCallBack(const sptr<ICallStatusCallback> &callback)
{
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::UnRegisterCallManagerCallBack()
{
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallStub::HoldCall(const CellularCallInfo &callInfo)
{
    if (!IsValidSlotId(callInfo.slotId)) {
        TELEPHONY_LOGE("CellularCallStub::HoldCall return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    if (CallType::TYPE_IMS == callInfo.callType) {
        auto imsControl = GetImsControl(slotId_);
        if (imsControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::HoldCall return, imsControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return imsControl->HoldCall();
    } else if (CallType::TYPE_CS == callInfo.callType) {
        auto csControl = GetCsControl(slotId_);
        if (csControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::HoldCall return, csControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return csControl->HoldCall();
    }
    TELEPHONY_LOGE("CellularCallStub::HoldCall return, call type error.");
    return TELEPHONY_ERR_ARGUMENT_INVALID;
}

int32_t CellularCallStub::UnHoldCall(const CellularCallInfo &callInfo)
{
    if (!IsValidSlotId(callInfo.slotId)) {
        TELEPHONY_LOGE("CellularCallStub::UnHoldCall return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    if (CallType::TYPE_IMS == callInfo.callType) {
        auto imsControl = GetImsControl(slotId_);
        if (imsControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::UnHoldCall return, imsControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return imsControl->UnHoldCall();
    } else if (CallType::TYPE_CS == callInfo.callType) {
        auto csControl = GetCsControl(slotId_);
        if (csControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::UnHoldCall return, csControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return csControl->UnHoldCall();
    }
    TELEPHONY_LOGE("CellularCallStub::UnHoldCall return, call type error.");
    return TELEPHONY_ERR_ARGUMENT_INVALID;
}

int32_t CellularCallStub::SwitchCall(const CellularCallInfo &callInfo)
{
    if (!IsValidSlotId(callInfo.slotId)) {
        TELEPHONY_LOGE("CellularCallStub::SwitchCall return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    if (CallType::TYPE_IMS == callInfo.callType) {
        auto imsControl = GetImsControl(slotId_);
        if (imsControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::SwitchCall return, imsControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return imsControl->SwitchCall();
    } else if (CallType::TYPE_CS == callInfo.callType) {
        auto csControl = GetCsControl(slotId_);
        if (csControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::SwitchCall return, csControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return csControl->SwitchCall();
    }
    TELEPHONY_LOGE("CellularCallStub::SwitchCall return, call type error.");
    return TELEPHONY_ERR_ARGUMENT_INVALID;
}

int32_t CellularCallStub::CombineConference(const CellularCallInfo &callInfo)
{
    if (!IsValidSlotId(callInfo.slotId)) {
        TELEPHONY_LOGE("CellularCallStub::CombineConference return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    if (CallType::TYPE_IMS == callInfo.callType) {
        auto imsControl = GetImsControl(slotId_);
        if (imsControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::CombineConference return, imsControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return imsControl->CombineConference();
    } else if (CallType::TYPE_CS == callInfo.callType) {
        auto csControl = GetCsControl(slotId_);
        if (csControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::CombineConference return, csControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return csControl->CombineConference();
    }
    TELEPHONY_LOGE("CellularCallStub::CombineConference return, call type error.");
    return TELEPHONY_ERR_ARGUMENT_INVALID;
}

int32_t CellularCallStub::SeparateConference(const CellularCallInfo &callInfo)
{
    if (!IsValidSlotId(callInfo.slotId)) {
        TELEPHONY_LOGE("CellularCallStub::SeparateConference return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    if (CallType::TYPE_IMS == callInfo.callType) {
        auto imsControl = GetImsControl(slotId_);
        if (imsControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::SeparateConference return, imsControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
    } else if (CallType::TYPE_CS == callInfo.callType) {
        auto csControl = GetCsControl(slotId_);
        if (csControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::SeparateConference return, csControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return csControl->SeparateConference(callInfo.phoneNum, callInfo.index);
    }
    TELEPHONY_LOGE("CellularCallStub::SeparateConference return, call type error.");
    return TELEPHONY_ERR_ARGUMENT_INVALID;
}

int32_t CellularCallStub::CallSupplement(CallSupplementType type)
{
    auto csControl = GetCsControl(slotId_);
    if (csControl == nullptr) {
        TELEPHONY_LOGE("CallSupplement return, csControl is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    return csControl->CallSupplement(type);
}

int32_t CellularCallStub::StartDtmf(char cDtmfCode, const CellularCallInfo &callInfo)
{
    if (!IsValidSlotId(callInfo.slotId)) {
        TELEPHONY_LOGE("CellularCallStub::StartDtmf return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    if (CallType::TYPE_IMS == callInfo.callType) {
        auto imsControl = GetImsControl(slotId_);
        if (imsControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::StartDtmf return, imsControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return imsControl->StartDtmf(imsControl->GetConnectionMap(), cDtmfCode, callInfo);
    } else if (CallType::TYPE_CS == callInfo.callType) {
        auto csControl = GetCsControl(slotId_);
        if (csControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::StartDtmf return, csControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return csControl->StartDtmf(csControl->GetConnectionMap(), cDtmfCode, callInfo);
    }
    TELEPHONY_LOGE("CellularCallStub::StartDtmf return, call type error.");
    return TELEPHONY_ERR_ARGUMENT_INVALID;
}

int32_t CellularCallStub::StopDtmf(const CellularCallInfo &callInfo)
{
    if (!IsValidSlotId(callInfo.slotId)) {
        TELEPHONY_LOGE("CellularCallStub::StopDtmf return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    if (CallType::TYPE_IMS == callInfo.callType) {
        auto imsControl = GetImsControl(slotId_);
        if (imsControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::StopDtmf return, imsControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return imsControl->StopDtmf(imsControl->GetConnectionMap(), callInfo);
    } else if (CallType::TYPE_CS == callInfo.callType) {
        auto csControl = GetCsControl(slotId_);
        if (csControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::StopDtmf return, csControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return csControl->StopDtmf(csControl->GetConnectionMap(), callInfo);
    }
    TELEPHONY_LOGE("CellularCallStub::StopDtmf return, call type error.");
    return TELEPHONY_ERR_ARGUMENT_INVALID;
}

int32_t CellularCallStub::SendDtmf(char cDtmfCode, const CellularCallInfo &callInfo)
{
    if (!IsValidSlotId(callInfo.slotId)) {
        TELEPHONY_LOGE("CellularCallStub::SendDtmf return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    if (CallType::TYPE_IMS == callInfo.callType) {
        auto imsControl = GetImsControl(slotId_);
        if (imsControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::SendDtmf return, imsControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return imsControl->SendDtmf(imsControl->GetConnectionMap(), cDtmfCode, callInfo);
    } else if (CallType::TYPE_CS == callInfo.callType) {
        auto csControl = GetCsControl(slotId_);
        if (csControl == nullptr) {
            TELEPHONY_LOGE("CellularCallStub::SendDtmf return, csControl is nullptr");
            return TELEPHONY_ERR_LOCAL_PTR_NULL;
        }
        return csControl->SendDtmf(csControl->GetConnectionMap(), cDtmfCode, callInfo);
    }
    TELEPHONY_LOGE("CellularCallStub::SendDtmf return, call type error.");
    return TELEPHONY_ERR_ARGUMENT_INVALID;
}

int32_t CellularCallStub::SendDtmfString(
    const std::string &dtmfCodeStr, const std::string &phoneNum, int32_t switchOn, int32_t switchOff)
{
    auto control = GetCsControl(slotId_);
    if (control == nullptr) {
        TELEPHONY_LOGE("CellularCallStub::SendDtmfString return, control is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    return control->SendDtmfString(dtmfCodeStr, switchOn, switchOff);
}

int32_t CellularCallStub::SetCallTransferInfo(const CallTransferInfo &cTInfo, int32_t slotId)
{
    if (!IsValidSlotId(slotId)) {
        TELEPHONY_LOGE("CellularCallStub::SetCallTransferInfo return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    return cellularCallSupplement_.SetCallTransferInfo(cTInfo);
}

int32_t CellularCallStub::GetCallTransferInfo(CallTransferType type, int32_t slotId)
{
    TELEPHONY_LOGI("CellularCallStub::GetCallTransferInfo");
    if (!IsValidSlotId(slotId)) {
        TELEPHONY_LOGE("CellularCallStub::GetCallTransferInfo return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    return cellularCallSupplement_.GetCallTransferInfo(type);
}

void CellularCallStub::Init()
{
    ModuleServiceUtils obtain;
    std::vector<int32_t> slotVector = obtain.GetSlotInfo();
    for (const auto &it : slotVector) {
        auto csControl = std::make_shared<CSControl>();
        csControl->SetSlotId(it);
        csControlMap_.insert(std::make_pair(it, csControl));

        auto imsControl = std::make_shared<IMSControl>();
        imsControl->SetSlotId(it);
        imsControlMap_.insert(std::make_pair(it, imsControl));
    }
}

std::shared_ptr<CSControl> CellularCallStub::GetCsControl(int32_t slotId)
{
    return csControlMap_[slotId];
}

std::shared_ptr<IMSControl> CellularCallStub::GetImsControl(int32_t slotId)
{
    return imsControlMap_[slotId];
}

int32_t CellularCallStub::SetCallWaiting(bool activate, int32_t slotId)
{
    if (!IsValidSlotId(slotId)) {
        TELEPHONY_LOGE("CellularCallStub::SetCallWaiting return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    return cellularCallSupplement_.SetCallWaiting(activate);
}

int32_t CellularCallStub::GetCallWaiting(int32_t slotId)
{
    TELEPHONY_LOGI("CellularCallStub::GetCallWaiting");
    if (!IsValidSlotId(slotId)) {
        TELEPHONY_LOGE("CellularCallStub::GetCallWaiting return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    return cellularCallSupplement_.GetCallWaiting();
}

int32_t CellularCallStub::SetCallRestriction(const CallRestrictionInfo &crInfo, int32_t slotId)
{
    TELEPHONY_LOGI("CellularCallStub::SetCallRestriction");
    if (!IsValidSlotId(slotId)) {
        TELEPHONY_LOGE("CellularCallStub::SetCallRestriction return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    return cellularCallSupplement_.SetCallRestriction(crInfo);
}

int32_t CellularCallStub::GetCallRestriction(CallRestrictionType facType, int32_t slotId)
{
    TELEPHONY_LOGI("CellularCallStub::GetCallRestriction");
    if (!IsValidSlotId(slotId)) {
        TELEPHONY_LOGE("CellularCallStub::GetCallRestriction return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    return cellularCallSupplement_.GetCallRestriction(facType);
}

int32_t CellularCallStub::IsEmergencyPhoneNumber(const std::string &phoneNum, int32_t slotId, int32_t &errorCode)
{
    if (!IsValidSlotId(slotId)) {
        TELEPHONY_LOGE("CellularCallStub::IsEmergencyPhoneNumber return, invalid slot id");
        errorCode = CALL_ERR_INVALID_SLOT_ID;
        return false;
    }
    EmergencyUtils emergencyUtils;
    errorCode = TELEPHONY_SUCCESS;
    return emergencyUtils.IsEmergencyCall(phoneNum, slotId);
}

int32_t CellularCallStub::SetCallPreferenceMode(int32_t slotId, int32_t mode)
{
    if (!IsValidSlotId(slotId)) {
        TELEPHONY_LOGE("CellularCallStub::SetCallPreferenceMode return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    return config_.SetCallPreferenceMode(mode);
}

int32_t CellularCallStub::GetCallPreferenceMode(int32_t slotId)
{
    if (!IsValidSlotId(slotId)) {
        TELEPHONY_LOGE("CellularCallStub::GetCallPreferenceMode return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    return config_.GetCallPreferenceMode();
}

int32_t CellularCallStub::SetLteImsSwitchStatus(int32_t slotId, bool active)
{
    if (!IsValidSlotId(slotId)) {
        TELEPHONY_LOGE("CellularCallStub::SetLteImsSwitchStatus return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    return config_.SetLteImsSwitchStatus(active);
}

int32_t CellularCallStub::GetLteImsSwitchStatus(int32_t slotId)
{
    if (!IsValidSlotId(slotId)) {
        TELEPHONY_LOGE("CellularCallStub::GetLteImsSwitchStatus return, invalid slot id");
        return CALL_ERR_INVALID_SLOT_ID;
    }
    return config_.GetLteImsSwitchStatus();
}

bool CellularCallStub::IsValidSlotId(int32_t slotId) const
{
    return slotId == CoreManager::DEFAULT_SLOT_ID;
}

bool CellularCallStub::IsNeedIms() const
{
    ModuleServiceUtils moduleUtils;
    bool imsRegState = moduleUtils.GetImsRegistrationState(slotId_);
    int32_t preferenceMode = config_.GetPreferenceMode();
    int32_t imsSwitchStatus = config_.GetSwitchStatus();
    if (imsRegState && preferenceMode != CallPreferenceMode::CS_VOICE_ONLY && imsSwitchStatus) {
        TELEPHONY_LOGI("CellularCallStub::IsNeedIms return true.");
        return true;
    }
    return false;
}

std::shared_ptr<CellularCallHandler> CellularCallStub::GetHandler(int32_t slotId)
{
    return handlerMap_[slotId];
}

int32_t CellularCallStub::CtrlCamera(
    const std::u16string &cameraId, const std::u16string &callingPackage, int32_t callingUid, int32_t callingPid)
{
    return config_.CtrlCamera(cameraId, callingPackage, callingUid, callingPid);
}

int32_t CellularCallStub::SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    return config_.SetPreviewWindow(x, y, z, width, height);
}

int32_t CellularCallStub::SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    return config_.SetDisplayWindow(x, y, z, width, height);
}

int32_t CellularCallStub::SetCameraZoom(float zoomRatio)
{
    return config_.SetCameraZoom(zoomRatio);
}

int32_t CellularCallStub::SetPauseImage(const std::u16string &path)
{
    return config_.SetPauseImage(path);
}

int32_t CellularCallStub::SetDeviceDirection(int32_t rotation)
{
    return config_.SetDeviceDirection(rotation);
}
} // namespace Telephony
} // namespace OHOS
