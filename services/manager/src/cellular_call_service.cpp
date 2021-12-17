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

#include <sstream>

#include "string_ex.h"
#include "system_ability_definition.h"

#include "cellular_call_dump_helper.h"
#include "module_service_utils.h"

namespace OHOS {
namespace Telephony {
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
    TELEPHONY_LOGI("CellularCallService Init");
    eventLoop_ = AppExecFwk::EventRunner::Create("CellularCallService");
    if (eventLoop_ == nullptr) {
        TELEPHONY_LOGE("failed to create EventRunner");
        return false;
    }
    CreateHandler();
    SendEventRegisterHandler();
    TELEPHONY_LOGI("init success");
    return true;
}

void CellularCallService::OnStart()
{
    TELEPHONY_LOGI("CellularCallService OnStart");
    bindTime_ =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    if (state_ == ServiceRunningState::STATE_RUNNING) {
        TELEPHONY_LOGE("CellularCallService has already started.");
        return;
    }
    if (!Init()) {
        TELEPHONY_LOGE("failed to init service.");
        return;
    }
    state_ = ServiceRunningState::STATE_RUNNING;
    if (eventLoop_ != nullptr) {
        eventLoop_->Run();
    }
    bool ret = Publish(DelayedSingleton<CellularCallService>::GetInstance().get());
    if (!ret) {
        TELEPHONY_LOGE("CellularCallService::OnStart Publish failed!");
    }
    endTime_ =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    TELEPHONY_LOGI("CellularCallService start success.");
}

void CellularCallService::OnStop()
{
    TELEPHONY_LOGI("CellularCallService stop service");
    if (eventLoop_ != nullptr) {
        eventLoop_.reset();
    }

    state_ = ServiceRunningState::STATE_STOPPED;

    HandlerResetUnRegister();
}

void CellularCallService::RegisterHandler()
{
    TELEPHONY_LOGI("connect core service Register Handler start  ");
    for (uint32_t i = 0; i < CONNECT_MAX_TRY_COUNT; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(CONNECT_SERVICE_WAIT_TIME));
        auto core = CoreManager::GetInstance().getCore(CoreManager::DEFAULT_SLOT_ID);
        if (core != nullptr && core->IsInitCore()) {
            RegisterCoreServiceHandler();
            break;
        }
        TELEPHONY_LOGW("connect core service Register Handler null or not init ");
    }
    TELEPHONY_LOGI("connect core service Register Handler end ");
}

std::shared_ptr<CellularCallHandler> CellularCallService::GetHandler(int32_t slot)
{
    return handlerMap_[slot];
}

void CellularCallService::CreateHandler()
{
    ModuleServiceUtils obtain;
    std::vector<int32_t> slotVector = obtain.GetSlotInfo();
    for (const auto &it : slotVector) {
        auto handler = std::make_shared<CellularCallHandler>(eventLoop_);
        handler->SetSlotId(it);
        handler->SetCsControl(GetCsControl(it));
        handler->SetImsControl(GetImsControl(it));
        handlerMap_.insert(std::make_pair(it, handler));
    }
}

void CellularCallService::HandlerResetUnRegister()
{
    for (const auto &it : handlerMap_) {
        int32_t slot = it.first;
        auto handler = it.second;
        if (handler != nullptr) {
            handler.reset();
        }
        auto core = CoreManager::GetInstance().getCore(slot);
        if (core == nullptr) {
            TELEPHONY_LOGE("CellularCallService::HandlerResetUnRegister, core is nullptr");
            return;
        }
        core->UnRegisterCoreNotify(handler, ObserverHandler::RADIO_CALL_STATE);
        core->UnRegisterCoreNotify(handler, ObserverHandler::RADIO_AVAIL);
        core->UnRegisterCoreNotify(handler, ObserverHandler::RADIO_NOT_AVAIL);
        core->UnRegisterCoreNotify(handler, ObserverHandler::RADIO_CALL_WAITING);
        core->UnRegisterCoreNotify(handler, ObserverHandler::RADIO_CALL_CONNECT);
        core->UnRegisterCoreNotify(handler, ObserverHandler::RADIO_CALL_END);
        core->UnRegisterCoreNotify(handler, ObserverHandler::RADIO_CALL_STATUS_INFO);
        core->UnRegisterCoreNotify(handler, ObserverHandler::RADIO_CALL_IMS_SERVICE_STATUS);

        if (GetCsControl(slot) == nullptr) {
            TELEPHONY_LOGE("CellularCallService::HandlerResetUnRegister, csControl is nullptr");
            return;
        }
        GetCsControl(slot)->ReleaseAllConnection();

        if (GetImsControl(slot) == nullptr) {
            TELEPHONY_LOGE("CellularCallService::HandlerResetUnRegister, imsControl is nullptr");
            return;
        }
        GetImsControl(slot)->ReleaseAllConnection();
    }
}

void CellularCallService::RegisterCoreServiceHandler()
{
    for (const auto &it : handlerMap_) {
        auto handler = it.second;
        auto core = CoreManager::GetInstance().getCore(it.first);
        if (core == nullptr) {
            TELEPHONY_LOGE("RegisterCoreServiceHandler, core is nullptr");
            return;
        }
        if (handler != nullptr) {
            core->RegisterCoreNotify(handler, ObserverHandler::RADIO_CALL_STATE, nullptr);
            core->RegisterCoreNotify(handler, ObserverHandler::RADIO_AVAIL, nullptr);
            core->RegisterCoreNotify(handler, ObserverHandler::RADIO_NOT_AVAIL, nullptr);
            core->RegisterCoreNotify(handler, ObserverHandler::RADIO_CALL_WAITING, nullptr);
            core->RegisterCoreNotify(handler, ObserverHandler::RADIO_CALL_CONNECT, nullptr);
            core->RegisterCoreNotify(handler, ObserverHandler::RADIO_CALL_END, nullptr);
            core->RegisterCoreNotify(handler, ObserverHandler::RADIO_CALL_STATUS_INFO, nullptr);
            core->RegisterCoreNotify(handler, ObserverHandler::RADIO_CALL_IMS_SERVICE_STATUS, nullptr);
        }

        CellularCallConfig config;
        if (config.GetCallPreferenceMode() != TELEPHONY_SUCCESS) {
            TELEPHONY_LOGW("RegisterCoreServiceHandler, GetCallPreferenceMode request fail");
        }
        if (config.GetLteImsSwitchStatus() != TELEPHONY_SUCCESS) {
            TELEPHONY_LOGW("RegisterCoreServiceHandler, GetLteImsSwitchStatus request fail");
        }
    }
}

void CellularCallService::SendEventRegisterHandler()
{
    int64_t delayTime_ = 1000;
    int32_t slot = CoreManager::DEFAULT_SLOT_ID;
    auto handler = handlerMap_[slot];
    if (handler == nullptr) {
        TELEPHONY_LOGE("SendEventRegisterHandler return, handler is nullptr");
        return;
    }
    handler->SendEvent(handler->REGISTER_HANDLER_ID, delayTime_, CellularCallHandler::Priority::HIGH);
}

int32_t CellularCallService::Dump(std::int32_t fd, const std::vector<std::u16string> &args)
{
    if (fd < 0) {
        TELEPHONY_LOGE("dump fd invalid");
        return TELEPHONY_ERR_FAIL;
    }
    std::vector<std::string> argsInStr;
    for (const auto &arg : args) {
        argsInStr.emplace_back(Str16ToStr8(arg));
    }
    std::string result;
    CellularCallDumpHelper dumpHelper;
    if (dumpHelper.Dump(argsInStr, result)) {
        std::int32_t ret = dprintf(fd, "%s", result.c_str());
        if (ret < 0) {
            TELEPHONY_LOGE("dprintf to dump fd failed");
            return TELEPHONY_ERR_FAIL;
        }
        return TELEPHONY_SUCCESS;
    }
    TELEPHONY_LOGW("dumpHelper failed");
    return TELEPHONY_ERR_FAIL;
}

std::string CellularCallService::GetBindTime()
{
    std::ostringstream oss;
    oss << bindTime_;
    return oss.str();
}

std::string CellularCallService::GetEndTime()
{
    std::ostringstream oss;
    oss << endTime_;
    return oss.str();
}

std::string CellularCallService::GetSpendTime()
{
    spendTime_ = endTime_ - bindTime_;
    std::ostringstream oss;
    oss << spendTime_;
    return oss.str();
}
} // namespace Telephony
} // namespace OHOS