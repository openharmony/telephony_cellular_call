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

#ifndef CELLULAR_CALL_SUPPLEMENT_REQUEST_H
#define CELLULAR_CALL_SUPPLEMENT_REQUEST_H

#include "cellular_call_handler.h"

#include "base_request.h"

namespace OHOS {
namespace Telephony {
class SupplementRequest : BaseRequest {
public:
    /**
     * Inquire Clip Request
     *
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t InquireClipRequest(int32_t slotId);

    /**
     * set Clir Request
     *
     * @param action
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetClirRequest(int32_t slotId, int32_t action);

    /**
     * Inquire Clir Request
     *
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t InquireClirRequest(int32_t slotId);

    /**
     * Inquire Call Transfer Request
     *
     * @param reason
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallTransferRequest(int32_t slotId, int32_t reason);

    /**
     * Set Call Transfer Request
     *
     * @param action
     * @param reason
     * @param transferNum
     * @param classType
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCallTransferRequest(
        int32_t slotId, int32_t action, int32_t reason, const std::string &transferNum, int32_t classType);

    /**
     * Get Call Restriction
     *
     * @param fac
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallRestrictionRequest(int32_t slotId, const std::string &fac);

    /**
     * Set Call Restriction
     *
     * @param fac
     * @param mode
     * @param pw
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCallRestrictionRequest(int32_t slotId, std::string &fac, int32_t mode, std::string &pw);

    /**
     * Set CallWaiting Request
     *
     * @param bool
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCallWaitingRequest(int32_t slotId, bool activate);

    /**
     * Get Call Waiting Request
     *
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallWaitingRequest(int32_t slotId);

    /**
     * Send ussd Request
     *
     * @param msg
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SendUssdRequest(int32_t slotId, const std::string &msg);

    /*
     * SIM PIN unlock
     *
     * @param slotId The ID of SIM slot
     * @param newPin The new pin code for unlock SIM
     * @param oldPin The old pin code for unlock SIM
     * @return Returns true on success.
     */
    bool AlterPinPassword(int32_t slotId, std::string newPin, std::string oldPin);

    /**
     * SIM PUK unlock
     *
     * @param slotId The ID of SIM slot
     * @param newPin  The new pin code for unlock SIM
     * @param puk The puk code for unlock SIM
     * @return Returns true on success.
     */
    bool UnlockPuk(int32_t slotId, std::string newPin, std::string puk);

    /**
     * SIM PIN2 unlock
     *
     * @param slotId The ID of SIM slot
     * @param newPin2 The new pin2 code for unlock SIM
     * @param oldPin2 The old pin2 code for unlock SIM
     * @return Returns true on success.
     */
    bool AlterPin2Password(int32_t slotId, std::string newPin2, std::string oldPin2);

    /**
     * SIM PUK2 unlock
     *
     * @param slotId The ID of SIM slot
     * @param newPin2 The new pin2 code for unlock SIM
     * @param puk2 The puk2 code for unlock SIM
     * @return Returns true on success.
     */
    bool UnlockPuk2(int32_t slotId, std::string newPin2, std::string puk2);

private:
    /**
     * GetMMIHandler
     *
     * @return std::shared_ptr<MMIHandler>
     */
    std::shared_ptr<CellularCallHandler> GetMMIHandler(int32_t slotId) const;

private:
    ModuleServiceUtils moduleUtils_;
};
} // namespace Telephony
} // namespace OHOS
#endif // CELLULAR_CALL_SUPPLEMENT_REQUEST_H
