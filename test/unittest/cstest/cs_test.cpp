/*
 * Copyright (C) 2021-2023 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "cellular_call_callback.h"
#include "cellular_call_handler.h"
#include "cellular_call_proxy.h"
#include "cellular_call_register.h"
#include "cellular_call_service.h"
#include "cellular_call_supplement.h"
#include "config_request.h"
#include "core_service_client.h"
#include "cs_control.h"
#include "tel_ril_call_parcel.h"
#include "operator_config_types.h"
#include "radio_event.h"
#include "securec.h"
#include "sim_state_type.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
const int32_t SIM1_SLOTID = 0;
const int32_t SIM2_SLOTID = 1;
const std::string PHONE_NUMBER = "0000000";
const std::string PHONE_NUMBER_SECOND = "1111111";
const std::string PHONE_NUMBER_THIRD = "2222222";
const int32_t CELLULAR_CALL_SUCCESS = 0;
const int32_t CELLULAR_CALL_ERROR = -1;

bool CsTest::HasSimCard(int32_t slotId)
{
    bool hasSimCard = false;
    DelayedRefSingleton<CoreServiceClient>::GetInstance().HasSimCard(slotId, hasSimCard);
    return hasSimCard;
}

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
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::DIAL)] = &CsTest::Dial;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::HANG_UP)] = &CsTest::HangUp;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::REJECT)] = &CsTest::Reject;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::ANSWER)] = &CsTest::Answer;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::HOLD_CALL)] = &CsTest::HoldCall;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::UN_HOLD_CALL)] = &CsTest::UnHoldCall;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SWITCH_CALL)] = &CsTest::SwitchCall;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::EMERGENCY_CALL)] = &CsTest::IsEmergencyPhoneNumber;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::COMBINE_CONFERENCE)] = &CsTest::CombineConference;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SEPARATE_CONFERENCE)] = &CsTest::SeparateConference;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::INVITE_TO_CONFERENCE)] =
        &CsTest::InviteToConference;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::KICK_OUT_CONFERENCE)] =
        &CsTest::KickOutFromConference;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::HANG_UP_ALL_CONNECTION)] =
        &CsTest::HangUpAllConnection;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::REGISTER_CALLBACK)] =
        &CsTest::RegisterCallBack;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::UNREGISTER_CALLBACK)] =
        &CsTest::UnRegisterCallBack;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::START_DTMF)] = &CsTest::StartDtmf;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::STOP_DTMF)] = &CsTest::StopDtmf;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SEND_DTMF)] = &CsTest::SendDtmf;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::START_RTT)] = &CsTest::StartRtt;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::STOP_RTT)] = &CsTest::StopRtt;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_CALL_TRANSFER)] =
        &CsTest::SetCallTransferInfo;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::GET_CALL_TRANSFER)] =
        &CsTest::GetCallTransferInfo;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_CALL_WAITING)] =
        &CsTest::SetCallWaiting;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::GET_CALL_WAITING)] =
        &CsTest::GetCallWaiting;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_CALL_RESTRICTION)] =
        &CsTest::SetCallRestriction;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::GET_CALL_RESTRICTION)] =
        &CsTest::GetCallRestriction;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_CALL_RESTRICTION_PWD)] =
        &CsTest::SetCallRestrictionPassword;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_MUTE)] = &CsTest::SetMute;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::GET_MUTE)] = &CsTest::GetMute;
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
    if (InitCallInfo(callInfo) != CELLULAR_CALL_SUCCESS) {
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
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
    if (InitCallInfo(callInfo) != CELLULAR_CALL_SUCCESS) {
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    return telephonyService->Answer(callInfo);
}

int32_t CsTest::Reject(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test Reject entry.\n";
    CellularCallInfo callInfo;
    if (InitCallInfo(callInfo) != CELLULAR_CALL_SUCCESS) {
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    std::cout << "please enter the connect index:";
    std::cin >> callInfo.index;
    return telephonyService->Reject(callInfo);
}

int32_t CsTest::HoldCall(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test HoldCall entry.\n";
    CellularCallInfo callInfo;
    if (InitCallInfo(callInfo) != CELLULAR_CALL_SUCCESS) {
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    return telephonyService->HoldCall(callInfo);
}

int32_t CsTest::UnHoldCall(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test UnHoldCall entry.\n";
    CellularCallInfo callInfo;
    if (InitCallInfo(callInfo) != CELLULAR_CALL_SUCCESS) {
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    return telephonyService->UnHoldCall(callInfo);
}

int32_t CsTest::SwitchCall(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SwitchCall entry.\n";
    CellularCallInfo callInfo;
    if (InitCallInfo(callInfo) != CELLULAR_CALL_SUCCESS) {
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
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
    bool enabled = false;
    telephonyService->IsEmergencyPhoneNumber(slotId, phoneNum, enabled);
    return enabled;
}

int32_t CsTest::CombineConference(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test CombineConference entry." << std::endl;
    CellularCallInfo callInfo;
    if (InitCallInfo(callInfo) != CELLULAR_CALL_SUCCESS) {
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    return telephonyService->CombineConference(callInfo);
}

int32_t CsTest::SeparateConference(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SeparateConference entry." << std::endl;
    CellularCallInfo callInfo;
    if (InitCallInfo(callInfo) != CELLULAR_CALL_SUCCESS) {
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
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
    CellularCallInfo callInfo;
    if (InitCallInfo(callInfo) != CELLULAR_CALL_SUCCESS) {
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    std::cout << "please enter the need kick out index:";
    std::cin >> callInfo.index;
    return telephonyService->KickOutFromConference(callInfo);
}

int32_t CsTest::HangUpAllConnection(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test HangUpAllConnection entry." << std::endl;
    return telephonyService->HangUpAllConnection();
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
    if (InitCallInfo(callInfo) != CELLULAR_CALL_SUCCESS) {
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
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
    if (InitCallInfo(callInfo) != CELLULAR_CALL_SUCCESS) {
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    std::cout << "please enter the index:";
    std::cin >> callInfo.index;
    return telephonyService->StopDtmf(callInfo);
}

int32_t CsTest::SendDtmf(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SendDtmf entry." << std::endl;
    CellularCallInfo callInfo;
    if (InitCallInfo(callInfo) != CELLULAR_CALL_SUCCESS) {
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
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

int32_t CsTest::SetCallRestrictionPassword(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetCallRestrictionPassword entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    std::cout << "please enter the fac(0 - 4):";
    int32_t fac = 0;
    std::cin >> fac;
    CallRestrictionType facType = static_cast<CallRestrictionType>(fac);
    std::cout << "please enter the old password:";
    char oldPassword[kMaxNumberLen + 1] = { 0 };
    std::cin >> oldPassword;
    std::cout << "please enter the new password:";
    char newPassword[kMaxNumberLen + 1] = { 0 };
    std::cin >> newPassword;
    int32_t ret = telephonyService->SetCallRestrictionPassword(slotId, facType, oldPassword, newPassword);
    (void)memset_s(oldPassword, sizeof(oldPassword), 0, sizeof(oldPassword));
    (void)memset_s(newPassword, sizeof(newPassword), 0, sizeof(newPassword));
    return ret;
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

void CsTest::JudgeIsEmergencyPhoneNumber()
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);

    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    bool enabled = false;
    int32_t successCode = 1;
    if (HasSimCard(SIM1_SLOTID)) {
        telephonyService->IsEmergencyPhoneNumber(SIM1_SLOTID, "499", enabled);
        EXPECT_NE(enabled, successCode);
        telephonyService->IsEmergencyPhoneNumber(SIM1_SLOTID, "443", enabled);
        EXPECT_NE(enabled, successCode);
        telephonyService->IsEmergencyPhoneNumber(SIM1_SLOTID, "356", enabled);
        EXPECT_NE(enabled, successCode);
        telephonyService->IsEmergencyPhoneNumber(SIM1_SLOTID, "975", enabled);
        EXPECT_NE(enabled, successCode);
        telephonyService->IsEmergencyPhoneNumber(SIM1_SLOTID, "783", enabled);
        EXPECT_NE(enabled, successCode);
        telephonyService->IsEmergencyPhoneNumber(SIM1_SLOTID, "350", enabled);
        EXPECT_NE(enabled, successCode);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        telephonyService->IsEmergencyPhoneNumber(SIM2_SLOTID, "499", enabled);
        EXPECT_NE(enabled, successCode);
        telephonyService->IsEmergencyPhoneNumber(SIM2_SLOTID, "443", enabled);
        EXPECT_NE(enabled, successCode);
        telephonyService->IsEmergencyPhoneNumber(SIM2_SLOTID, "356", enabled);
        EXPECT_NE(enabled, successCode);
        telephonyService->IsEmergencyPhoneNumber(SIM2_SLOTID, "975", enabled);
        EXPECT_NE(enabled, successCode);
        telephonyService->IsEmergencyPhoneNumber(SIM2_SLOTID, "783", enabled);
        EXPECT_NE(enabled, successCode);
        telephonyService->IsEmergencyPhoneNumber(SIM2_SLOTID, "350", enabled);
        EXPECT_NE(enabled, successCode);
    }
}

int32_t CsTest::InputNumForInterface(const sptr<CellularCallInterface> &telephonyService) const
{
    int32_t ret = -1;
    bool loopFlag = true;
    int32_t InputNumber = 0;
    int32_t returnNum = 1000; // end loop variable value
    while (loopFlag) {
        std::cout << "\n**********Unit Test Start**********\n"
                     "Usage: please input a cmd num:\n"
                     "1:Dial\n2:HangUp\n3:Reject\n4:Answer\n5:HoldCall\n6:UnHoldCall\n7:SwitchCall\n"
                     "8:IsEmergencyPhoneNumber\n10:CombineConference\n11:SeparateConference\n12:InviteToConference\n"
                     "13:KickOutFromConference\n14:HangUpAllConnection\n"
                     "17:RegisterCallBack\n18:UnRegisterCallBack\n100:StartDtmf\n101:StopDtmf\n102:SendDtmf\n"
                     "104:StartRtt\n105:StopRtt\n200:SetCallTransferInfo\n201:GetCallTransferInfo\n"
                     "203:SetCallWaiting\n204:GetCallWaiting\n205:SetCallRestriction\n"
                     "206:GetCallRestriction\n208:SetCallRestrictionPassword\n309:SetMute\n310:GetMute\n"
                     "1000:Exit\n"
                     "***********************************\n"
                     "Your choice: ";
        std::cin >> InputNumber;
        if (InputNumber == returnNum) {
            std::cout << "exiting...\n";
            break;
        }
        auto itFunc = requestFuncMap_.find(InputNumber);
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

int32_t CsTest::InitCallInfo(CellularCallInfo &callInfo) const
{
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "CellularCallService return, memset_s failed. \n";
        return CELLULAR_CALL_ERROR;
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
    return CELLULAR_CALL_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS
