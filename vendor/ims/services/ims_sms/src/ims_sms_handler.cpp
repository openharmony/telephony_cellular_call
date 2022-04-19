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
#include "ims_sms_handler.h"
#include "ims_radio_event.h"
#include "ims_sms_register.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
ImsSmsHandler::ImsSmsHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner)
    : ImsBaseHandler(runner)
{
    InitRequestFuncMap();
}

ImsSmsHandler::~ImsSmsHandler() {}

void ImsSmsHandler::ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("ImsSmsHandler::ProcessEvent event is nullptr");
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

void ImsSmsHandler::ImsSendMessageResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("ImsSendMessageResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsSmsRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("ImsSendMessageResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("ImsSendMessageResponse, info is nullptr");
        return;
    }
    auto result = event->GetSharedObject<SendSmsResultInfo>();
    if (result == nullptr) {
        TELEPHONY_LOGE("ImsSendMessageResponse, result is nullptr");
        return;
    }
    imsRegister->UpdateImsSendMessageResponse(*info, *result);
    TELEPHONY_LOGI("ImsSmsHandler::ImsSendMessageResponse");
}

void ImsSmsHandler::ImsSetSmsConfigResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("ImsSetSmsConfigResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsSmsRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("ImsSetSmsConfigResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("ImsSetSmsConfigResponse, info is nullptr");
        return;
    }
    imsRegister->UpdateImsSetSmsConfigResponse(*info);
    TELEPHONY_LOGI("ImsSmsHandler::ImsSetSmsConfigResponse");
}

void ImsSmsHandler::ImsGetSmsConfigResponse(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        TELEPHONY_LOGE("ImsGetSmsConfigResponse, event is nullptr");
        return;
    }
    auto imsRegister = DelayedSingleton<ImsSmsRegister>::GetInstance();
    if (imsRegister == nullptr) {
        TELEPHONY_LOGE("ImsGetSmsConfigResponse, ImsRegister is nullptr");
        return;
    }
    auto info = event->GetSharedObject<ImsResponseInfo>();
    if (info == nullptr) {
        TELEPHONY_LOGE("ImsGetSmsConfigResponse, ImsResponseInfo is nullptr");
        return;
    }
    auto imsSmsConfig = event->GetSharedObject<int32_t>();
    if (imsSmsConfig == nullptr) {
        TELEPHONY_LOGE("ImsGetSmsConfigResponse, imsSmsConfig is nullptr");
        return;
    }

    imsRegister->UpdateImsGetSmsConfigResponse(*info, *imsSmsConfig);
    TELEPHONY_LOGI("ImsSmsHandler::ImsGetSmsConfigResponse");
}

void ImsSmsHandler::ImsServiceStatusReport(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("ImsSmsHandler::ImsServiceStatusReport");
}

void ImsSmsHandler::InitRequestFuncMap()
{
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SENDMESSAGE] = &ImsSmsHandler::ImsSendMessageResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_SET_SMS_CONFIG] = &ImsSmsHandler::ImsSetSmsConfigResponse;
    requestFuncMap_[ImsRadioEvent::IMS_RADIO_GET_SMS_CONFIG] = &ImsSmsHandler::ImsGetSmsConfigResponse;

    requestFuncMap_[ImsRadioEvent::IMS_RAIDO_SERVICE_STATUS] = &ImsSmsHandler::ImsSendMessageResponse;
}
} // Telephony
} // OHOS

