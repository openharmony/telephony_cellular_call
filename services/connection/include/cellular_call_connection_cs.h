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

#ifndef CELLULAR_CALL_CONNECTION_CS_H
#define CELLULAR_CALL_CONNECTION_CS_H

#include "hril_call_parcel.h"
#include "base_connection.h"

namespace OHOS {
namespace Telephony {
class CellularCallConnectionCS : public BaseConnection {
public:
    /**
     * Constructor
     */
    CellularCallConnectionCS() = default;

    /**
     * Destructor
     */
    ~CellularCallConnectionCS() = default;

    /**
     *  DialRequest
     * @param DialRequestStruct
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t DialRequest(const DialRequestStruct &dialRequest, int32_t slotId);

    /**
     *  HangUpRequest
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t HangUpRequest(int32_t slotId);

    /**
     *  AnswerRequest
     *
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t AnswerRequest(int32_t slotId);

    /**
     *  RejectRequest
     *
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t RejectRequest(int32_t slotId);

    /**
     *  SwitchCallRequest
     *
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SwitchCallRequest(int32_t slotId);

    /**
     *  HoldRequest
     *
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t HoldRequest(int32_t slotId);

    /**
     *  UnHoldCallRequest
     *
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UnHoldCallRequest(int32_t slotId);

    /**
     *  CombineConferenceRequest
     *
     * @param slotId
     * @param voiceCall
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t CombineConferenceRequest(int32_t slotId, int32_t voiceCall);

    /**
     *  SeparateConferenceRequest
     *
     * @param index
     * @param slotId
     * @param voiceCall
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SeparateConferenceRequest(int32_t index, int32_t slotId, int32_t voiceCall);

    /**
     * CallSupplement Request
     *
     * 22083-400_2001 2 Call hold
     * 3GPP TS 22.030 [3]
     *
     * @param CallSupplementType
     * @param slotId
     * @return Error Code: Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t CallSupplementRequest(CallSupplementType type, int32_t slotId);

    /**
     * CSControl GetCsCallsDataRequest
     * 27007-430_2001 7.18 List current calls +CLCC
     * 3GPP TS 22.030 [19]
     *
     * Returns list of current calls of ME.
     *
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag);

    /**
     *  SendCDMAThreeWayDialRequest
     *
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SendCDMAThreeWayDialRequest(int32_t slotId);

    /**
     *  SendDtmfRequest
     *
     * @param char cDtmfCode
     * @param index
     * @param slotId
     * @return Error Code: Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SendDtmfRequest(char cDtmfCode, int32_t index, int32_t slotId) const;

    /**
     *  StartDtmfRequest
     *
     * @param char cDtmfCode
     * @param index
     * @param slotId
     * @return Error Code: Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t StartDtmfRequest(char cDtmfCode, int32_t index, int32_t slotId) const;

    /**
     *  StopDtmfRequest
     *
     * @param index
     * @param slotId
     * @return Error Code: Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t StopDtmfRequest(int32_t index, int32_t slotId) const;

    /**
     *  SendDtmfStringRequest
     * @param
     * @return Error Code: Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SendDtmfStringRequest(const std::string &sDtmfCode, int32_t on, int32_t off, int32_t slotId);

    /**
     * RegisterHandler
     */
    void RegisterHandler();

private:
    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "CellularCallConnectionCS"};
};
} // namespace Telephony
} // namespace OHOS

#endif // CELLULAR_CALL_CONNECTION_CS_H