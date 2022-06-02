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

#include "ims_call_death_recipient.h"
#include "ims_call_client.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
ImsCallDeathRecipient::ImsCallDeathRecipient()
{}

void ImsCallDeathRecipient::OnRemoteDied(const OHOS::wptr<OHOS::IRemoteObject> &object)
{
    std::shared_ptr<ImsCallClient> imsCallClient =
        DelayedSingleton<ImsCallClient>::GetInstance();
    if (imsCallClient == nullptr) {
        TELEPHONY_LOGE("ImsCallDeathRecipient OnRemoteDied, imsCallClient is nullptr!");
        return;
    }

    bool res = false;
    int32_t i = 0;

    do {
        TELEPHONY_LOGI("ImsCallDeathRecipient ReConnect service!");
        imsCallClient->Clean();
        res = imsCallClient->ReConnectService();
        if (!res) {
            i++;
            sleep(1);
        }
    } while (!res && (i < ImsCallClient::RE_CONNECT_SERVICE_COUNT_MAX));
    if (!res) {
        TELEPHONY_LOGE("ImsCallDeathRecipient Reconnect service is failed!");
        return;
    }
    TELEPHONY_LOGI("ImsCallDeathRecipient Reconnect service is successful!");
}
} // namespace Telephony
} // namespace OHOS
