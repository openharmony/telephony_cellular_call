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

#include "cellular_call_config.h"

#include "cellular_call_data_struct.h"

namespace OHOS {
namespace Telephony {
int32_t CellularCallConfig::mode_ = CS_VOICE_ONLY;
int32_t CellularCallConfig::active_ = TURN_OFF;
int32_t CellularCallConfig::modeTemp_ = CS_VOICE_ONLY;

int32_t CellularCallConfig::SetCallPreferenceMode(int32_t mode)
{
    if (mode < CallPreferenceMode::CS_VOICE_ONLY || mode > CallPreferenceMode::IMS_PS_VOICE_ONLY) {
        TELEPHONY_LOGE("SetCallPreferenceMode return, mode out of range!");
        return CALL_ERR_PARAMETER_OUT_OF_RANGE;
    }
    modeTemp_ = mode;
    return configRequest_.SetCallPreferenceModeRequest(mode);
}

int32_t CellularCallConfig::GetCallPreferenceMode()
{
    return configRequest_.GetCallPreferenceModeRequest();
}

int32_t CellularCallConfig::SetLteImsSwitchStatus(bool active)
{
    return configRequest_.SetLteImsSwitchStatusRequest(active);
}

int32_t CellularCallConfig::GetLteImsSwitchStatus()
{
    return configRequest_.GetLteImsSwitchStatusRequest();
}

void CellularCallConfig::GetCallPreferenceModeResponse(const std::shared_ptr<int32_t> &mode)
{
    if (mode == nullptr) {
        TELEPHONY_LOGE("GetCallPreferenceModeResponse return, mode is nullptr");
        return;
    }
    mode_ = *mode;
}

void CellularCallConfig::GetLteImsSwitchStatusResponse(const std::shared_ptr<int32_t> &active)
{
    if (active == nullptr) {
        TELEPHONY_LOGE("GetCallPreferenceModeResponse return, active is nullptr");
        return;
    }
    active_ = *active;
}

int32_t CellularCallConfig::GetPreferenceMode() const
{
    return mode_;
}

int32_t CellularCallConfig::GetSwitchStatus() const
{
    return active_;
}

int32_t CellularCallConfig::CtrlCamera(
    const std::u16string &cameraId, const std::u16string &callingPackage, int32_t callingUid, int32_t callingPid)
{
    TELEPHONY_LOGI("CellularCallConfig::CtrlCamera entry");
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConfig::SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    TELEPHONY_LOGI("CellularCallConfig::SetPreviewWindow entry");
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConfig::SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    TELEPHONY_LOGI("CellularCallConfig::SetDisplayWindow entry");
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConfig::SetCameraZoom(float zoomRatio)
{
    TELEPHONY_LOGI("CellularCallConfig::SetCameraZoom entry");
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConfig::SetPauseImage(const std::u16string &path)
{
    TELEPHONY_LOGI("CellularCallConfig::SetPauseImage entry");
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConfig::SetDeviceDirection(int32_t rotation)
{
    TELEPHONY_LOGI("CellularCallConfig::SetDeviceDirection entry");
    return TELEPHONY_SUCCESS;
}

void CellularCallConfig::SetTempMode()
{
    mode_ = modeTemp_;
}
} // namespace Telephony
} // namespace OHOS
