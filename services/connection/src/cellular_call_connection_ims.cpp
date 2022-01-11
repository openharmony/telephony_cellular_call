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

#include "cellular_call_connection_ims.h"

#include "securec.h"
#include "cellular_call_types.h"
#include "cellular_call_service.h"
#include "observer_handler.h"

namespace OHOS {
namespace Telephony {
int32_t CellularCallConnectionIMS::DialRequest(int32_t slotId, const ImsDialInfoStruct &dialRequest)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("DialRequest, call ims service");
        ImsCallInfo callInfo;
        if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
            TELEPHONY_LOGE("DialRequest return, memset_s error.");
            return TELEPHONY_ERR_MEMSET_FAIL;
        }
        size_t cpyLen = strlen(dialRequest.phoneNum.c_str()) + 1;
        if (strcpy_s(callInfo.phoneNum, cpyLen, dialRequest.phoneNum.c_str()) != EOK) {
            TELEPHONY_LOGE("DialRequest return, strcpy_s fail.");
            return TELEPHONY_ERR_STRCPY_FAIL;
        }
        callInfo.videoState = dialRequest.videoState;
        callInfo.slotId = slotId;
        return moduleUtils_.GetImsServiceRemoteObject()->Dial(callInfo, dialRequest.clirMode);
    }

    TELEPHONY_LOGI("DialRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("DialRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_DIAL);
    if (event == nullptr) {
        TELEPHONY_LOGE("DialRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("DialRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->Dial(dialRequest.phoneNum, dialRequest.clirMode, event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::HangUpRequest(int32_t slotId, const std::string &phoneNum, int32_t index)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("HangUpRequest, call ims service");
        ImsCallInfo callInfo;
        if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
            TELEPHONY_LOGE("HangUpRequest return, memset_s error.");
            return TELEPHONY_ERR_MEMSET_FAIL;
        }
        if (strcpy_s(callInfo.phoneNum, strlen(phoneNum.c_str()) + 1, phoneNum.c_str()) != EOK) {
            TELEPHONY_LOGE("HangUpRequest return, strcpy_s fail.");
            return TELEPHONY_ERR_STRCPY_FAIL;
        }
        callInfo.slotId = slotId;
        callInfo.index = index;
        return moduleUtils_.GetImsServiceRemoteObject()->HangUp(callInfo);
    }

    TELEPHONY_LOGI("HangUpRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("HangUpRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_HANGUP_CONNECT);
    if (event == nullptr) {
        TELEPHONY_LOGE("HangUpRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("HangUpRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->Hangup(index, event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::AnswerRequest(
    int32_t slotId, const std::string &phoneNum, int32_t videoState, int32_t index)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("AnswerRequest, call ims service");
        ImsCallInfo callInfo;
        if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
            TELEPHONY_LOGE("AnswerRequest return, memset_s error.");
            return TELEPHONY_ERR_MEMSET_FAIL;
        }
        if (strcpy_s(callInfo.phoneNum, strlen(phoneNum.c_str()) + 1, phoneNum.c_str()) != EOK) {
            TELEPHONY_LOGE("AnswerRequest return, strcpy_s fail.");
            return TELEPHONY_ERR_STRCPY_FAIL;
        }
        callInfo.videoState = videoState;
        callInfo.slotId = slotId;
        callInfo.index = index;
        return moduleUtils_.GetImsServiceRemoteObject()->Answer(callInfo);
    }

    TELEPHONY_LOGI("AnswerRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("AnswerRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_ACCEPT_CALL);
    if (event == nullptr) {
        TELEPHONY_LOGE("AnswerRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("AnswerRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->Answer(event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::RejectRequest(int32_t slotId, const std::string &phoneNum, int32_t index)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("RejectRequest, call ims service");
        ImsCallInfo callInfo;
        if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
            TELEPHONY_LOGE("RejectRequest return, memset_s error.");
            return TELEPHONY_ERR_MEMSET_FAIL;
        }
        if (strcpy_s(callInfo.phoneNum, strlen(phoneNum.c_str()) + 1, phoneNum.c_str()) != EOK) {
            TELEPHONY_LOGE("RejectRequest return, strcpy_s fail.");
            return TELEPHONY_ERR_STRCPY_FAIL;
        }
        callInfo.slotId = slotId;
        callInfo.index = index;
        return moduleUtils_.GetImsServiceRemoteObject()->Reject(callInfo);
    }

    TELEPHONY_LOGI("RejectRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("RejectRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_REJECT_CALL);
    if (event == nullptr) {
        TELEPHONY_LOGE("RejectRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("RejectRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->Reject(event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::HoldCallRequest(int32_t slotId)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("HoldCallRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->HoldCall(slotId);
    }

    TELEPHONY_LOGI("HoldCallRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("HoldCallRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_HOLD_CALL);
    if (event == nullptr) {
        TELEPHONY_LOGE("HoldCallRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("HoldCallRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->HoldCall(event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::UnHoldCallRequest(int32_t slotId)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("UnHoldCallRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->UnHoldCall(slotId);
    }

    TELEPHONY_LOGI("UnHoldCallRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("UnHoldCallRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_ACTIVE_CALL);
    if (event == nullptr) {
        TELEPHONY_LOGE("UnHoldCallRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("UnHoldCallRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->UnHoldCall(event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::SwitchCallRequest(int32_t slotId)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SwitchCallRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SwitchCall(slotId);
    }

    TELEPHONY_LOGI("SwitchCallRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("SwitchCallRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SWAP_CALL);
    if (event == nullptr) {
        TELEPHONY_LOGE("SwitchCallRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SwitchCallRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->SwitchCall(event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::CombineConferenceRequest(int32_t slotId, int32_t voiceCall)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("CombineConferenceRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->CombineConference(slotId);
    }

    TELEPHONY_LOGI("CombineConferenceRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("CombineConferenceRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_JOIN_CALL);
    if (event == nullptr) {
        TELEPHONY_LOGE("CombineConferenceRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CombineConferenceRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->CombineConference(voiceCall, event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::InviteToConferenceRequest(
    int32_t slotId, const std::vector<std::string> &numberList)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("InviteToConferenceRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->InviteToConference(slotId, numberList);
    }
    TELEPHONY_LOGI("InviteToConferenceRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::KickOutFromConferenceRequest(
    int32_t slotId, const std::vector<std::string> &numberList)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("KickOutFromConferenceRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->KickOutFromConference(slotId, numberList);
    }
    TELEPHONY_LOGI("KickOutFromConferenceRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::CallSupplementRequest(int32_t slotId, CallSupplementType type)
{
    TELEPHONY_LOGI("CallSupplementRequest start");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("CallSupplementRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_CALL_SUPPLEMENT);
    if (event == nullptr) {
        TELEPHONY_LOGE("CallSupplementRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CallSupplementRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->CallSupplement(type, event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::UpdateCallMediaModeRequest(const CellularCallInfo &callInfo, CallMediaMode mode)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("UpdateCallMediaModeRequest, call ims service");
        ImsCallInfo callInfo;
        if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
            TELEPHONY_LOGE("UpdateCallMediaModeRequest return, memset_s error.");
            return TELEPHONY_ERR_MEMSET_FAIL;
        }
        if (strcpy_s(callInfo.phoneNum, strlen(callInfo.phoneNum) + 1, callInfo.phoneNum) != EOK) {
            TELEPHONY_LOGE("UpdateCallMediaModeRequest return, strcpy_s fail.");
            return TELEPHONY_ERR_STRCPY_FAIL;
        }
        callInfo.slotId = callInfo.slotId;
        callInfo.index = callInfo.index;
        return moduleUtils_.GetImsServiceRemoteObject()->UpdateCallMediaMode(callInfo, mode);
    }
    TELEPHONY_LOGI("UpdateCallMediaModeRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag)
{
    TELEPHONY_LOGI("CellularCallConnectionIMS::GetImsCallsDataRequest entry.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("GetImsCallsDataRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_IMS_CALL_LIST, lastCallsDataFlag);
    if (event == nullptr) {
        TELEPHONY_LOGE("GetImsCallsDataRequest return, error type: event is null.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetImsCallsDataRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->GetImsCallList(event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::SendDtmfRequest(int32_t slotId, char cDtmfCode, int32_t index) const
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SendDtmfRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SendDtmf(slotId, cDtmfCode, index);
    }

    TELEPHONY_LOGI("SendDtmfRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("SendDtmfRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SEND_DTMF);
    if (event == nullptr) {
        TELEPHONY_LOGE("SendDtmfRequest return, error type: event is null.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SendDtmfRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->SendDTMF(cDtmfCode, index, event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::StartDtmfRequest(int32_t slotId, char cDtmfCode, int32_t index) const
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("StartDtmfRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->StartDtmf(slotId, cDtmfCode, index);
    }

    TELEPHONY_LOGI("StartDtmfRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("StartDtmfRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_START_DTMF);
    if (event == nullptr) {
        TELEPHONY_LOGE("StartDtmfRequest return, error type: event is null.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("StartDtmfRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->StartDTMF(cDtmfCode, index, event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::StopDtmfRequest(int32_t slotId, int32_t index) const
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("StopDtmfRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->StopDtmf(slotId, index);
    }

    TELEPHONY_LOGI("StopDtmfRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("StopDtmfRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_STOP_DTMF);
    if (event == nullptr) {
        TELEPHONY_LOGE("StopDtmfRequest return, error type: event is null.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("StopDtmfRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->StopDTMF(index, event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::StartRttRequest(int32_t slotId, const std::string &msg)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("StartRttRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->StartRtt(slotId, msg);
    }
    TELEPHONY_LOGI("StartRttRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::StopRttRequest(int32_t slotId)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("StopRttRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->StopRtt(slotId);
    }
    TELEPHONY_LOGI("StopRttRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::GetCallFailReasonRequest(int32_t slotId) const
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetCallFailReasonRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetCallFailReason(slotId);
    }

    TELEPHONY_LOGI("GetCallFailReasonRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("GetCallFailReasonRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_CALL_FAIL_REASON);
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallFailReasonRequest return, error type: event is null.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetCallFailReasonRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->GetCallFailReason(event);
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS