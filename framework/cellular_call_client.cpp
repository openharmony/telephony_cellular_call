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

#include "cellular_call_client.h"

#include "system_ability_definition.h"
#include "iservice_registry.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
CellularCallClient::CellularCallClient() = default;

CellularCallClient::~CellularCallClient()
{
    if (proxy_ != nullptr) {
        proxy_.clear();
        proxy_ = nullptr;
    }
}

sptr<CellularCallInterface> CellularCallClient::GetCellularCallProxy()
{
    if (proxy_ != nullptr) {
        return proxy_;
    }

    TELEPHONY_LOGE("CellularCallClient::GetCellularCallProxy, get remote service");
    auto managerPtr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (managerPtr == nullptr) {
        TELEPHONY_LOGE("GetCellularCallProxy return, get system ability manager error.");
        return nullptr;
    }
    auto remoteObjectPtr = managerPtr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    if (remoteObjectPtr == nullptr) {
        TELEPHONY_LOGE("GetCellularCallProxy return, remote service not exists.");
        return nullptr;
    }
    proxy_ = iface_cast<CellularCallInterface>(remoteObjectPtr);
    return proxy_;
}

bool CellularCallClient::IsConnect() const
{
    return (proxy_ != nullptr);
}
} // namespace Telephony
} // namespace OHOS
