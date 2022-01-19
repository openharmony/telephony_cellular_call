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

#include "cs_test.h"

#include "iservice_registry.h"
#include "securec.h"
#include "system_ability_definition.h"

#include "cellular_call_client.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
const int32_t CELLULAR_CALL_SUCCESS = 0;
void CsTest::SetUpTestCase(void)
{
    // step 3: Set Up Test Case
}

void CsTest::TearDownTestCase(void)
{
    // step 3: Tear Down Test Case
}

void CsTest::SetUp(void)
{
    // step 3: input testcase setup step
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::DIAL)] = &CsTest::Dial;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::HANG_UP)] = &CsTest::HangUp;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::REJECT)] = &CsTest::Reject;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::ANSWER)] = &CsTest::Answer;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::HOLD_CALL)] = &CsTest::HoldCall;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::UN_HOLD_CALL)] = &CsTest::UnHoldCall;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SWITCH_CALL)] = &CsTest::SwitchCall;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::EMERGENCY_CALL)] =
        &CsTest::IsEmergencyPhoneNumber;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::COMBINE_CONFERENCE)] =
        &CsTest::CombineConference;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SEPARATE_CONFERENCE)] =
        &CsTest::SeparateConference;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::INVITE_TO_CONFERENCE)] =
        &CsTest::InviteToConference;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::KICK_OUT_CONFERENCE)] =
        &CsTest::KickOutFromConference;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::HANG_UP_ALL_CONNECTION)] =
        &CsTest::HangUpAllConnection;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::UPDATE_CALL_MEDIA_MODE)] =
        &CsTest::UpdateImsCallMode;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::REGISTER_CALLBACK)] =
        &CsTest::RegisterCallBack;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::UNREGISTER_CALLBACK)] =
        &CsTest::UnRegisterCallBack;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::START_DTMF)] = &CsTest::StartDtmf;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::STOP_DTMF)] = &CsTest::StopDtmf;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SEND_DTMF)] = &CsTest::SendDtmf;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::START_RTT)] = &CsTest::StartRtt;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::STOP_RTT)] = &CsTest::StopRtt;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_CALL_TRANSFER)] =
        &CsTest::SetCallTransferInfo;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::GET_CALL_TRANSFER)] =
        &CsTest::GetCallTransferInfo;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_CALL_WAITING)] =
        &CsTest::SetCallWaiting;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::GET_CALL_WAITING)] =
        &CsTest::GetCallWaiting;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_CALL_RESTRICTION)] =
        &CsTest::SetCallRestriction;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::GET_CALL_RESTRICTION)] =
        &CsTest::GetCallRestriction;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_MUTE)] = &CsTest::SetMute;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::GET_MUTE)] = &CsTest::GetMute;
}

void CsTest::TearDown(void)
{
    // step 3: input testcase teardown step
}

int32_t CsTest::Dial(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test Dial entry.\n";
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "CellularCallService return, memset_s failed. \n";
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    callInfo.slotId = slotId;
    return telephonyService->Dial(callInfo);
}

int32_t CsTest::HangUp(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test HangUp entry.\n";
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "CellularCallService return, memset_s failed. \n";
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    std::cout << "please enter the call type(0:CS  1:IMS):";
    int32_t callType = 0;
    std::cin >> callType;
    callInfo.callType = static_cast<CallType>(callType);
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    callInfo.slotId = slotId;
    std::cout << "please enter the connect index:";
    std::cin >> callInfo.index;
    std::cout << "please enter the type:";
    int32_t type;
    std::cin >> type;
    return telephonyService->HangUp(callInfo, static_cast<CallSupplementType>(type));
}

int32_t CsTest::Answer(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test Answer entry.\n";
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "CellularCallService return, memset_s failed. \n";
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    std::cout << "please enter the call type(0:CS  1:IMS):";
    int32_t callType = 0;
    std::cin >> callType;
    callInfo.callType = static_cast<CallType>(callType);
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    callInfo.slotId = slotId;
    return telephonyService->Answer(callInfo);
}

int32_t CsTest::Reject(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test Reject entry.\n";
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "CellularCallService return, memset_s failed. \n";
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    std::cout << "please enter the call type(0:CS  1:IMS):";
    int32_t callType = 0;
    std::cin >> callType;
    callInfo.callType = static_cast<CallType>(callType);
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    callInfo.slotId = slotId;
    std::cout << "please enter the connect index:";
    std::cin >> callInfo.index;
    return telephonyService->Reject(callInfo);
}

int32_t CsTest::HoldCall(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test HoldCall entry.\n";
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "CellularCallService return, memset_s failed. \n";
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    std::cout << "please enter the call type(0:CS  1:IMS):";
    int32_t callType = 0;
    std::cin >> callType;
    callInfo.callType = static_cast<CallType>(callType);
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    callInfo.slotId = slotId;
    return telephonyService->HoldCall(callInfo);
}

int32_t CsTest::UnHoldCall(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test UnHoldCall entry.\n";
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "CellularCallService return, memset_s failed. \n";
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    std::cout << "please enter the call type(0:CS  1:IMS):";
    int32_t callType = 0;
    std::cin >> callType;
    callInfo.callType = static_cast<CallType>(callType);
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    callInfo.slotId = slotId;
    return telephonyService->UnHoldCall(callInfo);
}

int32_t CsTest::SwitchCall(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SwitchCall entry.\n";
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "CellularCallService return, memset_s failed. \n";
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }

    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    std::cout << "please enter the call type(0:CS  1:IMS):";
    int32_t callType = 0;
    std::cin >> callType;
    callInfo.callType = static_cast<CallType>(callType);
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    callInfo.slotId = slotId;
    return telephonyService->SwitchCall(callInfo);
}

int32_t CsTest::IsEmergencyPhoneNumber(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test IsEmergencyPhoneNumber entry.\n";
    std::string phoneNum;
    std::cout << "input phoneNum: ";
    std::cin >> phoneNum;
    std::cout << "input slotId: ";
    int32_t slotId = 0;
    std::cin >> slotId;
    int32_t errorCode = 0;
    return telephonyService->IsEmergencyPhoneNumber(slotId, phoneNum, errorCode);
}

int32_t CsTest::CombineConference(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test CombineConference entry." << std::endl;
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "CellularCallService return, memset_s failed. \n";
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    std::cout << "please enter the call type(0:CS  1:IMS):";
    int32_t callType = 0;
    std::cin >> callType;
    callInfo.callType = static_cast<CallType>(callType);
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    callInfo.slotId = slotId;
    return telephonyService->CombineConference(callInfo);
}

int32_t CsTest::SeparateConference(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SeparateConference entry." << std::endl;
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "CellularCallService return, memset_s failed. \n";
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    std::cout << "please enter the need split phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    std::cout << "please enter the call type(0:CS  1:IMS):";
    int32_t callType = 0;
    std::cin >> callType;
    callInfo.callType = static_cast<CallType>(callType);
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    callInfo.slotId = slotId;
    std::cout << "please enter the need split index:";
    std::cin >> callInfo.index;
    return telephonyService->SeparateConference(callInfo);
}

int32_t CsTest::InviteToConference(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test InviteToConference entry." << std::endl;
    std::vector<std::string> numberList;
    std::cout << "please enter the invite phone number:";
    std::string phoneNum;
    std::cin >> phoneNum;
    numberList.push_back(phoneNum);
    std::cout << "please enter the slotId:";
    int32_t slotId = 0;
    return telephonyService->InviteToConference(slotId, numberList);
}

int32_t CsTest::KickOutFromConference(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test KickOutFromConference entry." << std::endl;
    std::vector<std::string> numberList;
    std::cout << "please enter the kick out phone number:";
    std::string phoneNum;
    std::cin >> phoneNum;
    numberList.push_back(phoneNum);
    std::cout << "please enter the slotId:";
    int32_t slotId = 0;
    return telephonyService->KickOutFromConference(slotId, numberList);
}

int32_t CsTest::HangUpAllConnection(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test HangUpAllConnection entry." << std::endl;

    if (DelayedRefSingleton<CellularCallClient>::GetInstance().GetCellularCallProxy() == nullptr) {
        std::cout << "HangUpAllConnection return, GetCellularCallProxy is nullptr!" << std::endl;
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    return DelayedRefSingleton<CellularCallClient>::GetInstance().GetCellularCallProxy()->HangUpAllConnection();
}

int32_t CsTest::UpdateImsCallMode(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test UpdateImsCallMode entry." << std::endl;
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "UpdateImsCallMode return, memset_s failed. \n";
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    std::cout << "please enter the need update phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.callType = CallType::TYPE_IMS;
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    callInfo.slotId = slotId;
    std::cout << "please enter the need update index:";
    std::cin >> callInfo.index;
    std::cout << "please enter the mode:";
    int32_t mode = 0;
    std::cin >> mode;
    return telephonyService->UpdateImsCallMode(callInfo, static_cast<ImsCallMode>(mode));
}

int32_t CsTest::RegisterCallBack(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test RegisterCallBack entry.\n";
    return CELLULAR_CALL_SUCCESS;
}

int32_t CsTest::UnRegisterCallBack(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test UnRegisterCallBack entry.\n";
    return telephonyService->UnRegisterCallManagerCallBack();
}

int32_t CsTest::StartDtmf(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test StartDtmf entry." << std::endl;
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "CellularCallService return, memset_s failed. \n";
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    std::cout << "please enter the call type(0:CS  1:IMS):";
    int32_t callType = 0;
    std::cin >> callType;
    callInfo.callType = static_cast<CallType>(callType);
    callInfo.slotId = 0;
    std::cout << "please enter the index:";
    std::cin >> callInfo.index;
    char cDtmfCode;
    std::cout << "please enter the Dtmf code:";
    std::cin >> cDtmfCode;
    return telephonyService->StartDtmf(cDtmfCode, callInfo);
}

int32_t CsTest::StopDtmf(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test StopDtmf entry." << std::endl;
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "CellularCallService return, memset_s failed. \n";
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    std::cout << "please enter the call type(0:CS  1:IMS):";
    int32_t callType = 0;
    std::cin >> callType;
    callInfo.callType = static_cast<CallType>(callType);
    callInfo.slotId = 0;
    std::cout << "please enter the index:";
    std::cin >> callInfo.index;
    return telephonyService->StopDtmf(callInfo);
}

int32_t CsTest::SendDtmf(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SendDtmf entry." << std::endl;
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "CellularCallService return, memset_s failed. \n";
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    std::cout << "please enter the call type(0:CS  1:IMS):";
    int32_t callType = 0;
    std::cin >> callType;
    callInfo.callType = static_cast<CallType>(callType);
    callInfo.slotId = 0;
    std::cout << "please enter the index:";
    std::cin >> callInfo.index;
    char cDtmfCode;
    std::cout << "please enter the Dtmf code:";
    std::cin >> cDtmfCode;
    return telephonyService->SendDtmf(cDtmfCode, callInfo);
}

int32_t CsTest::StartRtt(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test StartRtt entry." << std::endl;
    std::string msg;
    std::cout << "please enter the send msg:";
    std::cin >> msg;
    int32_t slotId;
    std::cout << "please enter the slotId:";
    std::cin >> slotId;
    return telephonyService->StartRtt(slotId, msg);
}

int32_t CsTest::StopRtt(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test StopRtt entry." << std::endl;
    int32_t slotId;
    std::cout << "please enter the slotId:";
    std::cin >> slotId;
    return telephonyService->StopRtt(slotId);
}

int32_t CsTest::SetCallTransferInfo(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetCallTransferInfoInfo entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    CallTransferInfo callTransferInfo;
    std::cout << "please enter the transfer type(0 - 5):";
    int32_t type = 0;
    std::cin >> type;
    callTransferInfo.type = static_cast<CallTransferType>(type);
    std::cout << "please enter the transfer setting type(0 - 4):";
    int32_t settingType = 0;
    std::cin >> settingType;
    callTransferInfo.settingType = static_cast<CallTransferSettingType>(settingType);
    std::cout << "please enter the phone number:";
    std::cin >> callTransferInfo.transferNum;
    return telephonyService->SetCallTransferInfo(slotId, callTransferInfo);
}

int32_t CsTest::GetCallTransferInfo(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetCallTransferInfo entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    std::cout << "please enter the transfer type(0 - 5):";
    int32_t type = 0;
    std::cin >> type;
    return telephonyService->GetCallTransferInfo(slotId, static_cast<CallTransferType>(type));
}

int32_t CsTest::SetCallWaiting(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetCallWaiting entry.\n";
    bool activate = true;
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    return telephonyService->SetCallWaiting(slotId, activate);
}

int32_t CsTest::GetCallWaiting(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetCallWaiting entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    return telephonyService->GetCallWaiting(slotId);
}

int32_t CsTest::SetCallRestriction(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetCallRestriction entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    CallRestrictionInfo info;
    std::cout << "please enter the fac(0 - 4):";
    int32_t fac = 0;
    std::cin >> fac;
    info.fac = static_cast<CallRestrictionType>(fac);
    std::cout << "please enter the phone password:";
    std::cin >> info.password;
    std::cout << "please enter the mode:";
    int32_t mode = 0;
    std::cin >> mode;
    info.mode = static_cast<CallRestrictionMode>(mode);
    return telephonyService->SetCallRestriction(slotId, info);
}

int32_t CsTest::GetCallRestriction(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetCallRestriction entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    std::cout << "please enter the fac(0 - 4):";
    int32_t facType = 0;
    std::cin >> facType;
    return telephonyService->GetCallRestriction(slotId, static_cast<CallRestrictionType>(facType));
}

int32_t CsTest::SetMute(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetMute entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    std::cout << "please enter the mute(0 - 1):";
    int32_t mute = -1;
    std::cin >> mute;
    return telephonyService->SetMute(slotId, mute);
}

int32_t CsTest::GetMute(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetMute entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    return telephonyService->GetMute(slotId);
}

int32_t CsTest::InputNumForInterface(const sptr<CellularCallInterface> &telephonyService) const
{
    int32_t ret = -1;
    bool loopFlag = true;
    int32_t InputNum = 0;
    int32_t returnNum = 1000; // end loop variable value
    while (loopFlag) {
        std::cout << "\n**********Unit Test Start**********\n"
                     "Usage: please input a cmd num:\n"
                     "1:Dial\n2:HangUp\n3:Reject\n4:Answer\n5:HoldCall\n6:UnHoldCall\n7:SwitchCall\n"
                     "8:IsEmergencyPhoneNumber\n9:CombineConference\n10:SeparateConference\n11:InviteToConference\n"
                     "12:KickOutFromConference\n13:HangUpAllConnection\n14:UpdateImsCallMode\n"
                     "15:RegisterCallBack\n16:UnRegisterCallBack\n100:StartDtmf\n101:StopDtmf\n102:SendDtmf\n"
                     "103:StartRtt\n104:StopRtt\n200:SetCallTransferInfo\n201:GetCallTransferInfo\n"
                     "202:SetCallWaiting\n203:GetCallWaiting\n"
                     "204:SetCallRestriction\n205:GetCallRestriction\n311:SetMute\n312:GetMute\n"
                     "1000:Exit\n"
                     "***********************************\n"
                     "Your choice: ";
        std::cin >> InputNum;
        if (InputNum == returnNum) {
            std::cout << "exiting...\n";
            break;
        }
        auto itFunc = requestFuncMap_.find(InputNum);
        if (itFunc != requestFuncMap_.end()) {
            auto requestFunc = itFunc->second;
            if (requestFunc != nullptr) {
                ret = (this->*requestFunc)(telephonyService);
            }
        }
        if (ret != CELLULAR_CALL_SUCCESS) {
            std::cout << "this execution did not return a successful value, please check.\n";
            return ret;
        }
    }
    return CELLULAR_CALL_SUCCESS;
}

HWTEST_F(CsTest, cellular_call_cs_test_001, TestSize.Level0)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemAbilityMgr == nullptr) {
        std::cout << "CellularCallService Get ISystemAbilityManager failed.\n";
        return;
    }
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    if (remote == nullptr) {
        std::cout << "CellularCallService Remote service not exists.\n";
        return;
    }
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    std::cout << "HWTEST_F cellular_call_cs_test_001";
}

HWTEST_F(CsTest, cellular_call_cs_test_002, TestSize.Level1)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemAbilityMgr == nullptr) {
        std::cout << "CellularCallService Get ISystemAbilityManager failed.\n";
        return;
    }
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    if (remote == nullptr) {
        std::cout << "CellularCallService Remote service not exists.\n";
        return;
    }
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    std::cout << "HWTEST_F cellular_call_cs_test_002";
}
} // namespace Telephony
} // namespace OHOS
