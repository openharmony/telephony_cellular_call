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

#ifndef CELLULAR_CALL_CONTROL_CS_H
#define CELLULAR_CALL_CONTROL_CS_H

#include <call_manager_type.h>

#include "singleton.h"

#include "hril_call_parcel.h"
#include "event_handler.h"

#include "cellular_call_connection_cs.h"
#include "mmi_handler.h"

namespace OHOS {
namespace CellularCall {
class CSControl {
    DECLARE_DELAYED_SINGLETON(CSControl)
public:
    /**
     * CSControl Dial
     *
     * 27007-430_2001 6.27 Informative examples
     * 3GPP TS 22.030 [19]
     *
     * originate a voice call
     *
     * @param CellularCallInfo
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t Dial(const CellularCallInfo &callInfo);

    /**
     * CSControl End
     *
     * 27007-430_2001 7.13 Call related supplementary services +CHLD
     * 3GPP TS 22.030 [19]
     *
     * release the active call
     *
     * @param CellularCallInfo
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t End(const CellularCallInfo &callInfo);

    /**
     * CSControl Answer
     * 27007-430_2001 6.6 Alternating mode call control method
     * 3GPP TS 22.030 [19]
     *
     * Answer an incoming voice call.
     *
     * @param CellularCallInfo
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t Answer(const CellularCallInfo &callInfo);

    /**
     * CSControl Reject
     * 27007-430_2001 6.6 Alternating mode call control method
     * 3GPP TS 22.030 [19]
     *
     * Reject an incoming voice call
     *
     * @param CellularCallInfo
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t Reject(const CellularCallInfo &callInfo);

    /**
     * Determine whether it is MMI
     * @param string phoneNum
     * @param SIMCardInfo simCardInfo
     * @return Returns true for MMI was successfully executed, otherwise not the MMI process
     */
    bool HandleOnMMI(const std::string &phoneNum, const PhoneNetType &phoneNetType);

    /**
     * Determines if a connection is currently in this state
     * @param TelCallStates
     * @return Returns true or false
     */
    bool IsInState(TelCallStates state);

    /**
     * Determines if a connection is currently in alive
     * @return Returns true is in alive
     */
    bool IsInAliveState();

    /**
     * Determine whether the call can be initiated currently
     * @return Returns true can to call
     */
    bool CanCall();

    /**
     * CSControl SetConnectionData
     * @param string phoneNUm
     * @param CellularCallConnectionCS
     * @return bool
     */
    bool SetConnectionData(std::string key, CellularCallConnectionCS &pConnectionCS);

    /**
     * CSControl GetConnectionData
     * @param string phoneNUm
     * @return CellularCallConnectionCS pointer
     */
    CellularCallConnectionCS *GetConnectionData(std::string key);

    /**
     * CSControl FindConnectionByState
     * @param TelCallStates
     * @return CellularCallConnectionCS pointer
     */
    CellularCallConnectionCS *FindConnectionByState(TelCallStates state);

    /**
     * CSControl releaseConnection
     * @param string phoneNUm
     * @return Release Connection is Success
     */
    bool ReleaseConnection(const std::string &key);

    /**
     * CSControl ReleaseAllConnection
     */
    void ReleaseAllConnection();

    /**
     * CSControl DealCsCallsData.
     * @returns Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int DealCsCallsData(const CallInfoList &callInfoList);

    /**
     * Connection Has Dialing
     * @returns bool
     */
    bool ConnectionInDialing();

    /**
     * Has More Than One Incoming Connection
     * @returns bool
     */
    bool HasMoreThanOneIncomingConnection();

    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "CSControl"};

private:
    /**
     * Handle On MultiCall
     * @param callInfo
     * @param phoneNetType
     * @param returnValue Three Way Dial return result code
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    bool HandleOnMultiCall(
        const CellularCallInfo &callInfo, const PhoneNetType &phoneNetType, int32_t &returnValue);

    /**
     * Calculate International Roaming
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    bool CalculateInternationalRoaming();

    /**
     * Report being hung up data
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t ReportHungUpInfo();

    /**
     * Report Incoming info
     * @param list
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t ReportIncomingInfo(const CallInfoList &list);

    /**
     * Report update info
     * @param list
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t ReportUpdateInfo(const CallInfoList &list);

    /**
     * Encapsulation CallReportInfo
     * @param callInfo
     * @return CallReportInfo
     */
    TelephonyCallManager::CallReportInfo EncapsulationCallReportInfo(const CallInfo &callInfo);

    /**
     * DeleteConnection Connection send
     * @param cellularCSCallResponseInfo
     */
    void DeleteConnection(
        TelephonyCallManager::CallsReportInfo &callsResponseInfo, const CallInfoList &callInfoList);

    /**
     * Dial MMI Code
     * @param CellularCallInfo
     * @param std::string dialString
     * @returns Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t DialMMI(const CellularCallInfo &callInfo, const std::string &dialString);

    /**
     * Dial Cdma
     * @param CellularCallInfo
     * @param std::string dialString
     * @returns Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t DialCdma(const CellularCallInfo &callInfo, const std::string &dialString);

    /**
     *  Dial Gsm
     * @param CellularCallInfo
     * @param std::string phoneNum
     * @param CLIRMode clirMode
     * @returns Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t DialGsm(const CellularCallInfo &callInfo, const std::string &phoneNum, CLIRMode &clirMode);

    /**
     * cscontrol init
     */
    void Init();

    /**
     * Encapsulate Dial Common
     * @param std::string phoneNum
     * @param CLIRMode clirMode
     * @returns Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t EncapsulateDialCommon(const std::string &phoneNum, CLIRMode &clirMode);

private:
    std::map<std::string, CellularCallConnectionCS> connectionMap_; // save callConnection map
    int32_t slotId_ = 1;
    std::shared_ptr<AppExecFwk::EventRunner> eventLoop_;
    std::shared_ptr<MMIHandler> handler_;
};
} // namespace CellularCall
} // namespace OHOS

#endif // CELLULAR_CALL_CONTROL_CS_H
