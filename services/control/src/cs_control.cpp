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

#include "cs_control.h"

#include "securec.h"

#include "standardize_utils.h"
#include "module_service_utils.h"
#include "cellular_call_register.h"

namespace OHOS {
namespace Telephony {
CSControl::~CSControl()
{
    ReleaseAllConnection();
}

int32_t CSControl::Dial(const CellularCallInfo &callInfo)
{
    std::string dialString(callInfo.phoneNum);
    if (dialString.empty()) {
        TELEPHONY_LOGE("Dial return, dialString is empty.");
        return CALL_ERR_PHONE_NUMBER_EMPTY;
    }

    ModuleServiceUtils moduleServiceUtils;
    if (!moduleServiceUtils.GetRadioState(GetSlotId())) {
        TELEPHONY_LOGE("Dial return, radio error.");
        return CALL_ERR_GET_RADIO_STATE_FAILED;
    }

    RadioTech netType = moduleServiceUtils.GetNetworkStatus(GetSlotId());
    if (netType == RadioTech::RADIO_TECHNOLOGY_GSM) {
        return DialGsm(callInfo, dialString);
    }
    if (netType == RadioTech::RADIO_TECHNOLOGY_WCDMA) {
        return DialCdma(callInfo, dialString);
    }
    TELEPHONY_LOGE("Dial return, net type error.");
    return CALL_ERR_UNSUPPORTED_NETWORK_TYPE;
}

int32_t CSControl::DialCdma(const CellularCallInfo &callInfo, const std::string &dialString)
{
    if (!CanCall(connectionMap_)) {
        TELEPHONY_LOGE("CSControl::DialCdma return, error type: call state error.");
        return CALL_ERR_CALL_COUNTS_EXCEED_LIMIT;
    }

    StandardizeUtils standardizeUtils;
    // Remove the phone number separator
    std::string newPhoneNum = standardizeUtils.RemoveSeparatorsPhoneNumber(dialString);

    if (IsInState(connectionMap_, CALL_STATUS_ACTIVE)) {
        TELEPHONY_LOGI("DialCdma, CDMA is have connection in active state.");
        CallReportInfo reportInfo;
        if (memset_s(&reportInfo, sizeof(reportInfo), 0, sizeof(reportInfo)) != EOK) {
            TELEPHONY_LOGE("DialCdma return, memset_s fail.");
            return TELEPHONY_ERR_MEMSET_FAIL;
        }
        if (strcpy_s(reportInfo.accountNum, strlen(callInfo.phoneNum) + 1, callInfo.phoneNum) != EOK) {
            TELEPHONY_LOGE("DialCdma return, strcpy_s fail.");
            return TELEPHONY_ERR_STRCPY_FAIL;
        }

        reportInfo.state = CALL_STATUS_DIALING;
        reportInfo.callType = CallType::TYPE_CS;
        reportInfo.callMode = VideoStateType::TYPE_VOICE;
        CellularCallConnectionCS csConnection;
        csConnection.SetOrUpdateCallReportInfo(reportInfo);

        if (!SetConnectionData(connectionMap_, callInfo.phoneNum, csConnection)) {
            TELEPHONY_LOGE("DialCdma cdma return, SetConnectionData fail.");
            return CALL_ERR_CALL_ALREADY_EXISTS;
        }
        return csConnection.SendCDMAThreeWayDialRequest(GetSlotId());
    }
    CLIRMode clirMode = CLIRMode::DEFAULT;
    return EncapsulateDialCommon(newPhoneNum, clirMode);
}

int32_t CSControl::DialGsm(const CellularCallInfo &callInfo, const std::string &phoneNum)
{
    TELEPHONY_LOGI("DialGsm entry.");
    StandardizeUtils standardizeUtils;
    // Remove the phone number separator
    std::string newPhoneNum = standardizeUtils.RemoveSeparatorsPhoneNumber(phoneNum);

    CLIRMode clirMode = CLIRMode::DEFAULT;
    if (IsNeedExecuteMMI(newPhoneNum, clirMode)) {
        TELEPHONY_LOGI("DialGsm return, mmi code type.");
        return RETURN_TYPE_MMI;
    }

    if (!CanCall(connectionMap_)) {
        TELEPHONY_LOGE("DialGsm return, error type: call state error.");
        return CALL_ERR_CALL_COUNTS_EXCEED_LIMIT;
    }

    // Calls can be put on hold, recovered, released, added to conversation,
    // and transferred similarly as defined in 3GPP TS 22.030 [19].
    if (IsInState(connectionMap_, CALL_STATUS_ACTIVE)) {
        // New calls must be active, so other calls need to be hold
        TELEPHONY_LOGI("DialGsm, GSM is have connection in active state.");
        CellularCallConnectionCS pConnection;

        // Delay dialing to prevent failure to add a new call while making a multi-party call
        // Will it block the main thread or other threads? Will the reception of messages be blocked during sleep?
        // - a call can be temporarily disconnected from the ME but the connection is retained by the network
        pConnection.SwitchCallRequest(GetSlotId());
    }
    return EncapsulateDialCommon(phoneNum, clirMode);
}

int32_t CSControl::EncapsulateDialCommon(const std::string &phoneNum, CLIRMode &clirMode)
{
    CallReportInfo reportInfo;
    if (memset_s(&reportInfo, sizeof(reportInfo), 0, sizeof(reportInfo)) != EOK) {
        TELEPHONY_LOGE("EncapsulateDialCommon return, memset_s fail.");
        return TELEPHONY_ERR_MEMSET_FAIL;
    }
    if (strcpy_s(reportInfo.accountNum, strlen(phoneNum.c_str()) + 1, phoneNum.c_str()) != EOK) {
        TELEPHONY_LOGE("EncapsulateDialCommon return, strcpy_s fail.");
        return TELEPHONY_ERR_STRCPY_FAIL;
    }
    reportInfo.state = CALL_STATUS_DIALING;
    reportInfo.callType = CallType::TYPE_CS;
    reportInfo.callMode = VideoStateType::TYPE_VOICE;
    CellularCallConnectionCS csConnection;
    csConnection.SetOrUpdateCallReportInfo(reportInfo);

    if (!SetConnectionData(connectionMap_, phoneNum, csConnection)) {
        TELEPHONY_LOGE("EncapsulateDialCommon return, SetConnectionData fail.");
        return CALL_ERR_CALL_ALREADY_EXISTS;
    }

    DialRequestStruct dialRequest;
    /**
     * <idx>: integer type;
     * call identification number as described in 3GPP TS 22.030 [19] subclause 4.5.5.1
     * this number can be used in +CHLD command operations
     * <dir>:
     */
    dialRequest.phoneNum = phoneNum;

    /**
     * <n> (parameter sets the adjustment for outgoing calls):
     *  0	presentation indicator is used according to the subscription of the CLIR service
     *  1	CLIR invocation
     *  2	CLIR suppression
     */
    dialRequest.clirMode = clirMode;

    /**
     * An example of voice group call service request usage:
     * ATD*17*753#500; (originate voice group call with the priority level 3)
     * OK (voice group call setup was successful)
     */
    return csConnection.DialRequest(dialRequest, GetSlotId());
}

int32_t CSControl::HangUp(const CellularCallInfo &callInfo)
{
    // Match the session connection according to the phone number string
    auto pConnection =
        GetConnectionData<CsConnectionMap &, CellularCallConnectionCS *>(connectionMap_, callInfo.phoneNum);
    if (pConnection == nullptr) {
        TELEPHONY_LOGI("HangUp: connection cannot be matched, use index directly");
        pConnection =
            FindConnectionByIndex<CsConnectionMap &, CellularCallConnectionCS *>(connectionMap_, callInfo.index);
    }
    if (pConnection == nullptr) {
        TELEPHONY_LOGE("CSControl::HangUp, error type: connection is null");
        return CALL_ERR_CALL_CONNECTION_NOT_EXIST;
    }

    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CSControl::HangUp, error type: GetInstance() is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    CallReportInfo reportInfo = pConnection->GetCallReportInfo();
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSingleCallInfo(
        reportInfo, CALL_STATUS_DISCONNECTING);

    /**
     * The "directory number" case shall be handled with dial command D,
     * and the END case with hangup command H (or +CHUP).
     * (e.g. +CHLD: (0,1,1x,2,2x,3)).
     * NOTE: Call Hold, MultiParty and Explicit Call Transfer are only applicable to teleservice 11.
     */
    return pConnection->HangUpRequest(GetSlotId());
}

int32_t CSControl::Answer(const CellularCallInfo &callInfo)
{
    auto pConnection =
        GetConnectionData<CsConnectionMap &, CellularCallConnectionCS *>(connectionMap_, callInfo.phoneNum);
    if (pConnection == nullptr) {
        TELEPHONY_LOGI("Answer: connection cannot be matched, use index directly");
        pConnection =
            FindConnectionByIndex<CsConnectionMap &, CellularCallConnectionCS *>(connectionMap_, callInfo.index);
    }
    if (pConnection == nullptr) {
        TELEPHONY_LOGE("Answer return, error type: connection is null");
        return CALL_ERR_CALL_CONNECTION_NOT_EXIST;
    }

    /**
     * <stat> (state of the call):
     * 0 active
     * 1 held
     * 2 dialing (MO call)
     * 3 alerting (MO call)
     * 4 incoming (MT call)
     * 5 waiting (MT call)
     */
    // There is an active call when you call, or third party call waiting
    if (IsInState(connectionMap_, CALL_STATUS_ACTIVE) || pConnection->GetStatus() == CALL_STATUS_WAITING) {
        TELEPHONY_LOGI("Answer there is an active call when you call, or third party call waiting");
        auto con =
            FindConnectionByState<CsConnectionMap &, CellularCallConnectionCS *>(connectionMap_, CALL_STATUS_ACTIVE);
        if (con != nullptr) {
            /**
             * shows commands to start the call, to switch from voice to data (In Call Modification) and to hang up
             * the call. +CMOD and +FCLASS commands indicate the current settings before dialling or answering
             * command, not that they shall be given just before D or A command.
             */
            TELEPHONY_LOGI("Answer: There is an active session currently, and it needs to hold");
            con->SwitchCallRequest(GetSlotId());
        } else {
            TELEPHONY_LOGE("Answer return, error type: con is null, there are no active calls");
        }
    }

    if (pConnection->GetStatus() == CALL_STATUS_INCOMING || pConnection->GetStatus() == CALL_STATUS_ALERTING ||
        pConnection->GetStatus() == CALL_STATUS_WAITING) {
        return pConnection->AnswerRequest(GetSlotId());
    }

    TELEPHONY_LOGE("CSControl::Answer return, error type: call state error, phone not ringing.");
    return CALL_ERR_CALL_STATE;
}

int32_t CSControl::Reject(const CellularCallInfo &callInfo)
{
    auto pConnection =
        GetConnectionData<CsConnectionMap &, CellularCallConnectionCS *>(connectionMap_, callInfo.phoneNum);
    if (pConnection == nullptr) {
        TELEPHONY_LOGI("Reject: connection cannot be matched, use index directly");
        pConnection =
            FindConnectionByIndex<CsConnectionMap &, CellularCallConnectionCS *>(connectionMap_, callInfo.index);
    }
    if (pConnection == nullptr) {
        TELEPHONY_LOGE("CSControl::Reject, error type: connection is null");
        return CALL_ERR_CALL_CONNECTION_NOT_EXIST;
    }

    /**
     * shows commands to start the call, to switch from voice to data (In Call Modification) and to hang up the call.
     * +CMOD and +FCLASS commands indicate the current settings before dialling or answering command,
     * not that they shall be given just before D or A command.
     */
    if (!pConnection->IsRingingState()) {
        TELEPHONY_LOGE("CSControl::Reject return, error type: call state error, phone not ringing.");
        return CALL_ERR_CALL_STATE;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("CSControl::Reject, error type: GetInstance() is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    CallReportInfo reportInfo = pConnection->GetCallReportInfo();
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSingleCallInfo(
        reportInfo, CALL_STATUS_DISCONNECTING);
    return pConnection->RejectRequest(GetSlotId());
}

int32_t CSControl::HoldCall()
{
    /**
     * When the call hold service is invoked, communication is interrupted on the traffic channel and the traffic
     * channel is released from the existing call. The traffic channel is reserved for the served mobile subscriber
     * invoking the call hold service. The served mobile subscriber can only have one call on hold at a time.
     */
    if (IsInState(connectionMap_, CALL_STATUS_INCOMING)) {
        TELEPHONY_LOGE("HoldCall return, error type: call state error.");
        return CALL_ERR_CALL_STATE;
    }
    CellularCallConnectionCS connection;
    return connection.HoldRequest(GetSlotId());
}

int32_t CSControl::UnHoldCall()
{
    // A notification shall be send towards the previously held party that the call has been retrieved.
    if (IsInState(connectionMap_, CALL_STATUS_INCOMING)) {
        TELEPHONY_LOGE("UnHoldCall return, error type: call state error.");
        return CALL_ERR_CALL_STATE;
    }
    CellularCallConnectionCS connection;
    return connection.UnHoldCallRequest(GetSlotId());
}

int32_t CSControl::SwitchCall()
{
    /**
     * If the served mobile subscriber is connected to an active call and has another call on hold, she can:
     * 1) Alternate from one call to the other.
     * 2) Disconnect the active call.
     * 3) Disconnect the held call.
     * 4) Disconnect both calls.
     */
    if (IsInState(connectionMap_, CALL_STATUS_INCOMING)) {
        TELEPHONY_LOGE("SwitchCall return, error type: call state error.");
        return CALL_ERR_CALL_STATE;
    }
    CellularCallConnectionCS connection;
    return connection.SwitchCallRequest(GetSlotId());
}

/**
 * Explicitly choose one remote party to have a private communication with.
 * This results in that remote party being removed from the multiParty call which is placed on hold,
 * and the conversation between the served mobile subscriber and the designated remote party being a normal
 * active call. The remaining remote parties may have communication with each other in this state.
 */
int32_t CSControl::SeparateConference(const std::string &splitString, int32_t index)
{
    if (splitString.empty()) {
        TELEPHONY_LOGW("SeparateConference, splitString is empty.");
    }

    auto pConnection = GetConnectionData<CsConnectionMap &, CellularCallConnectionCS *>(connectionMap_, splitString);
    if (pConnection != nullptr) {
        return pConnection->SeparateConferenceRequest(pConnection->GetIndex(), GetSlotId(), VOICE_CALL);
    }

    TELEPHONY_LOGI("SeparateConference: connection cannot be matched, use index directly");
    CellularCallConnectionCS connection;
    return connection.SeparateConferenceRequest(index, GetSlotId(), VOICE_CALL);
}

/**
 * Add another remote party, to which a private communication has been established using
 * the same procedures as in Section 1.3.8.1, if the number of remote parties does not then
 * exceed the maximum number allowed, which results in an active multiParty call.
 */
int32_t CSControl::CombineConference()
{
    CellularCallConnectionCS connectionCs;
    return connectionCs.CombineConferenceRequest(GetSlotId(), VOICE_CALL);
}

int32_t CSControl::CallSupplement(CallSupplementType type)
{
    switch (type) {
        // 3GPP TS 27.007 V3.9.0 (2001-06) Call related supplementary services +CHLD
        // 3GPP TS 27.007 V3.9.0 (2001-06) 7.22	Informative examples
        case CallSupplementType::TYPE_HANG_UP_HOLD_WAIT:
        // release the second (active) call and recover the first (held) call
        case CallSupplementType::TYPE_HANG_UP_ACTIVE: {
            CellularCallConnectionCS connection;
            return connection.CallSupplementRequest(type, GetSlotId());
        }
        case CallSupplementType::TYPE_HANG_UP_ALL: {
            TELEPHONY_LOGI("CallSupplement, hang up all call");
            CellularCallConnectionCS connection;
            return connection.RejectRequest(GetSlotId());
        }
        default: {
            TELEPHONY_LOGE("CallSupplement warring, type is invalid");
            return TELEPHONY_ERR_ARGUMENT_INVALID;
        }
    }
}

int32_t CSControl::SendDtmfString(const std::string &sDtmfCode, int32_t switchOn, int32_t switchOff)
{
    /**
     * 3gpp 27007-430_2001
     *
     * C.2.11	DTMF and tone generation +VTS
     *
     * This command allows the transmission of DTMF tones and arbitrary tones (see note).
     * These tones may be used (for example) when announcing the start of a recording period.
     * The command is write only.
     * In this profile of commands, this command does not operate in data or fax modes of operation (+FCLASS=0,1,2
     7).
     * NOTE 1:	D is used only for dialling.

     * The string parameter of the command consists of combinations of the following separated by commas:
     * 1. <DTMF>. A single ASCII character in the set 0 9, #,*,A D.
     * This is interpreted as a single ACSII character whose duration is set by the +VTD command.
     *   NOTE 2:	In GSM this operates only in voice mode.
     * 2. [<tone1>,<tone2>,<duration>].
     * This is interpreted as a dual tone of frequencies <tone1> and <tone2>, lasting for a time <duration> (in 10
     ms multiples).
     *   NOTE 3:	This does not operate in GSM.
     * 3. {<DTMF>,<duration>}. This is interpreted as a DTMF tone of different duration from that mandated by the
     +VTD command.
     *   NOTE 4:	In GSM this operates only in voice mode.
     */
    // In GSM this operates only in voice mode.
    CellularCallConnectionCS connection;
    for (char i : sDtmfCode) {
        // A single ASCII character in the set 0 9, #,*,A D.
        if (!IsDtmfKey(i)) {
            return CALL_ERR_PARAMETER_OUT_OF_RANGE;
        }
    }
    return connection.SendDtmfStringRequest(sDtmfCode, switchOn, switchOff, GetSlotId());
}

bool CSControl::CalculateInternationalRoaming() const
{
    bool ret = true;
    ModuleServiceUtils moduleServiceUtils;
    std::string operatorCountryIso = moduleServiceUtils.GetNetworkCountryCode(GetSlotId());
    std::string simCountryIso = moduleServiceUtils.GetIsoCountryCode(GetSlotId());
    ret = !operatorCountryIso.empty() && !simCountryIso.empty() && (operatorCountryIso != simCountryIso);
    if (ret) {
        if (simCountryIso == "us") {
            ret = operatorCountryIso != "vi";
        } else if (simCountryIso == "vi") {
            ret = operatorCountryIso != "us";
        }
    }
    return ret;
}

int32_t CSControl::ReportCallsData(const CallInfoList &callInfoList)
{
    if (callInfoList.callSize <= 0 && !connectionMap_.empty()) {
        return ReportHungUpInfo();
    } else if (callInfoList.callSize > 0 && connectionMap_.empty()) {
        return ReportIncomingInfo(callInfoList);
    } else if (callInfoList.callSize > 0 && !connectionMap_.empty()) {
        return ReportUpdateInfo(callInfoList);
    }
    return TELEPHONY_ERROR;
}

int32_t CSControl::ReportUpdateInfo(const CallInfoList &callInfoList)
{
    CallsReportInfo callsReportInfo;
    for (int32_t i = 0; i < callInfoList.callSize; ++i) {
        CallReportInfo reportInfo = EncapsulationCallReportInfo(callInfoList.calls[i]);

        auto pConnection = GetConnectionData<CsConnectionMap &, CellularCallConnectionCS *>(
            connectionMap_, callInfoList.calls[i].number);
        if (pConnection == nullptr) {
            CellularCallConnectionCS connection;
            connection.SetOrUpdateCallReportInfo(reportInfo);
            connection.SetFlag(true);
            connection.SetIndex(callInfoList.calls[i].index);
            SetConnectionData(connectionMap_, callInfoList.calls[i].number, connection);
        } else {
            pConnection->SetFlag(true);
            pConnection->SetIndex(callInfoList.calls[i].index);
            pConnection->SetOrUpdateCallReportInfo(reportInfo);
        }
        callsReportInfo.callVec.push_back(reportInfo);
    }

    DeleteConnection(callsReportInfo, callInfoList);
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("ReportUpdateInfo return, GetInstance() is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    callsReportInfo.slotId = GetSlotId();
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportCallsInfo(callsReportInfo);
    return TELEPHONY_SUCCESS;
}

void CSControl::DeleteConnection(CallsReportInfo &callsReportInfo, const CallInfoList &callInfoList)
{
    auto it = connectionMap_.begin();
    while (it != connectionMap_.end()) {
        CallReportInfo callReportInfo = it->second.GetCallReportInfo();
        if (!it->second.GetFlag()) {
            callReportInfo.state = CALL_STATUS_DISCONNECTED;
            callsReportInfo.callVec.push_back(callReportInfo);
            connectionMap_.erase(it++);
        } else {
            it->second.SetFlag(false);
            ++it;
        }
    }
}

CallReportInfo CSControl::EncapsulationCallReportInfo(const CallInfo &callInfo)
{
    CallReportInfo callReportInfo;
    if (memset_s(&callReportInfo, sizeof(callReportInfo), 0, sizeof(callReportInfo)) != EOK) {
        TELEPHONY_LOGE("EncapsulationCallReportInfo return, memset_s fail.");
        return callReportInfo;
    }

    /**
     * <idx>: integer type;
     * call identification number as described in 3GPP TS 22.030 [19] subclause 4.5.5.1
     * this number can be used in +CHLD command operations
     * <dir>:
     */
    size_t cpyLen = strlen(callInfo.number.c_str()) + 1;
    if (strcpy_s(callReportInfo.accountNum, cpyLen, callInfo.number.c_str()) != EOK) {
        TELEPHONY_LOGE("EncapsulationCallReportInfo return, strcpy_s fail.");
        return callReportInfo;
    }

    /**
     * <stat> (state of the call):
     * 0 active
     * 1 held
     * 2 dialing (MO call)
     * 3 alerting (MO call)
     * 4 incoming (MT call)
     * 5 waiting (MT call)
     */
    callReportInfo.index = callInfo.index;
    callReportInfo.accountId = GetSlotId();
    callReportInfo.voiceDomain = callInfo.voiceDomain;
    callReportInfo.state = static_cast<TelCallState>(callInfo.state);
    callReportInfo.callType = CallType::TYPE_CS;
    callReportInfo.callMode = VideoStateType::TYPE_VOICE;
    return callReportInfo;
}

int32_t CSControl::ReportIncomingInfo(const CallInfoList &callInfoList)
{
    CallsReportInfo callsReportInfo;
    for (int32_t i = 0; i < callInfoList.callSize; ++i) {
        CallReportInfo cellularCallReportInfo = EncapsulationCallReportInfo(callInfoList.calls[i]);

        CellularCallConnectionCS connection;
        connection.SetStatus(static_cast<TelCallState>(callInfoList.calls[i].state));
        connection.SetIndex(callInfoList.calls[i].index);
        connection.SetOrUpdateCallReportInfo(cellularCallReportInfo);
        SetConnectionData(connectionMap_, callInfoList.calls[i].number, connection);

        callsReportInfo.callVec.push_back(cellularCallReportInfo);
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("ReportIncomingInfo return, GetInstance() is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    callsReportInfo.slotId = GetSlotId();
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportCallsInfo(callsReportInfo);
    return TELEPHONY_SUCCESS;
}

int32_t CSControl::ReportHungUpInfo()
{
    CallsReportInfo callsReportInfo;
    for (auto &it : connectionMap_) {
        CallReportInfo callReportInfo = it.second.GetCallReportInfo();
        callReportInfo.state = CALL_STATUS_DISCONNECTED;
        callReportInfo.accountId = GetSlotId();
        callsReportInfo.callVec.push_back(callReportInfo);
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("ReportHungUpInfo return, GetInstance() is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    callsReportInfo.slotId = GetSlotId();
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportCallsInfo(callsReportInfo);
    ReleaseAllConnection();
    return TELEPHONY_SUCCESS;
}

void CSControl::ReleaseAllConnection()
{
    connectionMap_.clear();
}

CsConnectionMap CSControl::GetConnectionMap()
{
    return connectionMap_;
}
} // namespace Telephony
} // namespace OHOS