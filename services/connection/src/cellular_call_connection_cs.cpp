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

#include "cellular_call_connection_cs.h"

#include "cellular_call_service.h"
#include "observer_handler.h"

namespace OHOS {
namespace Telephony {
int32_t CellularCallConnectionCS::DialRequest(int32_t slotId, const DialRequestStruct &dialRequest)
{
    TELEPHONY_LOGE("CellularCallConnectionCS::DialRequest start.");
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

int32_t CellularCallConnectionCS::HangUpRequest(int32_t slotId)
{
    TELEPHONY_LOGE("CellularCallConnectionCS::HangUpRequest start.");
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
    int32_t index = GetIndex();
    core->Hangup(index, event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionCS::AnswerRequest(int32_t slotId)
{
    TELEPHONY_LOGE("CellularCallConnectionCS::AnswerRequest start.");
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

int32_t CellularCallConnectionCS::RejectRequest(int32_t slotId)
{
    TELEPHONY_LOGE("CellularCallConnectionCS::RejectRequest start.");
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

int32_t CellularCallConnectionCS::HoldRequest(int32_t slotId)
{
    TELEPHONY_LOGE("CellularCallConnectionCS::HoldRequest start.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("HoldRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_HOLD_CALL);
    if (event == nullptr) {
        TELEPHONY_LOGE("HoldRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("HoldRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->HoldCall(event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionCS::UnHoldCallRequest(int32_t slotId)
{
    TELEPHONY_LOGE("CellularCallConnectionCS::UnHoldCallRequest start.");
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

int32_t CellularCallConnectionCS::SwitchCallRequest(int32_t slotId)
{
    TELEPHONY_LOGE("CellularCallConnectionCS::SwitchCallRequest start.");
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

int32_t CellularCallConnectionCS::CombineConferenceRequest(int32_t slotId, int32_t voiceCall)
{
    TELEPHONY_LOGE("CellularCallConnectionCS::CombineConferenceRequest start.");
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

int32_t CellularCallConnectionCS::SeparateConferenceRequest(int32_t slotId, int32_t index, int32_t voiceCall)
{
    TELEPHONY_LOGE("CellularCallConnectionCS::SeparateConferenceRequest start.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("SeparateConferenceRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SPLIT_CALL);
    if (event == nullptr) {
        TELEPHONY_LOGE("SeparateConferenceRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SeparateConferenceRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->SeparateConference(index, voiceCall, event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionCS::CallSupplementRequest(int32_t slotId, CallSupplementType type)
{
    TELEPHONY_LOGE("CellularCallConnectionCS::CallSupplementRequest start.");
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

int32_t CellularCallConnectionCS::SendCDMAThreeWayDialRequest(int32_t slotId)
{
    TELEPHONY_LOGE("CellularCallConnectionCS::SendCDMAThreeWayDialRequest start.");
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionCS::SendDtmfRequest(int32_t slotId, char cDtmfCode, int32_t index) const
{
    TELEPHONY_LOGE("CellularCallConnectionCS::SendDtmfRequest start.");
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

int32_t CellularCallConnectionCS::StartDtmfRequest(int32_t slotId, char cDtmfCode, int32_t index) const
{
    TELEPHONY_LOGE("CellularCallConnectionCS::StartDtmfRequest start.");
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

int32_t CellularCallConnectionCS::StopDtmfRequest(int32_t slotId, int32_t index) const
{
    TELEPHONY_LOGE("CellularCallConnectionCS::StopDtmfRequest start.");
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

int32_t CellularCallConnectionCS::GetCsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag)
{
    TELEPHONY_LOGE("CellularCallConnectionCS::GetCsCallsDataRequest start.");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("CellularCallHandler::GetCsCallsDataRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_CURRENT_CALLS, lastCallsDataFlag);
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCsCallsDataRequest return, error type: event is null.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("GetCsCallsDataRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));

    // Implementation
    // Optional. Recommended when +CHLD command is implemented.
    core->GetCallList(event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionCS::GetCallFailReasonRequest(int32_t slotId) const
{
    TELEPHONY_LOGE("CellularCallConnectionCS::GetCallFailReasonRequest start.");
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

void CellularCallConnectionCS::RegisterHandler()
{
    DelayedSingleton<CellularCallService>::GetInstance()->RegisterHandler();
}
} // namespace Telephony
} // namespace OHOS