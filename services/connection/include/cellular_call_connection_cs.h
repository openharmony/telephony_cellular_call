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

#include "call_manager_type.h"
#include "hril_call_parcel.h"
#include "i_tel_ril_manager.h"
#include "telephony_errors.h"
#include "cellular_call_data_struct.h"
#include "cellular_call_hilog.h"

namespace OHOS {
namespace CellularCall {
class CellularCallConnectionCS {
public:
    /**
     * MO new  CellularCallConnectionCS .
     * @param phoneNetType gsm or cdma
     *
     */
    explicit CellularCallConnectionCS();

    /**
     * ~CellularCallConnectionCS. deconstructor
     */
    ~CellularCallConnectionCS();

    /**
     *  DialRequest
     * @param DialRequestStruct
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t DialRequest(const DialRequestStruct &dialRequest, int32_t slotId);

    /**
     *  EndRequest
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t EndRequest(int32_t slotId);

    /**
     *  AnswerRequest
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t AnswerRequest(int32_t slotId);

    /**
     *  RejectRequest
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t RejectRequest(int32_t slotId);

    /**
     *  SwapWaitingHoldingAndActiveRequest
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t HoldingAndActiveRequest(int32_t slotId);

    /**
     *  JoinRequest
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t JoinRequest(int32_t slotId);

    /**
     *  SplitRequest
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t SplitRequest(int32_t slotId);

    /**
     *  SendCDMAThreeWayDialRequest
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t SendCDMAThreeWayDialRequest(int32_t slotId);

    /**
     * Set or Update CallReportInfo
     * @param callReportInfo
     */
    void SetOrUpdateCallReportInfo(TelephonyCallManager::CallReportInfo callReportInfo);

    /**
     * get CallReportInfo
     *
     * @return TelephonyCallManager::CallReportInfo
     */
    TelephonyCallManager::CallReportInfo GetCallReportInfo();

    /**
     * SetStatus
     * @param state
     */
    void SetStatus(TelCallStates state);

    /**
     * GetStatus
     * @return TelCallStates
     */
    TelCallStates GetStatus();

    /**
     * IsRingingState.
     *
     * @return bool IsRingingState
     */
    bool IsRingingState();

    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "CellularCallConnectionCS"};
    TelephonyCallManager::CallReportInfo callReportInfo_;
    bool flag_ = false;
    int index_ = 1;

private:
    /**
     * Get Manager for core service
     * @param slotId
     * @return IRilManager for core service
     */
    IRilManager *GetManager(int32_t slotId);
};
} // namespace CellularCall
} // namespace OHOS

#endif // CELLULAR_CALL_CONNECTION_CS_H