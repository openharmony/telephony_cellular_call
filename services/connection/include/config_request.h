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

#ifndef CELLULAR_CALL_CONFIG_REQUEST_H
#define CELLULAR_CALL_CONFIG_REQUEST_H

#include <core_manager.h>
#include "telephony_log_wrapper.h"
#include "base_request.h"

namespace OHOS {
namespace Telephony {
class ConfigRequest : BaseRequest {
public:
    /**
     * Set Call Preference Mode Request
     * @param mode
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetCallPreferenceModeRequest(int32_t mode);

    /**
     * Get Call Preference Mode Request
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t GetCallPreferenceModeRequest();

    /**
     * Set Lte Ims Switch Status Request
     * @param active
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetLteImsSwitchStatusRequest(int32_t active);

    /**
     * Get Lte Ims Switch Status Request
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t GetLteImsSwitchStatusRequest();

private:
    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "ConfigRequest"};
};
} // namespace Telephony
} // namespace OHOS
#endif // CELLULAR_CALL_CONFIG_REQUEST_H
