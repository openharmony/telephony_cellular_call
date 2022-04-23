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

#ifndef IMS_SMS_REGISTER_H
#define IMS_SMS_REGISTER_H

#include "singleton.h"
#include "ims_sms_callback_interface.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
class ImsSmsRegister {
    DECLARE_DELAYED_SINGLETON(ImsSmsRegister)

public:
    /**
     * GetImsSmsConfigResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */

    int32_t ImsSendMessageResponse(const ImsResponseInfo &info);
    /**
     * UpdateImsSendMessageResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateImsSendMessageResponse(const ImsResponseInfo &info, const SendSmsResultInfo &result);

    /**
     * UpdateImsSetSmsConfigResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateImsSetSmsConfigResponse(const ImsResponseInfo &info);

    /**
     * UpdateImsGetSmsConfigResponse
     *
     * @param info ImsResponseInfo
     * @param imsSmsConfig 1:ims sms is enabled, 0:ims sms is disabled
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateImsGetSmsConfigResponse(const ImsResponseInfo &info, int32_t imsSmsConfig);

    /**
     * Is ImsSmsCallback Exists
     *
     * @return bool
     */
    bool IsCallBackExists();

    /**
     * Register ImsSmsCallback
     *
     * @param sptr<ImsSmsback>
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t RegisterImsSmsCallBack(const sptr<ImsSmsCallbackInterface> &callback);

private:
    sptr<ImsSmsCallbackInterface> imsSmsCallback_ = nullptr;
};
} // namespace Telephony
} // namespace OHOS

#endif // IMS_SMS_REGISTER_H
