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
#include "cellular_call_types.h"
#include "ipc_skeleton.h"
#include "string_ex.h"

namespace OHOS {
namespace Telephony {
bool ModuleServiceUtils::GetRadioState(int32_t slotId)
{
    if (GetCore(slotId) == nullptr) {
        TELEPHONY_LOGE("ModuleServiceUtils::GetRadioState error, return.");
        return false;
    }

    int32_t ret = GetCore(slotId)->GetRadioState();
    if (ret != static_cast<int32_t>(ModemPowerState::CORE_SERVICE_POWER_ON)) {
        TELEPHONY_LOGE("ModuleServiceUtils::GetRadioState radio off.");
        return false;
    }
    TELEPHONY_LOGI("ModuleServiceUtils::GetRadioState radio on.");
    return true;
}

RadioTech ModuleServiceUtils::GetNetworkStatus(int32_t slotId)
{
    if (GetCore(slotId) == nullptr) {
        TELEPHONY_LOGE("ModuleServiceUtils::GetNetworkStatus error, return.");
        return RadioTech::RADIO_TECHNOLOGY_UNKNOWN;
    }
    return RadioTech::RADIO_TECHNOLOGY_GSM;
}

std::string ModuleServiceUtils::GetIsoCountryCode(int32_t slotId)
{
    if (GetCore(slotId) == nullptr) {
        TELEPHONY_LOGE("ModuleServiceUtils::GetIsoCountryCode error, return.");
        return std::string();
    }
    return Str16ToStr8(GetCore(slotId)->GetISOCountryCodeForSim(slotId));
}

std::string ModuleServiceUtils::GetNetworkCountryCode(int32_t slotId)
{
    if (GetCore(slotId) == nullptr) {
        TELEPHONY_LOGE("ModuleServiceUtils::GetNetworkCountryCode error, return.");
        return std::string();
    }
    return Str16ToStr8(GetCore(slotId)->GetIsoCountryCodeForNetwork(slotId));
}

bool ModuleServiceUtils::GetImsRegistrationState(int32_t slotId)
{
    if (GetCore(slotId) == nullptr) {
        TELEPHONY_LOGE("ModuleServiceUtils::GetImsRegistrationState error, return.");
        return false;
    }
    return GetCore(slotId)->GetImsRegStatus();
}

std::vector<int32_t> ModuleServiceUtils::GetSlotInfo()
{
    std::vector<int32_t> slotVector;
    int32_t slot = CoreManager::DEFAULT_SLOT_ID;
    slotVector.push_back(slot);
    return slotVector;
}

std::shared_ptr<Core> ModuleServiceUtils::GetCore(int32_t slotId)
{
    return CoreManager::GetInstance().getCore(slotId);
}
} // namespace Telephony
} // namespace OHOS