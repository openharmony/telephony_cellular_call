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

#define private public
#define protected public
#include "cellular_call_config.h"
#include "cellular_call_handler.h"
#include "cellular_call_proxy.h"
#include "cellular_call_register.h"
#include "cellular_call_service.h"
#include "tel_ril_call_parcel.h"
#include "ims_call_callback_proxy.h"
#include "ims_call_callback_stub.h"
#include "ims_call_client.h"
#include "ims_control.h"
#include "ims_error.h"
#include "securec.h"
#include "call_manager_errors.h"
#include "cellular_call_interface.h"
#include "core_service_client.h"
#include "gtest/gtest.h"
#include "ims_core_service_client.h"
#include "iservice_registry.h"
#include "system_ability_definition.h"
#include "token.h"
#include "mock_sim_manager.h"
#include "mock_tel_ril_manager.h"
#include "mock_network_search.h"

namespace OHOS {
namespace Telephony {
using namespace testing;
using namespace testing::ext;
const int32_t SIM1_SLOTID = 0;
const int32_t SIM2_SLOTID = 1;
const std::string PHONE_NUMBER = "0000000";

class Ims1Test : public testing::Test {
public:

    MockTelRilManager *mockTelRilManager = new MockTelRilManager();
    MockNetworkSearch *mockNetworkSearch = new MockNetworkSearch();
    MockSimManager *mockSimManager = new MockSimManager();

    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();

    bool HasSimCard(int32_t slotId)
    {
        bool hasSimCard = false;
        DelayedRefSingleton<CoreServiceClient>::GetInstance().HasSimCard(slotId, hasSimCard);
        return hasSimCard;
    }
    bool CanUseImsService(int32_t slotId, ImsServiceType type)
    {
        ImsRegInfo info;
        CoreManagerInner::GetInstance().GetImsRegStatus(slotId, type, info);
        bool imsReg = info.imsRegState == ImsRegState::IMS_REGISTERED;
        return imsReg;
    }

    int32_t InitCellularCallInfo(int32_t accountId, std::string phonenumber, CellularCallInfo &callInfo)
    {
        callInfo.accountId = accountId;
        callInfo.slotId = accountId;
        callInfo.index = accountId;
        callInfo.callType = CallType::TYPE_IMS;
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

    int32_t TestDialCallByIms(int32_t slotId, std::string code)
    {
        EXPECT_CALL(*mockSimManager, GetSimId(_)).WillRepeatedly(Return(1));
        EXPECT_CALL(*mockNetworkSearch, GetRadioState(_)).WillRepeatedly(Return(1));
        EXPECT_CALL(*mockNetworkSearch, GetImsRegStatus(_, _, _)).WillRepeatedly(Return(1));
        EXPECT_CALL(*mockNetworkSearch, GetPhoneType(_)).WillRepeatedly(Return(PhoneType::PHONE_TYPE_IS_CDMA));
        auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
        telephonyService->Init();
        CellularCallInfo imsCellularCallInfo;
        int32_t ret = TELEPHONY_SUCCESS;
        ret = InitCellularCallInfo(slotId, code, imsCellularCallInfo);
        if (ret != TELEPHONY_SUCCESS) {
            return ret;
        }
        // open ims, make this time use ims to test
        ret = telephonyService->SetImsSwitchStatus(slotId, true);
        if (ret != TELEPHONY_SUCCESS) {
            return ret;
        }
        ret = telephonyService->Dial(imsCellularCallInfo);
        return ret;
    };
};

void Ims1Test::SetUpTestCase(void)
{
    // step 3: Set Up Test Case
}

void Ims1Test::TearDownTestCase(void)
{
    // step 3: Tear Down Test Case
}

void Ims1Test::SetUp(void)
{
    std::shared_ptr<MockTelRilManager> mockTelRilManagerPtr(mockTelRilManager);
    std::shared_ptr<MockNetworkSearch> mockNetworkSearchPtr(mockNetworkSearch);
    std::shared_ptr<MockSimManager> mockSimManagerPtr(mockSimManager);
    CoreManagerInner::GetInstance().OnInit(mockNetworkSearchPtr, mockSimManagerPtr, mockTelRilManagerPtr);
}

void Ims1Test::TearDown(void)
{
    // step 3: input testcase teardown step
}
/**
 * @tc.number   cellular_call_ims_test_001
 * @tc.name     Test the corresponding functions by entering commands, such as 300 -- SetCallPreferenceMode, 301 --
 *              GetCallPreferenceMode, etc
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_ims_test_001, Function | MediumTest | Level0)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    std::cout << "HWTEST_F cellular_call_ims_test_001";
}

/**
 * @tc.number   cellular_call_DialCall_0001
 * @tc.name     Test for SetClip function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*30#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*30#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0002
 * @tc.name     Test for SetClip function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0002, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "#30#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "#30#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0003
 * @tc.name     Test for getClip function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0003, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*#30#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*#30#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0004
 * @tc.name     Test for SetClir function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0004, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*31#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*31#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0005
 * @tc.name     Test for SetClir function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0005, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "#31#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "#31#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0006
 * @tc.name     Test for GetClir function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0006, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*#31#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*#31#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0007
 * @tc.name     Test for SetCallTransfer function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0007, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*21#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*21#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0008
 * @tc.name     Test for SetCallTransfer function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0008, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "#21#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "#21#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0009
 * @tc.name     Test for GetCallTransfer function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0009, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*#21#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*#21#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0010
 * @tc.name     Test for SetCallRestriction function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0010, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*33#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*33#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0011
 * @tc.name     Test for SetCallRestriction function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0011, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "#33#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "#33#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0012
 * @tc.name     Test for GetCallRestriction function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0012, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*#33#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*#33#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0013
 * @tc.name     Test for SetCallWaiting function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0013, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*43#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*43#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0014
 * @tc.name     Test for SetCallWaiting function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0014, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "#43#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "#43#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0015
 * @tc.name     Test for GetCallWaiting function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_DialCall_0015, Function | MediumTest | Level2)
{
    AccessToken token;
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*#43#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
        ret = TestDialCallByIms(SIM1_SLOTID, "*#4@3#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*#43#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
        ret = TestDialCallByIms(SIM2_SLOTID, "*#4@3#");
        EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_HangUpCall_0001
 * @tc.name     Test for HangUp function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_HangUpCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HangUp(callInfo, CallSupplementType::TYPE_DEFAULT);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
        ret = telephonyService->HangUp(callInfo, CallSupplementType::TYPE_HANG_UP_ACTIVE);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM2_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HangUp(callInfo, CallSupplementType::TYPE_DEFAULT);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
        ret = telephonyService->HangUp(callInfo, CallSupplementType::TYPE_HANG_UP_ACTIVE);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_AnswerCall_0001
 * @tc.name     Test for answer function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_AnswerCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Answer(callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM2_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Answer(callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
}

/**
 * @tc.number   cellular_call_RejectCall_0001
 * @tc.name     Test for reject function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_RejectCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Reject(callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM2_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Reject(callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
}

/**
 * @tc.number   cellular_call_HoldCall_0001
 * @tc.name     Test for hold call function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_HoldCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HoldCall(callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM2_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HoldCall(callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_UnHoldCall_0001
 * @tc.name     Test for unhold call function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_UnHoldCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->UnHoldCall(callInfo);
        EXPECT_NE(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM2_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->UnHoldCall(callInfo);
        EXPECT_NE(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_SwitchCall_0001
 * @tc.name     Test for switch call function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_SwitchCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SwitchCall(callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM2_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SwitchCall(callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_CombineConference_0001
 * @tc.name     Test for combineConference function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_CombineConference_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->CombineConference(callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM2_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->CombineConference(callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_SeparateConference_0001
 * @tc.name     Test for separateConference function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_SeparateConference_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SeparateConference(callInfo);
        EXPECT_EQ(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM2_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SeparateConference(callInfo);
        EXPECT_EQ(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_KickOutFromConference_0001
 * @tc.name     Test for KickOutFromConference function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_KickOutFromConference_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->KickOutFromConference(callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM2_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->KickOutFromConference(callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_StartDtmf_0001
 * @tc.name     Test for startDtmf function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_StartDtmf_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->StartDtmf(code, callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM2_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->StartDtmf(code, callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
}

/**
 * @tc.number   cellular_call_StopDtmf_0001
 * @tc.name     Test for stopDtmf function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_StopDtmf_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->StopDtmf(callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM2_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->StopDtmf(callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
}

/**
 * @tc.number   cellular_call_SendDtmf_0001
 * @tc.name     Test for sendDtmf function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_SendDtmf_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->SendDtmf(code, callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        telephonyService->SetImsControl(SIM2_SLOTID, imsControl);
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->SendDtmf(code, callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
}

/**
 * @tc.number   cellular_call_CanSetCallTransferTime_0001
 * @tc.name     Test for CanSetCallTransferTime function by ims
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_CanSetCallTransferTime_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        bool result;
        int32_t ret = telephonyService->CanSetCallTransferTime(SIM1_SLOTID, result);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        telephonyService->SetImsControl(SIM2_SLOTID, imsControl);
        bool result;
        int32_t ret = telephonyService->CanSetCallTransferTime(SIM2_SLOTID, result);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}


/**
 * @tc.number   cellular_call_SetVoNRState_0001
 * @tc.name     Test for SetVoNRState function
 * @tc.desc     Function test
 */
HWTEST_F(Ims1Test, cellular_call_SetVoNRState_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto telephonyService = DelayedSingleton<CellularCallService>::GetInstance();
    telephonyService->Init();
    std::shared_ptr<IMSControl> imsControl = std::make_shared<IMSControl>();
    ASSERT_NE(imsControl, nullptr);
    if (HasSimCard(SIM1_SLOTID)) {
        telephonyService->SetImsControl(SIM1_SLOTID, imsControl);
        int32_t ret = telephonyService->SetVoNRState(SIM1_SLOTID, 1);
        EXPECT_EQ(ret, TELEPHONY_ERR_FAIL);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        int32_t ret = telephonyService->SetVoNRState(SIM2_SLOTID, 1);
        EXPECT_EQ(ret, TELEPHONY_ERR_FAIL);
    }

#ifdef SUPPORT_RTT_CALL
    int32_t callId = 0;
    int32_t ret = -100;
    ImsRTTCallMode mode = ImsRTTCallMode::LOCAL_REQUEST_DOWNGRADE;
    EXPECT_NE(imsControl->UpdateImsRttCallMode(SIM1_SLOTID, callId, mode), ret);
#endif
}
} // namespace Telephony
} // namespace OHOS
