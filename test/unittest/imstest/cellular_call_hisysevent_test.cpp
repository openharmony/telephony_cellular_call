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
#include "base_request.h"
#include "cellular_call_hisysevent.h"
#include "core_manager_inner.h"
#include "core_manager_inner.h"
#include "supplement_request_cs.h"
#include "supplement_request_ims.h"
#include "telephony_hisysevent.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;

static const int32_t INVALID_VALUE = -1;
static const int32_t CS_CALL_TYPE = 0;
static const int32_t IMS_CALL_TYPE = 1;
static const int32_t VOICE_TYPE = 0;
static const int32_t VIDEO_TYPE = 1;

class CellularCallHiSysEventTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};
void CellularCallHiSysEventTest::SetUpTestCase() {}

void CellularCallHiSysEventTest::TearDownTestCase() {}

void CellularCallHiSysEventTest::SetUp() {}

void CellularCallHiSysEventTest::TearDown() {}

/**
 * @tc.number   Telephony_CellularCallHiSysEventTest_0001
 * @tc.name     Test CellularCallHiSysEvent
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, CellularCallHiSysEventTest_0001, Function | MediumTest | Level1)
{
    std::shared_ptr<CellularCallHiSysEvent> cellularCallHiSysEvent = std::make_shared<CellularCallHiSysEvent>();
    cellularCallHiSysEvent->WriteFoundationRestartFaultEvent(2);
    cellularCallHiSysEvent->WriteCallEndBehaviorEvent(0, 17);

    CallBehaviorParameterInfo callInfo = {.callType = IMS_CALL_TYPE, .videoState = VOICE_TYPE};
    CallResponseResult result = CallResponseResult::COMMAND_FAILURE;
    cellularCallHiSysEvent->WriteDialCallBehaviorEvent(callInfo, result);

    callInfo.videoState = VIDEO_TYPE;
    cellularCallHiSysEvent->WriteDialCallBehaviorEvent(callInfo, result);

    callInfo.callType = INVALID_VALUE;
    cellularCallHiSysEvent->WriteDialCallBehaviorEvent(callInfo, result);

    callInfo.videoState = VOICE_TYPE;
    cellularCallHiSysEvent->WriteDialCallBehaviorEvent(callInfo, result);

    callInfo = {.callType = IMS_CALL_TYPE, .videoState = VOICE_TYPE};
    result = CallResponseResult::COMMAND_FAILURE;
    cellularCallHiSysEvent->WriteHangUpCallBehaviorEvent(callInfo, result);

    callInfo.videoState = VIDEO_TYPE;
    cellularCallHiSysEvent->WriteHangUpCallBehaviorEvent(callInfo, result);

    callInfo.callType = INVALID_VALUE;
    cellularCallHiSysEvent->WriteHangUpCallBehaviorEvent(callInfo, result);

    callInfo.videoState = VOICE_TYPE;
    cellularCallHiSysEvent->WriteHangUpCallBehaviorEvent(callInfo, result);

    int32_t slotId = 0; 
    int32_t callType = CS_CALL_TYPE;
    int32_t videoState = VOICE_TYPE;
    int32_t errCode = static_cast<int32_t>(TELEPHONY_ERR_MEMCPY_FAIL);
    std::string desc;
    CallErrorCode value = CallErrorCode::CALL_ERROR_NONE;
    cellularCallHiSysEvent->WriteIncomingCallFaultEvent(slotId, callType, videoState, errCode, desc);
    EXPECT_TRUE(cellularCallHiSysEvent->ErrorCodeConversion(errCode, value));
}

/**
 * @tc.number   Telephony_CellularCallHiSysEventTest_0003
 * @tc.name     Test CellularCallHiSysEvent
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, CellularCallHiSysEventTest_0003, Function | MediumTest | Level1)
{
    std::shared_ptr<CellularCallHiSysEvent> cellularCallHiSysEvent = std::make_shared<CellularCallHiSysEvent>();

    CallBehaviorParameterInfo callInfo = {.callType = IMS_CALL_TYPE, .videoState = VOICE_TYPE,
        .incomingCallType = IMS_CALL_TYPE, .incomingVideoState = VOICE_TYPE};
    CallResponseResult result = CallResponseResult::COMMAND_FAILURE;
    cellularCallHiSysEvent->WriteAnswerCallBehaviorEvent(callInfo, result);

    callInfo.incomingVideoState = VIDEO_TYPE;
    cellularCallHiSysEvent->WriteAnswerCallBehaviorEvent(callInfo, result);

    callInfo.videoState = VIDEO_TYPE;
    cellularCallHiSysEvent->WriteAnswerCallBehaviorEvent(callInfo, result);

    CallBehaviorParameterInfo callInfo1 = {.callType = CS_CALL_TYPE, .videoState = VOICE_TYPE,
        .incomingCallType = CS_CALL_TYPE, .incomingVideoState = VOICE_TYPE};
    cellularCallHiSysEvent->WriteAnswerCallBehaviorEvent(callInfo1, result);

    cellularCallHiSysEvent->WriteVoNRSwitchChangeEvent(0);
    cellularCallHiSysEvent->WriteVoNRSwitchChangeEvent(1);

    int32_t slotId = 0;
    int32_t callType = CS_CALL_TYPE;
    int32_t videoState = VOICE_TYPE; 
    int32_t errCode = 100;
    std::string desc;
    CallErrorCode value = CallErrorCode::CALL_ERROR_NONE;
    cellularCallHiSysEvent->WriteIncomingCallFaultEvent(slotId, callType, videoState, errCode, desc);
    EXPECT_FALSE(cellularCallHiSysEvent->
    ErrorCodeConversion(errCode, value));
}

/**
 * @tc.number   Telephony_CellularCallHiSysEventTest_0004
 * @tc.name     Test CellularCallHiSysEvent TelephonyErrorCodeConversion
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, CellularCallHiSysEventTest_0004, Function | MediumTest | Level1)
{
    std::shared_ptr<CellularCallHiSysEvent> cellularCallHiSysEvent = std::make_shared<CellularCallHiSysEvent>();
    int32_t errCode = static_cast<int32_t>(TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL);
    CallErrorCode eventValue;
    int32_t ret = cellularCallHiSysEvent->TelephonyErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_IPC_WRITE_DESCRIPTOR_TOKEN_FAIL);

    errCode = static_cast<int32_t>(TELEPHONY_ERR_WRITE_DATA_FAIL);
    ret = cellularCallHiSysEvent->TelephonyErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_IPC_WRITE_DATA_FAIL);

    errCode = static_cast<int32_t>(TELEPHONY_ERR_PERMISSION_ERR);
    ret = cellularCallHiSysEvent->TelephonyErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_PERMISSION_ERR);

    errCode = static_cast<int32_t>(TELEPHONY_ERR_MEMSET_FAIL);
    ret = cellularCallHiSysEvent->TelephonyErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_MEMSET_FAIL);

    errCode = static_cast<int32_t>(TELEPHONY_ERR_MEMCPY_FAIL);
    ret = cellularCallHiSysEvent->TelephonyErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_MEMCPY_FAIL);

    errCode = 100;
    ret = cellularCallHiSysEvent->TelephonyErrorCodeConversion(errCode, eventValue);
    EXPECT_FALSE(ret);
}

/**
 * @tc.number   Telephony_CellularCallHiSysEventTest_0005
 * @tc.name     Test CellularCallHiSysEvent
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, CellularCallHiSysEventTest_0005, Function | MediumTest | Level1)
{
    std::shared_ptr<CellularCallHiSysEvent> cellularCallHiSysEvent = std::make_shared<CellularCallHiSysEvent>();
    CallBehaviorParameterInfo info = {.callType = CS_CALL_TYPE, .videoState = VOICE_TYPE,
         .incomingCallType = CS_CALL_TYPE, .incomingVideoState = VOICE_TYPE};

    CallModeBehaviorType type = CallModeBehaviorType::SEND_REQUEST_EVENT;
    int32_t requestResult = INVALID_VALUE;
    cellularCallHiSysEvent->WriteImsCallModeBehaviorEvent(type, info, requestResult);
    requestResult = CS_CALL_TYPE;
    cellularCallHiSysEvent->WriteImsCallModeBehaviorEvent(type, info, requestResult);
    requestResult = IMS_CALL_TYPE;
    cellularCallHiSysEvent->WriteImsCallModeBehaviorEvent(type, info, requestResult);

    type = CallModeBehaviorType::SEND_RESPONSE_EVENT;
    requestResult = INVALID_VALUE;
    cellularCallHiSysEvent->WriteImsCallModeBehaviorEvent(type, info, requestResult);
    requestResult = CS_CALL_TYPE;
    cellularCallHiSysEvent->WriteImsCallModeBehaviorEvent(type, info, requestResult);
    requestResult = IMS_CALL_TYPE;
    cellularCallHiSysEvent->WriteImsCallModeBehaviorEvent(type, info, requestResult);

    type = CallModeBehaviorType::RECEIVE_REQUEST_EVENT;
    requestResult = INVALID_VALUE;
    cellularCallHiSysEvent->WriteImsCallModeBehaviorEvent(type, info, requestResult);
    requestResult = CS_CALL_TYPE;
    cellularCallHiSysEvent->WriteImsCallModeBehaviorEvent(type, info, requestResult);
    requestResult = IMS_CALL_TYPE;
    cellularCallHiSysEvent->WriteImsCallModeBehaviorEvent(type, info, requestResult);

    type = CallModeBehaviorType::RECEIVE_RESPONSE_EVENT;
    requestResult = INVALID_VALUE;
    cellularCallHiSysEvent->WriteImsCallModeBehaviorEvent(type, info, requestResult);
    requestResult = CS_CALL_TYPE;
    cellularCallHiSysEvent->WriteImsCallModeBehaviorEvent(type, info, requestResult);
    requestResult = IMS_CALL_TYPE;
    cellularCallHiSysEvent->WriteImsCallModeBehaviorEvent(type, info, requestResult);

    cellularCallHiSysEvent->SetIncomingCallParameterInfo(IMS_CALL_TYPE, VIDEO_TYPE);
    cellularCallHiSysEvent->GetCallParameterInfo(info);
    EXPECT_EQ(info.incomingCallType, IMS_CALL_TYPE);
    EXPECT_EQ(info.incomingVideoState, VIDEO_TYPE);
}

/**
 * @tc.number   Telephony_CellularCallHiSysEventTest_0008
 * @tc.name     Test CellularCallHiSysEvent CallDataErrorCodeConversion
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, CellularCallHiSysEventTest_0008, Function | MediumTest | Level1)
{
    std::shared_ptr<CellularCallHiSysEvent> cellularCallHiSysEvent = std::make_shared<CellularCallHiSysEvent>();
    int32_t errCode = static_cast<int32_t>(CALL_ERR_INVALID_SLOT_ID);
    CallErrorCode eventValue;
    int32_t ret = cellularCallHiSysEvent->CallDataErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_INVALID_SLOT_ID);

    errCode = static_cast<int32_t>(CALL_ERR_INVALID_CALLID);
    ret = cellularCallHiSysEvent->CallDataErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_INVALID_CALLID);

    errCode = static_cast<int32_t>(CALL_ERR_NUMBER_OUT_OF_RANGE);
    ret = cellularCallHiSysEvent->CallDataErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_NUMBER_OUT_OF_RANGE);

    errCode = static_cast<int32_t>(CALL_ERR_UNSUPPORTED_NETWORK_TYPE);
    ret = cellularCallHiSysEvent->CallDataErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_UNSUPPORTED_NETWORK_TYPE);

    errCode = static_cast<int32_t>(CALL_ERR_INVALID_DIAL_SCENE);
    ret = cellularCallHiSysEvent->CallDataErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_INVALID_DIAL_SCENE);

    errCode = static_cast<int32_t>(CALL_ERR_INVALID_VIDEO_STATE);
    ret = cellularCallHiSysEvent->CallDataErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_INVALID_VIDEO_STATE);

    errCode = static_cast<int32_t>(CALL_ERR_UNKNOW_DIAL_TYPE);
    ret = cellularCallHiSysEvent->CallDataErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_UNKNOW_DIAL_TYPE);

    errCode = static_cast<int32_t>(CALL_ERR_UNKNOW_CALL_TYPE);
    ret = cellularCallHiSysEvent->CallDataErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_UNKNOW_CALL_TYPE);

    errCode = static_cast<int32_t>(CALL_ERR_CALL_OBJECT_IS_NULL);
    ret = cellularCallHiSysEvent->CallDataErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_CALL_OBJECT_IS_NULL);
}

/**
 * @tc.number   Telephony_CellularCallHiSysEventTest_0009
 * @tc.name     Test CellularCallHiSysEvent CallInterfaceErrorCodeConversion
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, CellularCallHiSysEventTest_0009, Function | MediumTest | Level1)
{
    std::shared_ptr<CellularCallHiSysEvent> cellularCallHiSysEvent = std::make_shared<CellularCallHiSysEvent>();
    int32_t errCode = static_cast<int32_t>(CALL_ERR_DIAL_IS_BUSY);
    CallErrorCode eventValue;
    int32_t ret = cellularCallHiSysEvent->CallInterfaceErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_DIAL_IS_BUSY);

    errCode = static_cast<int32_t>(CALL_ERR_ILLEGAL_CALL_OPERATION);
    ret = cellularCallHiSysEvent->CallInterfaceErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_ILLEGAL_CALL_OPERATION);

    errCode = static_cast<int32_t>(CALL_ERR_PHONE_CALLSTATE_NOTIFY_FAILED);
    ret = cellularCallHiSysEvent->CallInterfaceErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_PHONE_CALLSTATE_NOTIFY_FAILED);

    errCode = static_cast<int32_t>(CALL_ERR_SYSTEM_EVENT_HANDLE_FAILURE);
    ret = cellularCallHiSysEvent->CallInterfaceErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_SYSTEM_EVENT_HANDLE_FAILURE);

    errCode = static_cast<int32_t>(CALL_ERR_CALL_COUNTS_EXCEED_LIMIT);
    ret = cellularCallHiSysEvent->CallInterfaceErrorCodeConversion(errCode, eventValue);
    EXPECT_TRUE(ret);
    EXPECT_EQ(eventValue, CallErrorCode::CALL_ERROR_CALL_COUNTS_EXCEED_LIMIT);
}

/**
 * @tc.number   Telephony_CellularCallHiSysEventTest_0011
 * @tc.name     Test CellularCallHiSysEvent SetIncomingStartTime
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, CellularCallHiSysEventTest_0011, Function | MediumTest | Level1)
{
    std::shared_ptr<CellularCallHiSysEvent> cellularCallHiSysEvent = std::make_shared<CellularCallHiSysEvent>();
    int64_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()
        .time_since_epoch()).count();
    cellularCallHiSysEvent->SetIncomingStartTime();
    int64_t stopTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()
        .time_since_epoch()).count();
    EXPECT_TRUE(((stopTime - startTime) >= 0) && ((stopTime - startTime) < NORMAL_INCOMING_TIME));
}

/**
 * @tc.number   Telephony_CellularCallHiSysEventTest_0012
 * @tc.name     Test CellularCallHiSysEvent JudgingIncomingTimeOut
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, CellularCallHiSysEventTest_0012, Function | MediumTest | Level1)
{
    std::shared_ptr<CellularCallHiSysEvent> cellularCallHiSysEvent = std::make_shared<CellularCallHiSysEvent>();

    int64_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()
        .time_since_epoch()).count();
    cellularCallHiSysEvent->SetIncomingStartTime();
    cellularCallHiSysEvent->JudgingIncomingTimeOut(0, CS_CALL_TYPE, VOICE_TYPE);
    int64_t stopTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()
        .time_since_epoch()).count();
    EXPECT_TRUE(((stopTime - startTime) >= 0) && ((stopTime - startTime) < NORMAL_INCOMING_TIME));

    startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()
        .time_since_epoch()).count();
    cellularCallHiSysEvent->SetIncomingStartTime();
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    cellularCallHiSysEvent->JudgingIncomingTimeOut(0, CS_CALL_TYPE, VOICE_TYPE);
    stopTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()
        .time_since_epoch()).count();
    EXPECT_TRUE((stopTime - startTime) > NORMAL_INCOMING_TIME);
}

/**
 * @tc.number   Telephony_CellularCallHiSysEventTest_0013
 * @tc.name     Test CellularCallHiSysEvent CallParameterInfo set and get
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, CellularCallHiSysEventTest_0013, Function | MediumTest | Level1)
{
    std::shared_ptr<CellularCallHiSysEvent> cellularCallHiSysEvent = std::make_shared<CellularCallHiSysEvent>();

    CallForwardingInfo info;
    int32_t slotId = 0;  
    bool enable = true;
    std::string number = "10086";

    cellularCallHiSysEvent->SetCallForwardingInfo(slotId, enable, number);
    cellularCallHiSysEvent->GetCallForwardingInfo(info);
    EXPECT_EQ(info.slotId, slotId);
    EXPECT_EQ(info.enable, enable);
    EXPECT_EQ(info.number, number);
}

/**
 * @tc.number   Telephony_SupplementRequestImsTest_0001
 * @tc.name     Test SupplementRequestImsTest
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, SupplementRequestImsTest_0001, Function | MediumTest | Level1)
{
    SupplementRequestIms supplementRequestIms;
    int32_t slotId = 0;
    std::string fac;
    int32_t mode = 0;
    std::string pw;
    int32_t index = 0;
    int32_t ret = supplementRequestIms.SetCallRestrictionRequest(slotId, fac, mode, pw, index);
    EXPECT_EQ(ret, TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
}

/**
 * @tc.number   Telephony_SupplementRequestImsTest_0002
 * @tc.name     Test SupplementRequestImsTest
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, SupplementRequestImsTest_0002, Function | MediumTest | Level1)
{
    SupplementRequestIms supplementRequestIms;
    int32_t slotId = 0;
    bool activate = false;
    int32_t classType = 0;
    int32_t index = 0;
    int32_t ret = supplementRequestIms.SetCallWaitingRequest(slotId, activate, classType, index);
    EXPECT_EQ(ret, TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
}

/**
 * @tc.number   Telephony_SupplementRequestImsTest_0003
 * @tc.name     Test SupplementRequestImsTest
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, SupplementRequestImsTest_0003, Function | MediumTest | Level1)
{
    SupplementRequestIms supplementRequestIms;
    int32_t slotId = 0;
    int32_t index = 0;
    int32_t ret = supplementRequestIms.GetCallWaitingRequest(slotId, index);
    EXPECT_EQ(ret, TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
}

/**
 * @tc.number   Telephony_SupplementRequestImsTest_0004
 * @tc.name     Test SupplementRequestImsTest
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, SupplementRequestImsTest_0004, Function | MediumTest | Level1)
{
    SupplementRequestIms supplementRequestIms;
    int32_t slotId = 0;
    int32_t presentation = 0;
    int32_t index = 0;
    int32_t ret = supplementRequestIms.SetColrRequest(slotId, presentation, index);
    EXPECT_EQ(ret, TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
}

/**
 * @tc.number   Telephony_SupplementRequestImsTest_0005
 * @tc.name     Test SupplementRequestImsTest
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, SupplementRequestImsTest_0005, Function | MediumTest | Level1)
{
    SupplementRequestIms supplementRequestIms;
    int32_t slotId = 0;
    int32_t index = 0;
    int32_t ret = supplementRequestIms.GetColrRequest(slotId, index);
    EXPECT_EQ(ret, TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
}

/**
 * @tc.number   Telephony_SupplementRequestImsTest_0006
 * @tc.name     Test SupplementRequestImsTest
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, SupplementRequestImsTest_0006, Function | MediumTest | Level1)
{
    SupplementRequestIms supplementRequestIms;
    int32_t slotId = 0;
    int32_t action = 0;
    int32_t index = 0;
    auto point = supplementRequestIms.GetMMIHandler(slotId);
    int32_t ret = supplementRequestIms.SetColpRequest(slotId, action, index);
    EXPECT_EQ(ret, TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
}

/**
 * @tc.number   Telephony_SupplementRequestCsTest_0001
 * @tc.name     Test SupplementRequestCsTest
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, SupplementRequestCsTest_0001, Function | MediumTest | Level1)
{
    SupplementRequestCs supplementRequestCs;
    int32_t slotId = 0;
    std::string msg;
    auto ret = supplementRequestCs.SendUssdRequest(slotId, msg);
    EXPECT_EQ(ret, TELEPHONY_ERR_LOCAL_PTR_NULL);

    slotId = -1;
    ret = supplementRequestCs.SendUssdRequest(slotId, msg);
    EXPECT_NE(ret, TELEPHONY_ERR_ARGUMENT_INVALID);
}

/**
 * @tc.number   Telephony_SupplementRequestCsTest_0002
 * @tc.name     Test SupplementRequestCsTest
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallHiSysEventTest, SupplementRequestCsTest_0002, Function | MediumTest | Level1)
{
    SupplementRequestCs supplementRequestCs;
    int32_t slotId = 0;
    auto ret = supplementRequestCs.CloseUnFinishedUssdRequest(slotId);
    EXPECT_EQ(ret, TELEPHONY_ERR_LOCAL_PTR_NULL);

    CoreManagerInner::GetInstance().telRilManager_ = nullptr;
    ret = supplementRequestCs.CloseUnFinishedUssdRequest(slotId);
    EXPECT_EQ(ret, TELEPHONY_ERR_LOCAL_PTR_NULL);
}
} // namespace Telephony
} // namespace OHOS