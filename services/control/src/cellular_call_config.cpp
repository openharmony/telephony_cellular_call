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

#include "cellular_call_config.h"

#include "telephony_types.h"

#include "cellular_call_register.h"
#include "cellular_call_data_struct.h"

#include "cellular_call_service.h"

#include "sim_state_type.h"

#include "module_service_utils.h"

#include "string_ex.h"

#include "core_manager_inner.h"

#include "parameters.h"

namespace OHOS {
namespace Telephony {
std::map<int32_t, int32_t> CellularCallConfig::modeMap_;

std::map<int32_t, int32_t> CellularCallConfig::modeTempMap_;
std::mutex mutex_;
std::map<int32_t, std::vector<EmergencyCall>> CellularCallConfig::eccListRadioMap_;
std::vector<EmergencyCall> CellularCallConfig::eccList3gppHasSim_;
std::vector<EmergencyCall> CellularCallConfig::eccList3gppNoSim_;
std::map<int32_t, std::vector<EmergencyCall>> CellularCallConfig::allEccList_;
int32_t CellularCallConfig::SIM_PRESENT = 1;
int32_t CellularCallConfig::SIM_ABSENT = 0;
std::map<int32_t, int32_t> CellularCallConfig::simState_;

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
    TELEPHONY_LOGI(
        "CellularCallConfig::SetLteImsSwitchStatus entry, slotId: %{public}d, active: %{public}d", slotId, active);
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
    const std::string ENHANCED_4G_MODE_ENABLED_KEY = std::to_string(slotId) + "ENHANCED_4G_MODE_ENABLED";
    bool ret = OHOS::system::SetParameter(ENHANCED_4G_MODE_ENABLED_KEY, BooleanToPropertyString(active));
    if (!ret) {
        TELEPHONY_LOGE("SetLteImsSwitchStatus  failed!");
        DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetLteImsSwitchResult(ImsErrType::IMS_FAILED);
        return TELEPHONY_ERROR;
    }

    int32_t simState = CoreManagerInner::GetInstance().GetSimState(slotId);
    TELEPHONY_LOGI("active: %{public}d simState : %{public}d", active, simState);
    if (simState == static_cast<int32_t>(SimState::SIM_STATE_LOADED)) {
        configRequest_.SetLteImsSwitchStatusRequest(slotId, active);
    }
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportSetLteImsSwitchResult(ImsErrType::IMS_SUCCESS);
    return TELEPHONY_SUCCESS;
}

std::string CellularCallConfig::BooleanToPropertyString(bool value)
{
    return value ? "1" : "0";
}

int32_t CellularCallConfig::GetLteImsSwitchStatus(int32_t slotId)
{
    TELEPHONY_LOGI("CellularCallConfig::GetLteImsSwitchStatus entry, slotId: %{public}d", slotId);
    LteImsSwitchResponse response;
    response.result = ImsErrType::IMS_SUCCESS;
    response.active = GetSwitchStatus(slotId);
    DelayedSingleton<CellularCallRegister>::GetInstance()->ReportGetLteImsSwitchResult(response);
    return TELEPHONY_SUCCESS;
}

void CellularCallConfig::HandleSimStateChanged(int32_t slotId)
{
    TELEPHONY_LOGI("CellularCallConfig::HandleSimStateChanged entry, slotId: %{public}d", slotId);
    if (IsNeedUpdateEccListWhenSimStateChanged(slotId)) {
        MergeEccCallList(slotId);
        SetEmergencyCallList(slotId);
    }
}

void CellularCallConfig::HandleSimRecordsLoaded(int32_t slotId)
{
    TELEPHONY_LOGI("CellularCallConfig::HandleSimRecordsLoaded entry");
    int32_t simState = CoreManagerInner::GetInstance().GetSimState(slotId);
    TELEPHONY_LOGI("HandleSimRecordsLoaded slotId: %{public}d, sim state is :%{public}d", slotId, simState);

    const std::string ENHANCED_4G_MODE_ENABLED_KEY = std::to_string(slotId) + "ENHANCED_4G_MODE_ENABLED";
    std::string imsSwitchValueSetting = system::GetParameter(ENHANCED_4G_MODE_ENABLED_KEY,
        IMS_SWITCH_VALUE_DISABLED);
    TELEPHONY_LOGI("imsSwitchValueSetting : %{public}s", imsSwitchValueSetting.c_str());
    if (simState == static_cast<int32_t>(SimState::SIM_STATE_READY)) {
        if (imsSwitchValueSetting == IMS_SWITCH_VALUE_ENABLED) {
            configRequest_.SetLteImsSwitchStatusRequest(slotId, true);
        } else {
            configRequest_.SetLteImsSwitchStatusRequest(slotId, false);
        }
    }
}

void CellularCallConfig::HandleSetLteImsSwitchResult(int32_t slotId, HRilErrType result)
{
    TELEPHONY_LOGI("CellularCallConfig::HandleSetLteImsSwitchResult entry, slotId: %{public}d", slotId);
    if (result != HRilErrType::NONE) {
        TELEPHONY_LOGE("HandleSetLteImsSwitchResult set ims switch to modem failed!");
        // need to reset the Ims Switch parameter and notify APP to update UI.
    }
}

void CellularCallConfig::GetDomainPreferenceModeResponse(int32_t slotId, int32_t mode)
{
    modeMap_[slotId] = mode;
}

void CellularCallConfig::GetLteImsSwitchStatusResponse(int32_t slotId, int32_t active)
{
}

int32_t CellularCallConfig::GetPreferenceMode(int32_t slotId) const
{
    return modeMap_[slotId];
}

int32_t CellularCallConfig::GetSwitchStatus(int32_t slotId) const
{
    TELEPHONY_LOGI("CellularCallConfig::GetSwitchStatus entry, slotId: %{public}d", slotId);
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
    const std::string ENHANCED_4G_MODE_ENABLED_KEY = std::to_string(slotId) + "ENHANCED_4G_MODE_ENABLED";
    std::string prevSetting = system::GetParameter(ENHANCED_4G_MODE_ENABLED_KEY, IMS_SWITCH_VALUE_DISABLED);
    int32_t imsSwitchStatus = static_cast<int32_t>(atoi(prevSetting.c_str()));
    TELEPHONY_LOGI("imsSwitchStatus : %{public}d", imsSwitchStatus);
    return imsSwitchStatus;
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
    TELEPHONY_LOGE("InitModeActive start ");
    int32_t slotId = DEFAULT_SIM_SLOT_ID;
    modeMap_[slotId] = DomainPreferenceMode::IMS_PS_VOICE_PREFERRED;
    eccListRadioMap_.clear();
    eccList3gppHasSim_.clear();
    eccList3gppNoSim_.clear();
    allEccList_.clear();
    eccList3gppHasSim_.push_back(CreateWithSimEmergencyInfo("112"));
    eccList3gppHasSim_.push_back(CreateWithSimEmergencyInfo("991"));
    eccList3gppNoSim_.push_back(CreateWithSimEmergencyInfo("112"));
    eccList3gppNoSim_.push_back(CreateWithSimEmergencyInfo("991"));
    eccList3gppNoSim_.push_back(CreateWithSimEmergencyInfo("000"));
    eccList3gppNoSim_.push_back(CreateWithSimEmergencyInfo("08"));
    eccList3gppNoSim_.push_back(CreateWithSimEmergencyInfo("110"));
    eccList3gppNoSim_.push_back(CreateWithSimEmergencyInfo("118"));
    eccList3gppNoSim_.push_back(CreateWithSimEmergencyInfo("119"));
    eccList3gppNoSim_.push_back(CreateWithSimEmergencyInfo("999"));
}

EmergencyCall CellularCallConfig::CreateWithSimEmergencyInfo(const std::string &number)
{
    EmergencyCall  emergencyCall;
    emergencyCall.eccNum = number;
    emergencyCall.eccType = EccType::TYPE_CATEGORY;
    emergencyCall.simpresent = SimpresentType::TYPE_NO_CARD;
    emergencyCall.mcc = "460";
    emergencyCall.abnormalService = AbnormalServiceType::TYPE_ALL;
    return emergencyCall;
}

void CellularCallConfig::MergeEccCallList(int32_t slotId_)
{
    std::lock_guard<std::mutex> lock(mutex_);
    TELEPHONY_LOGE("MergeEccCallList start %{public}d", slotId_);
    allEccList_[slotId_].clear();
    for (auto ecc : eccListRadioMap_[slotId_]) {
        allEccList_[slotId_].push_back(ecc);
    }
    if (CoreManagerInner::GetInstance().GetSimState(slotId_) != static_cast<int32_t>(SimState::SIM_STATE_NOT_PRESENT)) {
        std::string mcc = GetMcc(slotId_);
        TELEPHONY_LOGE("MergeEccCallList start countryCode %{public}s", mcc.c_str());
        for (auto ecc : eccList3gppHasSim_) {
            ecc.mcc = mcc;
            allEccList_[slotId_].push_back(ecc);
        }
    } else {
        for (auto ecc : eccList3gppNoSim_) {
            allEccList_[slotId_].push_back(ecc);
        }
    }
}

std::string CellularCallConfig::GetMcc(int32_t slotId_)
{
    TELEPHONY_LOGE("getMcc slotd_ %{public}d", slotId_);
    std::string imsi = Str16ToStr8(CoreManagerInner::GetInstance().GetSimOperatorNumeric(slotId_));
    int len = (int)imsi.length();
    std::string mcc = imsi;
    if (len >= MCC_LEN) {
        mcc = imsi.substr(0, MCC_LEN);
    }
    TELEPHONY_LOGE("getMcc countryCode %{public}s", mcc.c_str());
    return mcc;
}

int32_t CellularCallConfig::SetEmergencyCallList(int32_t slotId)
{
    TELEPHONY_LOGE("SetEmergencyCallList start");
    return SetEmergencyCallList(slotId, allEccList_[slotId]);
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

int32_t CellularCallConfig::SetEmergencyCallList(int32_t slotId, std::vector<EmergencyCall>  &eccVec)
{
    TELEPHONY_LOGI("SetEmergencyCallList start %{public}d", slotId);
    std::lock_guard<std::mutex> lock(mutex_);
    std::vector<EmergencyCall> uniques;
    for (auto ecc : eccVec) {
        bool hasEcc = false;
        for (auto temp : uniques) {
            if (IsEmergencyCallExit(ecc, temp)) {
                hasEcc = true;
                break;
            }
        }
        if (hasEcc) {
            TELEPHONY_LOGI("SetEmergencyCallList ecc %{public}s mcc %{public}s has repeat",
                ecc.eccNum.c_str(), ecc.mcc.c_str());
            continue;
        }
        for (auto temp : eccListRadioMap_[slotId]) {
            if (IsEmergencyCallExit(ecc, temp)) {
                hasEcc = true;
                break;
            }
        }
        if (hasEcc) {
            TELEPHONY_LOGI("SetEmergencyCallList ecc %{public}s mcc %{public}s has set in modem",
                ecc.eccNum.c_str(), ecc.mcc.c_str());
                continue;
        }
        uniques.push_back(ecc);
    }
    if (uniques.size() <= 0) {
        TELEPHONY_LOGI("SetEmergencyCallList eccList has exit");
        return TELEPHONY_ERR_SUCCESS;
    }
    TELEPHONY_LOGI("SetEmergencyCallList temp refresh size %{public}zu", uniques.size());
    for (auto ecc : uniques) {
        TELEPHONY_LOGE("SetEmergencyCallList temp refresh: eccNum %{public}s mcc %{public}s",
            ecc.eccNum.c_str(), ecc.mcc.c_str());
        allEccList_[slotId].push_back(ecc);
    }
    return configRequest_.SetEmergencyCallListRequest(slotId, uniques);
}

bool CellularCallConfig::IsEmergencyCallExit(const EmergencyCall &from, const EmergencyCall &to)
{
    return from.mcc == to.mcc && from.eccNum == to.eccNum &&  from.simpresent == to.simpresent;
}

EmergencyCall CellularCallConfig::BuildEmergencyCall(int32_t slotId, const EmergencyInfo &from)
{
    EmergencyCall to = {};
    to.eccNum = from.eccNum;
    to.eccType = EccType(from.category);
    to.simpresent = SimpresentType(from.simpresent);
    to.mcc = from.mcc;
    to.abnormalService =  AbnormalServiceType(from.abnormalService);
    return to;
}

bool CellularCallConfig::IsNeedUpdateEccListWhenSimStateChanged(int32_t slotId)
{
    int32_t simState = CoreManagerInner::GetInstance().GetSimState(slotId);
    int32_t simStateForEcc;
    switch (simState) {
        case static_cast<int32_t>(SimState::SIM_STATE_READY):
        case static_cast<int32_t>(SimState::SIM_STATE_LOADED): {
            simStateForEcc = CellularCallConfig::SIM_PRESENT;
            break;
        }
        default: {
            simStateForEcc = CellularCallConfig::SIM_ABSENT;
            break;
        }
    }
    bool result = (simState_[slotId] != simStateForEcc);
    simState_[slotId] = simStateForEcc;
    return result;
}

void CellularCallConfig::GetEmergencyCallListResponse(int32_t slotId, const EmergencyInfoList &eccList)
{
    TELEPHONY_LOGI("GetEmergencyCallListResponse %{publid}d", slotId);
    eccListRadioMap_[slotId] = std::vector<EmergencyCall>();
    for (auto ecc : eccList.calls) {
        TELEPHONY_LOGE("GetEmergencyCallListResponse , data: eccNum %{public}s mcc %{public}s",
            ecc.eccNum.c_str(), ecc.mcc.c_str());
    eccListRadioMap_[slotId] .push_back(BuildEmergencyCall(slotId, ecc));
    }
    MergeEccCallList(slotId);
}

std::vector<EmergencyCall> CellularCallConfig::GetEccCallList(int32_t slotId)
{
    TELEPHONY_LOGI("GetEccCallList  start %{publiic}d", slotId);
    std::lock_guard<std::mutex> lock(mutex_);
    TELEPHONY_LOGI("GetEccCallList  size %{publiic}zu",  allEccList_[slotId].size());
    for (auto ecc : allEccList_[slotId]) {
        TELEPHONY_LOGE("GetEccCallList, data: eccNum %{public}s mcc %{public}s",
            ecc.eccNum.c_str(), ecc.mcc.c_str());
    }
    return allEccList_[slotId];
}
} // namespace Telephony
} // namespace OHOS
