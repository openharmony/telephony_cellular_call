/*
 * Copyright (C) 2021-2022 Huawei Device Co., Ltd.
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

#include "ims_unit_test.h"

#include "iservice_registry.h"
#include "securec.h"
#include "system_ability_definition.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
const int32_t CELLULAR_CALL_ERROR = -1;
const int32_t CELLULAR_CALL_SUCCESS = 0;

void ImsUnitTest::SetUpTestCase(void)
{
    // step 3: Set Up Test Case
}

void ImsUnitTest::TearDownTestCase(void)
{
    // step 3: Tear Down Test Case
}

void ImsUnitTest::SetUp(void)
{
    // step 3: input testcase setup step
    requestFuncMap_[ImsInterface::IMS_DIAL] = &ImsUnitTest::Dial;
    requestFuncMap_[ImsInterface::IMS_HANG_UP] = &ImsUnitTest::HangUp;
    requestFuncMap_[ImsInterface::IMS_REJECT] = &ImsUnitTest::Reject;
    requestFuncMap_[ImsInterface::IMS_ANSWER] = &ImsUnitTest::Answer;
    requestFuncMap_[ImsInterface::IMS_HOLD] = &ImsUnitTest::HoldCall;
    requestFuncMap_[ImsInterface::IMS_UN_HOLD] = &ImsUnitTest::UnHoldCall;
    requestFuncMap_[ImsInterface::IMS_SWITCH] = &ImsUnitTest::SwitchCall;
    requestFuncMap_[ImsInterface::IMS_COMBINE_CONFERENCE] = &ImsUnitTest::CombineConference;
    requestFuncMap_[ImsInterface::IMS_INVITE_TO_CONFERENCE] = &ImsUnitTest::InviteToConference;
    requestFuncMap_[ImsInterface::IMS_KICK_OUT_CONFERENCE] = &ImsUnitTest::KickOutFromConference;
    requestFuncMap_[ImsInterface::IMS_UPDATE_CALL_MEDIA_MODE] = &ImsUnitTest::UpdateImsCallMode;
    requestFuncMap_[ImsInterface::IMS_EMERGENCY_CALL] = &ImsUnitTest::IsEmergencyPhoneNumber;
    requestFuncMap_[ImsInterface::GET_CALL_FAIL_REASON] = &ImsUnitTest::GetCallFailReason;
    requestFuncMap_[ImsInterface::IMS_START_DTMF] = &ImsUnitTest::StartDtmf;
    requestFuncMap_[ImsInterface::IMS_SEND_DTMF] = &ImsUnitTest::SendDtmf;
    requestFuncMap_[ImsInterface::IMS_STOP_DTMF] = &ImsUnitTest::StopDtmf;
    requestFuncMap_[ImsInterface::IMS_START_RTT] = &ImsUnitTest::StartRtt;
    requestFuncMap_[ImsInterface::IMS_STOP_RTT] = &ImsUnitTest::StopRtt;
    requestFuncMap_[ImsInterface::IMS_SET_DOMAIN_PREFERENCE_MODE] = &ImsUnitTest::SetDomainPreferenceMode;
    requestFuncMap_[ImsInterface::IMS_GET_DOMAIN_PREFERENCE_MODE] = &ImsUnitTest::GetDomainPreferenceMode;
    requestFuncMap_[ImsInterface::IMS_SET_IMS_SWITCH_STATUS] = &ImsUnitTest::SetImsSwitchStatus;
    requestFuncMap_[ImsInterface::IMS_GET_IMS_SWITCH_STATUS] = &ImsUnitTest::GetImsSwitchStatus;
    requestFuncMap_[ImsInterface::IMS_SET_IMS_CONFIG_STRING] = &ImsUnitTest::SetImsConfigString;
    requestFuncMap_[ImsInterface::IMS_SET_IMS_CONFIG_INT] = &ImsUnitTest::SetImsConfigInt;
    requestFuncMap_[ImsInterface::IMS_GET_IMS_CONFIG] = &ImsUnitTest::GetImsConfig;
    requestFuncMap_[ImsInterface::IMS_SET_IMS_FEATURE] = &ImsUnitTest::SetImsFeatureValue;
    requestFuncMap_[ImsInterface::IMS_GET_IMS_FEATURE] = &ImsUnitTest::GetImsFeatureValue;
    requestFuncMap_[ImsInterface::IMS_SET_IMS_SWITCH_ENHANCE_MODE] = &ImsUnitTest::SetImsSwitchEnhanceMode;
    requestFuncMap_[ImsInterface::IMS_GET_IMS_SWITCH_ENHANCE_MODE] = &ImsUnitTest::GetImsSwitchEnhanceMode;
    requestFuncMap_[ImsInterface::IMS_CTRL_CAMERA] = &ImsUnitTest::CtrlCamera;
    requestFuncMap_[ImsInterface::IMS_SET_PREVIEW_WINDOW] = &ImsUnitTest::SetPreviewWindow;
    requestFuncMap_[ImsInterface::IMS_SET_DISPLAY_WINDOW] = &ImsUnitTest::SetDisplayWindow;
    requestFuncMap_[ImsInterface::IMS_SET_CAMERA_ZOOM] = &ImsUnitTest::SetCameraZoom;
    requestFuncMap_[ImsInterface::IMS_SET_PAUSE_IMAGE] = &ImsUnitTest::SetPauseImage;
    requestFuncMap_[ImsInterface::IMS_SET_DEVICE_DIRECTION] = &ImsUnitTest::SetDeviceDirection;
    requestFuncMap_[ImsInterface::IMS_REGISTER_CALLBACK] = &ImsUnitTest::RegisterCellularCallBack;
    requestFuncMap_[ImsInterface::IMS_IS_CALLBACK_EXISTS] = &ImsUnitTest::IsCallBackExists;
    requestFuncMap_[ImsInterface::IMS_SET_MUTE] = &ImsUnitTest::SetMute;
    requestFuncMap_[ImsInterface::IMS_GET_MUTE] = &ImsUnitTest::GetMute;
    requestFuncMap_[ImsInterface::IMS_SET_CALL_TRANSFER] = &ImsUnitTest::SetCallTransfer;
    requestFuncMap_[ImsInterface::IMS_GET_CALL_TRANSFER] = &ImsUnitTest::GetCallTransfer;
    requestFuncMap_[ImsInterface::IMS_SET_CALL_RESTRICTION] = &ImsUnitTest::SetCallRestriction;
    requestFuncMap_[ImsInterface::IMS_GET_CALL_RESTRICTION] = &ImsUnitTest::GetCallRestriction;
    requestFuncMap_[ImsInterface::IMS_SET_CALL_WAITING] = &ImsUnitTest::SetCallWaiting;
    requestFuncMap_[ImsInterface::IMS_GET_CALL_WAITING] = &ImsUnitTest::GetCallWaiting;
}

void ImsUnitTest::TearDown(void)
{
    // step 3: input testcase teardown step
}

int32_t ImsUnitTest::Dial(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test Dial entry." << std::endl;
    ImsCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "Dial return, memset_s failed." << std::endl;
        return CELLULAR_CALL_ERROR;
    }
    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    callInfo.slotId = 0;
    CLIRMode mode = CLIRMode::DEFAULT;
    telephonyService->Dial(callInfo, mode);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::HangUp(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test HangUp entry." << std::endl;
    ImsCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "HangUp return, memset_s failed." << std::endl;
        return CELLULAR_CALL_ERROR;
    }
    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    callInfo.slotId = 0;
    std::cout << "please enter the connect index:";
    std::cin >> callInfo.index;
    telephonyService->HangUp(callInfo);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::Reject(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test Reject entry." << std::endl;
    ImsCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "Reject return, memset_s failed." << std::endl;
        return CELLULAR_CALL_ERROR;
    }
    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    callInfo.slotId = 0;
    std::cout << "please enter the connect index:";
    std::cin >> callInfo.index;
    telephonyService->Reject(callInfo);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::Answer(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test Answer entry." << std::endl;
    ImsCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "Answer return, memset_s failed." << std::endl;
        return CELLULAR_CALL_ERROR;
    }
    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    callInfo.slotId = 0;
    std::cout << "please enter the connect index:";
    std::cin >> callInfo.index;
    telephonyService->Answer(callInfo);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::HoldCall(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test HoldCall entry." << std::endl;
    int32_t slotId;
    std::cout << "please enter the slot id:";
    std::cin >> slotId;
    telephonyService->HoldCall(slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::UnHoldCall(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test UnHoldCall entry." << std::endl;
    int32_t slotId;
    std::cout << "please enter the slot id:";
    std::cin >> slotId;
    telephonyService->UnHoldCall(slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SwitchCall(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SwitchCall entry." << std::endl;
    int32_t slotId;
    std::cout << "please enter the slot id:";
    std::cin >> slotId;
    telephonyService->SwitchCall(slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::CombineConference(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test CombineConference entry." << std::endl;
    std::cout << "please enter the slotId:";
    int32_t slotId = 0;
    telephonyService->CombineConference(slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::InviteToConference(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test InviteToConference entry." << std::endl;
    std::vector<std::string> numberList;
    std::cout << "please enter the invite phone number:";
    std::string phoneNum;
    std::cin >> phoneNum;
    numberList.push_back(phoneNum);
    std::cout << "please enter the slotId:";
    int32_t slotId = 0;
    telephonyService->InviteToConference(slotId, numberList);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::KickOutFromConference(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test KickOutFromConference entry." << std::endl;
    std::vector<std::string> numberList;
    std::cout << "please enter the kick out phone number:";
    std::string phoneNum;
    std::cin >> phoneNum;
    numberList.push_back(phoneNum);
    std::cout << "please enter the slotId:";
    int32_t slotId = 0;
    telephonyService->KickOutFromConference(slotId, numberList);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::UpdateImsCallMode(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test UpdateImsCallMode entry." << std::endl;
    ImsCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        std::cout << "UpdateImsCallMode return, memset_s failed." << std::endl;
        return CELLULAR_CALL_ERROR;
    }
    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    callInfo.slotId = 0;
    std::cout << "please enter the connect index:";
    std::cin >> callInfo.index;
    std::cout << "please enter the update call mode():";
    int32_t mode = 0;
    std::cin >> mode;
    telephonyService->UpdateImsCallMode(callInfo, static_cast<ImsCallMode>(mode));
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::IsEmergencyPhoneNumber(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test IsEmergencyPhoneNumber entry." << std::endl;
    std::cout << "please enter the phone number:";
    std::string phoneNum;
    std::cin >> phoneNum;
    std::cout << "please enter the slot id:";
    int32_t slotId = 0;
    std::cin >> slotId;
    telephonyService->IsEmergencyPhoneNumber(slotId, phoneNum);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::GetCallFailReason(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test GetCallFailReason entry." << std::endl;
    std::cout << "please enter the slot id:";
    int32_t slotId = 0;
    std::cin >> slotId;
    telephonyService->GetCallFailReason(slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::StartDtmf(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test StartDtmf entry." << std::endl;
    std::cout << "please enter the dtmf code(0-9,#,*,A,D):";
    char dtmfCode;
    std::cin >> dtmfCode;
    std::cout << "please enter the index:";
    int32_t index = 0;
    std::cin >> index;
    std::cout << "please enter the slot id:";
    int32_t slotId = 0;
    std::cin >> slotId;
    telephonyService->StartDtmf(slotId, dtmfCode, index);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SendDtmf(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SendDtmf entry." << std::endl;
    std::cout << "please enter the dtmf code(0-9,#,*,A,D):";
    char dtmfCode;
    std::cin >> dtmfCode;
    std::cout << "please enter the index:";
    int32_t index = 0;
    std::cin >> index;
    std::cout << "please enter the slot id:";
    int32_t slotId = 0;
    std::cin >> slotId;
    telephonyService->SendDtmf(slotId, dtmfCode, index);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::StopDtmf(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test StopDtmf entry." << std::endl;
    std::cout << "please enter the index:";
    int32_t index = 0;
    std::cin >> index;
    std::cout << "please enter the slot id:";
    int32_t slotId = 0;
    std::cin >> slotId;
    telephonyService->StopDtmf(slotId, index);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::StartRtt(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test StartRtt entry." << std::endl;
    std::cout << "please enter the send msg:";
    std::string msg;
    std::cin >> msg;
    std::cout << "please enter the slot id:";
    int32_t slotId = 0;
    std::cin >> slotId;
    telephonyService->StartRtt(slotId, msg);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::StopRtt(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test StopRtt entry." << std::endl;
    std::cout << "please enter the slot id:";
    int32_t slotId = 0;
    std::cin >> slotId;
    telephonyService->StopRtt(slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SetDomainPreferenceMode(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetDomainPreferenceMode entry." << std::endl;
    std::cout << "please enter the need mode:(1 - 4)";
    int32_t mode;
    std::cin >> mode;
    std::cout << "please enter the slot id:";
    int32_t slotId = 0;
    std::cin >> slotId;
    telephonyService->SetDomainPreferenceMode(slotId, mode);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::GetDomainPreferenceMode(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test GetDomainPreferenceMode entry." << std::endl;
    std::cout << "please enter the slot id:";
    int32_t slotId = 0;
    std::cin >> slotId;
    telephonyService->GetDomainPreferenceMode(slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SetImsSwitchStatus(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetImsSwitchStatus entry." << std::endl;
    std::cout << "please enter the switch state:";
    bool active;
    std::cin >> active;
    std::cout << "please enter the slot id:";
    int32_t slotId = 0;
    std::cin >> slotId;
    telephonyService->SetImsSwitchStatus(slotId, active);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::GetImsSwitchStatus(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test GetImsSwitchStatus entry." << std::endl;
    std::cout << "please enter the slot id:";
    int32_t slotId = 0;
    std::cin >> slotId;
    telephonyService->GetImsSwitchStatus(slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SetImsConfigString(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetImsConfigString entry." << std::endl;
    std::cout << "please enter the item id:";
    int32_t item = 0;
    std::cin >> item;
    std::cout << "please enter the item value:";
    std::string value;
    std::cin >> value;
    telephonyService->SetImsConfig(static_cast<ImsConfigItem>(item), value);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SetImsConfigInt(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetImsConfigInt entry." << std::endl;
    std::cout << "please enter the item id:";
    int32_t item = 0;
    std::cin >> item;
    std::cout << "please enter the item value:";
    int32_t value = 0;
    std::cin >> value;
    telephonyService->SetImsConfig(static_cast<ImsConfigItem>(item), value);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::GetImsConfig(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test GetImsConfig entry." << std::endl;
    std::cout << "please enter the item id:";
    int32_t item = 0;
    std::cin >> item;
    telephonyService->GetImsConfig(static_cast<ImsConfigItem>(item));
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SetImsFeatureValue(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetImsFeatureValue entry." << std::endl;
    std::cout << "please enter the feature type:";
    int32_t type = 0;
    std::cin >> type;
    std::cout << "please enter the feature value:";
    int32_t value = 0;
    std::cin >> value;
    telephonyService->SetImsFeatureValue(static_cast<FeatureType>(type), value);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::GetImsFeatureValue(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test GetImsFeatureValue entry." << std::endl;
    std::cout << "please enter the feature type:";
    int32_t type = 0;
    std::cin >> type;
    telephonyService->GetImsFeatureValue(static_cast<FeatureType>(type));
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SetImsSwitchEnhanceMode(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetImsSwitchEnhanceMode entry." << std::endl;
    std::cout << "please enter the ImsSwitch enhance mode:";
    bool mode;
    std::cin >> mode;
    telephonyService->SetImsSwitchEnhanceMode(mode);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::GetImsSwitchEnhanceMode(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test GetImsSwitchEnhanceMode entry." << std::endl;
    telephonyService->GetImsSwitchEnhanceMode();
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::CtrlCamera(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test CtrlCamera entry." << std::endl;
    std::u16string cameraId = u"cameraId";
    int32_t callingUid = 0;
    int32_t callingPid = 0;
    telephonyService->CtrlCamera(cameraId, callingUid, callingPid);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SetPreviewWindow(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetPreviewWindow entry." << std::endl;
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    int32_t width = 0;
    int32_t height = 0;
    telephonyService->SetPreviewWindow(x, y, z, width, height);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SetDisplayWindow(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetDisplayWindow entry." << std::endl;
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    int32_t width = 0;
    int32_t height = 0;
    telephonyService->SetDisplayWindow(x, y, z, width, height);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SetCameraZoom(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetCameraZoom entry." << std::endl;
    float zoomRatio = 1.0;
    telephonyService->SetCameraZoom(zoomRatio);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SetPauseImage(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetPauseImage entry." << std::endl;
    std::u16string path = u"path";
    telephonyService->SetPauseImage(path);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SetDeviceDirection(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetDeviceDirection entry." << std::endl;
    int32_t rotation = 0;
    telephonyService->SetDeviceDirection(rotation);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::RegisterCellularCallBack(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test RegisterCellularCallBack entry." << std::endl;
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::IsCallBackExists(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test IsCallBackExists entry." << std::endl;
    bool ret = telephonyService->IsCallBackExists();
    std::cout << "test IsCallBackExists:" << ret << std::endl;
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsUnitTest::SetMute(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetMute entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the mute(0 - 1):";
    int32_t mute = -1;
    std::cin >> mute;
    return telephonyService->SetMute(slotId, mute);
}

int32_t ImsUnitTest::GetMute(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test GetMute entry.\n";
    int32_t slotId = 0;
    return telephonyService->GetMute(slotId);
}

int32_t ImsUnitTest::SetCallTransfer(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetCallTransfer entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the transfer type(0 - 5):";
    int32_t type = 0;
    std::cin >> type;
    std::cout << "please enter the transfer mode(0 - 4):";
    int32_t mode = 0;
    std::cin >> mode;
    std::cout << "please enter the phone number:";
    std::string transferNum;
    std::cin >> transferNum;
    int32_t classType = 1;
    return telephonyService->SetCallTransfer(slotId, type, mode, transferNum, classType);
}

int32_t ImsUnitTest::GetCallTransfer(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test GetCallTransfer entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the transfer type(0 - 5):";
    int32_t type = 0;
    std::cin >> type;
    return telephonyService->GetCallTransfer(slotId, type);
}

int32_t ImsUnitTest::SetCallRestriction(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetCallRestriction entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the fac:";
    std::string fac = "AO";
    std::cout << "please enter the phone password:";
    std::string password;
    std::cin >> password;
    std::cout << "please enter the mode:";
    int32_t mode = 0;
    std::cin >> mode;
    return telephonyService->SetCallRestriction(slotId, fac, mode, password);
}

int32_t ImsUnitTest::GetCallRestriction(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test GetCallRestriction entry.\n";
    int32_t slotId = 0;
    std::cout << "please enter the fac:";
    std::string facType = "AO";
    return telephonyService->GetCallRestriction(slotId, facType);
}

int32_t ImsUnitTest::SetCallWaiting(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test SetCallWaiting entry.\n";
    bool activate = true;
    int32_t slotId = 0;
    return telephonyService->SetCallWaiting(slotId, activate);
}

int32_t ImsUnitTest::GetCallWaiting(const sptr<ImsInterface> &telephonyService) const
{
    std::cout << "test GetCallWaiting entry.\n";
    int32_t slotId = 0;
    return telephonyService->GetCallWaiting(slotId);
}

int32_t ImsUnitTest::InputNumForInterface(const sptr<ImsInterface> &telephonyService) const
{
    int32_t ret = -1;
    int32_t InputNum = 0;
    int32_t returnNum = 1000; // end loop variable value
    bool loopFlag = true;
    while (loopFlag) {
        std::cout << "\n**********Unit Test Start**********\n"
                     "Usage: please input a cmd num:\n"
                     "1:Dial\n2:HangUp\n3:Reject\n4:Answer\n5:HoldCall\n6:UnHoldCall\n7:SwitchCall\n"
                     "8:CombineConference\n9:InviteToConference\n10:KickOutFromConference\n11:UpdateImsCallMode\n"
                     "12:IsEmergencyPhoneNumber\n13:GetCallFailReason\n100:StartDtmf\n101:SendDtmf\n102:StopDtmf\n"
                     "103:StartRtt\n104:StopRtt\n200:SetCallPreferenceMode\n201:GetCallPreferenceMode\n202:"
                     "SetImsSwitchStatus\n203:GetImsSwitchStatus\n204:SetImsConfigString\n205:SetImsConfigInt\n"
                     "206:GetImsConfig\n207:SetImsFeatureValue\n208:GetImsFeatureValue\n209:SetImsSwitchEnhanceMode\n"
                     "210:GetImsSwitchEnhanceMode\n211:SetMUte\n212:GetMute\n300:CtrlCamera\n301:SetPreviewWindow\n"
                     "302:SetDisplayWindow\n303:SetCameraZoom\n304:SetPauseImage\n305:SetDeviceDirection\n"
                     "403:SetCallTransfer\n404:GetCallTransfer\n405:SetCallRestriction\n406:GetCallRestriction\n"
                     "407:SetCallWaiting\n408:GetCallWaiting\n"
                     "500:RegisterCellularCallBack\n501:IsCallBackExists\n"
                     "1000:Exit\n"
                     "***********************************\n"
                     "Your choice: ";
        std::cin >> InputNum;
        if (InputNum == returnNum) {
            std::cout << "exiting...\n";
            break;
        }
        auto itFunc = requestFuncMap_.find(InputNum);
        if (itFunc != requestFuncMap_.end()) {
            auto requestFunc = itFunc->second;
            if (requestFunc != nullptr) {
                ret = (this->*requestFunc)(telephonyService);
            }
        }
        if (ret != CELLULAR_CALL_SUCCESS) {
            std::cout << "this execution did not return a successful value, please check.\n";
            return ret;
        }
    }
    return CELLULAR_CALL_SUCCESS;
}

/**
 * @tc.number   ims_vendor_test_001
 * @tc.name     Test the corresponding functions by entering commands, such as 1 -- Dial, 2 -- Hangup, 3 -- Reject, etc
 * @tc.desc     Function test
 */
HWTEST_F(ImsUnitTest, ims_vendor_test_001, TestSize.Level0)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemAbilityMgr == nullptr) {
        std::cout << "ImsUnitTest return, Get ISystemAbilityManager failed!\n";
        return;
    }
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_IMS_SYS_ABILITY_ID);
    if (remote == nullptr) {
        std::cout << "ImsUnitTest return, Remote service not exists!\n";
        return;
    }
    auto telephonyService = iface_cast<ImsInterface>(remote);
    std::cout << "ImsUnitTest HWTEST_F ims_vendor_test_001";
}

/**
 * @tc.number   ims_vendor_test_002
 * @tc.name     Test the corresponding functions by entering commands, such as 1 -- Dial, 2 -- Hangup, 3 -- Reject, etc
 * @tc.desc     Function test
 */
HWTEST_F(ImsUnitTest, ims_vendor_test_002, TestSize.Level1)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemAbilityMgr == nullptr) {
        std::cout << "ImsUnitTest return, Get ISystemAbilityManager failed!\n";
        return;
    }
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_IMS_SYS_ABILITY_ID);
    if (remote == nullptr) {
        std::cout << "ImsUnitTest return, Remote service not exists!\n";
        return;
    }
    auto telephonyService = iface_cast<ImsInterface>(remote);
    std::cout << "ImsUnitTest HWTEST_F ims_vendor_test_002";
}
} // namespace Telephony
} // namespace OHOS
