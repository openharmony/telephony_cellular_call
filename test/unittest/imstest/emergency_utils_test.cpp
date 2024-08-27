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
#include "telephony_errors.h"
#include "emergency_utils.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
class EmergencyUtilsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};
void EmergencyUtilsTest::SetUpTestCase() {}

void EmergencyUtilsTest::TearDownTestCase() {}

void EmergencyUtilsTest::SetUp() {}

void EmergencyUtilsTest::TearDown() {}

/**
 * @tc.number   Telephony_EmergencyUtilsTest_0001
 * @tc.name     Test EmergencyUtilsTest
 * @tc.desc     Function test
 */
HWTEST_F(EmergencyUtilsTest, EmergencyUtilsTest_0001, Function | MediumTest | Level1)
{
    EmergencyUtils emergencyUtils;
    int32_t slotId = 0;
    std::string phoneNum;
    bool enabled = false;
    EXPECT_EQ(emergencyUtils.IsEmergencyCall(slotId, phoneNum, enabled), TELEPHONY_ERR_ARGUMENT_INVALID);

    phoneNum = "+911";
    EXPECT_EQ(emergencyUtils.IsEmergencyCall(slotId, phoneNum, enabled), TELEPHONY_ERR_ARGUMENT_INVALID);

    phoneNum = "911@123456778901";
    EXPECT_EQ(emergencyUtils.IsEmergencyCall(slotId, phoneNum, enabled), TELEPHONY_ERR_ARGUMENT_INVALID);

    phoneNum = "911%40123456778901";
    EXPECT_EQ(emergencyUtils.IsEmergencyCall(slotId, phoneNum, enabled), TELEPHONY_ERR_ARGUMENT_INVALID);
}

/**
 * @tc.number   Telephony_EmergencyUtilsTest_0002
 * @tc.name     Test EmergencyUtilsTest
 * @tc.desc     Function test
 */
HWTEST_F(EmergencyUtilsTest, EmergencyUtilsTest_0002, Function | MediumTest | Level1)
{
    EmergencyUtils emergencyUtils;
    int32_t slotId = 0;
    bool enabled = false;

    std::string formatString = "57694898180";
    EXPECT_EQ(emergencyUtils.IsEmergencyCallProcessing(slotId, formatString, enabled), TELEPHONY_SUCCESS);

    formatString = "110";
    EXPECT_EQ(emergencyUtils.IsEmergencyCallProcessing(slotId, formatString, enabled), TELEPHONY_SUCCESS);
    
    formatString = "120";
    EXPECT_EQ(emergencyUtils.IsEmergencyCallProcessing(slotId, formatString, enabled), TELEPHONY_SUCCESS);
    
    formatString = "119";
    EXPECT_EQ(emergencyUtils.IsEmergencyCallProcessing(slotId, formatString, enabled), TELEPHONY_SUCCESS);
    
    formatString = "122";
    EXPECT_EQ(emergencyUtils.IsEmergencyCallProcessing(slotId, formatString, enabled), TELEPHONY_SUCCESS);
    
    formatString = "112";
    EXPECT_EQ(emergencyUtils.IsEmergencyCallProcessing(slotId, formatString, enabled), TELEPHONY_SUCCESS);
    
    formatString = "000";
    EXPECT_EQ(emergencyUtils.IsEmergencyCallProcessing(slotId, formatString, enabled), TELEPHONY_SUCCESS);
    
    formatString = "911";
    EXPECT_EQ(emergencyUtils.IsEmergencyCallProcessing(slotId, formatString, enabled), TELEPHONY_SUCCESS);
    
    formatString = "08";
    EXPECT_EQ(emergencyUtils.IsEmergencyCallProcessing(slotId, formatString, enabled), TELEPHONY_SUCCESS);
    
    formatString = "118";
    EXPECT_EQ(emergencyUtils.IsEmergencyCallProcessing(slotId, formatString, enabled), TELEPHONY_SUCCESS);
    
    formatString = "999";
    EXPECT_EQ(emergencyUtils.IsEmergencyCallProcessing(slotId, formatString, enabled), TELEPHONY_SUCCESS);
}
} // namespace Telephony
} // namespace OHOS