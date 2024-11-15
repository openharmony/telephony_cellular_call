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

#include "gtest/gtest.h"

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
#include "system_ability_definition.h"
#include "token.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
const int32_t SIM1_SLOTID = 0;
const int32_t SIM2_SLOTID = 1;
const int32_t INVALID_SLOTID = 0xFF;
const std::string PHONE_NUMBER = "0000000";
const std::string PHONE_NUMBER_SECOND = "1111111";
const std::string PHONE_NUMBER_THIRD = "2222222";

class Cs1Test : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
    int32_t TestDialCallByCs(int32_t slotId, std::string code);
    void JudgeIsEmergencyPhoneNumber();
    bool HasSimCard(int32_t slotId)
    {
        bool hasSimCard = false;
        DelayedRefSingleton<CoreServiceClient>::GetInstance().HasSimCard(slotId, hasSimCard);
        return hasSimCard;
    }
private:
    int32_t InitCellularCallInfo(int32_t accountId, std::string phonenumber, CellularCallInfo &callInfo);
};

int32_t CsCallOperationTest::TestDialCallByCs(int32_t slotId, std::string code)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemAbilityMgr == nullptr) {
        return TELEPHONY_ERR_FAIL;
    }
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    if (remote == nullptr) {
        return TELEPHONY_ERR_FAIL;
    }
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    if (telephonyService == nullptr) {
        return TELEPHONY_ERR_FAIL;
    }
    CellularCallInfo callInfo;
    int32_t ret = TELEPHONY_SUCCESS;
    ret = InitCellularCallInfo(slotId, code, callInfo);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    // close ims, make this time use cs to test
    ret = telephonyService->SetImsSwitchStatus(slotId, false);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    ret = telephonyService->Dial(callInfo);
    return ret;
};

int32_t Cs1Test::InitCellularCallInfo(int32_t accountId, std::string phonenumber,
    CellularCallInfo &callInfo)
{
    callInfo.accountId = accountId;
    callInfo.slotId = accountId;
    callInfo.index = accountId;
    callInfo.callType = CallType::TYPE_CS;
    callInfo.videoState = 0; // 0 means audio
    if (memset_s(callInfo.phoneNum, kMaxNumberLen, 0, kMaxNumberLen) != EOK) {
        return TELEPHONY_ERR_MEMSET_FAIL;
    }
    if (phonenumber.length() > static_cast<size_t>(kMaxNumberLen)) {
        return CALL_ERR_NUMBER_OUT_OF_RANGE;
    }
    if (memcpy_s(callInfo.phoneNum, kMaxNumberLen, phonenumber.c_str(), phonenumber.length()) != EOK) {
        return TELEPHONY_ERR_MEMCPY_FAIL;
    }
    return TELEPHONY_SUCCESS;
};

void Cs1Test::JudgeIsEmergencyPhoneNumber()
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

void Cs1Test::SetUpTestCase(void)
{
    // step 3: Set Up Test Case
}

void Cs1Test::TearDownTestCase(void)
{
    // step 3: Tear Down Test Case
}

void Cs1Test::SetUp(void)
{
    // step 3: input testcase setup step
}

void Cs1Test::TearDown(void)
{
    // step 3: input testcase teardown step
}

/**
 * @tc.number   cellular_call_cs_test_001
 * @tc.name     Test the corresponding functions by entering commands, such as 1 -- Dial, 2 -- Hangup, 3 -- Reject, etc
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_cs_test_001, Function | MediumTest | Level0)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    std::cout << "HWTEST_F cellular_call_cs_test_001";
}

/**
 * @tc.number   cellular_call_cs_test_002
 * @tc.name     Test the corresponding functions by entering commands, such as 1 -- Dial, 2 -- Hangup, 3 -- Reject, etc
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_cs_test_002, Function | MediumTest | Level1)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    std::cout << "HWTEST_F cellular_call_cs_test_002";
}

/**
 * @tc.number   Telephony_CallManager_SetEmergencyCallList_0101
 * @tc.name     SetEmergencyCallList "443,356,789",test SetEmergencyCallList(),return success
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_SetEmergencyCallList_0101, Function | MediumTest | Level3)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto emergencyRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(emergencyRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(emergencyRemote);
    ASSERT_TRUE(telephonyService != nullptr);

    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }

    std::vector<EmergencyCall> eccVec;
    EmergencyCall temp0 = { "499", "460", EccType::TYPE_CATEGORY, SimpresentType::TYPE_NO_CARD,
        AbnormalServiceType::TYPE_ALL };
    EmergencyCall temp1 = { "443", "460", EccType::TYPE_POLICE, SimpresentType::TYPE_NO_CARD,
        AbnormalServiceType::TYPE_ALL };
    EmergencyCall temp2 = { "356", "460", EccType::TYPE_AMBULANCE, SimpresentType::TYPE_NO_CARD,
        AbnormalServiceType::TYPE_ALL };
    EmergencyCall temp3 = { "783", "460", EccType::TYPE_FIRE, SimpresentType::TYPE_NO_CARD,
        AbnormalServiceType::TYPE_ALL };
    EmergencyCall temp4 = { "975", "460", EccType::TYPE_SEA, SimpresentType::TYPE_HAS_CARD,
        AbnormalServiceType::TYPE_ONLY_CS };
    EmergencyCall temp5 = { "350", "460", EccType::TYPE_MOUNTAIN, SimpresentType::TYPE_HAS_CARD,
        AbnormalServiceType::TYPE_ALL };
    eccVec.push_back(temp0);
    eccVec.push_back(temp1);
    eccVec.push_back(temp2);
    eccVec.push_back(temp3);
    eccVec.push_back(temp4);
    eccVec.push_back(temp5);
    if (HasSimCard(SIM1_SLOTID)) {
        EXPECT_EQ(telephonyService->SetEmergencyCallList(SIM1_SLOTID, eccVec), 0);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        EXPECT_EQ(telephonyService->SetEmergencyCallList(SIM2_SLOTID, eccVec), 0);
    }
    JudgeIsEmergencyPhoneNumber();
}

HWTEST_F(Cs1Test, cellular_call_IsOperatorConfigEmergencyCallList_0001, Function | MediumTest | Level3)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto operatorRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(operatorRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(operatorRemote);
    ASSERT_TRUE(telephonyService != nullptr);

    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    OperatorConfig opc;
    if (HasSimCard(SIM1_SLOTID)) {
        DelayedRefSingleton<CoreServiceClient>::GetInstance().GetOperatorConfigs(SIM1_SLOTID, opc);
        if (opc.stringArrayValue.find(KEY_EMERGENCY_CALL_STRING_ARRAY) != opc.stringArrayValue.end()) {
            for (auto number : opc.stringArrayValue[KEY_EMERGENCY_CALL_STRING_ARRAY]) {
                bool enabled = false;
                int32_t errorCode = telephonyService->IsEmergencyPhoneNumber(SIM1_SLOTID, number, enabled);
                EXPECT_EQ(TELEPHONY_SUCCESS, errorCode);
            }
        }
    }
    if (HasSimCard(SIM2_SLOTID)) {
        DelayedRefSingleton<CoreServiceClient>::GetInstance().GetOperatorConfigs(SIM2_SLOTID, opc);
        if (opc.stringArrayValue.find(KEY_EMERGENCY_CALL_STRING_ARRAY) != opc.stringArrayValue.end()) {
            for (auto number : opc.stringArrayValue[KEY_EMERGENCY_CALL_STRING_ARRAY]) {
                bool enabled = false;
                int32_t errorCode = telephonyService->IsEmergencyPhoneNumber(SIM2_SLOTID, number, enabled);
                EXPECT_EQ(TELEPHONY_SUCCESS, errorCode);
            }
        }
    }
}

/**
 * @tc.number   cellular_call_DialCall_0001
 * @tc.name     Test for SetClip function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0001, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*30#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*30#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0002
 * @tc.name     Test for SetClip function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0002, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "#30#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "#30#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0003
 * @tc.name     Test for getClip function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0003, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*#30#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*#30#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0004
 * @tc.name     Test for SetClir function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0004, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*31#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*31#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0005
 * @tc.name     Test for SetClir function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0005, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "#31#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "#31#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0006
 * @tc.name     Test for GetClir function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0006, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*#31#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*#31#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0007
 * @tc.name     Test for SetCallTransfer function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0007, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*21#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*21#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0008
 * @tc.name     Test for SetCallTransfer function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0008, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "#21#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "#21#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0009
 * @tc.name     Test for GetCallTransfer function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0009, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*#21#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*#21#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0010
 * @tc.name     Test for SetCallRestriction function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0010, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*33#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*33#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0011
 * @tc.name     Test for SetCallRestriction function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0011, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "#33#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "#33#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0012
 * @tc.name     Test for GetCallRestriction function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0012, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*#33#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*#33#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0013
 * @tc.name     Test for SetCallWaiting function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0013, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*43#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*43#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0014
 * @tc.name     Test for SetCallWaiting function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0014, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "#43#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "#43#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0015
 * @tc.name     Test for GetCallWaiting function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0015, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*#43#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*#43#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0016
 * @tc.name     Test for AlterPinPassword function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0016, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*04#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*04#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0017
 * @tc.name     Test for UnlockPuk function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0017, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*05#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*05#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0018
 * @tc.name     Test for AlterPin2Password function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0018, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*042#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*042#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0019
 * @tc.name     Test for UnlockPuk2 function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0019, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*052#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*052#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0020
 * @tc.name     Test for SendUssd function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0020, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM1_SLOTID, "*4444#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(SIM2_SLOTID, "*4444#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0021
 * @tc.name     Test for dial function with invalid slot by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_DialCall_0021, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = TestDialCallByCs(INVALID_SLOTID, PHONE_NUMBER);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = TestDialCallByCs(INVALID_SLOTID, PHONE_NUMBER);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_HangUpCall_0001
 * @tc.name     Test for HangUp function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_HangUpCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto hangUpCallRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(hangUpCallRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(hangUpCallRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    CellularCallInfo hangUpCallInfo;
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, hangUpCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HangUp(hangUpCallInfo, CallSupplementType::TYPE_DEFAULT);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
        ret = telephonyService->HangUp(hangUpCallInfo, CallSupplementType::TYPE_HANG_UP_ACTIVE);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, hangUpCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HangUp(hangUpCallInfo, CallSupplementType::TYPE_DEFAULT);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
        ret = telephonyService->HangUp(hangUpCallInfo, CallSupplementType::TYPE_HANG_UP_ACTIVE);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_HangUpCall_0002
 * @tc.name     Test for HangUp function with invalid slot by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_HangUpCall_0002, Function | MediumTest | Level2)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto hangUpCallRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(hangUpCallRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(hangUpCallRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo hangUpCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, hangUpCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HangUp(hangUpCallInfo, CallSupplementType::TYPE_DEFAULT);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo hangUpCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, hangUpCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HangUp(hangUpCallInfo, CallSupplementType::TYPE_DEFAULT);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_AnswerCall_0001
 * @tc.name     Test for answer function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_AnswerCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto answerCallRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(answerCallRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(answerCallRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo answerCallInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, answerCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Answer(answerCallInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo answerCallInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, answerCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Answer(answerCallInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
}

/**
 * @tc.number   cellular_call_AnswerCall_0002
 * @tc.name     Test for answer function with invalid slot by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_AnswerCall_0002, Function | MediumTest | Level2)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto answerCallRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(answerCallRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(answerCallRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo answerCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, answerCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Answer(answerCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo answerCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, answerCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Answer(answerCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_RejectCall_0001
 * @tc.name     Test for reject function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_RejectCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto rejectCallRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(rejectCallRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(rejectCallRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo rejectCallInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, rejectCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Reject(rejectCallInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo rejectCallInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, rejectCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Reject(rejectCallInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
}

/**
 * @tc.number   cellular_call_RejectCall_0002
 * @tc.name     Test for reject function with invalid slot by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_RejectCall_0002, Function | MediumTest | Level2)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto rejectCallRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(rejectCallRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(rejectCallRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo rejectCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, rejectCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Reject(rejectCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo rejectCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, rejectCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Reject(rejectCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_HoldCall_0001
 * @tc.name     Test for hold call function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_HoldCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto holdCallRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(holdCallRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(holdCallRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo holdCallInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, holdCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HoldCall(holdCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo holdCallInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, holdCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HoldCall(holdCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_HoldCall_0002
 * @tc.name     Test for hold function with invalid slot by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_HoldCall_0002, Function | MediumTest | Level2)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto holdCallRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(holdCallRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(holdCallRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo holdCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, holdCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HoldCall(holdCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo holdCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, holdCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HoldCall(holdCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_UnHoldCall_0001
 * @tc.name     Test for unhold call function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_UnHoldCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto unHoldCallRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(unHoldCallRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(unHoldCallRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo unHoldCallInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, unHoldCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->UnHoldCall(unHoldCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo unHoldCallInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, unHoldCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->UnHoldCall(unHoldCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_UnHoldCall_0002
 * @tc.name     Test for unhold function with invalid slot by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_UnHoldCall_0002, Function | MediumTest | Level2)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto unHoldCallRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(unHoldCallRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(unHoldCallRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo unHoldCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, unHoldCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->UnHoldCall(unHoldCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo unHoldCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, unHoldCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->UnHoldCall(unHoldCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_SwitchCall_0001
 * @tc.name     Test for switch call function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_SwitchCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto switchCallRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(switchCallRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(switchCallRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo switchCallInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, switchCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SwitchCall(switchCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo switchCallInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, switchCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SwitchCall(switchCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_SwitchCall_0002
 * @tc.name     Test for switch function with invalid slot by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs1Test, cellular_call_SwitchCall_0002, Function | MediumTest | Level2)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto switchCallRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(switchCallRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(switchCallRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo switchCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, switchCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SwitchCall(switchCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo switchCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, switchCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SwitchCall(switchCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}
} // namespace Telephony
} // namespace OHOS
