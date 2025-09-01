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

#include <fstream>
#include "gtest/gtest.h"
#include "cellular_call_supplement.h"
#include "telephony_ext_wrapper.h"
#include "ims_control.h"
#include "parameters.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
class CellularCallSupplementTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

bool IsEmptyMmiResultFilteredMock(int slotId)
{
    return true;
}

bool IsEmptyMmiResultFilteredMockFalse(int slotId)
{
    return false;
}

bool IsMmiCodeMock(int32_t slotId, std::string &number)
{
    return true;
}

bool IsMmiCodeMockFalse(int32_t slotId, std::string &number)
{
    return false;
}

bool IsUssdReleaseMsgFilteredMock(int32_t slotId)
{
    return true;
}

bool IsUssdReleaseMsgFilteredMockFalse(int32_t slotId)
{
    return false;
}

void UnescapeHtmlCodeMock(int32_t slotId, std::string &content)
{}

static void RenameFile(std::string from, std::string to)
{
    std::fstream fs;
    fs.open(from.c_str());
    if (fs.fail()) {
        fs.close();
        return;
    }
    fs.close();
    rename(from.c_str(), to.c_str());
}

void CellularCallSupplementTest::SetUpTestCase()
{}

void CellularCallSupplementTest::TearDownTestCase()
{}

void CellularCallSupplementTest::SetUp()
{}

void CellularCallSupplementTest::TearDown()
{}

/**
 * @tc.number   CellularCallSupplementTest_001
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_001, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isEmptyMmiResultFiltered_ = IsEmptyMmiResultFilteredMock;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "";
    ussdNoticeInfo.m = 1;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

/**
 * @tc.number   CellularCallSupplementTest_002
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_002, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isEmptyMmiResultFiltered_ = IsEmptyMmiResultFilteredMock;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "abc";
    ussdNoticeInfo.m = 1;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

/**
 * @tc.number   CellularCallSupplementTest_003
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_003, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isEmptyMmiResultFiltered_ = IsEmptyMmiResultFilteredMockFalse;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "";
    ussdNoticeInfo.m = 1;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

/**
 * @tc.number   CellularCallSupplementTest_004
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_004, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isEmptyMmiResultFiltered_ = nullptr;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "";
    ussdNoticeInfo.m = 1;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

/**
 * @tc.number   CellularCallSupplementTest_005
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_005, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isUssdReleaseMsgFiltered_ = IsUssdReleaseMsgFilteredMock;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "abc";
    ussdNoticeInfo.m = 2;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

/**
 * @tc.number   CellularCallSupplementTest_006
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_006, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isUssdReleaseMsgFiltered_ = IsUssdReleaseMsgFilteredMockFalse;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "abc";
    ussdNoticeInfo.m = 2;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

/**
 * @tc.number   CellularCallSupplementTest_007
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_007, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isUssdReleaseMsgFiltered_ = nullptr;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "abc";
    ussdNoticeInfo.m = 2;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

/**
 * @tc.number   CellularCallSupplementTest_008
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_008, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.unescapeHtmlCode_ = UnescapeHtmlCodeMock;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "&amp;";
    ussdNoticeInfo.m = 2;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

/**
 * @tc.number   CellularCallSupplementTest_009
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_009, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.unescapeHtmlCode_ = nullptr;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "&amp;";
    ussdNoticeInfo.m = 2;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

/**
 * @tc.number   CellularCallSupplementTest_010
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_010, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isMmiCode_ = IsMmiCodeMock;
    IMSControl control;
    std::string phoneNum = "*9";
    CLIRMode mode = CLIRMode::DEFAULT;
    bool isNeed = control.IsNeedExecuteMMI(0, phoneNum, mode, true);
    EXPECT_FALSE(isNeed);
}

/**
 * @tc.number   CellularCallSupplementTest_011
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_011, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isMmiCode_ = nullptr;
    IMSControl control;
    std::string phoneNum = "*9";
    CLIRMode mode = CLIRMode::DEFAULT;
    bool isNeed = control.IsNeedExecuteMMI(0, phoneNum, mode, true);
    EXPECT_FALSE(isNeed);
}

/**
 * @tc.number   CellularCallSupplementTest_012
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_012, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isMmiCode_ = IsMmiCodeMockFalse;
    IMSControl control;
    std::string phoneNum = "*100#";
    CLIRMode mode = CLIRMode::DEFAULT;
    bool isNeed = control.IsNeedExecuteMMI(0, phoneNum, mode, true);
    EXPECT_FALSE(isNeed);
}

/**
 * @tc.number   CellularCallSupplementTest_013
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_013, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.InitTelephonyExtWrapper();
    EXPECT_TRUE(TELEPHONY_EXT_WRAPPER.isEmptyMmiResultFiltered_ != nullptr);
    EXPECT_TRUE(TELEPHONY_EXT_WRAPPER.isMmiCode_ != nullptr);
    EXPECT_TRUE(TELEPHONY_EXT_WRAPPER.isUssdReleaseMsgFiltered_ != nullptr);
    EXPECT_TRUE(TELEPHONY_EXT_WRAPPER.unescapeHtmlCode_ != nullptr);
    TELEPHONY_EXT_WRAPPER.~TelephonyExtWrapper();
    TELEPHONY_EXT_WRAPPER.InitTelephonyExtWrapper();
}

/**
 * @tc.number   CellularCallSupplementTest_014
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_014, Function | MediumTest | Level1)
{
    std::string filePath = "/system/lib64/libtelephony_ext_service.z.so";
    std::string bakFilePath = "/system/lib64/libtelephony_ext_service.z.so.bak";
    RenameFile(filePath, bakFilePath);
    TELEPHONY_EXT_WRAPPER.InitTelephonyExtWrapper();
    EXPECT_FALSE(TELEPHONY_EXT_WRAPPER.isEmptyMmiResultFiltered_ == nullptr);
    EXPECT_FALSE(TELEPHONY_EXT_WRAPPER.isMmiCode_ == nullptr);
    EXPECT_FALSE(TELEPHONY_EXT_WRAPPER.isUssdReleaseMsgFiltered_ == nullptr);
    EXPECT_FALSE(TELEPHONY_EXT_WRAPPER.unescapeHtmlCode_ == nullptr);
    TELEPHONY_EXT_WRAPPER.~TelephonyExtWrapper();
    RenameFile(bakFilePath, filePath);
    TELEPHONY_EXT_WRAPPER.InitTelephonyExtWrapper();
}

/**
 * @tc.number   CellularCallSupplementTest_015
 * @tc.name     Test CellularCallSupplement
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_015, Function | MediumTest | Level1)
{
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "";
    ussdNoticeInfo.m = 2;
    CellularCallSupplement callSup;
    SetParameter("const.telephony.hw_show_mmi_error", "true");
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
    SetParameter("const.telephony.hw_show_mmi_error", "false");
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
    ussdNoticeInfo.str = "12345";
    SetParameter("const.telephony.hw_show_mmi_error", "true");
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
    SetParameter("const.telephony.hw_show_mmi_error", "false");
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

}  // namespace Telephony
}  // namespace OHOS