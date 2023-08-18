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
#include "hril_call_parcel.h"
#include "ims_call_callback_proxy.h"
#include "ims_call_callback_stub.h"
#include "ims_call_client.h"
#include "ims_control.h"
#include "ims_error.h"
#include "securec.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;

namespace {
const int32_t INVALID_SLOTID = 2;
const int32_t SIM1_SLOTID = 0;
const std::string PHONE_NUMBER = "00000000";
} // namespace

class DemoHandler : public AppExecFwk::EventHandler {
public:
    explicit DemoHandler(std::shared_ptr<AppExecFwk::EventRunner> &runner) : AppExecFwk::EventHandler(runner) {}
    virtual ~DemoHandler() {}
    void ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event) {}
};

class BranchTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
    int32_t InitCellularCallInfo(int32_t accountId, std::string phonenumber, CellularCallInfo &callInfo);
    void InitImsCallInfoList(ImsCurrentCallList &callInfoList, int32_t num);
    void InitCsCallInfoList(CallInfoList &callInfoList, int32_t num);
};

void BranchTest::SetUpTestCase()
{
    std::cout << "---------- CellularCallService start ------------" << std::endl;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    DelayedSingleton<ImsCallClient>::GetInstance()->Init();
}

void BranchTest::TearDownTestCase() {}

void BranchTest::SetUp() {}

void BranchTest::TearDown() {}

int32_t BranchTest::InitCellularCallInfo(int32_t accountId, std::string phonenumber, CellularCallInfo &callInfo)
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

void BranchTest::InitImsCallInfoList(ImsCurrentCallList &callInfoList, int32_t num)
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

void BranchTest::InitCsCallInfoList(CallInfoList &callInfoList, int32_t num)
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
HWTEST_F(BranchTest, Telephony_CellularCallConfig_001, Function | MediumTest | Level3)
{
    CellularCallConfig config;
    config.SetDomainPreferenceMode(SIM1_SLOTID, 1);
    config.SetDomainPreferenceMode(SIM1_SLOTID, -1);
    config.GetDomainPreferenceMode(SIM1_SLOTID);
    bool enabled = false;
    config.SetImsSwitchStatus(INVALID_SLOTID, enabled);
    config.SetImsSwitchStatus(SIM1_SLOTID, enabled);
    config.GetImsSwitchStatus(SIM1_SLOTID, enabled);
    int32_t state = 0;
    config.SetVoNRSwitchStatus(SIM1_SLOTID, state);
    config.GetVoNRSwitchStatus(SIM1_SLOTID, state);
    config.GetDomainPreferenceModeResponse(SIM1_SLOTID, 1);
    config.GetImsSwitchStatusResponse(SIM1_SLOTID, 1);
    config.GetPreferenceMode(SIM1_SLOTID);
    std::string value = "";
    config.SetImsConfig(ImsConfigItem::ITEM_VIDEO_QUALITY, value);
    config.SetImsConfig(ImsConfigItem::ITEM_VIDEO_QUALITY, 1);
    config.GetImsConfig(ImsConfigItem::ITEM_VIDEO_QUALITY);
    config.SetImsFeatureValue(FeatureType::TYPE_VOICE_OVER_LTE, 1);
    config.GetImsFeatureValue(FeatureType::TYPE_VOICE_OVER_LTE);
}

/**
 * @tc.number   Telephony_CellularCallConfig_002
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(BranchTest, Telephony_CellularCallConfig_002, Function | MediumTest | Level3)
{
    CellularCallConfig config;
    std::u16string cameraId = u"";
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    int32_t width = 10;
    int32_t height = 10;
    config.CtrlCamera(cameraId, 0, 0);
    config.SetPreviewWindow(x, y, z, width, height);
    config.SetDisplayWindow(x, y, z, width, height);
    config.SetCameraZoom(1.0);
    std::u16string path = u"";
    config.SetPauseImage(path);
    config.SetDeviceDirection(1);
}

/**
 * @tc.number   Telephony_CellularCallConfig_003
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(BranchTest, Telephony_CellularCallConfig_003, Function | MediumTest | Level3)
{
    CellularCallConfig config;
    config.SetMute(SIM1_SLOTID, 0);
    config.GetMute(SIM1_SLOTID);
    config.GetEmergencyCallList(SIM1_SLOTID);
    std::vector<EmergencyCall> eccVec = {};
    config.SetEmergencyCallList(SIM1_SLOTID);
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
    config.HandleSetLteImsSwitchResult(SIM1_SLOTID, HRilErrType::NONE);
    config.HandleSetVoNRSwitchResult(SIM1_SLOTID, HRilErrType::NONE);
    config.HandleSimRecordsLoaded(SIM1_SLOTID);
    config.HandleOperatorConfigChanged(SIM1_SLOTID);
    OperatorConfig poc;
    config.ParseAndCacheOperatorConfigs(SIM1_SLOTID, poc);
    config.UpdateImsCapabilities(SIM1_SLOTID, true);
}

/**
 * @tc.number   Telephony_CellularCallSupplement_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(BranchTest, Telephony_CellularCallSupplement_001, Function | MediumTest | Level3)
{
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

    CallTransferInfo cfInfo;
    callSup.SetCallTransferInfo(SIM1_SLOTID, cfInfo);
    bool result = false;
    callSup.CanSetCallTransferTime(SIM1_SLOTID, result);
    callSup.GetCallTransferInfo(SIM1_SLOTID, CallTransferType::TRANSFER_TYPE_UNCONDITIONAL);
    callSup.HandleCallRestriction(SIM1_SLOTID, mmiDataEmp);
    callSup.HandleCallRestriction(SIM1_SLOTID, mmiDataAct);
    callSup.HandleCallRestriction(SIM1_SLOTID, mmiDataDeact);
    callSup.HandleCallRestriction(SIM1_SLOTID, mmiDataInterrogate);
    CallRestrictionInfo crInfo;
    callSup.SetCallRestriction(SIM1_SLOTID, crInfo);
    callSup.GetCallRestriction(SIM1_SLOTID, CallRestrictionType::RESTRICTION_TYPE_ALL_INCOMING);
    callSup.SetBarringPassword(SIM1_SLOTID, CallRestrictionType::RESTRICTION_TYPE_ALL_INCOMING, "1111", "0000");
    callSup.HandleCallWaiting(SIM1_SLOTID, mmiDataEmp);
    callSup.HandleCallWaiting(SIM1_SLOTID, mmiDataAct);
    callSup.HandleCallWaiting(SIM1_SLOTID, mmiDataDeact);
    bool activate = false;
    callSup.SetCallWaiting(SIM1_SLOTID, activate);
    callSup.GetCallWaiting(SIM1_SLOTID);
}

/**
 * @tc.number   Telephony_CellularCallSupplement_002
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(BranchTest, Telephony_CellularCallSupplement_002, Function | MediumTest | Level3)
{
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
    callSup.EventSetClip(0, message, 0);
    callSup.EventSetClip(0, message, 1);
    GetClirResult getClirResult;
    callSup.EventGetClir(getClirResult, message, 0);
    callSup.EventGetClir(getClirResult, message, 1);
    callSup.EventSetClir(0, message, 0);
    callSup.EventSetClir(0, message, 1);
    GetColrResult getColrResult;
    callSup.EventGetColr(getColrResult, message, 0);
    callSup.EventGetColr(getColrResult, message, 1);
    callSup.EventSetColr(0, message, 0);
    callSup.EventSetColr(0, message, 1);
}

/**
 * @tc.number   Telephony_CellularCallSupplement_003
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(BranchTest, Telephony_CellularCallSupplement_003, Function | MediumTest | Level3)
{
    CellularCallSupplement callSup;
    GetColpResult getColpResult;
    std::string message = "";
    callSup.EventGetColp(getColpResult, message, 0);
    callSup.EventGetColp(getColpResult, message, 1);
    callSup.EventSetColp(0, message, 0);
    callSup.EventSetColp(0, message, 1);
    CallRestrictionResult callResResult;
    callSup.EventGetCallRestriction(callResResult, message, 0);
    callSup.EventGetCallRestriction(callResResult, message, 1);
    callSup.EventSetCallRestriction(0, message, 0);
    callSup.EventSetCallRestriction(0, message, 1);
    callSup.EventSetBarringPassword(0, message, 0);
    callSup.EventSetBarringPassword(0, message, 1);
    CallWaitResult waitingInfo;
    callSup.EventGetCallWaiting(waitingInfo, message, 0);
    callSup.EventGetCallWaiting(waitingInfo, message, 1);
    callSup.EventSetCallWaiting(0, message, 0);
    callSup.EventSetCallWaiting(0, message, 1);
    CallForwardQueryInfoList cFQueryList;
    callSup.EventGetCallTransferInfo(cFQueryList, message, 0);
    CallForwardQueryResult queryResult;
    callSup.BuildCallForwardQueryInfo(queryResult, message, 0);
    callSup.BuildCallForwardQueryInfo(queryResult, message, 1);
    callSup.EventSetCallTransferInfo(0, message, 0);
    callSup.EventSetCallTransferInfo(0, message, 1);
    HRilRadioResponseInfo responseInfo;
    callSup.EventSendUssd(responseInfo);
    SsNoticeInfo ssNoticeInfo;
    callSup.EventSsNotify(ssNoticeInfo);
    UssdNoticeInfo ussdNoticeInfo;
    callSup.EventUssdNotify(ussdNoticeInfo);
    HRilRadioResponseInfo response;
    callSup.EventCloseUnFinishedUssd(response);
}

/**
 * @tc.number   Telephony_CellularCallCsControl_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(BranchTest, Telephony_CellularCallCsControl_001, Function | MediumTest | Level3)
{
    CSControl csControl;
    CellularCallInfo cellularCallInfo;
    InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, cellularCallInfo);
    CallInfoList callInfoList;
    csControl.ReportCallsData(SIM1_SLOTID, callInfoList);
    InitCsCallInfoList(callInfoList, 5);
    csControl.ReportCallsData(SIM1_SLOTID, callInfoList);
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
    csControl.ReportHungUpInfo(SIM1_SLOTID);
    csControl.ReportIncomingInfo(SIM1_SLOTID, callInfoList);
    csControl.ReportUpdateInfo(SIM1_SLOTID, callInfoList);
    CallInfo callInfo;
    csControl.EncapsulationCallReportInfo(SIM1_SLOTID, callInfo);
    std::string phoneNum = "00000000";
    CLIRMode clirMode = CLIRMode::DEFAULT;
    csControl.EncapsulateDialCommon(SIM1_SLOTID, phoneNum, clirMode);
    CallsReportInfo callsReportInfo;
    csControl.DeleteConnection(callsReportInfo, callInfoList);
    csControl.ReleaseAllConnection();
}

/**
 * @tc.number   Telephony_CellularCallImsControl_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(BranchTest, Telephony_CellularCallImsControl_001, Function | MediumTest | Level3)
{
    IMSControl imsControl;
    CellularCallInfo cellularCallInfo;
    int32_t invalidSupType = -1;
    ImsCurrentCallList ImsCallList;
    InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, cellularCallInfo);
    imsControl.ReportImsCallsData(SIM1_SLOTID, ImsCallList);
    InitImsCallInfoList(ImsCallList, 5);
    imsControl.ReportImsCallsData(SIM1_SLOTID, ImsCallList);
    imsControl.Dial(cellularCallInfo, true);
    imsControl.HangUp(cellularCallInfo, CallSupplementType::TYPE_DEFAULT);
    imsControl.HangUp(cellularCallInfo, CallSupplementType::TYPE_HANG_UP_HOLD_WAIT);
    imsControl.HangUp(cellularCallInfo, CallSupplementType::TYPE_HANG_UP_ACTIVE);
    imsControl.HangUp(cellularCallInfo, CallSupplementType::TYPE_HANG_UP_ALL);
    imsControl.HangUp(cellularCallInfo, static_cast<CallSupplementType>(invalidSupType));
    imsControl.Answer(cellularCallInfo);
    imsControl.Reject(cellularCallInfo);
    imsControl.UpdateImsCallMode(cellularCallInfo, ImsCallMode::CALL_MODE_AUDIO_ONLY);
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
    CLIRMode clirMode = CLIRMode::DEFAULT;
    int32_t videoState = 0;
    imsControl.DialJudgment(SIM1_SLOTID, PHONE_NUMBER, clirMode, videoState);
    imsControl.EncapsulateDial(SIM1_SLOTID, PHONE_NUMBER, clirMode, videoState);
    std::string msg = "";
    imsControl.StartRtt(SIM1_SLOTID, msg);
    imsControl.StopRtt(SIM1_SLOTID);
    imsControl.GetConnectionMap();
    imsControl.ReleaseAllConnection();
}

/**
 * @tc.number   Telephony_CellularCallImsControl_002
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(BranchTest, Telephony_CellularCallImsControl_002, Function | MediumTest | Level3)
{
    IMSControl imsControl;
    ImsCurrentCallList ImsCallList;
    imsControl.ReportImsCallsData(SIM1_SLOTID, ImsCallList);
    InitImsCallInfoList(ImsCallList, 5);
    imsControl.ReportImsCallsData(SIM1_SLOTID, ImsCallList);
    CallInfoList callInfoList;
    imsControl.ReportCallsData(SIM1_SLOTID, callInfoList);
    imsControl.ReportHungUpInfo(SIM1_SLOTID);
    imsControl.ReportIncomingInfo(SIM1_SLOTID, ImsCallList);
    imsControl.ReportUpdateInfo(SIM1_SLOTID, ImsCallList);
    ImsCurrentCall ImsCallInfo;
    imsControl.EncapsulationCallReportInfo(SIM1_SLOTID, ImsCallInfo);
    CallsReportInfo callsReportInfo;
    imsControl.DeleteConnection(callsReportInfo, ImsCallList);
    imsControl.ReleaseAllConnection();
}

/**
 * @tc.number   Telephony_CellularCallConnectionIms_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(BranchTest, Telephony_CellularCallConnectionIms_001, Function | MediumTest | Level3)
{
    CellularCallConnectionIMS callConn;
    ImsDialInfoStruct dialRequest;
    callConn.DialRequest(SIM1_SLOTID, dialRequest);
    callConn.HangUpRequest(SIM1_SLOTID, PHONE_NUMBER, 0);
    callConn.AnswerRequest(SIM1_SLOTID, PHONE_NUMBER, 0, 0);
    callConn.RejectRequest(SIM1_SLOTID, PHONE_NUMBER, 0);
    callConn.HoldCallRequest(SIM1_SLOTID);
    callConn.UnHoldCallRequest(SIM1_SLOTID);
    callConn.SwitchCallRequest(SIM1_SLOTID);
    callConn.CombineConferenceRequest(SIM1_SLOTID, 0);
    std::vector<std::string> numberList = {};
    callConn.InviteToConferenceRequest(SIM1_SLOTID, numberList);
    callConn.KickOutFromConferenceRequest(SIM1_SLOTID, 0);
    callConn.CallSupplementRequest(SIM1_SLOTID, CallSupplementType::TYPE_DEFAULT);
    CellularCallInfo callInfo;
    callConn.UpdateCallMediaModeRequest(callInfo, ImsCallMode::CALL_MODE_AUDIO_ONLY);
    std::string msg = "";
    callConn.StartRttRequest(SIM1_SLOTID, msg);
    callConn.StopRttRequest(SIM1_SLOTID);
    callConn.GetImsCallsDataRequest(SIM1_SLOTID, 0);
    callConn.SendDtmfRequest(SIM1_SLOTID, '*', 0);
    callConn.StartDtmfRequest(SIM1_SLOTID, '*', 0);
    callConn.StopDtmfRequest(SIM1_SLOTID, 0);
    callConn.GetCallFailReasonRequest(SIM1_SLOTID);
}

/**
 * @tc.number   Telephony_CellularCallConfigRequest_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(BranchTest, Telephony_CellularCallConfigRequest_001, Function | MediumTest | Level3)
{
    ConfigRequest configReq;
    configReq.SetDomainPreferenceModeRequest(SIM1_SLOTID, 1);
    configReq.GetDomainPreferenceModeRequest(SIM1_SLOTID);
    bool enabled = false;
    configReq.SetImsSwitchStatusRequest(SIM1_SLOTID, enabled);
    configReq.GetImsSwitchStatusRequest(SIM1_SLOTID);
    int32_t state = 0;
    configReq.SetVoNRSwitchStatusRequest(SIM1_SLOTID, state);
    std::string value = "";
    configReq.SetImsConfigRequest(ImsConfigItem::ITEM_VIDEO_QUALITY, value);
    configReq.SetImsConfigRequest(ImsConfigItem::ITEM_VIDEO_QUALITY, 1);
    configReq.GetImsConfigRequest(ImsConfigItem::ITEM_VIDEO_QUALITY);
    configReq.SetImsFeatureValueRequest(FeatureType::TYPE_VOICE_OVER_LTE, 1);
    int32_t imsFeature = 0;
    configReq.GetImsFeatureValueRequest(FeatureType::TYPE_VOICE_OVER_LTE, imsFeature);

    std::u16string cameraId = u"";
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    int32_t width = 10;
    int32_t height = 10;
    std::u16string path = u"";
    configReq.CtrlCameraRequest(cameraId, 0, 0);
    configReq.SetPreviewWindowRequest(x, y, z, width, height);
    configReq.SetDisplayWindowRequest(x, y, z, width, height);
    configReq.SetCameraZoomRequest(1.0);
    configReq.SetPauseImageRequest(path);
    configReq.SetDeviceDirectionRequest(1);
    configReq.SetMuteRequest(SIM1_SLOTID, 0);
    configReq.GetMuteRequest(SIM1_SLOTID);
    std::vector<EmergencyCall> eccVec = {};
    configReq.GetEmergencyCallListRequest(SIM1_SLOTID);
    configReq.SetEmergencyCallListRequest(SIM1_SLOTID, eccVec);
    ImsCapabilityList imsCapabilityList;
    configReq.UpdateImsCapabilities(SIM1_SLOTID, imsCapabilityList);
}

} // namespace Telephony
} // namespace OHOS
