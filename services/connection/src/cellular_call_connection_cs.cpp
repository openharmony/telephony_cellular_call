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
#include <securec.h>
#include <utility>

#include "phone_manager.h"

#include "cellular_call_service.h"

namespace OHOS {
namespace CellularCall {
CellularCallConnectionCS::CellularCallConnectionCS()
{
    HILOG_ERROR("CellularCallConnectionCS::CellularCallConnectionCS.\n");
    if (memset_s(&callReportInfo_, sizeof(callReportInfo_), 0, sizeof(callReportInfo_)) != EOK) {
        HILOG_ERROR("ReportUpdateInfo return, memset_s fail.");
    }
}

CellularCallConnectionCS::~CellularCallConnectionCS()
{
    HILOG_ERROR("CellularCallConnectionCS::~CellularCallConnectionCS.\n");
}

int32_t CellularCallConnectionCS::DialRequest(const DialRequestStruct &dialRequest, int32_t slotId)
{
    HILOG_DEBUG("CellularCallConnectionCS, DialRequest start");
    IRilManager *rilManager = GetManager(slotId);
    if (rilManager == nullptr) {
        HILOG_ERROR("DialRequest return, error type: rilManager is nullptr.\n");
        return ERR_RIL_MANAGER;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_DIAL);
    if (event == nullptr) {
        HILOG_ERROR("DialRequest return, error type: event is null.\n");
        return ERR_PARAMETER_INVALID;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler());
    rilManager->Dial(dialRequest.phoneNum, dialRequest.clirMode, event);

    return TELEPHONY_NO_ERROR;
}

int32_t CellularCallConnectionCS::EndRequest(int32_t slotId)
{
    HILOG_DEBUG("CellularCallConnectionCS, EndRequest start");
    IRilManager *rilManager = GetManager(slotId);
    if (rilManager == nullptr) {
        HILOG_ERROR("EndRequest return, error type: rilmanager is null.");
        return ERR_RIL_MANAGER;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_HANDUP_CONNECT);
    if (event == nullptr) {
        HILOG_ERROR("EndRequest return, error type: event is null.");
        return ERR_PARAMETER_INVALID;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler());
    rilManager->Hangup(index_, event);
    return TELEPHONY_NO_ERROR;
}

int32_t CellularCallConnectionCS::AnswerRequest(int32_t slotId)
{
    HILOG_DEBUG("CellularCallConnectionCS, AnswerRequest start");
    IRilManager *rilManager = GetManager(slotId);
    if (rilManager == nullptr) {
        HILOG_ERROR("AnswerRequest return, error type: rilmanager is null.");
        return ERR_RIL_MANAGER;
    }
    HILOG_DEBUG("CellularCallConnectionCS, AnswerRequest start Answer");
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_ACCEPT_CALL);
    if (event == nullptr) {
        HILOG_ERROR("AnswerRequest return, error type: event is null.");
        return ERR_PARAMETER_INVALID;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler());
    rilManager->Answer(event);
    return TELEPHONY_NO_ERROR;
}

int32_t CellularCallConnectionCS::RejectRequest(int32_t slotId)
{
    HILOG_DEBUG("CellularCallConnectionCS, RejectRequest start");
    IRilManager *rilManager = GetManager(slotId);
    if (rilManager == nullptr) {
        HILOG_ERROR("RejectRequest return, error type: rilmanager is null.");
        return ERR_RIL_MANAGER;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_REJECT_CALL);
    if (event == nullptr) {
        HILOG_ERROR("RejectRequest return, error type: event is null.");
        return ERR_PARAMETER_INVALID;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler());
    rilManager->Reject(event);
    return TELEPHONY_NO_ERROR;
}

int32_t CellularCallConnectionCS::HoldingAndActiveRequest(int32_t slotId)
{
    return TELEPHONY_NO_ERROR;
}

int32_t CellularCallConnectionCS::JoinRequest(int32_t slotId)
{
    return TELEPHONY_NO_ERROR;
}

int32_t CellularCallConnectionCS::SplitRequest(int32_t slotId)
{
    return TELEPHONY_NO_ERROR;
}

int32_t CellularCallConnectionCS::SendCDMAThreeWayDialRequest(int32_t slotId)
{
    return TELEPHONY_NO_ERROR;
}

IRilManager *CellularCallConnectionCS::GetManager(int32_t slotId)
{
    return PhoneManager::GetInstance().phone_[slotId]->rilManager_;
}

void CellularCallConnectionCS::SetOrUpdateCallReportInfo(TelephonyCallManager::CallReportInfo callReportInfo)
{
    callReportInfo_ = callReportInfo;
}

TelephonyCallManager::CallReportInfo CellularCallConnectionCS::GetCallReportInfo()
{
    return callReportInfo_;
}

void CellularCallConnectionCS::SetStatus(TelCallStates state)
{
    callReportInfo_.state = state;
}

TelCallStates CellularCallConnectionCS::GetStatus()
{
    return callReportInfo_.state;
}

bool CellularCallConnectionCS::IsRingingState()
{
    return this->GetStatus() == CALL_STATUS_INCOMING || this->GetStatus() == CALL_STATUS_WAITING ||
        this->GetStatus() == CALL_STATUS_ALERTING;
}
} // namespace CellularCall
} // namespace OHOS