/*
 * Copyright (C) 2021-2022 Huawei Device Co., Ltd.
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

#include "ims_test.h"

#define private public
#define protected public
#include "cellular_call_config.h"
#include "cellular_call_handler.h"
#include "cellular_call_proxy.h"
#include "cellular_call_register.h"
#include "hril_call_parcel.h"
#include "ims_call_callback_proxy.h"
#include "ims_call_callback_stub.h"
#include "ims_call_client.h"
#include "ims_control.h"
#include "ims_error.h"
#include "securec.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
const int32_t SIM1_SLOTID = 0;
const int32_t SIM2_SLOTID = 1;
const int32_t INVALID_SLOTID = -1;
const int32_t INVALID_HANG_UP_TYPE = -1;
const int32_t RESULT = 1;
const std::string PHONE_NUMBER = "0000000";
const std::string PHONE_NUMBER_SECOND = "1111111";
const std::string PHONE_NUMBER_THIRD = "2222222";
const std::string PHONE_NUMBER_FOUR = "3333333";
const int32_t CELLULAR_CALL_SUCCESS = 0;
const int32_t DEFAULT_INDEX = 1;

void ImsTest::SetUpTestCase(void)
{
    // step 3: Set Up Test Case
}

void ImsTest::TearDownTestCase(void)
{
    // step 3: Tear Down Test Case
}

void ImsTest::SetUp(void)
{
    // step 3: input testcase setup step
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_DOMAIN_PREFERENCE_MODE)] =
        &ImsTest::SetDomainPreferenceMode;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::GET_DOMAIN_PREFERENCE_MODE)] =
        &ImsTest::GetDomainPreferenceMode;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_IMS_SWITCH_STATUS)] =
        &ImsTest::SetImsSwitchStatus;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::GET_IMS_SWITCH_STATUS)] =
        &ImsTest::GetImsSwitchStatus;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_IMS_CONFIG_STRING)] =
        &ImsTest::SetImsConfigString;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_IMS_CONFIG_INT)] =
        &ImsTest::SetImsConfigInt;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::GET_IMS_CONFIG)] =
        &ImsTest::GetImsConfig;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_IMS_FEATURE)] =
        &ImsTest::SetImsFeatureValue;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::GET_IMS_FEATURE)] =
        &ImsTest::GetImsFeatureValue;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::CTRL_CAMERA)] = &ImsTest::CtrlCamera;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_PREVIEW_WINDOW)] =
        &ImsTest::SetPreviewWindow;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_DISPLAY_WINDOW)] =
        &ImsTest::SetDisplayWindow;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_CAMERA_ZOOM)] =
        &ImsTest::SetCameraZoom;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_PAUSE_IMAGE)] =
        &ImsTest::SetPauseImage;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_DEVICE_DIRECTION)] =
        &ImsTest::SetDeviceDirection;
}

void ImsTest::TearDown(void)
{
    // step 3: input testcase teardown step
}

int32_t ImsTest::SetDomainPreferenceMode(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetDomainPreferenceMode entry." << std::endl;
    std::cout << "please enter the need mode:(1 - 4)";
    int32_t mode;
    std::cin >> mode;
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    return telephonyService->SetDomainPreferenceMode(slotId, mode);
}

int32_t ImsTest::GetDomainPreferenceMode(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetDomainPreferenceMode entry." << std::endl;
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    return telephonyService->GetDomainPreferenceMode(slotId);
}

int32_t ImsTest::SetImsSwitchStatus(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetImsSwitchStatus entry." << std::endl;
    std::cout << "please enter the switch state:";
    bool active;
    std::cin >> active;
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    return telephonyService->SetImsSwitchStatus(slotId, active);
}

int32_t ImsTest::GetImsSwitchStatus(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetImsSwitchStatus entry." << std::endl;
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    bool enabled;
    return telephonyService->GetImsSwitchStatus(slotId, enabled);
}

int32_t ImsTest::SetImsConfigString(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetImsConfigString entry." << std::endl;
    std::cout << "please enter the item id:";
    int32_t item = 0;
    std::cin >> item;
    std::cout << "please enter the item value:";
    std::string value;
    std::cin >> value;
    int32_t slotId = 0;
    return telephonyService->SetImsConfig(slotId, static_cast<ImsConfigItem>(item), value);
}

int32_t ImsTest::SetImsConfigInt(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetImsConfigInt entry." << std::endl;
    std::cout << "please enter the item id:";
    int32_t item = 0;
    std::cin >> item;
    std::cout << "please enter the item value:";
    int32_t value = 0;
    std::cin >> value;
    int32_t slotId = 0;
    return telephonyService->SetImsConfig(slotId, static_cast<ImsConfigItem>(item), value);
}

int32_t ImsTest::GetImsConfig(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetImsConfig entry." << std::endl;
    std::cout << "please enter the item id:";
    int32_t item = 0;
    std::cin >> item;
    int32_t slotId = 0;
    return telephonyService->GetImsConfig(slotId, static_cast<ImsConfigItem>(item));
}

int32_t ImsTest::SetImsFeatureValue(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetImsFeatureValue entry." << std::endl;
    std::cout << "please enter the feature type:";
    int32_t type = 0;
    std::cin >> type;
    std::cout << "please enter the feature value:";
    int32_t value = 0;
    std::cin >> value;
    int32_t slotId = 0;
    return telephonyService->SetImsFeatureValue(slotId, static_cast<FeatureType>(type), value);
}

int32_t ImsTest::GetImsFeatureValue(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetImsFeatureValue entry." << std::endl;
    std::cout << "please enter the feature type:";
    int32_t type = 0;
    std::cin >> type;
    int32_t slotId = 0;
    return telephonyService->GetImsFeatureValue(slotId, static_cast<FeatureType>(type));
}

int32_t ImsTest::CtrlCamera(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test CtrlCamera entry." << std::endl;
    std::u16string cameraId = u"cameraId";
    int32_t callingUid = 0;
    int32_t callingPid = 0;
    return telephonyService->CtrlCamera(cameraId, callingUid, callingPid);
}

int32_t ImsTest::SetPreviewWindow(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetPreviewWindow entry." << std::endl;
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    int32_t width = 0;
    int32_t height = 0;
    return telephonyService->SetPreviewWindow(x, y, z, width, height);
}

int32_t ImsTest::SetDisplayWindow(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetDisplayWindow entry." << std::endl;
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    int32_t width = 0;
    int32_t height = 0;
    return telephonyService->SetDisplayWindow(x, y, z, width, height);
}

int32_t ImsTest::SetCameraZoom(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetCameraZoom entry." << std::endl;
    float zoomRatio = 1.0;
    return telephonyService->SetCameraZoom(zoomRatio);
}

int32_t ImsTest::SetPauseImage(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetPauseImage entry." << std::endl;
    std::u16string path = u"path";
    return telephonyService->SetPauseImage(path);
}

int32_t ImsTest::SetDeviceDirection(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetDeviceDirection entry." << std::endl;
    int32_t rotation = 0;
    return telephonyService->SetDeviceDirection(rotation);
}

int32_t ImsTest::InputNumForInterface(const sptr<CellularCallInterface> &telephonyService) const
{
    int32_t ret = -1;
    bool loopFlag = true;
    int32_t InputNum = 0;
    int32_t returnNum = 1000; // end loop variable value
    while (loopFlag) {
        std::cout << "\n**********Unit Test Start**********\n"
                     "Usage: please input a cmd num:\n"
                     "300:SetCallPreferenceMode\n"
                     "301:GetCallPreferenceMode\n"
                     "302:SetImsSwitchStatus\n"
                     "303:GetImsSwitchStatus\n"
                     "304:SetImsConfigString\n"
                     "305:SetImsConfigInt\n"
                     "306:GetImsConfig\n"
                     "307:SetImsFeatureValue\n"
                     "308:GetImsFeatureValue\n"
                     "400:CtrlCamera\n"
                     "401:SetPreviewWindow\n"
                     "402:SetDisplayWindow\n"
                     "403:SetCameraZoom\n"
                     "404:SetPauseImage\n"
                     "405:SetDeviceDirection\n"
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

/**
 * @tc.number   cellular_call_ims_test_001
 * @tc.name     Test the corresponding functions by entering commands, such as 300 -- SetCallPreferenceMode, 301 --
 *              GetCallPreferenceMode, etc
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ims_test_001, Function | MediumTest | Level0)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    std::cout << "HWTEST_F cellular_call_ims_test_001";
}

/**
 * @tc.number   cellular_call_ims_test_002
 * @tc.name     Test the corresponding functions by entering commands, such as 300 -- SetCallPreferenceMode, 301 --
 *              GetCallPreferenceMode, etc
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ims_test_002, Function | MediumTest | Level1)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    std::cout << "HWTEST_F cellular_call_ims_test_002";
}

/**
 * @tc.number   cellular_call_DialCall_0001
 * @tc.name     Test for SetClip function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0001, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*30#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*30#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0002
 * @tc.name     Test for SetClip function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0002, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "#30#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "#30#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0003
 * @tc.name     Test for getClip function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0003, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*#30#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*#30#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0004
 * @tc.name     Test for SetClir function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0004, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*31#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*31#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0005
 * @tc.name     Test for SetClir function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0005, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "#31#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "#31#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0006
 * @tc.name     Test for GetClir function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0006, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*#31#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*#31#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0007
 * @tc.name     Test for SetCallTransfer function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0007, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*21#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*21#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0008
 * @tc.name     Test for SetCallTransfer function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0008, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "#21#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "#21#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0009
 * @tc.name     Test for GetCallTransfer function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0009, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*#21#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*#21#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0010
 * @tc.name     Test for SetCallRestriction function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0010, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*33#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*33#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0011
 * @tc.name     Test for SetCallRestriction function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0011, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "#33#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "#33#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0012
 * @tc.name     Test for GetCallRestriction function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0012, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*#33#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*#33#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0013
 * @tc.name     Test for SetCallWaiting function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0013, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*43#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*43#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0014
 * @tc.name     Test for SetCallWaiting function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0014, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "#43#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "#43#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_DialCall_0015
 * @tc.name     Test for GetCallWaiting function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_DialCall_0015, Function | MediumTest | Level2)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM1_SLOTID, "*#43#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = TestDialCallByIms(SIM1_SLOTID, "*#4@3#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_UT)) {
        int32_t ret = TestDialCallByIms(SIM2_SLOTID, "*#43#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = TestDialCallByIms(SIM2_SLOTID, "*#4@3#");
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_HangUpCall_0001
 * @tc.name     Test for HangUp function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_HangUpCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HangUp(callInfo, CallSupplementType::TYPE_DEFAULT);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
        ret = telephonyService->HangUp(callInfo, CallSupplementType::TYPE_HANG_UP_ACTIVE);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
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
HWTEST_F(ImsTest, cellular_call_AnswerCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Answer(callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
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
HWTEST_F(ImsTest, cellular_call_RejectCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->Reject(callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
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
HWTEST_F(ImsTest, cellular_call_HoldCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HoldCall(callInfo);
        EXPECT_EQ(ret, TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->HoldCall(callInfo);
        EXPECT_EQ(ret, TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
    }
}

/**
 * @tc.number   cellular_call_UnHoldCall_0001
 * @tc.name     Test for unhold call function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_UnHoldCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->UnHoldCall(callInfo);
        EXPECT_EQ(ret, TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->UnHoldCall(callInfo);
        EXPECT_EQ(ret, TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
    }
}

/**
 * @tc.number   cellular_call_SwitchCall_0001
 * @tc.name     Test for switch call function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_SwitchCall_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SwitchCall(callInfo);
        EXPECT_EQ(ret, TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SwitchCall(callInfo);
        EXPECT_EQ(ret, TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
    }
}

/**
 * @tc.number   cellular_call_CombineConference_0001
 * @tc.name     Test for combineConference function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_CombineConference_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->CombineConference(callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
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
HWTEST_F(ImsTest, cellular_call_SeparateConference_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SeparateConference(callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM2_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->SeparateConference(callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_StartDtmf_0001
 * @tc.name     Test for startDtmf function by ims
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_StartDtmf_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->StartDtmf(code, callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
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
HWTEST_F(ImsTest, cellular_call_StopDtmf_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        ret = telephonyService->StopDtmf(callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
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
HWTEST_F(ImsTest, cellular_call_SendDtmf_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_VOICE)) {
        CellularCallInfo callInfo;
        int32_t ret = InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, callInfo);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
        char code = '1';
        ret = telephonyService->SendDtmf(code, callInfo);
        EXPECT_EQ(ret, CALL_ERR_CALL_CONNECTION_NOT_EXIST);
    }
    if (HasSimCard(SIM2_SLOTID) && CanUseImsService(SIM2_SLOTID, ImsServiceType::TYPE_VOICE)) {
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
HWTEST_F(ImsTest, cellular_call_CanSetCallTransferTime_0001, Function | MediumTest | Level2)
{
    AccessToken token;
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    ASSERT_TRUE(telephonyService != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    if (HasSimCard(SIM1_SLOTID) && CanUseImsService(SIM1_SLOTID, ImsServiceType::TYPE_UT)) {
        bool result;
        int32_t ret = telephonyService->CanSetCallTransferTime(SIM1_SLOTID, result);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
    if (HasSimCard(SIM2_SLOTID)) {
        bool result;
        int32_t ret = telephonyService->CanSetCallTransferTime(SIM2_SLOTID, result);
        EXPECT_EQ(ret, TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsControl_0001
 * @tc.name     Test for ImsControl
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsControl_0001, Function | MediumTest | Level3)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto imsControl = std::make_shared<IMSControl>();
    CellularCallInfo cellularCallInfo;
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId) || !CanUseImsService(slotId, ImsServiceType::TYPE_VOICE)) {
            continue;
        }
        EXPECT_EQ(imsControl->Answer(cellularCallInfo), TELEPHONY_ERROR);
        EXPECT_EQ(imsControl->Reject(cellularCallInfo), TELEPHONY_ERROR);
        EXPECT_EQ(imsControl->UpdateImsCallMode(cellularCallInfo, ImsCallMode::CALL_MODE_AUDIO_ONLY),
            CALL_ERR_CALL_CONNECTION_NOT_EXIST);
        EXPECT_EQ(InitCellularCallInfo(slotId, PHONE_NUMBER, cellularCallInfo), TELEPHONY_SUCCESS);
        bool enabled = false;
        EXPECT_EQ(imsControl->Dial(cellularCallInfo, enabled), CALL_ERR_GET_RADIO_STATE_FAILED);
        CLIRMode mode = CLIRMode::DEFAULT;
        EXPECT_EQ(imsControl->DialJudgment(slotId, PHONE_NUMBER_SECOND, mode, 0), TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
        EXPECT_EQ(imsControl->DialJudgment(slotId, PHONE_NUMBER_THIRD, mode, 0), TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
        EXPECT_EQ(InitCellularCallInfo(slotId, PHONE_NUMBER_SECOND, cellularCallInfo), TELEPHONY_SUCCESS);
        EXPECT_EQ(imsControl->Answer(cellularCallInfo), CALL_ERR_CALL_STATE);
        EXPECT_EQ(imsControl->UpdateImsCallMode(cellularCallInfo, ImsCallMode::CALL_MODE_AUDIO_ONLY), TELEPHONY_ERROR);
        EXPECT_EQ(InitCellularCallInfo(slotId, PHONE_NUMBER_THIRD, cellularCallInfo), TELEPHONY_SUCCESS);
        EXPECT_EQ(imsControl->Answer(cellularCallInfo), TELEPHONY_ERROR);
        EXPECT_EQ(InitCellularCallInfo(slotId, PHONE_NUMBER_FOUR, cellularCallInfo), TELEPHONY_SUCCESS);
        EXPECT_EQ(imsControl->Answer(cellularCallInfo), CALL_ERR_CALL_STATE);
        EXPECT_EQ(imsControl->Reject(cellularCallInfo), CALL_ERR_CALL_STATE);
        EXPECT_EQ(imsControl->HoldCall(slotId), CALL_ERR_CALL_STATE);
        std::vector<std::string> numberList;
        EXPECT_EQ(imsControl->KickOutFromConference(slotId, numberList), TELEPHONY_ERROR);
        EXPECT_EQ(imsControl->InviteToConference(slotId, numberList), TELEPHONY_ERROR);
        EXPECT_EQ(imsControl->StartRtt(slotId, PHONE_NUMBER), TELEPHONY_ERROR);
        EXPECT_EQ(imsControl->StopRtt(slotId), TELEPHONY_ERROR);
        EXPECT_EQ(
            imsControl->UpdateImsCallMode(cellularCallInfo, ImsCallMode::CALL_MODE_AUDIO_ONLY), CALL_ERR_CALL_STATE);
        EXPECT_EQ(imsControl->HangUp(cellularCallInfo, CallSupplementType::TYPE_DEFAULT), TELEPHONY_ERROR);
        EXPECT_EQ(imsControl->HangUp(cellularCallInfo, CallSupplementType::TYPE_HANG_UP_ACTIVE),
            CALL_ERR_RESOURCE_UNAVAILABLE);
        EXPECT_EQ(imsControl->HangUp(cellularCallInfo, CallSupplementType::TYPE_HANG_UP_ALL), TELEPHONY_ERROR);
        EXPECT_EQ(imsControl->HangUp(cellularCallInfo, static_cast<CallSupplementType>(INVALID_HANG_UP_TYPE)),
            TELEPHONY_ERR_ARGUMENT_INVALID);
    }
}

/**
 * @tc.number   cellular_call_ImsControl_0002
 * @tc.name     Test for ImsControl
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsControl_0002, Function | MediumTest | Level3)
{
    auto imsControl = std::make_shared<IMSControl>();
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId) || !CanUseImsService(slotId, ImsServiceType::TYPE_VOICE)) {
            continue;
        }
        ImsCurrentCallList callList;
        callList.callSize = 0;
        CallInfoList callInfoList;
        EXPECT_EQ(imsControl->ReportCallsData(slotId, callInfoList), TELEPHONY_ERROR);
        EXPECT_EQ(imsControl->ReportImsCallsData(slotId, callList), TELEPHONY_ERROR);
        ImsCurrentCall callInfo;
        callList.callSize = 1;
        callInfo.number = PHONE_NUMBER;
        callInfo.index = 1;
        callInfo.state = static_cast<int32_t>(TelCallState::CALL_STATUS_INCOMING);
        callList.calls.push_back(callInfo);
        EXPECT_EQ(imsControl->ReportImsCallsData(slotId, callList), TELEPHONY_SUCCESS);
        EXPECT_EQ(imsControl->HangUpAllConnection(slotId), TELEPHONY_ERROR);
        callList.callSize = 2;
        callInfo.index = 2;
        callInfo.state = static_cast<int32_t>(TelCallState::CALL_STATUS_ACTIVE);
        callInfo.number = PHONE_NUMBER_SECOND;
        callList.calls.push_back(callInfo);
        callList.callSize = 3;
        callInfo.index = 3;
        callInfo.state = static_cast<int32_t>(TelCallState::CALL_STATUS_WAITING);
        callInfo.number = PHONE_NUMBER_THIRD;
        callList.calls.push_back(callInfo);
        callList.callSize = 4;
        callInfo.index = 4;
        callInfo.state = static_cast<int32_t>(TelCallState::CALL_STATUS_DISCONNECTED);
        callInfo.number = PHONE_NUMBER_FOUR;
        callList.calls.push_back(callInfo);
        EXPECT_EQ(imsControl->ReportImsCallsData(slotId, callList), TELEPHONY_SUCCESS);
        callList.callSize = 0;
        EXPECT_EQ(imsControl->ReportImsCallsData(slotId, callList), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_CellularCallConnectionIMS_0001
 * @tc.name     Test for CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_CellularCallConnectionIMS_0001, Function | MediumTest | Level3)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId) || !CanUseImsService(slotId, ImsServiceType::TYPE_VOICE)) {
            continue;
        }
        CellularCallConnectionIMS imsConnection;
        EXPECT_EQ(imsConnection.SendDtmfRequest(slotId, '1', 1), TELEPHONY_ERROR);
        EXPECT_EQ(imsConnection.StartDtmfRequest(slotId, '1', 1), TELEPHONY_ERROR);
        EXPECT_EQ(imsConnection.StopDtmfRequest(slotId, 1), TELEPHONY_ERROR);
        EXPECT_EQ(imsConnection.GetImsCallsDataRequest(slotId, 1), TELEPHONY_ERROR);
        EXPECT_EQ(imsConnection.GetCallFailReasonRequest(slotId), TELEPHONY_ERROR);
    }
}

/**
 * @tc.number   cellular_call_CellularCallRegister_0001
 * @tc.name     Test for CellularCallRegister
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_CellularCallRegister_0001, Function | MediumTest | Level3)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    ASSERT_TRUE(systemAbilityMgr != nullptr);
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    ASSERT_TRUE(remote != nullptr);
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    auto callRegister = DelayedSingleton<CellularCallRegister>::GetInstance();
    ASSERT_TRUE(callRegister != nullptr);
    GetImsConfigResponse imsConfigResponse;
    callRegister->ReportGetImsConfigResult(imsConfigResponse);
    callRegister->ReportSetImsConfigResult(RESULT);
    GetImsFeatureValueResponse imsFeatureValueResponse;
    callRegister->ReportGetImsFeatureResult(imsFeatureValueResponse);
    callRegister->ReportSetImsFeatureResult(RESULT);
    callRegister->ReportUpdateCallMediaModeResult(RESULT);
}

/**
 * @tc.number   cellular_call_CellularCallConfig_0001
 * @tc.name     Test for CellularCallConfig
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_CellularCallConfig_0001, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }

    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        CellularCallConfig config;
        ASSERT_TRUE(config.GetImsSwitchOnByDefaultConfig(INVALID_SLOTID));
        ASSERT_TRUE(config.GetImsSwitchOnByDefaultConfig(slotId));
        ASSERT_FALSE(config.GethideImsSwitchConfig(INVALID_SLOTID));
        ASSERT_FALSE(config.GethideImsSwitchConfig(slotId));
        ASSERT_FALSE(config.GetvolteSupportedConfig(INVALID_SLOTID));
        ASSERT_FALSE(config.GetvolteSupportedConfig(slotId));
        config.GetNrModeSupportedListConfig(INVALID_SLOTID);
        config.GetNrModeSupportedListConfig(slotId);
        ASSERT_FALSE(config.GetVolteProvisioningSupportedConfig(INVALID_SLOTID));
        ASSERT_FALSE(config.GetVolteProvisioningSupportedConfig(slotId));
        ASSERT_FALSE(config.GetSsOverUtSupportedConfig(INVALID_SLOTID));
        ASSERT_FALSE(config.GetSsOverUtSupportedConfig(slotId));
        ASSERT_FALSE(config.GetImsGbaRequiredConfig(INVALID_SLOTID));
        ASSERT_FALSE(config.GetImsGbaRequiredConfig(slotId));
        ASSERT_FALSE(config.GetUtProvisioningSupportedConfig(INVALID_SLOTID));
        ASSERT_FALSE(config.GetUtProvisioningSupportedConfig(slotId));
        ASSERT_TRUE(config.GetImsPreferForEmergencyConfig(INVALID_SLOTID));
        ASSERT_TRUE(config.GetImsPreferForEmergencyConfig(slotId));
        config.GetCallWaitingServiceClassConfig(INVALID_SLOTID);
        config.GetCallWaitingServiceClassConfig(slotId);
        config.GetImsCallDisconnectResoninfoMappingConfig(INVALID_SLOTID);
        config.GetImsCallDisconnectResoninfoMappingConfig(slotId);
        ASSERT_FALSE(config.GetForceVolteSwitchOnConfig(INVALID_SLOTID));
        ASSERT_FALSE(config.GetForceVolteSwitchOnConfig(slotId));
    }
}

/**
 * @tc.number   cellular_call_CellularCallHandler_0001
 * @tc.name     Test for CellularCallHandler
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_CellularCallHandler_0001, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }

    std::shared_ptr<AppExecFwk::EventRunner> runner = AppExecFwk::EventRunner::Create("ims_test");
    EventFwk::MatchingSkills matchingSkills;
    matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
    EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
    CellularCallHandler handler { runner, subscriberInfo };
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        handler.SetSlotId(slotId);
        auto event = AppExecFwk::InnerEvent::Get(0);
        handler.GetImsCallsDataResponse(event);
        handler.GetImsCallsDataRequest(event);
        auto rilRadioResponse = std::make_shared<HRilRadioResponseInfo>();
        rilRadioResponse->error = HRilErrType::HRIL_ERR_GENERIC_FAILURE;
        auto responseEvent = AppExecFwk::InnerEvent::Get(0, rilRadioResponse);
        handler.SetDomainPreferenceModeResponse(responseEvent);
        handler.GetDomainPreferenceModeResponse(event);
        handler.SetDomainPreferenceModeResponse(event);
        ASSERT_EQ(handler.GetSlotId(), slotId);
    }
}

/**
 * @tc.number   cellular_call_ImsCallClient_0001
 * @tc.name     test for ImsCallClient
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsCallClient_0001, Function | MediumTest | Level3)
{
    ImsCallClient::SystemAbilityListener listen;
    int32_t systemAbilityId = 1;
    std::string deviceId = "123";
    listen.OnAddSystemAbility(systemAbilityId, deviceId);
    listen.OnRemoveSystemAbility(systemAbilityId, deviceId);
    listen.OnAddSystemAbility(COMMON_EVENT_SERVICE_ID, deviceId);
    listen.OnRemoveSystemAbility(COMMON_EVENT_SERVICE_ID, deviceId);
}

/**
 * @tc.number   cellular_call_ImsCallCallbackProxy_0001
 * @tc.name     Test for ImsCallCallbackProxy
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsCallCallbackProxy_0001, Function | MediumTest | Level3)
{
    const sptr<ImsCallCallbackInterface> imsCallCallback_ = (std::make_unique<ImsCallCallbackStub>()).release();
    auto callCallbackProxy = iface_cast<ImsCallCallbackInterface>(imsCallCallback_->AsObject().GetRefPtr());
    ASSERT_TRUE(callCallbackProxy != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        EventFwk::MatchingSkills matchingSkills;
        matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
        EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
        std::shared_ptr<AppExecFwk::EventRunner> eventLoop = AppExecFwk::EventRunner::Create("Imstest");
        auto handler = std::make_shared<CellularCallHandler>(eventLoop, subscriberInfo);
        handler->SetSlotId(slotId);
        handler->RegisterImsCallCallbackHandler();
        HRilRadioResponseInfo rilRadioResponse;
        rilRadioResponse.error = HRilErrType::HRIL_ERR_GENERIC_FAILURE;
        ASSERT_EQ(callCallbackProxy->DialResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->HangUpResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->RejectWithReasonResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->AnswerResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->HoldCallResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->UnHoldCallResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SwitchCallResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->StartDtmfResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SendDtmfResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->StopDtmfResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetImsSwitchResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->GetImsSwitchResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->GetImsCallsDataResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->CallStateChangeReport(slotId), TELEPHONY_SUCCESS);
        ImsCurrentCallList imsCallList;
        imsCallList.callSize = 0;
        ASSERT_EQ(callCallbackProxy->GetImsCallsDataResponse(slotId, imsCallList), TELEPHONY_SUCCESS);
        DisconnectedDetails details;
        ASSERT_EQ(callCallbackProxy->LastCallFailReasonResponse(slotId, details), TELEPHONY_SUCCESS);
        RingbackVoice ringback;
        ASSERT_EQ(callCallbackProxy->CallRingBackReport(slotId, ringback), TELEPHONY_SUCCESS);
        int32_t active = 0;
        ASSERT_EQ(callCallbackProxy->GetImsSwitchResponse(slotId, active), TELEPHONY_SUCCESS);
        MuteControlResponse muteResponse;
        ASSERT_EQ(callCallbackProxy->SetMuteResponse(slotId, muteResponse), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackProxy_0002
 * @tc.name     Test for ImsCallCallbackProxy
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsCallCallbackProxy_0002, Function | MediumTest | Level3)
{
    const sptr<ImsCallCallbackInterface> imsCallCallback_ = (std::make_unique<ImsCallCallbackStub>()).release();
    auto callCallbackProxy = iface_cast<ImsCallCallbackInterface>(imsCallCallback_->AsObject().GetRefPtr());
    ASSERT_TRUE(callCallbackProxy != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        EventFwk::MatchingSkills matchingSkills;
        matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
        EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
        std::shared_ptr<AppExecFwk::EventRunner> eventLoop = AppExecFwk::EventRunner::Create("Imstest");
        auto handler = std::make_shared<CellularCallHandler>(eventLoop, subscriberInfo);
        handler->SetSlotId(slotId);
        handler->RegisterImsCallCallbackHandler();
        GetClipResult clipResult;
        clipResult.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetClipResponse(slotId, clipResult), TELEPHONY_SUCCESS);
        GetClirResult clirResult;
        clirResult.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetClirResponse(slotId, clirResult), TELEPHONY_SUCCESS);
        SsBaseResult normalResult;
        normalResult.index = DEFAULT_INDEX;
        ASSERT_EQ(callCallbackProxy->SetClipResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetClirResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetCallTransferResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetCallRestrictionResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetCallWaitingResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetColrResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetColpResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        CallForwardQueryInfoList callList;
        callList.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetCallTransferResponse(slotId, callList), TELEPHONY_SUCCESS);
        CallRestrictionResult crResult;
        crResult.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetCallRestrictionResponse(slotId, crResult), TELEPHONY_SUCCESS);
        CallWaitResult cwResult;
        cwResult.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetCallWaitingResponse(slotId, cwResult), TELEPHONY_SUCCESS);
        GetColrResult colrResult;
        colrResult.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetColrResponse(slotId, colrResult), TELEPHONY_SUCCESS);
        GetColpResult colpResult;
        colpResult.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetColpResponse(slotId, colpResult), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0001
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsCallCallbackStub_0001, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    sptr<ImsCallCallbackStub> stub = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stub != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        HRilRadioResponseInfo rilRadioResponse;
        rilRadioResponse.error = HRilErrType::HRIL_ERR_GENERIC_FAILURE;
        MessageParcel answerData;
        MessageParcel answerReply;
        ASSERT_TRUE(answerData.WriteInt32(slotId));
        ASSERT_TRUE(answerData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo)));
        ASSERT_EQ(stub->OnAnswerResponseInner(answerData, answerReply), TELEPHONY_SUCCESS);

        MessageParcel dialData;
        MessageParcel dialReply;
        ASSERT_TRUE(dialData.WriteInt32(slotId));
        ASSERT_TRUE(dialData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo)));
        ASSERT_EQ(stub->OnDialResponseInner(dialData, dialReply), TELEPHONY_SUCCESS);

        MessageParcel imsCallsData;
        MessageParcel imsCallsReply;
        ASSERT_TRUE(imsCallsData.WriteInt32(slotId));
        ASSERT_TRUE(imsCallsData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo)));
        ASSERT_EQ(stub->OnGetImsCallsDataResponseInner(imsCallsData, imsCallsReply), TELEPHONY_SUCCESS);

        MessageParcel hangupData;
        MessageParcel hangupReply;
        ASSERT_TRUE(hangupData.WriteInt32(slotId));
        ASSERT_TRUE(hangupData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo)));
        ASSERT_EQ(stub->OnHangUpResponseInner(hangupData, hangupReply), TELEPHONY_SUCCESS);

        MessageParcel holdCallData;
        MessageParcel holdCallReply;
        ASSERT_TRUE(holdCallData.WriteInt32(slotId));
        ASSERT_TRUE(holdCallData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo)));
        ASSERT_EQ(stub->OnHoldCallResponseInner(holdCallData, holdCallReply), TELEPHONY_SUCCESS);

        MessageParcel rejectData;
        MessageParcel rejectReply;
        ASSERT_TRUE(rejectData.WriteInt32(slotId));
        ASSERT_TRUE(rejectData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo)));
        ASSERT_EQ(stub->OnRejectResponseInner(rejectData, rejectReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0002
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsCallCallbackStub_0002, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    sptr<ImsCallCallbackStub> stub = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stub != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        HRilRadioResponseInfo rilRadioResponse;
        rilRadioResponse.error = HRilErrType::HRIL_ERR_GENERIC_FAILURE;
        MessageParcel sendDtmfData;
        MessageParcel sendDtmfReply;
        ASSERT_TRUE(sendDtmfData.WriteInt32(slotId));
        ASSERT_TRUE(sendDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo)));
        ASSERT_EQ(stub->OnSendDtmfResponseInner(sendDtmfData, sendDtmfReply), TELEPHONY_SUCCESS);

        MessageParcel setImsSwitchData;
        MessageParcel setImsSwitchReply;
        ASSERT_TRUE(setImsSwitchData.WriteInt32(slotId));
        ASSERT_TRUE(setImsSwitchData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo)));
        ASSERT_EQ(stub->OnSetImsSwitchResponseInner(setImsSwitchData, setImsSwitchReply), TELEPHONY_SUCCESS);

        MessageParcel startDtmfData;
        MessageParcel startDtmfReply;
        ASSERT_TRUE(startDtmfData.WriteInt32(slotId));
        ASSERT_TRUE(startDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo)));
        ASSERT_EQ(stub->OnStartDtmfResponseInner(startDtmfData, startDtmfReply), TELEPHONY_SUCCESS);

        MessageParcel stopDtmfData;
        MessageParcel stopDtmfReply;
        ASSERT_TRUE(stopDtmfData.WriteInt32(slotId));
        ASSERT_TRUE(stopDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo)));
        ASSERT_EQ(stub->OnStopDtmfResponseInner(stopDtmfData, stopDtmfReply), TELEPHONY_SUCCESS);

        MessageParcel switchCallData;
        MessageParcel switchCallReply;
        ASSERT_TRUE(switchCallData.WriteInt32(slotId));
        ASSERT_TRUE(switchCallData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo)));
        ASSERT_EQ(stub->OnSwitchCallResponseInner(switchCallData, switchCallReply), TELEPHONY_SUCCESS);

        MessageParcel unholdData;
        MessageParcel unholdReply;
        ASSERT_TRUE(unholdData.WriteInt32(slotId));
        ASSERT_TRUE(unholdData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo)));
        ASSERT_EQ(stub->OnUnHoldCallResponseInner(unholdData, unholdReply), TELEPHONY_SUCCESS);

        MessageParcel getImsSwitchData;
        MessageParcel getImsSwitchReply;
        ASSERT_TRUE(getImsSwitchData.WriteInt32(slotId));
        ASSERT_TRUE(getImsSwitchData.WriteRawData((const void *)&rilRadioResponse, sizeof(HRilRadioResponseInfo)));
        ASSERT_EQ(stub->OnGetImsSwitchResponseInner(getImsSwitchData, getImsSwitchReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0003
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsCallCallbackStub_0003, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }

    sptr<ImsCallCallbackStub> stub = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stub != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        MessageParcel data;
        MessageParcel reply;
        ASSERT_TRUE(data.WriteInt32(slotId));
        ASSERT_NE(stub->OnAnswerResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnCallRingBackReportInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnDialResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnGetCallRestrictionResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnGetCallTransferResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnGetCallWaitingResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnGetClipResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnGetClirResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnGetColpResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnGetColrResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnGetImsCallsDataResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnHangUpResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnHoldCallResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnRejectResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnSendDtmfResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnSetImsSwitchResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnStartDtmfResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnStopDtmfResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnSwitchCallResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnUnHoldCallResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnSetCallRestrictionResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnSetCallTransferResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnSetCallWaitingResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnSetClipResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnSetClirResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnSetColpResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnSetColrResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->OnSetMuteResponseInner(data, reply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0004
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsCallCallbackStub_0004, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    sptr<ImsCallCallbackStub> stub = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stub != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        SsBaseResult normalResult;
        normalResult.index = DEFAULT_INDEX;
        MessageParcel crData;
        MessageParcel crReply;
        ASSERT_TRUE(crData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(crData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetCallRestrictionResponseInner(crData, crReply), TELEPHONY_SUCCESS);
        MessageParcel ctData;
        MessageParcel ctReply;
        ASSERT_TRUE(ctData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(ctData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetCallTransferResponseInner(ctData, ctReply), TELEPHONY_SUCCESS);
        MessageParcel cwData;
        MessageParcel cwReply;
        ASSERT_TRUE(cwData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(cwData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetCallWaitingResponseInner(cwData, cwReply), TELEPHONY_SUCCESS);
        MessageParcel clipData;
        MessageParcel clipReply;
        ASSERT_TRUE(clipData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(clipData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetClipResponseInner(clipData, clipReply), TELEPHONY_SUCCESS);
        MessageParcel clirData;
        MessageParcel clirReply;
        ASSERT_TRUE(clirData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(clirData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetClirResponseInner(clirData, clirReply), TELEPHONY_SUCCESS);
        MessageParcel colpData;
        MessageParcel colpReply;
        ASSERT_TRUE(colpData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(colpData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetColpResponseInner(colpData, colpReply), TELEPHONY_SUCCESS);
        MessageParcel colrData;
        MessageParcel colrReply;
        ASSERT_TRUE(colrData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(colrData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetColrResponseInner(colrData, colrReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0005
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsCallCallbackStub_0005, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    sptr<ImsCallCallbackStub> stub = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stub != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        SsBaseResult normalResult;
        normalResult.index = INVALID_INDEX;
        MessageParcel crData;
        MessageParcel crReply;
        ASSERT_TRUE(crData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(crData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetCallRestrictionResponseInner(crData, crReply), TELEPHONY_SUCCESS);
        MessageParcel ctData;
        MessageParcel ctReply;
        ASSERT_TRUE(ctData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(ctData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetCallTransferResponseInner(ctData, ctReply), TELEPHONY_SUCCESS);
        MessageParcel cwData;
        MessageParcel cwReply;
        ASSERT_TRUE(cwData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(cwData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetCallWaitingResponseInner(cwData, cwReply), TELEPHONY_SUCCESS);
        MessageParcel clipData;
        MessageParcel clipReply;
        ASSERT_TRUE(clipData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(clipData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetClipResponseInner(clipData, clipReply), TELEPHONY_SUCCESS);
        MessageParcel clirData;
        MessageParcel clirReply;
        ASSERT_TRUE(clirData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(clirData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetClirResponseInner(clirData, clirReply), TELEPHONY_SUCCESS);
        MessageParcel colpData;
        MessageParcel colpReply;
        ASSERT_TRUE(colpData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(colpData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetColpResponseInner(colpData, colpReply), TELEPHONY_SUCCESS);
        MessageParcel colrData;
        MessageParcel colrReply;
        ASSERT_TRUE(colrData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(colrData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnSetColrResponseInner(colrData, colrReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0006
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsCallCallbackStub_0006, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    sptr<ImsCallCallbackStub> stub = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stub != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        SsBaseResult normalResult;
        normalResult.index = DEFAULT_INDEX;
        normalResult.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stub->SetCallRestrictionResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->SetCallTransferResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->SetCallWaitingResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_NE(stub->SetClirResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        MessageParcel muteData;
        MessageParcel muteReply;
        MuteControlResponse muteResponse;
        ASSERT_TRUE(muteData.WriteInt32(slotId));
        ASSERT_TRUE(muteData.WriteRawData((const void *)&muteResponse, sizeof(MuteControlResponse)));
        ASSERT_EQ(stub->OnSetMuteResponseInner(muteData, muteReply), TELEPHONY_SUCCESS);
        MessageParcel ringData;
        MessageParcel ringReply;
        RingbackVoice ringback;
        ASSERT_TRUE(ringData.WriteInt32(slotId));
        ASSERT_TRUE(ringData.WriteRawData((const void *)&ringback, sizeof(RingbackVoice)));
        ASSERT_EQ(stub->OnCallRingBackReportInner(ringData, ringReply), TELEPHONY_SUCCESS);
        MessageParcel failData;
        MessageParcel failReply;
        DisconnectedDetails details;
        ASSERT_TRUE(failData.WriteInt32(slotId));
        ASSERT_TRUE(failData.WriteInt32(static_cast<int32_t>(details.reason)));
        ASSERT_TRUE(failData.WriteString(details.message));
        ASSERT_EQ(stub->OnLastCallFailReasonResponseInner(failData, failReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0007
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsCallCallbackStub_0007, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    sptr<ImsCallCallbackStub> stub = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stub != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        CallRestrictionResult crResult;
        crResult.result.index = INVALID_INDEX;
        MessageParcel crErrorData;
        MessageParcel crErrorReply;
        ASSERT_TRUE(crErrorData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsResult(crErrorData, crResult.result, crResult.status, crResult.classCw), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetCallRestrictionResponseInner(crErrorData, crErrorReply), TELEPHONY_SUCCESS);

        crResult.result.index = DEFAULT_INDEX;
        MessageParcel crData;
        MessageParcel crReply;
        ASSERT_TRUE(crData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsResult(crData, crResult.result, crResult.status, crResult.classCw), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetCallRestrictionResponseInner(crData, crReply), TELEPHONY_SUCCESS);
        crResult.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stub->GetCallRestrictionResponse(slotId, crResult), TELEPHONY_SUCCESS);

        CallForwardQueryInfoList callList;
        callList.result.index = INVALID_INDEX;
        MessageParcel ctErrorData;
        MessageParcel ctErrorReply;
        ASSERT_TRUE(ctErrorData.WriteInt32(slotId));
        ASSERT_EQ(WriteCallForwardResult(ctErrorData, callList), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetCallTransferResponseInner(ctErrorData, ctErrorReply), TELEPHONY_SUCCESS);

        callList.result.index = DEFAULT_INDEX;
        MessageParcel ctData;
        MessageParcel ctReply;
        ASSERT_TRUE(ctData.WriteInt32(slotId));
        ASSERT_EQ(WriteCallForwardResult(ctData, callList), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetCallTransferResponseInner(ctData, ctReply), TELEPHONY_SUCCESS);
        callList.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stub->GetCallTransferResponse(slotId, callList), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0008
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsCallCallbackStub_0008, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    sptr<ImsCallCallbackStub> stub = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stub != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        CallWaitResult cwResult;
        cwResult.result.index = INVALID_INDEX;
        MessageParcel cwErrorData;
        MessageParcel cwErrorReply;
        ASSERT_TRUE(cwErrorData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsResult(cwErrorData, cwResult.result, cwResult.status, cwResult.classCw), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetCallWaitingResponseInner(cwErrorData, cwErrorReply), TELEPHONY_SUCCESS);

        cwResult.result.index = DEFAULT_INDEX;
        MessageParcel cwData;
        MessageParcel cwReply;
        ASSERT_TRUE(cwData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsResult(cwData, cwResult.result, cwResult.status, cwResult.classCw), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetCallWaitingResponseInner(cwData, cwReply), TELEPHONY_SUCCESS);
        cwResult.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stub->GetCallWaitingResponse(slotId, cwResult), TELEPHONY_SUCCESS);

        GetClipResult clipResult;
        clipResult.result.index = INVALID_INDEX;
        MessageParcel clipErrorData;
        MessageParcel clipErrorReply;
        ASSERT_TRUE(clipErrorData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(clipErrorData, clipResult.result, clipResult.action, clipResult.clipStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetClipResponseInner(clipErrorData, clipErrorReply), TELEPHONY_SUCCESS);

        clipResult.result.index = DEFAULT_INDEX;
        MessageParcel clipData;
        MessageParcel clipReply;
        ASSERT_TRUE(clipData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(clipData, clipResult.result, clipResult.action, clipResult.clipStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetClipResponseInner(clipData, clipReply), TELEPHONY_SUCCESS);
        clipResult.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stub->GetClipResponse(slotId, clipResult), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0009
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ImsCallCallbackStub_0009, Function | MediumTest | Level3)
{
    if (!HasSimCard(SIM1_SLOTID) && !HasSimCard(SIM2_SLOTID)) {
        return;
    }
    sptr<ImsCallCallbackStub> stub = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stub != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        GetClirResult clirResult;
        clirResult.result.index = INVALID_INDEX;
        MessageParcel clirErrorData;
        MessageParcel clirErrorReply;
        ASSERT_TRUE(clirErrorData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(clirErrorData, clirResult.result, clirResult.action, clirResult.clirStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetClirResponseInner(clirErrorData, clirErrorReply), TELEPHONY_SUCCESS);

        clirResult.result.index = DEFAULT_INDEX;
        MessageParcel clirData;
        MessageParcel clirReply;
        ASSERT_TRUE(clirData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(clirData, clirResult.result, clirResult.action, clirResult.clirStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetClirResponseInner(clirData, clirReply), TELEPHONY_SUCCESS);
        clirResult.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stub->GetClirResponse(slotId, clirResult), TELEPHONY_SUCCESS);

        GetColpResult colpResult;
        colpResult.result.index = INVALID_INDEX;
        MessageParcel colpErrorData;
        MessageParcel colpErrorReply;
        ASSERT_TRUE(colpErrorData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(colpErrorData, colpResult.result, colpResult.action, colpResult.colpStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetColpResponseInner(colpErrorData, colpErrorReply), TELEPHONY_SUCCESS);

        colpResult.result.index = DEFAULT_INDEX;
        MessageParcel colpData;
        MessageParcel colpReply;
        ASSERT_TRUE(colpData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(colpData, colpResult.result, colpResult.action, colpResult.colpStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetColpResponseInner(colpData, colpReply), TELEPHONY_SUCCESS);

        GetColrResult colrResult;
        colrResult.result.index = INVALID_INDEX;
        MessageParcel colrErrorData;
        MessageParcel colrErrorReply;
        ASSERT_TRUE(colrErrorData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(colrErrorData, colrResult.result, colrResult.action, colrResult.colrStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetColrResponseInner(colrErrorData, colrErrorReply), TELEPHONY_SUCCESS);

        colrResult.result.index = DEFAULT_INDEX;
        MessageParcel colrData;
        MessageParcel colrReply;
        ASSERT_TRUE(colrData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(colrData, colrResult.result, colrResult.action, colrResult.colrStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stub->OnGetColrResponseInner(colrData, colrReply), TELEPHONY_SUCCESS);
    }
}
} // namespace Telephony
} // namespace OHOS
