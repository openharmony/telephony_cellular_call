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

#include "cellular_call_types.h"
#include "cellular_call_service.h"

namespace OHOS {
namespace Telephony {
int32_t CellularCallConnectionIMS::DialRequest(const ImsDialInfoStruct &dialRequest, int32_t slotId)
{
    TELEPHONY_LOGI("DialRequest start");
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

int32_t CellularCallConnectionIMS::EndRequest(int32_t index, int32_t slotId)
{
    TELEPHONY_LOGI("EndRequest start");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("EndRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_HANGUP_CONNECT);
    if (event == nullptr) {
        TELEPHONY_LOGE("EndRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("EndRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->Hangup(index, event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::AnswerRequest(int32_t videoState, int32_t slotId)
{
    TELEPHONY_LOGI("AnswerRequest start");
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

int32_t CellularCallConnectionIMS::RejectRequest(int32_t slotId)
{
    TELEPHONY_LOGI("RejectRequest start");
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

int32_t CellularCallConnectionIMS::SwapRequest(int32_t slotId)
{
    TELEPHONY_LOGI("SwapRequest start");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("SwapRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SWAP_CALL);
    if (event == nullptr) {
        TELEPHONY_LOGE("SwapRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SwapRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->SwitchCall(event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::HoldRequest(int32_t slotId)
{
    TELEPHONY_LOGI("HoldRequest start");
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

int32_t CellularCallConnectionIMS::ActiveRequest(int32_t slotId)
{
    TELEPHONY_LOGI("ActiveRequest start");
    auto core = GetCore(slotId);
    if (core == nullptr) {
        TELEPHONY_LOGE("ActiveRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_ACTIVE_CALL);
    if (event == nullptr) {
        TELEPHONY_LOGE("ActiveRequest return, error type: event is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("ActiveRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId));
    core->UnHoldCall(event);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionIMS::CombineConferenceRequest(int32_t slotId, int32_t voiceCall)
{
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

int32_t CellularCallConnectionIMS::CallSupplementRequest(CallSupplementType type, int32_t slotId)
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

int32_t CellularCallConnectionIMS::SendDtmfRequest(char cDtmfCode, int32_t index, int32_t slotId) const
{
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

int32_t CellularCallConnectionIMS::StartDtmfRequest(char cDtmfCode, int32_t index, int32_t slotId) const
{
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

int32_t CellularCallConnectionIMS::StopDtmfRequest(int32_t index, int32_t slotId) const
{
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
} // namespace Telephony
} // namespace OHOS