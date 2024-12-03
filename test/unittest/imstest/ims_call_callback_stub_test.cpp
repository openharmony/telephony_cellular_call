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
#include "ims_call_callback_stub.h"
#include "ipc_types.h"
#include "ims_call_callback_ipc_interface_code.h"
#include "ims_call_ipc_interface_code.h"


namespace OHOS {
namespace Telephony {
using namespace testing::ext;
class ImsCallCallbackStubTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void ImsCallCallbackStubTest::SetUpTestCase() {}

void ImsCallCallbackStubTest::TearDownTestCase() {}

void ImsCallCallbackStubTest::SetUp() {}

void ImsCallCallbackStubTest::TearDown() {}

/**
 * @tc.number   Telephony_ImsCallCallbackStubTest_0001
 * @tc.name     Test ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallCallbackStubTest, ImsCallCallbackStubTest_0001, Function | MediumTest | Level1)
{
    ImsCallCallbackStub callBackStub;
    int32_t slotId = 0;
    uint32_t code = 150;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    RadioResponseInfo rilRadioResponse;
    rilRadioResponse.error = ErrType::ERR_GENERIC_FAILURE;
    data.WriteInt32(slotId);
    data.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo));
    EXPECT_NE(callBackStub.OnRemoteRequest(code, data, reply, option), IPC_STUB_UNKNOW_TRANS_ERR);

    code = static_cast<uint32_t>(ImsCallInterfaceCode::IMS_ANSWER);
    callBackStub.OnRemoteRequest(code, data, reply, option);

    EXPECT_NE(callBackStub.OnDialResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnHangUpResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnRejectResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnAnswerResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnHoldCallResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnUnHoldCallResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnSwitchCallResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnStartDtmfResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnSendDtmfResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnStopDtmfResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnCallStateChangeReportInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnSetImsSwitchResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnGetImsSwitchResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnGetImsCallsDataResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnSetMuteResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnCallRingBackReportInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnLastCallFailReasonResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnSetClipResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnGetClipResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnSetClirResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnGetClirResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnGetCallTransferResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnSetCallTransferResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnGetCallRestrictionResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnSetCallRestrictionResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnGetCallWaitingResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnSetCallWaitingResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnSetColrResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnGetColrResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnSetColpResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_EQ(callBackStub.OnGetColpResponseInner(data, reply), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_ImsCallCallbackStubTest_0002
 * @tc.name     Test ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallCallbackStubTest, ImsCallCallbackStubTest_0002, Function | MediumTest | Level1)
{
    ImsCallCallbackStub callBackStub;
    int32_t slotId = 0;
    MessageParcel data;
    MessageParcel reply;
    RadioResponseInfo rilRadioResponse;
    rilRadioResponse.error = ErrType::ERR_GENERIC_FAILURE;
    data.WriteInt32(slotId);
    data.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo));
    EXPECT_EQ(callBackStub.OnCombineConferenceResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnInviteToConferenceResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnReceiveUpdateCallMediaModeRequestInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnReceiveUpdateCallMediaModeResponseInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnCallSessionEventChangedInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnPeerDimensionsChangedInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnCallDataUsageChangedInner(data, reply), TELEPHONY_SUCCESS);
    EXPECT_NE(callBackStub.OnCameraCapabilitiesChangedInner(data, reply), TELEPHONY_SUCCESS);
    callBackStub.DialResponse(slotId, rilRadioResponse);
    callBackStub.HangUpResponse(slotId, rilRadioResponse);
    callBackStub.RejectWithReasonResponse(slotId, rilRadioResponse);
    callBackStub.AnswerResponse(slotId, rilRadioResponse);
    callBackStub.HoldCallResponse(slotId, rilRadioResponse);
    callBackStub.UnHoldCallResponse(slotId, rilRadioResponse);
    callBackStub.SwitchCallResponse(slotId, rilRadioResponse);
    callBackStub.StartDtmfResponse(slotId, rilRadioResponse);
    callBackStub.StopDtmfResponse(slotId, rilRadioResponse);
    callBackStub.SetImsSwitchResponse(slotId, rilRadioResponse);
    callBackStub.GetImsSwitchResponse(slotId, rilRadioResponse);
    callBackStub.CombineConferenceResponse(slotId, rilRadioResponse);
    callBackStub.InviteToConferenceResponse(slotId, rilRadioResponse);
    callBackStub.GetImsCallsDataResponse(slotId, rilRadioResponse);
    int32_t callIndex = 0;
    callBackStub.SendDtmfResponse(slotId, rilRadioResponse, callIndex);
    callBackStub.CallStateChangeReport(slotId);
    ImsCurrentCallList callList;
    callBackStub.GetImsCallsDataResponse(slotId, callList);
    ImsCallModeReceiveInfo callModeResponse;
    callBackStub.ReceiveUpdateCallMediaModeRequest(slotId, callModeResponse);
    callBackStub.ReceiveUpdateCallMediaModeResponse(slotId, callModeResponse);
    MuteControlResponse response;
    EXPECT_EQ(callBackStub.SetMuteResponse(slotId, response), TELEPHONY_SUCCESS);

    slotId = -100;
    EXPECT_EQ(callBackStub.SwitchCallResponse(slotId, rilRadioResponse), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.SendDtmfResponse(slotId, rilRadioResponse, callIndex), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.CallStateChangeReport(slotId), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.GetImsCallsDataResponse(slotId, callList), TELEPHONY_ERR_LOCAL_PTR_NULL);
}

/**
 * @tc.number   Telephony_ImsCallCallbackStubTest_0003
 * @tc.name     Test ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallCallbackStubTest, ImsCallCallbackStubTest_0003, Function | MediumTest | Level1)
{
    ImsCallCallbackStub callBackStub;
    int32_t slotId = 0;
    int32_t active = 0;
    callBackStub.GetImsSwitchResponse(slotId, active);
    
    RingbackVoice info;
    callBackStub.CallRingBackReport(slotId, info);
    DisconnectedDetails details;
    callBackStub.LastCallFailReasonResponse(slotId, details);
    SsBaseResult baseResult;
    callBackStub.SetClipResponse(slotId, baseResult);
    GetClipResult clipResult;
    callBackStub.GetClipResponse(slotId, clipResult);
    GetClirResult clirResult;
    callBackStub.GetClirResponse(slotId, clirResult);
    callBackStub.SetClirResponse(slotId, baseResult);
    CallForwardQueryInfoList cFQueryList;
    callBackStub.GetCallTransferResponse(slotId, cFQueryList);
    callBackStub.SetCallTransferResponse(slotId, baseResult);
    CallRestrictionResult callRestriResult;
    callBackStub.GetCallRestrictionResponse(slotId, callRestriResult);
    callBackStub.SetCallTransferResponse(slotId, baseResult);
    CallWaitResult waitResult;
    callBackStub.GetCallWaitingResponse(slotId, waitResult);
    callBackStub.SetCallWaitingResponse(slotId, baseResult);
    GetColrResult colrResult;
    callBackStub.GetColrResponse(slotId, colrResult);
    callBackStub.SetColrResponse(slotId, baseResult);
    GetColpResult colpResult;
    callBackStub.GetColpResponse(slotId, colpResult);
    callBackStub.SetColpResponse(slotId, baseResult);
    ImsCallSessionEventInfo callSessionEventInfo;
    callBackStub.CallSessionEventChanged(slotId, callSessionEventInfo);

    slotId = -100;
    EXPECT_EQ(callBackStub.GetImsSwitchResponse(slotId, active), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.CallRingBackReport(slotId, info), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.LastCallFailReasonResponse(slotId, details), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.GetClipResponse(slotId, clipResult), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.GetClirResponse(slotId, clirResult), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.GetCallTransferResponse(slotId, cFQueryList), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.GetCallRestrictionResponse(slotId, callRestriResult), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.GetCallWaitingResponse(slotId, waitResult), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.GetColrResponse(slotId, colrResult), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.GetColpResponse(slotId, colpResult), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.CallSessionEventChanged(slotId, callSessionEventInfo), TELEPHONY_ERR_LOCAL_PTR_NULL);
}

/**
 * @tc.number   Telephony_ImsCallCallbackStubTest_0004
 * @tc.name     Test ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallCallbackStubTest, ImsCallCallbackStubTest_0004, Function | MediumTest | Level1)
{
    ImsCallCallbackStub callBackStub;
    int32_t slotId = 0;

    ImsCallPeerDimensionsInfo callPeerDimensionsInfo;
    callBackStub.PeerDimensionsChanged(slotId, callPeerDimensionsInfo);

    ImsCallDataUsageInfo callDataUsageInfo;
    callBackStub.CallDataUsageChanged(slotId, callDataUsageInfo);

    CameraCapabilitiesInfo cameraCapabilitiesInfo;
    callBackStub.CameraCapabilitiesChanged(slotId, cameraCapabilitiesInfo);

    SsRequestCommand ss;
    int32_t index = 0;
    callBackStub.GetSsRequestCommand(slotId, index, ss);

    CallForwardQueryInfoList cFQueryList;
    CallForwardQueryInfoList cFQueryResultList;
    callBackStub.BuildCallForwardInfo(cFQueryList, cFQueryResultList);

    int32_t eventId = 0;
    RadioResponseInfo rilRadioResponse;
    rilRadioResponse.error = ErrType::ERR_GENERIC_FAILURE;
    callBackStub.SendEvent(slotId, eventId, rilRadioResponse);

    SsBaseResult baseResult;
    callBackStub.SendEvent(slotId, eventId, baseResult);

    ImsCallModeReceiveInfo callModeInfo;
    callBackStub.SendEvent(slotId, eventId, callModeInfo);

    slotId = -100;
    EXPECT_EQ(callBackStub.PeerDimensionsChanged(slotId, callPeerDimensionsInfo), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.CallDataUsageChanged(slotId, callDataUsageInfo), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.CameraCapabilitiesChanged(slotId, cameraCapabilitiesInfo), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.GetSsRequestCommand(slotId, index, ss), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.SendEvent(slotId, eventId, rilRadioResponse), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.SendEvent(slotId, eventId, baseResult), TELEPHONY_ERR_LOCAL_PTR_NULL);
    EXPECT_EQ(callBackStub.SendEvent(slotId, eventId, callModeInfo), TELEPHONY_ERR_LOCAL_PTR_NULL);
}

} // namespace Telephony
} // namespace OHOS