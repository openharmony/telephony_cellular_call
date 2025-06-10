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

#define private public
#define protected public
#include "cellular_call_config.h"
#include "cellular_call_handler.h"
#include "cellular_call_proxy.h"
#include "cellular_call_register.h"
#include "cellular_call_service.h"
#include "core_service_client.h"
#include "tel_ril_call_parcel.h"
#include "satellite_call_callback_proxy.h"
#include "satellite_call_callback_stub.h"
#include "satellite_call_client.h"
#include "satellite_control.h"
#include "gtest/gtest.h"
#include "securec.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
const int32_t SIM1_SLOTID = 0;
const int32_t SIM2_SLOTID = 1;
const int32_t SLOT_COUNT = 2;
const std::string PHONE_NUMBER = "0000000";

class SatelliteCallbackTest : public testing::Test {
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

void SatelliteCallbackTest::SetUpTestCase(void)
{
    // step 3: Set Up Test Case
}

void SatelliteCallbackTest::TearDownTestCase(void)
{
    // step 3: Tear Down Test Case
}

void SatelliteCallbackTest::SetUp(void)
{
    // step 3: input testcase setup step
}

void SatelliteCallbackTest::TearDown(void)
{
    // step 3: input testcase teardown step
}

/**
 * @tc.number   cellular_call_SatelliteCallCallbackProxy_0001
 * @tc.name     Test for SatelliteCallCallbackProxy
 * @tc.desc     Function test
 */
HWTEST_F(SatelliteCallbackTest, cellular_call_SatelliteCallCallbackProxy_0001, Function | MediumTest | Level3)
{
    const sptr<SatelliteCallCallbackInterface> satelliteCallCallback_ =
        (std::make_unique<SatelliteCallCallbackStub>()).release();
    auto callCallbackProxy =
        (std::make_unique<SatelliteCallCallbackProxy>(satelliteCallCallback_->AsObject().GetRefPtr())).release();
    ASSERT_TRUE(callCallbackProxy != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        EventFwk::MatchingSkills matchingSkills;
        matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
        EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
        auto handler = std::make_shared<CellularCallHandler>(subscriberInfo);
        auto callClient = DelayedSingleton<SatelliteCallClient>::GetInstance();
        callClient->RegisterSatelliteCallCallbackHandler(slotId, handler);
        RadioResponseInfo rilRadioResponse;
        rilRadioResponse.error = ErrType::ERR_GENERIC_FAILURE;

        ASSERT_EQ(callCallbackProxy->DialSatelliteResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->HangUpSatelliteResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->AnswerSatelliteResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->RejectSatelliteResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->GetSatelliteCallsDataResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->CallStateChangeReport(slotId), TELEPHONY_SUCCESS);
        SatelliteCurrentCallList satelliteCallList;
        satelliteCallList.callSize = 0;
        ASSERT_EQ(callCallbackProxy->GetSatelliteCallsDataResponse(slotId, satelliteCallList), TELEPHONY_SUCCESS);
    }
    DelayedSingleton<SatelliteCallClient>::GetInstance()->UnInit();
    DelayedSingleton<SatelliteCallClient>::DestroyInstance();
}

/**
 * @tc.number   cellular_call_SatelliteCallCallbackProxy_0002
 * @tc.name     Test for SatelliteCallCallbackProxy
 * @tc.desc     Function test
 */
HWTEST_F(SatelliteCallbackTest, cellular_call_SatelliteCallCallbackProxy_0002, Function | MediumTest | Level3)
{
    const sptr<SatelliteCallCallbackInterface> satelliteCallCallback_ =
        (std::make_unique<SatelliteCallCallbackStub>()).release();
    auto callCallbackProxy =
        (std::make_unique<SatelliteCallCallbackProxy>(satelliteCallCallback_->AsObject().GetRefPtr())).release();
    ASSERT_TRUE(callCallbackProxy != nullptr);
    for (int32_t slotId = 0; slotId < SLOT_COUNT; slotId++) {
        EventFwk::MatchingSkills matchingSkills;
        matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
        EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
        auto handler = std::make_shared<CellularCallHandler>(subscriberInfo);
        auto callClient = DelayedSingleton<SatelliteCallClient>::GetInstance();
        callClient->RegisterSatelliteCallCallbackHandler(slotId, handler);
        RadioResponseInfo rilRadioResponse;
        rilRadioResponse.error = ErrType::ERR_GENERIC_FAILURE;

        ASSERT_EQ(callCallbackProxy->DialSatelliteResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->HangUpSatelliteResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->AnswerSatelliteResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->RejectSatelliteResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->GetSatelliteCallsDataResponse(slotId, rilRadioResponse), TELEPHONY_SUCCESS);
        ASSERT_EQ(callCallbackProxy->CallStateChangeReport(slotId), TELEPHONY_SUCCESS);
        SatelliteCurrentCallList satelliteCallList;
        satelliteCallList.callSize = 0;
        ASSERT_EQ(callCallbackProxy->GetSatelliteCallsDataResponse(slotId, satelliteCallList), TELEPHONY_SUCCESS);
    }
    DelayedSingleton<SatelliteCallClient>::GetInstance()->UnInit();
    DelayedSingleton<SatelliteCallClient>::DestroyInstance();
}

/**
 * @tc.number   cellular_call_SatelliteCallCallbackStub_0001
 * @tc.name     Test for SatelliteCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(SatelliteCallbackTest, cellular_call_SatelliteCallCallbackStub_0001, Function | MediumTest | Level3)
{
    sptr<SatelliteCallCallbackStub> stub = (std::make_unique<SatelliteCallCallbackStub>()).release();
    ASSERT_TRUE(stub != nullptr);
    
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        RadioResponseInfo rilRadioResponse;
        rilRadioResponse.error = ErrType::ERR_GENERIC_FAILURE;
        MessageParcel answerData;
        MessageParcel answerReply;
        ASSERT_TRUE(answerData.WriteInt32(slotId));
        ASSERT_TRUE(answerData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stub->OnAnswerResponseInner(answerData, answerReply), TELEPHONY_SUCCESS);

        MessageParcel dialData;
        MessageParcel dialReply;
        ASSERT_TRUE(dialData.WriteInt32(slotId));
        ASSERT_TRUE(dialData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stub->OnDialResponseInner(dialData, dialReply), TELEPHONY_SUCCESS);

        MessageParcel CallsData;
        MessageParcel CallsReply;
        ASSERT_TRUE(CallsData.WriteInt32(slotId));
        ASSERT_TRUE(CallsData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stub->OnGetSatelliteCallsDataResponseInner(CallsData, CallsReply), TELEPHONY_SUCCESS);

        MessageParcel hangupData;
        MessageParcel hangupReply;
        ASSERT_TRUE(hangupData.WriteInt32(slotId));
        ASSERT_TRUE(hangupData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stub->OnHangUpResponseInner(hangupData, hangupReply), TELEPHONY_SUCCESS);

        MessageParcel rejectData;
        MessageParcel rejectReply;
        ASSERT_TRUE(rejectData.WriteInt32(slotId));
        ASSERT_TRUE(rejectData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stub->OnRejectResponseInner(rejectData, rejectReply), TELEPHONY_SUCCESS);

        MessageParcel statechangeData;
        MessageParcel statechangeReply;
        ASSERT_TRUE(statechangeData.WriteInt32(slotId));
        ASSERT_EQ(stub->OnCallStateChangeReportInner(statechangeData, statechangeReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_SatelliteCallCallbackStub_0002
 * @tc.name     Test for SatelliteCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(SatelliteCallbackTest, cellular_call_SatelliteCallCallbackStub_0002, Function | MediumTest | Level3)
{
    sptr<SatelliteCallCallbackStub> stub = (std::make_unique<SatelliteCallCallbackStub>()).release();
    ASSERT_TRUE(stub != nullptr);
    int32_t slotId = 0;
    RadioResponseInfo rilRadioResponse;
    rilRadioResponse.error = ErrType::ERR_GENERIC_FAILURE;
    MessageParcel answerData;
    MessageParcel answerReply;
    ASSERT_TRUE(answerData.WriteInt32(slotId));
    ASSERT_TRUE(answerData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
    ASSERT_EQ(stub->OnAnswerResponseInner(answerData, answerReply), TELEPHONY_SUCCESS);

    MessageParcel dialData;
    MessageParcel dialReply;
    ASSERT_TRUE(dialData.WriteInt32(slotId));
    ASSERT_TRUE(dialData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
    ASSERT_EQ(stub->OnDialResponseInner(dialData, dialReply), TELEPHONY_SUCCESS);

    MessageParcel CallsData;
    MessageParcel CallsReply;
    ASSERT_TRUE(CallsData.WriteInt32(slotId));
    ASSERT_TRUE(CallsData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
    ASSERT_EQ(stub->OnGetSatelliteCallsDataResponseInner(CallsData, CallsReply), TELEPHONY_SUCCESS);

    MessageParcel hangupData;
    MessageParcel hangupReply;
    ASSERT_TRUE(hangupData.WriteInt32(slotId));
    ASSERT_TRUE(hangupData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
    ASSERT_EQ(stub->OnHangUpResponseInner(hangupData, hangupReply), TELEPHONY_SUCCESS);

    MessageParcel rejectData;
    MessageParcel rejectReply;
    ASSERT_TRUE(rejectData.WriteInt32(slotId));
    ASSERT_TRUE(rejectData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
    ASSERT_EQ(stub->OnRejectResponseInner(rejectData, rejectReply), TELEPHONY_SUCCESS);

    MessageParcel statechangeData;
    MessageParcel statechangeReply;
    ASSERT_TRUE(statechangeData.WriteInt32(slotId));
    ASSERT_EQ(stub->OnCallStateChangeReportInner(statechangeData, statechangeReply), TELEPHONY_SUCCESS);
}
} // namespace Telephony
} // namespace OHOS
