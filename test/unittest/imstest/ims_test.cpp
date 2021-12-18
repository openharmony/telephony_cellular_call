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
    requestFuncMap_['A'] = &ImsTest::SetCallPreferenceMode;
    requestFuncMap_['B'] = &ImsTest::GetCallPreferenceMode;
    requestFuncMap_['C'] = &ImsTest::SetLteImsSwitchStatus;
    requestFuncMap_['D'] = &ImsTest::GetLteImsSwitchStatus;
    requestFuncMap_['E'] = &ImsTest::CtrlCamera;
    requestFuncMap_['F'] = &ImsTest::SetPreviewWindow;
    requestFuncMap_['G'] = &ImsTest::SetDisplayWindow;
    requestFuncMap_['H'] = &ImsTest::SetCameraZoom;
    requestFuncMap_['I'] = &ImsTest::SetPauseImage;
    requestFuncMap_['J'] = &ImsTest::SetDeviceDirection;
}

void ImsTest::TearDown(void)
{
    // step 3: input testcase teardown step
}

int32_t ImsTest::SetCallPreferenceMode(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetCallPreferenceMode entry." << std::endl;
    int32_t slotId = 0;
    std::cout << "please enter the need mode:(1 - 4)";
    int32_t mode;
    std::cin >> mode;
    telephonyService->SetCallPreferenceMode(slotId, mode);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsTest::GetCallPreferenceMode(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetCallPreferenceMode entry." << std::endl;
    int32_t slotId = 0;
    telephonyService->GetCallPreferenceMode(slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsTest::SetLteImsSwitchStatus(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetLteImsSwitchStatus entry." << std::endl;
    int32_t slotId = 0;
    std::cout << "please enter the switch state:";
    bool active;
    std::cin >> active;
    telephonyService->SetLteImsSwitchStatus(slotId, active);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsTest::GetLteImsSwitchStatus(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test GetLteImsSwitchStatus entry." << std::endl;
    int32_t slotId = 0;
    telephonyService->GetLteImsSwitchStatus(slotId);
    return CELLULAR_CALL_SUCCESS;
}

int32_t ImsTest::CtrlCamera(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test CtrlCamera entry." << std::endl;
    std::u16string cameraId = u"cameraId";
    std::u16string callingPackage = u"callingPackage";
    int32_t callingUid = 0;
    int32_t callingPid = 0;
    telephonyService->CtrlCamera(cameraId, callingPackage, callingUid, callingPid);
    return 0;
}

int32_t ImsTest::SetPreviewWindow(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetPreviewWindow entry." << std::endl;
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    int32_t width = 0;
    int32_t height = 0;
    telephonyService->SetPreviewWindow(x, y, z, width, height);
    return 0;
}

int32_t ImsTest::SetDisplayWindow(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetDisplayWindow entry." << std::endl;
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    int32_t width = 0;
    int32_t height = 0;
    telephonyService->SetDisplayWindow(x, y, z, width, height);
    return 0;
}

int32_t ImsTest::SetCameraZoom(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetCameraZoom entry." << std::endl;
    float zoomRatio = 1.0;
    telephonyService->SetCameraZoom(zoomRatio);
    return 0;
}

int32_t ImsTest::SetPauseImage(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetPauseImage entry." << std::endl;
    std::u16string path = u"path";
    telephonyService->SetPauseImage(path);
    return 0;
}

int32_t ImsTest::SetDeviceDirection(const sptr<CellularCallInterface> &telephonyService) const
{
    std::cout << "test SetDeviceDirection entry." << std::endl;
    int32_t rotation = 0;
    telephonyService->SetDeviceDirection(rotation);
    return 0;
}

int32_t ImsTest::InputNumForInterface(const sptr<CellularCallInterface> &telephonyService) const
{
    char interfaceNum = '0';
    bool loopFlag = true;
    int32_t ret = -1;
    while (loopFlag) {
        std::cout << "\n**********Unit Test Start**********\n"
                     "Usage: please input a cmd num:\n"
                     "A:SetCallPreferenceMode\n"
                     "B:GetCallPreferenceMode\n"
                     "C:SetLteImsSwitchStatus\n"
                     "D:GetLteImsSwitchStatus\n"
                     "E:CtrlCamera\n"
                     "F:SetPreviewWindow\n"
                     "G:SetDisplayWindow\n"
                     "H:SetCameraZoom\n"
                     "I:SetPauseImage\n"
                     "J:SetDeviceDirection\n"
                     "W:Exit\n"
                     "***********************************\n"
                     "Your choice: ";
        std::cin >> interfaceNum;
        if (interfaceNum == 'W') {
            break;
        }
        auto itFunc = requestFuncMap_.find(interfaceNum);
        if (itFunc != requestFuncMap_.end()) {
            auto requestFunc = itFunc->second;
            if (requestFunc != nullptr) {
                ret = (this->*requestFunc)(telephonyService);
            }
        }
        if (ret != CELLULAR_CALL_SUCCESS) {
            return ret;
        }
    }
    return 0;
}

HWTEST_F(ImsTest, cellular_call_interface_002, TestSize.Level1)
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
    sptr<CellularCallInterface> telephonyService = iface_cast<CellularCallInterface>(remote);
    std::cout << "HWTEST_F cellular_call_interface_002";
}
} // namespace Telephony
} // namespace OHOS
