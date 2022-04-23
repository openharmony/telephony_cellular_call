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

#include "ims_core_service_register.h"
#include "telephony_errors.h"

namespace OHOS {
namespace Telephony {
ImsCoreServiceRegister::ImsCoreServiceRegister() {}

ImsCoreServiceRegister::~ImsCoreServiceRegister() {}

int32_t ImsCoreServiceRegister::UpdateImsServiceStatusReport(int32_t slotId, const ImsServiceStatus &imsServiceStatus)
{
    TELEPHONY_LOGI("ImsServiceStatusReport");
    if (imsCoreServiceCallback_ == nullptr) {
        TELEPHONY_LOGE("ImsCoreServiceCallback is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    return imsCoreServiceCallback_->ImsServiceStatusReport(slotId, imsServiceStatus);
}

int32_t ImsCoreServiceRegister::UpdateImsNetworkStateChange(int32_t slotId)
{
    TELEPHONY_LOGI("UpdateImsNetworkStateChange");
    if (imsCoreServiceCallback_ == nullptr) {
        TELEPHONY_LOGE("UpdateImsNetworkStateChange is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCoreServiceCallback_->ImsNetworkStateChange(slotId);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCoreServiceRegister::UpdateImsRegistrationStatusResponse(
    const ImsResponseInfo &info, const ImsRegistrationStatus &imsRegStatus)
{
    TELEPHONY_LOGI("UpdateImsRegistrationStatusResponse");
    if (imsCoreServiceCallback_ == nullptr) {
        TELEPHONY_LOGE("UpdateImsRegistrationStatusResponse is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCoreServiceCallback_->ImsRegistrationStatusResponse(info, imsRegStatus);
    return TELEPHONY_SUCCESS;
}

int32_t ImsCoreServiceRegister::RegisterImsCoreServiceCallback(const sptr<ImsCoreServiceCallbackInterface> &callback)
{
    imsCoreServiceCallback_ = callback;
    return TELEPHONY_SUCCESS;
}

bool ImsCoreServiceRegister::IsCallBackExists()
{
    return imsCoreServiceCallback_ != nullptr;
}
} // namespace Telephony
} // namespace OHOS
