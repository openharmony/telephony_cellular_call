/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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
#include "ims_core_service_handler.h"
#include "ims_core_service_register.h"
#include "ims_radio_event.h"
#include "telephony_log_wrapper.h"
#include "ims_ril_manager.h"

namespace OHOS {
namespace Telephony {
ImsCoreServiceHandler::ImsCoreServiceHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner)
    : ImsBaseHandler(runner)
{
    InitRequestFuncMap();
}

ImsCoreServiceHandler::~ImsCoreServiceHandler() {}

void ImsCoreServiceHandler::ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("ImsCoreServiceHandler::ProcessEvent event is nullptr");
        return;
    }
    auto it = requestFuncMap_.find(event->GetInnerEventId());
    if (it == requestFuncMap_.end()) {
        TELEPHONY_LOGE("Can not find eventId");
        return;
    }

    auto requestFunc = it->second;
    if (requestFunc != nullptr) {
        (this->*requestFunc)(event);
    } else {
        TELEPHONY_LOGE("Request function is nullptr");
    }
}

void ImsCoreServiceHandler::ImsServiceStatusReport(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("ImsServiceStatusReport, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCoreServiceRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("ImsServiceStatusReport, ImsRegister is nullptr");
        return;
    }
    auto slotId = event->GetSharedObject<int32_t>();
    if (slotId == nullptr) {
        TELEPHONY_LOGE("ImsServiceStatusReport, slotId is nullptr");
        return;
    }
    auto imsServiceStatus = event->GetSharedObject<ImsServiceStatus>();
    if (imsServiceStatus == nullptr) {
        TELEPHONY_LOGE("ImsServiceStatusReport, imsServiceStatus is nullptr");
        return;
    }
    imsRegister->UpdateImsServiceStatusReport(*slotId, *imsServiceStatus);
    TELEPHONY_LOGI("ImsServiceStatusReport");
}

void ImsCoreServiceHandler::ImsNetworkStateChange(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("ImsNetworkStateChange, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCoreServiceRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("ImsNetworkStateChange, ImsRegister is nullptr");
        return;
    }
    auto slotId = event->GetSharedObject<int32_t>();
    if (slotId == nullptr) {
        TELEPHONY_LOGE("ImsNetworkStateChange, slotId is nullptr");
        return;
    }
    imsRegister->UpdateImsNetworkStateChange(*slotId);
    TELEPHONY_LOGI("ImsNetworkStateChange");
}

void ImsCoreServiceHandler::ImsRegistrationStatusResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("ImsRegistrationStatusResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsCoreServiceRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("ImsRegistrationStatusResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("ImsRegistrationStatusResponse, info is nullptr");
        return;
    }
    auto imsRegStatus = event->GetSharedObject<ImsRegistrationStatus>();
    if (imsRegStatus == nullptr) {
        TELEPHONY_LOGE("ImsRegistrationStatusResponse, imsServiceStatus is nullptr");
        return;
    }
    imsRegister->UpdateImsRegistrationStatusResponse(*info, *imsRegStatus);
    TELEPHONY_LOGI("ImsRegistrationStatusResponse");
}

void ImsCoreServiceHandler::InitRequestFuncMap()
{
    requestFuncMap_[IMS_RAIDO_SERVICE_STATUS] = &ImsCoreServiceHandler::ImsServiceStatusReport;
    requestFuncMap_[IMS_RADIO_NET_STATE_CHANGE] = &ImsCoreServiceHandler::ImsNetworkStateChange;
    requestFuncMap_[IMS_RADIO_GET_REGISTRATION_STATUS] = &ImsCoreServiceHandler::ImsRegistrationStatusResponse;
}
} // Telephony
} // OHOS

