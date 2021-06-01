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

#include "cellular_call_handler.h"
#include "hril_call_parcel.h"
#include "phone_manager.h"
#include "cs_control.h"
namespace OHOS {
namespace CellularCall {
CellularCallHandler::CellularCallHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner)
    : AppExecFwk::EventHandler(runner)
{
    lastFlag_ = 0;
    HILOG_INFO("CellularCallHandler::CellularCallHandler::instance created.");
}

void CellularCallHandler::ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        HILOG_ERROR("CellularCallHandler::ProcessEvent, event is nullptr");
        return;
    }
    switch (event->GetInnerEventId()) {
        case ObserverHandler::RADIO_DIAL:
        case ObserverHandler::RADIO_HANDUP_CONNECT:
        case ObserverHandler::RADIO_REJECT_CALL:
        case ObserverHandler::RADIO_ACCEPT_CALL:
        case ObserverHandler::RADIO_CALL_STATE:
        case ObserverHandler::RADIO_AVAIL:
        case ObserverHandler::RADIO_NOT_AVAIL: {
            HILOG_DEBUG("CellularCallHandler::ProcessEvent event entry.");
            GetCsCallsData();
            break;
        }
        case ObserverHandler::RADIO_CURRENT_CALLS: {
            HILOG_DEBUG("CellularCallHandler::ProcessEvent query current calls result entry.");
            // Returns list of current calls of ME. If command succeeds but no calls are available,
            // no information response is sent to TE. Refer subclause 9.2 for possible <err> values.
            auto callInfoList = event->GetSharedObject<CallInfoList>();
            if (callInfoList == nullptr) {
                HILOG_ERROR("CellularCallHandler::ProcessEvent, radioResponseInfo is nullptr");
                return;
            }
            DelayedSingleton<CSControl>::GetInstance()->DealCsCallsData(*callInfoList);
            break;
        }
        default: {
            HILOG_ERROR("CellularCallHandler::ProcessEvent, event id is unknown.");
            break;
        }
    }
}

int CellularCallHandler::GetCsCallsData()
{
    HILOG_DEBUG("CSControl::GetCsCallsData entry.");
    IRilManager *rilManager = GetManager(slotId_);
    if (rilManager == nullptr) {
        HILOG_ERROR("CSControl::DialRequest return, error type: rilManager is nullptr.");
        return ERR_RIL_MANAGER;
    }
    int32_t flag = GetLastFlag();
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_CURRENT_CALLS, flag);
    if (event == nullptr) {
        HILOG_ERROR("GetCsCallsData return, error type: event is null.");
        return ERR_PARAMETER_INVALID;
    }
    event->SetOwner(shared_from_this());
    // Implementation
    // Optional. Recommended when +CHLD command is implemented.
    rilManager->GetCallList(event);
    return TELEPHONY_NO_ERROR;
}

IRilManager *CellularCallHandler::GetManager(int32_t slotId)
{
    return PhoneManager::GetInstance().phone_[slotId]->rilManager_;
}

int CellularCallHandler::GetLastFlag()
{
    return lastFlag_++;
}
} // namespace CellularCall
} // namespace OHOS
