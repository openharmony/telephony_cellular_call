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
#include <random>

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
const int32_t INVALID_HANG_UP_TYPE = -1;
const int32_t SUCCESS_RESULT = 0;
const int32_t ERROR_RESULT = 1;
const int32_t USSD_MODE_NOTIFY = 0;
const std::string PHONE_NUMBER = "0000000";
const std::string PHONE_NUMBER_SECOND = "1111111";
const std::string PHONE_NUMBER_THIRD = "2222222";

class Cs2Test : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
    int32_t TestDialCallByCs(int32_t slotId, std::string code);
    bool HasSimCard(int32_t slotId)
    {
        bool hasSimCard = false;
        DelayedRefSingleton<CoreServiceClient>::GetInstance().HasSimCard(slotId, hasSimCard);
        return hasSimCard;
    }
    int32_t InitCellularCallInfo(int32_t accountId, std::string phonenumber, CellularCallInfo &callInfo);
};

int32_t Cs2Test::TestDialCallByCs(int32_t slotId, std::string code)
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

int32_t Cs2Test::InitCellularCallInfo(int32_t accountId, std::string phonenumber,
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

void Cs2Test::SetUpTestCase(void)
{
    // step 3: Set Up Test Case
}

void Cs2Test::TearDownTestCase(void)
{
    // step 3: Tear Down Test Case
}

void Cs2Test::SetUp(void)
{
    // step 3: input testcase setup step
}

void Cs2Test::TearDown(void)
{
    // step 3: input testcase teardown step
}

/**
 * @tc.number   cellular_call_CombineConference_0001
 * @tc.name     Test for combineConference function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CombineConference_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto combineRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(combineRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(combineRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo conferenceCallInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, conferenceCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->CombineConference(conferenceCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo conferenceCallInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, conferenceCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->CombineConference(conferenceCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_CombineConference_0002
 * @tc.name     Test for combineConference function with invalid slot by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CombineConference_0002, Function | MediumTest | Level2)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto combineRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(combineRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(combineRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo conferenceCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, conferenceCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->CombineConference(conferenceCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo conferenceCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, conferenceCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->CombineConference(conferenceCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_SeparateConference_0001
 * @tc.name     Test for separateConference function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_SeparateConference_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto separateRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(separateRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(separateRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SeparateConference(callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SeparateConference(callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_SeparateConference_0002
 * @tc.name     Test for separateConference function with invalid slot by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_SeparateConference_0002, Function | MediumTest | Level2)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto separateRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(separateRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(separateRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo separateCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, separateCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SeparateConference(separateCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo separateCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, separateCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SeparateConference(separateCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_KickOutFromConference_0001
 * @tc.name     Test for separateConference function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_KickOutFromConference_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto kickOutRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(kickOutRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(kickOutRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo kickOutCallInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, kickOutCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->KickOutFromConference(kickOutCallInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo kickOutCallInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, kickOutCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->KickOutFromConference(kickOutCallInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
}

/**
 * @tc.number   cellular_call_KickOutFromConference_0002
 * @tc.name     Test for KickOutFromConference function with invalid slot by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_KickOutFromConference_0002, Function | MediumTest | Level2)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto kickOutRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(kickOutRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(kickOutRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo kickOutCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, kickOutCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->KickOutFromConference(kickOutCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo kickOutCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, kickOutCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->KickOutFromConference(kickOutCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_HangUpAllConnection_0001
 * @tc.name     Test for hangup all connection function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_HangUpAllConnection_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto hangUpAllConRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(hangUpAllConRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(hangUpAllConRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = telephonyService->HangUpAllConnection();
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = telephonyService->HangUpAllConnection();
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_StartDtmf_0001
 * @tc.name     Test for startDtmf function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_StartDtmf_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto startDtmfRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(startDtmfRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(startDtmfRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->StartDtmf(code, callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->StartDtmf(code, callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
}

/**
 * @tc.number   cellular_call_StartDtmf_0002
 * @tc.name     Test for startDtmf function with invalid slot by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_StartDtmf_0002, Function | MediumTest | Level2)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto startDtmfRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(startDtmfRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(startDtmfRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    CellularCallInfo callInfo;
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->StartDtmf(code, callInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->StartDtmf(code, callInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_StopDtmf_0001
 * @tc.name     Test for stopDtmf function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_StopDtmf_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto stopDtmfRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(stopDtmfRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(stopDtmfRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->StopDtmf(callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->StopDtmf(callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
}

/**
 * @tc.number   cellular_call_StopDtmf_0002
 * @tc.name     Test for stopDtmf function with invalid slot by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_StopDtmf_0002, Function | MediumTest | Level2)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto stopDtmfRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(stopDtmfRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(stopDtmfRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo stopDtmfCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, stopDtmfCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->StopDtmf(stopDtmfCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo stopDtmfCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, stopDtmfCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->StopDtmf(stopDtmfCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_SendDtmf_0001
 * @tc.name     Test for sendDtmf function by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_SendDtmf_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto sendDtmfRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(sendDtmfRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(sendDtmfRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo sendDtmfCallInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, sendDtmfCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->SendDtmf(code, sendDtmfCallInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo sendDtmfCallInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, sendDtmfCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->SendDtmf(code, sendDtmfCallInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
}

/**
 * @tc.number   cellular_call_SendDtmf_0002
 * @tc.name     Test for sendDtmf function with invalid slot by cs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_SendDtmf_0002, Function | MediumTest | Level2)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto sendDtmfRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(sendDtmfRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(sendDtmfRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        CellularCallInfo sendDtmfCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, sendDtmfCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->SendDtmf(code, sendDtmfCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        CellularCallInfo sendDtmfCallInfo;
        int32_t ret = InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, sendDtmfCallInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->SendDtmf(code, sendDtmfCallInfo);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_GetDomainPreferenceMode_0001
 * @tc.name     Test for GetDomainPreferenceMode function by invalid slotId
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_GetDomainPreferenceMode_0001, Function | MediumTest | Level3)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto domainPrefModeRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(domainPrefModeRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(domainPrefModeRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = telephonyService->GetDomainPreferenceMode(INVALID_SLOTID);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = telephonyService->GetDomainPreferenceMode(INVALID_SLOTID);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_GetDomainPreferenceMode_0002
 * @tc.name     Test for GetDomainPreferenceMode function by valid slotId
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_GetDomainPreferenceMode_0002, Function | MediumTest | Level3)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto domainPrefModeRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(domainPrefModeRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(domainPrefModeRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = telephonyService->GetDomainPreferenceMode(SIM1_SLOTID);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = telephonyService->GetDomainPreferenceMode(SIM2_SLOTID);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_GetMute_0001
 * @tc.name     Test for GetMute function by invalid slotId
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_GetMute_0001, Function | MediumTest | Level3)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto getMuteRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(getMuteRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(getMuteRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = telephonyService->GetMute(INVALID_SLOTID);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = telephonyService->GetMute(INVALID_SLOTID);
        EXPECT_EQ(ret, CALL_ERR_INVALID_SLOT_ID);
    }
}

/**
 * @tc.number   cellular_call_GetMute_0002
 * @tc.name     Test for GetMute function by valid slotId
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_GetMute_0002, Function | MediumTest | Level3)
{
    AccessToken token;
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto getMuteRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(getMuteRemote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(getMuteRemote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        int32_t ret = telephonyService->GetMute(SIM1_SLOTID);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = telephonyService->GetMute(SIM2_SLOTID);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_CsControl_0001
 * @tc.name     Test for CsControl
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CsControl_0001, Function | MediumTest | Level3)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto csControlRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(csControlRemote != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto csControl = std::make_shared<CSControl>();
    CellularCallInfo cellularCallInfo;
    bool enabled = false;
    EXPECT_EQ(InitCellularCallInfo(INVALID_SLOTID, PHONE_NUMBER, cellularCallInfo), TELEPHONY_SUCCESS);
    EXPECT_EQ(csControl->Dial(cellularCallInfo, enabled), CALL_ERR_GET_RADIO_STATE_FAILED);
    EXPECT_EQ(InitCellularCallInfo(INVALID_SLOTID, "", cellularCallInfo), TELEPHONY_SUCCESS);
    EXPECT_EQ(csControl->Dial(cellularCallInfo, enabled), CALL_ERR_PHONE_NUMBER_EMPTY);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        EXPECT_EQ(InitCellularCallInfo(slotId, "*30#", cellularCallInfo), TELEPHONY_SUCCESS);
        EXPECT_EQ(csControl->DialCdma(cellularCallInfo), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(csControl->DialGsm(cellularCallInfo), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(InitCellularCallInfo(slotId, "#30#", cellularCallInfo), TELEPHONY_SUCCESS);
        EXPECT_EQ(csControl->DialGsm(cellularCallInfo), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(InitCellularCallInfo(slotId, PHONE_NUMBER, cellularCallInfo), TELEPHONY_SUCCESS);
        EXPECT_EQ(csControl->DialCdma(cellularCallInfo), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(csControl->Dial(cellularCallInfo, enabled), CALL_ERR_GET_RADIO_STATE_FAILED);
        ASSERT_FALSE(csControl->CalculateInternationalRoaming(slotId));
        EXPECT_NE(csControl->DialCdma(cellularCallInfo), TELEPHONY_SUCCESS);
        EXPECT_EQ(csControl->DialGsm(cellularCallInfo), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_NE(csControl->Answer(cellularCallInfo), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(InitCellularCallInfo(slotId, PHONE_NUMBER_SECOND, cellularCallInfo), TELEPHONY_SUCCESS);
        EXPECT_NE(csControl->Answer(cellularCallInfo), CALL_ERR_CALL_STATE);
        EXPECT_EQ(InitCellularCallInfo(slotId, PHONE_NUMBER_THIRD, cellularCallInfo), TELEPHONY_SUCCESS);
        EXPECT_NE(csControl->Answer(cellularCallInfo), CALL_ERR_CALL_STATE);
        EXPECT_NE(csControl->Reject(cellularCallInfo), CALL_ERR_CALL_STATE);
        EXPECT_EQ(InitCellularCallInfo(slotId, PHONE_NUMBER, cellularCallInfo), TELEPHONY_SUCCESS);
        EXPECT_EQ(csControl->SeparateConference(slotId, PHONE_NUMBER, 1), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(csControl->SeparateConference(slotId, "", 1), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_NE(csControl->HangUp(cellularCallInfo, CallSupplementType::TYPE_DEFAULT), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(csControl->HangUp(cellularCallInfo, CallSupplementType::TYPE_HANG_UP_ACTIVE),
            CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(
            csControl->HangUp(cellularCallInfo, CallSupplementType::TYPE_HANG_UP_ALL), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(csControl->HangUp(cellularCallInfo, static_cast<CallSupplementType>(INVALID_HANG_UP_TYPE)),
            TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_CsControl_0002
 * @tc.name     Test for CsControl
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CsControl_0002, Function | MediumTest | Level3)
{
    auto csControl = std::make_shared<CSControl>();
    CellularCallInfo cellularCallInfo;
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        CallInfoList callList;
        callList.callSize = 0;
        EXPECT_EQ(csControl->ReportCallsData(slotId, callList), TELEPHONY_SUCCESS);
        EXPECT_EQ(csControl->ReportUpdateInfo(slotId, callList), TELEPHONY_SUCCESS);
        CallInfo callInfo;
        callList.callSize = 1;
        callInfo.number = PHONE_NUMBER;
        callInfo.index = 1;
        callInfo.state = static_cast<int32_t>(TelCallState::CALL_STATUS_INCOMING);
        callList.calls.push_back(callInfo);
        EXPECT_EQ(csControl->ReportCallsData(slotId, callList), TELEPHONY_SUCCESS);
        callList.callSize = 2;
        callInfo.state = static_cast<int32_t>(TelCallState::CALL_STATUS_ACTIVE);
        callInfo.number = PHONE_NUMBER_SECOND;
        callInfo.index = 2;
        callList.calls.push_back(callInfo);
        callList.callSize = 3;
        callInfo.state = static_cast<int32_t>(TelCallState::CALL_STATUS_DISCONNECTED);
        callInfo.number = PHONE_NUMBER_THIRD;
        callInfo.index = 3;
        callList.calls.push_back(callInfo);
        callList.callSize = 0;
        EXPECT_EQ(csControl->ReportCallsData(slotId, callList), TELEPHONY_SUCCESS);
        EXPECT_NE(csControl->Reject(cellularCallInfo), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_NE(csControl->HoldCall(slotId), CALL_ERR_CALL_STATE);
        EXPECT_NE(csControl->UnHoldCall(slotId), CALL_ERR_CALL_STATE);
        EXPECT_NE(csControl->SwitchCall(slotId), CALL_ERR_CALL_STATE);
    }
}

/**
 * @tc.number   cellular_call_CellularCallConnectionCS_0001
 * @tc.name     Test for CellularCallConnectionCS
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CellularCallConnectionCS_0001, Function | MediumTest | Level3)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }

    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        CellularCallConnectionCS csConnection;
        EXPECT_EQ(csConnection.SendDtmfRequest(slotId, '1', 1), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(csConnection.StartDtmfRequest(slotId, '1', 1), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(csConnection.StopDtmfRequest(slotId, 1), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(csConnection.GetCsCallsDataRequest(slotId, 1), CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(csConnection.GetCallFailReasonRequest(slotId), CALL_ERR_RESOURCE_UNAVAILABLE);
        MMICodeUtils utils;
        ASSERT_FALSE(utils.IsNeedExecuteMmi("", false));
        ASSERT_FALSE(utils.ExecuteMmiCode(slotId));
    }
}

/**
 * @tc.number   cellular_call_CellularCallRegister_0001
 * @tc.name     Test for CellularCallRegister
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CellularCallRegister_0001, Function | MediumTest | Level3)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto cellularCallRemote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(cellularCallRemote != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto callRegister = DelayedSingleton<CellularCallRegister>::GetInstance();
    ASSERT_TRUE(callRegister != nullptr);
    CellularCallEventInfo callEvent;
    callRegister->ReportEventResultInfo(callEvent);
    CallWaitResponse waitResponse;
    callRegister->ReportGetWaitingResult(waitResponse);
    callRegister->ReportSetWaitingResult(ERROR_RESULT);
    CallRestrictionResponse restrictionResponse;
    callRegister->ReportGetRestrictionResult(restrictionResponse);
    callRegister->ReportSetRestrictionResult(ERROR_RESULT);
    callRegister->ReportSetBarringPasswordResult(ERROR_RESULT);
    CallTransferResponse transferResponse;
    callRegister->ReportGetTransferResult(transferResponse);
    callRegister->ReportSetTransferResult(ERROR_RESULT);
    ClipResponse clipResponse;
    callRegister->ReportGetClipResult(clipResponse);
    ClirResponse clirResponse;
    callRegister->ReportGetClirResult(clirResponse);
    callRegister->ReportSetClirResult(ERROR_RESULT);
    callRegister->ReportCallRingBackResult(ERROR_RESULT);
    DisconnectedDetails details;
    callRegister->ReportCallFailReason(details);
    MuteControlResponse muteResponse;
    callRegister->ReportSetMuteResult(muteResponse);
    callRegister->ReportGetMuteResult(muteResponse);
    callRegister->ReportInviteToConferenceResult(ERROR_RESULT);
    callRegister->ReportGetCallDataResult(ERROR_RESULT);
    callRegister->ReportStartDtmfResult(ERROR_RESULT);
    callRegister->ReportStopDtmfResult(ERROR_RESULT);
    callRegister->ReportStartRttResult(ERROR_RESULT);
    callRegister->ReportStopRttResult(ERROR_RESULT);
    callRegister->ReportSendUssdResult(ERROR_RESULT);
    SetEccListResponse eccListResponse;
    callRegister->ReportSetEmergencyCallListResponse(eccListResponse);
    MmiCodeInfo mmiInfo;
    callRegister->ReportMmiCodeResult(mmiInfo);
    ASSERT_FALSE(callRegister->IsCallManagerCallBackRegistered());
}

/**
 * @tc.number   cellular_call_CellularCallRegister_0002
 * @tc.name     Test for CellularCallRegister
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CellularCallRegister_0002, Function | MediumTest | Level3)
{
    auto callRegister = DelayedSingleton<CellularCallRegister>::GetInstance();
    CallReportInfo callRepotInfo;
    callRepotInfo.callType = CallType::TYPE_CS;
    callRepotInfo.accountId = INVALID_SLOTID;
    callRepotInfo.state = TelCallState::CALL_STATUS_INCOMING;
    callRepotInfo.callMode = VideoStateType::TYPE_VOICE;
    CallsReportInfo calls;
    calls.slotId = INVALID_SLOTID;
    calls.callVec.push_back(callRepotInfo);
    callRegister->ReportCallsInfo(calls);
    callRegister->ReportSingleCallInfo(callRepotInfo, TelCallState::CALL_STATUS_INCOMING);
    EXPECT_EQ(callRegister->RegisterCallManagerCallBack(nullptr), TELEPHONY_SUCCESS);
    EXPECT_EQ(callRegister->UnRegisterCallManagerCallBack(), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   cellular_call_SupplementRequestCs_0001
 * @tc.name     Test for SupplementRequestCs
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_SupplementRequestCs_0001, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }

    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        SupplementRequestCs request;
        std::string fac = "fac";
        std::string pw = "test";
        int32_t index = 1;
        int32_t mode = 1;
        int32_t classType = 1;
        const char *oldPassword = "oldpwd";
        const char *newPassword = "newpwd";
        bool active = true;
        CallTransferParam param;
        EXPECT_NE(request.GetCallRestrictionRequest(slotId, fac, index), TELEPHONY_SUCCESS);
        EXPECT_NE(request.SetCallRestrictionRequest(slotId, fac, mode, pw, index), TELEPHONY_SUCCESS);
        EXPECT_NE(request.SetBarringPasswordRequest(slotId, fac, index, oldPassword, newPassword), TELEPHONY_SUCCESS);
        EXPECT_NE(request.GetCallWaitingRequest(slotId, index), TELEPHONY_SUCCESS);
        EXPECT_NE(request.SetCallWaitingRequest(slotId, active, classType, index), TELEPHONY_SUCCESS);
        EXPECT_NE(request.GetClipRequest(slotId, index), TELEPHONY_SUCCESS);
        EXPECT_NE(request.GetClirRequest(slotId, index), TELEPHONY_SUCCESS);
        EXPECT_NE(request.SetClirRequest(slotId, mode, index), TELEPHONY_SUCCESS);
        EXPECT_NE(request.GetCallTransferRequest(slotId, mode, index), TELEPHONY_SUCCESS);
        EXPECT_NE(request.SetCallTransferRequest(slotId, param, index), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ConfigRequest_0001
 * @tc.name     Test for ConfigRequest
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_ConfigRequest_0001, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }

    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        ConfigRequest config;
        int32_t mode = 1;
        EXPECT_NE(config.SetDomainPreferenceModeRequest(slotId, mode), TELEPHONY_SUCCESS);
        EXPECT_NE(config.GetDomainPreferenceModeRequest(slotId), TELEPHONY_SUCCESS);
        EXPECT_NE(config.SetMuteRequest(slotId, mode), TELEPHONY_SUCCESS);
        EXPECT_NE(config.GetMuteRequest(slotId), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_CellularCallSupplement_0001
 * @tc.name     Test for CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CellularCallSupplement_0001, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }

    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        MMIData mmiData;
        CellularCallSupplement supplement;
        mmiData.actionString = "";
        supplement.AlterPinPassword(slotId, mmiData);
        supplement.AlterPin2Password(slotId, mmiData);
        supplement.UnlockPuk(slotId, mmiData);
        supplement.UnlockPuk2(slotId, mmiData);
        mmiData.actionString = "test";
        mmiData.serviceInfoA = "infoA";
        mmiData.serviceInfoB = "infoB";
        mmiData.serviceInfoC = "infoC";
        supplement.AlterPinPassword(slotId, mmiData);
        supplement.AlterPin2Password(slotId, mmiData);
        supplement.UnlockPuk(slotId, mmiData);
        supplement.UnlockPuk2(slotId, mmiData);
        mmiData.serviceInfoC = "infoB";
        supplement.AlterPinPassword(slotId, mmiData);
        supplement.AlterPin2Password(slotId, mmiData);
        supplement.UnlockPuk(slotId, mmiData);
        supplement.UnlockPuk2(slotId, mmiData);
        ASSERT_FALSE(supplement.IsVaildPinOrPuk("B", "B"));
        EXPECT_NE(supplement.SendUssd(slotId, "test"), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_CellularCallSupplement_0002
 * @tc.name     Test for CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CellularCallSupplement_0002, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }

    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        CellularCallSupplement supplement;
        supplement.ObtainBarringInstallation("33");
        supplement.ObtainBarringInstallation("331");
        supplement.ObtainBarringInstallation("332");
        supplement.ObtainBarringInstallation("351");
        supplement.ObtainBarringInstallation("35");
        supplement.ObtainBarringInstallation("330");
        supplement.ObtainBarringInstallation("333");
        supplement.ObtainBarringInstallation("353");
        supplement.ObtainBarringInstallation("1000");

        EXPECT_NE(supplement.ObtainServiceCode("10"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainServiceCode("11"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainServiceCode("12"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainServiceCode("13"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainServiceCode("16"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainServiceCode("19"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainServiceCode("20"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainServiceCode("21"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainServiceCode("22"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainServiceCode("24"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainServiceCode("25"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainServiceCode("99"), TELEPHONY_SUCCESS);
        EXPECT_EQ(supplement.ObtainServiceCode("100"), TELEPHONY_SUCCESS);

        EXPECT_EQ(supplement.ObtainCause("21"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainCause("61"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainCause("62"), TELEPHONY_SUCCESS);
        EXPECT_NE(supplement.ObtainCause("67"), TELEPHONY_SUCCESS);
        EXPECT_EQ(supplement.ObtainCause("99"), TELEPHONY_ERROR);
    }
}

/**
 * @tc.number   cellular_call_CellularCallSupplement_0003
 * @tc.name     Test for CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CellularCallSupplement_0003, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }

    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        CellularCallSupplement supplement;
        std::string action = "*";
        std::string number = "";
        CallTransferSettingType type;
        EXPECT_EQ(supplement.ObtainCallTrasferAction(action.c_str(), number, type), TELEPHONY_SUCCESS);
        EXPECT_EQ(supplement.ObtainCallTrasferAction(action.c_str(), PHONE_NUMBER, type), TELEPHONY_SUCCESS);
        action = "#";
        EXPECT_EQ(supplement.ObtainCallTrasferAction(action.c_str(), number, type), TELEPHONY_SUCCESS);
        action = "**";
        EXPECT_EQ(supplement.ObtainCallTrasferAction(action.c_str(), number, type), TELEPHONY_SUCCESS);
        action = "##";
        EXPECT_EQ(supplement.ObtainCallTrasferAction(action.c_str(), number, type), TELEPHONY_SUCCESS);
        action = "*#";
        EXPECT_NE(supplement.ObtainCallTrasferAction(action.c_str(), number, type), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_CellularCallHandler_0001
 * @tc.name     Test for CellularCallHandler
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CellularCallHandler_0001, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }

    EventFwk::MatchingSkills matchingSkills;
    matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
    EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
    CellularCallHandler firstHandler { subscriberInfo };
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        firstHandler.SetSlotId(slotId);
        auto event = AppExecFwk::InnerEvent::Get(0);
        auto rilRadioResponse = std::make_shared<RadioResponseInfo>();
        rilRadioResponse->error = ErrType::ERR_GENERIC_FAILURE;
        firstHandler.CellularCallIncomingStartTrace(static_cast<int32_t>(TelCallState::CALL_STATUS_INCOMING));
        firstHandler.CellularCallIncomingFinishTrace(static_cast<int32_t>(TelCallState::CALL_STATUS_INCOMING));
        firstHandler.GetCsCallsDataResponse(event);
        firstHandler.GetCsCallsDataRequest(event);
        firstHandler.GetMMIResponse(event);
        auto ringbackResponse = std::make_shared<RingbackVoice>();
        ringbackResponse->status = ERROR_RESULT;
        auto ringbackEvent = AppExecFwk::InnerEvent::Get(0, ringbackResponse);
        firstHandler.CallRingBackVoiceResponse(event);
        firstHandler.CallRingBackVoiceResponse(ringbackEvent);
        auto srvccStatus = std::make_shared<SrvccStatus>();
        srvccStatus->status = SrvccState::SRVCC_NONE;
        auto srvccEvent1 = AppExecFwk::InnerEvent::Get(0, srvccStatus);
        firstHandler.UpdateSrvccStateReport(event);
        firstHandler.UpdateSrvccStateReport(srvccEvent1);
        srvccStatus->status = SrvccState::COMPLETED;
        auto srvccEvent2 = AppExecFwk::InnerEvent::Get(0, srvccStatus);
        firstHandler.UpdateSrvccStateReport(srvccEvent2);
        firstHandler.UpdateRsrvccStateReport(event);
        firstHandler.GetCallFailReasonResponse(event);
        firstHandler.GetEmergencyCallListResponse(event);
        firstHandler.ReportEccChanged(event);
        firstHandler.SetEmergencyCallListResponse(event);
        firstHandler.SendUssdResponse(event);
        ASSERT_EQ(firstHandler.GetSlotId(), slotId);
    }
}

/**
 * @tc.number   cellular_call_CellularCallHandler_0002
 * @tc.name     Test for CellularCallHandler
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CellularCallHandler_0002, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }

    EventFwk::MatchingSkills matchingSkills;
    matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
    EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
    CellularCallHandler secondHandler { subscriberInfo };
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        secondHandler.SetSlotId(slotId);
        auto event = AppExecFwk::InnerEvent::Get(0);
        auto rilRadioResponse = std::make_shared<RadioResponseInfo>();
        rilRadioResponse->error = ErrType::ERR_GENERIC_FAILURE;
        secondHandler.CommonResultResponse(event);
        auto rejectEvent = AppExecFwk::InnerEvent::Get(RadioEvent::RADIO_REJECT_CALL, rilRadioResponse);
        secondHandler.CommonResultResponse(rejectEvent);
        auto supplementEvent = AppExecFwk::InnerEvent::Get(RadioEvent::RADIO_CALL_SUPPLEMENT, rilRadioResponse);
        secondHandler.CommonResultResponse(supplementEvent);

        rilRadioResponse->error = ErrType::NONE;
        auto hangupConnectEvent = AppExecFwk::InnerEvent::Get(RadioEvent::RADIO_HANGUP_CONNECT, rilRadioResponse);
        secondHandler.CommonResultResponse(hangupConnectEvent);
        auto acceptEvent = AppExecFwk::InnerEvent::Get(RadioEvent::RADIO_ACCEPT_CALL, rilRadioResponse);
        secondHandler.CommonResultResponse(acceptEvent);
        auto splitNoErrorEvent = AppExecFwk::InnerEvent::Get(RadioEvent::RADIO_SPLIT_CALL, rilRadioResponse);
        secondHandler.CommonResultResponse(splitNoErrorEvent);

        auto ssResult = std::make_shared<SsBaseResult>();
        ssResult->index = INVALID_INDEX;
        ssResult->result = SUCCESS_RESULT;
        auto errorEvent = AppExecFwk::InnerEvent::Get(0, ssResult);
        secondHandler.SetCallRestrictionResponse(event);
        secondHandler.SetCallRestrictionResponse(errorEvent);
        secondHandler.SetBarringPasswordResponse(event);
        secondHandler.SetCallTransferInfoResponse(event);
        secondHandler.SetCallWaitingResponse(event);
        secondHandler.SetClipResponse(event);
        secondHandler.SetClirResponse(event);
        secondHandler.SetColpResponse(event);
        secondHandler.SetColrResponse(event);

        auto responseEvent = AppExecFwk::InnerEvent::Get(0, rilRadioResponse);
        secondHandler.SetMuteResponse(event);
        secondHandler.SetMuteResponse(responseEvent);
        secondHandler.GetMuteResponse(event);
        secondHandler.GetMuteResponse(responseEvent);
        ASSERT_EQ(secondHandler.GetSlotId(), slotId);
    }
}

/**
 * @tc.number   cellular_call_CellularCallHandler_0003
 * @tc.name     Test for CellularCallHandler
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CellularCallHandler_0003, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    EventFwk::MatchingSkills matchingSkills;
    matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
    EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
    CellularCallHandler thirdhandler { subscriberInfo };
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        thirdhandler.SetSlotId(slotId);
        auto event = AppExecFwk::InnerEvent::Get(0);
        auto ussdNoticeResponse = std::make_shared<UssdNoticeInfo>();
        ussdNoticeResponse->m = USSD_MODE_NOTIFY;
        ussdNoticeResponse->str = "tdd test";
        auto successEvent = AppExecFwk::InnerEvent::Get(0, ussdNoticeResponse);
        thirdhandler.UssdNotifyResponse(event);
        thirdhandler.UssdNotifyResponse(successEvent);
        ussdNoticeResponse->str = "";
        auto errorEvent = AppExecFwk::InnerEvent::Get(0, ussdNoticeResponse);
        thirdhandler.UssdNotifyResponse(errorEvent);

        auto ssNoticeResponse = std::make_shared<SsNoticeInfo>();
        ssNoticeResponse->result = ERROR_RESULT;
        auto defaultEvent = AppExecFwk::InnerEvent::Get(0, ssNoticeResponse);
        thirdhandler.SsNotifyResponse(event);
        thirdhandler.SsNotifyResponse(defaultEvent);
        ssNoticeResponse->requestType = SUCCESS_RESULT;
        auto noticeErrorEvent = AppExecFwk::InnerEvent::Get(0, ssNoticeResponse);
        thirdhandler.SsNotifyResponse(noticeErrorEvent);
        ssNoticeResponse->result = SUCCESS_RESULT;
        auto noticeDefaultEvent = AppExecFwk::InnerEvent::Get(0, ssNoticeResponse);
        thirdhandler.SsNotifyResponse(noticeDefaultEvent);
        ssNoticeResponse->serviceType = static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_UNCONDITIONAL);
        auto noticeUnconditinalEvent = AppExecFwk::InnerEvent::Get(0, ssNoticeResponse);
        thirdhandler.SsNotifyResponse(noticeUnconditinalEvent);
        ssNoticeResponse->serviceType = static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_BUSY);
        auto noticeBusyEvent = AppExecFwk::InnerEvent::Get(0, ssNoticeResponse);
        thirdhandler.SsNotifyResponse(noticeBusyEvent);
        ssNoticeResponse->serviceType = static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_NO_REPLY);
        auto noticeNoReplyEvent = AppExecFwk::InnerEvent::Get(0, ssNoticeResponse);
        thirdhandler.SsNotifyResponse(noticeNoReplyEvent);
        ssNoticeResponse->serviceType = static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_NOT_REACHABLE);
        auto noticeNotReachableEvent = AppExecFwk::InnerEvent::Get(0, ssNoticeResponse);
        thirdhandler.SsNotifyResponse(noticeNotReachableEvent);
        ASSERT_EQ(thirdhandler.GetSlotId(), slotId);
    }
}

/**
 * @tc.number   cellular_call_CellularCallHandler_0004
 * @tc.name     Test for CellularCallHandler
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CellularCallHandler_0004, Function | MediumTest | Level3)
{
    EventFwk::MatchingSkills matchingSkills;
    matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
    EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
    CellularCallHandler fourthHandler { subscriberInfo };
    auto callInfoList = std::make_shared<CallInfoList>();
    callInfoList->callSize = 1;
    std::string expectedPhoneNumber = "+861565910xxxx";
    std::string unexpectedPhoneNumber = "00861565910xxxx";
    std::vector<CallInfo> callInfoLists;
    CallInfo callInfo;
    callInfo.number = unexpectedPhoneNumber;
    callInfoLists.push_back(callInfo);
    callInfoList->calls = callInfoLists;
    fourthHandler.ProcessCsPhoneNumber(*callInfoList);
    EXPECT_EQ(callInfoList->calls[0].number, expectedPhoneNumber);
    auto callInfoListFirst = std::make_shared<CallInfoList>();
    callInfoListFirst->callSize = 0;
    callInfoLists.clear();
    callInfo.number = unexpectedPhoneNumber;
    callInfoLists.push_back(callInfo);
    callInfoListFirst->calls = callInfoLists;
    fourthHandler.ProcessCsPhoneNumber(*callInfoListFirst);
    EXPECT_EQ(callInfoListFirst->calls[0].number, unexpectedPhoneNumber);
    auto callInfoListSecond = std::make_shared<CallInfoList>();
    callInfoListSecond->callSize = 1;
    fourthHandler.ProcessCsPhoneNumber(*callInfoListSecond);
    EXPECT_EQ(callInfoListSecond->callSize, 1);
    auto callInfoListThird = std::make_shared<CallInfoList>();
    callInfoListThird->callSize = 1;
    expectedPhoneNumber = "+861565910xxxx";
    unexpectedPhoneNumber = "123";
    callInfoLists.clear();
    callInfo.number = unexpectedPhoneNumber;
    callInfoLists.push_back(callInfo);
    callInfoListThird->calls = callInfoLists;
    fourthHandler.ProcessCsPhoneNumber(*callInfoListThird);
    EXPECT_EQ(callInfoListThird->calls[0].number, unexpectedPhoneNumber);
    callInfoLists.clear();
    unexpectedPhoneNumber = "0861565910xxxx";
    callInfo.number = unexpectedPhoneNumber;
    callInfoLists.push_back(callInfo);
    callInfoListThird->calls = callInfoLists;
    fourthHandler.ProcessCsPhoneNumber(*callInfoListThird);
    EXPECT_EQ(callInfoListThird->calls[0].number, unexpectedPhoneNumber);
}

 /**
 * @tc.number   cellular_call_CellularCallHandler_0005
 * @tc.name     Test for CellularCallHandler
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CellularCallHandler_0005, Function | MediumTest | Level3)
{
    EventFwk::MatchingSkills matchingSkills;
    matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
    EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
    CellularCallHandler fifthHandler { subscriberInfo };
    auto callInfoList = std::make_shared<CallInfoList>();
    callInfoList->callSize = 1;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 9);
    int randomNumber = 0;
    int phonenumberLength = 8;
    for (int i = 0; i < phonenumberLength; i++) {
        randomNumber = randomNumber * 10 + distrib(gen);
    }
    std::string expectedPhoneNumber = "+86156" + std::to_string(randomNumber);
    std::string unexpectedPhoneNumber = "+8686156" + std::to_string(randomNumber);
    CallInfo callInfo;
    callInfo.number = unexpectedPhoneNumber;
    callInfo.type = 145;
    callInfoList->calls.push_back(callInfo);
    fifthHandler.ProcessRedundantCode(*callInfoList);
    EXPECT_EQ(callInfoList->calls[0].number, expectedPhoneNumber);
    callInfoList->calls[0].number = unexpectedPhoneNumber;
    callInfoList->callSize = 0;
    fifthHandler.ProcessRedundantCode(*callInfoList);
    EXPECT_EQ(callInfoList->calls[0].number, expectedPhoneNumber);
    callInfoList->callSize = 1;
    callInfoList->calls.clear();
    fifthHandler.ProcessRedundantCode(*callInfoList);
    EXPECT_EQ(callInfoList->callSize, 1);
    callInfo.number = unexpectedPhoneNumber;
    callInfo.type = 136;
    callInfoList->calls.push_back(callInfo);
    fifthHandler.ProcessRedundantCode(*callInfoList);
    EXPECT_EQ(callInfoList->calls[0].number, unexpectedPhoneNumber);
    unexpectedPhoneNumber = "+561565910xxxx";
    callInfo.number = unexpectedPhoneNumber;
    callInfo.type = 145;
    callInfoList->calls.clear();
    callInfoList->calls.push_back(callInfo);
    fifthHandler.ProcessRedundantCode(*callInfoList);
    EXPECT_EQ(callInfoList->calls[0].number, unexpectedPhoneNumber);
    unexpectedPhoneNumber = "+861565910";
    callInfo.number = unexpectedPhoneNumber;
    callInfoList->calls.clear();
    callInfoList->calls.push_back(callInfo);
    fifthHandler.ProcessRedundantCode(*callInfoList);
    EXPECT_EQ(callInfoList->calls[0].number, unexpectedPhoneNumber);
}

/**
 * @tc.number   cellular_call_TestDump_0001
 * @tc.name     TestDump
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_TestDump_0001, Function | MediumTest | Level3)
{
    std::vector<std::u16string> emptyArgs = {};
    std::vector<std::u16string> args = { u"test", u"test1" };
    EXPECT_GE(DelayedSingleton<CellularCallService>::GetInstance()->Dump(-1, args), 0);
    EXPECT_GE(DelayedSingleton<CellularCallService>::GetInstance()->Dump(0, emptyArgs), 0);
    EXPECT_GE(DelayedSingleton<CellularCallService>::GetInstance()->Dump(0, args), 0);
}

/**
 * @tc.number   cellular_call_ModuleServiceUtils_0001
 * @tc.name     ModuleServiceUtils
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_ModuleServiceUtils_0001, Function | MediumTest | Level3)
{
    ModuleServiceUtils moduleServiceUtils;
    bool airplaneModeOn = false;
    moduleServiceUtils.GetCsRegState(SIM1_SLOTID);
    moduleServiceUtils.GetPsRegState(SIM1_SLOTID);
    moduleServiceUtils.GetRadioState(SIM1_SLOTID);
    moduleServiceUtils.GetNetworkStatus(SIM1_SLOTID);
    moduleServiceUtils.GetIsoCountryCode(SIM1_SLOTID);
    moduleServiceUtils.GetNetworkCountryCode(SIM1_SLOTID);
    moduleServiceUtils.GetImsRegistrationState(SIM1_SLOTID);
    moduleServiceUtils.GetSatelliteStatus();
    moduleServiceUtils.GetSlotInfo();
    moduleServiceUtils.NeedCallImsService();
    moduleServiceUtils.GetImsServiceRemoteObject();
    EXPECT_NE(moduleServiceUtils.GetAirplaneMode(airplaneModeOn), TELEPHONY_SUCCESS);
    EXPECT_NE(moduleServiceUtils.UpdateRadioOn(SIM1_SLOTID), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   cellular_call_CellularCallConfig_0001
 * @tc.name     CellularCallConfig
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, cellular_call_CellularCallConfig_0001, Function | MediumTest | Level3)
{
    CellularCallConfig CellularCallConfig;
    bool isReadyToCall = false;
    bool csType = 0;
    CellularCallConfig.SetReadyToCall(SIM1_SLOTID, isReadyToCall);
    CellularCallCallback cellularCallCallback;
    cellularCallCallback.SetReadyToCall(SIM1_SLOTID, csType, isReadyToCall);
    EXPECT_EQ(CellularCallConfig.IsReadyToCall(SIM1_SLOTID), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   EncapsulationCallReportInfo_0001
 * @tc.name     CsControl
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, EncapsulationCallReportInfo_0001, Function | MediumTest | Level3)
{
    auto csControl = std::make_shared<CSControl>();
    CallInfo callInfo;
    callInfo.number = "";
    callInfo.name = "aaa";
    CallReportInfo reportInfo = csControl->EncapsulationCallReportInfo(SIM1_SLOTID, callInfo);
    EXPECT_EQ("", reportInfo.name);
}

/**
 * @tc.number   EncapsulationCallReportInfo_0002
 * @tc.name     CsControl
 * @tc.desc     Function test
 */
HWTEST_F(Cs2Test, EncapsulationCallReportInfo_0002, Function | MediumTest | Level3)
{
    auto csControl = std::make_shared<CSControl>();
    CallInfo callInfo;
    callInfo.number = "1234567";
    callInfo.name = "aaa";
    CallReportInfo reportInfo = csControl->EncapsulationCallReportInfo(SIM1_SLOTID, callInfo);
    EXPECT_EQ("aaa", reportInfo.name);
}
} // namespace Telephony
} // namespace OHOS
