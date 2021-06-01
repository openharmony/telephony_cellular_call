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

#include "cellular_call_service.h"
#include "system_ability_definition.h"
#include "phone_manager.h"
#include "cs_control.h"

namespace OHOS {
namespace CellularCall {
const int32_t M_SLEEPT_TIME = 5;
bool g_registerResult =
    SystemAbility::MakeAndRegisterAbility(DelayedSingleton<CellularCallService>::GetInstance().get());

CellularCallService::CellularCallService() : SystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID, true)
{
    state_ = ServiceRunningState::STATE_STOPPED;
}

CellularCallService::~CellularCallService()
{
    state_ = ServiceRunningState::STATE_STOPPED;
}

bool CellularCallService::Init()
{
    HILOG_DEBUG("CellularCallService Init");
    eventLoop_ = AppExecFwk::EventRunner::Create("CellularCallService");
    if (eventLoop_ == nullptr) {
        HILOG_ERROR("failed to create EventRunner");
        return false;
    }
    handler_ = std::make_shared<CellularCallHandler>(eventLoop_);
    if (handler_ == nullptr) {
        HILOG_ERROR("failed to make_shared handler_");
        return false;
    }
    RegisterHandler();
    HILOG_DEBUG("init success");
    return true;
}

void CellularCallService::OnStart()
{
    HILOG_DEBUG("CellularCallService OnStart");
    if (state_ == ServiceRunningState::STATE_RUNNING) {
        HILOG_DEBUG("CellularCallService has already started.");
        return;
    }
    if (!Init()) {
        HILOG_ERROR("failed to init service.");
        return;
    }
    state_ = ServiceRunningState::STATE_RUNNING;
    if (eventLoop_ != nullptr) {
        eventLoop_->Run();
    }
    bool ret = Publish(DelayedSingleton<CellularCallService>::GetInstance().get());
    if (!ret) {
        HILOG_DEBUG("CellularCallService::Init Publish failed!");
    }
    HILOG_DEBUG("CellularCallService start success.");
}

void CellularCallService::OnStop()
{
    HILOG_DEBUG("CellularCallService stop service");
    if (eventLoop_ != nullptr) {
        eventLoop_.reset();
    }
    if (handler_ != nullptr) {
        handler_.reset();
    }
    state_ = ServiceRunningState::STATE_STOPPED;
    DelayedSingleton<CSControl>::GetInstance()->ReleaseAllConnection();
    IRilManager *rilManager = PhoneManager::GetInstance().phone_[slotId_]->rilManager_;
    if (rilManager == nullptr) {
        HILOG_ERROR("CellularCallService::OnStop, rilManager is nullptr");
        return;
    }
    rilManager->UnRegisterPhoneNotify(ObserverHandler::RADIO_CALL_STATE);
    rilManager->UnRegisterPhoneNotify(ObserverHandler::RADIO_AVAIL);
    rilManager->UnRegisterPhoneNotify(ObserverHandler::RADIO_NOT_AVAIL);
}

void CellularCallService::RegisterHandler()
{
    sleep(M_SLEEPT_TIME);
    IRilManager *rilManager = PhoneManager::GetInstance().phone_[slotId_]->rilManager_;
    if (rilManager == nullptr) {
        HILOG_ERROR("RegisterHandler, rilManager is nullptr");
        return;
    }
    if (handler_ != nullptr) {
        rilManager->RegisterPhoneNotify(handler_, ObserverHandler::RADIO_CALL_STATE, nullptr);
        rilManager->RegisterPhoneNotify(handler_, ObserverHandler::RADIO_AVAIL, nullptr);
        rilManager->RegisterPhoneNotify(handler_, ObserverHandler::RADIO_NOT_AVAIL, nullptr);
    }
}

void CellularCallService::OnDump()
{
    HILOG_DEBUG("CellularCallService OnDump");
}

std::shared_ptr<CellularCallHandler> CellularCallService::GetHandler()
{
    return handler_;
}
} // namespace CellularCall
} // namespace OHOS