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

#ifndef CELLULAR_CALL_CONNECTION_IMS_H
#define CELLULAR_CALL_CONNECTION_IMS_H

#include <vector>
#include "base_connection.h"

namespace OHOS {
namespace Telephony {
class CellularCallConnectionIMS : public BaseConnection {
public:
    /**
     * Constructor
     */
    CellularCallConnectionIMS() = default;

    /**
     * Destructor
     */
    ~CellularCallConnectionIMS() = default;

    /**
     *  Dial Request
     *
     * @param ImsDialInfoStruct
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t DialRequest(const ImsDialInfoStruct &dialRequest, int32_t slotId);

    /**
     *  End Request
     *
     * @param index
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t EndRequest(int32_t index, int32_t slotId);

    /**
     * Answer Request
     * @param videoState
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t AnswerRequest(int32_t videoState, int32_t slotId);

    /**
     * Reject Request
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t RejectRequest(int32_t slotId);

    /**
     * Swap Request
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t SwapRequest(int32_t slotId);

    /**
     * Hold Request
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t HoldRequest(int32_t slotId);

    /**
     * Active Request
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t ActiveRequest(int32_t slotId);

    /**
     * CombineConferenceRequest
     *
     * @param slotId
     * @param voiceCall
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t CombineConferenceRequest(int32_t slotId, int32_t voiceCall);

    /**
     * CallSupplement Request
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t CallSupplementRequest(CallSupplementType type, int32_t slotId);

    /**
     * CellularCallConnectionIMS GetImsCallsDataRequest
     *
     * @param slotId
     * @param lastCallsDataFlag
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag);

    /**
     * Send Dtmf Request
     *
     * @param char cDtmfCode
     * @param index
     * @param slotId
     * @return Error Code: Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SendDtmfRequest(char cDtmfCode, int32_t index, int32_t slotId) const;

    /**
     * Start Dtmf Request
     *
     * @param char cDtmfCode
     * @param index
     * @param slotId
     * @return Error Code: Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t StartDtmfRequest(char cDtmfCode, int32_t index, int32_t slotId) const;

    /**
     * Stop Dtmf Request
     *
     * @param index
     * @param slotId
     * @return Error Code: Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t StopDtmfRequest(int32_t index, int32_t slotId) const;

private:
    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "CellularCallConnectionIMS"};
};
} // namespace Telephony
} // namespace OHOS

#endif // CELLULAR_CALL_CONNECTION_IMS_H