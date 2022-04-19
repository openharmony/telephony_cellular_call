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
#include "ims_sms.h"
#include "telephony_errors.h"
#include "ims_ril_manager.h"
#include "ims_radio_event.h"

namespace OHOS {
namespace Telephony {
ImsSms::ImsSms()
{
}

ImsSms::~ImsSms()
{
}

bool ImsSms::Init()
{
    TELEPHONY_LOGI("ImsSms Init");
    SetSlotIds();

    if (!CreateEventLoop("ImsSmsLoop")) {
        TELEPHONY_LOGE("ImsSms::CreateEventLoop failed");
        return false;
    }
    if (!CreateHandler()) {
        TELEPHONY_LOGE("ImsSms::CreateHandler failed");
        return false;
    }
    if (!RegisterObserver()) {
        TELEPHONY_LOGE("ImsSms::RegisterHandler failed");
        return false;
    }

    TELEPHONY_LOGI("ImsSms:Init success");
    return true;
}

void ImsSms::SetSlotIds()
{
    slotIds_.emplace_back(DEFAULT_SIM_SLOT_ID);
}

int32_t ImsSms::ImsSendMessage(int32_t slotId, const ImsMessageInfo &imsMessageInfo)
{
    AppExecFwk::InnerEvent::Pointer response = AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SENDMESSAGE);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->ImsSendMessage(slotId, imsMessageInfo, response);
}

int32_t ImsSms::ImsSetSmsConfig(int32_t slotId, int32_t imsSmsConfig)
{
    AppExecFwk::InnerEvent::Pointer response = AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_SMS_CONFIG);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->ImsSetSmsConfig(slotId, imsSmsConfig, response);
}

int32_t ImsSms::ImsGetSmsConfig(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response = AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_SMS_CONFIG);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->ImsGetSmsConfig(slotId, response);
}

int32_t ImsSms::RegisterImsSmsCallback(const sptr<ImsSmsCallbackInterface> &callback)
{
    auto imsSmsRegister = DelayedSingleton<ImsSmsRegister>::GetInstance();
    if (imsSmsRegister == nullptr) {
        TELEPHONY_LOGE("ImsSmsRegister is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    if (imsSmsRegister->RegisterImsSmsCallBack(callback) != TELEPHONY_SUCCESS) {
        TELEPHONY_LOGE("Register IMS call callback faled");
        return TELEPHONY_ERR_FAIL;
    }
    TELEPHONY_LOGI("Register IMS call callback");
    return TELEPHONY_SUCCESS;
}

bool ImsSms::RegisterObserver()
{
    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return false;
    }
    for (auto &entry : handlerMap_) {
        auto &handler = entry.second;
        imsRilManager->ImsRegisterObserver(handler->GetSlotId(), ImsRadioEvent::IMS_RAIDO_SERVICE_STATUS, handler);
    }
    return true;
}
} // Telephony
} // OHOS
