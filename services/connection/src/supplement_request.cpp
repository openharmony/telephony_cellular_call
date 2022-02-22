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

#include "cellular_call_service.h"
#include "radio_event.h"
#include "telephony_log_wrapper.h"
#include "telephony_types.h"

namespace OHOS {
namespace Telephony {
int32_t SupplementRequest::InquireClipRequest(int32_t slotId)
{
    TELEPHONY_LOGI("InquireClipRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("InquireClipRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->InquireClip(slotId);
    }
    CoreManagerInner::GetInstance().GetClip(slotId, RadioEvent::RADIO_GET_CALL_CLIP, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetClirRequest(int32_t slotId, int32_t action)
{
    TELEPHONY_LOGI("SetClirRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetClirRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetClir(slotId, action);
    }
    CoreManagerInner::GetInstance().SetClir(slotId, RadioEvent::RADIO_SET_CALL_CLIR, action, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::InquireClirRequest(int32_t slotId)
{
    TELEPHONY_LOGI("InquireClirRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("InquireClirRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->InquireClir(slotId);
    }
    CoreManagerInner::GetInstance().GetClir(slotId, RadioEvent::RADIO_GET_CALL_CLIR, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::GetCallTransferRequest(int32_t slotId, int32_t reason)
{
    TELEPHONY_LOGI("GetCallTransferRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetCallTransferRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetCallTransfer(slotId, reason);
    }
    CoreManagerInner::GetInstance().GetCallTransferInfo(
        slotId, RadioEvent::RADIO_GET_CALL_FORWARD, reason, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetCallTransferRequest(
    int32_t slotId, int32_t action, int32_t reason, const std::string &transferNum, int32_t classType)
{
    TELEPHONY_LOGI("SetCallTransferRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetCallTransferRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetCallTransfer(
            slotId, reason, action, transferNum, classType);
    }
    CallTransferParam callTransferParam;
    callTransferParam.mode = action;
    callTransferParam.reason = reason;
    callTransferParam.number = transferNum;
    callTransferParam.classx = classType;
    CoreManagerInner::GetInstance().SetCallTransferInfo(
        slotId, RadioEvent::RADIO_SET_CALL_FORWARD, callTransferParam, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::GetCallRestrictionRequest(int32_t slotId, const std::string &fac)
{
    TELEPHONY_LOGI("GetCallRestrictionRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetCallRestrictionRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetCallRestriction(slotId, fac);
    }
    CoreManagerInner::GetInstance().GetCallRestriction(
        slotId, RadioEvent::RADIO_GET_CALL_RESTRICTION, fac, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetCallRestrictionRequest(int32_t slotId, std::string &fac, int32_t mode, std::string &pw)
{
    TELEPHONY_LOGI("SetCallRestrictionRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetCallRestrictionRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetCallRestriction(slotId, fac, mode, pw);
    }
    CallRestrictionParam callRestrictionParam;
    callRestrictionParam.mode = mode;
    callRestrictionParam.fac = fac;
    callRestrictionParam.password = pw;
    CoreManagerInner::GetInstance().SetCallRestriction(
        slotId, RadioEvent::RADIO_SET_CALL_RESTRICTION, callRestrictionParam, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::SetCallWaitingRequest(int32_t slotId, bool activate)
{
    TELEPHONY_LOGI("SetCallWaitingRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetCallWaitingRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetCallWaiting(slotId, activate);
    }
    CoreManagerInner::GetInstance().SetCallWaiting(
        slotId, RadioEvent::RADIO_SET_CALL_WAIT, activate, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

int32_t SupplementRequest::GetCallWaitingRequest(int32_t slotId)
{
    TELEPHONY_LOGI("GetCallWaitingRequest entry");
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetCallWaitingRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetCallWaiting(slotId);
    }
    CoreManagerInner::GetInstance().GetCallWaiting(slotId, RadioEvent::RADIO_GET_CALL_WAIT, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}

std::shared_ptr<CellularCallHandler> SupplementRequest::GetMMIHandler(int32_t slotId) const
{
    auto callService = DelayedSingleton<CellularCallService>::GetInstance();
    if (callService == nullptr) {
        TELEPHONY_LOGE("GetMMIHandler return, error type: callService is nullptr.");
        return nullptr;
    }
    return callService->GetHandler(slotId);
}

int32_t SupplementRequest::SendUssdRequest(int32_t slotId, const std::string &msg)
{
    TELEPHONY_LOGI("SendUssdRequest entry");
    CoreManagerInner::GetInstance().SetUssd(slotId, RadioEvent::RADIO_SET_USSD, msg, GetMMIHandler(slotId));
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS
