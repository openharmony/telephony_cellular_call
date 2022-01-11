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
    TELEPHONY_LOGI("InquireClipRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("InquireClipRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->InquireClip(slotId_);
    }

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

int32_t SupplementRequest::SetClirRequest(int32_t action)
{
    TELEPHONY_LOGI("SetClirRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetClirRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetClir(slotId_, action);
    }

    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("SetClirRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_CALL_CLIR);
    if (event == nullptr) {
        TELEPHONY_LOGE("SetClirRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->SetClir(action, event);
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::InquireClirRequest()
{
    TELEPHONY_LOGI("InquireClirRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("InquireClirRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->InquireClir(slotId_);
    }

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

int32_t SupplementRequest::GetCallTransferRequest(int32_t reason)
{
    TELEPHONY_LOGI("GetCallTransferRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetCallTransferRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetCallTransfer(slotId_, reason);
    }

    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("GetCallTransferRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_CALL_FORWARD);
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallTransferRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->GetCallTransferInfo(reason, event);
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetCallTransferRequest(
    int32_t action, int32_t reason, const std::string &transferNum, int32_t classType)
{
    TELEPHONY_LOGI("SetCallTransferRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetCallTransferRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetCallTransfer(
            slotId_, reason, action, transferNum, classType);
    }

    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("SetCallTransferRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_CALL_FORWARD);
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallTransferRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->SetCallTransferInfo(reason, action, transferNum, classType, event);
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::GetCallRestrictionRequest(const std::string &fac)
{
    TELEPHONY_LOGI("GetCallRestrictionRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetCallRestrictionRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetCallRestriction(slotId_, fac);
    }

    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("GetCallRestrictionRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_CALL_RESTRICTION);
    if (event == nullptr) {
        TELEPHONY_LOGE("GetCallRestrictionRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->GetCallRestriction(fac, event);
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetCallRestrictionRequest(std::string &fac, int32_t mode, std::string &pw)
{
    TELEPHONY_LOGI("SetCallRestrictionRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetCallRestrictionRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetCallRestriction(slotId_, fac, mode, pw);
    }

    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("SetCallRestrictionRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_CALL_RESTRICTION);
    if (event == nullptr) {
        TELEPHONY_LOGE("SetCallRestrictionRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->SetCallRestriction(fac, mode, pw, event);
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetCallWaitingRequest(bool activate)
{
    TELEPHONY_LOGI("SetCallWaitingRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetCallWaitingRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetCallWaiting(slotId_, activate);
    }

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
    TELEPHONY_LOGI("GetCallWaitingRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetCallWaitingRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetCallWaiting(slotId_);
    }

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

std::shared_ptr<CellularCallHandler> SupplementRequest::GetMMIHandler() const
{
    auto callService = DelayedSingleton<CellularCallService>::GetInstance();
    if (callService == nullptr) {
        TELEPHONY_LOGE("GetMMIHandler return, error type: callService is nullptr.");
        return nullptr;
    }
    return callService->GetHandler(slotId_);
}

int32_t SupplementRequest::SendUssdRequest(const std::string &msg)
{
    TELEPHONY_LOGI("SendUssdRequest entry");
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("SendUssdRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_USSD_CUSD);
    if (event == nullptr) {
        TELEPHONY_LOGE("SendUssdRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(GetMMIHandler());
    core->SetUssdCusd(msg, event);
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS