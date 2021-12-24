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

#include "ims_control.h"

#include "securec.h"

#include "module_service_utils.h"
#include "cellular_call_register.h"
#include "standardize_utils.h"
#include "emergency_utils.h"

namespace OHOS {
namespace Telephony {
IMSControl::~IMSControl()
{
    TELEPHONY_LOGI("~IMSControl start");
    ReleaseAllConnection();
}

int32_t IMSControl::Dial(const CellularCallInfo &callInfo)
{
    TELEPHONY_LOGI("Dial start");
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

    // sip uri needs to remove separator
    std::string newPhoneNum = dialString;
    StandardizeUtils standardizeUtils;
    if (dialString.find('@') != std::string::npos || dialString.find("%40") != std::string::npos) {
        newPhoneNum = standardizeUtils.RemoveSeparatorsPhoneNumber(dialString);
    }

    CLIRMode clirMode = CLIRMode::DEFAULT;
    if (!IsNeedExecuteMMI(newPhoneNum, clirMode)) {
        return DialJudgment(newPhoneNum, clirMode, callInfo.videoState);
    }
    TELEPHONY_LOGI("Dial return, mmi code type.");
    return RETURN_TYPE_MMI;
}

int32_t IMSControl::DialJudgment(const std::string &phoneNum, CLIRMode &clirMode, int32_t videoState)
{
    TELEPHONY_LOGI("DialJudgment entry.");
    if (!CanCall(connectionMap_)) {
        TELEPHONY_LOGE("DialJudgment return, error type: call state error.");
        return CALL_ERR_CALL_COUNTS_EXCEED_LIMIT;
    }

    // Calls can be put on hold, recovered, released, added to conversation,
    // and transferred similarly as defined in 3GPP TS 22.030 [19].
    if (IsInState(connectionMap_, CALL_STATUS_ACTIVE)) {
        // New calls must be active, so other calls need to be hold
        TELEPHONY_LOGI("DialJudgment, have connection in active state.");
        CellularCallConnectionIMS connection;
        // - a call can be temporarily disconnected from the ME but the connection is retained by the network
        connection.HoldRequest(GetSlotId());
    }
    return EncapsulateDial(phoneNum, clirMode, videoState);
}

int32_t IMSControl::EncapsulateDial(const std::string &phoneNum, CLIRMode &clirMode, int32_t videoState) const
{
    TELEPHONY_LOGI("EncapsulateDial start");

    ImsDialInfoStruct dialInfo;
    dialInfo.videoState = videoState;
    EmergencyUtils emergencyUtils;
    dialInfo.bEmergencyCall = emergencyUtils.IsEmergencyCall(phoneNum, GetSlotId());

    /**
     * <idx>: integer type;
     * call identification number as described in 3GPP TS 22.030 [19] subclause 4.5.5.1
     * this number can be used in +CHLD command operations
     * <dir>:
     */
    dialInfo.phoneNum = phoneNum;
    /**
     * <n> (parameter sets the adjustment for outgoing calls):
     *  0	presentation indicator is used according to the subscription of the CLIR service
     *  1	CLIR invocation
     *  2	CLIR suppression
     */
    dialInfo.clirMode = clirMode;
    /**
     * An example of voice group call service request usage:
     * ATD*17*753#500; (originate voice group call with the priority level 3)
     * OK (voice group call setup was successful)
     */

    CellularCallConnectionIMS cellularCallConnectionIms;
    return cellularCallConnectionIms.DialRequest(dialInfo, GetSlotId());
}

int32_t IMSControl::HangUp(CallSupplementType type, const CellularCallInfo &callInfo)
{
    TELEPHONY_LOGI("HangUp start");
    switch (type) {
        case CallSupplementType::TYPE_DEFAULT: {
            auto pConnection =
                GetConnectionData<ImsConnectionMap &, CellularCallConnectionIMS *>(connectionMap_, callInfo.phoneNum);
            if (pConnection == nullptr) {
                TELEPHONY_LOGI("HangUp: connection cannot be matched, use index directly");
                pConnection = FindConnectionByIndex<ImsConnectionMap &, CellularCallConnectionIMS *>(
                    connectionMap_, callInfo.index);
            }
            if (pConnection == nullptr) {
                TELEPHONY_LOGE("HangUp return, error type: connection is null");
                return CALL_ERR_CALL_CONNECTION_NOT_EXIST;
            }
            return pConnection->EndRequest(callInfo.index, GetSlotId());
        }
        case CallSupplementType::TYPE_HANG_UP_HOLD_WAIT:
            // release the second (active) call and recover the first (held) call
        case CallSupplementType::TYPE_HANG_UP_ACTIVE: {
            CellularCallConnectionIMS connection;
            return connection.CallSupplementRequest(type, GetSlotId());
        }
        case CallSupplementType::TYPE_HANG_UP_ALL: {
            TELEPHONY_LOGI("HangUp, hang up all call");
            CellularCallConnectionIMS connection;
            return connection.RejectRequest(GetSlotId());
        }
        default: {
            TELEPHONY_LOGE("HangUp warring, type is invalid");
            return TELEPHONY_ERR_ARGUMENT_INVALID;
        }
    }
}

int32_t IMSControl::Answer(const CellularCallInfo &callInfo)
{
    TELEPHONY_LOGI("IMSControl::Answer start");
    auto pConnection =
        GetConnectionData<ImsConnectionMap &, CellularCallConnectionIMS *>(connectionMap_, callInfo.phoneNum);
    if (pConnection == nullptr) {
        TELEPHONY_LOGE("IMSControl::Answer, error type: connection is null");
        return CALL_ERR_CALL_CONNECTION_NOT_EXIST;
    }
    if (IsInState(connectionMap_, CALL_STATUS_ACTIVE) && pConnection->GetStatus() == CALL_STATUS_WAITING) {
        TELEPHONY_LOGI("Answer there is an active call when you call, or third party call waiting");
        auto con = FindConnectionByState<ImsConnectionMap &, CellularCallConnectionIMS *>(
            connectionMap_, CALL_STATUS_ACTIVE);
        if (con == nullptr) {
            TELEPHONY_LOGE("Answer return, error type: con is null, there are no active calls");
            return CALL_ERR_CALL_CONNECTION_NOT_EXIST;
        }
        return con->SwapRequest(GetSlotId());
    }
    if (pConnection->GetStatus() == CALL_STATUS_ALERTING || pConnection->GetStatus() == CALL_STATUS_INCOMING ||
        pConnection->GetStatus() == CALL_STATUS_WAITING) {
        return pConnection->AnswerRequest(callInfo.videoState, GetSlotId());
    }
    TELEPHONY_LOGE("IMSControl::Answer return, error type: call state error, phone not ringing.");
    return CALL_ERR_CALL_STATE;
}

int32_t IMSControl::Reject(const CellularCallInfo &callInfo)
{
    TELEPHONY_LOGI("IMSControl::Reject start");
    auto pConnection =
        GetConnectionData<ImsConnectionMap &, CellularCallConnectionIMS *>(connectionMap_, callInfo.phoneNum);
    if (pConnection == nullptr) {
        TELEPHONY_LOGI("Reject: connection cannot be matched, use index directly");
        pConnection =
            FindConnectionByIndex<ImsConnectionMap &, CellularCallConnectionIMS *>(connectionMap_, callInfo.index);
    }
    if (pConnection == nullptr) {
        TELEPHONY_LOGE("IMSControl::Reject, error type: connection is null");
        return CALL_ERR_CALL_CONNECTION_NOT_EXIST;
    }
    if (!pConnection->IsRingingState()) {
        TELEPHONY_LOGE("IMSControl::Reject return, error type: call state error, phone not ringing.");
        return CALL_ERR_CALL_STATE;
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("IMSControl::Reject, error type: GetInstance() is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    return pConnection->RejectRequest(GetSlotId());
}

int32_t IMSControl::HoldCall()
{
    TELEPHONY_LOGI("HoldCall start");
    if (IsInState(connectionMap_, CALL_STATUS_INCOMING)) {
        TELEPHONY_LOGE("HoldCall return, error type: call state error.");
        return CALL_ERR_CALL_STATE;
    }
    CellularCallConnectionIMS cellularCallConnectionIms;
    return cellularCallConnectionIms.HoldRequest(GetSlotId());
}

int32_t IMSControl::UnHoldCall()
{
    TELEPHONY_LOGI("UnHoldCall start");
    CellularCallConnectionIMS cellularCallConnectionIms;
    return cellularCallConnectionIms.ActiveRequest(GetSlotId());
}

int32_t IMSControl::SwitchCall()
{
    TELEPHONY_LOGI("SwitchCall start");
    CellularCallConnectionIMS cellularCallConnectionIms;
    return cellularCallConnectionIms.SwapRequest(GetSlotId());
}

/**
 * Add another remote party, to which a private communication has been established using
 * the same procedures as in Section 1.3.8.1, if the number of remote parties does not then
 * exceed the maximum number allowed, which results in an active multiParty call.
 */
int32_t IMSControl::CombineConference()
{
    CellularCallConnectionIMS connection;
    int32_t voiceCall = 0;
    return connection.CombineConferenceRequest(GetSlotId(), voiceCall);
}

void IMSControl::ReleaseAllConnection()
{
    connectionMap_.clear();
}

ImsConnectionMap IMSControl::GetConnectionMap()
{
    return connectionMap_;
}

int32_t IMSControl::ReportCallsData(const CallInfoList &callInfoList)
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

int32_t IMSControl::ReportHungUpInfo()
{
    TELEPHONY_LOGI("ReportHungUpInfo entry");
    CallsReportInfo callsReportInfo;
    for (auto &it : connectionMap_) {
        CallReportInfo reportInfo = it.second.GetCallReportInfo();
        reportInfo.state = CALL_STATUS_DISCONNECTED;
        reportInfo.accountId = GetSlotId();
        callsReportInfo.callVec.push_back(reportInfo);
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

int32_t IMSControl::ReportIncomingInfo(const CallInfoList &callInfoList)
{
    TELEPHONY_LOGI("ReportIncomingInfo entry");
    CallsReportInfo callsReportInfo;
    for (int32_t i = 0; i < callInfoList.callSize; ++i) {
        CallReportInfo reportInfo = EncapsulationCallReportInfo(callInfoList.calls[i]);

        CellularCallConnectionIMS connection;
        connection.SetStatus(static_cast<TelCallState>(callInfoList.calls[i].state));
        connection.SetIndex(callInfoList.calls[i].index);
        connection.SetOrUpdateCallReportInfo(reportInfo);
        SetConnectionData(connectionMap_, callInfoList.calls[i].number, connection);

        callsReportInfo.callVec.push_back(reportInfo);
    }
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("ReportIncomingInfo return, GetInstance() is nullptr.");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    callsReportInfo.slotId = GetSlotId();
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportCallsInfo(callsReportInfo);
    return TELEPHONY_SUCCESS;
}

int32_t IMSControl::ReportUpdateInfo(const CallInfoList &callInfoList)
{
    TELEPHONY_LOGI("ReportUpdateInfo entry");
    CallsReportInfo callsReportInfo;
    for (int32_t i = 0; i < callInfoList.callSize; ++i) {
        CallReportInfo reportInfo = EncapsulationCallReportInfo(callInfoList.calls[i]);

        auto pConnection = GetConnectionData<ImsConnectionMap &, CellularCallConnectionIMS *>(
            connectionMap_, callInfoList.calls[i].number);
        if (pConnection == nullptr) {
            CellularCallConnectionIMS connection;
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

CallReportInfo IMSControl::EncapsulationCallReportInfo(const CallInfo &callInfo)
{
    TELEPHONY_LOGI("EncapsulationCallReportInfo entry");
    CallReportInfo callReportInfo;
    if (memset_s(&callReportInfo, sizeof(callReportInfo), 0, sizeof(callReportInfo)) != EOK) {
        TELEPHONY_LOGE("EncapsulationCallReportInfo return, memset_s fail.");
        return callReportInfo;
    }

    size_t cpyLen = strlen(callInfo.number.c_str()) + 1;
    if (strcpy_s(callReportInfo.accountNum, cpyLen, callInfo.number.c_str()) != EOK) {
        TELEPHONY_LOGE("EncapsulationCallReportInfo return, strcpy_s fail.");
        return callReportInfo;
    }
    callReportInfo.index = callInfo.index;
    callReportInfo.accountId = GetSlotId();
    callReportInfo.state = static_cast<TelCallState>(callInfo.state);
    callReportInfo.voiceDomain = callInfo.voiceDomain;
    callReportInfo.callType = CallType::TYPE_IMS;
    callReportInfo.callMode = callInfo.callType ? VideoStateType::TYPE_VIDEO : VideoStateType::TYPE_VOICE;
    return callReportInfo;
}

void IMSControl::DeleteConnection(CallsReportInfo &callsReportInfo, const CallInfoList &callInfoList)
{
    TELEPHONY_LOGI("DeleteConnection entry");
    auto it = connectionMap_.begin();
    while (it != connectionMap_.end()) {
        if (!it->second.GetFlag()) {
            CallReportInfo callReportInfo = it->second.GetCallReportInfo();
            callReportInfo.state = CALL_STATUS_DISCONNECTED;
            callsReportInfo.callVec.push_back(callReportInfo);
            connectionMap_.erase(it++);
        } else {
            it->second.SetFlag(false);
            ++it;
        }
    }
}
} // namespace Telephony
} // namespace OHOS