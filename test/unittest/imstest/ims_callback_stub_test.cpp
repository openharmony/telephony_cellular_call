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
#include "tel_ril_call_parcel.h"
#include "ims_call_callback_proxy.h"
#include "ims_call_callback_stub.h"
#include "ims_call_client.h"
#include "ims_control.h"
#include "ims_error.h"
#include "core_service_client.h"
#include "gtest/gtest.h"
#include "ims_core_service_client.h"
#include "token.h"
#include "securec.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
const int32_t SIM1_SLOTID = 0;
const int32_t SIM2_SLOTID = 1;
const int32_t SLOT_COUNT = 2;
const std::string PHONE_NUMBER = "0000000";
const int32_t DEFAULT_INDEX = 1;

class ImsCallbackStubTest : public testing::Test {
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

    int32_t WriteSsBaseResult(MessageParcel &in, const SsBaseResult &ssResult)
    {
        if (!in.WriteInt32(ssResult.index)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        if (!in.WriteInt32(ssResult.result)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        if (!in.WriteInt32(ssResult.reason)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        if (!in.WriteString(ssResult.message)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        return TELEPHONY_SUCCESS;
    };

    int32_t WriteSsResult(MessageParcel &in, const SsBaseResult &ssResult, const int32_t action, const int32_t state)
    {
        int32_t ret = WriteSsBaseResult(in, ssResult);
        if (ret != TELEPHONY_SUCCESS) {
            return ret;
        }
        if (!in.WriteInt32(action)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        if (!in.WriteInt32(state)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        return TELEPHONY_SUCCESS;
    };

    int32_t WriteCallForwardResult(MessageParcel &in, const CallForwardQueryInfoList &cFQueryList)
    {
        int32_t ret = WriteSsBaseResult(in, cFQueryList.result);
        if (ret != TELEPHONY_SUCCESS) {
            return ret;
        }
        if (!in.WriteInt32(cFQueryList.callSize) || !in.WriteInt32(cFQueryList.flag)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        if (!in.WriteInt32(static_cast<int32_t>(cFQueryList.calls.size()))) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        for (auto call : cFQueryList.calls) {
            if (!in.WriteInt32(call.serial) || !in.WriteInt32(call.result) || !in.WriteInt32(call.status) ||
                !in.WriteInt32(call.classx) || !in.WriteString(call.number) || !in.WriteInt32(call.type) ||
                !in.WriteInt32(call.reason) || !in.WriteInt32(call.time) || !in.WriteInt32(call.startHour) ||
                !in.WriteInt32(call.startMinute) || !in.WriteInt32(call.endHour) || !in.WriteInt32(call.endMinute)) {
                return TELEPHONY_ERR_WRITE_DATA_FAIL;
            }
        }
        return TELEPHONY_SUCCESS;
    }
};

void ImsCallbackStubTest::SetUpTestCase(void)
{
    // step 3: Set Up Test Case
    std::cout << "---------- ImsCoreServiceClient start ------------" << std::endl;
    DelayedSingleton<ImsCoreServiceClient>::GetInstance()->Init();
}

void ImsCallbackStubTest::TearDownTestCase(void)
{
    // step 3: Tear Down Test Case
}

void ImsCallbackStubTest::SetUp(void) {}

void ImsCallbackStubTest::TearDown(void)
{
    // step 3: input testcase teardown step
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0001
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0001, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stub = (std::make_unique<ImsCallCallbackStub>()).release();
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

        MessageParcel imsCallsData;
        MessageParcel imsCallsReply;
        ASSERT_TRUE(imsCallsData.WriteInt32(slotId));
        ASSERT_TRUE(imsCallsData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stub->OnGetImsCallsDataResponseInner(imsCallsData, imsCallsReply), TELEPHONY_SUCCESS);

        MessageParcel hangupData;
        MessageParcel hangupReply;
        ASSERT_TRUE(hangupData.WriteInt32(slotId));
        ASSERT_TRUE(hangupData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stub->OnHangUpResponseInner(hangupData, hangupReply), TELEPHONY_SUCCESS);

        MessageParcel holdCallData;
        MessageParcel holdCallReply;
        ASSERT_TRUE(holdCallData.WriteInt32(slotId));
        ASSERT_TRUE(holdCallData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stub->OnHoldCallResponseInner(holdCallData, holdCallReply), TELEPHONY_SUCCESS);

        MessageParcel rejectData;
        MessageParcel rejectReply;
        ASSERT_TRUE(rejectData.WriteInt32(slotId));
        ASSERT_TRUE(rejectData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stub->OnRejectResponseInner(rejectData, rejectReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0002
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0002, Function | MediumTest | Level3)
{
    
    sptr<ImsCallCallbackStub> stubTestTwo = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestTwo != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        RadioResponseInfo rilRadioResponse;
        rilRadioResponse.error = ErrType::ERR_GENERIC_FAILURE;
        MessageParcel sendDtmfData;
        MessageParcel sendDtmfReply;
        ASSERT_TRUE(sendDtmfData.WriteInt32(slotId));
        ASSERT_TRUE(sendDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_GE(stubTestTwo->OnSendDtmfResponseInner(sendDtmfData, sendDtmfReply), TELEPHONY_SUCCESS);

        MessageParcel setImsSwitchData;
        MessageParcel setImsSwitchReply;
        ASSERT_TRUE(setImsSwitchData.WriteInt32(slotId));
        ASSERT_TRUE(setImsSwitchData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stubTestTwo->OnSetImsSwitchResponseInner(setImsSwitchData, setImsSwitchReply), TELEPHONY_SUCCESS);

        MessageParcel startDtmfData;
        MessageParcel startDtmfReply;
        ASSERT_TRUE(startDtmfData.WriteInt32(slotId));
        ASSERT_TRUE(startDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stubTestTwo->OnStartDtmfResponseInner(startDtmfData, startDtmfReply), TELEPHONY_SUCCESS);

        MessageParcel stopDtmfData;
        MessageParcel stopDtmfReply;
        ASSERT_TRUE(stopDtmfData.WriteInt32(slotId));
        ASSERT_TRUE(stopDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stubTestTwo->OnStopDtmfResponseInner(stopDtmfData, stopDtmfReply), TELEPHONY_SUCCESS);

        MessageParcel switchCallData;
        MessageParcel switchCallReply;
        ASSERT_TRUE(switchCallData.WriteInt32(slotId));
        ASSERT_TRUE(switchCallData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stubTestTwo->OnSwitchCallResponseInner(switchCallData, switchCallReply), TELEPHONY_SUCCESS);

        MessageParcel unholdData;
        MessageParcel unholdReply;
        ASSERT_TRUE(unholdData.WriteInt32(slotId));
        ASSERT_TRUE(unholdData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stubTestTwo->OnUnHoldCallResponseInner(unholdData, unholdReply), TELEPHONY_SUCCESS);

        MessageParcel getImsSwitchData;
        MessageParcel getImsSwitchReply;
        ASSERT_TRUE(getImsSwitchData.WriteInt32(slotId));
        ASSERT_TRUE(getImsSwitchData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stubTestTwo->OnGetImsSwitchResponseInner(getImsSwitchData, getImsSwitchReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0003
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0003, Function | MediumTest | Level3)
{
    

    sptr<ImsCallCallbackStub> stubTestThree = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestThree != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        MessageParcel data;
        MessageParcel reply;
        ASSERT_TRUE(data.WriteInt32(slotId));
        ASSERT_NE(stubTestThree->OnAnswerResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnCallRingBackReportInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnDialResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnHangUpResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnHoldCallResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnRejectResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnSendDtmfResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnSetImsSwitchResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnStartDtmfResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnStopDtmfResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnSwitchCallResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnUnHoldCallResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnSetMuteResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnCombineConferenceResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnInviteToConferenceResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnReceiveUpdateCallMediaModeRequestInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnReceiveUpdateCallMediaModeResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnCallSessionEventChangedInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnPeerDimensionsChangedInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnCallDataUsageChangedInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnCameraCapabilitiesChangedInner(data, reply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0004
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0004, Function | MediumTest | Level3)
{
    
    sptr<ImsCallCallbackStub> stubTestFour = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestFour != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        SsBaseResult normalResult;
        normalResult.index = DEFAULT_INDEX;
        MessageParcel crData;
        MessageParcel crReply;
        ASSERT_TRUE(crData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(crData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetCallRestrictionResponseInner(crData, crReply), TELEPHONY_SUCCESS);
        MessageParcel ctData;
        MessageParcel ctReply;
        ASSERT_TRUE(ctData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(ctData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetCallTransferResponseInner(ctData, ctReply), TELEPHONY_SUCCESS);
        MessageParcel cwData;
        MessageParcel cwReply;
        ASSERT_TRUE(cwData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(cwData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetCallWaitingResponseInner(cwData, cwReply), TELEPHONY_SUCCESS);
        MessageParcel clipData;
        MessageParcel clipReply;
        ASSERT_TRUE(clipData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(clipData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetClipResponseInner(clipData, clipReply), TELEPHONY_SUCCESS);
        MessageParcel clirData;
        MessageParcel clirReply;
        ASSERT_TRUE(clirData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(clirData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetClirResponseInner(clirData, clirReply), TELEPHONY_SUCCESS);
        MessageParcel colpData;
        MessageParcel colpReply;
        ASSERT_TRUE(colpData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(colpData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetColpResponseInner(colpData, colpReply), TELEPHONY_SUCCESS);
        MessageParcel colrData;
        MessageParcel colrReply;
        ASSERT_TRUE(colrData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(colrData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetColrResponseInner(colrData, colrReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0005
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0005, Function | MediumTest | Level3)
{
    
    sptr<ImsCallCallbackStub> stubTestFive = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestFive != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        SsBaseResult normalResult;
        normalResult.index = INVALID_INDEX;
        MessageParcel crData;
        MessageParcel crReply;
        ASSERT_TRUE(crData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(crData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetCallRestrictionResponseInner(crData, crReply), TELEPHONY_SUCCESS);
        MessageParcel ctData;
        MessageParcel ctReply;
        ASSERT_TRUE(ctData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(ctData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetCallTransferResponseInner(ctData, ctReply), TELEPHONY_SUCCESS);
        MessageParcel cwData;
        MessageParcel cwReply;
        ASSERT_TRUE(cwData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(cwData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetCallWaitingResponseInner(cwData, cwReply), TELEPHONY_SUCCESS);
        MessageParcel clipData;
        MessageParcel clipReply;
        ASSERT_TRUE(clipData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(clipData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetClipResponseInner(clipData, clipReply), TELEPHONY_SUCCESS);
        MessageParcel clirData;
        MessageParcel clirReply;
        ASSERT_TRUE(clirData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(clirData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetClirResponseInner(clirData, clirReply), TELEPHONY_SUCCESS);
        MessageParcel colpData;
        MessageParcel colpReply;
        ASSERT_TRUE(colpData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(colpData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetColpResponseInner(colpData, colpReply), TELEPHONY_SUCCESS);
        MessageParcel colrData;
        MessageParcel colrReply;
        ASSERT_TRUE(colrData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(colrData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetColrResponseInner(colrData, colrReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0006
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0006, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stubTestSix = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestSix != nullptr);
    
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        SsBaseResult ssBaseResult;
        ssBaseResult.index = DEFAULT_INDEX;
        ssBaseResult.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stubTestSix->SetCallRestrictionResponse(slotId, ssBaseResult), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestSix->SetCallTransferResponse(slotId, ssBaseResult), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestSix->SetCallWaitingResponse(slotId, ssBaseResult), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestSix->SetClirResponse(slotId, ssBaseResult), TELEPHONY_SUCCESS);
        MessageParcel muteData;
        MessageParcel muteReply;
        MuteControlResponse muteResponse;
        ASSERT_TRUE(muteData.WriteInt32(slotId));
        ASSERT_TRUE(muteData.WriteRawData((const void *)&muteResponse, sizeof(MuteControlResponse)));
        ASSERT_EQ(stubTestSix->OnSetMuteResponseInner(muteData, muteReply), TELEPHONY_SUCCESS);
        MessageParcel ringData;
        MessageParcel ringReply;
        RingbackVoice ringback;
        ASSERT_TRUE(ringData.WriteInt32(slotId));
        ASSERT_TRUE(ringData.WriteRawData((const void *)&ringback, sizeof(RingbackVoice)));
        ASSERT_EQ(stubTestSix->OnCallRingBackReportInner(ringData, ringReply), TELEPHONY_SUCCESS);
        MessageParcel failData;
        MessageParcel failReply;
        DisconnectedDetails details;
        ASSERT_TRUE(failData.WriteInt32(slotId));
        ASSERT_TRUE(failData.WriteInt32(static_cast<int32_t>(details.reason)));
        ASSERT_TRUE(failData.WriteString(details.message));
        ASSERT_EQ(stubTestSix->OnLastCallFailReasonResponseInner(failData, failReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0007
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0007, Function | MediumTest | Level3)
{
    
    sptr<ImsCallCallbackStub> stubTestSeven = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestSeven != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        CallRestrictionResult crResult;
        crResult.result.index = INVALID_INDEX;
        MessageParcel crErrorData;
        MessageParcel crErrorReply;
        ASSERT_TRUE(crErrorData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsResult(crErrorData, crResult.result, crResult.status, crResult.classCw), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestSeven->OnGetCallRestrictionResponseInner(crErrorData, crErrorReply), TELEPHONY_SUCCESS);

        crResult.result.index = DEFAULT_INDEX;
        MessageParcel crData;
        MessageParcel crReply;
        ASSERT_TRUE(crData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsResult(crData, crResult.result, crResult.status, crResult.classCw), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestSeven->OnGetCallRestrictionResponseInner(crData, crReply), TELEPHONY_SUCCESS);
        crResult.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stubTestSeven->GetCallRestrictionResponse(slotId, crResult), TELEPHONY_SUCCESS);

        CallForwardQueryInfoList callList;
        callList.result.index = INVALID_INDEX;
        MessageParcel ctErrorData;
        MessageParcel ctErrorReply;
        ASSERT_TRUE(ctErrorData.WriteInt32(slotId));
        ASSERT_EQ(WriteCallForwardResult(ctErrorData, callList), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestSeven->OnGetCallTransferResponseInner(ctErrorData, ctErrorReply), TELEPHONY_SUCCESS);

        callList.result.index = DEFAULT_INDEX;
        MessageParcel ctData;
        MessageParcel ctReply;
        ASSERT_TRUE(ctData.WriteInt32(slotId));
        ASSERT_EQ(WriteCallForwardResult(ctData, callList), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestSeven->OnGetCallTransferResponseInner(ctData, ctReply), TELEPHONY_SUCCESS);
        callList.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stubTestSeven->GetCallTransferResponse(slotId, callList), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0008
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0008, Function | MediumTest | Level3)
{
    
    sptr<ImsCallCallbackStub> stubTestEigth = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestEigth != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        CallWaitResult cwResult;
        cwResult.result.index = INVALID_INDEX;
        MessageParcel cwErrorData;
        MessageParcel cwErrorReply;
        ASSERT_TRUE(cwErrorData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsResult(cwErrorData, cwResult.result, cwResult.status, cwResult.classCw), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestEigth->OnGetCallWaitingResponseInner(cwErrorData, cwErrorReply), TELEPHONY_SUCCESS);

        cwResult.result.index = DEFAULT_INDEX;
        MessageParcel cwData;
        MessageParcel cwReply;
        ASSERT_TRUE(cwData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsResult(cwData, cwResult.result, cwResult.status, cwResult.classCw), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestEigth->OnGetCallWaitingResponseInner(cwData, cwReply), TELEPHONY_SUCCESS);
        cwResult.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stubTestEigth->GetCallWaitingResponse(slotId, cwResult), TELEPHONY_SUCCESS);

        GetClipResult clipResult;
        clipResult.result.index = INVALID_INDEX;
        MessageParcel clipErrorData;
        MessageParcel clipErrorReply;
        ASSERT_TRUE(clipErrorData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(clipErrorData, clipResult.result, clipResult.action, clipResult.clipStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestEigth->OnGetClipResponseInner(clipErrorData, clipErrorReply), TELEPHONY_SUCCESS);

        clipResult.result.index = DEFAULT_INDEX;
        MessageParcel clipData;
        MessageParcel clipReply;
        ASSERT_TRUE(clipData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(clipData, clipResult.result, clipResult.action, clipResult.clipStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestEigth->OnGetClipResponseInner(clipData, clipReply), TELEPHONY_SUCCESS);
        clipResult.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stubTestEigth->GetClipResponse(slotId, clipResult), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0009
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0009, Function | MediumTest | Level3)
{
    
    sptr<ImsCallCallbackStub> stubTestNight = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestNight != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        GetClirResult clirResult;
        clirResult.result.index = INVALID_INDEX;
        MessageParcel clirErrorData;
        MessageParcel clirErrorReply;
        ASSERT_TRUE(clirErrorData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(clirErrorData, clirResult.result, clirResult.action, clirResult.clirStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestNight->OnGetClirResponseInner(clirErrorData, clirErrorReply), TELEPHONY_SUCCESS);

        clirResult.result.index = DEFAULT_INDEX;
        MessageParcel clirData;
        MessageParcel clirReply;
        ASSERT_TRUE(clirData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(clirData, clirResult.result, clirResult.action, clirResult.clirStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestNight->OnGetClirResponseInner(clirData, clirReply), TELEPHONY_SUCCESS);
        clirResult.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stubTestNight->GetClirResponse(slotId, clirResult), TELEPHONY_SUCCESS);

        GetColpResult colpResult;
        colpResult.result.index = INVALID_INDEX;
        MessageParcel colpErrorData;
        MessageParcel colpErrorReply;
        ASSERT_TRUE(colpErrorData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(colpErrorData, colpResult.result, colpResult.action, colpResult.colpStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestNight->OnGetColpResponseInner(colpErrorData, colpErrorReply), TELEPHONY_SUCCESS);

        colpResult.result.index = DEFAULT_INDEX;
        MessageParcel colpData;
        MessageParcel colpReply;
        ASSERT_TRUE(colpData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(colpData, colpResult.result, colpResult.action, colpResult.colpStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestNight->OnGetColpResponseInner(colpData, colpReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0010
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0010, Function | MediumTest | Level3)
{
    

    sptr<ImsCallCallbackStub> stubTestTen = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestTen != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        GetColrResult colrResult;
        colrResult.result.index = INVALID_INDEX;
        MessageParcel colrErrorData;
        MessageParcel colrErrorReply;
        ASSERT_TRUE(colrErrorData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(colrErrorData, colrResult.result, colrResult.action, colrResult.colrStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestTen->OnGetColrResponseInner(colrErrorData, colrErrorReply), TELEPHONY_SUCCESS);

        colrResult.result.index = DEFAULT_INDEX;
        MessageParcel colrData;
        MessageParcel colrReply;
        ASSERT_TRUE(colrData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(colrData, colrResult.result, colrResult.action, colrResult.colrStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestTen->OnGetColrResponseInner(colrData, colrReply), TELEPHONY_SUCCESS);

        SsBaseResult normalResult;
        normalResult.index = DEFAULT_INDEX;
        MessageParcel ctErrorData;
        MessageParcel ctReply;
        ASSERT_TRUE(ctErrorData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(ctErrorData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_TRUE(ctErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_TRUE(ctErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_TRUE(ctErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_NE(stubTestTen->OnGetCallTransferResponseInner(ctErrorData, ctReply), TELEPHONY_SUCCESS);

        MessageParcel icErrorData;
        MessageParcel icReply;
        ASSERT_TRUE(icErrorData.WriteInt32(slotId));
        ASSERT_TRUE(icErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_TRUE(icErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_TRUE(icErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_TRUE(icErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_NE(stubTestTen->OnGetImsCallsDataResponseInner(icErrorData, icReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0011
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0011, Function | MediumTest | Level3)
{
    
    sptr<ImsCallCallbackStub> stubTestEleven = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestEleven != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        MessageParcel callModeReceiveRequestData;
        MessageParcel callModeReceiveRequestReply;
        ImsCallModeReceiveInfo callModeReceiveRequesInfo;
        callModeReceiveRequesInfo.callIndex = DEFAULT_INDEX;
        ASSERT_TRUE(callModeReceiveRequestData.WriteInt32(slotId));
        ASSERT_TRUE(callModeReceiveRequestData.WriteRawData(
            (const void *)&callModeReceiveRequesInfo, sizeof(ImsCallModeReceiveInfo)));
        ASSERT_EQ(stubTestEleven->OnReceiveUpdateCallMediaModeRequestInner(
            callModeReceiveRequestData, callModeReceiveRequestReply), TELEPHONY_SUCCESS);
        MessageParcel callModeReceiveResponseData;
        MessageParcel callModeReceiveResponseReply;
        ImsCallModeReceiveInfo callModeReceiveResponseInfo;
        callModeReceiveResponseInfo.callIndex = DEFAULT_INDEX;
        ASSERT_TRUE(callModeReceiveResponseData.WriteInt32(slotId));
        ASSERT_TRUE(callModeReceiveResponseData.WriteRawData(
            (const void *)&callModeReceiveResponseInfo, sizeof(ImsCallModeReceiveInfo)));
        ASSERT_EQ(stubTestEleven->OnReceiveUpdateCallMediaModeResponseInner(
            callModeReceiveResponseData, callModeReceiveResponseReply), TELEPHONY_SUCCESS);
        MessageParcel callSessionEventInfoData;
        MessageParcel callSessionEventInfoReply;
        ImsCallSessionEventInfo callSessionEventInfo;
        callSessionEventInfo.callIndex = DEFAULT_INDEX;
        ASSERT_TRUE(callSessionEventInfoData.WriteInt32(slotId));
        ASSERT_TRUE(callSessionEventInfoData.WriteRawData(
            (const void *)&callSessionEventInfo, sizeof(ImsCallSessionEventInfo)));
        ASSERT_EQ(stubTestEleven->OnCallSessionEventChangedInner(
            callSessionEventInfoData, callSessionEventInfoReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0012
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0012, Function | MediumTest | Level3)
{
    
    sptr<ImsCallCallbackStub> stubTestEleven = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestEleven != nullptr);
    for (int32_t slotId = 0; slotId < SIM_SLOT_COUNT; slotId++) {
        if (!HasSimCard(slotId)) {
            continue;
        }
        MessageParcel callPeerDimensionsInfoData;
        MessageParcel callPeerDimensionsInfoReply;
        ImsCallPeerDimensionsInfo callPeerDimensionsInfo;
        callPeerDimensionsInfo.callIndex = DEFAULT_INDEX;
        ASSERT_TRUE(callPeerDimensionsInfoData.WriteInt32(slotId));
        ASSERT_TRUE(callPeerDimensionsInfoData.WriteRawData(
            (const void *)&callPeerDimensionsInfo, sizeof(ImsCallPeerDimensionsInfo)));
        ASSERT_EQ(stubTestEleven->OnPeerDimensionsChangedInner(
            callPeerDimensionsInfoData, callPeerDimensionsInfoReply), TELEPHONY_SUCCESS);
        MessageParcel callDataUsageInfoData;
        MessageParcel callDataUsageInfoReply;
        ImsCallDataUsageInfo callDataUsageInfo;
        callDataUsageInfo.callIndex = DEFAULT_INDEX;
        ASSERT_TRUE(callDataUsageInfoData.WriteInt32(slotId));
        ASSERT_TRUE(callDataUsageInfoData.WriteRawData(
            (const void *)&callDataUsageInfo, sizeof(ImsCallDataUsageInfo)));
        ASSERT_EQ(stubTestEleven->OnCallDataUsageChangedInner(
            callDataUsageInfoData, callDataUsageInfoReply), TELEPHONY_SUCCESS);
        MessageParcel cameraCapabilitiesInfoData;
        MessageParcel cameraCapabilitiesInfoReply;
        CameraCapabilitiesInfo cameraCapabilitiesInfo;
        cameraCapabilitiesInfo.callIndex = DEFAULT_INDEX;
        ASSERT_TRUE(cameraCapabilitiesInfoData.WriteInt32(slotId));
        ASSERT_TRUE(cameraCapabilitiesInfoData.WriteRawData(
            (const void *)&cameraCapabilitiesInfo, sizeof(CameraCapabilitiesInfo)));
        ASSERT_EQ(stubTestEleven->OnCameraCapabilitiesChangedInner(
            cameraCapabilitiesInfoData, cameraCapabilitiesInfoReply), TELEPHONY_SUCCESS);
    }
}
/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0013
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0013, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stub = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stub != nullptr);
    for (int32_t slotId = 0; slotId < SLOT_COUNT; slotId++) {
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

        MessageParcel imsCallsData;
        MessageParcel imsCallsReply;
        ASSERT_TRUE(imsCallsData.WriteInt32(slotId));
        ASSERT_TRUE(imsCallsData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stub->OnGetImsCallsDataResponseInner(imsCallsData, imsCallsReply), TELEPHONY_SUCCESS);

        MessageParcel hangupData;
        MessageParcel hangupReply;
        ASSERT_TRUE(hangupData.WriteInt32(slotId));
        ASSERT_TRUE(hangupData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stub->OnHangUpResponseInner(hangupData, hangupReply), TELEPHONY_SUCCESS);

        MessageParcel holdCallData;
        MessageParcel holdCallReply;
        ASSERT_TRUE(holdCallData.WriteInt32(slotId));
        ASSERT_TRUE(holdCallData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stub->OnHoldCallResponseInner(holdCallData, holdCallReply), TELEPHONY_SUCCESS);

        MessageParcel rejectData;
        MessageParcel rejectReply;
        ASSERT_TRUE(rejectData.WriteInt32(slotId));
        ASSERT_TRUE(rejectData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stub->OnRejectResponseInner(rejectData, rejectReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0014
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0014, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stubTestTwo = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestTwo != nullptr);
    for (int32_t slotId = 0; slotId < SLOT_COUNT; slotId++) {
        RadioResponseInfo rilRadioResponse;
        rilRadioResponse.error = ErrType::ERR_GENERIC_FAILURE;
        MessageParcel sendDtmfData;
        MessageParcel sendDtmfReply;
        ASSERT_TRUE(sendDtmfData.WriteInt32(slotId));
        ASSERT_TRUE(sendDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_GE(stubTestTwo->OnSendDtmfResponseInner(sendDtmfData, sendDtmfReply), TELEPHONY_SUCCESS);

        MessageParcel setImsSwitchData;
        MessageParcel setImsSwitchReply;
        ASSERT_TRUE(setImsSwitchData.WriteInt32(slotId));
        ASSERT_TRUE(setImsSwitchData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stubTestTwo->OnSetImsSwitchResponseInner(setImsSwitchData, setImsSwitchReply), TELEPHONY_SUCCESS);

        MessageParcel startDtmfData;
        MessageParcel startDtmfReply;
        ASSERT_TRUE(startDtmfData.WriteInt32(slotId));
        ASSERT_TRUE(startDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stubTestTwo->OnStartDtmfResponseInner(startDtmfData, startDtmfReply), TELEPHONY_SUCCESS);

        MessageParcel stopDtmfData;
        MessageParcel stopDtmfReply;
        ASSERT_TRUE(stopDtmfData.WriteInt32(slotId));
        ASSERT_TRUE(stopDtmfData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stubTestTwo->OnStopDtmfResponseInner(stopDtmfData, stopDtmfReply), TELEPHONY_SUCCESS);

        MessageParcel switchCallData;
        MessageParcel switchCallReply;
        ASSERT_TRUE(switchCallData.WriteInt32(slotId));
        ASSERT_TRUE(switchCallData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stubTestTwo->OnSwitchCallResponseInner(switchCallData, switchCallReply), TELEPHONY_SUCCESS);

        MessageParcel unholdData;
        MessageParcel unholdReply;
        ASSERT_TRUE(unholdData.WriteInt32(slotId));
        ASSERT_TRUE(unholdData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stubTestTwo->OnUnHoldCallResponseInner(unholdData, unholdReply), TELEPHONY_SUCCESS);

        MessageParcel getImsSwitchData;
        MessageParcel getImsSwitchReply;
        ASSERT_TRUE(getImsSwitchData.WriteInt32(slotId));
        ASSERT_TRUE(getImsSwitchData.WriteRawData((const void *)&rilRadioResponse, sizeof(RadioResponseInfo)));
        ASSERT_EQ(stubTestTwo->OnGetImsSwitchResponseInner(getImsSwitchData, getImsSwitchReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0015
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0015, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stubTestThree = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestThree != nullptr);
    for (int32_t slotId = 0; slotId < SLOT_COUNT; slotId++) {
        MessageParcel data;
        MessageParcel reply;
        ASSERT_TRUE(data.WriteInt32(slotId));
        ASSERT_NE(stubTestThree->OnAnswerResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnCallRingBackReportInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnDialResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnHangUpResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnHoldCallResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnRejectResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnSendDtmfResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnSetImsSwitchResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnStartDtmfResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnStopDtmfResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnSwitchCallResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnUnHoldCallResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnSetMuteResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnCombineConferenceResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnInviteToConferenceResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnReceiveUpdateCallMediaModeRequestInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnReceiveUpdateCallMediaModeResponseInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnCallSessionEventChangedInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnPeerDimensionsChangedInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnCallDataUsageChangedInner(data, reply), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestThree->OnCameraCapabilitiesChangedInner(data, reply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0016
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0016, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stubTestFour = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestFour != nullptr);
    for (int32_t slotId = 0; slotId < SLOT_COUNT; slotId++) {
        SsBaseResult normalResult;
        normalResult.index = DEFAULT_INDEX;
        MessageParcel crData;
        MessageParcel crReply;
        ASSERT_TRUE(crData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(crData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetCallRestrictionResponseInner(crData, crReply), TELEPHONY_SUCCESS);
        MessageParcel ctData;
        MessageParcel ctReply;
        ASSERT_TRUE(ctData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(ctData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetCallTransferResponseInner(ctData, ctReply), TELEPHONY_SUCCESS);
        MessageParcel cwData;
        MessageParcel cwReply;
        ASSERT_TRUE(cwData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(cwData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetCallWaitingResponseInner(cwData, cwReply), TELEPHONY_SUCCESS);
        MessageParcel clipData;
        MessageParcel clipReply;
        ASSERT_TRUE(clipData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(clipData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetClipResponseInner(clipData, clipReply), TELEPHONY_SUCCESS);
        MessageParcel clirData;
        MessageParcel clirReply;
        ASSERT_TRUE(clirData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(clirData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetClirResponseInner(clirData, clirReply), TELEPHONY_SUCCESS);
        MessageParcel colpData;
        MessageParcel colpReply;
        ASSERT_TRUE(colpData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(colpData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetColpResponseInner(colpData, colpReply), TELEPHONY_SUCCESS);
        MessageParcel colrData;
        MessageParcel colrReply;
        ASSERT_TRUE(colrData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(colrData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFour->OnSetColrResponseInner(colrData, colrReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0017
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0017, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stubTestFive = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestFive != nullptr);
    for (int32_t slotId = 0; slotId < SLOT_COUNT; slotId++) {
        SsBaseResult normalResult;
        normalResult.index = INVALID_INDEX;
        MessageParcel crData;
        MessageParcel crReply;
        ASSERT_TRUE(crData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(crData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetCallRestrictionResponseInner(crData, crReply), TELEPHONY_SUCCESS);
        MessageParcel ctData;
        MessageParcel ctReply;
        ASSERT_TRUE(ctData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(ctData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetCallTransferResponseInner(ctData, ctReply), TELEPHONY_SUCCESS);
        MessageParcel cwData;
        MessageParcel cwReply;
        ASSERT_TRUE(cwData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(cwData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetCallWaitingResponseInner(cwData, cwReply), TELEPHONY_SUCCESS);
        MessageParcel clipData;
        MessageParcel clipReply;
        ASSERT_TRUE(clipData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(clipData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetClipResponseInner(clipData, clipReply), TELEPHONY_SUCCESS);
        MessageParcel clirData;
        MessageParcel clirReply;
        ASSERT_TRUE(clirData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(clirData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetClirResponseInner(clirData, clirReply), TELEPHONY_SUCCESS);
        MessageParcel colpData;
        MessageParcel colpReply;
        ASSERT_TRUE(colpData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(colpData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetColpResponseInner(colpData, colpReply), TELEPHONY_SUCCESS);
        MessageParcel colrData;
        MessageParcel colrReply;
        ASSERT_TRUE(colrData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(colrData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestFive->OnSetColrResponseInner(colrData, colrReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0018
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0018, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stubTestSix = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestSix != nullptr);
    for (int32_t slotId = 0; slotId < SLOT_COUNT; slotId++) {
        SsBaseResult ssBaseResult;
        ssBaseResult.index = DEFAULT_INDEX;
        ssBaseResult.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stubTestSix->SetCallRestrictionResponse(slotId, ssBaseResult), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestSix->SetCallTransferResponse(slotId, ssBaseResult), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestSix->SetCallWaitingResponse(slotId, ssBaseResult), TELEPHONY_SUCCESS);
        ASSERT_NE(stubTestSix->SetClirResponse(slotId, ssBaseResult), TELEPHONY_SUCCESS);
        MessageParcel muteData;
        MessageParcel muteReply;
        MuteControlResponse muteResponse;
        ASSERT_TRUE(muteData.WriteInt32(slotId));
        ASSERT_TRUE(muteData.WriteRawData((const void *)&muteResponse, sizeof(MuteControlResponse)));
        ASSERT_EQ(stubTestSix->OnSetMuteResponseInner(muteData, muteReply), TELEPHONY_SUCCESS);
        MessageParcel ringData;
        MessageParcel ringReply;
        RingbackVoice ringback;
        ASSERT_TRUE(ringData.WriteInt32(slotId));
        ASSERT_TRUE(ringData.WriteRawData((const void *)&ringback, sizeof(RingbackVoice)));
        ASSERT_EQ(stubTestSix->OnCallRingBackReportInner(ringData, ringReply), TELEPHONY_SUCCESS);
        MessageParcel failData;
        MessageParcel failReply;
        DisconnectedDetails details;
        ASSERT_TRUE(failData.WriteInt32(slotId));
        ASSERT_TRUE(failData.WriteInt32(static_cast<int32_t>(details.reason)));
        ASSERT_TRUE(failData.WriteString(details.message));
        ASSERT_EQ(stubTestSix->OnLastCallFailReasonResponseInner(failData, failReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0019
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0019, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stubTestSeven = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestSeven != nullptr);
    for (int32_t slotId = 0; slotId < SLOT_COUNT; slotId++) {
        CallRestrictionResult crResult;
        crResult.result.index = INVALID_INDEX;
        MessageParcel crErrorData;
        MessageParcel crErrorReply;
        ASSERT_TRUE(crErrorData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsResult(crErrorData, crResult.result, crResult.status, crResult.classCw), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestSeven->OnGetCallRestrictionResponseInner(crErrorData, crErrorReply), TELEPHONY_SUCCESS);

        crResult.result.index = DEFAULT_INDEX;
        MessageParcel crData;
        MessageParcel crReply;
        ASSERT_TRUE(crData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsResult(crData, crResult.result, crResult.status, crResult.classCw), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestSeven->OnGetCallRestrictionResponseInner(crData, crReply), TELEPHONY_SUCCESS);
        crResult.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stubTestSeven->GetCallRestrictionResponse(slotId, crResult), TELEPHONY_SUCCESS);

        CallForwardQueryInfoList callList;
        callList.result.index = INVALID_INDEX;
        MessageParcel ctErrorData;
        MessageParcel ctErrorReply;
        ASSERT_TRUE(ctErrorData.WriteInt32(slotId));
        ASSERT_EQ(WriteCallForwardResult(ctErrorData, callList), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestSeven->OnGetCallTransferResponseInner(ctErrorData, ctErrorReply), TELEPHONY_SUCCESS);

        callList.result.index = DEFAULT_INDEX;
        MessageParcel ctData;
        MessageParcel ctReply;
        ASSERT_TRUE(ctData.WriteInt32(slotId));
        ASSERT_EQ(WriteCallForwardResult(ctData, callList), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestSeven->OnGetCallTransferResponseInner(ctData, ctReply), TELEPHONY_SUCCESS);
        callList.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stubTestSeven->GetCallTransferResponse(slotId, callList), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0020
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0020, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stubTestEigth = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestEigth != nullptr);
    for (int32_t slotId = 0; slotId < SLOT_COUNT; slotId++) {
        CallWaitResult cwResult;
        cwResult.result.index = INVALID_INDEX;
        MessageParcel cwErrorData;
        MessageParcel cwErrorReply;
        ASSERT_TRUE(cwErrorData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsResult(cwErrorData, cwResult.result, cwResult.status, cwResult.classCw), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestEigth->OnGetCallWaitingResponseInner(cwErrorData, cwErrorReply), TELEPHONY_SUCCESS);

        cwResult.result.index = DEFAULT_INDEX;
        MessageParcel cwData;
        MessageParcel cwReply;
        ASSERT_TRUE(cwData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsResult(cwData, cwResult.result, cwResult.status, cwResult.classCw), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestEigth->OnGetCallWaitingResponseInner(cwData, cwReply), TELEPHONY_SUCCESS);
        cwResult.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stubTestEigth->GetCallWaitingResponse(slotId, cwResult), TELEPHONY_SUCCESS);

        GetClipResult clipResult;
        clipResult.result.index = INVALID_INDEX;
        MessageParcel clipErrorData;
        MessageParcel clipErrorReply;
        ASSERT_TRUE(clipErrorData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(clipErrorData, clipResult.result, clipResult.action, clipResult.clipStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestEigth->OnGetClipResponseInner(clipErrorData, clipErrorReply), TELEPHONY_SUCCESS);

        clipResult.result.index = DEFAULT_INDEX;
        MessageParcel clipData;
        MessageParcel clipReply;
        ASSERT_TRUE(clipData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(clipData, clipResult.result, clipResult.action, clipResult.clipStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestEigth->OnGetClipResponseInner(clipData, clipReply), TELEPHONY_SUCCESS);
        clipResult.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stubTestEigth->GetClipResponse(slotId, clipResult), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0021
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0021, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stubTestNight = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestNight != nullptr);
    for (int32_t slotId = 0; slotId < SLOT_COUNT; slotId++) {
        GetClirResult clirResult;
        clirResult.result.index = INVALID_INDEX;
        MessageParcel clirErrorData;
        MessageParcel clirErrorReply;
        ASSERT_TRUE(clirErrorData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(clirErrorData, clirResult.result, clirResult.action, clirResult.clirStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestNight->OnGetClirResponseInner(clirErrorData, clirErrorReply), TELEPHONY_SUCCESS);

        clirResult.result.index = DEFAULT_INDEX;
        MessageParcel clirData;
        MessageParcel clirReply;
        ASSERT_TRUE(clirData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(clirData, clirResult.result, clirResult.action, clirResult.clirStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestNight->OnGetClirResponseInner(clirData, clirReply), TELEPHONY_SUCCESS);
        clirResult.result.result = IMS_ERROR_UT_CS_FALLBACK;
        ASSERT_NE(stubTestNight->GetClirResponse(slotId, clirResult), TELEPHONY_SUCCESS);

        GetColpResult colpResult;
        colpResult.result.index = INVALID_INDEX;
        MessageParcel colpErrorData;
        MessageParcel colpErrorReply;
        ASSERT_TRUE(colpErrorData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(colpErrorData, colpResult.result, colpResult.action, colpResult.colpStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestNight->OnGetColpResponseInner(colpErrorData, colpErrorReply), TELEPHONY_SUCCESS);

        colpResult.result.index = DEFAULT_INDEX;
        MessageParcel colpData;
        MessageParcel colpReply;
        ASSERT_TRUE(colpData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(colpData, colpResult.result, colpResult.action, colpResult.colpStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestNight->OnGetColpResponseInner(colpData, colpReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0022
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0022, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stubTestTen = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestTen != nullptr);
    for (int32_t slotId = 0; slotId < SLOT_COUNT; slotId++) {
        GetColrResult colrResult;
        colrResult.result.index = INVALID_INDEX;
        MessageParcel colrErrorData;
        MessageParcel colrErrorReply;
        ASSERT_TRUE(colrErrorData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(colrErrorData, colrResult.result, colrResult.action, colrResult.colrStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestTen->OnGetColrResponseInner(colrErrorData, colrErrorReply), TELEPHONY_SUCCESS);

        colrResult.result.index = DEFAULT_INDEX;
        MessageParcel colrData;
        MessageParcel colrReply;
        ASSERT_TRUE(colrData.WriteInt32(slotId));
        ASSERT_EQ(
            WriteSsResult(colrData, colrResult.result, colrResult.action, colrResult.colrStat), TELEPHONY_SUCCESS);
        ASSERT_EQ(stubTestTen->OnGetColrResponseInner(colrData, colrReply), TELEPHONY_SUCCESS);

        SsBaseResult normalResult;
        normalResult.index = DEFAULT_INDEX;
        MessageParcel ctErrorData;
        MessageParcel ctReply;
        ASSERT_TRUE(ctErrorData.WriteInt32(slotId));
        ASSERT_EQ(WriteSsBaseResult(ctErrorData, normalResult), TELEPHONY_SUCCESS);
        ASSERT_TRUE(ctErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_TRUE(ctErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_TRUE(ctErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_NE(stubTestTen->OnGetCallTransferResponseInner(ctErrorData, ctReply), TELEPHONY_SUCCESS);

        MessageParcel icErrorData;
        MessageParcel icReply;
        ASSERT_TRUE(icErrorData.WriteInt32(slotId));
        ASSERT_TRUE(icErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_TRUE(icErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_TRUE(icErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_TRUE(icErrorData.WriteInt32(INVALID_INDEX));
        ASSERT_NE(stubTestTen->OnGetImsCallsDataResponseInner(icErrorData, icReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0023
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0023, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stubTestEleven = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestEleven != nullptr);
    for (int32_t slotId = 0; slotId < SLOT_COUNT; slotId++) {
        MessageParcel callModeReceiveRequestData;
        MessageParcel callModeReceiveRequestReply;
        ImsCallModeReceiveInfo callModeReceiveRequesInfo;
        callModeReceiveRequesInfo.callIndex = DEFAULT_INDEX;
        ASSERT_TRUE(callModeReceiveRequestData.WriteInt32(slotId));
        ASSERT_TRUE(callModeReceiveRequestData.WriteRawData(
            (const void *)&callModeReceiveRequesInfo, sizeof(ImsCallModeReceiveInfo)));
        ASSERT_EQ(stubTestEleven->OnReceiveUpdateCallMediaModeRequestInner(
            callModeReceiveRequestData, callModeReceiveRequestReply), TELEPHONY_SUCCESS);
        MessageParcel callModeReceiveResponseData;
        MessageParcel callModeReceiveResponseReply;
        ImsCallModeReceiveInfo callModeReceiveResponseInfo;
        callModeReceiveResponseInfo.callIndex = DEFAULT_INDEX;
        ASSERT_TRUE(callModeReceiveResponseData.WriteInt32(slotId));
        ASSERT_TRUE(callModeReceiveResponseData.WriteRawData(
            (const void *)&callModeReceiveResponseInfo, sizeof(ImsCallModeReceiveInfo)));
        ASSERT_EQ(stubTestEleven->OnReceiveUpdateCallMediaModeResponseInner(
            callModeReceiveResponseData, callModeReceiveResponseReply), TELEPHONY_SUCCESS);
        MessageParcel callSessionEventInfoData;
        MessageParcel callSessionEventInfoReply;
        ImsCallSessionEventInfo callSessionEventInfo;
        callSessionEventInfo.callIndex = DEFAULT_INDEX;
        ASSERT_TRUE(callSessionEventInfoData.WriteInt32(slotId));
        ASSERT_TRUE(callSessionEventInfoData.WriteRawData(
            (const void *)&callSessionEventInfo, sizeof(ImsCallSessionEventInfo)));
        ASSERT_EQ(stubTestEleven->OnCallSessionEventChangedInner(
            callSessionEventInfoData, callSessionEventInfoReply), TELEPHONY_SUCCESS);
    }
}

/**
 * @tc.number   cellular_call_ImsCallCallbackStub_0024
 * @tc.name     Test for ImsCallCallbackStub
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackStubTest, cellular_call_ImsCallCallbackStub_0024, Function | MediumTest | Level3)
{
    sptr<ImsCallCallbackStub> stubTestEleven = (std::make_unique<ImsCallCallbackStub>()).release();
    ASSERT_TRUE(stubTestEleven != nullptr);
    for (int32_t slotId = 0; slotId < SLOT_COUNT; slotId++) {
        MessageParcel callPeerDimensionsInfoData;
        MessageParcel callPeerDimensionsInfoReply;
        ImsCallPeerDimensionsInfo callPeerDimensionsInfo;
        callPeerDimensionsInfo.callIndex = DEFAULT_INDEX;
        ASSERT_TRUE(callPeerDimensionsInfoData.WriteInt32(slotId));
        ASSERT_TRUE(callPeerDimensionsInfoData.WriteRawData(
            (const void *)&callPeerDimensionsInfo, sizeof(ImsCallPeerDimensionsInfo)));
        ASSERT_EQ(stubTestEleven->OnPeerDimensionsChangedInner(
            callPeerDimensionsInfoData, callPeerDimensionsInfoReply), TELEPHONY_SUCCESS);
        MessageParcel callDataUsageInfoData;
        MessageParcel callDataUsageInfoReply;
        ImsCallDataUsageInfo callDataUsageInfo;
        callDataUsageInfo.callIndex = DEFAULT_INDEX;
        ASSERT_TRUE(callDataUsageInfoData.WriteInt32(slotId));
        ASSERT_TRUE(callDataUsageInfoData.WriteRawData(
            (const void *)&callDataUsageInfo, sizeof(ImsCallDataUsageInfo)));
        ASSERT_EQ(stubTestEleven->OnCallDataUsageChangedInner(
            callDataUsageInfoData, callDataUsageInfoReply), TELEPHONY_SUCCESS);
        MessageParcel cameraCapabilitiesInfoData;
        MessageParcel cameraCapabilitiesInfoReply;
        CameraCapabilitiesInfo cameraCapabilitiesInfo;
        cameraCapabilitiesInfo.callIndex = DEFAULT_INDEX;
        ASSERT_TRUE(cameraCapabilitiesInfoData.WriteInt32(slotId));
        ASSERT_TRUE(cameraCapabilitiesInfoData.WriteRawData(
            (const void *)&cameraCapabilitiesInfo, sizeof(CameraCapabilitiesInfo)));
        ASSERT_EQ(stubTestEleven->OnCameraCapabilitiesChangedInner(
            cameraCapabilitiesInfoData, cameraCapabilitiesInfoReply), TELEPHONY_SUCCESS);
    }
}
} // namespace Telephony
} // namespace OHOS
