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
    requestFuncMap_['A'] = &CsTest::Dial;
    requestFuncMap_['B'] = &CsTest::HangUp;
    requestFuncMap_['C'] = &CsTest::Answer;
    requestFuncMap_['D'] = &CsTest::Reject;
    requestFuncMap_['E'] = &CsTest::HoldCall;
    requestFuncMap_['F'] = &CsTest::UnHoldCall;
    requestFuncMap_['G'] = &CsTest::SwitchCall;
    requestFuncMap_['H'] = &CsTest::IsEmergencyPhoneNumber;
    requestFuncMap_['I'] = &CsTest::CombineConference;
    requestFuncMap_['J'] = &CsTest::SeparateConference;
    requestFuncMap_['K'] = &CsTest::CallSupplement;
    requestFuncMap_['L'] = &CsTest::StartDtmf;
    requestFuncMap_['M'] = &CsTest::StopDtmf;
    requestFuncMap_['N'] = &CsTest::SendDtmf;
    requestFuncMap_['O'] = &CsTest::SendDtmfString;
    requestFuncMap_['P'] = &CsTest::SetCallTransferInfo;
    requestFuncMap_['Q'] = &CsTest::GetCallTransferInfo;
    requestFuncMap_['R'] = &CsTest::SetCallWaiting;
    requestFuncMap_['S'] = &CsTest::GetCallWaiting;
    requestFuncMap_['T'] = &CsTest::SetCallRestriction;
    requestFuncMap_['U'] = &CsTest::GetCallRestriction;
    requestFuncMap_['V'] = &CsTest::RegisterCallBack;
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
        printf("CellularCallService return, memset_s failed. \n");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    callInfo.slotId = 0;
    telephonyService->Dial(callInfo);
    return CELLULAR_CALL_SUCCESS;
}

int32_t CsTest::HangUp(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test HangUp entry.\n";
    CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        printf("CellularCallService return, memset_s failed. \n");
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
    std::cout << "please enter the connect index:";
    std::cin >> callInfo.index;

    telephonyService->HangUp(callInfo);
    return CELLULAR_CALL_SUCCESS;
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
    callInfo.slotId = 0;

    telephonyService->Answer(callInfo);
    return CELLULAR_CALL_SUCCESS;
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
    callInfo.slotId = 0;
    std::cout << "please enter the connect index:";
    std::cin >> callInfo.index;

    telephonyService->Reject(callInfo);
    return CELLULAR_CALL_SUCCESS;
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
    callInfo.slotId = 0;
    telephonyService->HoldCall(callInfo);
    return CELLULAR_CALL_SUCCESS;
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
    callInfo.slotId = 0;
    telephonyService->UnHoldCall(callInfo);
    return CELLULAR_CALL_SUCCESS;
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
    callInfo.slotId = 0;
    telephonyService->SwitchCall(callInfo);
    return CELLULAR_CALL_SUCCESS;
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
    telephonyService->IsEmergencyPhoneNumber(phoneNum, slotId, errorCode);
    return CELLULAR_CALL_SUCCESS;
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
    callInfo.slotId = 0;
    telephonyService->CombineConference(callInfo);
    return CELLULAR_CALL_SUCCESS;
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
    callInfo.slotId = 0;
    std::cout << "please enter the need split index:";
    std::cin >> callInfo.index;
    telephonyService->SeparateConference(callInfo);
    return CELLULAR_CALL_SUCCESS;
}

int32_t CsTest::CallSupplement(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test CallSupplement entry." << std::endl;
    std::cout << "please enter the type:";
    int32_t type;
    std::cin >> type;
    telephonyService->CallSupplement(static_cast<CallSupplementType>(type));
    return CELLULAR_CALL_SUCCESS;
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
    telephonyService->StartDtmf(cDtmfCode, callInfo);
    return CELLULAR_CALL_SUCCESS;
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
    telephonyService->StopDtmf(callInfo);
    return CELLULAR_CALL_SUCCESS;
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
    telephonyService->SendDtmf(cDtmfCode, callInfo);
    return CELLULAR_CALL_SUCCESS;
}

int32_t CsTest::SendDtmfString(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SendDtmfString entry." << std::endl;
    std::string dtmfCodeStr;
    std::cout << "please enter the Dtmf code string:";
    std::cin >> dtmfCodeStr;
    std::string phoneNum;
    std::cout << "please enter the phone number:";
    std::cin >> phoneNum;
    int32_t switchOn;
    std::cout << "please enter the switchOn:";
    std::cin >> switchOn;
    int32_t switchOff;
    std::cout << "please enter the switchOff:";
    std::cin >> switchOff;
    telephonyService->SendDtmfString(dtmfCodeStr, phoneNum, switchOn, switchOff);
    return CELLULAR_CALL_SUCCESS;
}

int32_t CsTest::SetCallTransferInfo(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetCallTransferInfoInfo entry.\n";
    int32_t slotId = 0;
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
    telephonyService->SetCallTransferInfo(callTransferInfo, slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t CsTest::GetCallTransferInfo(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetCallTransferInfo entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the transfer type(0 - 5):";
    int32_t type = 0;
    std::cin >> type;
    telephonyService->GetCallTransferInfo(static_cast<CallTransferType>(type), slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t CsTest::SetCallWaiting(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetCallWaiting entry.\n";
    bool activate = true;
    int32_t slotId = 0;
    telephonyService->SetCallWaiting(activate, slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t CsTest::GetCallWaiting(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetCallWaiting entry.\n";
    int32_t slotId = 0;
    telephonyService->GetCallWaiting(slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t CsTest::SetCallRestriction(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetCallRestriction entry.\n";
    int32_t slotId = 0;
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
    telephonyService->SetCallRestriction(info, slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t CsTest::GetCallRestriction(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetCallRestriction entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the fac(0 - 4):";
    int32_t facType = 0;
    std::cin >> facType;
    telephonyService->GetCallRestriction(static_cast<CallRestrictionType>(facType), slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t CsTest::RegisterCallBack(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test RegisterCallBack entry.\n";
    return CELLULAR_CALL_SUCCESS;
}

int32_t CsTest::InputNumForInterface(const sptr<CellularCallInterface> &telephonyService) const
{
    char interfaceNum = '0';
    bool loopFlag = true;
    int32_t ret = -1;
    while (loopFlag) {
        std::cout << "\n**********Unit Test Start**********\n"
                     "Usage: please input a cmd num:\n"
                     "A:Dial\n"
                     "B:HangUp\n"
                     "C:Answer\n"
                     "D:Reject\n"
                     "E:HoldCall\n"
                     "F:UnHoldCall\n"
                     "G:SwitchCall\n"
                     "H:IsEmergencyPhoneNumber\n"
                     "I:CombineConference\n"
                     "J:SeparateConference\n"
                     "K:CallSupplement\n"
                     "L:StartDtmf\n"
                     "M:StopDtmf\n"
                     "N:SendDtmf\n"
                     "O:SendDtmfString\n"
                     "P:SetCallTransferInfo\n"
                     "Q:GetCallTransferInfo\n"
                     "R:SetCallWaiting\n"
                     "S:GetCallWaiting\n"
                     "T:SetCallRestriction\n"
                     "U:GetCallRestriction\n"
                     "V:RegisterCallBack\n"
                     "W:Exit\n"
                     "***********************************\n"
                     "Your choice: ";
        std::cin >> interfaceNum;
        if (interfaceNum == 'W') {
            break;
        }
        auto itFunc = requestFuncMap_.find(interfaceNum);
        if (itFunc != requestFuncMap_.end()) {
            auto requestFunc = itFunc->second;
            if (requestFunc != nullptr) {
                ret = (this->*requestFunc)(telephonyService);
            }
        }
        if (ret != CELLULAR_CALL_SUCCESS) {
            return ret;
        }
    }
    return 0;
}

HWTEST_F(CsTest, cellular_call_interface_001, TestSize.Level1)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemAbilityMgr == nullptr) {
        printf("CellularCallService Get ISystemAbilityManager failed.\n");
        return;
    }
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    if (remote == nullptr) {
        printf("CellularCallService Remote service not exists.\n");
        return;
    }
    sptr<CellularCallInterface> telephonyService = iface_cast<CellularCallInterface>(remote);
    std::cout << "HWTEST_F cellular_call_interface_001";
}
} // namespace Telephony
} // namespace OHOS
