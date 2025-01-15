/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "config_request.h"
#include "call_manager_inner_type.h"
#include "ims_call_client.h"
#include "cellular_call_service.h"
#include "ims_feature.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
class ConfigRequestTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};
void ConfigRequestTest::SetUpTestCase() {}

void ConfigRequestTest::TearDownTestCase() {}

void ConfigRequestTest::SetUp() {}

void ConfigRequestTest::TearDown() {}

/**
 * @tc.number   Telephony_ConfigRequestTest_0001
 * @tc.name     Test EmergencyUtilsTest SetImsSwitchStatusRequest
 * @tc.desc     Function test
 */
HWTEST_F(ConfigRequestTest, ConfigRequestTest_0001, Function | MediumTest | Level1)
{
    ConfigRequest configRequest;
    DelayedSingleton<ImsCallClient>::GetInstance()->UnInit();
    int32_t slotId = 0;
    bool active = true;
    EXPECT_EQ(configRequest.SetImsSwitchStatusRequest(slotId, active), CALL_ERR_RESOURCE_UNAVAILABLE);
}

/**
 * @tc.number   Telephony_ConfigRequestTest_0002
 * @tc.name     Test EmergencyUtilsTest SetVoNRSwitchStatusRequest
 * @tc.desc     Function test
 */
HWTEST_F(ConfigRequestTest, ConfigRequestTest_0002, Function | MediumTest | Level1)
{
    ConfigRequest configRequest;
    int32_t slotId = 0;
    int32_t state = 0;
    EXPECT_EQ(configRequest.SetVoNRSwitchStatusRequest(slotId, state), CALL_ERR_RESOURCE_UNAVAILABLE);

    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    EXPECT_NE(configRequest.SetVoNRSwitchStatusRequest(slotId, state), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_ConfigRequestTest_0003
 * @tc.name     Test EmergencyUtilsTest SetVoNRSwitchStatusRequest
 * @tc.desc     Function test
 */
HWTEST_F(ConfigRequestTest, ConfigRequestTest_0003, Function | MediumTest | Level1)
{
    ConfigRequest configRequest;
    int32_t slotId = 0;
    configRequest.GetImsSwitchStatusRequest(slotId);

    DelayedSingleton<ImsCallClient>::GetInstance()->UnInit();
    EXPECT_EQ(configRequest.GetImsSwitchStatusRequest(slotId), CALL_ERR_RESOURCE_UNAVAILABLE);
}

/**
 * @tc.number   Telephony_ConfigRequestTest_0004
 * @tc.name     Test EmergencyUtilsTest SetVoNRSwitchStatusRequest
 * @tc.desc     Function test
 */
HWTEST_F(ConfigRequestTest, ConfigRequestTest_0004, Function | MediumTest | Level1)
{
    ConfigRequest configRequest;
    std::string value;
    int32_t intValue = 1;
    configRequest.SetImsConfigRequest(ImsConfigItem::ITEM_VIDEO_QUALITY, value);
    configRequest.SetImsConfigRequest(ImsConfigItem::ITEM_VIDEO_QUALITY, intValue);
    configRequest.SetImsFeatureValueRequest(FeatureType::TYPE_VOICE_OVER_LTE, intValue);

    DelayedSingleton<ImsCallClient>::GetInstance()->UnInit();
    EXPECT_EQ(configRequest.SetImsConfigRequest(ImsConfigItem::ITEM_VIDEO_QUALITY, value),
        CALL_ERR_RESOURCE_UNAVAILABLE);
    EXPECT_EQ(configRequest.SetImsConfigRequest(ImsConfigItem::ITEM_VIDEO_QUALITY, intValue),
        CALL_ERR_RESOURCE_UNAVAILABLE);
    EXPECT_EQ(configRequest.GetImsFeatureValueRequest(FeatureType::TYPE_VOICE_OVER_LTE, intValue),
        CALL_ERR_RESOURCE_UNAVAILABLE);
}

/**
 * @tc.number   Telephony_ConfigRequestTest_0005
 * @tc.name     Test EmergencyUtilsTest SetVoNRSwitchStatusRequest
 * @tc.desc     Function test
 */
HWTEST_F(ConfigRequestTest, ConfigRequestTest_0005, Function | MediumTest | Level1)
{
    ConfigRequest configRequest;
    ImsConfigItem item = ITEM_VIDEO_QUALITY;
    configRequest.GetImsConfigRequest(item);

    DelayedSingleton<ImsCallClient>::GetInstance()->UnInit();
    EXPECT_EQ(configRequest.GetImsConfigRequest(item), CALL_ERR_RESOURCE_UNAVAILABLE);

    int32_t slotId = 0;
    ImsCapabilityList imsCapList;
    EXPECT_EQ(configRequest.UpdateImsCapabilities(slotId, imsCapList), CALL_ERR_RESOURCE_UNAVAILABLE);
}

/**
 * @tc.number   Telephony_ConfigRequestTest_0006
 * @tc.name     Test EmergencyUtilsTest SetVoNRSwitchStatusRequest
 * @tc.desc     Function test
 */
HWTEST_F(ConfigRequestTest, ConfigRequestTest_0006, Function | MediumTest | Level1)
{
    ConfigRequest configRequest;
    int32_t slotId = 0;
    int32_t mute = 1;
    configRequest.SetMuteRequest(slotId, mute);
    configRequest.GetMuteRequest(slotId);

    DelayedSingleton<ImsCallClient>::GetInstance()->UnInit();
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    EXPECT_NE(configRequest.SetMuteRequest(slotId, mute), TELEPHONY_SUCCESS);
    EXPECT_NE(configRequest.GetMuteRequest(slotId), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_ConfigRequestTest_0007
 * @tc.name     Test EmergencyUtilsTest SetVoNRSwitchStatusRequest
 * @tc.desc     Function test
 */
HWTEST_F(ConfigRequestTest, ConfigRequestTest_0007, Function | MediumTest | Level1)
{
    ConfigRequest configRequest;
    int32_t slotId = -1;
    std::vector<EmergencyCall> eccVec;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    EXPECT_EQ(configRequest.GetEmergencyCallListRequest(slotId), CALL_ERR_RESOURCE_UNAVAILABLE);
    EXPECT_EQ(configRequest.SetEmergencyCallListRequest(slotId, eccVec), CALL_ERR_RESOURCE_UNAVAILABLE);
}

/**
 * @tc.number   Telephony_ConfigRequestTest_0008
 * @tc.name     Test SetVideoCallWating
 * @tc.desc     Function test
 */
HWTEST_F(ConfigRequestTest, ConfigRequestTest_0008, Function | MediumTest | Level1)
{
    ConfigRequest configRequest;
    int32_t slotId = 1;
    bool activate = false;
    EXPECT_EQ(configRequest.SetVideoCallWaiting(slotId, activate), TELEPHONY_SUCCESS);
    DelayedSingleton<ImsCallClient>::GetInstance()->UnInit();
    EXPECT_EQ(configRequest.SetVideoCallWaiting(slotId, activate), CALL_ERR_RESOURCE_UNAVAILABLE);
}
} // namespace Telephony
} // namespace OHOS