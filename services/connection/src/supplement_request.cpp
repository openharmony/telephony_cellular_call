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

#include "supplement_request.h"
#include "observer_handler.h"

#include "cellular_call_service.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
int32_t SupplementRequest::InquireClipRequest()
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("SupplementRequest::InquireClipRequest return, error type: core is nullptr.\n");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_CALL_CLIP);
    if (event == nullptr) {
        TELEPHONY_LOGE("SupplementRequest::InquireClipRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->GetClip(event);
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetClirActivateRequest(int32_t action)
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("SetClirActivateRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_CALL_CLIR);
    if (event == nullptr) {
        TELEPHONY_LOGE("SetClirActivateRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->SetClir(action, event);
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetClirDeactivateRequest(int32_t action)
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("SetClirDeactivateRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_CALL_CLIR);
    if (event == nullptr) {
        TELEPHONY_LOGE("SetClirDeactivateRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->SetClir(action, event);
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::InquireClirRequest()
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("InquireClirRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_CALL_CLIR);
    if (event == nullptr) {
        TELEPHONY_LOGE("InquireClirRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->GetClir(event);
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::GetCallTransferInfoRequest(int32_t type)
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("GetCallTransferInfoRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_CALL_FORWARD);
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallTransferInfoRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->GetCallTransferInfo(type, event);
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetCallTransferInfoRequest(
    int32_t action, int32_t cause, const std::string &transferPhone, int32_t serviceInfoB)
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("SetCallTransferInfoRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_CALL_FORWARD);
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallTransferInfoRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->SetCallTransferInfo(cause, action, transferPhone, serviceInfoB, event);
    TELEPHONY_LOGI("SetCallTransferInfoRequest end");
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::GetCallRestrictionRequest(const std::string &fac)
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("GetCallRestriction return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_CALL_RESTRICTION);
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallRestriction return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->GetCallRestriction(fac, event);
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetCallRestrictionRequest(std::string &fac, int32_t mode, std::string &pw)
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("SetCallRestriction return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_CALL_RESTRICTION);
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallRestriction return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->SetCallRestriction(fac, mode, pw, event);
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetCallWaitingRequest(bool activate)
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("SetCallWaitingRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_CALL_WAIT);
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallWaitingRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->SetCallWaiting(activate, event);
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::GetCallWaitingRequest()
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("GetCallWaitingRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_CALL_WAIT);
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallWaitingRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->GetCallWaiting(event);
    return TELEPHONY_SUCCESS;
}

std::shared_ptr<MMIHandler> SupplementRequest::GetMMIHandler() const
{
    auto callService = DelayedSingleton<CellularCallService>::GetInstance();
    if (callService == nullptr) {
        TELEPHONY_LOGE("GetMMIHandler return, error type: callService is nullptr.");
        return nullptr;
    }
    if (callService->GetHandler(slotId_) == nullptr) {
        TELEPHONY_LOGE("GetMMIHandler return, error type: GetHandler() is nullptr.");
        return nullptr;
    }
    if (callService->GetHandler(slotId_)->GetCsControl() == nullptr) {
        TELEPHONY_LOGE("GetMMIHandler return, error type: GetCsControl() is nullptr.");
        return nullptr;
    }
    return callService->GetHandler(slotId_)->GetCsControl()->GetMMIHandler();
}
} // namespace Telephony
} // namespace OHOS