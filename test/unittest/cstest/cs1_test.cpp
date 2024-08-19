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
const int32_t INVALID_SLOTID = 0xFF;
const std::string PHONE_NUMBER = "0000000";
const std::string PHONE_NUMBER_SECOND = "1111111";
const std::string PHONE_NUMBER_THIRD = "2222222";

/**
 * @tc.number   cellular_call_cs_test_001
 * @tc.name     Test the corresponding functions by entering commands, such as 1 -- Dial, 2 -- Hangup, 3 -- Reject, etc
 * @tc.desc     Function test
 */
HWTEST_F(CsTest, cellular_call_cs_test_001, Function | MediumTest | Level0)
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
HWTEST_F(CsTest, cellular_call_cs_test_002, Function | MediumTest | Level1)
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
HWTEST_F(CsTest, cellular_call_SetEmergencyCallList_0101, Function | MediumTest | Level3)
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

HWTEST_F(CsTest, cellular_call_IsOperatorConfigEmergencyCallList_0001, Function | MediumTest | Level3)
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
} // namespace Telephony
} // namespace OHOS
