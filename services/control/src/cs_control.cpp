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
#include "mmi_code_utils.h"
#include "module_service_utils.h"
#include "cellular_call_register.h"

namespace OHOS {
namespace CellularCall {
using namespace TelephonyCallManager;
CSControl::CSControl()
{
    Init();
}

void CSControl::Init()
{
    HILOG_DEBUG("CellularCallServiceService Init");
    eventLoop_ = AppExecFwk::EventRunner::Create("CSControl");
    if (eventLoop_ == nullptr) {
        HILOG_ERROR("failed to create EventRunner");
        return;
    }
    handler_ = std::make_shared<MMIHandler>(eventLoop_);
    if (handler_ == nullptr) {
        HILOG_ERROR("failed to make_shared handler_");
        return;
    }
}

CSControl::~CSControl()
{
    ReleaseAllConnection();
}

int32_t CSControl::Dial(const CellularCallInfo &callInfo)
{
    std::string dialString(callInfo.phoneNum);
    if (dialString.empty()) {
        HILOG_INFO("Dial return, dialString is empty.");
        return ERR_PARAMETER_INVALID;
    }
    ModuleServiceUtils moduleServiceUtils;
    moduleServiceUtils.GetRadioStatus(slotId_);
    if (callInfo.phoneNetType == PHONE_TYPE_GSM) {
        return DialMMI(callInfo, dialString);
    }
    if (callInfo.phoneNetType == PHONE_TYPE_CDMA) {
        return DialCdma(callInfo, dialString);
    }
    return ERR_PARAMETER_INVALID;
}

int32_t CSControl::DialCdma(const CellularCallInfo &callInfo, const std::string &dialString)
{
    HILOG_DEBUG("CSControl::DialCdma entry.");
    if (!CanCall()) {
        HILOG_ERROR("CSControl::Dial return, error type: call state error.");
        return ERR_CALL_STATE;
    }
    bool bInternationalRoaming = true;
    // When a terminal wanders between countries (i.e. networks), need get get the country and operator name
    if (callInfo.phoneNetType == PHONE_TYPE_CDMA) {
        bInternationalRoaming = CalculateInternationalRoaming();
    }
    StandardizeUtils standardizeUtils;
    // Remove the phone number separator
    std::string newPhoneNum = standardizeUtils.RemoveSeparatorsPhoneNumber(dialString);
    CLIRMode clirMode = DEFAULT;
    std::string convertString = newPhoneNum;
    if (bInternationalRoaming) {
        convertString = standardizeUtils.ConvertNumberIfNeed(newPhoneNum);
    }
    int32_t ret = TELEPHONY_NO_ERROR;
    if (IsInState(CALL_STATUS_ACTIVE)) {
        HILOG_INFO("Dial, CDMA is have connection in active state.");
        if (!HandleOnMultiCall(callInfo, callInfo.phoneNetType, ret)) {
            return ret;
        }
    }
    return EncapsulateDialCommon(convertString, clirMode);
}

int32_t CSControl::DialMMI(const CellularCallInfo &callInfo, const std::string &dialString)
{
    HILOG_DEBUG("CSControl::DialMMI entry.");
    StandardizeUtils standardizeUtils;
    // Remove the phone number separator
    std::string newPhoneNum = standardizeUtils.RemoveSeparatorsPhoneNumber(dialString);
    CLIRMode clirMode = DEFAULT;
    // Also supplementary services may be controlled using dial command according to 3GPP TS 22.030 [19].
    // An example of call forwarding on no reply for telephony with the adjustment of the
    // no reply condition timer on 25 seconds:
    if (HandleOnMMI(newPhoneNum, callInfo.phoneNetType)) {
        HILOG_DEBUG("CSControl::MMIProcess return, mmi code type.");
        return ERR_MMI_TYPE;
    }
    // look at the Network portion
    std::string networkString = standardizeUtils.StandardizePhoneNumber(newPhoneNum);
    // Parse the MMI code from the string
    std::unique_ptr<MMICodeUtils> mmiCodeUtils = std::make_unique<MMICodeUtils>();
    if (mmiCodeUtils == nullptr) {
        HILOG_ERROR("failed to make_unique mmiCodeUtils");
        return ERR_MMI_TYPE;
    }

    if (mmiCodeUtils->IsNeedExecuteMmi(networkString, clirMode)) {
        if (handler_ != nullptr) {
            handler_->SendEvent(MMIHandlerId::MMI_EVENT_Id, mmiCodeUtils);
        }
        HILOG_DEBUG("CSControl::MMIProcess return, mmi code type.");
        return ERR_MMI_TYPE;
    }
    return DialGsm(callInfo, newPhoneNum, clirMode);
}

int32_t CSControl::DialGsm(const CellularCallInfo &callInfo, const std::string &phoneNum, CLIRMode &clirMode)
{
    HILOG_DEBUG("CSControl::DialRequest entry.");
    if (!CanCall()) {
        HILOG_ERROR("CSControl::Dial return, error type: call state error.");
        return ERR_CALL_STATE;
    }

    int32_t ret = TELEPHONY_NO_ERROR;
    // Calls can be put on hold, recovered, released, added to conversation,
    // and transferred similarly as defined in 3GPP TS 22.030 [19].
    if (IsInState(CALL_STATUS_ACTIVE)) {
        HILOG_INFO("Dial, GSM is have connection in active state.");
        if (!HandleOnMultiCall(callInfo, callInfo.phoneNetType, ret)) {
            return ret;
        }
    }
    return EncapsulateDialCommon(phoneNum, clirMode);
}

int32_t CSControl::EncapsulateDialCommon(const std::string &phoneNum, CLIRMode &clirMode)
{
    CallReportInfo cellularCallReportInfo;
    if (memset_s(&cellularCallReportInfo, sizeof(cellularCallReportInfo), 0, sizeof(cellularCallReportInfo)) !=
        EOK) {
        HILOG_ERROR("Dial return, memset_s fail.");
        return ERR_SYSTEM_INVOKE;
    }
    if (strcpy_s(cellularCallReportInfo.accountNum, strlen(phoneNum.c_str()) + 1, phoneNum.c_str()) != EOK) {
        HILOG_ERROR("Dial return, strcpy_s fail.");
        return ERR_SYSTEM_INVOKE;
    }
    cellularCallReportInfo.state = CALL_STATUS_DIALING;
    cellularCallReportInfo.callType = CallType::TYPE_CS;
    cellularCallReportInfo.callMode = VedioStateType::TYPE_VOICE;
    CellularCallConnectionCS pCSConnection;
    pCSConnection.SetOrUpdateCallReportInfo(cellularCallReportInfo);

    std::string key = phoneNum;
    if (!SetConnectionData(key, pCSConnection)) {
        HILOG_ERROR("CSControl::Dial return, SetConnectionData fail.");
        return ERR_PARAMETER_INVALID;
    }
    DialRequestStruct dialRequest;
    if (memset_s(&dialRequest, sizeof(dialRequest), 0, sizeof(dialRequest)) != EOK) {
        HILOG_ERROR("CSControl::Dial return, memset_s fail.");
        return ERR_SYSTEM_INVOKE;
    }

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
    return pCSConnection.DialRequest(dialRequest, slotId_);
}

int32_t CSControl::End(const CellularCallInfo &callInfo)
{
    HILOG_DEBUG("CSControl::End start");
    std::string phoneNum(callInfo.phoneNum);
    CellularCallConnectionCS *pConnection = nullptr;
    // Match the session connection according to the phone number string
    pConnection = GetConnectionData(callInfo.phoneNum);
    if (pConnection == nullptr) {
        HILOG_ERROR("CSControl::End, error type: connection is null");
        return ERR_CONNECTION;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSingleCallInfo(
        *pConnection, CALL_STATUS_DISCONNECTING);
    /**
     * The "directory number" case shall be handled with dial command D,
     * and the END case with hangup command H (or +CHUP).
     * (e.g. +CHLD: (0,1,1x,2,2x,3)).
     * NOTE: Call Hold, MultiParty and Explicit Call Transfer are only applicable to teleservice 11.
     */
    return pConnection->EndRequest(slotId_);
}

int32_t CSControl::Answer(const CellularCallInfo &callInfo)
{
    HILOG_DEBUG("CSControl::Answer start");
    std::string phoneNum(callInfo.phoneNum);
    int32_t ret = TELEPHONY_NO_ERROR;
    CellularCallConnectionCS *pConnection = GetConnectionData(phoneNum);
    if (pConnection == nullptr) {
        HILOG_ERROR("CSControl::Answer, error type: connection is null");
        return ERR_CONNECTION;
    }
    /**
     * <stat> (state of the call):
     *   0	active
     *   1	held
     *   2	dialing (MO call)
     *   3	alerting (MO call)
     *   4	incoming (MT call)
     *   5	waiting (MT call)
     */
    if (pConnection->GetStatus() == CALL_STATUS_INCOMING || pConnection->GetStatus() == CALL_STATUS_ALERTING) {
        return pConnection->AnswerRequest(slotId_);
    } else if (pConnection->GetStatus() == CALL_STATUS_WAITING) { // Third party call waiting
        CellularCallConnectionCS *con = FindConnectionByState(CALL_STATUS_ACTIVE);
        if (con == nullptr) {
            HILOG_ERROR("CSControl::Answer, error type: con is null, There is not active call");
            return ERR_CONNECTION;
        }
        /**
         * shows commands to start the call, to switch from voice to data (In Call Modification) and to hang up the
         * call. +CMOD and +FCLASS commands indicate the current settings before dialling or answering command, not
         * that they shall be given just before D or A command.
         */
        if (callInfo.phoneNetType == PHONE_TYPE_GSM) {
            ret = con->HoldingAndActiveRequest(slotId_);
            if (ret != TELEPHONY_NO_ERROR) {
                return ret;
            }
        }
        return pConnection->AnswerRequest(slotId_);
    } else {
        HILOG_ERROR("CSControl::Answer return, error type: call state error, phone not ringing.");
        return ERR_CALL_STATE;
    }
}

int32_t CSControl::Reject(const CellularCallInfo &callInfo)
{
    HILOG_DEBUG("CSControl::Reject start");
    std::string phoneNum(callInfo.phoneNum);
    CellularCallConnectionCS *pConnection = GetConnectionData(phoneNum);
    if (pConnection == nullptr) {
        HILOG_ERROR("CSControl::Reject, error type: connection is null");
        return ERR_CONNECTION;
    }
    /**
     * shows commands to start the call, to switch from voice to data (In Call Modification) and to hang up the call.
     * +CMOD and +FCLASS commands indicate the current settings before dialling or answering command,
     * not that they shall be given just before D or A command.
     */
    if (pConnection->IsRingingState()) {
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSingleCallInfo(
            *pConnection, CALL_STATUS_DISCONNECTING);
        return pConnection->RejectRequest(slotId_);
    } else {
        HILOG_ERROR("CSControl::Reject return, error type: call state error, phone not ringing.");
        return ERR_CALL_STATE;
    }
}

bool CSControl::HandleOnMMI(const std::string &phoneNum, const PhoneNetType &phoneNetType)
{
    if (phoneNetType != PHONE_TYPE_GSM) {
        HILOG_WARN("HandleMMI return, is NOT supported in CDMA!");
        return false;
    }

    // Processing MMI needs to be in alive state
    if (!IsInAliveState()) {
        HILOG_DEBUG("HandleOnMMI, is not in alive state.");
        return false;
    }

    if (phoneNum.empty()) {
        HILOG_INFO("HandleOnMMI return, phoneNum is empty.");
        return false;
    }

    return false;
}

bool CSControl::HandleOnMultiCall(
    const CellularCallInfo &callInfo, const PhoneNetType &phoneNetType, int32_t &returnValue)
{
    // - a call can be temporarily disconnected from the ME but the connection is retained by the network
    if (phoneNetType == PHONE_TYPE_GSM) {
        // New calls must be active, so other calls need to be hold

        CellularCallConnectionCS *pConnection = nullptr;
        pConnection = FindConnectionByState(CALL_STATUS_ACTIVE);
        if (pConnection == nullptr) {
            HILOG_ERROR("HandleOnMultiCall return, connection in active state could not be found.");
            return true;
        }
        // Delay dialing to prevent failure to add a new call while making a multi-party call
        // Will it block the main thread or other threads? Will the reception of messages be blocked during sleep?
        pConnection->HoldingAndActiveRequest(slotId_);
        return true; // continue to call
    } else if (phoneNetType == PHONE_TYPE_CDMA) {
        CallReportInfo cellularCallReportInfo;
        if (memset_s(&cellularCallReportInfo, sizeof(cellularCallReportInfo), 0, sizeof(cellularCallReportInfo)) !=
            EOK) {
            HILOG_ERROR("HandleOnMultiCall return, memset_s fail.");
            return ERR_SYSTEM_INVOKE;
        }
        if (strcpy_s(cellularCallReportInfo.accountNum, strlen(callInfo.phoneNum) + 1, callInfo.phoneNum) != EOK) {
            HILOG_ERROR("HandleOnMultiCall return, strcpy_s fail.");
            return ERR_SYSTEM_INVOKE;
        }

        cellularCallReportInfo.state = CALL_STATUS_DIALING;
        cellularCallReportInfo.callType = CallType::TYPE_CS;
        cellularCallReportInfo.callMode = VedioStateType::TYPE_VOICE;
        CellularCallConnectionCS pCSConnection;
        pCSConnection.SetOrUpdateCallReportInfo(cellularCallReportInfo);

        std::string key = callInfo.phoneNum;
        if (!SetConnectionData(key, pCSConnection)) {
            HILOG_ERROR("HandleOnMultiCall cdma return, SetConnectionData fail.");
            returnValue = ERR_PARAMETER_INVALID;
            return false;
        }

        returnValue = pCSConnection.SendCDMAThreeWayDialRequest(slotId_);
        if (returnValue != TELEPHONY_NO_ERROR) {
        }
        return false;
    }
    HILOG_ERROR("HandleOnMultiCall return, error type: phone network error.");
    returnValue = ERR_NETWORK_TYPE;
    return false;
}

bool CSControl::CalculateInternationalRoaming()
{
    bool ret = true;
    ModuleServiceUtils moduleServiceUtils;
    std::string operatorCountryIso = moduleServiceUtils.GetNetworkCountryCode(slotId_);
    std::string simCountryIso = moduleServiceUtils.GetIsoCountryCode(slotId_);
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

bool CSControl::CanCall()
{
    return connectionMap_.size() == 0;
}

bool CSControl::IsInState(TelCallStates state)
{
    bool ret = false;
    CellularCallConnectionCS *pConnection = FindConnectionByState(state);
    if (pConnection != nullptr) {
        ret = true;
    }
    return ret;
}

bool CSControl::IsInAliveState()
{
    return !(IsInState(CALL_STATUS_IDLE) || IsInState(CALL_STATUS_DISCONNECTED) ||
        IsInState(CALL_STATUS_DISCONNECTING));
}

bool CSControl::SetConnectionData(std::string key, CellularCallConnectionCS &pConnectionCS)
{
    HILOG_INFO("CSControl::SetConnectionData start");
    if (key.empty()) {
        HILOG_INFO("SetConnectionData, key is empty.");
        return false;
    }
    if (!connectionMap_.insert(std::make_pair(key, pConnectionCS)).second) {
        HILOG_INFO("SetConnectionData, key already exists.");
        return false;
    }
    return true;
}

CellularCallConnectionCS *CSControl::GetConnectionData(std::string key)
{
    if (key.empty()) {
        HILOG_INFO("GetConnectionData, key is empty.");
        return nullptr;
    }

    auto p = connectionMap_.find(key);
    if (p != connectionMap_.end()) {
        return &p->second;
    }
    return nullptr;
}

CellularCallConnectionCS *CSControl::FindConnectionByState(TelCallStates state)
{
    CellularCallConnectionCS *pConnection = nullptr;
    std::map<std::string, CellularCallConnectionCS>::iterator it;
    for (it = connectionMap_.begin(); it != connectionMap_.end(); ++it) {
        pConnection = &it->second;
        if (pConnection != nullptr && pConnection->GetStatus() == state) {
            return pConnection;
        }
    }
    return nullptr;
}

bool CSControl::ReleaseConnection(const std::string &key)
{
    if (key.empty()) {
        HILOG_ERROR("ReleaseConnection, key is empty.");
        return false;
    }
    connectionMap_.erase(key);

    return true;
}

int CSControl::DealCsCallsData(const CallInfoList &callInfoList)
{
    if (callInfoList.callSize <= 0 && !connectionMap_.empty()) {
        return ReportHungUpInfo();
    } else if (callInfoList.callSize > 0 && connectionMap_.empty()) {
        return ReportIncomingInfo(callInfoList);
    } else if (callInfoList.callSize > 0 && !connectionMap_.empty()) {
        return ReportUpdateInfo(callInfoList);
    }
    return ERR_REPORT_CALLS_INFO;
}

int CSControl::ReportUpdateInfo(const CallInfoList &callInfoList)
{
    HILOG_DEBUG("ReportUpdateInfo entry");
    CallsReportInfo callsReportInfo;
    if (memset_s(&callsReportInfo, sizeof(callsReportInfo), 0, sizeof(callsReportInfo)) != EOK) {
        HILOG_ERROR("ReportUpdateInfo return, memset_s fail.");
        return ERR_SYSTEM_INVOKE;
    }
    for (int i = 0; i < callInfoList.callSize; ++i) {
        CallReportInfo cellularCallReportInfo = EncapsulationCallReportInfo(callInfoList.calls[i]);

        CellularCallConnectionCS *pConnection = nullptr;
        pConnection = GetConnectionData(callInfoList.calls[i].remoteNumber);
        if (pConnection == nullptr) {
            CellularCallConnectionCS connection;
            connection.SetOrUpdateCallReportInfo(cellularCallReportInfo);
            connection.flag_ = true;
            connection.index_ = i + 1;
            SetConnectionData(callInfoList.calls[i].remoteNumber, connection);
        } else {
            pConnection->flag_ = true;
            pConnection->index_ = i + 1;
            pConnection->SetOrUpdateCallReportInfo(cellularCallReportInfo);
        }
        callsReportInfo.callVec.push_back(cellularCallReportInfo);
    }
    DeleteConnection(callsReportInfo, callInfoList);
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportCallsInfo(callsReportInfo);
    return TELEPHONY_NO_ERROR;
}

void CSControl::DeleteConnection(CallsReportInfo &callsReportInfo, const CallInfoList &callInfoList)
{
    HILOG_DEBUG("DeleteConnection entry");
    auto it = connectionMap_.begin();
    while (it != connectionMap_.end()) {
        CellularCallConnectionCS *pConnection = &it->second;
        if (!pConnection->flag_) {
            pConnection->callReportInfo_.state = CALL_STATUS_DISCONNECTED;
            callsReportInfo.callVec.push_back(pConnection->callReportInfo_);
            connectionMap_.erase(it++);
        } else {
            pConnection->flag_ = false;
            ++it;
        }
    }
}

CallReportInfo CSControl::EncapsulationCallReportInfo(const CallInfo &callInfo)
{
    HILOG_DEBUG("EncapsulationCallReportInfo entry");
    CallReportInfo callReportInfo;
    if (memset_s(&callReportInfo, sizeof(callReportInfo), 0, sizeof(callReportInfo)) != EOK) {
        HILOG_ERROR("EncapsulationCallReportInfo return, memset_s fail.");
        return callReportInfo;
    }
    /**
     * <idx>: integer type;
     * call identification number as described in 3GPP TS 22.030 [19] subclause 4.5.5.1
     * this number can be used in +CHLD command operations
     * <dir>:
     */
    int32_t cpyLen = strlen(callInfo.remoteNumber.c_str()) + 1;
    if (strcpy_s(callReportInfo.accountNum, cpyLen, callInfo.remoteNumber.c_str()) != EOK) {
        HILOG_ERROR("EncapsulationCallReportInfo return, strcpy_s fail.");
        return callReportInfo;
    }
    /**
     * <stat> (state of the call):
     *   0	active
     *   1	held
     *   2	dialing (MO call)
     *   3	alerting (MO call)
     *   4	incoming (MT call)
     *   5	waiting (MT call)
     */
    callReportInfo.state = static_cast<OHOS::TelCallStates>(callInfo.state);
    callReportInfo.callType = CallType::TYPE_CS;
    callReportInfo.callMode = VedioStateType::TYPE_VOICE;
    return callReportInfo;
}

int32_t CSControl::ReportIncomingInfo(const CallInfoList &callInfoList)
{
    HILOG_DEBUG("ReportIncomingInfo entry");
    CallsReportInfo callsReportInfo;
    if (memset_s(&callsReportInfo, sizeof(callsReportInfo), 0, sizeof(callsReportInfo)) != EOK) {
        HILOG_ERROR("ReportIncomingInfo return, memset_s fail.");
        return ERR_SYSTEM_INVOKE;
    }
    for (int i = 0; i < callInfoList.callSize; ++i) {
        CallReportInfo cellularCallReportInfo = EncapsulationCallReportInfo(callInfoList.calls[i]);

        CellularCallConnectionCS connection;
        connection.SetStatus(static_cast<TelCallStates>(callInfoList.calls[i].state));
        connection.index_ = i + 1;
        connection.SetOrUpdateCallReportInfo(cellularCallReportInfo);
        SetConnectionData(callInfoList.calls[i].remoteNumber, connection);

        callsReportInfo.callVec.push_back(cellularCallReportInfo);
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportCallsInfo(callsReportInfo);
    return TELEPHONY_NO_ERROR;
}

int32_t CSControl::ReportHungUpInfo()
{
    HILOG_DEBUG("ReportHungUpInfo entry");
    CallsReportInfo callsReportInfo;
    if (memset_s(&callsReportInfo, sizeof(callsReportInfo), 0, sizeof(callsReportInfo)) != EOK) {
        HILOG_ERROR("ReportHungUpInfo return, memset_s fail.");
        return ERR_SYSTEM_INVOKE;
    }
    std::map<std::string, CellularCallConnectionCS>::iterator it;
    for (it = connectionMap_.begin(); it != connectionMap_.end(); ++it) {
        CellularCallConnectionCS *pConnection = &it->second;
        pConnection->callReportInfo_.state = CALL_STATUS_DISCONNECTED;
        callsReportInfo.callVec.push_back((*pConnection).callReportInfo_);
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportCallsInfo(callsReportInfo);
    ReleaseAllConnection();
    return TELEPHONY_NO_ERROR;
}

bool CSControl::ConnectionInDialing()
{
    CellularCallConnectionCS *pConnection = nullptr;
    std::map<std::string, CellularCallConnectionCS>::iterator it;
    for (it = connectionMap_.begin(); it != connectionMap_.end(); ++it) {
        pConnection = &it->second;
        if (pConnection != nullptr && pConnection->GetStatus() == CALL_STATUS_DIALING) {
            return true;
        }
    }
    return false;
}

bool CSControl::HasMoreThanOneIncomingConnection()
{
    int count = 0;
    CellularCallConnectionCS *pConnection = nullptr;
    std::map<std::string, CellularCallConnectionCS>::iterator it;
    for (it = connectionMap_.begin(); it != connectionMap_.end(); ++it) {
        pConnection = &it->second;
        if (pConnection != nullptr &&
            (pConnection->GetStatus() == CALL_STATUS_INCOMING || pConnection->GetStatus() == CALL_STATUS_WAITING)) {
            if (++count > 1) {
                return true;
            }
        }
    }
    return false;
}

void CSControl::ReleaseAllConnection()
{
    connectionMap_.clear();
}
} // namespace CellularCall
} // namespace OHOS