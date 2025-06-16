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
const int32_t ACTIVATE_ACTION = 1;
const std::string PHONE_NUMBER = "00000000";
const int32_t DEFAULT_INDEX = 1;
const int32_t FIVE_MINUTES = 5;
} // namespace

class DemoHandler : public AppExecFwk::EventHandler {
public:
    explicit DemoHandler(std::shared_ptr<AppExecFwk::EventRunner> &runner) : AppExecFwk::EventHandler(runner) {}
    virtual ~DemoHandler() {}
    void ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event) {}
};

class ZeroBranch1Test : public testing::Test {
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

void ZeroBranch1Test::SetUpTestCase()
{
    std::cout << "---------- CellularCallService start ------------" << std::endl;
    DelayedSingleton<CellularCallService>::GetInstance()->Init();
    DelayedSingleton<ImsCallClient>::GetInstance()->Init();
}

void ZeroBranch1Test::TearDownTestCase() {}

void ZeroBranch1Test::SetUp() {}

void ZeroBranch1Test::TearDown()
{
    std::this_thread::sleep_for(std::chrono::seconds(FIVE_MINUTES));
}

int32_t ZeroBranch1Test::InitCellularCallInfo(int32_t accountId, std::string phonenumber, CellularCallInfo &callInfo)
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

void ZeroBranch1Test::InitImsCallInfoList(ImsCurrentCallList &callInfoList, int32_t num)
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

void ZeroBranch1Test::MakeCallInfoParcelData(bool isError, MessageParcel &data)
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

void ZeroBranch1Test::InitCsCallInfoList(CallInfoList &callInfoList, int32_t num)
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
 * @tc.number   Telephony_CellularCallStub_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallStub_001, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallService callStub;
    MessageParcel reply;

    MessageParcel dialErrorData;
    MakeCallInfoParcelData(true, dialErrorData);
    callStub.OnDialInner(dialErrorData, reply);
    MessageParcel dialData;
    MakeCallInfoParcelData(false, dialData);
    callStub.OnDialInner(dialData, reply);

    MessageParcel hangUpErrorData;
    MakeCallInfoParcelData(true, hangUpErrorData);
    callStub.OnHangUpInner(hangUpErrorData, reply);
    MessageParcel hangUpData;
    MakeCallInfoParcelData(false, hangUpData);
    hangUpData.WriteInt32(1);
    callStub.OnHangUpInner(hangUpData, reply);

    MessageParcel rejectErrorData;
    MakeCallInfoParcelData(true, rejectErrorData);
    callStub.OnRejectInner(rejectErrorData, reply);
    MessageParcel rejectData;
    MakeCallInfoParcelData(false, rejectData);
    callStub.OnRejectInner(rejectData, reply);

    MessageParcel answerErrorData;
    MakeCallInfoParcelData(true, answerErrorData);
    callStub.OnAnswerInner(answerErrorData, reply);
    MessageParcel answerData;
    MakeCallInfoParcelData(false, answerData);
    callStub.OnAnswerInner(answerData, reply);

    MessageParcel holdErrorData;
    MakeCallInfoParcelData(true, holdErrorData);
    callStub.OnHoldCallInner(holdErrorData, reply);
    MessageParcel holdData;
    MakeCallInfoParcelData(false, answerData);
    callStub.OnHoldCallInner(holdData, reply);

    MessageParcel unholdErrorData;
    MakeCallInfoParcelData(true, unholdErrorData);
    callStub.OnUnHoldCallInner(unholdErrorData, reply);
    MessageParcel unholdData;
    MakeCallInfoParcelData(false, unholdData);
    callStub.OnUnHoldCallInner(unholdData, reply);

    MessageParcel switchCallErrorData;
    MakeCallInfoParcelData(true, switchCallErrorData);
    callStub.OnSwitchCallInner(switchCallErrorData, reply);
    MessageParcel switchCallData;
    MakeCallInfoParcelData(false, switchCallData);
    ASSERT_EQ(callStub.OnSwitchCallInner(switchCallData, reply), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallStub_002
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallStub_002, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallService callStub;
    MessageParcel reply;
    int32_t size = 1;

    MessageParcel combineErrorData;
    MakeCallInfoParcelData(true, combineErrorData);
    callStub.OnCombineConferenceInner(combineErrorData, reply);
    MessageParcel combineData;
    MakeCallInfoParcelData(false, combineData);
    callStub.OnCombineConferenceInner(combineData, reply);

    MessageParcel separateErrorData;
    MakeCallInfoParcelData(true, separateErrorData);
    callStub.OnSeparateConferenceInner(separateErrorData, reply);
    MessageParcel separateData;
    MakeCallInfoParcelData(false, separateData);
    callStub.OnSeparateConferenceInner(separateData, reply);

    MessageParcel kickOutErrorData;
    MakeCallInfoParcelData(true, kickOutErrorData);
    callStub.OnKickOutFromConferenceInner(kickOutErrorData, reply);
    MessageParcel kickOutData;
    MakeCallInfoParcelData(false, kickOutData);
    callStub.OnKickOutFromConferenceInner(kickOutData, reply);

    MessageParcel stopDtmfErrorData;
    MakeCallInfoParcelData(true, stopDtmfErrorData);
    callStub.OnStopDtmfInner(stopDtmfErrorData, reply);
    MessageParcel stopDtmfData;
    MakeCallInfoParcelData(false, stopDtmfData);
    callStub.OnStopDtmfInner(stopDtmfData, reply);

    MessageParcel postDialErrorData;
    MakeCallInfoParcelData(true, postDialErrorData);
    callStub.OnPostDialProceedInner(postDialErrorData, reply);
    MessageParcel postDialData;
    MakeCallInfoParcelData(false, postDialData);
    postDialData.WriteBool(false);
    callStub.OnPostDialProceedInner(postDialData, reply);

    MessageParcel cameraData;
    cameraData.WriteInt32(size);
    ASSERT_EQ(callStub.OnControlCameraInner(cameraData, reply), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallStub_003
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallStub_003, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallService callStub;
    CellularCallInfo callInfo;
    callInfo.slotId = -1;
    int32_t errorSize = -1;
    int32_t size = 1;
    MessageParcel reply;

    MessageParcel hangUpAllData;
    hangUpAllData.WriteInt32(size);
    callStub.OnHangUpAllConnectionInner(hangUpAllData, reply);
    MessageParcel startDtmfData;
    startDtmfData.WriteInt32(size);
    startDtmfData.WriteInt8('1');
    startDtmfData.WriteRawData((const void *)&callInfo, sizeof(CellularCallInfo));
    callStub.OnStartDtmfInner(startDtmfData, reply);
    MessageParcel sendDtmfData;
    sendDtmfData.WriteInt32(size);
    sendDtmfData.WriteInt8('1');
    sendDtmfData.WriteRawData((const void *)&callInfo, sizeof(CellularCallInfo));
    callStub.OnSendDtmfInner(sendDtmfData, reply);
    MessageParcel emergencyData;
    emergencyData.WriteInt32(size);
    emergencyData.WriteInt32(errorSize);
    callStub.OnIsEmergencyPhoneNumberInner(emergencyData, reply);
    MessageParcel setReadyData;
    setReadyData.WriteInt32(errorSize);
    callStub.OnSetReadyToCallInner(setReadyData, reply);
    MessageParcel setCallTransferData;
    setCallTransferData.WriteInt32(size);
    setCallTransferData.WriteInt32(errorSize);
    callStub.OnSetCallTransferInner(setCallTransferData, reply);
    MessageParcel canSetTimerData;
    canSetTimerData.WriteInt32(size);
    canSetTimerData.WriteInt32(errorSize);
    callStub.OnCanSetCallTransferTimeInner(canSetTimerData, reply);
    MessageParcel getCallTransferData;
    getCallTransferData.WriteInt32(size);
    getCallTransferData.WriteInt32(errorSize);
    callStub.OnGetCallTransferInner(getCallTransferData, reply);
    MessageParcel setCallWaitData;
    setCallWaitData.WriteInt32(size);
    setCallWaitData.WriteInt32(errorSize);
    callStub.OnSetCallWaitingInner(setCallWaitData, reply);
    MessageParcel getCallWaitData;
    getCallWaitData.WriteInt32(size);
    getCallWaitData.WriteInt32(errorSize);
    ASSERT_EQ(callStub.OnGetCallWaitingInner(getCallWaitData, reply), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallStub_004
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallStub_004, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallService callStub;
    int32_t errorSize = -1;
    int32_t size = 1;
    MessageParcel reply;

    MessageParcel setCallRestData;
    setCallRestData.WriteInt32(size);
    setCallRestData.WriteInt32(errorSize);
    callStub.OnSetCallRestrictionInner(setCallRestData, reply);
    MessageParcel getCallRestData;
    getCallRestData.WriteInt32(size);
    getCallRestData.WriteInt32(errorSize);
    callStub.OnGetCallRestrictionInner(getCallRestData, reply);
    MessageParcel setCallRestPwdData;
    setCallRestPwdData.WriteInt32(size);
    setCallRestPwdData.WriteInt32(errorSize);
    callStub.OnSetCallRestrictionPasswordInner(setCallRestPwdData, reply);
    MessageParcel setDomainData;
    setDomainData.WriteInt32(size);
    setDomainData.WriteInt32(errorSize);
    callStub.OnSetDomainPreferenceModeInner(setDomainData, reply);
    MessageParcel getDomainData;
    getDomainData.WriteInt32(size);
    getDomainData.WriteInt32(errorSize);
    callStub.OnGetDomainPreferenceModeInner(getDomainData, reply);
    MessageParcel setImsSwitchData;
    setImsSwitchData.WriteInt32(size);
    setImsSwitchData.WriteInt32(errorSize);
    callStub.OnSetImsSwitchStatusInner(setImsSwitchData, reply);
    MessageParcel getImsSwitchData;
    getImsSwitchData.WriteInt32(size);
    getImsSwitchData.WriteInt32(errorSize);
    callStub.OnGetImsSwitchStatusInner(getImsSwitchData, reply);
    MessageParcel setVonrData;
    setVonrData.WriteInt32(size);
    setVonrData.WriteInt32(errorSize);
    callStub.OnSetVoNRStateInner(setVonrData, reply);
    MessageParcel getVonrData;
    getVonrData.WriteInt32(size);
    getVonrData.WriteInt32(errorSize);
    callStub.OnGetVoNRStateInner(getVonrData, reply);
    MessageParcel setconfigData;
    setconfigData.WriteInt32(size);
    setconfigData.WriteInt32(errorSize);
    ASSERT_EQ(callStub.OnSetImsConfigStringInner(setconfigData, reply), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallStub_005
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallStub_005, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallService callStub;
    int32_t errorSize = -1;
    int32_t size = 1;
    MessageParcel reply;

    MessageParcel setconfigData;
    setconfigData.WriteInt32(size);
    setconfigData.WriteInt32(errorSize);
    callStub.OnSetImsConfigIntInner(setconfigData, reply);
    MessageParcel getconfigData;
    getconfigData.WriteInt32(size);
    getconfigData.WriteInt32(errorSize);
    callStub.OnGetImsConfigInner(getconfigData, reply);
    MessageParcel setFeatureData;
    setFeatureData.WriteInt32(size);
    setFeatureData.WriteInt32(errorSize);
    callStub.OnSetImsFeatureValueInner(setFeatureData, reply);
    MessageParcel getFeatureData;
    getFeatureData.WriteInt32(size);
    getFeatureData.WriteInt32(errorSize);
    callStub.OnGetImsFeatureValueInner(getFeatureData, reply);
    MessageParcel setMuteData;
    setMuteData.WriteInt32(size);
    setMuteData.WriteInt32(errorSize);
    callStub.OnSetMuteInner(setMuteData, reply);
    MessageParcel getMuteData;
    getMuteData.WriteInt32(size);
    getMuteData.WriteInt32(errorSize);
    callStub.OnGetMuteInner(getMuteData, reply);
    MessageParcel closeUssdData;
    closeUssdData.WriteInt32(size);
    closeUssdData.WriteInt32(errorSize);
    callStub.OnCloseUnFinishedUssdInner(closeUssdData, reply);
    MessageParcel clearCallsData;
    MakeCallInfoParcelData(false, clearCallsData);
    ASSERT_EQ(callStub.OnClearAllCallsInner(clearCallsData, reply), TELEPHONY_SUCCESS);
    MessageParcel ussdData;
    ussdData.WriteInt32(0);
    ussdData.WriteString("1");
}

/**
 * @tc.number   Telephony_CellularCallStub_006
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallStub_006, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallService callStub;
    int32_t errorSize = -1;
    int32_t size = 1;
    MessageParcel reply;
    MessageParcel setPreviewData;
    setPreviewData.WriteInt32(errorSize);
    callStub.OnSetPreviewWindowInner(setPreviewData, reply);
    MessageParcel setDisplayData;
    setDisplayData.WriteInt32(errorSize);
    callStub.OnSetDisplayWindowInner(setDisplayData, reply);
    MessageParcel setCameraData;
    setCameraData.WriteInt32(errorSize);
    callStub.OnSetCameraZoomInner(setCameraData, reply);
    MessageParcel setImageData;
    setImageData.WriteInt32(errorSize);
    callStub.OnSetPausePictureInner(setImageData, reply);
    MessageParcel setDirectionData;
    setDirectionData.WriteInt32(errorSize);
    callStub.OnSetDeviceDirectionInner(setDirectionData, reply);

    MessageParcel setEmergencyData;
    setEmergencyData.WriteInt32(size);
    setEmergencyData.WriteInt32(errorSize);
    setEmergencyData.WriteInt32(size);
    if (setEmergencyData.WriteString("123") && setEmergencyData.WriteString("456") &&
        setEmergencyData.WriteInt32(size) && setEmergencyData.WriteInt32(size) && setEmergencyData.WriteInt32(size)) {
        callStub.OnSetEmergencyCallList(setEmergencyData, reply);
    }

    MessageParcel registerData;
    registerData.WriteInt32(size);
    callStub.OnRegisterCallBackInner(registerData, reply);
    MessageParcel unRegisterData;
    unRegisterData.WriteInt32(errorSize);
    callStub.OnUnRegisterCallBackInner(unRegisterData, reply);
    MessageParcel inviteData;
    registerData.WriteInt32(size);
    inviteData.WriteInt32(errorSize);
    callStub.OnInviteToConferenceInner(inviteData, reply);
    MessageParcel startRttData;
    startRttData.WriteInt32(size);
    startRttData.WriteInt32(errorSize);
    startRttData.WriteString("1");
    callStub.OnStartRttInner(startRttData, reply);
    MessageParcel stopRttData;
    stopRttData.WriteInt32(size);
    stopRttData.WriteInt32(errorSize);
    ASSERT_EQ(callStub.OnStopRttInner(stopRttData, reply), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallStub_007
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallStub_007, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallService callStub;
    int32_t size = 1;
    MessageParcel reply;
    MessageParcel callMediaModeRequestData;
    MakeCallInfoParcelData(false, callMediaModeRequestData);
    ImsCallMode requestMode = ImsCallMode::CALL_MODE_AUDIO_ONLY;
    callMediaModeRequestData.WriteInt32(static_cast<int32_t>(requestMode));
    callStub.OnSendUpdateCallMediaModeRequestInner(callMediaModeRequestData, reply);

    MessageParcel callMediaModeResponseData;
    MakeCallInfoParcelData(false, callMediaModeResponseData);
    ImsCallMode responseMode = ImsCallMode::CALL_MODE_AUDIO_ONLY;
    callMediaModeResponseData.WriteInt32(static_cast<int32_t>(responseMode));
    callStub.OnSendUpdateCallMediaModeResponseInner(callMediaModeResponseData, reply);

    MessageParcel callUpgradeData;
    callUpgradeData.WriteInt32(size);
    callUpgradeData.WriteInt32(SIM1_SLOTID);
    callUpgradeData.WriteInt32(DEFAULT_INDEX);
    callStub.OnCancelCallUpgradeInner(callUpgradeData, reply);

    MessageParcel cameraCapabilitiesData;
    cameraCapabilitiesData.WriteInt32(size);
    cameraCapabilitiesData.WriteInt32(SIM1_SLOTID);
    cameraCapabilitiesData.WriteInt32(DEFAULT_INDEX);
    ASSERT_EQ(callStub.OnRequestCameraCapabilitiesInner(cameraCapabilitiesData, reply), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallService_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallService_001, Function | MediumTest | Level3)
{
    // AccessToken token;
    CellularCallService cellularCall;
    std::vector<std::u16string> args = { u"1", u"2" };
    cellularCall.Dump(-1, args);
    cellularCall.Dump(1, args);
    cellularCall.GetServiceRunningState();
    cellularCall.GetBindTime();
    cellularCall.GetEndTime();
    cellularCall.GetSpendTime();

    CellularCallInfo csCallInfo = { .callType = CallType::TYPE_CS };
    CellularCallInfo imsCallInfo = { .callType = CallType::TYPE_IMS };
    CellularCallInfo errCallInfo = { .callType = CallType::TYPE_ERR_CALL };
    cellularCall.Dial(csCallInfo);
    cellularCall.Dial(imsCallInfo);
    cellularCall.Dial(errCallInfo);

    cellularCall.HangUp(csCallInfo, CallSupplementType::TYPE_HANG_UP_HOLD_WAIT);
    cellularCall.HangUp(imsCallInfo, CallSupplementType::TYPE_HANG_UP_HOLD_WAIT);
    cellularCall.HangUp(errCallInfo, CallSupplementType::TYPE_HANG_UP_HOLD_WAIT);

    cellularCall.Reject(csCallInfo);
    cellularCall.Reject(imsCallInfo);
    cellularCall.Reject(errCallInfo);

    cellularCall.Answer(csCallInfo);
    cellularCall.Answer(imsCallInfo);
    cellularCall.Answer(errCallInfo);

    cellularCall.HoldCall(csCallInfo);
    cellularCall.HoldCall(imsCallInfo);
    cellularCall.HoldCall(errCallInfo);

    cellularCall.UnHoldCall(csCallInfo);
    cellularCall.UnHoldCall(imsCallInfo);
    cellularCall.UnHoldCall(errCallInfo);

    cellularCall.SwitchCall(csCallInfo);
    cellularCall.SwitchCall(imsCallInfo);
    cellularCall.SwitchCall(errCallInfo);

    bool enabled = false;
    std::string phoneNum = "000";
    cellularCall.IsEmergencyPhoneNumber(INVALID_SLOTID, phoneNum, enabled);
    ASSERT_EQ(cellularCall.IsEmergencyPhoneNumber(SIM1_SLOTID, phoneNum, enabled), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallService_002
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallService_002, Function | MediumTest | Level3)
{
    // AccessToken token;
    CellularCallService cellularCall;
    CellularCallInfo csCallInfo = { .callType = CallType::TYPE_CS };
    CellularCallInfo imsCallInfo = { .callType = CallType::TYPE_IMS };
    CellularCallInfo errCallInfo = { .callType = CallType::TYPE_ERR_CALL };
    EmergencyCall ecc;
    std::vector<EmergencyCall> eccVec;
    eccVec.push_back(ecc);
    cellularCall.SetEmergencyCallList(SIM1_SLOTID, eccVec);
    cellularCall.CombineConference(csCallInfo);
    cellularCall.CombineConference(imsCallInfo);
    cellularCall.CombineConference(errCallInfo);

    cellularCall.SeparateConference(csCallInfo);
    cellularCall.SeparateConference(imsCallInfo);
    cellularCall.SeparateConference(errCallInfo);

    std::vector<std::string> numberList = { "111", "222" };
    cellularCall.InviteToConference(SIM1_SLOTID, numberList);
    cellularCall.KickOutFromConference(csCallInfo);
    cellularCall.KickOutFromConference(imsCallInfo);
    cellularCall.KickOutFromConference(errCallInfo);
    cellularCall.HangUpAllConnection();
    cellularCall.HangUpAllConnection(SIM1_SLOTID);

    cellularCall.SetReadyToCall(SIM1_SLOTID, 0, true);
    cellularCall.SetReadyToCall(SIM1_SLOTID, 1, true);
    cellularCall.SetReadyToCall(SIM1_SLOTID, 3, true);
    cellularCall.StartDtmf('*', csCallInfo);
    cellularCall.StartDtmf('*', imsCallInfo);
    cellularCall.StartDtmf('*', errCallInfo);
    cellularCall.StopDtmf(csCallInfo);
    cellularCall.StopDtmf(imsCallInfo);
    cellularCall.StopDtmf(errCallInfo);

    cellularCall.PostDialProceed(csCallInfo, true);
    cellularCall.PostDialProceed(imsCallInfo, true);
    cellularCall.PostDialProceed(errCallInfo, true);
    cellularCall.SendDtmf('*', csCallInfo);
    cellularCall.SendDtmf('*', imsCallInfo);
    cellularCall.SendDtmf('*', errCallInfo);
    std::string msg = "";
    cellularCall.StartRtt(SIM1_SLOTID, msg);
    ASSERT_NE(cellularCall.StopRtt(SIM1_SLOTID), TELEPHONY_SUCCESS);
}

/**
 * @tc.number   Telephony_CellularCallService_003
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallService_003, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallService cellularCall;
    CallTransferInfo cTInfoDisable = { .settingType = CallTransferSettingType::CALL_TRANSFER_DISABLE };
    CallTransferInfo cTInfoEnable = { .settingType = CallTransferSettingType::CALL_TRANSFER_ENABLE };
    cellularCall.SetCallTransferInfo(SIM1_SLOTID, cTInfoDisable);
    cellularCall.SetCallTransferInfo(SIM1_SLOTID, cTInfoEnable);
    bool result = false;
    cellularCall.CanSetCallTransferTime(SIM1_SLOTID, result);
    cellularCall.GetCallTransferInfo(SIM1_SLOTID, CallTransferType::TRANSFER_TYPE_UNCONDITIONAL);
    cellularCall.SetCallWaiting(SIM1_SLOTID, true);
    cellularCall.GetCallWaiting(SIM1_SLOTID);
    CallRestrictionInfo crInfo;
    cellularCall.SetCallRestriction(SIM1_SLOTID, crInfo);
    cellularCall.GetCallRestriction(SIM1_SLOTID, CallRestrictionType::RESTRICTION_TYPE_ALL_INCOMING);
    std::string password = "1111";
    cellularCall.SetCallRestrictionPassword(
        SIM1_SLOTID, CallRestrictionType::RESTRICTION_TYPE_ALL_INCOMING, password.c_str(), password.c_str());
    cellularCall.SetDomainPreferenceMode(SIM1_SLOTID, 1);
    cellularCall.GetDomainPreferenceMode(SIM1_SLOTID);
    cellularCall.SetImsSwitchStatus(SIM1_SLOTID, true);
    bool enabled = false;
    cellularCall.GetImsSwitchStatus(SIM1_SLOTID, enabled);
    std::string value = "";
    cellularCall.SetImsConfig(SIM1_SLOTID, ImsConfigItem::ITEM_VIDEO_QUALITY, value);
    int32_t state = 0;
    cellularCall.SetVoNRState(SIM1_SLOTID, state);
    cellularCall.GetVoNRState(SIM1_SLOTID, state);
    cellularCall.SetImsConfig(SIM1_SLOTID, ImsConfigItem::ITEM_VIDEO_QUALITY, 1);
    cellularCall.GetImsConfig(SIM1_SLOTID, ImsConfigItem::ITEM_VIDEO_QUALITY);
    cellularCall.SetImsFeatureValue(SIM1_SLOTID, FeatureType::TYPE_VOICE_OVER_LTE, 1);
    cellularCall.GetImsFeatureValue(SIM1_SLOTID, FeatureType::TYPE_VOICE_OVER_LTE);
    std::string cameraId = "";
    cellularCall.ControlCamera(SIM1_SLOTID, DEFAULT_INDEX, cameraId);
    std::string surfaceId = "";
    cellularCall.SetPreviewWindow(SIM1_SLOTID, DEFAULT_INDEX, surfaceId, nullptr);
    cellularCall.SetDisplayWindow(SIM1_SLOTID, DEFAULT_INDEX, surfaceId, nullptr);
    cellularCall.SetCameraZoom(1.0);
    std::string path = "";
    cellularCall.SetPausePicture(SIM1_SLOTID, DEFAULT_INDEX, path);
    cellularCall.SetDeviceDirection(SIM1_SLOTID, DEFAULT_INDEX, 0);
    CellularCallInfo cellularCallInfo;
    InitCellularCallInfo(SIM1_SLOTID, PHONE_NUMBER, cellularCallInfo);
    cellularCall.SendUpdateCallMediaModeRequest(cellularCallInfo, ImsCallMode::CALL_MODE_AUDIO_ONLY);
    cellularCall.SendUpdateCallMediaModeResponse(cellularCallInfo, ImsCallMode::CALL_MODE_AUDIO_ONLY);
    cellularCall.CancelCallUpgrade(SIM1_SLOTID, DEFAULT_INDEX);
}

/**
 * @tc.number   Telephony_CellularCallService_004
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallService_004, Function | MediumTest | Level3)
{
    AccessToken token;
    CellularCallService cellularCall;
    cellularCall.SetMute(SIM1_SLOTID, 0);
    cellularCall.GetMute(SIM1_SLOTID);
    cellularCall.CloseUnFinishedUssd(SIM1_SLOTID);
    std::vector<CellularCallInfo> infos = {};
    cellularCall.ClearAllCalls(infos);
    cellularCall.IsNeedIms(SIM1_SLOTID);
    cellularCall.GetCsControl(SIM1_SLOTID);
    cellularCall.GetImsControl(SIM1_SLOTID);
    std::shared_ptr<CSControl> csControl;
    cellularCall.SetCsControl(SIM1_SLOTID, csControl);
    std::shared_ptr<IMSControl> imsControl;
    cellularCall.SetImsControl(SIM1_SLOTID, imsControl);
    cellularCall.GetHandler(SIM1_SLOTID);
    cellularCall.SetSrvccState(SrvccState::SRVCC_NONE);
    cellularCall.GetSrvccState();
    cellularCall.RegisterHandler();
#ifdef CALL_MANAGER_AUTO_START_OPTIMIZE
    cellularCall.StartCallManagerService();
    ASSERT_EQ(cellularCall.RequestCameraCapabilities(SIM1_SLOTID, DEFAULT_INDEX), INVALID_VALUE);
#else
    ASSERT_EQ(cellularCall.RequestCameraCapabilities(SIM1_SLOTID, DEFAULT_INDEX), TELEPHONY_SUCCESS);
#endif
    cellularCall.Init();
    cellularCall.RegisterCoreServiceHandler();
    cellularCall.CreateHandler();
    cellularCall.SendEventRegisterHandler();
    cellularCall.IsValidSlotId(SIM1_SLOTID);
    CellularCallInfo imsCallInfo = { .callType = CallType::TYPE_IMS };
    CellularCallInfo csCallInfo = { .callType = CallType::TYPE_CS };
    cellularCall.UseImsForEmergency(imsCallInfo, true);
    cellularCall.HandleCallManagerException();
    cellularCall.HandleCellularControlException(imsCallInfo);
    cellularCall.HandleCellularControlException(csCallInfo);
    cellularCall.HangUpWithCellularCallRestart(infos);
    cellularCall.SetControl(imsCallInfo);
    cellularCall.SetControl(csCallInfo);
    sptr<ICallStatusCallback> callback;
    cellularCall.RegisterCallManagerCallBack(callback);
    cellularCall.UnRegisterCallManagerCallBack();
    cellularCall.HandlerResetUnRegister();
    cellularCall.OnStop();
    cellularCall.SendUssdResponse(0, "1");
    ASSERT_EQ(callback, nullptr);
}

/**
 * @tc.number	Telephony_CellularCallSupplementRequestIms_001
 * @tc.name 	Test error branch
 * @tc.desc 	Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallSupplementRequestIms_001, Function | MediumTest | Level3)
{
    SupplementRequestIms SRequestIms;
    CallTransferInfo CTransferInfo;
    std::string fac = "";
    SRequestIms.SetClipRequest(SIM1_SLOTID, ACTIVATE_ACTION, 0);
    SRequestIms.GetClipRequest(SIM1_SLOTID, 0);
    SRequestIms.SetClirRequest(SIM1_SLOTID, ACTIVATE_ACTION, 0);
    SRequestIms.GetClirRequest(SIM1_SLOTID, 0);
    SRequestIms.GetCallTransferRequest(SIM1_SLOTID, 0, 0);
    SRequestIms.SetCallTransferRequest(SIM1_SLOTID, CTransferInfo, ACTIVATE_ACTION, 0);
    bool enable = false;
    SRequestIms.CanSetCallTransferTime(SIM1_SLOTID, enable);
    SRequestIms.GetCallRestrictionRequest(SIM1_SLOTID, fac, 0);
    std::string pw = "";
    SRequestIms.SetCallRestrictionRequest(SIM1_SLOTID, fac, 0, pw, 0);
    SRequestIms.SetCallWaitingRequest(SIM1_SLOTID, true, 0, 0);
    SRequestIms.GetCallWaitingRequest(SIM1_SLOTID, 0);
    SRequestIms.SetColrRequest(SIM1_SLOTID, 0, 0);
    SRequestIms.GetColrRequest(SIM1_SLOTID, 0);
    SRequestIms.SetColpRequest(SIM1_SLOTID, 0, 0);
    SRequestIms.GetMMIHandler(SIM1_SLOTID);
    ASSERT_NE(SRequestIms.GetColpRequest(SIM1_SLOTID, 0), TELEPHONY_SUCCESS);
}

/**
 * @tc.number	Telephony_CellularCallbaseconnection_001
 * @tc.name 	Test error branch
 * @tc.desc 	Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallbaseconnection_001, Function | MediumTest | Level3)
{
    BaseConnection BConnection;
    char c = ' ';
    BConnection.postDialCalltate_ = PostDialCallState::POST_DIAL_CALL_CANCELED;
    EXPECT_EQ(BConnection.ProcessNextChar(SIM1_SLOTID, c), 5);
    EXPECT_EQ(BConnection.GetLeftPostDialCallString(), "");
    BConnection.postDialCallString_ = "111111";
    BConnection.postDialCalltate_ = PostDialCallState::POST_DIAL_CALL_NOT_STARTED;
}
/**
 * @tc.number   Telephony_CellularCallHiSysEvent_001
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallHiSysEvent_001, Function | MediumTest | Level3)
{
    // AccessToken token;
    std::shared_ptr<CellularCallHiSysEvent> cellularCallHiSysEvent = std::make_shared<CellularCallHiSysEvent>();
    std::string desc;
    cellularCallHiSysEvent->WriteFoundationRestartFaultEvent(2);
    CallBehaviorParameterInfo Info = { .callType = 1 };
    CallResponseResult result = CallResponseResult::COMMAND_FAILURE;
    cellularCallHiSysEvent->WriteDialCallBehaviorEvent(Info, result);
    result = CallResponseResult::COMMAND_SUCCESS;
    cellularCallHiSysEvent->WriteDialCallBehaviorEvent(Info, result);
    Info = { .callType = 0 };
    cellularCallHiSysEvent->WriteDialCallBehaviorEvent(Info, result);
    Info = { .callType = 1 };
    result = CallResponseResult::COMMAND_FAILURE;
    cellularCallHiSysEvent->WriteHangUpCallBehaviorEvent(Info, result);
    result = CallResponseResult::COMMAND_SUCCESS;
    cellularCallHiSysEvent->WriteHangUpCallBehaviorEvent(Info, result);
    Info = { .callType = 0 };
    cellularCallHiSysEvent->WriteHangUpCallBehaviorEvent(Info, result);
    cellularCallHiSysEvent->WriteIncomingCallFaultEvent(
        0, 0, 0, static_cast<int32_t>(TELEPHONY_ERR_MEMCPY_FAIL), desc);
    cellularCallHiSysEvent->WriteIncomingCallFaultEvent(0, 0, 0, -1, desc);
    cellularCallHiSysEvent->JudgingIncomingTimeOut(0, 0, 0);
    CallForwardingInfo cfInfo;
    cellularCallHiSysEvent->GetCallForwardingInfo(cfInfo);
    ASSERT_TRUE(desc.empty());
}

/**
 * @tc.number   Telephony_CellularCallHiSysEvent_002
 * @tc.name     Test error branch
 * @tc.desc     Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallHiSysEvent_002, Function | MediumTest | Level3)
{
    // AccessToken token;
    std::shared_ptr<CellularCallHiSysEvent> cellularCallHiSysEvent = std::make_shared<CellularCallHiSysEvent>();
    CallErrorCode eventValue;
    cellularCallHiSysEvent->TelephonyErrorCodeConversion(-1, eventValue);
    cellularCallHiSysEvent->TelephonyErrorCodeConversion(
        static_cast<int32_t>(TELEPHONY_ERR_LOCAL_PTR_NULL), eventValue);
    cellularCallHiSysEvent->TelephonyErrorCodeConversion(
        static_cast<int32_t>(TELEPHONY_ERR_ARGUMENT_INVALID), eventValue);
    cellularCallHiSysEvent->TelephonyErrorCodeConversion(
        static_cast<int32_t>(TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL), eventValue);
    cellularCallHiSysEvent->TelephonyErrorCodeConversion(
        static_cast<int32_t>(TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL), eventValue);
    cellularCallHiSysEvent->TelephonyErrorCodeConversion(
        static_cast<int32_t>(TELEPHONY_ERR_WRITE_DATA_FAIL), eventValue);
    cellularCallHiSysEvent->TelephonyErrorCodeConversion(
        static_cast<int32_t>(TELEPHONY_ERR_PERMISSION_ERR), eventValue);
    cellularCallHiSysEvent->TelephonyErrorCodeConversion(static_cast<int32_t>(TELEPHONY_ERR_MEMSET_FAIL), eventValue);
    cellularCallHiSysEvent->TelephonyErrorCodeConversion(static_cast<int32_t>(TELEPHONY_ERR_MEMCPY_FAIL), eventValue);
    cellularCallHiSysEvent->CallDataErrorCodeConversion(-1, eventValue);
    cellularCallHiSysEvent->CallDataErrorCodeConversion(static_cast<int32_t>(CALL_ERR_INVALID_SLOT_ID), eventValue);
    cellularCallHiSysEvent->CallDataErrorCodeConversion(static_cast<int32_t>(CALL_ERR_INVALID_CALLID), eventValue);
    cellularCallHiSysEvent->CallDataErrorCodeConversion(static_cast<int32_t>(CALL_ERR_PHONE_NUMBER_EMPTY), eventValue);
    cellularCallHiSysEvent->CallDataErrorCodeConversion(
        static_cast<int32_t>(CALL_ERR_NUMBER_OUT_OF_RANGE), eventValue);
    cellularCallHiSysEvent->CallDataErrorCodeConversion(
        static_cast<int32_t>(CALL_ERR_UNSUPPORTED_NETWORK_TYPE), eventValue);
    cellularCallHiSysEvent->CallDataErrorCodeConversion(static_cast<int32_t>(CALL_ERR_INVALID_DIAL_SCENE), eventValue);
    cellularCallHiSysEvent->CallDataErrorCodeConversion(
        static_cast<int32_t>(CALL_ERR_INVALID_VIDEO_STATE), eventValue);
    cellularCallHiSysEvent->CallDataErrorCodeConversion(static_cast<int32_t>(CALL_ERR_UNKNOW_DIAL_TYPE), eventValue);
    cellularCallHiSysEvent->CallDataErrorCodeConversion(static_cast<int32_t>(CALL_ERR_UNKNOW_CALL_TYPE), eventValue);
    cellularCallHiSysEvent->CallDataErrorCodeConversion(
        static_cast<int32_t>(CALL_ERR_CALL_OBJECT_IS_NULL), eventValue);
    cellularCallHiSysEvent->CallInterfaceErrorCodeConversion(-1, eventValue);
    cellularCallHiSysEvent->CallInterfaceErrorCodeConversion(static_cast<int32_t>(CALL_ERR_DIAL_IS_BUSY), eventValue);
    cellularCallHiSysEvent->CallInterfaceErrorCodeConversion(
        static_cast<int32_t>(CALL_ERR_ILLEGAL_CALL_OPERATION), eventValue);
    cellularCallHiSysEvent->CallInterfaceErrorCodeConversion(
        static_cast<int32_t>(CALL_ERR_PHONE_CALLSTATE_NOTIFY_FAILED), eventValue);
    cellularCallHiSysEvent->CallInterfaceErrorCodeConversion(
        static_cast<int32_t>(CALL_ERR_SYSTEM_EVENT_HANDLE_FAILURE), eventValue);
    cellularCallHiSysEvent->CallInterfaceErrorCodeConversion(
        static_cast<int32_t>(CALL_ERR_CALL_COUNTS_EXCEED_LIMIT), eventValue);
    ASSERT_NE(cellularCallHiSysEvent->CallInterfaceErrorCodeConversion(
        static_cast<int32_t>(CALL_ERR_GET_RADIO_STATE_FAILED), eventValue), 0);
}

/**
 * @tc.number	Telephony_CellularCallConnectionCs_001
 * @tc.name 	Test error branch
 * @tc.desc 	Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallConnectionCs_001, Function | MediumTest | Level3)
{
    CellularCallConnectionCS cellularCallConnectionCS;
    DialRequestStruct dialRequestStruct;
    cellularCallConnectionCS.DialRequest(SIM2_SLOTID, dialRequestStruct);
    cellularCallConnectionCS.HangUpRequest(SIM2_SLOTID);
    cellularCallConnectionCS.AnswerRequest(SIM2_SLOTID);
    cellularCallConnectionCS.AnswerRequest(SIM1_SLOTID);
    cellularCallConnectionCS.RejectRequest(SIM2_SLOTID);
    cellularCallConnectionCS.HoldRequest(SIM2_SLOTID);
    cellularCallConnectionCS.UnHoldCallRequest(SIM2_SLOTID);
    cellularCallConnectionCS.SwitchCallRequest(SIM2_SLOTID);
    cellularCallConnectionCS.CombineConferenceRequest(SIM2_SLOTID, 0);
    cellularCallConnectionCS.SeparateConferenceRequest(SIM2_SLOTID, 0, 0);
    cellularCallConnectionCS.CallSupplementRequest(SIM2_SLOTID, CallSupplementType::TYPE_DEFAULT);
    char cDtmfCode = ' ';
    cellularCallConnectionCS.SendDtmfRequest(SIM2_SLOTID, cDtmfCode, 0);
    cellularCallConnectionCS.StartDtmfRequest(SIM2_SLOTID, cDtmfCode, 0);
    cellularCallConnectionCS.StopDtmfRequest(SIM2_SLOTID, 0);
    cellularCallConnectionCS.GetCsCallsDataRequest(SIM2_SLOTID, 0);
    cellularCallConnectionCS.GetCallFailReasonRequest(SIM2_SLOTID);
    ASSERT_EQ(cellularCallConnectionCS.ProcessPostDialCallChar(SIM1_SLOTID, cDtmfCode), TELEPHONY_SUCCESS);
}

/**
 * @tc.number	Telephony_SupplementRequestCs_001
 * @tc.name 	Test error branch
 * @tc.desc 	Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_SupplementRequestCs_001, Function | MediumTest | Level3)
{
    SupplementRequestCs supplementRequestCs;
    std::string msg = "11111";
    std::string fac = "";
    std::string pw = "";
    std::string oldPin = "123456";
    std::string newPin = "789101";
    std::string puk = "22222";
    CallTransferParam callTransferParam;
    ASSERT_EQ(supplementRequestCs.SendUssdRequest(SIM1_SLOTID, msg), TELEPHONY_ERR_LOCAL_PTR_NULL);
    ASSERT_EQ(supplementRequestCs.CloseUnFinishedUssdRequest(SIM1_SLOTID), TELEPHONY_ERR_LOCAL_PTR_NULL);
    ASSERT_EQ(supplementRequestCs.SetClirRequest(SIM1_SLOTID, ACTIVATE_ACTION, 0), TELEPHONY_ERR_LOCAL_PTR_NULL);
    ASSERT_EQ(supplementRequestCs.GetClipRequest(SIM1_SLOTID, 0), TELEPHONY_ERR_LOCAL_PTR_NULL);
    ASSERT_EQ(supplementRequestCs.GetClirRequest(SIM1_SLOTID, 0), TELEPHONY_ERR_LOCAL_PTR_NULL);
    ASSERT_EQ(supplementRequestCs.SetCallTransferRequest(SIM1_SLOTID, callTransferParam, 0),
        TELEPHONY_ERR_LOCAL_PTR_NULL);
    ASSERT_EQ(supplementRequestCs.GetCallTransferRequest(SIM1_SLOTID, 0, 0), TELEPHONY_ERR_LOCAL_PTR_NULL);
    ASSERT_EQ(supplementRequestCs.GetCallRestrictionRequest(SIM1_SLOTID, fac, 0), TELEPHONY_ERR_LOCAL_PTR_NULL);
    ASSERT_EQ(supplementRequestCs.SetCallRestrictionRequest(SIM1_SLOTID, fac, 0, pw, 0), TELEPHONY_ERR_LOCAL_PTR_NULL);
    ASSERT_EQ(supplementRequestCs.SetBarringPasswordRequest(SIM1_SLOTID, msg, 0, oldPin.c_str(), newPin.c_str()),
        TELEPHONY_ERR_LOCAL_PTR_NULL);
    ASSERT_EQ(supplementRequestCs.SetCallWaitingRequest(SIM1_SLOTID, true, 0, 0), TELEPHONY_ERR_LOCAL_PTR_NULL);
    ASSERT_EQ(supplementRequestCs.AlterPinPassword(SIM1_SLOTID, newPin, oldPin), TELEPHONY_ERROR);
    ASSERT_EQ(supplementRequestCs.UnlockPuk(SIM1_SLOTID, newPin, puk), TELEPHONY_ERROR);
    ASSERT_EQ(supplementRequestCs.AlterPin2Password(SIM1_SLOTID, newPin, oldPin), TELEPHONY_ERROR);
    ASSERT_EQ(supplementRequestCs.UnlockPuk2(SIM1_SLOTID, newPin, puk), TELEPHONY_ERROR);
    ASSERT_EQ(supplementRequestCs.GetCallWaitingRequest(SIM1_SLOTID, 0), TELEPHONY_ERR_LOCAL_PTR_NULL);
}

/**
 * @tc.number	Telephony_StandardizeUtils_001
 * @tc.name 	Test error branch
 * @tc.desc 	Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_StandardizeUtils_001, Function | MediumTest | Level3)
{
    StandardizeUtils standardizeUtils;
    std::string phoneString = {0};
    std::string networkAddress = "1111111";
    std::string postDial = "11111111";
    ASSERT_EQ(standardizeUtils.RemoveSeparatorsPhoneNumber(phoneString), "");
    phoneString = "1111111,123321";
    standardizeUtils.ExtractAddressAndPostDial(phoneString, networkAddress, postDial);
    ASSERT_EQ(postDial, "11111111,123321");
    std::vector<std::string> split = standardizeUtils.Split(phoneString, ",");
    ASSERT_FALSE(split.empty());
}

/**
 * @tc.number	Telephony_MmiCodeUtils_001
 * @tc.name 	Test error branch
 * @tc.desc 	Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_MmiCodeUtils_001, Function | MediumTest | Level3)
{
    MMICodeUtils mmiCodeUtils;
    bool enable = false;
    ASSERT_FALSE(mmiCodeUtils.IsNeedExecuteMmi("111111#", enable));
    mmiCodeUtils.isNeedUseIms_ = true;
    ASSERT_FALSE(mmiCodeUtils.ExecuteMmiCode(SIM1_SLOTID));
    mmiCodeUtils.isNeedUseIms_ = false;
    mmiCodeUtils.mmiData_.serviceCode = "11111";
    ASSERT_FALSE(mmiCodeUtils.ExecuteMmiCode(SIM1_SLOTID));
    mmiCodeUtils.mmiData_.serviceCode.clear();
    mmiCodeUtils.mmiData_.fullString = "11111";
    ASSERT_TRUE(mmiCodeUtils.ExecuteMmiCode(SIM1_SLOTID));
    mmiCodeUtils.mmiData_.fullString.clear();
    mmiCodeUtils.mmiData_.dialString = "11111#";
    ASSERT_FALSE(mmiCodeUtils.RegexMatchMmi("111111#"));
}

/**
 * @tc.number	Telephony_CellularCallRdbHelper_001
 * @tc.name 	Test error branch
 * @tc.desc 	Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallRdbHelper_001, Function | MediumTest | Level3)
{
    std::u16string u16Hplmn = u"";
    CoreManagerInner::GetInstance().GetSimOperatorNumeric(SIM1_SLOTID, u16Hplmn);
    std::string hplmn = Str16ToStr8(u16Hplmn);
    std::vector<EccNum> eccVec;
    ASSERT_NE(DelayedSingleton<CellularCallRdbHelper>::GetInstance()->QueryEccList(hplmn, eccVec), TELEPHONY_SUCCESS);
}

/**
 * @tc.number	Telephony_CellularCallDumpHelper_001
 * @tc.name 	Test error branch
 * @tc.desc 	Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_CellularCallDumpHelper_001, Function | MediumTest | Level3)
{
    CellularCallDumpHelper cellularCallDumpHelper;
    std::vector<std::string> args = { "123456", "234567" };
    std::string result;
    cellularCallDumpHelper.WhetherHasSimCard(SIM1_SLOTID);
    ASSERT_NE(cellularCallDumpHelper.Dump(args, result), TELEPHONY_SUCCESS);
}

/**
 * @tc.number	Telephony_EmergencyUtils_001
 * @tc.name 	Test error branch
 * @tc.desc 	Function test
 */
HWTEST_F(ZeroBranch1Test, Telephony_EmergencyUtils_001, Function | MediumTest | Level3)
{
    EmergencyUtils emergencyUtils;
    std::string phoneNum = "1234567";
    bool enabled = false;
    ASSERT_EQ(emergencyUtils.IsEmergencyCall(SIM1_SLOTID, phoneNum, enabled), TELEPHONY_SUCCESS);
}

} // namespace Telephony
} // namespace OHOS