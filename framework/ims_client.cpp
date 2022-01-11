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

#include "ims_client.h"

#include "iservice_registry.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
ImsClient::ImsClient() = default;

ImsClient::~ImsClient()
{
    if (proxy_ != nullptr) {
        proxy_.clear();
        proxy_ = nullptr;
    }
}

sptr<ImsInterface> ImsClient::GetImsProxy()
{
    if (proxy_ != nullptr) {
        return proxy_;
    }

    auto managerPtr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (managerPtr == nullptr) {
        TELEPHONY_LOGE("GetImsProxy return, get system ability manager error.");
        return nullptr;
    }
    auto remoteObjectPtr = managerPtr->CheckSystemAbility(TELEPHONY_IMS_SYS_ABILITY_ID);
    if (remoteObjectPtr == nullptr) {
        TELEPHONY_LOGE("GetImsProxy return, remote service not exists.");
        return nullptr;
    }
    proxy_ = iface_cast<ImsInterface>(remoteObjectPtr);
    return proxy_;
}

bool ImsClient::IsConnect() const
{
    return (proxy_ != nullptr);
}
} // namespace Telephony
} // namespace OHOS
