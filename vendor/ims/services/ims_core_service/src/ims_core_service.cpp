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
#include "ims_core_service.h"
#include "ims_core_service_register.h"
#include "ims_ril_manager.h"
#include "ims_call.h"
#include "ims_sms.h"
#include "telephony_errors.h"
#include "ims_radio_event.h"

namespace OHOS {
namespace Telephony {
bool g_registerResult = SystemAbility::MakeAndRegisterAbility(DelayedSingleton<ImsCoreService>::GetInstance().get());

ImsCoreService::ImsCoreService() : SystemAbility(TELEPHONY_IMS_SYS_ABILITY_ID, true)
{
    state_ = ServiceRunningState::STATE_STOPPED;
}

ImsCoreService::~ImsCoreService()
{
    state_ = ServiceRunningState::STATE_STOPPED;
}

void ImsCoreService::OnStart()
{
    TELEPHONY_LOGI("OnStart");
    if (state_ == ServiceRunningState::STATE_RUNNING) {
        TELEPHONY_LOGI("ImsCoreService is already running");
        return;
    }
    if (!Init()) {
        TELEPHONY_LOGE("ImsCoreService init fail.");
        return;
    }
    bool ret = Publish(DelayedSingleton<ImsCoreService>::GetInstance().get());
    if (!ret) {
        TELEPHONY_LOGE("ImsCoreService publish failed!");
        return;
    }
    TELEPHONY_LOGI("ImsCoreService start success.");
    state_ = ServiceRunningState::STATE_RUNNING;
}

void ImsCoreService::OnStop()
{
    TELEPHONY_LOGI("OnStop");
    state_ = ServiceRunningState::STATE_STOPPED;
}

bool ImsCoreService::Init()
{
    SetSlotIds();

    if (!CreateEventLoop("ImsCoreServiceLoop")) {
        TELEPHONY_LOGE("ImsCoreService::CreateEventLoop failed");
        return false;
    }
    if (!CreateHandler()) {
        TELEPHONY_LOGE("ImsCoreService::CreateHandler failed");
        return false;
    }
    if (!RegisterObserver()) {
        TELEPHONY_LOGE("ImsCoreService::RegisterHandler failed");
        return false;
    }
    if (!InitSubService()) {
        TELEPHONY_LOGE("Init Subservice failed");
        return false;
    }
    TELEPHONY_LOGI("ImsCoreService:Init success");
    return true;
}

void ImsCoreService::SetSlotIds()
{
    slotIds_.emplace_back(DEFAULT_SIM_SLOT_ID);
}

bool ImsCoreService::InitSubService()
{
    sptr<ImsCall> imsCall = (std::make_unique<ImsCall>()).release();
    if (imsCall == nullptr) {
        TELEPHONY_LOGE("create ImsCall object failed!");
        return false;
    }
    if (!imsCall->Init()) {
        TELEPHONY_LOGE("Ims call service init failed");
        return false;
    }
    proxyObjectPtrMap_[PROXY_IMS_CALL] = imsCall->AsObject().GetRefPtr();

    sptr<ImsSms> imsSms = (std::make_unique<ImsSms>()).release();
    if (imsSms == nullptr) {
        TELEPHONY_LOGE("create ImsSms object failed!");
        return false;
    }
    if (!imsSms->Init()) {
        TELEPHONY_LOGE("Ims sms service init failed");
        return false;
    }
    proxyObjectPtrMap_[PROXY_IMS_SMS] = imsSms->AsObject().GetRefPtr();
    TELEPHONY_LOGI("create ImsSms object success!");
    return true;
}

int32_t ImsCoreService::GetImsRegistrationStatus(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_CALL_WAITING);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetCallWaiting(slotId, response);
}

int32_t ImsCoreService::RegisterImsCoreServiceCallback(const sptr<ImsCoreServiceCallbackInterface> &callback)
{
    auto imsCoreServiceRegister = DelayedSingleton<ImsCoreServiceRegister>::GetInstance();
    if (imsCoreServiceRegister == nullptr) {
        TELEPHONY_LOGE("imsCoreRegister is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    if (imsCoreServiceRegister->RegisterImsCoreServiceCallback(callback) != TELEPHONY_SUCCESS) {
        TELEPHONY_LOGE("Register IMS coreservice callback faled");
        return TELEPHONY_ERR_FAIL;
    }
    TELEPHONY_LOGI("Register IMS coreservice callback");
    return TELEPHONY_SUCCESS;
}

sptr<IRemoteObject> ImsCoreService::GetProxyObjectPtr(ImsServiceProxyType proxyType)
{
    auto it = proxyObjectPtrMap_.find(static_cast<uint32_t>(proxyType));
    if (it != proxyObjectPtrMap_.end()) {
        TELEPHONY_LOGI("GetProxyObjectPtr success! proxyType:%{public}d", proxyType);
        return it->second;
    }
    TELEPHONY_LOGE("GetProxyObjectPtr failed! proxyType:%{public}d", proxyType);
    return nullptr;
}

bool ImsCoreService::RegisterObserver()
{
    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return false;
    }
    for (auto &handler : handlerMap_) {
        imsRilManager->ImsRegisterObserver(handler.second->GetSlotId(),
                                           ImsRadioEvent::IMS_RAIDO_SERVICE_STATUS, handler.second);
    }

    return true;
}
} // Telephony
} // OHOS
