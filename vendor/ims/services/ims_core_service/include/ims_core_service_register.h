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

#ifndef IMS_CORE_SERVICE_REGISTER_H
#define IMS_CORE_SERVICE_REGISTER_H

#include "singleton.h"
#include "ims_core_service_callback_interface.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
class ImsCoreServiceRegister {
    DECLARE_DELAYED_SINGLETON(ImsCoreServiceRegister)

public:
    /**
     * Is ImsCoreServiceCallbackInterface Exists
     *
     * @return bool
     */
    bool IsCallBackExists();

    /**
     * UpdateImsServiceStatusReport
     * @param int32_t
     * @param ImsServiceStatus
     * @return Returns TELEPHONY_SUCCESS on success, others on failure
     */
    int32_t UpdateImsServiceStatusReport(int32_t slotId, const ImsServiceStatus &imsServiceStatus);

    /**
     * ImsNetworkStateChange
     *
     * @param slotId
     * @return Returns nullptr on failure, others on success.
     */
    int32_t UpdateImsNetworkStateChange(int32_t slotId);

    /**
     * ImsRegistrationStatusResponse
     *
     * @param imsRegStatus
     * @return Returns nullptr on failure, others on success.
     */
    int32_t UpdateImsRegistrationStatusResponse(
        const ImsResponseInfo &info, const ImsRegistrationStatus &imsRegStatus);

    /**
     * Register ImsCoreServiceCallbackInterface
     *
     * @param sptr<ImsCoreServiceCallbackInterface>
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t RegisterImsCoreServiceCallback(const sptr<ImsCoreServiceCallbackInterface> &callback);
private:
    sptr<ImsCoreServiceCallbackInterface> imsCoreServiceCallback_ = nullptr;
};
} // namespace Telephony
} // namespace OHOS

#endif // IMS_CORE_SERVICE_REGISTER_H
