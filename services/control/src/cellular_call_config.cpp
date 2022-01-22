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
std::map<int32_t, int32_t> CellularCallConfig::modeMap_;
std::map<int32_t, int32_t> CellularCallConfig::activeMap_;
std::map<int32_t, int32_t> CellularCallConfig::modeTempMap_;
std::map<int32_t, std::vector<EmergencyInfo>> CellularCallConfig::eccListMap_;

int32_t CellularCallConfig::SetDomainPreferenceMode(int32_t slotId, int32_t mode)
{
    if (mode < DomainPreferenceMode::CS_VOICE_ONLY || mode > DomainPreferenceMode::IMS_PS_VOICE_ONLY) {
        TELEPHONY_LOGE("SetDomainPreferenceMode return, mode out of range!");
        return CALL_ERR_PARAMETER_OUT_OF_RANGE;
    }
    modeTempMap_[slotId] = mode;
    return configRequest_.SetDomainPreferenceModeRequest(slotId, mode);
}

int32_t CellularCallConfig::GetDomainPreferenceMode(int32_t slotId)
{
    return configRequest_.GetDomainPreferenceModeRequest(slotId);
}

int32_t CellularCallConfig::SetLteImsSwitchStatus(int32_t slotId, bool active)
{
    /*
     * The Mobility_Management_IMS_Voice_Termination leaf indicates whether the UE mobility management performs
     * additional procedures as specified in 3GPP TS 24.008 [17] and 3GPP TS 24.301 [15] to support
     * terminating access domain selection by the network.
     * -	Format: bool
     * -	Access Types: Get, Replace
     * -	Values: 0, 1
     *      0 – Mobility Management for IMS Voice Termination disabled.
     *      1 – Mobility Management for IMS Voice Termination enabled.
     */
    return configRequest_.SetLteImsSwitchStatusRequest(slotId, active);
}

int32_t CellularCallConfig::GetLteImsSwitchStatus(int32_t slotId)
{
    /*
     * The Mobility_Management_IMS_Voice_Termination leaf indicates whether the UE mobility management performs
     * additional procedures as specified in 3GPP TS 24.008 [17] and 3GPP TS 24.301 [15] to support
     * terminating access domain selection by the network.
     * -	Format: bool
     * -	Access Types: Get, Replace
     * -	Values: 0, 1
     *      0 – Mobility Management for IMS Voice Termination disabled.
     *      1 – Mobility Management for IMS Voice Termination enabled.
     */
    return configRequest_.GetLteImsSwitchStatusRequest(slotId);
}

void CellularCallConfig::GetDomainPreferenceModeResponse(int32_t slotId, int32_t mode)
{
    modeMap_[slotId] = mode;
}

void CellularCallConfig::GetLteImsSwitchStatusResponse(int32_t slotId, int32_t active)
{
    activeMap_[slotId] = active;
}

int32_t CellularCallConfig::GetPreferenceMode(int32_t slotId) const
{
    return modeMap_[slotId];
}

int32_t CellularCallConfig::GetSwitchStatus(int32_t slotId) const
{
    return activeMap_[slotId];
}

int32_t CellularCallConfig::SetImsConfig(ImsConfigItem item, const std::string &value)
{
    return configRequest_.SetImsConfigRequest(item, value);
}

int32_t CellularCallConfig::SetImsConfig(ImsConfigItem item, int32_t value)
{
    return configRequest_.SetImsConfigRequest(item, value);
}

int32_t CellularCallConfig::GetImsConfig(ImsConfigItem item)
{
    return configRequest_.GetImsConfigRequest(item);
}

int32_t CellularCallConfig::SetImsFeatureValue(FeatureType type, int32_t value)
{
    return configRequest_.SetImsFeatureValueRequest(type, value);
}

int32_t CellularCallConfig::GetImsFeatureValue(FeatureType type)
{
    return configRequest_.GetImsFeatureValueRequest(type);
}

int32_t CellularCallConfig::SetImsSwitchEnhanceMode(bool value)
{
    return configRequest_.SetImsSwitchEnhanceModeRequest(value);
}

int32_t CellularCallConfig::GetImsSwitchEnhanceMode()
{
    return configRequest_.GetImsSwitchEnhanceModeRequest();
}

int32_t CellularCallConfig::CtrlCamera(const std::u16string &cameraId, int32_t callingUid, int32_t callingPid)
{
    return configRequest_.CtrlCameraRequest(cameraId, callingUid, callingPid);
}

int32_t CellularCallConfig::SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    return configRequest_.SetPreviewWindowRequest(x, y, z, width, height);
}

int32_t CellularCallConfig::SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    return configRequest_.SetDisplayWindowRequest(x, y, z, width, height);
}

int32_t CellularCallConfig::SetCameraZoom(float zoomRatio)
{
    return configRequest_.SetCameraZoomRequest(zoomRatio);
}

int32_t CellularCallConfig::SetPauseImage(const std::u16string &path)
{
    return configRequest_.SetPauseImageRequest(path);
}

int32_t CellularCallConfig::SetDeviceDirection(int32_t rotation)
{
    return configRequest_.SetDeviceDirectionRequest(rotation);
}

void CellularCallConfig::SetTempMode(int32_t slotId)
{
    modeMap_[slotId] = modeTempMap_[slotId];
}

void CellularCallConfig::InitModeActive()
{
    int32_t slotId = DEFAULT_SIM_SLOT_ID;
    modeMap_[slotId] = DomainPreferenceMode::IMS_PS_VOICE_PREFERRED;
    activeMap_[slotId] = true;
    eccListMap_.clear();
}

int32_t CellularCallConfig::SetMute(int32_t slotId, int32_t mute)
{
    return configRequest_.SetMuteRequest(slotId, mute);
}

int32_t CellularCallConfig::GetMute(int32_t slotId)
{
    return configRequest_.GetMuteRequest(slotId);
}

int32_t CellularCallConfig::GetEmergencyCallList(int32_t slotId)
{
    return configRequest_.GetEmergencyCallListRequest(slotId);
}

void CellularCallConfig::GetEmergencyCallListResponse(int32_t slotId, const EmergencyInfoList &eccList)
{
    eccListMap_[slotId] = eccList.calls;
}

std::vector<EmergencyInfo> CellularCallConfig::GetEccCallList(int32_t slotId)
{
    return eccListMap_[slotId];
}
} // namespace Telephony
} // namespace OHOS
