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
#define PRIVATE public
#define PROTECTED public
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
const std::string PHONE_NUMBER = "0000000";
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
    std::cout << "---------- ImsCoreServiceClient start ------------" << std::endl;
    DelayedSingleton<ImsCoreServiceClient>::GetInstance()->Init();
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
        handler->SetSlotId(slotId);
        handler->RegisterImsCallCallbackHandler();
        RadioResponseInfo rilRadioResponse;
        rilRadioResponse.error = ErrType::ERR_GENERIC_FAILURE;
        ASSERT_EQ(callCallbackProxy->DialResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->HangUpResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->RejectWithReasonResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->AnswerResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->HoldCallResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->UnHoldCallResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SwitchCallResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->StartDtmfResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_GE(callCallbackProxy->SendDtmfResponse(slotId, rilRadioResponse, DEFAULT_INDEX), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->StopDtmfResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetImsSwitchResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->GetImsSwitchResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->GetImsCallsDataResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->CallStateChangeReport(slotId), TELEPHONY_SUCCESS);
        ImsCurrentCallList imsCallList;
        imsCallList.callSize = 0;
        ASSERT_EQ(callCallbackProxy->GetImsCallsDataResponse(slotId, imsCallList), TELEPHONY_SUCCESS);
        DisconnectedDetails details;
        ASSERT_EQ(callCallbackProxy->LastCallFailReasonResponse(slotId, details), TELEPHONY_SUCCESS);
        RingbackVoice ringback;
        ASSERT_EQ(callCallbackProxy->CallRingBackReport(slotId, ringback), TELEPHONY_SUCCESS);
        int32_t active = 0;
        ASSERT_EQ(callCallbackProxy->GetImsSwitchResponse(slotId, active), TELEPHONY_SUCCESS);
        ImsCapFromChip imsCap = {0};
        ASSERT_EQ(callCallbackProxy->GetImsCapResponse(slotId, imsCap), TELEPHONY_SUCCESS);
        MuteControlResponse muteResponse;
        ASSERT_EQ(callCallbackProxy->SetMuteResponse(slotId, muteResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->CombineConferenceResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->InviteToConferenceResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
    }
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
        handler->SetSlotId(slotId);
        handler->RegisterImsCallCallbackHandler();
        GetClipResult clipResult;
        clipResult.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetClipResponse(slotId, clipResult), TELEPHONY_SUCCESS);
        GetClirResult clirResult;
        clirResult.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetClirResponse(slotId, clirResult), TELEPHONY_SUCCESS);
        SsBaseResult normalResult;
        normalResult.index = DEFAULT_INDEX;
        ASSERT_EQ(callCallbackProxy->SetClipResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetClirResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetCallTransferResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetCallRestrictionResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetCallWaitingResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetColrResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->SetColpResponse(slotId, normalResult), TELEPHONY_SUCCESS);
        CallForwardQueryInfoList callList;
        callList.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetCallTransferResponse(slotId, callList), TELEPHONY_SUCCESS);
        CallRestrictionResult crResult;
        crResult.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetCallRestrictionResponse(slotId, crResult), TELEPHONY_SUCCESS);
        CallWaitResult cwResult;
        cwResult.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetCallWaitingResponse(slotId, cwResult), TELEPHONY_SUCCESS);
        GetColrResult colrResult;
        colrResult.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetColrResponse(slotId, colrResult), TELEPHONY_SUCCESS);
        GetColpResult colpResult;
        colpResult.result.index = INVALID_INDEX;
        ASSERT_EQ(callCallbackProxy->GetColpResponse(slotId, colpResult), TELEPHONY_SUCCESS);
    }
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
        handler->SetSlotId(slotId);
        handler->RegisterImsCallCallbackHandler();
        ImsCallModeReceiveInfo callModeReceiveInfo;
        callModeReceiveInfo.callIndex = DEFAULT_INDEX;
        ASSERT_EQ(
            callCallbackProxy->ReceiveUpdateCallMediaModeResponse(slotId, callModeReceiveInfo), TELEPHONY_SUCCESS);
        ASSERT_EQ(
            callCallbackProxy->ReceiveUpdateCallMediaModeRequest(slotId, callModeReceiveInfo), TELEPHONY_SUCCESS);
        ImsCallSessionEventInfo callSessionEventInfo;
        callSessionEventInfo.callIndex = DEFAULT_INDEX;
        ASSERT_EQ(callCallbackProxy->CallSessionEventChanged(slotId, callSessionEventInfo), TELEPHONY_SUCCESS);
        ImsCallPeerDimensionsInfo callPeerDimensionsInfo;
        callPeerDimensionsInfo.callIndex = DEFAULT_INDEX;
        ASSERT_EQ(callCallbackProxy->PeerDimensionsChanged(slotId, callPeerDimensionsInfo), TELEPHONY_SUCCESS);
        ImsCallDataUsageInfo callDataUsageInfo;
        callDataUsageInfo.callIndex = DEFAULT_INDEX;
        ASSERT_EQ(callCallbackProxy->CallDataUsageChanged(slotId, callDataUsageInfo), TELEPHONY_SUCCESS);
        CameraCapabilitiesInfo cameraCapabilitiesInfo;
        cameraCapabilitiesInfo.callIndex = DEFAULT_INDEX;
        ASSERT_EQ(callCallbackProxy->CameraCapabilitiesChanged(slotId, cameraCapabilitiesInfo), TELEPHONY_SUCCESS);
    }
}
} // namespace Telephony
} // namespace OHOS
