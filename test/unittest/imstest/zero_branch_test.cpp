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
#include "cellular_call_connection_ims.h"
#include "cellular_call_handler.h"
#include "cellular_call_proxy.h"
#include "cellular_call_register.h"
#include "cellular_call_service.h"
#include "cellular_call_supplement.h"
#include "config_request.h"
#include "control_base.h"
#include "cs_control.h"
#include "gtest/gtest.h"
#include "tel_ril_call_parcel.h"
#include "ims_call_callback_proxy.h"
#include "ims_call_callback_stub.h"
#include "ims_call_client.h"
#include "ims_control.h"
#include "ims_error.h"
#include "token.h"
#include "securec.h"
#include "cellular_call_hisysevent.h"
#include "standardize_utils.h"
#include "cellular_call_rdb_helper.h"
#include "cellular_call_dump_helper.h"
#include "emergency_utils.h"
#include "satellite_call_client.h"
#include "ims_video_call_control.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;

#ifdef CALL_MANAGER_AUTO_START_OPTIMIZE
static const int32_t INVALID_VALUE = -1;
#endif

namespace {
const int32_t INVALID_SLOTID = 2;
const int32_t SIM1_SLOTID = 0;
const int32_t SIM2_SLOTID = 1;
const std::string PHONE_NUMBER = "00000000";
const int32_t DEFAULT_INDEX = 1;
} // namespace

class DemoHandler : public AppExecFwk::EventHandler {
public:
    explicit DemoHandler(std::shared_ptr<AppExecFwk::EventRunner> &runner) : AppExecFwk::EventHandler(runner) {}
    virtual ~DemoHandler() {}
    void ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event) {}
};

class ZeroBranchTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
    int32_t InitCellularCallInfo(int32_t accountId, std::string phonenumber, CellularCallInfo &callInfo);
    void InitImsCallInfoList(ImsCurrentCallList &callInfoList, int32_t num);
    void InitCsCallInfoList(CallInfoList &callInfoList, int32_t num);
    void MakeCallInfoParcelData(bool isError, MessageParcel &data);
};

void ZeroBranchTest::SetUpTestCase()
{
    std::cout << "---------- CellularCallService start ------------" << std::endl;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    DelayedSingleton<ImsCallClient>::GetInstance()->Init();
}

void ZeroBranchTest::TearDownTestCase() {}

void ZeroBranchTest::SetUp() {}

void ZeroBranchTest::TearDown() {}


int32_t ZeroBranchTest::InitCellularCallInfo(int32_t accountId, std::string phonenumber, CellularCallInfo &callInfo)
{
    callInfo.accountId = accountId;
    callInfo.slotId = accountId;
    callInfo.index = accountId;
    callInfo.callType = CallType::TYPE_IMS;
    callInfo.videoState = 0; // 0 means audio
    if (memset_s(callInfo.phoneNum, kMaxNumberLen, 0, kMaxNumberLen) != EOK) {
        return TELEPHONY_ERR_MEMSET_FAIL;
    }
    if (phonenumber.length() > static_cast<size_t>(kMaxNumberLen)) {
        return CALL_ERR_NUMBER_OUT_OF_RANGE;
    }
    if (memcpy_s(callInfo.phoneNum, kMaxNumberLen, phonenumber.c_str(), phonenumber.length()) != EOK) {
        return TELEPHONY_ERR_MEMCPY_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

void ZeroBranchTest::InitImsCallInfoList(ImsCurrentCallList &callInfoList, int32_t num)
{
    callInfoList.callSize = num;
    ImsCurrentCall call;
    int32_t callStateSum = 6;
    for (int32_t i = 0; i < num; ++i) {
        call.index = i;
        call.state = i % callStateSum;
        callInfoList.calls.push_back(call);
    }
}

void ZeroBranchTest::MakeCallInfoParcelData(bool isError, MessageParcel &data)
{
    if (isError) {
        int32_t errorSize = 0;
        data.WriteInt32(errorSize);
    } else {
        CellularCallInfo callInfo;
        callInfo.slotId = -1;
        int32_t size = 1;
        data.WriteInt32(size);
        data.WriteRawData(static_cast<const void *>(&callInfo), sizeof(CellularCallInfo));
    }
}

void ZeroBranchTest::InitCsCallInfoList(CallInfoList &callInfoList, int32_t num)
{
    callInfoList.callSize = num;
    CallInfo call;
    int32_t callStateSum = 9;
    for (int32_t i = 0; i < num; ++i) {
        call.index = i;
        call.state = i % callStateSum;
        callInfoList.calls.push_back(call);
    }
}

/**
 * @tc.number   Telephony_CellularCallConfig_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallConfig_001, TestSize.Level1)
{
    AccessToken token;
    CellularCallConfig config;
    config.SetDomainPreferenceMode(SIM1_SLOTID, 1);
    config.SetDomainPreferenceMode(SIM1_SLOTID, -1);
    config.GetDomainPreferenceMode(SIM1_SLOTID);
    bool enabled = false;
    config.SetImsSwitchStatus(INVALID_SLOTID, enabled);
    config.SetImsSwitchStatus(SIM1_SLOTID, enabled);
    config.volteSupported_[SIM1_SLOTID] = true;
    config.volteSupported_[INVALID_SLOTID] = true;
    config.volteProvisioningSupported_[SIM1_SLOTID] = true;
    config.volteProvisioningSupported_[INVALID_SLOTID] = true;
    config.SetImsSwitchStatus(INVALID_SLOTID, enabled);
    config.SetImsSwitchStatus(SIM1_SLOTID, true);
    config.volteSupported_[SIM1_SLOTID] = enabled;
    config.volteSupported_[INVALID_SLOTID] = enabled;
    config.volteProvisioningSupported_[SIM1_SLOTID] = enabled;
    config.volteProvisioningSupported_[INVALID_SLOTID] = enabled;
    config.GetImsSwitchStatus(SIM1_SLOTID, enabled);
    config.saveImsSwitchStatusToLocalForPowerOn(SIM1_SLOTID);
    config.saveImsSwitchStatusToLocal(SIM1_SLOTID, true);
    config.GetImsSwitchStatus(SIM1_SLOTID, enabled);
    int32_t state = 0;
    config.SetVoNRSwitchStatus(SIM1_SLOTID, state);
    config.SetVoNRSwitchStatus(INVALID_SLOTID, state);
    config.GetVoNRSwitchStatus(SIM1_SLOTID, state);
    config.GetVoNRSwitchStatus(SIM2_SLOTID, state);
    config.GetDomainPreferenceModeResponse(SIM1_SLOTID, 1);
    config.GetImsSwitchStatusResponse(SIM1_SLOTID, 1);
    config.GetPreferenceMode(SIM1_SLOTID);
    std::string value = "";
    config.SetImsConfig(ImsConfigItem::ITEM_VIDEO_QUALITY, value);
    config.SetImsConfig(ImsConfigItem::ITEM_VIDEO_QUALITY, 1);
    config.GetImsConfig(ImsConfigItem::ITEM_VIDEO_QUALITY);
    config.SetImsFeatureValue(FeatureType::TYPE_VOICE_OVER_LTE, 1);
    int32_t res = config.GetImsFeatureValue(FeatureType::TYPE_VOICE_OVER_LTE);
    config.HandleFactoryReset(0);
    config.HandleFactoryReset(1);
#ifdef CALL_MANAGER_AUTO_START_OPTIMIZE
    ASSERT_EQ(res, CALL_ERR_RESOURCE_UNAVAILABLE);
#else
    ASSERT_EQ(res, TELEPHONY_SUCCESS);
#endif
}

/**
 * @tc.number   Telephony_CellularCallConfig_002
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallConfig_002, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallConfig config;
    config.SetMute(SIM1_SLOTID, 0);
    config.GetMute(SIM1_SLOTID);
    config.GetEmergencyCallList(SIM1_SLOTID);
    std::vector<EmergencyCall> eccVec = {};
    config.SetEmergencyCallList(SIM1_SLOTID, eccVec);
    config.SetTempMode(SIM1_SLOTID);
    config.InitModeActive();
    EmergencyInfoList eccList;
    config.UpdateEmergencyCallFromRadio(SIM1_SLOTID, eccList);
    config.GetEccCallList(SIM1_SLOTID);
    config.GetMcc(SIM1_SLOTID);
    config.SetReadyToCall(SIM1_SLOTID, true);
    config.SetReadyToCall(INVALID_SLOTID, true);
    config.IsReadyToCall(SIM1_SLOTID);
    config.IsReadyToCall(INVALID_SLOTID);

    config.HandleSimStateChanged(SIM1_SLOTID);
    config.HandleSetLteImsSwitchResult(SIM1_SLOTID, ErrType::NONE);
    config.HandleSetVoNRSwitchResult(SIM1_SLOTID, ErrType::NONE);
    config.HandleSimRecordsLoaded(SIM1_SLOTID);
    config.HandleOperatorConfigChanged(SIM1_SLOTID, 0);
    config.UpdateImsConfiguration(SIM1_SLOTID, -1, false);
    OperatorConfig poc;
    config.ParseAndCacheOperatorConfigs(SIM1_SLOTID, poc);
    config.UpdateImsCapabilities(SIM1_SLOTID, true, false, -1);
    bool enabled = false;
    config.SaveImsSwitch(SIM1_SLOTID, true);
    config.IsUtProvisioned(SIM1_SLOTID);
    config.utProvisioningSupported_[SIM1_SLOTID] = true;
    config.IsUtProvisioned(SIM1_SLOTID);
    config.utProvisioningSupported_[SIM1_SLOTID] = enabled;
    config.ResetImsSwitch(SIM1_SLOTID);
    config.HandleSimAccountLoaded(SIM1_SLOTID);
    ASSERT_FALSE(config.utProvisioningSupported_[SIM1_SLOTID]);
}

/**
 * @tc.number   Telephony_CellularCallSupplement_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallSupplement_001, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallSupplement callSup;
    MMIData mmiDataEmp = {};
    MMIData mmiDataAct = { .actionString = "*" };
    MMIData mmiDataDeact = { .actionString = "#" };
    MMIData mmiDataInterrogate = { .actionString = "*#" };
    callSup.HandleClip(SIM1_SLOTID, mmiDataEmp);
    callSup.HandleClip(SIM1_SLOTID, mmiDataAct);
    callSup.HandleClip(SIM1_SLOTID, mmiDataDeact);
    callSup.HandleClip(SIM1_SLOTID, mmiDataInterrogate);
    callSup.HandleClir(SIM1_SLOTID, mmiDataEmp);
    callSup.HandleClir(SIM1_SLOTID, mmiDataAct);
    callSup.HandleClir(SIM1_SLOTID, mmiDataDeact);
    callSup.HandleClir(SIM1_SLOTID, mmiDataInterrogate);
    callSup.HandleColr(SIM1_SLOTID, mmiDataEmp);
    callSup.HandleColr(SIM1_SLOTID, mmiDataAct);
    callSup.HandleColr(SIM1_SLOTID, mmiDataDeact);
    callSup.HandleColr(SIM1_SLOTID, mmiDataInterrogate);
    callSup.HandleColp(SIM1_SLOTID, mmiDataEmp);
    callSup.HandleColp(SIM1_SLOTID, mmiDataAct);
    callSup.HandleColp(SIM1_SLOTID, mmiDataDeact);
    callSup.HandleColp(SIM1_SLOTID, mmiDataInterrogate);
    callSup.HandleCallTransfer(SIM1_SLOTID, mmiDataEmp);
    callSup.HandleCallTransfer(SIM1_SLOTID, mmiDataInterrogate);
    callSup.HandleCallTransfer(SIM1_SLOTID, mmiDataAct);
    callSup.HandleCallRestriction(SIM1_SLOTID, mmiDataEmp);
    callSup.HandleCallRestriction(SIM1_SLOTID, mmiDataAct);
    callSup.HandleCallRestriction(SIM1_SLOTID, mmiDataDeact);
    callSup.HandleCallRestriction(SIM1_SLOTID, mmiDataInterrogate);
    callSup.HandleCallWaiting(SIM1_SLOTID, mmiDataEmp);
    callSup.HandleCallWaiting(SIM1_SLOTID, mmiDataAct);
    callSup.HandleCallWaiting(SIM1_SLOTID, mmiDataDeact);
    ASSERT_EQ(callSup.ObtainCause("002"), static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_ALL));
    ASSERT_EQ(callSup.ObtainCause("004"), static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_CONDITIONAL));
    ASSERT_FALSE(mmiDataAct.actionString.empty());
}

/**
 * @tc.number   Telephony_CellularCallSupplement_002
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallSupplement_002, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallSupplement callSup;
    callSup.SendUssd(SIM1_SLOTID, "*#21#");
    PinPukResponse pinPuk;
    callSup.EventSetPinPuk(pinPuk);
    MMIData mmiDataPin = { .serviceInfoA = "1234", .serviceInfoB = "1111", .serviceInfoC = "1111" };
    callSup.AlterPinPassword(SIM1_SLOTID, mmiDataPin);
    callSup.UnlockPuk(SIM1_SLOTID, mmiDataPin);
    callSup.AlterPin2Password(SIM1_SLOTID, mmiDataPin);
    callSup.UnlockPuk2(SIM1_SLOTID, mmiDataPin);
    mmiDataPin = { .serviceInfoA = "1234", .serviceInfoB = "1111", .serviceInfoC = "1112" };
    callSup.AlterPinPassword(SIM1_SLOTID, mmiDataPin);
    callSup.UnlockPuk(SIM1_SLOTID, mmiDataPin);
    callSup.AlterPin2Password(SIM1_SLOTID, mmiDataPin);
    callSup.UnlockPuk2(SIM1_SLOTID, mmiDataPin);
    mmiDataPin = { .serviceInfoA = "1234", .serviceInfoB = "1111", .serviceInfoC = "111111111" };
    callSup.AlterPinPassword(SIM1_SLOTID, mmiDataPin);
    callSup.UnlockPuk(SIM1_SLOTID, mmiDataPin);
    callSup.AlterPin2Password(SIM1_SLOTID, mmiDataPin);
    callSup.UnlockPuk2(SIM1_SLOTID, mmiDataPin);
    callSup.CloseUnFinishedUssd(SIM1_SLOTID);
    GetClipResult getClipResult;
    std::string message = "";
    callSup.EventGetClip(getClipResult, message, 0);
    callSup.EventGetClip(getClipResult, message, 1);
    callSup.EventSetClip(0, message, 0, 1);
    callSup.EventSetClip(0, message, 1, 1);
    GetClirResult getClirResult;
    callSup.EventGetClir(getClirResult, message, 0);
    callSup.EventGetClir(getClirResult, message, 1);
    callSup.EventSetClir(0, message, 0, 1);
    callSup.EventSetClir(0, message, 1, 1);
    GetColrResult getColrResult;
    callSup.EventGetColr(getColrResult, message, 0);
    callSup.EventGetColr(getColrResult, message, 1);
    callSup.EventSetColr(0, message, 0, 1);
    callSup.EventSetColr(0, message, 1, 1);
    ASSERT_TRUE(mmiDataPin.actionString.empty());
}

/**
 * @tc.number   Telephony_CellularCallSupplement_003
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallSupplement_003, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallSupplement callSup;
    GetColpResult getColpResult;
    std::string message = "";
    callSup.EventGetColp(getColpResult, message, 0);
    callSup.EventGetColp(getColpResult, message, 1);
    callSup.EventSetColp(0, message, 0, 1);
    callSup.EventSetColp(0, message, 1, 1);
    CallRestrictionResult callResResult;
    callSup.EventGetCallRestriction(callResResult, message, 0);
    callSup.EventGetCallRestriction(callResResult, message, 1);
    callResResult.status = 1;
    callSup.EventGetCallRestriction(callResResult, message, 0);
    callResResult.result.result = 1;
    callSup.EventGetCallRestriction(callResResult, message, 0);
    callSup.EventSetCallRestriction(0, message, 0, 1);
    callSup.EventSetCallRestriction(0, message, 1, 1);
    callSup.EventSetBarringPassword(0, message, 0);
    callSup.EventSetBarringPassword(0, message, 1);
    callSup.EventSetCallWaiting(0, message, 0, 1);
    callSup.EventSetCallWaiting(0, message, 1, 1);
    CallForwardQueryInfoList cFQueryList;
    callSup.EventGetCallTransferInfo(cFQueryList, message, 0);
    CallForwardQueryResult queryResult;
    callSup.BuildCallForwardQueryInfo(queryResult, message, 0);
    callSup.BuildCallForwardQueryInfo(queryResult, message, 1);
    queryResult.classx = 1;
    callSup.BuildCallForwardQueryInfo(queryResult, message, 0);
    queryResult.status = 1;
    callSup.BuildCallForwardQueryInfo(queryResult, message, 0);
    queryResult.reason = 2;
    callSup.BuildCallForwardQueryInfo(queryResult, message, 0);
    std::string targetNumber = "1234567";
    callSup.EventSetCallTransferInfo(0, message, 0, 1, targetNumber);
    callSup.EventSetCallTransferInfo(0, message, 1, 1, targetNumber);
    RadioResponseInfo responseInfo;
    callSup.EventSendUssd(responseInfo);
    SsNoticeInfo ssNoticeInfo;
    callSup.EventSsNotify(ssNoticeInfo);
    UssdNoticeInfo ussdNoticeInfo;
    callSup.EventUssdNotify(ussdNoticeInfo, SIM1_SLOTID);
    RadioResponseInfo response;
    callSup.EventCloseUnFinishedUssd(response);
    callSup.GetCallTransferInfo(SIM1_SLOTID, CallTransferType::TRANSFER_TYPE_UNCONDITIONAL);
    ASSERT_EQ(callSup.GetCallTransferInfo(SIM2_SLOTID, CallTransferType::TRANSFER_TYPE_UNCONDITIONAL),
        TELEPHONY_ERR_LOCAL_PTR_NULL);
}

/**
 * @tc.number   Telephony_CellularCallSupplement_004
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallSupplement_004, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallSupplement callSup;
    CallWaitResult waitingInfo;
    std::string message = "";
    callSup.EventGetCallWaiting(waitingInfo, message, 0);
    callSup.EventGetCallWaiting(waitingInfo, message, 1);
    waitingInfo.status =1;
    callSup.EventGetCallWaiting(waitingInfo, message, 0);
    waitingInfo.classCw =1;
    callSup.EventGetCallWaiting(waitingInfo, message, 0);
    waitingInfo.classCw =4;
    callSup.EventGetCallWaiting(waitingInfo, message, 0);
    waitingInfo.classCw =8;
    callSup.EventGetCallWaiting(waitingInfo, message, 0);
    waitingInfo.classCw =16;
    callSup.EventGetCallWaiting(waitingInfo, message, 0);
    waitingInfo.classCw =32;
    callSup.EventGetCallWaiting(waitingInfo, message, 0);
    waitingInfo.classCw =64;
    callSup.EventGetCallWaiting(waitingInfo, message, 0);
    waitingInfo.classCw =128;
    callSup.EventGetCallWaiting(waitingInfo, message, 0);
    CallTransferInfo cfInfo;
    callSup.SetCallTransferInfo(SIM1_SLOTID, cfInfo);
    strcpy_s(cfInfo.transferNum, kMaxNumberLen + 1, "111");
    callSup.SetCallTransferInfo(SIM1_SLOTID, cfInfo);
    callSup.SetCallTransferInfo(SIM2_SLOTID, cfInfo);
    auto utCommand = std::make_shared<SsRequestCommand>();
    callSup.SetCallTransferInfoByIms(SIM1_SLOTID, cfInfo, utCommand);
    callSup.SetCallTransferInfoByIms(SIM2_SLOTID, cfInfo, utCommand);
    bool activate = false;
    callSup.SetCallWaiting(SIM1_SLOTID, activate);
    callSup.SetCallWaiting(SIM2_SLOTID, activate);
    callSup.GetCallWaiting(SIM1_SLOTID);
    callSup.GetCallWaiting(SIM2_SLOTID);
    CallRestrictionInfo crInfo;
    callSup.SetCallRestriction(SIM1_SLOTID, crInfo);
    callSup.SetCallRestriction(SIM2_SLOTID, crInfo);
    auto crCommand = std::make_shared<SsRequestCommand>();
    std::string info(crInfo.password);
    std::string fac("AO");
    callSup.SetCallRestrictionByIms(SIM1_SLOTID, fac, static_cast<int32_t>(crInfo.mode), info, crCommand);
    callSup.SetCallRestrictionByIms(SIM2_SLOTID, fac, static_cast<int32_t>(crInfo.mode), info, crCommand);
    callSup.GetCallRestriction(SIM1_SLOTID, CallRestrictionType::RESTRICTION_TYPE_ALL_INCOMING);
    callSup.GetCallRestriction(SIM2_SLOTID, CallRestrictionType::RESTRICTION_TYPE_ALL_INCOMING);
    callSup.SetBarringPassword(SIM1_SLOTID, CallRestrictionType::RESTRICTION_TYPE_ALL_INCOMING, "1111", "0000");
    ASSERT_NE(callSup.SetBarringPassword(SIM2_SLOTID, CallRestrictionType::RESTRICTION_TYPE_ALL_INCOMING,
        "1111", "0000"), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallSupplement_005
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallSupplement_005, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallSupplement callSup;
    MMIData mmiDataEmp = {};
    MMIData mmiDataAct = { .actionString = "*" };
    MMIData mmiDataDeact = { .actionString = "#" };
    MMIData mmiDataInterrogate = { .actionString = "*#" };
    callSup.HandleClip(SIM2_SLOTID, mmiDataEmp);
    callSup.HandleClip(SIM2_SLOTID, mmiDataAct);
    callSup.HandleClip(SIM2_SLOTID, mmiDataDeact);
    callSup.HandleClip(SIM2_SLOTID, mmiDataInterrogate);
    callSup.HandleColr(SIM2_SLOTID, mmiDataEmp);
    callSup.HandleColr(SIM2_SLOTID, mmiDataAct);
    callSup.HandleColr(SIM2_SLOTID, mmiDataDeact);
    callSup.HandleColr(SIM2_SLOTID, mmiDataInterrogate);
    callSup.HandleColp(SIM2_SLOTID, mmiDataEmp);
    callSup.HandleColp(SIM2_SLOTID, mmiDataAct);
    callSup.HandleColp(SIM2_SLOTID, mmiDataDeact);
    callSup.HandleColp(SIM2_SLOTID, mmiDataInterrogate);
    callSup.HandleCallTransfer(SIM2_SLOTID, mmiDataEmp);
    callSup.HandleCallTransfer(SIM2_SLOTID, mmiDataInterrogate);
    callSup.HandleCallTransfer(SIM2_SLOTID, mmiDataAct);
    callSup.HandleCallRestriction(SIM2_SLOTID, mmiDataEmp);
    callSup.HandleCallRestriction(SIM2_SLOTID, mmiDataAct);
    callSup.HandleCallRestriction(SIM2_SLOTID, mmiDataDeact);
    callSup.HandleCallRestriction(SIM2_SLOTID, mmiDataInterrogate);
    callSup.HandleCallWaiting(SIM2_SLOTID, mmiDataEmp);
    callSup.HandleCallWaiting(SIM2_SLOTID, mmiDataAct);
    callSup.HandleCallWaiting(SIM2_SLOTID, mmiDataDeact);
    bool enable = false;
#ifdef CALL_MANAGER_AUTO_START_OPTIMIZE
    ASSERT_EQ(callSup.CanSetCallTransferTime(SIM1_SLOTID, enable), CALL_ERR_RESOURCE_UNAVAILABLE);
#else
    ASSERT_EQ(callSup.CanSetCallTransferTime(SIM1_SLOTID, enable), TELEPHONY_SUCCESS);
#endif
}

/**
 * @tc.number   Telephony_CellularCallSupplement_006
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallSupplement_006, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallSupplement callSup;
    MMIData mmiDataEmp = {};
    MMIData mmiDataAct = { .actionString = "*" };
    MMIData mmiDataDeact = { .actionString = "#" };
    MMIData mmiDataInterrogate = { .actionString = "*#" };
    EventFwk::MatchingSkills matchingSkills;
    matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
    EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
    auto handler = std::make_shared<CellularCallHandler>(subscriberInfo);
    auto callClient = DelayedSingleton<SatelliteCallClient>::GetInstance();
    ASSERT_EQ(callClient->RegisterSatelliteCallCallbackHandler(SIM1_SLOTID, handler), TELEPHONY_SUCCESS);
    callSup.HandleClip(SIM1_SLOTID, mmiDataAct);
    callSup.HandleClip(SIM1_SLOTID, mmiDataDeact);
    callSup.HandleClip(SIM1_SLOTID, mmiDataInterrogate);
    callSup.HandleColr(SIM1_SLOTID, mmiDataAct);
    callSup.HandleColr(SIM1_SLOTID, mmiDataDeact);
    callSup.HandleColr(SIM1_SLOTID, mmiDataInterrogate);
    callSup.HandleColp(SIM1_SLOTID, mmiDataAct);
    callSup.HandleColp(SIM1_SLOTID, mmiDataDeact);
    callSup.HandleColp(SIM1_SLOTID, mmiDataInterrogate);
    int32_t cause = 0;
    callSup.HandleGetCallTransfer(SIM1_SLOTID, cause);
    int32_t serviceCode = 0;
    std::string phoneNumber("1234567890");
    CallTransferSettingType callTransferAction = CallTransferSettingType::CALL_TRANSFER_DISABLE;
    callSup.HandleSetCallTransfer(SIM1_SLOTID, serviceCode, cause, phoneNumber, callTransferAction);
    callSup.HandleCallRestriction(SIM1_SLOTID, mmiDataAct);
    callSup.HandleCallRestriction(SIM1_SLOTID, mmiDataDeact);
    callSup.HandleCallRestriction(SIM1_SLOTID, mmiDataInterrogate);
    callSup.HandleCallWaiting(SIM1_SLOTID, mmiDataAct);
    callSup.HandleCallWaiting(SIM1_SLOTID, mmiDataDeact);
    callSup.HandleCallWaiting(SIM1_SLOTID, mmiDataInterrogate);
}

/**
 * @tc.number   Telephony_CellularCallSupplement_007
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallSupplement_007, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallSupplement callSup;
    MMIData mmiDataEmp = {};
    MMIData mmiDataAct = { .actionString = "*" };
    MMIData mmiDataDeact = { .actionString = "#" };
    MMIData mmiDataInterrogate = { .actionString = "*#" };
    EventFwk::MatchingSkills matchingSkills;
    matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
    EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
    auto handler = std::make_shared<CellularCallHandler>(subscriberInfo);
    auto callClient = DelayedSingleton<SatelliteCallClient>::GetInstance();
    ASSERT_EQ(callClient->RegisterSatelliteCallCallbackHandler(SIM1_SLOTID, handler), TELEPHONY_SUCCESS);
    std::string serviceInfoB("10");
    ASSERT_EQ(callSup.ObtainServiceCode(serviceInfoB), 13);
    serviceInfoB = "11";
    ASSERT_EQ(callSup.ObtainServiceCode(serviceInfoB), 1);
    serviceInfoB = "12";
    ASSERT_EQ(callSup.ObtainServiceCode(serviceInfoB), 12);
    serviceInfoB = "13";
    ASSERT_EQ(callSup.ObtainServiceCode(serviceInfoB), 4);
    serviceInfoB = "16";
    ASSERT_EQ(callSup.ObtainServiceCode(serviceInfoB), 8);
    serviceInfoB = "19";
    ASSERT_EQ(callSup.ObtainServiceCode(serviceInfoB), 5);
    serviceInfoB = "20";
    ASSERT_EQ(callSup.ObtainServiceCode(serviceInfoB), 48);
    serviceInfoB = "21";
    ASSERT_EQ(callSup.ObtainServiceCode(serviceInfoB), 160);
    serviceInfoB = "22";
    ASSERT_EQ(callSup.ObtainServiceCode(serviceInfoB), 80);
    serviceInfoB = "24";
    ASSERT_EQ(callSup.ObtainServiceCode(serviceInfoB), 16);
    serviceInfoB = "25";
    ASSERT_EQ(callSup.ObtainServiceCode(serviceInfoB), 32);
    serviceInfoB = "99";
    ASSERT_EQ(callSup.ObtainServiceCode(serviceInfoB), 64);
    std::string phoneNumber("1234");
    CallTransferSettingType callTransferAction;
    ASSERT_EQ(callSup.ObtainCallTrasferAction("*", phoneNumber, callTransferAction), TELEPHONY_SUCCESS);
    ASSERT_EQ(callSup.ObtainCallTrasferAction("**", phoneNumber, callTransferAction), TELEPHONY_SUCCESS);
    ASSERT_EQ(callSup.ObtainCallTrasferAction("#", phoneNumber, callTransferAction), TELEPHONY_SUCCESS);
    ASSERT_EQ(callSup.ObtainCallTrasferAction("##", phoneNumber, callTransferAction), TELEPHONY_SUCCESS);
    ASSERT_EQ(callSup.ObtainCause("21"), static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_UNCONDITIONAL));
    ASSERT_EQ(callSup.ObtainCause("61"), static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_NO_REPLY));
    ASSERT_EQ(callSup.ObtainCause("62"), static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_NOT_REACHABLE));
    ASSERT_EQ(callSup.ObtainCause("67"), static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_BUSY));
    ASSERT_EQ(callSup.ObtainCause("99"), TELEPHONY_ERROR);
}

/**
 * @tc.number   Telephony_CellularCallSupplement_008
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallSupplement_008, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallSupplement callSup;
    EventFwk::MatchingSkills matchingSkills;
    matchingSkills.AddEvent(EventFwk::CommonEventSupport::COMMON_EVENT_OPERATOR_CONFIG_CHANGED);
    EventFwk::CommonEventSubscribeInfo subscriberInfo(matchingSkills);
    auto handler = std::make_shared<CellularCallHandler>(subscriberInfo);
    auto callClient = DelayedSingleton<SatelliteCallClient>::GetInstance();
    ASSERT_EQ(callClient->RegisterSatelliteCallCallbackHandler(SIM1_SLOTID, handler), TELEPHONY_SUCCESS);
    ASSERT_EQ(callSup.ObtainBarringInstallation("33"), "AO");
    ASSERT_EQ(callSup.ObtainBarringInstallation("331"), "OI");
    ASSERT_EQ(callSup.ObtainBarringInstallation("332"), "OX");
    ASSERT_EQ(callSup.ObtainBarringInstallation("351"), "IR");
    ASSERT_EQ(callSup.ObtainBarringInstallation("35"), "AI");
    ASSERT_EQ(callSup.ObtainBarringInstallation("330"), "AB");
    ASSERT_EQ(callSup.ObtainBarringInstallation("333"), "AG");
    ASSERT_EQ(callSup.ObtainBarringInstallation("353"), "AC");
    ASSERT_EQ(callSup.ObtainBarringInstallation("1000"), "");
    std::string fac;
    ASSERT_EQ(callSup.CheckCallRestrictionType(fac, CallRestrictionType::RESTRICTION_TYPE_ALL_OUTGOING),
        TELEPHONY_SUCCESS);
    ASSERT_EQ(callSup.CheckCallRestrictionType(fac, CallRestrictionType::RESTRICTION_TYPE_INTERNATIONAL),
        TELEPHONY_SUCCESS);
    ASSERT_EQ(callSup.CheckCallRestrictionType(fac,
        CallRestrictionType::RESTRICTION_TYPE_INTERNATIONAL_EXCLUDING_HOME), TELEPHONY_SUCCESS);
    ASSERT_EQ(callSup.CheckCallRestrictionType(fac, CallRestrictionType::RESTRICTION_TYPE_ALL_INCOMING),
        TELEPHONY_SUCCESS);
    ASSERT_EQ(callSup.CheckCallRestrictionType(fac, CallRestrictionType::RESTRICTION_TYPE_ROAMING_INCOMING),
        TELEPHONY_SUCCESS);
    ASSERT_EQ(callSup.CheckCallRestrictionType(fac, CallRestrictionType::RESTRICTION_TYPE_ALL_CALLS),
        TELEPHONY_SUCCESS);
    ASSERT_EQ(callSup.CheckCallRestrictionType(fac, CallRestrictionType::RESTRICTION_TYPE_OUTGOING_SERVICES),
        TELEPHONY_SUCCESS);
    ASSERT_EQ(callSup.CheckCallRestrictionType(fac, CallRestrictionType::RESTRICTION_TYPE_INCOMING_SERVICES),
        TELEPHONY_SUCCESS);
    MmiCodeInfo mmiCodeInfo;
    SsNoticeInfo ssNoticeInfo;
    ssNoticeInfo.result = 0;
    callSup.GetMessage(mmiCodeInfo, ssNoticeInfo);
    ssNoticeInfo.result = 1;
    ssNoticeInfo.serviceType = static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_UNCONDITIONAL);
    callSup.GetMessage(mmiCodeInfo, ssNoticeInfo);
    ssNoticeInfo.serviceType = static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_BUSY);
    callSup.GetMessage(mmiCodeInfo, ssNoticeInfo);
    ssNoticeInfo.serviceType = static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_NO_REPLY);
    callSup.GetMessage(mmiCodeInfo, ssNoticeInfo);
    ssNoticeInfo.serviceType = static_cast<int32_t>(CallTransferType::TRANSFER_TYPE_NOT_REACHABLE);
    callSup.GetMessage(mmiCodeInfo, ssNoticeInfo);
}

/**
 * @tc.number   Telephony_CellularCallSupplement_009
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallSupplement_009, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallSupplement callSup;
    MMIData mmiDataAct = { .actionString = "*" };
    auto command = std::make_shared<SsRequestCommand>();
    CallTransferInfo cfInfo;
#ifdef CALL_MANAGER_AUTO_START_OPTIMIZE
    ASSERT_EQ(callSup.SetCallTransferInfoByIms(SIM1_SLOTID, cfInfo, command), TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
#else
    ASSERT_EQ(callSup.SetCallTransferInfoByIms(SIM1_SLOTID, cfInfo, command), TELEPHONY_SUCCESS);
#endif
    ASSERT_EQ(callSup.SetCallTransferInfo(SIM1_SLOTID, cfInfo), TELEPHONY_ERR_ARGUMENT_INVALID);
    ASSERT_NE(callSup.GetCallTransferInfo(SIM1_SLOTID, CallTransferType::TRANSFER_TYPE_UNCONDITIONAL),
        TELEPHONY_SUCCESS);
    bool activate = true;
    ASSERT_EQ(callSup.SetCallWaiting(SIM1_SLOTID, activate), CALL_ERR_UNSUPPORTED_NETWORK_TYPE);
    ASSERT_EQ(callSup.GetCallWaiting(SIM1_SLOTID), CALL_ERR_UNSUPPORTED_NETWORK_TYPE);
    CallRestrictionInfo cRInfo;
    std::string info(cRInfo.password);
    std::string fac("AO");
#ifdef CALL_MANAGER_AUTO_START_OPTIMIZE
    ASSERT_EQ(callSup.SetCallRestrictionByIms(SIM1_SLOTID, fac, static_cast<int32_t>(cRInfo.mode), info, command),
        TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
#else
    ASSERT_EQ(callSup.SetCallRestrictionByIms(SIM1_SLOTID, fac, static_cast<int32_t>(cRInfo.mode), info, command),
        TELEPHONY_SUCCESS);
#endif
    ASSERT_EQ(callSup.GetCallRestriction(SIM1_SLOTID, CallRestrictionType::RESTRICTION_TYPE_ALL_INCOMING),
        CALL_ERR_UNSUPPORTED_NETWORK_TYPE);
    ASSERT_EQ(callSup.SetBarringPassword(SIM1_SLOTID, CallRestrictionType::RESTRICTION_TYPE_ALL_INCOMING,
        "1111", "0000"), CALL_ERR_UNSUPPORTED_NETWORK_TYPE);
    ASSERT_EQ(callSup.SetCallRestriction(SIM1_SLOTID, cRInfo), CALL_ERR_UNSUPPORTED_NETWORK_TYPE);
    callSup.AlterPinPassword(SIM1_SLOTID, mmiDataAct);
    callSup.UnlockPuk(SIM1_SLOTID, mmiDataAct);
    callSup.AlterPin2Password(SIM1_SLOTID, mmiDataAct);
    callSup.UnlockPuk2(SIM1_SLOTID, mmiDataAct);
    ASSERT_FALSE(callSup.IsVaildPinOrPuk("123", "123"));
    ASSERT_FALSE(callSup.IsVaildPinOrPuk("1234567", "123"));
    ASSERT_TRUE(callSup.IsVaildPinOrPuk("1234567", "1234567"));
}

/**
 * @tc.number   Telephony_CellularCallCsControl_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallCsControl_001, Function | MediumTest | Level3)
{
    AccessToken token;
    CSControl csControl;
    CellularCallInfo cellularCallInfo;
    InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, cellularCallInfo);
    CallInfoList callInfoList;
    csControl.ReportCsCallsData(SIM1_SLOTID, callInfoList);
    csControl.connectionMap_.insert(std::make_pair(1, CellularCallConnectionCS()));
    csControl.ReportCsCallsData(SIM1_SLOTID, callInfoList);
    csControl.connectionMap_.insert(std::make_pair(1, CellularCallConnectionCS()));
    InitCsCallInfoList(callInfoList, 5);
    csControl.ReportCsCallsData(SIM1_SLOTID, callInfoList);
    csControl.connectionMap_.clear();
    csControl.ReportCsCallsData(SIM1_SLOTID, callInfoList);
    bool enabled = false;
    csControl.Dial(cellularCallInfo, enabled);
    csControl.DialCdma(cellularCallInfo);
    csControl.DialGsm(cellularCallInfo);
    csControl.CalculateInternationalRoaming(SIM1_SLOTID);
    csControl.Answer(cellularCallInfo);
    csControl.Reject(cellularCallInfo);
    csControl.SeparateConference(SIM1_SLOTID, PHONE_NUMBER, 1);
    csControl.SeparateConference(SIM1_SLOTID, "", 1);
    int32_t invlaidCallType = -1;
    csControl.HangUp(cellularCallInfo, CallSupplementType::TYPE_DEFAULT);
    csControl.HangUp(cellularCallInfo, CallSupplementType::TYPE_HANG_UP_ACTIVE);
    csControl.HangUp(cellularCallInfo, CallSupplementType::TYPE_HANG_UP_ALL);
    csControl.HangUp(cellularCallInfo, static_cast<CallSupplementType>(invlaidCallType));
    csControl.HoldCall(SIM1_SLOTID);
    csControl.UnHoldCall(SIM1_SLOTID);
    csControl.SwitchCall(SIM1_SLOTID);
    csControl.CombineConference(SIM1_SLOTID);
    csControl.HangUpAllConnection(SIM1_SLOTID);
    csControl.GetConnectionMap();
    csControl.ReportHangUpInfo(SIM1_SLOTID);
    csControl.ReportIncomingInfo(SIM1_SLOTID, callInfoList);
    csControl.ReportUpdateInfo(SIM1_SLOTID, callInfoList);
    CallInfo callInfo;
    csControl.EncapsulationCallReportInfo(SIM1_SLOTID, callInfo);
    std::string phoneNum = "00000000";
    CLIRMode clirMode = CLIRMode::DEFAULT;
    int res = csControl.EncapsulateDialCommon(SIM1_SLOTID, phoneNum, clirMode);
    CallsReportInfo callsReportInfo;
    csControl.DeleteConnection(callsReportInfo, callInfoList);
    csControl.ReleaseAllConnection();
    ASSERT_EQ(res, TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallCsControl_002
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallCsControl_002, Function | MediumTest | Level3)
{
    AccessToken token;
    CSControl csControl;
    CellularCallInfo cellularCallInfo;
    InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, cellularCallInfo);
    CellularCallInfo cellularCallInfo_new;
    cellularCallInfo_new.callType = CallType::TYPE_CS;
    std::vector<CellularCallInfo> infos;
    bool enabled = false;
    infos.emplace_back(cellularCallInfo);
    infos.emplace_back(cellularCallInfo_new);
    csControl.PostDialProceed(cellularCallInfo, true);
    csControl.PostDialProceed(cellularCallInfo, enabled);
    csControl.ExecutePostDial(SIM1_SLOTID, 0);
    csControl.connectionMap_.insert(std::make_pair(1, CellularCallConnectionCS()));
    cellularCallInfo.index = 1;
    csControl.Answer(cellularCallInfo);
    csControl.PostDialProceed(cellularCallInfo, true);
    csControl.ExecutePostDial(SIM1_SLOTID, 0);
    csControl.ExecutePostDial(SIM1_SLOTID, 1);
    csControl.connectionMap_.clear();
    for (uint16_t i = 0; i <= 7; ++i) {
        csControl.connectionMap_.insert(std::make_pair(i, CellularCallConnectionCS()));
    }
    csControl.DialCdma(cellularCallInfo);
    csControl.DialGsm(cellularCallInfo);
    csControl.connectionMap_.clear();
    ASSERT_EQ(csControl.ReportHangUp(infos, SIM1_SLOTID), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallImsControl_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallImsControl_001, Function | MediumTest | Level3)
{
    AccessToken token;
    IMSControl imsControl;
    CellularCallInfo cellularCallInfo;
    std::vector<CellularCallInfo> infos;
    infos.emplace_back(cellularCallInfo);
    CellularCallInfo cellularCallInfo_new;
    bool enabled = false;
    int32_t invalidSupType = -1;
    ImsCurrentCallList ImsCallList;
    InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, cellularCallInfo);
    imsControl.ReportImsCallsData(SIM1_SLOTID, ImsCallList);
    InitImsCallInfoList(ImsCallList, 5);
    imsControl.ReportImsCallsData(SIM1_SLOTID, ImsCallList);
    imsControl.Dial(cellularCallInfo, true);
    cellularCallInfo_new.slotId = 1;
    imsControl.Dial(cellularCallInfo_new, true);
    cellularCallInfo_new.callType = CallType::TYPE_IMS;
    infos.emplace_back(cellularCallInfo_new);
    imsControl.HangUp(cellularCallInfo, CallSupplementType::TYPE_DEFAULT);
    imsControl.HangUp(cellularCallInfo, CallSupplementType::TYPE_HANG_UP_HOLD_WAIT);
    imsControl.HangUp(cellularCallInfo, CallSupplementType::TYPE_HANG_UP_ACTIVE);
    imsControl.HangUp(cellularCallInfo, CallSupplementType::TYPE_HANG_UP_ALL);
    imsControl.HangUp(cellularCallInfo, static_cast<CallSupplementType>(invalidSupType));
    imsControl.Answer(cellularCallInfo);
    imsControl.Reject(cellularCallInfo);
    imsControl.PostDialProceed(cellularCallInfo, true);
    imsControl.PostDialProceed(cellularCallInfo, enabled);
    imsControl.RestoreConnection(infos, SIM1_SLOTID);
    imsControl.RestoreConnection(infos, SIM2_SLOTID);
    imsControl.ReportHangUp(infos, SIM1_SLOTID);
    imsControl.ReportHangUp(infos, SIM2_SLOTID);
    imsControl.HoldCall(SIM1_SLOTID);
    imsControl.UnHoldCall(SIM1_SLOTID);
    imsControl.SwitchCall(SIM1_SLOTID);
    imsControl.CombineConference(SIM1_SLOTID);
    std::vector<std::string> numberList;
    imsControl.InviteToConference(SIM1_SLOTID, numberList);
    std::string kickOutStr = "";
    imsControl.KickOutFromConference(SIM1_SLOTID, kickOutStr, 0);
    kickOutStr = "111";
    imsControl.KickOutFromConference(SIM1_SLOTID, kickOutStr, 0);
    imsControl.HangUpAllConnection(SIM1_SLOTID);
}

/**
 * @tc.number   Telephony_CellularCallImsControl_002
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallImsControl_002, Function | MediumTest | Level3)
{
    AccessToken token;
    IMSControl imsControl;
    ImsCurrentCallList ImsCallList;
    imsControl.ReportImsCallsData(SIM1_SLOTID, ImsCallList);
    InitImsCallInfoList(ImsCallList, 5);
    imsControl.ReportImsCallsData(SIM1_SLOTID, ImsCallList);
    CallInfoList callInfoList;
    imsControl.ReportCallsData(SIM1_SLOTID, callInfoList);
    imsControl.ReportHangUpInfo(SIM1_SLOTID);
    imsControl.ReportIncomingInfo(SIM1_SLOTID, ImsCallList);
    imsControl.ReportUpdateInfo(SIM1_SLOTID, ImsCallList);
    ImsCurrentCall ImsCallInfo;
    imsControl.EncapsulationCallReportInfo(SIM1_SLOTID, ImsCallInfo);
    CallsReportInfo callsReportInfo;
    imsControl.DeleteConnection(callsReportInfo, ImsCallList);
    imsControl.ReleaseAllConnection();
    imsControl.DialAfterHold(SIM1_SLOTID);
    std::string msg = "";
    imsControl.StartRtt(SIM1_SLOTID, msg);
    imsControl.GetConnectionMap();
    imsControl.ReleaseAllConnection();
    CLIRMode clirMode = CLIRMode::DEFAULT;
    int32_t videoState = 0;
    imsControl.DialJudgment(SIM1_SLOTID, PHONE_NUMBER, clirMode, videoState);
#ifdef CALL_MANAGER_AUTO_START_OPTIMIZE
    ASSERT_EQ(imsControl.StopRtt(SIM1_SLOTID), INVALID_VALUE);
    ASSERT_EQ(imsControl.EncapsulateDial(SIM1_SLOTID, PHONE_NUMBER, clirMode, videoState),
        TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
#else
    ASSERT_EQ(imsControl.StopRtt(SIM1_SLOTID), TELEPHONY_SUCCESS);
    ASSERT_EQ(imsControl.EncapsulateDial(SIM1_SLOTID, PHONE_NUMBER, clirMode, videoState), TELEPHONY_SUCCESS);
#endif
}

/**
 * @tc.number   Telephony_CellularCallImsControl_003
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallImsControl_003, Function | MediumTest | Level3)
{
    AccessToken token;
    IMSControl imsControl;
    imsControl.connectionMap_.insert(std::make_pair(1, CellularCallConnectionIMS()));
    imsControl.RecoverPendingHold();
    imsControl.DialAfterHold(SIM1_SLOTID);
    imsControl.HangUpAllConnection(SIM1_SLOTID);
    ImsCurrentCallList imsCallList;
    CallsReportInfo callsReportInfo;
    imsControl.DeleteConnection(callsReportInfo, imsCallList);
    ASSERT_EQ(imsControl.ReportHangUpInfo(SIM1_SLOTID), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_ImsVideoCallControl_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_ImsVideoCallControl_001, Function | MediumTest | Level3)
{
    AccessToken token;
    auto imsVideoCallControl = DelayedSingleton<ImsVideoCallControl>::GetInstance();
    ASSERT_NE(imsVideoCallControl, nullptr);
    std::string cameraId = "";
    std::string surfaceId = "";
    std::string path = "";
    CellularCallInfo cellularCallInfo;
    InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, cellularCallInfo);
#ifdef CALL_MANAGER_AUTO_START_OPTIMIZE
    ASSERT_EQ(imsVideoCallControl->ControlCamera(SIM1_SLOTID, DEFAULT_INDEX, cameraId), INVALID_VALUE);
    ASSERT_EQ(imsVideoCallControl->SetPreviewWindow(SIM1_SLOTID, DEFAULT_INDEX, surfaceId, nullptr),
        INVALID_VALUE);
    ASSERT_EQ(imsVideoCallControl->SetDisplayWindow(SIM1_SLOTID, DEFAULT_INDEX, surfaceId, nullptr),
        INVALID_VALUE);
    ASSERT_EQ(imsVideoCallControl->SetCameraZoom(1.0), INVALID_VALUE);
    ASSERT_EQ(imsVideoCallControl->SetPausePicture(SIM1_SLOTID, DEFAULT_INDEX, path), INVALID_VALUE);
    ASSERT_EQ(imsVideoCallControl->SetDeviceDirection(SIM1_SLOTID, DEFAULT_INDEX, 0), INVALID_VALUE);
    ASSERT_EQ(imsVideoCallControl->SendUpdateCallMediaModeRequest(cellularCallInfo, ImsCallMode::CALL_MODE_AUDIO_ONLY),
        INVALID_VALUE);
    ASSERT_EQ(imsVideoCallControl->SendUpdateCallMediaModeResponse(cellularCallInfo, ImsCallMode::CALL_MODE_AUDIO_ONLY),
        INVALID_VALUE);
    ASSERT_EQ(imsVideoCallControl->CancelCallUpgrade(SIM1_SLOTID, DEFAULT_INDEX), INVALID_VALUE);
    ASSERT_EQ(imsVideoCallControl->RequestCameraCapabilities(SIM1_SLOTID, DEFAULT_INDEX), INVALID_VALUE);
#else
    ASSERT_EQ(imsVideoCallControl->ControlCamera(SIM1_SLOTID, DEFAULT_INDEX, cameraId), TELEPHONY_SUCCESS);
    ASSERT_EQ(imsVideoCallControl->SetPreviewWindow(SIM1_SLOTID, DEFAULT_INDEX, surfaceId, nullptr),
        TELEPHONY_SUCCESS);
    ASSERT_EQ(imsVideoCallControl->SetDisplayWindow(SIM1_SLOTID, DEFAULT_INDEX, surfaceId, nullptr),
        TELEPHONY_SUCCESS);
    ASSERT_EQ(imsVideoCallControl->SetCameraZoom(1.0), TELEPHONY_SUCCESS);
    ASSERT_EQ(imsVideoCallControl->SetPausePicture(SIM1_SLOTID, DEFAULT_INDEX, path), TELEPHONY_SUCCESS);
    ASSERT_EQ(imsVideoCallControl->SetDeviceDirection(SIM1_SLOTID, DEFAULT_INDEX, 0), TELEPHONY_SUCCESS);
    ASSERT_EQ(imsVideoCallControl->SendUpdateCallMediaModeRequest(cellularCallInfo, ImsCallMode::CALL_MODE_AUDIO_ONLY),
        TELEPHONY_ERR_FAIL);
    ASSERT_EQ(imsVideoCallControl->SendUpdateCallMediaModeResponse(cellularCallInfo, ImsCallMode::CALL_MODE_AUDIO_ONLY),
        TELEPHONY_ERR_FAIL);
    ASSERT_EQ(imsVideoCallControl->CancelCallUpgrade(SIM1_SLOTID, DEFAULT_INDEX), TELEPHONY_SUCCESS);
    ASSERT_EQ(imsVideoCallControl->RequestCameraCapabilities(SIM1_SLOTID, DEFAULT_INDEX), TELEPHONY_SUCCESS);
#endif
}

/**
 * @tc.number   Telephony_ImsVideoCallControl_002
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_ImsVideoCallControl_002, Function | MediumTest | Level3)
{
    AccessToken token;
    auto imsVideoCallControl = DelayedSingleton<ImsVideoCallControl>::GetInstance();
    ASSERT_NE(imsVideoCallControl, nullptr);
    ImsCallMode mode = ImsCallMode::CALL_MODE_AUDIO_ONLY;
    ASSERT_EQ(imsVideoCallControl->ConverToImsCallType(mode), ImsCallType::TEL_IMS_CALL_TYPE_VOICE);
    mode = ImsCallMode::CALL_MODE_RECEIVE_ONLY;
    ASSERT_EQ(imsVideoCallControl->ConverToImsCallType(mode), ImsCallType::TEL_IMS_CALL_TYPE_VT_RX);
    mode = ImsCallMode::CALL_MODE_SEND_ONLY;
    ASSERT_EQ(imsVideoCallControl->ConverToImsCallType(mode), ImsCallType::TEL_IMS_CALL_TYPE_VT_TX);
    mode = ImsCallMode::CALL_MODE_SEND_RECEIVE;
    ASSERT_EQ(imsVideoCallControl->ConverToImsCallType(mode), ImsCallType::TEL_IMS_CALL_TYPE_VT);
    mode = ImsCallMode::CALL_MODE_VIDEO_PAUSED;
    ASSERT_EQ(imsVideoCallControl->ConverToImsCallType(mode), ImsCallType::TEL_IMS_CALL_TYPE_PAUSE);
}

/**
 * @tc.number   Telephony_CellularCallConnectionIms_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallConnectionIms_001, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallConnectionIMS callConn;
    ImsDialInfoStruct dialRequest;
    std::vector<std::string> numberList = {};
    std::string msg = "";
    int32_t videoState = 0;
#ifdef CALL_MANAGER_AUTO_START_OPTIMIZE
    ASSERT_EQ(callConn.DialRequest(SIM1_SLOTID, dialRequest), TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL);
    ASSERT_EQ(callConn.HangUpRequest(SIM1_SLOTID, PHONE_NUMBER, 0), INVALID_VALUE);
    ASSERT_EQ(callConn.AnswerRequest(SIM1_SLOTID, PHONE_NUMBER, 0, 0), INVALID_VALUE);
    ASSERT_EQ(callConn.RejectRequest(SIM1_SLOTID, PHONE_NUMBER, 0), INVALID_VALUE);
    ASSERT_EQ(callConn.HoldCallRequest(SIM1_SLOTID), INVALID_VALUE);
    ASSERT_EQ(callConn.UnHoldCallRequest(SIM1_SLOTID), INVALID_VALUE);
    ASSERT_EQ(callConn.SwitchCallRequest(SIM1_SLOTID, videoState), INVALID_VALUE);
    ASSERT_EQ(callConn.CombineConferenceRequest(SIM1_SLOTID, 0), INVALID_VALUE);
    ASSERT_EQ(callConn.InviteToConferenceRequest(SIM1_SLOTID, numberList), INVALID_VALUE);
    ASSERT_EQ(callConn.KickOutFromConferenceRequest(SIM1_SLOTID, 0), INVALID_VALUE);
    ASSERT_EQ(callConn.CallSupplementRequest(SIM1_SLOTID, CallSupplementType::TYPE_DEFAULT), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.StartRttRequest(SIM1_SLOTID, msg), INVALID_VALUE);
    ASSERT_EQ(callConn.StopRttRequest(SIM1_SLOTID), INVALID_VALUE);
    ASSERT_EQ(callConn.GetImsCallsDataRequest(SIM1_SLOTID, 0), INVALID_VALUE);
    ASSERT_EQ(callConn.SendDtmfRequest(SIM1_SLOTID, '*', 0), INVALID_VALUE);
    ASSERT_EQ(callConn.StartDtmfRequest(SIM1_SLOTID, '*', 0), INVALID_VALUE);
    ASSERT_EQ(callConn.StopDtmfRequest(SIM1_SLOTID, 0), INVALID_VALUE);
    ASSERT_EQ(callConn.GetCallFailReasonRequest(SIM1_SLOTID), INVALID_VALUE);
#else
    ASSERT_EQ(callConn.DialRequest(SIM1_SLOTID, dialRequest), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.HangUpRequest(SIM1_SLOTID, PHONE_NUMBER, 0), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.AnswerRequest(SIM1_SLOTID, PHONE_NUMBER, 0, 0), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.RejectRequest(SIM1_SLOTID, PHONE_NUMBER, 0), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.HoldCallRequest(SIM1_SLOTID), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.UnHoldCallRequest(SIM1_SLOTID), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.SwitchCallRequest(SIM1_SLOTID, videoState), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.CombineConferenceRequest(SIM1_SLOTID, 0), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.InviteToConferenceRequest(SIM1_SLOTID, numberList), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.KickOutFromConferenceRequest(SIM1_SLOTID, 0), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.CallSupplementRequest(SIM1_SLOTID, CallSupplementType::TYPE_DEFAULT), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.StartRttRequest(SIM1_SLOTID, msg), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.StopRttRequest(SIM1_SLOTID), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.GetImsCallsDataRequest(SIM1_SLOTID, 0), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.SendDtmfRequest(SIM1_SLOTID, '*', 0), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.StartDtmfRequest(SIM1_SLOTID, '*', 0), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.StopDtmfRequest(SIM1_SLOTID, 0), TELEPHONY_SUCCESS);
    ASSERT_EQ(callConn.GetCallFailReasonRequest(SIM1_SLOTID), TELEPHONY_SUCCESS);
#endif
}

/**
 * @tc.number   Telephony_CellularCallConfigRequest_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranchTest, Telephony_CellularCallConfigRequest_001, Function | MediumTest | Level3)
{
    AccessToken token;
    ConfigRequest configReq;
    configReq.SetDomainPreferenceModeRequest(SIM1_SLOTID, 1);
    configReq.GetDomainPreferenceModeRequest(SIM1_SLOTID);
    configReq.SetDomainPreferenceModeRequest(SIM2_SLOTID, 1);
    configReq.GetDomainPreferenceModeRequest(SIM2_SLOTID);
    bool enabled = false;
    configReq.SetImsSwitchStatusRequest(SIM1_SLOTID, enabled);
    configReq.GetImsSwitchStatusRequest(SIM1_SLOTID);
    int32_t state = 0;
    configReq.SetVoNRSwitchStatusRequest(SIM1_SLOTID, state);
    configReq.SetVoNRSwitchStatusRequest(SIM2_SLOTID, state);
    std::string value = "";
    configReq.SetImsConfigRequest(ImsConfigItem::ITEM_VIDEO_QUALITY, value);
    configReq.SetImsConfigRequest(ImsConfigItem::ITEM_VIDEO_QUALITY, 1);
    configReq.GetImsConfigRequest(ImsConfigItem::ITEM_VIDEO_QUALITY);
    configReq.SetImsFeatureValueRequest(FeatureType::TYPE_VOICE_OVER_LTE, 1);
    int32_t imsFeature = 0;
    configReq.GetImsFeatureValueRequest(FeatureType::TYPE_VOICE_OVER_LTE, imsFeature);
    configReq.SetMuteRequest(SIM1_SLOTID, 0);
    configReq.GetMuteRequest(SIM1_SLOTID);
    configReq.SetMuteRequest(SIM2_SLOTID, 0);
    configReq.GetMuteRequest(SIM2_SLOTID);
    std::vector<EmergencyCall> eccVec = {};
    configReq.GetEmergencyCallListRequest(SIM1_SLOTID);
    configReq.SetEmergencyCallListRequest(SIM1_SLOTID, eccVec);
    configReq.GetEmergencyCallListRequest(SIM2_SLOTID);
    configReq.SetEmergencyCallListRequest(SIM2_SLOTID, eccVec);
    ImsCapabilityList imsCapabilityList;
#ifdef CALL_MANAGER_AUTO_START_OPTIMIZE
    ASSERT_EQ(configReq.UpdateImsCapabilities(SIM1_SLOTID, imsCapabilityList), CALL_ERR_RESOURCE_UNAVAILABLE);
#else
    ASSERT_EQ(configReq.UpdateImsCapabilities(SIM1_SLOTID, imsCapabilityList), TELEPHONY_SUCCESS);
#endif
}
} // namespace Telephony
} // namespace OHOS