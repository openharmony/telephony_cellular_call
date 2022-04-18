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

#include "module_service_utils.h"

#include "ipc_skeleton.h"
#include "string_ex.h"

#include "cellular_call_register.h"
#include "ims_call_client.h"
#include "ims_call_death_recipient.h"
#include "telephony_log_wrapper.h"
#include "telephony_types.h"

namespace OHOS {
namespace Telephony {
bool ModuleServiceUtils::GetRadioState(int32_t slotId)
{
    int32_t ret = CoreManagerInner::GetInstance().GetRadioState(slotId);
    if (ret != ModemPowerState::CORE_SERVICE_POWER_ON) {
        TELEPHONY_LOGE("ModuleServiceUtils::GetRadioState radio off.");
        return false;
    }
    return true;
}

PhoneType ModuleServiceUtils::GetNetworkStatus(int32_t slotId)
{
    return CoreManagerInner::GetInstance().GetPhoneType(slotId);
}

std::string ModuleServiceUtils::GetIsoCountryCode(int32_t slotId)
{
    return Str16ToStr8(CoreManagerInner::GetInstance().GetISOCountryCodeForSim(slotId));
}

std::string ModuleServiceUtils::GetNetworkCountryCode(int32_t slotId)
{
    return Str16ToStr8(CoreManagerInner::GetInstance().GetIsoCountryCodeForNetwork(slotId));
}

bool ModuleServiceUtils::GetImsRegistrationState(int32_t slotId)
{
    return CoreManagerInner::GetInstance().GetImsRegStatus(slotId);
}

std::vector<int32_t> ModuleServiceUtils::GetSlotInfo()
{
    const int32_t slotSingle = 1;
    const int32_t slotDouble = 2;
    std::vector<int32_t> slotVector;
    if (SIM_SLOT_COUNT == slotSingle) {
        slotVector.push_back(DEFAULT_SIM_SLOT_ID);
    } else if (SIM_SLOT_COUNT == slotDouble) {
        slotVector.push_back(SIM_SLOT_0);
        slotVector.push_back(SIM_SLOT_1);
    }
    return slotVector;
}

bool ModuleServiceUtils::NeedCallImsService() const
{
    if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("ImsCallClient is nullptr.");
        return false;
    }
    auto remoteProxy = DelayedSingleton<ImsCallClient>::GetInstance()->GetImsCallProxy();
    if (remoteProxy == nullptr) {
        TELEPHONY_LOGE("NeedCallImsService return, ims service SA not exists.");
        return false;
    }
    return true;
}

sptr<ImsCallInterface> ModuleServiceUtils::GetImsServiceRemoteObject() const
{
    if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("ImsCallClient is nullptr.");
        return nullptr;
    }
    return DelayedSingleton<ImsCallClient>::GetInstance()->GetImsCallProxy();
}

int32_t ModuleServiceUtils::ConnectImsService()
{
    auto managerPtr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (managerPtr == nullptr) {
        TELEPHONY_LOGE("ConnectImsService return, get system ability manager error.");
        return TELEPHONY_ERROR;
    }
    int32_t imsSaId = TELEPHONY_IMS_SYS_ABILITY_ID;
    auto iRemoteObjectPtr = managerPtr->GetSystemAbility(imsSaId);
    if (iRemoteObjectPtr == nullptr) {
        TELEPHONY_LOGE("ConnectImsService return, remote service not exists.");
        return TELEPHONY_ERROR;
    }

    std::weak_ptr<ModuleServiceUtils> weakPtr = shared_from_this();
    auto deathCallback = [weakPtr](const wptr<IRemoteObject> &object) {
        auto sharedPtr = weakPtr.lock();
        if (sharedPtr) {
            sharedPtr->NotifyDeath();
        }
    };
    sptr<IRemoteObject::DeathRecipient> imsRecipient_ =
        (std::make_unique<ImsCallDeathRecipient>(deathCallback)).release();
    if (imsRecipient_ == nullptr) {
        TELEPHONY_LOGE("ConnectImsService return, imsRecipient_ is nullptr.");
        return TELEPHONY_ERROR;
    }
    if (!iRemoteObjectPtr->AddDeathRecipient(imsRecipient_)) {
        TELEPHONY_LOGE("ConnectImsService return, add death recipient fail.");
        return TELEPHONY_ERROR;
    }
    return TELEPHONY_SUCCESS;
}

void ModuleServiceUtils::NotifyDeath()
{
    TELEPHONY_LOGI("service is dead, connect again");
    for (uint32_t i = 0; i < CONNECT_MAX_TRY_COUNT; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(CONNECT_SERVICE_WAIT_TIME));
        int32_t result = ConnectImsService();
        if (result != TELEPHONY_SUCCESS) {
            TELEPHONY_LOGI("connect Ims service successful");
            return;
        }
    }
    TELEPHONY_LOGI("connect cellular call service failed");
}
} // namespace Telephony
} // namespace OHOS