/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
#define PRIVATE PUBLIC
#define PROTECTED PUBLIC
#include "cellular_call_config.h"
#include "cellular_call_handler.h"
#include "cellular_call_proxy.h"
#include "cellular_call_register.h"
#include "cellular_call_service.h"
#include "tel_ril_call_parcel.h"
#include "ims_call_callback_proxy.h"
#include "ims_call_callback_stub.h"
#include "ims_call_client.h"
#include "ims_control.h"
#include "ims_error.h"
#include "core_service_client.h"
#include "gtest/gtest.h"
#include "securec.h"
#include "ims_core_service_client.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
const int32_t DEFAULT_INDEX = 1;

class ImsCallbackProxyTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
    bool HasSimCard(int32_t slotId)
    {
        bool hasSimCard = false;
        DelayedRefSingleton<CoreServiceClient>::GetInstance().HasSimCard(slotId, hasSimCard);
        return hasSimCard;
    }
};

void ImsCallbackProxyTest::SetUpTestCase(void)
{
    // step 3: Set Up Test Case
}

void ImsCallbackProxyTest::TearDownTestCase(void) {}

void ImsCallbackProxyTest::SetUp(void) {}

void ImsCallbackProxyTest::TearDown(void) {}

/**
 * @tc.number   cellular_call_ImsCallCallbackProxy_0001
 * @tc.name     Test for ImsCallCallbackProxy
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackProxyTest, cellular_call_ImsCallCallbackProxy_0001, Function | MediumTest | Level3)
{
    const sptr<ImsCallCallbackInterface> imsCallCallback_ = (std::make_unique<ImsCallCallbackStub>()).release();
    auto callCallbackProxy =
        (std::make_unique<ImsCallCallbackProxy>(imsCallCallback_->AsObject().GetRefPtr())).release();
    ASSERT_TRUE(callCallbackProxy != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        EventFwk::MatchingSkills matchingSkills;
        matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
        EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
        auto handler = std::make_shared<CellularCallHandler>(subscriberInfo);
        auto callClient = DelayedSingleton<ImsCallClient>::GetInstance();
        ASSERT_EQ(callClient->RegisterImsCallCallbackHandler(slotId, handler), TELEPHONY_SUCCESS);
        RadioResponseInfo rilRadioResponse;
        rilRadioResponse.error = ErrType::ERR_GENERIC_FAILURE;
        EXPECT_EQ(callCallbackProxy->DialResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->HangUpResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->RejectWithReasonResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->AnswerResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->HoldCallResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->UnHoldCallResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->SwitchCallResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->StartDtmfResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        EXPECT_GE(callCallbackProxy->SendDtmfResponse(slotId, rilRadioResponse, DEFAULT_INDEX), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->StopDtmfResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->SetImsSwitchResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->GetImsSwitchResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->GetImsCallsDataResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->CallStateChangeReport(slotId), TELEPHONY_SUCCESS);
        ImsCurrentCallList imsCallList;
        imsCallList.callSize = 0;
        EXPECT_EQ(callCallbackProxy->GetImsCallsDataResponse(slotId, imsCallList), TELEPHONY_SUCCESS);
        DisconnectedDetails details;
        EXPECT_EQ(callCallbackProxy->LastCallFailReasonResponse(slotId, details), TELEPHONY_SUCCESS);
        RingbackVoice ringback;
        EXPECT_EQ(callCallbackProxy->CallRingBackReport(slotId, ringback), TELEPHONY_SUCCESS);
        int32_t active = 0;
        EXPECT_EQ(callCallbackProxy->GetImsSwitchResponse(slotId, active), TELEPHONY_SUCCESS);
        ImsCapFromChip imsCap = {0};
        EXPECT_EQ(callCallbackProxy->GetImsCapResponse(slotId, imsCap), TELEPHONY_SUCCESS);
        MuteControlResponse muteResponse;
        EXPECT_EQ(callCallbackProxy->SetMuteResponse(slotId, muteResponse), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->CombineConferenceResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->InviteToConferenceResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
    }
    DelayedSingleton<ImsCallClient>::GetInstance()->UnInit();
    DelayedSingleton<ImsCallClient>::DestroyInstance();
}

/**
 * @tc.number   cellular_call_ImsCallCallbackProxy_0002
 * @tc.name     Test for ImsCallCallbackProxy
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackProxyTest, cellular_call_ImsCallCallbackProxy_0002, Function | MediumTest | Level3)
{
    const sptr<ImsCallCallbackInterface> imsCallCallback_ = (std::make_unique<ImsCallCallbackStub>()).release();
    auto callCallbackProxy =
        (std::make_unique<ImsCallCallbackProxy>(imsCallCallback_->AsObject().GetRefPtr())).release();
    ASSERT_TRUE(callCallbackProxy != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        EventFwk::MatchingSkills matchingSkills;
        matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
        EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
        auto handler = std::make_shared<CellularCallHandler>(subscriberInfo);
        auto callClient = DelayedSingleton<ImsCallClient>::GetInstance();
        ASSERT_EQ(callClient->RegisterImsCallCallbackHandler(slotId, handler), TELEPHONY_SUCCESS);
        GetClipResult clipResult;
        clipResult.result.index = INVALID_INDEX;
        EXPECT_EQ(callCallbackProxy->GetClipResponse(slotId, clipResult), TELEPHONY_SUCCESS);
        GetClirResult clirResult;
        clirResult.result.index = INVALID_INDEX;
        EXPECT_EQ(callCallbackProxy->GetClirResponse(slotId, clirResult), TELEPHONY_SUCCESS);
        SsBaseResult normalResult;
        normalResult.index = DEFAULT_INDEX;
        EXPECT_EQ(callCallbackProxy->SetClipResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->SetClirResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->SetCallTransferResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->SetCallRestrictionResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->SetCallWaitingResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->SetColrResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        EXPECT_EQ(callCallbackProxy->SetColpResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        CallForwardQueryInfoList callList;
        callList.result.index = INVALID_INDEX;
        EXPECT_EQ(callCallbackProxy->GetCallTransferResponse(slotId, callList), TELEPHONY_SUCCESS);
        CallRestrictionResult crResult;
        crResult.result.index = INVALID_INDEX;
        EXPECT_EQ(callCallbackProxy->GetCallRestrictionResponse(slotId, crResult), TELEPHONY_SUCCESS);
        CallWaitResult cwResult;
        cwResult.result.index = INVALID_INDEX;
        EXPECT_EQ(callCallbackProxy->GetCallWaitingResponse(slotId, cwResult), TELEPHONY_SUCCESS);
        GetColrResult colrResult;
        colrResult.result.index = INVALID_INDEX;
        EXPECT_EQ(callCallbackProxy->GetColrResponse(slotId, colrResult), TELEPHONY_SUCCESS);
        GetColpResult colpResult;
        colpResult.result.index = INVALID_INDEX;
        EXPECT_EQ(callCallbackProxy->GetColpResponse(slotId, colpResult), TELEPHONY_SUCCESS);
    }
    DelayedSingleton<ImsCallClient>::GetInstance()->UnInit();
    DelayedSingleton<ImsCallClient>::DestroyInstance();
}

/**
 * @tc.number   cellular_call_ImsCallCallbackProxy_0003
 * @tc.name     Test for ImsCallCallbackProxy
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackProxyTest, cellular_call_ImsCallCallbackProxy_0003, Function | MediumTest | Level3)
{
    const sptr<ImsCallCallbackInterface> imsCallCallback_ = (std::make_unique<ImsCallCallbackStub>()).release();
    auto callCallbackProxy =
        (std::make_unique<ImsCallCallbackProxy>(imsCallCallback_->AsObject().GetRefPtr())).release();
    ASSERT_TRUE(callCallbackProxy != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        EventFwk::MatchingSkills matchingSkills;
        matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
        EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
        auto handler = std::make_shared<CellularCallHandler>(subscriberInfo);
        auto callClient = DelayedSingleton<ImsCallClient>::GetInstance();
        ASSERT_EQ(callClient->RegisterImsCallCallbackHandler(slotId, handler), TELEPHONY_SUCCESS);
        ImsCallModeReceiveInfo callModeReceiveInfo;
        callModeReceiveInfo.callIndex = DEFAULT_INDEX;
        EXPECT_EQ(
            callCallbackProxy->ReceiveUpdateCallMediaModeResponse(slotId, callModeReceiveInfo), TELEPHONY_SUCCESS);
        EXPECT_EQ(
            callCallbackProxy->ReceiveUpdateCallMediaModeRequest(slotId, callModeReceiveInfo), TELEPHONY_SUCCESS);
        ImsCallSessionEventInfo callSessionEventInfo;
        callSessionEventInfo.callIndex = DEFAULT_INDEX;
        EXPECT_EQ(callCallbackProxy->CallSessionEventChanged(slotId, callSessionEventInfo), TELEPHONY_SUCCESS);
        ImsCallPeerDimensionsInfo callPeerDimensionsInfo;
        callPeerDimensionsInfo.callIndex = DEFAULT_INDEX;
        EXPECT_EQ(callCallbackProxy->PeerDimensionsChanged(slotId, callPeerDimensionsInfo), TELEPHONY_SUCCESS);
        ImsCallDataUsageInfo callDataUsageInfo;
        callDataUsageInfo.callIndex = DEFAULT_INDEX;
        EXPECT_EQ(callCallbackProxy->CallDataUsageChanged(slotId, callDataUsageInfo), TELEPHONY_SUCCESS);
        CameraCapabilitiesInfo cameraCapabilitiesInfo;
        cameraCapabilitiesInfo.callIndex = DEFAULT_INDEX;
        EXPECT_EQ(callCallbackProxy->CameraCapabilitiesChanged(slotId, cameraCapabilitiesInfo), TELEPHONY_SUCCESS);
#ifdef SUPPORT_RTT_CALL
        RadioResponseInfo info;
        EXPECT_NE(callCallbackProxy->StartRttResponse(slotId, info), -100);
        EXPECT_NE(callCallbackProxy->StopRttResponse(slotId, info), -100);
#endif
    }
    DelayedSingleton<ImsCallClient>::GetInstance()->UnInit();
    DelayedSingleton<ImsCallClient>::DestroyInstance();
#ifdef SUPPORT_RTT_CALL
    int32_t slotId = 0;
    ImsCallRttEventInfo rttEvtInfo;
    ImsCallRttErrorInfo rttErrInfo;
    EXPECT_NE(callCallbackProxy->ReceiveUpdateImsCallRttEvtResponse(slotId, rttEvtInfo), -100);
    EXPECT_NE(callCallbackProxy->ReceiveUpdateImsCallRttErrResponse(slotId, rttErrInfo), -100);
#endif
}

/**
 * @tc.number   cellular_call_ImsCallCallbackProxy_0004
 * @tc.name     Test for ImsCallCallbackProxy
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackProxyTest, cellular_call_ImsCallCallbackProxy_0004, Function | MediumTest | Level3)
{
    const sptr<ImsCallCallbackInterface> imsCallCallback_ = (std::make_unique<ImsCallCallbackStub>()).release();
    auto callCallbackProxy =
        (std::make_unique<ImsCallCallbackProxy>(imsCallCallback_->AsObject().GetRefPtr())).release();
    ASSERT_TRUE(callCallbackProxy != nullptr);
    EventFwk::MatchingSkills matchingSkills;
    matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
    EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
    auto handler = std::make_shared<CellularCallHandler>(subscriberInfo);
    auto callClient = DelayedSingleton<ImsCallClient>::GetInstance();
    int32_t slotId = 0;
    ASSERT_EQ(callClient->RegisterImsCallCallbackHandler(slotId, handler), TELEPHONY_SUCCESS);
    EXPECT_EQ(callCallbackProxy->GetImsSuppExtResponse(slotId, 2, INVALID_INDEX), TELEPHONY_SUCCESS);
    EXPECT_EQ(callCallbackProxy->GetImsSuppExtResponse(slotId, 3, INVALID_INDEX), TELEPHONY_SUCCESS);
    DelayedSingleton<ImsCallClient>::GetInstance()->UnInit();
    DelayedSingleton<ImsCallClient>::DestroyInstance();
}
} // namespace Telephony
} // namespace OHOS
