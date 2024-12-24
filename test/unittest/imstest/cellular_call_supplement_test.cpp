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

bool IsNeedRemoveMmiMock(int slotId)
{
    return true;
}

bool IsNeedRemoveMmiMockFalse(int slotId)
{
    return false;
}

bool IsNeedMmiToNormalCallMock(int32_t slotId, std::string &number)
{
    return true;
}

bool IsNeedMmiToNormalCallMockFalse(int32_t slotId, std::string &number)
{
    return false;
}

bool IsUssdOkForReleaseMock(int32_t slotId)
{
    return true;
}

bool IsUssdOkForReleaseMockFalse(int32_t slotId)
{
    return false;
}

void MmiCodeUnescapehtmlMock(int32_t slotId, std::string &content)
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

HWTEST_F(
    CellularCallSupplementTest, CellularCallSupplementTest_IsNeedRemoveMmi_true_001, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isNeedRemoveMmi_ = IsNeedRemoveMmiMock;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "";
    ussdNoticeInfo.m = 1;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

HWTEST_F(
    CellularCallSupplementTest, CellularCallSupplementTest_IsNeedRemoveMmi_true_002, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isNeedRemoveMmi_ = IsNeedRemoveMmiMock;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "abc";
    ussdNoticeInfo.m = 1;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_IsNeedRemoveMmi_false, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isNeedRemoveMmi_ = IsNeedRemoveMmiMockFalse;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "";
    ussdNoticeInfo.m = 1;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_IsNeedRemoveMmi_null, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isNeedRemoveMmi_ = nullptr;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "";
    ussdNoticeInfo.m = 1;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_isUssdOkForRelease_true, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isUssdOkForRelease_ = IsUssdOkForReleaseMock;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "abc";
    ussdNoticeInfo.m = 2;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

HWTEST_F(
    CellularCallSupplementTest, CellularCallSupplementTest_isUssdOkForRelease_false, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isUssdOkForRelease_ = IsUssdOkForReleaseMockFalse;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "abc";
    ussdNoticeInfo.m = 2;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_isUssdOkForRelease_null, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isUssdOkForRelease_ = nullptr;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "abc";
    ussdNoticeInfo.m = 2;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_mmiCodeUnescapehtml, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.mmiCodeUnescapehtml_ = MmiCodeUnescapehtmlMock;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "&amp;";
    ussdNoticeInfo.m = 2;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

HWTEST_F(
    CellularCallSupplementTest, CellularCallSupplementTest_mmiCodeUnescapehtml_null, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.mmiCodeUnescapehtml_ = nullptr;
    UssdNoticeInfo ussdNoticeInfo;
    ussdNoticeInfo.str = "&amp;";
    ussdNoticeInfo.m = 2;
    CellularCallSupplement callSup;
    EXPECT_NO_FATAL_FAILURE(callSup.EventUssdNotify(ussdNoticeInfo, 0));
}

HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_IsNeedMmiToNormalCall, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isNeedMmiToNormalCall_ = IsNeedMmiToNormalCallMock;
    IMSControl control;
    std::string phoneNum = "*9";
    CLIRMode mode = CLIRMode::DEFAULT;
    bool isNeed = control.IsNeedExecuteMMI(0, phoneNum, mode, true);
    EXPECT_FALSE(isNeed);
}

HWTEST_F(
    CellularCallSupplementTest, CellularCallSupplementTest_IsNeedMmiToNormalCall_null, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isNeedMmiToNormalCall_ = nullptr;
    IMSControl control;
    std::string phoneNum = "*9";
    CLIRMode mode = CLIRMode::DEFAULT;
    bool isNeed = control.IsNeedExecuteMMI(0, phoneNum, mode, true);
    EXPECT_FALSE(isNeed);
}

HWTEST_F(
    CellularCallSupplementTest, CellularCallSupplementTest_IsNeedMmiToNormalCall_false, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.isNeedMmiToNormalCall_ = IsNeedMmiToNormalCallMockFalse;
    IMSControl control;
    std::string phoneNum = "*100#";
    CLIRMode mode = CLIRMode::DEFAULT;
    bool isNeed = control.IsNeedExecuteMMI(0, phoneNum, mode, true);
    EXPECT_FALSE(isNeed);
}

HWTEST_F(CellularCallSupplementTest, CellularCallSupplementTest_InitTelephonyExtWrapper, Function | MediumTest | Level1)
{
    TELEPHONY_EXT_WRAPPER.InitTelephonyExtWrapper();
    EXPECT_TRUE(TELEPHONY_EXT_WRAPPER.isNeedRemoveMmi_ != nullptr);
    EXPECT_TRUE(TELEPHONY_EXT_WRAPPER.isNeedMmiToNormalCall_ != nullptr);
    EXPECT_TRUE(TELEPHONY_EXT_WRAPPER.isUssdOkForRelease_ != nullptr);
    EXPECT_TRUE(TELEPHONY_EXT_WRAPPER.mmiCodeUnescapehtml_ != nullptr);
    TELEPHONY_EXT_WRAPPER.~TelephonyExtWrapper();
    TELEPHONY_EXT_WRAPPER.InitTelephonyExtWrapper();
}

HWTEST_F(
    CellularCallSupplementTest, CellularCallSupplementTest_InitTelephonyExtWrapper_fail, Function | MediumTest | Level1)
{
    std::string filePath = "/system/lib64/libtelephony_ext_service.z.so";
    std::string bakFilePath = "/system/lib64/libtelephony_ext_service.z.so.bak";
    RenameFile(filePath, bakFilePath);
    TELEPHONY_EXT_WRAPPER.InitTelephonyExtWrapper();
    EXPECT_TRUE(TELEPHONY_EXT_WRAPPER.isNeedRemoveMmi_ == nullptr);
    EXPECT_TRUE(TELEPHONY_EXT_WRAPPER.isNeedMmiToNormalCall_ == nullptr);
    EXPECT_TRUE(TELEPHONY_EXT_WRAPPER.isUssdOkForRelease_ == nullptr);
    EXPECT_TRUE(TELEPHONY_EXT_WRAPPER.mmiCodeUnescapehtml_ == nullptr);
    TELEPHONY_EXT_WRAPPER.~TelephonyExtWrapper();
    RenameFile(bakFilePath, filePath);
    TELEPHONY_EXT_WRAPPER.InitTelephonyExtWrapper();
}

}  // namespace Telephony
}  // namespace OHOS