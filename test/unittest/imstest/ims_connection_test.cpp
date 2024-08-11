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
#include "cellular_call_connection_ims.h"
#include "cellular_call_connection_satellite.h"
#include "call_manager_base.h"
#include "cellular_call_service.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
class ImsConnectionTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};
void ImsConnectionTest::SetUpTestCase() {}

void ImsConnectionTest::TearDownTestCase() {}

void ImsConnectionTest::SetUp() {}

void ImsConnectionTest::TearDown() {}
/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0001
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0001, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    std::string phoneNum;
    int32_t index = 0;
    int32_t ret = cellularCallConnectionIMS->HangUpRequest(slotId, phoneNum, index);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0002
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0002, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    std::string phoneNum;
    int32_t index = 0;
    int32_t videoState = 0;
    int32_t ret = cellularCallConnectionIMS->AnswerRequest(slotId, phoneNum, videoState, index);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0003
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0003, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    std::string phoneNum;
    int32_t index = 0;
    int32_t ret = cellularCallConnectionIMS->RejectRequest(slotId, phoneNum, index);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0004
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0004, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    int32_t ret = cellularCallConnectionIMS->HoldCallRequest(slotId);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0005
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0005, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    int32_t ret = cellularCallConnectionIMS->UnHoldCallRequest(slotId);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0006
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0006, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    int32_t voiceCall = 0;
    int32_t ret = cellularCallConnectionIMS->CombineConferenceRequest(slotId, voiceCall);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0007
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0007, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    std::vector<std::string> numberList;
    int32_t ret = cellularCallConnectionIMS->InviteToConferenceRequest(slotId, numberList);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0008
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0008, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    int32_t index = 0;
    int32_t ret = cellularCallConnectionIMS->KickOutFromConferenceRequest(slotId, index);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0009
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0009, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    int32_t ret = cellularCallConnectionIMS->SwitchCallRequest(slotId);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0010
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0010, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    int64_t lastCallsDataFlag = 0;
    int32_t ret = cellularCallConnectionIMS->GetImsCallsDataRequest(slotId, lastCallsDataFlag);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0011
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0011, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    int32_t lastCallsDataFlag = 0;
    char cDtmfCode = 0;
    int32_t ret = cellularCallConnectionIMS->SendDtmfRequest(slotId, cDtmfCode, lastCallsDataFlag);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0012
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0012, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    int32_t lastCallsDataFlag = 0;
    char cDtmfCode = 0;
    int32_t ret = cellularCallConnectionIMS->StartDtmfRequest(slotId, cDtmfCode, lastCallsDataFlag);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0013
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0013, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    int32_t index = 0;
    int32_t ret = cellularCallConnectionIMS->StopDtmfRequest(slotId, index);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0014
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0014, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    std::string msg;
    int32_t ret = cellularCallConnectionIMS->StartRttRequest(slotId, msg);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0015
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0015, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    int32_t ret = cellularCallConnectionIMS->StopRttRequest(slotId);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0016
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0016, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    int32_t ret = cellularCallConnectionIMS->GetCallFailReasonRequest(slotId);
    EXPECT_EQ(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0017
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0017, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    int32_t slotId = 0;
    char c = 0;
    int32_t ret = cellularCallConnectionIMS->ProcessPostDialCallChar(slotId, c);
    EXPECT_EQ(ret, TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0018
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0018, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    EXPECT_FALSE(cellularCallConnectionIMS->IsNeedToDial());
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0019
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0019, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    bool isNeedToDial = false;
    cellularCallConnectionIMS->SetDialFlag(isNeedToDial);
    EXPECT_EQ(cellularCallConnectionIMS->isNeedToDial_, 0);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIMSTest_0021
 * @tc.name     Test CellularCallConnectionIMS
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionIMSTest_0021, Function | MediumTest | Level1)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    EXPECT_FALSE(cellularCallConnectionIMS->IsPendingHold());
}

/**
 * @tc.number   Telephony_CellularCallConnectionSatelliteTest_0001
 * @tc.name     Test CellularCallConnectionSatellite
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionSatelliteTest_0001, Function | MediumTest | Level1)
{
    auto cellularCallconnerctionSatellite = std::make_shared<CellularCallConnectionSatellite>();
    int32_t slotId = 0;
    int32_t index = 0;
    int32_t ret = cellularCallconnerctionSatellite->SendDtmfRequest(slotId, '1', index);
    EXPECT_NE(ret, TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallConnectionSatelliteTest_0002
 * @tc.name     Test CellularCallConnectionSatellite
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionSatelliteTest_0002, Function | MediumTest | Level1)
{
    auto cellularCallconnerctionSatellite = std::make_shared<CellularCallConnectionSatellite>();
    int32_t slotId = 0;
    int32_t index = 0;
    int32_t ret = cellularCallconnerctionSatellite->SendDtmfRequest(slotId, '1', index);
    EXPECT_NE(ret, TELEPHONY_ERROR);
    auto handle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
    EXPECT_EQ(handle, nullptr);
}

/**
 * @tc.number   Telephony_CellularCallConnectionSatelliteTest_0003
 * @tc.name     Test CellularCallConnectionSatellite
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionSatelliteTest_0003, Function | MediumTest | Level1)
{
    auto cellularCallconnerctionSatellite = std::make_shared<CellularCallConnectionSatellite>();
    int32_t slotId = 0;
    int32_t index = 0;
    int32_t ret = cellularCallconnerctionSatellite->StartDtmfRequest(slotId, '1', index);
    EXPECT_NE(ret, TELEPHONY_ERROR);

    auto handle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
    EXPECT_EQ(handle, nullptr);
}

/**
 * @tc.number   Telephony_CellularCallConnectionSatelliteTest_0004
 * @tc.name     Test CellularCallConnectionSatellite
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionSatelliteTest_0004, Function | MediumTest | Level1)
{
    auto cellularCallconnerctionSatellite = std::make_shared<CellularCallConnectionSatellite>();
    int32_t slotId = 0;
    int32_t index = 0;
    int32_t ret = cellularCallconnerctionSatellite->StopDtmfRequest(slotId, index);
    EXPECT_NE(ret, TELEPHONY_ERROR);

    auto handle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
    EXPECT_EQ(handle, nullptr);
}

/**
 * @tc.number   Telephony_CellularCallConnectionSatelliteTest_0005
 * @tc.name     Test CellularCallConnectionSatellite
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionSatelliteTest_0005, Function | MediumTest | Level1)
{
    auto cellularCallconnerctionSatellite = std::make_shared<CellularCallConnectionSatellite>();
    int32_t slotId = 0;
    int32_t ret = cellularCallconnerctionSatellite->ProcessPostDialCallChar(slotId, '1');
    EXPECT_EQ(ret, TELEPHONY_SUCCESS);

    auto handle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
    EXPECT_EQ(handle, nullptr);
}

/**
 * @tc.number   Telephony_ImsBaseConnectionTest_0001
 * @tc.name     Test BaseConnection
 * @tc.desc     Function test GetState
 */
HWTEST_F(ImsConnectionTest, BaseConnectionTest_0001, Function | MediumTest | Level1)
{
    BaseConnection baseConnection;
    baseConnection.SetStatus(TelCallState::CALL_STATUS_DIALING);
    EXPECT_EQ(baseConnection.GetStatus(), TelCallState::CALL_STATUS_DIALING);
}

/**
 * @tc.number   Telephony_ImsBaseConnectionTest_0002
 * @tc.name     Test BaseConnection
 * @tc.desc     Function test IsRingingState
 */
HWTEST_F(ImsConnectionTest, BaseConnectionTest_0002, Function | MediumTest | Level1)
{
    BaseConnection baseConnection;
    baseConnection.SetStatus(TelCallState::CALL_STATUS_DIALING);
    EXPECT_FALSE(baseConnection.IsRingingState());

    baseConnection.SetStatus(TelCallState::CALL_STATUS_WAITING);
    EXPECT_TRUE(baseConnection.IsRingingState());

    baseConnection.SetStatus(TelCallState::CALL_STATUS_ALERTING);
    EXPECT_TRUE(baseConnection.IsRingingState());
}

/**
 * @tc.number   Telephony_ImsBaseConnectionTest_0003
 * @tc.name     Test BaseConnection
 * @tc.desc     Function test GetFlag and SetFlag
 */
HWTEST_F(ImsConnectionTest, BaseConnectionTest_0003, Function | MediumTest | Level1)
{
    BaseConnection baseConnection;
    baseConnection.SetFlag(true);
    EXPECT_EQ(baseConnection.GetFlag(), true);
}

/**
 * @tc.number   Telephony_ImsBaseConnectionTest_0004
 * @tc.name     Test BaseConnection
 * @tc.desc     Function test GetNumber
 */
HWTEST_F(ImsConnectionTest, BaseConnectionTest_0004, Function | MediumTest | Level1)
{
    BaseConnection baseConnection;
    baseConnection.SetNumber("1234567890");
    EXPECT_EQ(baseConnection.GetNumber(), "1234567890");
}

/**
 * @tc.number   Telephony_ImsBaseConnectionTest_0005
 * @tc.name     Test BaseConnection
 * @tc.desc     Function test GetNumber
 */
HWTEST_F(ImsConnectionTest, BaseConnectionTest_0005, Function | MediumTest | Level1)
{
    BaseConnection baseConnection;
    baseConnection.SetNumber("1234567890");
    EXPECT_EQ(baseConnection.GetNumber(), "1234567890");
}

/**
 * @tc.number   Telephony_ImsBaseConnectionTest_0006
 * @tc.name     Test BaseConnection
 * @tc.desc     Function test UpdatePendingHoldFlag
 */
HWTEST_F(ImsConnectionTest, BaseConnectionTest_0006, Function | MediumTest | Level1)
{
    BaseConnection baseConnection;
    baseConnection.UpdatePendingHoldFlag(true);
    EXPECT_EQ(baseConnection.GetCallReportInfo().isPendingHold, true);
}

/**
 * @tc.number   Telephony_ImsBaseConnectionTest_0007
 * @tc.name     Test BaseConnection
 * @tc.desc     Function test ProcessPostDialCallChar
 */
HWTEST_F(ImsConnectionTest, BaseConnectionTest_0007, Function | MediumTest | Level1)
{
    BaseConnection baseConnection;
    int32_t slotId = 0;
    char c = 'B';
    EXPECT_EQ(baseConnection.ProcessPostDialCallChar(slotId, c), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_ImsBaseConnectionTest_0008
 * @tc.name     Test BaseConnection
 * @tc.desc     Function test GetLeftPostDialCallString
 */
HWTEST_F(ImsConnectionTest, BaseConnectionTest_0008, Function | MediumTest | Level1)
{
    BaseConnection baseConnection;
    EXPECT_EQ(baseConnection.GetLeftPostDialCallString(), "");

    baseConnection.SetPostDialCallState(PostDialCallState::POST_DIAL_CALL_NOT_STARTED);
    std::string phoneString = "13363669099,123321";
    baseConnection.UpdateCallNumber(phoneString);
    EXPECT_NE(baseConnection.GetLeftPostDialCallString(), "13363669099");
}

/**
 * @tc.number   Telephony_ImsBaseConnectionTest_0009
 * @tc.name     Test BaseConnection
 * @tc.desc     Function test ProcessNextChar
 */
HWTEST_F(ImsConnectionTest, BaseConnectionTest_0009, Function | MediumTest | Level1)
{
    BaseConnection baseConnection;
    baseConnection.SetPostDialCallState(PostDialCallState::POST_DIAL_CALL_CANCELED);
    int32_t slotId = 0;
    char c = 'B';
    EXPECT_EQ(baseConnection.ProcessNextChar(slotId, c), PostDialCallState::POST_DIAL_CALL_CANCELED);

    baseConnection.SetPostDialCallState(PostDialCallState::POST_DIAL_CALL_NOT_STARTED);
    EXPECT_EQ(baseConnection.ProcessNextChar(slotId, c), PostDialCallState::POST_DIAL_CALL_COMPLETE);

    baseConnection.SetPostDialCallState(PostDialCallState::POST_DIAL_CALL_NOT_STARTED);
    std::string phoneString = "13363669099,123321";
    baseConnection.UpdateCallNumber(phoneString);
    EXPECT_NE(baseConnection.ProcessNextChar(slotId, c), PostDialCallState::POST_DIAL_CALL_CANCELED);
}

/**
 * @tc.number   Telephony_SupplementRequestImsTest_0001
 * @tc.name     Test SupplementRequestIms
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, SupplementRequestImsTest_0001, Function | MediumTest | Level1)
{
    SupplementRequestIms supplementRequestIms;
    int32_t slotId = 0;
    int32_t index = 0;
    int32_t ret = supplementRequestIms.GetClipRequest(slotId, index);
    EXPECT_NE(ret, CALL_ERR_RESOURCE_UNAVAILABLE);
}

/**
 * @tc.number   Telephony_SupplementRequestImsTest_0002
 * @tc.name     Test SupplementRequestIms
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, SupplementRequestImsTest_0002, Function | MediumTest | Level1)
{
    SupplementRequestIms supplementRequestIms;
    int32_t slotId = 0;
    int32_t reason = 0;
    int32_t index = 0;
    int32_t ret = supplementRequestIms.GetCallTransferRequest(slotId, reason, index);
    EXPECT_NE(ret, CALL_ERR_RESOURCE_UNAVAILABLE);
}

/**
 * @tc.number   Telephony_SupplementRequestImsTest_0003
 * @tc.name     Test SupplementRequestIms
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, SupplementRequestImsTest_0003, Function | MediumTest | Level1)
{
    SupplementRequestIms supplementRequestIms;
    int32_t slotId = 0;
    int32_t reason = 0;
    CallTransferInfo cfInfo;
    int32_t index = 0;
    int32_t ret = supplementRequestIms.SetCallTransferRequest(slotId, cfInfo, reason, index);
    EXPECT_NE(ret, CALL_ERR_RESOURCE_UNAVAILABLE);
}

/**
 * @tc.number   Telephony_SupplementRequestImsTest_0004
 * @tc.name     Test SupplementRequestIms
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, SupplementRequestImsTest_0004, Function | MediumTest | Level1)
{
    SupplementRequestIms supplementRequestIms;
    int32_t slotId = 0;
    bool result = false;
    int32_t ret = supplementRequestIms.CanSetCallTransferTime(slotId, result);
    EXPECT_NE(ret, CALL_ERR_RESOURCE_UNAVAILABLE);
}

/**
 * @tc.number   Telephony_SupplementRequestImsTest_0005
 * @tc.name     Test SupplementRequestIms
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, SupplementRequestImsTest_0005, Function | MediumTest | Level1)
{
    SupplementRequestIms supplementRequestIms;
    int32_t slotId = 0;
    int32_t reason = 0;
    int32_t index = 0;
    int32_t ret = supplementRequestIms.GetCallTransferRequest(slotId, reason, index);
    EXPECT_NE(ret, CALL_ERR_RESOURCE_UNAVAILABLE);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0001
 * @tc.name     Test CellularCallConnectionCS HangUpRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0001, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    int32_t ret = cellularCallConnectionCS.HangUpRequest(slotId);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);

    slotId = -1;
    ret = cellularCallConnectionCS.HangUpRequest(slotId);
    EXPECT_EQ(ret, CALL_ERR_RESOURCE_UNAVAILABLE);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0002
 * @tc.name     Test CellularCallConnectionCS AnswerRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0002, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    int32_t ret = cellularCallConnectionCS.AnswerRequest(slotId);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);

    slotId = -1;
    ret = cellularCallConnectionCS.AnswerRequest(slotId);
    EXPECT_EQ(ret, CALL_ERR_RESOURCE_UNAVAILABLE);
}


/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0003
 * @tc.name     Test CellularCallConnectionCS RejectRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0003, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    int32_t ret = cellularCallConnectionCS.RejectRequest(slotId);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0004
 * @tc.name     Test CellularCallConnectionCS HoldRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0004, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    int32_t ret = cellularCallConnectionCS.HoldRequest(slotId);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0005
 * @tc.name     Test CellularCallConnectionCS UnHoldRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0005, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    int32_t ret = cellularCallConnectionCS.UnHoldCallRequest(slotId);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0006
 * @tc.name     Test CellularCallConnectionCS SwitchCallRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0006, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    int32_t ret = cellularCallConnectionCS.SwitchCallRequest(slotId);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0007
 * @tc.name     Test CellularCallConnectionCS CombineConferenceRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0007, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    int32_t voiceCall = 0;
    int32_t ret = cellularCallConnectionCS.CombineConferenceRequest(slotId, voiceCall);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);

    slotId = -1;
    ret = cellularCallConnectionCS.CombineConferenceRequest(slotId, voiceCall);
    EXPECT_EQ(ret, CALL_ERR_RESOURCE_UNAVAILABLE);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0008
 * @tc.name     Test CellularCallConnectionCS SeparateConferenceRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0008, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    int32_t voiceCall = 0;
    int32_t index = 0;
    int32_t ret = cellularCallConnectionCS.SeparateConferenceRequest(slotId, index, voiceCall);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);

    slotId = -1;
    ret = cellularCallConnectionCS.SeparateConferenceRequest(slotId, index, voiceCall);
    EXPECT_EQ(ret, CALL_ERR_RESOURCE_UNAVAILABLE);
}
/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0009
 * @tc.name     Test CellularCallConnectionCS CallSupplementRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0009, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    CallSupplementType type = CallSupplementType::TYPE_DEFAULT;
    int32_t ret = cellularCallConnectionCS.CallSupplementRequest(slotId, type);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0010
 * @tc.name     Test CellularCallConnectionCS SendCDMAThreeWayDialRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0010, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    int32_t slotId = 0;
    int32_t ret = cellularCallConnectionCS.SendCDMAThreeWayDialRequest(slotId);
    EXPECT_EQ(ret, TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0011
 * @tc.name     Test CellularCallConnectionCS SeparateConferenceRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0011, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    int32_t index = 0;
    char cDtmfCode = '0';
    int32_t ret = cellularCallConnectionCS.SendDtmfRequest(slotId, cDtmfCode, index);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0012
 * @tc.name     Test CellularCallConnectionCS StartDtmfRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0012, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    int32_t index = 0;
    char cDtmfCode = '0';
    int32_t ret = cellularCallConnectionCS.StartDtmfRequest(slotId, cDtmfCode, index);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0013
 * @tc.name     Test CellularCallConnectionCS StopDtmfRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0013, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    int32_t index = 0;
    int32_t ret = cellularCallConnectionCS.StopDtmfRequest(slotId, index);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0014
 * @tc.name     Test CellularCallConnectionCS GetCsCallsDataRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0014, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    int64_t lastCallsDataFlag = 0;
    int32_t ret = cellularCallConnectionCS.GetCsCallsDataRequest(slotId, lastCallsDataFlag);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0015
 * @tc.name     Test CellularCallConnectionCS GetCallFailReasonRequest
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0015, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    int32_t ret = cellularCallConnectionCS.GetCallFailReasonRequest(slotId);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallConnectionCSTest_0016
 * @tc.name     Test CellularCallConnectionCS ProcessPostDialCallChar
 * @tc.desc     Function test
 */
HWTEST_F(ImsConnectionTest, CellularCallConnectionCSTest_0016, Function | MediumTest | Level1)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    int32_t slotId = 0;
    char c = '0';
    int32_t ret = cellularCallConnectionCS.ProcessPostDialCallChar(slotId, c);
    EXPECT_EQ(ret, TELEPHONY_SUCCESS);

    c = ',';
    slotId = -1;
    ret = cellularCallConnectionCS.ProcessPostDialCallChar(slotId, c);
    EXPECT_EQ(ret, CALL_ERR_RESOURCE_UNAVAILABLE);

    slotId = 0;
    ret = cellularCallConnectionCS.ProcessPostDialCallChar(slotId, c);
    EXPECT_NE(ret, TELEPHONY_SUCCESS);

    c = ';';
    ret = cellularCallConnectionCS.ProcessPostDialCallChar(slotId, c);
    EXPECT_EQ(ret, TELEPHONY_SUCCESS);
}
} // namespace Telephony
} // namespace OHOS
