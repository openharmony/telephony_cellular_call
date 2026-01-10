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
#include "cellular_call_stub.h"
#include "cellular_call_service.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
class CellularCallStubTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void CellularCallStubTest::SetUpTestCase() {}

void CellularCallStubTest::TearDownTestCase() {}

void CellularCallStubTest::SetUp() {}

void CellularCallStubTest::TearDown() {}

/**
 * @tc.number   Telephony_CellularCallStubTest_0001
 * @tc.name     Test CellularCallStub
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallStubTest, CellularCallStubTest_0001, Function | MediumTest | Level1)
{
    CellularCallService cellularCallStub;
    MessageParcel data;
    MessageParcel reply;
    data.WriteInt32(50);
    EXPECT_NE(cellularCallStub.OnDialInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnHangUpInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnRejectInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnAnswerInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnIsEmergencyPhoneNumberInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetEmergencyCallList(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnUnRegisterCallBackInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnHoldCallInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnUnHoldCallInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSwitchCallInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnCombineConferenceInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSeparateConferenceInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnInviteToConferenceInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnKickOutFromConferenceInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnHangUpAllConnectionInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(cellularCallStub.OnSetReadyToCallInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSendUpdateCallMediaModeRequestInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSendUpdateCallMediaModeResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnCancelCallUpgradeInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnIsMmiCodeInner(data, reply), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallStubTest_0002
 * @tc.name     Test CellularCallStub
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallStubTest, CellularCallStubTest_0002, Function | MediumTest | Level1)
{
    CellularCallService cellularCallStub;
    MessageParcel data;
    MessageParcel reply;
    data.WriteInt32(50);
    EXPECT_NE(cellularCallStub.OnRequestCameraCapabilitiesInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnStartDtmfInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnStopDtmfInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnPostDialProceedInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSendDtmfInner(data, reply), TELEPHONY_SUCCESS);
#ifdef SUPPORT_RTT_CALL
    EXPECT_NE(cellularCallStub.OnUpdateImsRttCallModeInner(data, reply), TELEPHONY_SUCCESS);
#endif
    EXPECT_NE(cellularCallStub.OnSetCallTransferInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnCanSetCallTransferTimeInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnGetCallTransferInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetCallWaitingInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnGetCallWaitingInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetCallRestrictionInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnGetCallRestrictionInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetCallRestrictionPasswordInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetDomainPreferenceModeInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnGetDomainPreferenceModeInner(data, reply), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallStubTest_0003
 * @tc.name     Test CellularCallStub
 * @tc.desc     Function test
 */
HWTEST_F(CellularCallStubTest, CellularCallStubTest_0003, Function | MediumTest | Level1)
{
    CellularCallService cellularCallStub;
    MessageParcel data;
    MessageParcel reply;
    data.WriteInt32(50);
    EXPECT_NE(cellularCallStub.OnSetImsSwitchStatusInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnGetImsSwitchStatusInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetVoNRStateInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnGetVoNRStateInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetImsConfigStringInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetImsConfigIntInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnGetImsConfigInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetImsFeatureValueInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnGetImsFeatureValueInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnControlCameraInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetPreviewWindowInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetDisplayWindowInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetCameraZoomInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetPausePictureInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetDeviceDirectionInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnSetMuteInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnGetMuteInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnCloseUnFinishedUssdInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.OnClearAllCallsInner(data, reply), TELEPHONY_SUCCESS);
#ifdef SUPPORT_RTT_CALL
    EXPECT_NE(cellularCallStub.SetRttCapability(-1, false), TELEPHONY_SUCCESS);
    EXPECT_NE(cellularCallStub.UpdateImsRttCallMode(-1, -1, ImsRTTCallMode::LOCAL_REQUEST_UPGRADE), TELEPHONY_SUCCESS);
#endif
}
} // namespace Telephony
} // namespace OHOS