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

#include "config_request.h"

#include <observer_handler.h>
#include <call_manager_errors.h>
#include <cellular_call_service.h>

namespace OHOS {
namespace Telephony {
int32_t ConfigRequest::SetCallPreferenceModeRequest(int32_t mode)
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetCallPreferenceMode return, error type: core is nullptr.\n");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_CALL_PREFERENCE_MODE);
    if (event == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetCallPreferenceMode return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId_));
    core->SetCallPreferenceMode(mode, event);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetCallPreferenceModeRequest()
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetCallPreferenceMode return, error type: core is nullptr.\n");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_CALL_PREFERENCE_MODE);
    if (event == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetCallPreferenceMode return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId_));
    core->GetCallPreferenceMode(event);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetLteImsSwitchStatusRequest(int32_t active)
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetCallPreferenceMode return, error type: core is nullptr.\n");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_LTE_IMS_SWITCH_STATUS);
    if (event == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetCallPreferenceMode return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId_));
    core->SetLteImsSwitchStatus(active, event);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetLteImsSwitchStatusRequest()
{
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetCallPreferenceMode return, error type: core is nullptr.\n");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_LTE_IMS_SWITCH_STATUS);
    if (event == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetCallPreferenceMode return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId_));
    core->GetLteImsSwitchStatus(event);
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS