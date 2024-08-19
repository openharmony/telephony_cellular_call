/*
 * Copyright (C) 2021-2023 Huawei Device Co., Ltd.
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

#include "ims_test.h"

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
#include "securec.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
const int32_t SIM1_SLOTID = 0;
const std::string PHONE_NUMBER = "0000000";
const std::string PHONE_NUMBER_SECOND = "1111111";
const std::string PHONE_NUMBER_THIRD = "2222222";
const std::string PHONE_NUMBER_FOUR = "3333333";
const int32_t CELLULAR_CALL_SUCCESS = 0;
const int32_t DEFAULT_INDEX = 1;

void ImsTest::SetUpTestCase(void)
{
    // step 3: Set Up Test Case
    std::cout << "---------- ImsCoreServiceClient start ------------" << std::endl;
    DelayedSingleton<ImsCoreServiceClient>::GetInstance()->Init();
}

void ImsTest::TearDownTestCase(void)
{
    // step 3: Tear Down Test Case
}

void ImsTest::SetUp(void)
{
    // step 3: input testcase setup step
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_DOMAIN_PREFERENCE_MODE)] =
        &ImsTest::SetDomainPreferenceMode;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::GET_DOMAIN_PREFERENCE_MODE)] =
        &ImsTest::GetDomainPreferenceMode;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_IMS_SWITCH_STATUS)] =
        &ImsTest::SetImsSwitchStatus;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::GET_IMS_SWITCH_STATUS)] =
        &ImsTest::GetImsSwitchStatus;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_IMS_CONFIG_STRING)] =
        &ImsTest::SetImsConfigString;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_IMS_CONFIG_INT)] = &ImsTest::SetImsConfigInt;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::GET_IMS_CONFIG)] = &ImsTest::GetImsConfig;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_IMS_FEATURE)] = &ImsTest::SetImsFeatureValue;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::GET_IMS_FEATURE)] = &ImsTest::GetImsFeatureValue;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::CTRL_CAMERA)] = &ImsTest::ControlCamera;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_PREVIEW_WINDOW)] = &ImsTest::SetPreviewWindow;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_DISPLAY_WINDOW)] = &ImsTest::SetDisplayWindow;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_CAMERA_ZOOM)] = &ImsTest::SetCameraZoom;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_PAUSE_IMAGE)] = &ImsTest::SetPausePicture;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SET_DEVICE_DIRECTION)] =
        &ImsTest::SetDeviceDirection;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SEND_CALL_MEDIA_MODE_REQUEST)] =
        &ImsTest::SendUpdateCallMediaModeRequest;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::SEND_CALL_MEDIA_MODE_RESPONSE)] =
        &ImsTest::SendUpdateCallMediaModeResponse;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::CANCEL_CALL_UPGRADE)] =
        &ImsTest::CancelCallUpgrade;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterfaceCode::REQUEST_CAMERA_CAPABILITY)] =
        &ImsTest::RequestCameraCapabilities;
}

void ImsTest::TearDown(void)
{
    // step 3: input testcase teardown step
}

int32_t ImsTest::SetDomainPreferenceMode(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetDomainPreferenceMode entry." << std::endl;
    std::cout << "please enter the need mode:(1 - 4)";
    int32_t mode;
    std::cin >> mode;
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    return telephonyService->SetDomainPreferenceMode(slotId, mode);
}

int32_t ImsTest::GetDomainPreferenceMode(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetDomainPreferenceMode entry." << std::endl;
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    return telephonyService->GetDomainPreferenceMode(slotId);
}

int32_t ImsTest::SetImsSwitchStatus(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetImsSwitchStatus entry." << std::endl;
    std::cout << "please enter the switch state:";
    bool active;
    std::cin >> active;
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    return telephonyService->SetImsSwitchStatus(slotId, active);
}

int32_t ImsTest::GetImsSwitchStatus(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetImsSwitchStatus entry." << std::endl;
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    bool enabled;
    return telephonyService->GetImsSwitchStatus(slotId, enabled);
}

int32_t ImsTest::SetImsConfigString(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetImsConfigString entry." << std::endl;
    std::cout << "please enter the item id:";
    int32_t item = 0;
    std::cin >> item;
    std::cout << "please enter the item value:";
    std::string value;
    std::cin >> value;
    int32_t slotId = 0;
    return telephonyService->SetImsConfig(slotId, static_cast<ImsConfigItem>(item), value);
}

int32_t ImsTest::SetImsConfigInt(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetImsConfigInt entry." << std::endl;
    std::cout << "please enter the item id:";
    int32_t item = 0;
    std::cin >> item;
    std::cout << "please enter the item value:";
    int32_t value = 0;
    std::cin >> value;
    int32_t slotId = 0;
    return telephonyService->SetImsConfig(slotId, static_cast<ImsConfigItem>(item), value);
}

int32_t ImsTest::GetImsConfig(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetImsConfig entry." << std::endl;
    std::cout << "please enter the item id:";
    int32_t item = 0;
    std::cin >> item;
    int32_t slotId = 0;
    return telephonyService->GetImsConfig(slotId, static_cast<ImsConfigItem>(item));
}

int32_t ImsTest::SetImsFeatureValue(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetImsFeatureValue entry." << std::endl;
    std::cout << "please enter the feature type:";
    int32_t type = 0;
    std::cin >> type;
    std::cout << "please enter the feature value:";
    int32_t value = 0;
    std::cin >> value;
    int32_t slotId = 0;
    return telephonyService->SetImsFeatureValue(slotId, static_cast<FeatureType>(type), value);
}

int32_t ImsTest::GetImsFeatureValue(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetImsFeatureValue entry." << std::endl;
    std::cout << "please enter the feature type:";
    int32_t type = 0;
    std::cin >> type;
    int32_t slotId = 0;
    return telephonyService->GetImsFeatureValue(slotId, static_cast<FeatureType>(type));
}

int32_t ImsTest::ControlCamera(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test ControlCamera entry." << std::endl;
    int32_t slotId = SIM1_SLOTID;
    int32_t callIndex = DEFAULT_INDEX;
    std::string cameraId = "cameraId";
    return telephonyService->ControlCamera(slotId, callIndex, cameraId);
}

int32_t ImsTest::SetPreviewWindow(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetPreviewWindow entry." << std::endl;
    int32_t slotId = SIM1_SLOTID;
    int32_t callIndex = DEFAULT_INDEX;
    std::string surfaceId = "123";
    std::string subSurfaceId = surfaceId.substr(0, 1);
    uint64_t tmpSurfaceId = std::stoull(subSurfaceId);
    auto surface = SurfaceUtils::GetInstance()->GetSurface(tmpSurfaceId);
    if (surface == nullptr) {
        surfaceId = "";
    }
    return telephonyService->SetPreviewWindow(slotId, callIndex, subSurfaceId, surface);
}

int32_t ImsTest::SetDisplayWindow(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetDisplayWindow entry." << std::endl;
    int32_t slotId = SIM1_SLOTID;
    int32_t callIndex = DEFAULT_INDEX;
    std::string surfaceId = "123";
    std::string subSurfaceId = surfaceId.substr(0, 1);
    uint64_t tmpSurfaceId = std::stoull(subSurfaceId);
    auto surface = SurfaceUtils::GetInstance()->GetSurface(tmpSurfaceId);
    if (surface == nullptr) {
        surfaceId = "";
    }
    return telephonyService->SetDisplayWindow(slotId, callIndex, subSurfaceId, surface);
}

int32_t ImsTest::SetCameraZoom(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetCameraZoom entry." << std::endl;
    float zoomRatio = 1.0;
    return telephonyService->SetCameraZoom(zoomRatio);
}

int32_t ImsTest::SetPausePicture(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetPausePicture entry." << std::endl;
    int32_t slotId = SIM1_SLOTID;
    int32_t callIndex = DEFAULT_INDEX;
    std::string path = "path";
    return telephonyService->SetPausePicture(slotId, callIndex, path);
}

int32_t ImsTest::SetDeviceDirection(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetDeviceDirection entry." << std::endl;
    int32_t slotId = SIM1_SLOTID;
    int32_t callIndex = DEFAULT_INDEX;
    int32_t rotation = 0;
    return telephonyService->SetDeviceDirection(slotId, callIndex, rotation);
}

int32_t ImsTest::SendUpdateCallMediaModeRequest(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SendUpdateCallMediaModeRequest entry." << std::endl;
    CellularCallInfo callInfo;
    callInfo.accountId = SIM1_SLOTID;
    callInfo.slotId = SIM1_SLOTID;
    callInfo.index = DEFAULT_INDEX;
    callInfo.callType = CallType::TYPE_IMS;
    callInfo.videoState = 0; // 0 means audio
    if (memset_s(callInfo.phoneNum, kMaxNumberLen, 0, kMaxNumberLen) != EOK) {
        return TELEPHONY_ERR_MEMSET_FAIL;
    }
    if (memcpy_s(callInfo.phoneNum, kMaxNumberLen, PHONE_NUMBER.c_str(), PHONE_NUMBER.length()) != EOK) {
        return TELEPHONY_ERR_MEMCPY_FAIL;
    }
    std::cout << "please enter the ims call mode:";
    std::cout << "0:audio_only, 1:send_only, 2:receive_only, 3:send_receive, 4:video_paused";
    ImsCallMode callMode = ImsCallMode::CALL_MODE_AUDIO_ONLY;
    int32_t input = 0;
    std::cin >> input;
    callMode = static_cast<ImsCallMode>(input);
    return telephonyService->SendUpdateCallMediaModeRequest(callInfo, callMode);
}

int32_t ImsTest::SendUpdateCallMediaModeResponse(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SendUpdateCallMediaModeResponse entry." << std::endl;
    CellularCallInfo callInfo;
    callInfo.accountId = SIM1_SLOTID;
    callInfo.slotId = SIM1_SLOTID;
    callInfo.index = DEFAULT_INDEX;
    callInfo.callType = CallType::TYPE_IMS;
    callInfo.videoState = 0; // 0 means audio
    if (memset_s(callInfo.phoneNum, kMaxNumberLen, 0, kMaxNumberLen) != EOK) {
        return TELEPHONY_ERR_MEMSET_FAIL;
    }
    if (memcpy_s(callInfo.phoneNum, kMaxNumberLen, PHONE_NUMBER.c_str(), PHONE_NUMBER.length()) != EOK) {
        return TELEPHONY_ERR_MEMCPY_FAIL;
    }
    std::cout << "please enter the ims call mode:";
    std::cout << "0:audio_only, 1:send_only, 2:receive_only, 3:send_receive, 4:video_paused";
    ImsCallMode callMode = ImsCallMode::CALL_MODE_AUDIO_ONLY;
    int32_t input = 0;
    std::cin >> input;
    callMode = static_cast<ImsCallMode>(input);
    return telephonyService->SendUpdateCallMediaModeResponse(callInfo, callMode);
}

int32_t ImsTest::CancelCallUpgrade(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test CancelCallUpgrade entry." << std::endl;
    int32_t slotId = SIM1_SLOTID;
    int32_t callIndex = DEFAULT_INDEX;
    return telephonyService->CancelCallUpgrade(slotId, callIndex);
}

int32_t ImsTest::RequestCameraCapabilities(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test RequestCameraCapabilities entry." << std::endl;
    int32_t slotId = SIM1_SLOTID;
    int32_t callIndex = DEFAULT_INDEX;
    return telephonyService->RequestCameraCapabilities(slotId, callIndex);
}

int32_t ImsTest::InputNumForInterface(const sptr<CellularCallInterface> &telephonyService) const
{
    int32_t ret = -1;
    bool loopFlag = true;
    int32_t inputNumber = 0;
    int32_t returnNum = 1000; // end loop variable value
    while (loopFlag) {
        std::cout << "\n**********Unit Test Start**********\n"
                     "Usage: please input a cmd num:\n"
                     "300:SetCallPreferenceMode\n"
                     "301:GetCallPreferenceMode\n"
                     "302:SetImsSwitchStatus\n"
                     "303:GetImsSwitchStatus\n"
                     "304:SetImsConfigString\n"
                     "305:SetImsConfigInt\n"
                     "306:GetImsConfig\n"
                     "307:SetImsFeatureValue\n"
                     "308:GetImsFeatureValue\n"
                     "400:ControlCamera\n"
                     "401:SetPreviewWindow\n"
                     "402:SetDisplayWindow\n"
                     "403:SetCameraZoom\n"
                     "404:SetPausePicture\n"
                     "405:SetDeviceDirection\n"
                     "406:SendUpdateCallMediaModeRequest\n"
                     "407:SendUpdateCallMediaModeResponse\n"
                     "408:CancelCallUpgrade\n"
                     "409:RequestCameraCapabilities\n"
                     "1000:Exit\n"
                     "***********************************\n"
                     "Your choice: ";
        std::cin >> inputNumber;
        if (inputNumber == returnNum) {
            std::cout << "exiting...\n";
            break;
        }
        auto itFunction = requestFuncMap_.find(inputNumber);
        if (itFunction != requestFuncMap_.end()) {
            auto requestFunction = itFunction->second;
            if (requestFunction != nullptr) {
                ret = (this->*requestFunction)(telephonyService);
            }
        }
        if (ret != CELLULAR_CALL_SUCCESS) {
            std::cout << "this execution did not return a successful value, please check.\n";
            return ret;
        }
    }
    return CELLULAR_CALL_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS
