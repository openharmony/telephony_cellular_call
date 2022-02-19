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

#include "cellular_call_supplement.h"

#include "securec.h"
#include "cellular_call_register.h"
#include "standardize_utils.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
constexpr unsigned long long operator"" _hash(char const *p, size_t s)
{
    return StandardizeUtils::HashCompileTime(p);
}

void CellularCallSupplement::GetClip(int32_t slotId, const MMIData &mmiData)
{
    const std::string interrogate = "*#";
    if (!mmiData.actionString.empty() && mmiData.actionString == interrogate) {
        supplementRequest_.InquireClipRequest(slotId);
    }
}

void CellularCallSupplement::GetClir(int32_t slotId, const MMIData &mmiData)
{
    const std::string interrogate = "*#";
    const std::string activate = "*";
    const std::string deactivate = "#";
    if (mmiData.actionString.empty()) {
        TELEPHONY_LOGE("GetClir return, actionString is empty!");
        return;
    }
    if (mmiData.actionString == activate) {
        supplementRequest_.SetClirRequest(slotId, ACTIVATE_ACTION);
    } else if (mmiData.actionString == deactivate) {
        supplementRequest_.SetClirRequest(slotId, DEACTIVATE_ACTION);
    } else if (mmiData.actionString == interrogate) {
        supplementRequest_.InquireClirRequest(slotId);
    }
}

void CellularCallSupplement::DealCallTransfer(int32_t slotId, const MMIData &mmiData)
{
    const std::string interrogate = "*#";
    int32_t serviceCode = ObtainServiceCode(mmiData.serviceInfoB);
    int32_t cause = ObtainCause(mmiData.serviceCode);
    if (!mmiData.actionString.empty() && mmiData.actionString == interrogate) {
        supplementRequest_.GetCallTransferRequest(slotId, cause);
        return;
    }
    std::string phoneNumber = mmiData.serviceInfoA;
    int32_t callForwardAction;
    if (mmiData.actionString.empty()) {
        TELEPHONY_LOGE("DealCallTransfer return, actionString is empty!");
        return;
    }

    // 3GPP TS 24.082 V4.0.0 (2001-03) 1 Call Forwarding Unconditional (CFU)
    // 3GPP TS 24.082 V4.0.0 (2001-03) 2 Call Forwarding on mobile subscriber Busy (CFB)
    // 3GPP TS 24.082 V4.0.0 (2001-03) 3 Call Forwarding on No Reply (CFNRy)
    // 3GPP TS 24.082 V4.0.0 (2001-03) 4 Call Forwarding on mobile subscriber Not Reachable (CFNRc)
    switch (StandardizeUtils::Hash_(mmiData.actionString.c_str())) {
        case "*"_hash:
            if (phoneNumber.empty()) {
                callForwardAction = (int32_t)CallTransferSettingType::CALL_TRANSFER_ENABLE;
            } else {
                callForwardAction = (int32_t)CallTransferSettingType::CALL_TRANSFER_REGISTRATION;
            }
            break;
        case "#"_hash:
            callForwardAction = (int32_t)CallTransferSettingType::CALL_TRANSFER_DISABLE;
            break;
        case "**"_hash:
            callForwardAction = (int32_t)CallTransferSettingType::CALL_TRANSFER_REGISTRATION;
            break;
        case "##"_hash:
            callForwardAction = (int32_t)CallTransferSettingType::CALL_TRANSFER_ERASURE;
            break;
        default:
            TELEPHONY_LOGE("DealCallTransfer return, actionString out of range, please check!");
            return;
    }
    supplementRequest_.SetCallTransferRequest(slotId, callForwardAction, cause, phoneNumber, serviceCode);
}

int32_t CellularCallSupplement::ObtainServiceCode(const std::string &serviceInfoB)
{
    if (serviceInfoB.empty()) {
        TELEPHONY_LOGE("ObtainServiceCode return, serviceInfoB is empty!");
        return NONE;
    }
    int32_t intServiceInfoB = atoi(serviceInfoB.c_str());
    switch (intServiceInfoB) {
        case ALL_TELE_SERVICES:
            return SHORT_MESSAGE_SERVICE + FAX + VOICE;
        case TELE_SERVICES:
            return VOICE;
        case ALL_DATA_TELE_SERVICES:
            return SHORT_MESSAGE_SERVICE + FAX;
        case FACSIMILE_SERVICES:
            return FAX;
        case SHORT_MESSAGE_SERVICES:
            return SHORT_MESSAGE_SERVICE;
        case ALL_TELE_SERVICES_EXCEPT_SMS:
            return FAX + VOICE;
        case ALL_BEARER_SERVICES:
            return DATA_CIRCUIT_ASYNC + DATA_CIRCUIT_SYNC;
        case ALL_ASYNC_SERVICES:
            return DEDICATED_PAD_ACCESS + DATA_CIRCUIT_ASYNC;
        case ALL_SYNC_SERVICES:
            return DEDICATED_PACKET_ACCESS + DATA_CIRCUIT_SYNC;
        case ALL_DATA_CIRCUIT_SYNC:
            return DATA_CIRCUIT_SYNC;
        case ALL_DATA_CIRCUIT_ASYNC:
            return DATA_CIRCUIT_ASYNC;
        case ALL_GPRS_BEARER_SERVICES:
            return DEDICATED_PACKET_ACCESS;
        default:
            TELEPHONY_LOGE("ObtainServiceCode return, serviceInfoB out of range, please check!");
            return NONE;
    }
}

int32_t CellularCallSupplement::ObtainCause(const std::string &actionStr)
{
    if (actionStr.empty()) {
        TELEPHONY_LOGE("ObtainCause return, actionStr is empty!");
        return TELEPHONY_ERROR;
    }

    /*
     * 3GPP TS 22.030 V4.0.0 (2001-03) Annex B (normative): Codes for defined Supplementary Services
     * CFU	                21
     * CF Busy	            67
     * CF No Reply	        61
     * CF Not Reachable 	62
     * all CF		        002
     * all conditional CF	004
     */
    switch (StandardizeUtils::Hash_(actionStr.c_str())) {
        case "21"_hash:
            return (int32_t)CallTransferType::TRANSFER_TYPE_UNCONDITIONAL;
        case "67"_hash:
            return (int32_t)CallTransferType::TRANSFER_TYPE_BUSY;
        case "62"_hash:
            return (int32_t)CallTransferType::TRANSFER_TYPE_NO_REPLY;
        case "61"_hash:
            return (int32_t)CallTransferType::TRANSFER_TYPE_NOT_REACHABLE;
        default:
            TELEPHONY_LOGE("ObtainCause return, actionStr out of range!");
            return TELEPHONY_ERROR;
    }
}

void CellularCallSupplement::DealCallRestriction(int32_t slotId, const MMIData &mmiData)
{
    std::string infoA = mmiData.serviceInfoA;
    std::string facType = ObtainBarringInstallation(mmiData.serviceInfoC);
    const std::string interrogate = "*#";
    const std::string activate = "*";
    const std::string deactivate = "#";
    if (mmiData.actionString.empty()) {
        TELEPHONY_LOGE("DealCallRestriction return, actionString is empty!");
        return;
    }
    if (mmiData.actionString == interrogate) {
        supplementRequest_.GetCallRestrictionRequest(slotId, facType);
    } else if (mmiData.actionString == activate || mmiData.actionString == deactivate) {
        supplementRequest_.SetCallRestrictionRequest(slotId, facType, mmiData.actionString == activate, infoA);
    }
}

std::string CellularCallSupplement::ObtainBarringInstallation(const std::string &serviceInfoC)
{
    if (serviceInfoC.empty()) {
        TELEPHONY_LOGE("ObtainBarringInstallation return, serviceInfoC is empty!");
        return std::string();
    }

    /*
     * 27007-430_2001 7.4	Facility lock +CLCK
     *  Supplementary	Service Service	Code	SIA	SIB	SIC
     * 	22.088
     * 	BAOC	            33	                 PW	BS	-
     * 	BAOIC	            331	                 PW	BS	-
     * 	BAOIC exc home	    332	                 PW	BS	-
     * 	BAIC	            35	                 PW	BS	-
     * 	BAIC roaming	    351	                 PW	BS	-
     *  all Barring Serv.   330	                 PW	BS	-
     *  Outg. Barr. Serv.   333	                 PW	BS
     *  Inc. Barr. Serv.	353	                 PW	BS
     */
    switch (StandardizeUtils::Hash_(serviceInfoC.c_str())) {
        case "33"_hash:
            // "AO"	BAOC (Barr All Outgoing Calls) (refer 3GPP TS 22.088 [6] clause 1)
            return BARR_ALL_OUTGOING_CALLS;
        case "331"_hash:
            // "OI"	BOIC (Barr Outgoing International Calls) (refer 3GPP TS 22.088 [6] clause 1)
            return BARR_OUTGOING_INTERNATIONAL_CALLS;
        case "332"_hash:
            // "OX"	BOIC exHC (Barr Outgoing International Calls except to Home Country)
            // (refer 3GPP TS 22.088 [6] clause 1)
            return BARR_OUTGOING_INTERNATIONAL_CALLS_EXCLUDING_HOME;
        case "351"_hash:
            // "IR"	BIC Roam (Barr Incoming Calls when Roaming outside the home country)
            // (refer 3GPP TS 22.088 [6] clause 2)
            return BARR_INCOMING_CALLS_OUTSIDE_HOME;
        case "35"_hash:
            // "AI"	BAIC (Barr All Incoming Calls) (refer 3GPP TS 22.088 [6] clause 2)
            return BARR_ALL_INCOMING_CALLS;
        case "330"_hash:
            // "AB"	All Barring services (refer 3GPP TS 22.030 [19]) (applicable only for <mode>=0)
            return ALL_BARRING_SERVICES;
        case "333"_hash:
            // "AG"	All outGoing barring services (refer 3GPP TS 22.030 [19]) (applicable only for <mode>=0)
            return ALL_OUTGOING_BARRING_SERVICES;
        case "353"_hash:
            // "AC"	All inComing barring services (refer 3GPP TS 22.030 [19]) (applicable only for <mode>=0)
            return ALL_INCOMING_BARRING_SERVICES;
        default:
            TELEPHONY_LOGE("ObtainBarringInstallation return, serviceInfoC out of range!");
            return std::string();
    }
}

void CellularCallSupplement::DealCallWaiting(int32_t slotId, const MMIData &mmiData)
{
    if (mmiData.actionString.empty()) {
        TELEPHONY_LOGE("DealCallWaiting return, actionString is empty!");
        return;
    }
    const std::string activate = "*";
    const std::string deactivate = "#";
    const std::string interrogate = "*#";
    if (mmiData.actionString == activate || mmiData.actionString == deactivate) {
        supplementRequest_.SetCallWaitingRequest(slotId, mmiData.actionString == activate);
    } else if (mmiData.actionString == interrogate) {
        supplementRequest_.GetCallWaitingRequest(slotId);
    }
}

void CellularCallSupplement::EventGetCallWaiting(CallWaitResult &waitingInfo)
{
    CallWaitResponse callWaitResponse;
    callWaitResponse.result = waitingInfo.result;

    /*
     * <n> (sets/shows the result code presentation status in the TA):
     * 0	disable
     * 1	enable
     */
    callWaitResponse.status = waitingInfo.status;
    callWaitResponse.classCw = waitingInfo.classCw;
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("EventGetCallWaiting return, GetInstance is nullptr.");
        return;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetWaitingResult(callWaitResponse);
}

void CellularCallSupplement::EventSetCallWaiting(HRilRadioResponseInfo &responseInfo)
{
    CallWaitResponse callWaitResponse;
    callWaitResponse.result = static_cast<int32_t>(responseInfo.error);
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("EventSetCallWaiting return, GetInstance is nullptr.");
        return;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetWaitingResult((int32_t)responseInfo.error);
}

void CellularCallSupplement::EventGetCallTransferInfo(CallForwardQueryResult &queryResult)
{
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("EventGetCallTransferInfo return, GetInstance is nullptr.");
        return;
    }

    // 3GPP TS 27.007 V3.9.0 (2001-06) 7.11	Call forwarding number and conditions +CCFC
    CallTransferResponse response;
    if (memset_s(&response, sizeof(response), 0, sizeof(response)) != EOK) {
        TELEPHONY_LOGE("EventGetCallTransferInfo return, memset_s fail.");
        return;
    }

    // <number>: string type phone number of forwarding address in format specified by <type>
    size_t cpyLen = strlen(queryResult.number.c_str()) + 1;
    if (strcpy_s(response.number, cpyLen, queryResult.number.c_str()) != EOK) {
        TELEPHONY_LOGE("EventGetCallTransferInfo return, strcpy_s fail.");
        return;
    }

    response.result = queryResult.result;

    /*
     * <status>:0	not active;    1	  active
     * */
    response.status = queryResult.status;

    /*
     * <classx> is a sum of integers each representing a class of information (default 7):
     * 1	voice (telephony)
     * 2	data (refers to all bearer services)
     * 4	fax (facsimile services)
     * 8	short message service
     * 16	data circuit sync
     * 32	data circuit async
     * 64	dedicated packet access
     * 128	dedicated PAD access
     */
    response.classx = queryResult.classx;
    // <type>: type of address octet in integer format (refer GSM 04.08 [8] subclause 10.5.4.7);
    // default 145 when dialling string includes international access code character "+", otherwise 129
    response.type = queryResult.type;

    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetTransferResult(response);
}

void CellularCallSupplement::EventSetCallTransferInfo(HRilRadioResponseInfo &responseInfo)
{
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("EventSetCallTransferInfo return, GetInstance is nullptr.");
        return;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetTransferResult((int32_t)responseInfo.error);
}

void CellularCallSupplement::EventGetCallRestriction(const CallRestrictionResult &result)
{
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("EventGetCallRestriction return, GetInstance is nullptr.");
        return;
    }
    CallRestrictionResponse response;
    response.result = result.result;

    /*
     * <status>:0	not active    1	  active
     */
    response.status = result.status;
    response.classCw = result.classCw;

    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetRestrictionResult(response);
}

void CellularCallSupplement::EventSetCallRestriction(HRilRadioResponseInfo &info)
{
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("EventSetCallRestriction return, GetInstance is nullptr.");
        return;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetRestrictionResult((int32_t)info.error);
}

int32_t CellularCallSupplement::SetCallTransferInfo(int32_t slotId, const CallTransferInfo &cfInfo)
{
    if (!PhoneTypeGsmOrNot(slotId)) {
        TELEPHONY_LOGE("SetCallTransferInfo return, network type is not supported!");
        return CALL_ERR_UNSUPPORTED_NETWORK_TYPE;
    }
    if (strlen(cfInfo.transferNum) == 0) {
        TELEPHONY_LOGE("SetCallTransferInfo return, transferNum is empty!");
        return CALL_ERR_PHONE_NUMBER_EMPTY;
    }

    /*
     * <reason>:
     * 0   unconditional
     * 1   mobile busy
     * 2   no reply
     * 3   not reachable
     * 4   all call forwarding (refer 3GPP TS 22.030 [19])
     * 5   all conditional call forwarding (refer 3GPP TS 22.030 [19])
     * <mode>:
     * 0   disable
     * 1   enable
     * 2   query status
     * 3   registration
     * 4   erasure
     */
    if (cfInfo.type > CallTransferType::TRANSFER_TYPE_NOT_REACHABLE ||
        cfInfo.type < CallTransferType::TRANSFER_TYPE_UNCONDITIONAL ||
        cfInfo.settingType > CallTransferSettingType::CALL_TRANSFER_ERASURE ||
        cfInfo.settingType < CallTransferSettingType::CALL_TRANSFER_DISABLE) {
        TELEPHONY_LOGE("SetCallTransferInfo return, parameter out of range!");
        return CALL_ERR_PARAMETER_OUT_OF_RANGE;
    }

    std::string dialString(cfInfo.transferNum);
    return supplementRequest_.SetCallTransferRequest(
        slotId, (int32_t)cfInfo.settingType, (int32_t)cfInfo.type, dialString, 1);
}

int32_t CellularCallSupplement::GetCallTransferInfo(int32_t slotId, CallTransferType type)
{
    if (!PhoneTypeGsmOrNot(slotId)) {
        TELEPHONY_LOGE("GetCallTransferInfo return, network type is not supported!");
        return CALL_ERR_UNSUPPORTED_NETWORK_TYPE;
    }

    /*
     * When querying the status of a network service (<mode>=2) the response line for 'not active' case
     * (<status>=0) should be returned only if service is not active for any <class>
     */
    return supplementRequest_.GetCallTransferRequest(slotId, (int32_t)type);
}

bool CellularCallSupplement::PhoneTypeGsmOrNot(int32_t slotId)
{
    return moduleServiceUtils_.GetNetworkStatus(slotId) == PhoneType::PHONE_TYPE_IS_GSM;
}

int32_t CellularCallSupplement::SetCallWaiting(int32_t slotId, bool activate)
{
    /*
     * <n> (sets/shows the result code presentation status in the TA):
     * 0	disable
     * 1	enable
     */
    if (!PhoneTypeGsmOrNot(slotId)) {
        TELEPHONY_LOGE("SetCallWaiting return, network type is not supported!");
        return CALL_ERR_UNSUPPORTED_NETWORK_TYPE;
    }
    return supplementRequest_.SetCallWaitingRequest(slotId, activate);
}

int32_t CellularCallSupplement::GetCallWaiting(int32_t slotId)
{
    if (!PhoneTypeGsmOrNot(slotId)) {
        TELEPHONY_LOGE("GetCallWaiting return, network type is not supported!");
        return CALL_ERR_UNSUPPORTED_NETWORK_TYPE;
    }
    return supplementRequest_.GetCallWaitingRequest(slotId);
}

int32_t CellularCallSupplement::SetCallRestriction(int32_t slotId, const CallRestrictionInfo &cRInfo)
{
    /*
     * <fac> values reserved by the present document:
     * "SC"	SIM (lock SIM/UICC card) (SIM/UICC asks password in ME power up and when this lock command issued)
     * "AO"	BAOC (Barr All Outgoing Calls) (refer 3GPP TS 22.088 [6] clause 1)
     * "OI"	BOIC (Barr Outgoing International Calls) (refer 3GPP TS 22.088 [6] clause 1)
     * "OX"	BOIC exHC (Barr Outgoing International Calls except to Home Country) (refer 3GPP TS 22.088 [6] clause 1)
     * "AI"	BAIC (Barr All Incoming Calls) (refer 3GPP TS 22.088 [6] clause 2)
     * "IR"	BIC Roam (Barr Incoming Calls when Roaming outside the home country) (refer 3GPP TS 22.088 [6] clause 2)
     * "AB"	All Barring services (refer 3GPP TS 22.030 [19]) (applicable only for <mode>=0)
     * "AG"	All outGoing barring services (refer 3GPP TS 22.030 [19]) (applicable only for <mode>=0)
     * "AC"	All inComing barring services (refer 3GPP TS 22.030 [19]) (applicable only for <mode>=0)
     */
    if (!PhoneTypeGsmOrNot(slotId)) {
        TELEPHONY_LOGE("SetCallRestriction return, network type is not supported!");
        return CALL_ERR_UNSUPPORTED_NETWORK_TYPE;
    }

    std::string fac;
    switch (cRInfo.fac) {
        case CallRestrictionType::RESTRICTION_TYPE_ALL_OUTGOING:
            fac = BARR_ALL_OUTGOING_CALLS;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_INTERNATIONAL:
            fac = BARR_OUTGOING_INTERNATIONAL_CALLS;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_INTERNATIONAL_EXCLUDING_HOME:
            fac = BARR_OUTGOING_INTERNATIONAL_CALLS_EXCLUDING_HOME;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_ALL_INCOMING:
            fac = BARR_ALL_INCOMING_CALLS;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_ROAMING_INCOMING:
            fac = BARR_INCOMING_CALLS_OUTSIDE_HOME;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_ALL_CALLS:
            fac = ALL_BARRING_SERVICES;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_OUTGOING_SERVICES:
            fac = ALL_OUTGOING_BARRING_SERVICES;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_INCOMING_SERVICES:
            fac = ALL_INCOMING_BARRING_SERVICES;
            break;
        default:
            TELEPHONY_LOGE("SetCallRestriction return, fac parameter out of range!");
            return CALL_ERR_PARAMETER_OUT_OF_RANGE;
    }
    if (cRInfo.mode < CallRestrictionMode::RESTRICTION_MODE_DEACTIVATION ||
        cRInfo.mode > CallRestrictionMode::RESTRICTION_MODE_ACTIVATION) {
        TELEPHONY_LOGE("SetCallRestriction return, mode parameter out of range!");
        return CALL_ERR_PARAMETER_OUT_OF_RANGE;
    }
    std::string info(cRInfo.password);
    return supplementRequest_.SetCallRestrictionRequest(slotId, fac, (int32_t)cRInfo.mode, info);
}

int32_t CellularCallSupplement::GetCallRestriction(int32_t slotId, CallRestrictionType facType)
{
    if (!PhoneTypeGsmOrNot(slotId)) {
        TELEPHONY_LOGE("GetCallRestriction return, network type is not supported!");
        return CALL_ERR_UNSUPPORTED_NETWORK_TYPE;
    }
    std::string fac;
    switch (facType) {
        case CallRestrictionType::RESTRICTION_TYPE_ALL_OUTGOING:
            fac = BARR_ALL_OUTGOING_CALLS;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_INTERNATIONAL:
            fac = BARR_OUTGOING_INTERNATIONAL_CALLS;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_INTERNATIONAL_EXCLUDING_HOME:
            fac = BARR_OUTGOING_INTERNATIONAL_CALLS_EXCLUDING_HOME;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_ALL_INCOMING:
            fac = BARR_ALL_INCOMING_CALLS;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_ROAMING_INCOMING:
            fac = BARR_INCOMING_CALLS_OUTSIDE_HOME;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_ALL_CALLS:
            fac = ALL_BARRING_SERVICES;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_OUTGOING_SERVICES:
            fac = ALL_OUTGOING_BARRING_SERVICES;
            break;
        case CallRestrictionType::RESTRICTION_TYPE_INCOMING_SERVICES:
            fac = ALL_INCOMING_BARRING_SERVICES;
            break;
        default:
            TELEPHONY_LOGE("GetCallRestriction return, parameter out of range!");
            return CALL_ERR_PARAMETER_OUT_OF_RANGE;
    }
    return supplementRequest_.GetCallRestrictionRequest(slotId, fac);
}

void CellularCallSupplement::EventGetClip(GetClipResult &getClipResult)
{
    ClipResponse clipResponse;
    clipResponse.result = getClipResult.result;
    clipResponse.action = getClipResult.action;
    clipResponse.clipStat = getClipResult.clipStat;
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("EventGetClip return, GetInstance is nullptr.");
        return;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetClipResult(clipResponse);
}

void CellularCallSupplement::EventGetClir(GetClirResult &result)
{
    ClirResponse response;
    // 3GPP TS 27.007 V3.9.0 (2001-06) 7.7	Calling line identification restriction +CLIR
    response.result = result.result;
    response.action = result.action;
    response.clirStat = result.clirStat;
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("EventGetClir return, GetInstance is nullptr.");
        return;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetClirResult(response);
}

void CellularCallSupplement::EventSetClir(HRilRadioResponseInfo &info)
{
    TELEPHONY_LOGI("CellularCallSupplement::EventSetClir entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("EventSetClir return, GetInstance is nullptr.");
        return;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetClirResult(static_cast<int32_t>(info.error));
}

int32_t CellularCallSupplement::SendUssd(int32_t slotId, const std::string &msg)
{
    TELEPHONY_LOGI("CellularCallSupplement::SendUssd entry");
    if (!PhoneTypeGsmOrNot(slotId)) {
        TELEPHONY_LOGE("SendUssd return, network type is not supported!");
        return CALL_ERR_UNSUPPORTED_NETWORK_TYPE;
    }
    return supplementRequest_.SendUssdRequest(slotId, msg);
}

void CellularCallSupplement::EventSendUssd(HRilRadioResponseInfo &responseInfo)
{
    TELEPHONY_LOGI("CellularCallSupplement::EventSendUssd entry");
    if (DelayedSingleton<CellularCallRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("EventSendUssd return, GetInstance is nullptr.");
        return;
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSendUssdResult(
        static_cast<int32_t>(responseInfo.error));
}
} // namespace Telephony
} // namespace OHOS
