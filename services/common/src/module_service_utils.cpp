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
namespace CellularCall {
int32_t ModuleServiceUtils::GetRadioStatus(int32_t slotId)
{
    auto networkSearchManager_ = PhoneManager::GetInstance().phone_[slotId]->networkSearchManager_;
    if (networkSearchManager_ == nullptr) {
        HILOG_ERROR("ModuleServiceUtils::GetRadioStatus error.");
        return ERR_GET_RADIO_STATE;
    }
    return networkSearchManager_->GetRadioState(slotId);
}

sptr<NetworkState> ModuleServiceUtils::GetNetworkStatus(int32_t slotId)
{
    auto networkSearchManager_ = PhoneManager::GetInstance().phone_[slotId]->networkSearchManager_;
    if (networkSearchManager_ == nullptr) {
        HILOG_ERROR("ModuleServiceUtils::GetNetworkStatus ERROR");
        return nullptr;
    }
    return networkSearchManager_->GetNetworkStatus(slotId);
}

std::string ModuleServiceUtils::GetIsoCountryCode(int32_t slotId)
{
    auto simFileManager = PhoneManager::GetInstance().phone_[slotId]->simFileManager_;
    if (simFileManager == nullptr) {
        HILOG_ERROR("simFileManager::GetIsoCountryCode ERROR");
        return std::string();
    }
    return Str16ToStr8(simFileManager->GetIsoCountryCode(slotId));
}

std::string ModuleServiceUtils::GetNetworkCountryCode(int32_t slotId)
{
    auto networkSearchManager_ = PhoneManager::GetInstance().phone_[slotId]->networkSearchManager_;
    if (networkSearchManager_ == nullptr) {
        HILOG_ERROR("ModuleServiceUtils::GetNetworkCountryCode ERROR");
        return std::string();
    }
    return Str16ToStr8(networkSearchManager_->GetOperatorNumeric(slotId));
}
} // namespace CellularCall
} // namespace OHOS