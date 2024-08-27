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
#include "standardize_utils.h"
#include "mmi_code_utils.h"
#include "module_service_utils.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
class StandardizeUtilsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};
void StandardizeUtilsTest::SetUpTestCase() {}

void StandardizeUtilsTest::TearDownTestCase() {}

void StandardizeUtilsTest::SetUp() {}

void StandardizeUtilsTest::TearDown() {}


/**
 * @tc.number   Telephony_StandardizeUtilsTest_0001
 * @tc.name     Test CellularCallConnectionCS
 * @tc.desc     Function test
 */
HWTEST_F(StandardizeUtilsTest, StandardizeUtilsTest_0001, Function | MediumTest | Level1)
{
    StandardizeUtils standardizeUtils;
    std::string phoneString;
    EXPECT_EQ(standardizeUtils.RemoveSeparatorsPhoneNumber(phoneString), "");

    phoneString = "1234567890*#+N,;!@$%^&*()_-={}[]|:<>?";
    EXPECT_NE(standardizeUtils.RemoveSeparatorsPhoneNumber(phoneString), "1234567890*#+N,;");

    std::string networkAddress;
    std::string postDial;
    standardizeUtils.ExtractAddressAndPostDial(phoneString, networkAddress, postDial);
    EXPECT_EQ(networkAddress, "1234567890*#+N");
    EXPECT_EQ(postDial, ",;!@$%^&*()_-={}[]|:<>?");

    int32_t intValue1 = 145;
    int32_t intValue2 = 133;
    phoneString = "1234567890*#+N,;!@$%^&*()_-={}[]|:<>?";
    EXPECT_EQ(standardizeUtils.FormatNumberAndToa(phoneString, intValue1), "+1234567890*#+N,;!@$%^&*()_-={}[]|:<>?");
    EXPECT_EQ(standardizeUtils.FormatNumberAndToa(phoneString, intValue2), "1234567890*#+N,;!@$%^&*()_-={}[]|:<>?");

    phoneString = "+1234567890*#+N,;!@$%^&*()_-={}[]|:<>?";
    EXPECT_EQ(standardizeUtils.FormatNumberAndToa(phoneString, intValue1), "+1234567890*#+N,;!@$%^&*()_-={}[]|:<>?");
    EXPECT_EQ(standardizeUtils.FormatNumberAndToa(phoneString, intValue2), "+1234567890*#+N,;!@$%^&*()_-={}[]|:<>?");

    phoneString = "12345678908";
    EXPECT_EQ(standardizeUtils.FormatNumberAndToa(phoneString, intValue1), "+12345678908");
    EXPECT_EQ(standardizeUtils.FormatNumberAndToa(phoneString, intValue2), "12345678908");

    phoneString = "+12345678908";
    EXPECT_EQ(standardizeUtils.FormatNumberAndToa(phoneString, intValue1), "+12345678908");
    EXPECT_EQ(standardizeUtils.FormatNumberAndToa(phoneString, intValue2), "+12345678908");
}

/**
 * @tc.number   Telephony_MMICodeUtilsTest_0001
 * @tc.name     Test MMICodeUtils
 * @tc.desc     Function test
 */
HWTEST_F(StandardizeUtilsTest, MMICodeUtilsTest_0001, Function | MediumTest | Level1)
{
    MMICodeUtils mmiCodeUtils;
    std::string analyseString;
    bool isNeedUseIms = true;
    mmiCodeUtils.IsNeedExecuteMmi(analyseString, isNeedUseIms);

    int32_t slotId = 0;
    EXPECT_FALSE(mmiCodeUtils.ExecuteMmiCode(slotId));

    mmiCodeUtils.mmiData_.serviceCode = "03";
    mmiCodeUtils.ExecuteMmiCode(slotId);
    EXPECT_TRUE(mmiCodeUtils.ExecuteMmiCode(slotId));
}

/**
 * @tc.number   Telephony_ModuleServiceUtilsTest_0001
 * @tc.name     Test ModuleServiceUtils
 * @tc.desc     Function test
 */
HWTEST_F(StandardizeUtilsTest, ModuleServiceUtilsTest_0001, Function | MediumTest | Level1)
{
    ModuleServiceUtils moduleServiceUtils;
    int32_t slotId = 0;
    EXPECT_FALSE(moduleServiceUtils.GetImsUtSupportState(slotId));

    auto ptr = moduleServiceUtils.GetImsServiceRemoteObject();
    EXPECT_EQ(ptr, nullptr);
}
} // namespace Telephony
} // namespace OHOS