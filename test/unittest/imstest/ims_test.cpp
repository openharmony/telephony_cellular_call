/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
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

#include "iservice_registry.h"
#include "securec.h"
#include "system_ability_definition.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
const int32_t CELLULAR_CALL_SUCCESS = 0;

void ImsTest::SetUpTestCase(void)
{
    // step 3: Set Up Test Case
}

void ImsTest::TearDownTestCase(void)
{
    // step 3: Tear Down Test Case
}

void ImsTest::SetUp(void)
{
    // step 3: input testcase setup step
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_DOMAIN_PREFERENCE_MODE)] =
        &ImsTest::SetDomainPreferenceMode;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::GET_DOMAIN_PREFERENCE_MODE)] =
        &ImsTest::GetDomainPreferenceMode;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_LTE_IMS_SWITCH_STATUS)] =
        &ImsTest::SetLteImsSwitchStatus;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::GET_LTE_IMS_SWITCH_STATUS)] =
        &ImsTest::GetLteImsSwitchStatus;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_IMS_CONFIG_STRING)] =
        &ImsTest::SetImsConfigString;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_IMS_CONFIG_INT)] =
        &ImsTest::SetImsConfigInt;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::GET_IMS_CONFIG)] =
        &ImsTest::GetImsConfig;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_IMS_FEATURE)] =
        &ImsTest::SetImsFeatureValue;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::GET_IMS_FEATURE)] =
        &ImsTest::GetImsFeatureValue;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_IMS_SWITCH_ENHANCE_MODE)] =
        &ImsTest::SetImsSwitchEnhanceMode;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::GET_IMS_SWITCH_ENHANCE_MODE)] =
        &ImsTest::GetImsSwitchEnhanceMode;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::CTRL_CAMERA)] = &ImsTest::CtrlCamera;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_PREVIEW_WINDOW)] =
        &ImsTest::SetPreviewWindow;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_DISPLAY_WINDOW)] =
        &ImsTest::SetDisplayWindow;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_CAMERA_ZOOM)] =
        &ImsTest::SetCameraZoom;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_PAUSE_IMAGE)] =
        &ImsTest::SetPauseImage;
    requestFuncMap_[static_cast<int32_t>(CellularCallInterface::OperationType::SET_DEVICE_DIRECTION)] =
        &ImsTest::SetDeviceDirection;
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

int32_t ImsTest::SetLteImsSwitchStatus(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetLteImsSwitchStatus entry." << std::endl;
    std::cout << "please enter the switch state:";
    bool active;
    std::cin >> active;
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    return telephonyService->SetLteImsSwitchStatus(slotId, active);
}

int32_t ImsTest::GetLteImsSwitchStatus(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetLteImsSwitchStatus entry." << std::endl;
    int32_t slotId = 0;
    std::cout << "please enter the slotId:(0   1)";
    std::cin >> slotId;
    return telephonyService->GetLteImsSwitchStatus(slotId);
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

int32_t ImsTest::SetImsSwitchEnhanceMode(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetImsSwitchEnhanceMode entry." << std::endl;
    std::cout << "please enter the ImsSwitch enhance mode:";
    bool mode;
    std::cin >> mode;
    int32_t slotId = 0;
    return telephonyService->SetImsSwitchEnhanceMode(slotId, mode);
}

int32_t ImsTest::GetImsSwitchEnhanceMode(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetImsSwitchEnhanceMode entry." << std::endl;
    int32_t slotId = 0;
    return telephonyService->GetImsSwitchEnhanceMode(slotId);
}

int32_t ImsTest::CtrlCamera(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test CtrlCamera entry." << std::endl;
    std::u16string cameraId = u"cameraId";
    int32_t callingUid = 0;
    int32_t callingPid = 0;
    return telephonyService->CtrlCamera(cameraId, callingUid, callingPid);
}

int32_t ImsTest::SetPreviewWindow(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetPreviewWindow entry." << std::endl;
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    int32_t width = 0;
    int32_t height = 0;
    return telephonyService->SetPreviewWindow(x, y, z, width, height);
}

int32_t ImsTest::SetDisplayWindow(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetDisplayWindow entry." << std::endl;
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    int32_t width = 0;
    int32_t height = 0;
    return telephonyService->SetDisplayWindow(x, y, z, width, height);
}

int32_t ImsTest::SetCameraZoom(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetCameraZoom entry." << std::endl;
    float zoomRatio = 1.0;
    return telephonyService->SetCameraZoom(zoomRatio);
}

int32_t ImsTest::SetPauseImage(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetPauseImage entry." << std::endl;
    std::u16string path = u"path";
    return telephonyService->SetPauseImage(path);
}

int32_t ImsTest::SetDeviceDirection(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetDeviceDirection entry." << std::endl;
    int32_t rotation = 0;
    return telephonyService->SetDeviceDirection(rotation);
}

int32_t ImsTest::InputNumForInterface(const sptr<CellularCallInterface> &telephonyService) const
{
    int32_t ret = -1;
    bool loopFlag = true;
    int32_t InputNum = 0;
    int32_t returnNum = 1000; // end loop variable value
    while (loopFlag) {
        std::cout << "\n**********Unit Test Start**********\n"
                     "Usage: please input a cmd num:\n"
                     "300:SetCallPreferenceMode\n"
                     "301:GetCallPreferenceMode\n"
                     "302:SetLteImsSwitchStatus\n"
                     "303:GetLteImsSwitchStatus\n"
                     "304:SetImsConfigString\n"
                     "305:SetImsConfigInt\n"
                     "306:GetImsConfig\n"
                     "307:SetImsFeatureValue\n"
                     "308:GetImsFeatureValue\n"
                     "309:SetImsSwitchEnhanceMode\n"
                     "310:GetImsSwitchEnhanceMode\n"
                     "400:CtrlCamera\n"
                     "401:SetPreviewWindow\n"
                     "402:SetDisplayWindow\n"
                     "403:SetCameraZoom\n"
                     "404:SetPauseImage\n"
                     "405:SetDeviceDirection\n"
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
 * @tc.number   cellular_call_ims_test_001
 * @tc.name     Test the corresponding functions by entering commands, such as 300 -- SetCallPreferenceMode, 301 --
 *              GetCallPreferenceMode, etc
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ims_test_001, TestSize.Level0)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemAbilityMgr == nullptr) {
        std::cout << "CellularCallService Get ISystemAbilityManager failed.\n";
        return;
    }
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    if (remote == nullptr) {
        std::cout << "CellularCallService Remote service not exists.\n";
        return;
    }
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    std::cout << "HWTEST_F cellular_call_ims_test_001";
}

/**
 * @tc.number   cellular_call_ims_test_002
 * @tc.name     Test the corresponding functions by entering commands, such as 300 -- SetCallPreferenceMode, 301 --
 *              GetCallPreferenceMode, etc
 * @tc.desc     Function test
 */
HWTEST_F(ImsTest, cellular_call_ims_test_002, TestSize.Level1)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemAbilityMgr == nullptr) {
        std::cout << "CellularCallService Get ISystemAbilityManager failed.\n";
        return;
    }
    auto remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    if (remote == nullptr) {
        std::cout << "CellularCallService Remote service not exists.\n";
        return;
    }
    auto telephonyService = iface_cast<CellularCallInterface>(remote);
    std::cout << "HWTEST_F cellular_call_ims_test_002";
}
} // namespace Telephony
} // namespace OHOS
