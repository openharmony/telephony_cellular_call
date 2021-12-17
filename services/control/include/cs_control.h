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

#include "call_manager_inner_type.h"

#include "cellular_call_connection_cs.h"
#include "control_base.h"

namespace OHOS {
namespace Telephony {
using CsConnectionMap = std::map<std::string, CellularCallConnectionCS>;
class CSControl : public ControlBase {
public:
    /**
     *  new CSControl
     *
     */
    CSControl() = default;

    /**
     * ~CSControl destructor
     */
    ~CSControl();

    /**
     * CSControl Dial
     *
     * 27007-430_2001 6.27 Informative examples
     * 3GPP TS 22.030 [19]
     *
     * originate a voice call
     *
     * @param CellularCallInfo
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Dial(const CellularCallInfo &callInfo) override;

    /**
     * CSControl HangUp
     *
     * 27007-430_2001 7.13 Call related supplementary services +CHLD
     * 3GPP TS 22.030 [19]
     *
     * release the active call
     *
     * @param CellularCallInfo
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t HangUp(const CellularCallInfo &callInfo);

    /**
     * CSControl Answer
     * 27007-430_2001 6.6 Alternating mode call control method
     * 3GPP TS 22.030 [19]
     *
     * Answer an incoming voice call.
     *
     * @param CellularCallInfo
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Answer(const CellularCallInfo &callInfo) override;

    /**
     * CSControl Reject
     * 27007-430_2001 6.6 Alternating mode call control method
     * 3GPP TS 22.030 [19]
     *
     * Reject an incoming voice call
     *
     * @param CellularCallInfo
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Reject(const CellularCallInfo &callInfo) override;

    /**
     * CSControl HoldCall
     *
     * 22083-400_2001 2 Call hold
     * 3GPP TS 22.030 [3]
     * 3GPP TS 23.083 V4.2.0 (2001-04) 2 Call hold (HOLD)
     *
     * The call hold service allows a served mobile subscriber
     *
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t HoldCall() override;

    /**
     * CSControl UnHoldCall
     *
     * 22083-400_2001 2 Call hold
     * 3GPP TS 22.030 [3]
     *
     * Retrieve the held call.
     *
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UnHoldCall() override;

    /**
     * CSControl SwitchCall
     *
     * 22083-400_2001 2 Call hold
     * 3GPP TS 22.030 [3]
     *
     * Alternate from one call to the other
     *
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SwitchCall() override;

    /**
     * CSControl CombineConference
     *
     * 22084-400_2001 1.3.8.2	Managing an active multiParty call
     * 3GPP TS 22.030
     *
     * Add another remote party
     * @return Error Code: Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t CombineConference() override;

    /**
     * CSControl SeparateConference
     *
     * 22084-400_2001 1.3.8.2	Managing an active multiParty call
     * 3GPP TS 22.030
     *
     * Separate a remote party
     * @param std::string splitString
     * @param index
     * @return Error Code: Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SeparateConference(const std::string &splitString, int32_t index);

    /**
     * CSControl CallSupplement
     *
     * 3GPP TS 27.007 V3.9.0 (2001-06) Call related supplementary services +CHLD
     * 3GPP TS 27.007 V3.9.0 (2001-06) 7.22	Informative examples
     *
     * @param CallSupplementType
     * @return Error Code: Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t CallSupplement(CallSupplementType type);

    /**
     * Send Dtmf String
     *
     * 23014-400_2001 6	Support of DTMF across the air interface
     * 3GPP TS 22.030
     *
     * @param sDtmfCode
     * @param on the DTMF ON length in milliseconds, or 0 for default
     * @param off the DTMF OFF length in milliseconds, or 0 for default
     * @return Returns true for MMI was successfully executed, otherwise not the MMI process
     */
    int32_t SendDtmfString(const std::string &sDtmfCode, int32_t switchOn, int32_t switchOff);

    /**
     * CSControl ReleaseAllConnection
     */
    void ReleaseAllConnection();

    /**
     * CSControl GetConnectionMap
     *
     * @return CsConnectionMap
     */
    CsConnectionMap GetConnectionMap();

    /**
     * CSControl DealCsCallsData.
     * @returns Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t ReportCallsData(const CallInfoList &callInfoList) override;

private:
    /**
     * Calculate International Roaming
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    bool CalculateInternationalRoaming() const;

    /**
     * Report being hung up data
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t ReportHungUpInfo();

    /**
     * Report Incoming info
     * @param list
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t ReportIncomingInfo(const CallInfoList &list);

    /**
     * Report update info
     * @param list
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t ReportUpdateInfo(const CallInfoList &list);

    /**
     * Encapsulation CallReportInfo
     * @param callInfo
     * @return CallReportInfo
     */
    CallReportInfo EncapsulationCallReportInfo(const CallInfo &callInfo);

    /**
     * DeleteConnection Connection send
     * @param cellularCSCallResponseInfo
     */
    void DeleteConnection(CallsReportInfo &callsResponseInfo, const CallInfoList &callInfoList);

    /**
     * Dial Cdma
     * @param CellularCallInfo
     * @param std::string dialString
     * @returns Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t DialCdma(const CellularCallInfo &callInfo, const std::string &dialString);

    /**
     *  Dial Gsm
     * @param CellularCallInfo
     * @param std::string phoneNum
     * @returns Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t DialGsm(const CellularCallInfo &callInfo, const std::string &phoneNum);

    /**
     * Encapsulate Dial Common
     * @param std::string phoneNum
     * @param CLIRMode clirMode
     * @returns Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t EncapsulateDialCommon(const std::string &phoneNum, CLIRMode &clirMode);

private:
    CsConnectionMap connectionMap_; // save callConnection map
    const int32_t VOICE_CALL = 0;
    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "CSControl"};
};
} // namespace Telephony
} // namespace OHOS

#endif // CELLULAR_CALL_CONTROL_CS_H
