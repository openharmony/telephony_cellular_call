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

#ifndef CELLULAR_CALL_CONFIG_H
#define CELLULAR_CALL_CONFIG_H

#include "config_request.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
class CellularCallConfig {
public:
    /**
     * Set Domain Preference Mode
     *
     * 3GPP TS 27.007 V17.3.0 (2021-09) 10.1.35	UE's voice domain preference E-UTRAN +CEVDP
     * 3GPP TS 24.167 V17.1.0 (2020-12) 5.27 /<X>/Voice_Domain_Preference_E_UTRAN
     *
     * @param mode
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetDomainPreferenceMode(int32_t slotId, int32_t mode);

    /**
     * Get Domain Preference Mode
     *
     * 3GPP TS 27.007 V17.3.0 (2021-09) 10.1.35	UE's voice domain preference E-UTRAN +CEVDP
     * 3GPP TS 24.167 V17.1.0 (2020-12) 5.27 /<X>/Voice_Domain_Preference_E_UTRAN
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetDomainPreferenceMode(int32_t slotId);

    /**
     * Set Lte Ims Switch Status
     *
     * 3GPP TS 24.167 V17.1.0 (2020-12) 5.31 /<X>/Mobility_Management_IMS_Voice_Termination
     *
     * @param slotId
     * @param active
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetLteImsSwitchStatus(int32_t slotId, bool active);

    /**
     * Get Lte Ims Switch Status
     *
     * 3GPP TS 24.167 V17.1.0 (2020-12) 5.31 /<X>/Mobility_Management_IMS_Voice_Termination
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetLteImsSwitchStatus(int32_t slotId);

    /**
     * Get Lte Ims Switch Status Response
     *
     * @param slotId
     * @param mode
     */
    void GetCallPreferenceModeResponse(int32_t slotId, const std::shared_ptr<int32_t> &mode);

    /**
     * Get Lte Ims Switch Status Response
     *
     * @param slotId
     * @param active
     */
    void GetLteImsSwitchStatusResponse(int32_t slotId, const std::shared_ptr<int32_t> &active);

    /**
     * Get Preference Mode
     *
     * @param slotId
     * @return mode
     */
    int32_t GetPreferenceMode(int32_t slotId) const;

    /**
     * Get Switch Status
     *
     * @param slotId
     * @return active
     */
    int32_t GetSwitchStatus(int32_t slotId) const;

    /**
     * Set Ims Config
     *
     * @param ImsConfigItem
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsConfig(ImsConfigItem item, const std::string &value);

    /**
     * Set Ims Config
     *
     * @param ImsConfigItem
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsConfig(ImsConfigItem item, int32_t value);

    /**
     * Get Ims Config
     *
     * @param ImsConfigItem
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsConfig(ImsConfigItem item);

    /**
     * Set Ims Feature Value
     *
     * @param FeatureType
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsFeatureValue(FeatureType type, int32_t value);

    /**
     * Get Ims Feature Value
     *
     * @param FeatureType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsFeatureValue(FeatureType type);

    /**
     * Set Ims Switch Enhance Mode
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsSwitchEnhanceMode(bool value);

    /**
     * Get Ims Switch Enhance Mode
     *
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsSwitchEnhanceMode();

    /**
     * CtrlCamera
     *
     * @param cameraId
     * @param callingUid
     * @param callingPid
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t CtrlCamera(const std::u16string &cameraId, int32_t callingUid, int32_t callingPid);

    /**
     * SetPreviewWindow
     *
     * @param x
     * @param y
     * @param z
     * @param width
     * @param height
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height);

    /**
     * SetDisplayWindow
     *
     * @param x
     * @param y
     * @param z
     * @param width
     * @param height
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height);

    /**
     * SetCameraZoom
     *
     * @param zoomRatio
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCameraZoom(float zoomRatio);

    /**
     * SetPauseImage
     *
     * @param path
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetPauseImage(const std::u16string &path);

    /**
     * SetDeviceDirection
     *
     * @param rotation
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetDeviceDirection(int32_t rotation);

    /**
     * SetMute
     *
     * @param slotId
     * @param mute
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetMute(int32_t slotId, int32_t mute);

    /**
     * GetMute
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetMute(int32_t slotId);

    /**
     * GetEmergencyCallList
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetEmergencyCallList(int32_t slotId);

    /**
     * SetTempMode
     *
     * @param slotId
     */
    void SetTempMode(int32_t slotId);

    /**
     * Init mode and active
     */
    void InitModeActive();

    /**
     * Get Emergency Call List Response
     *
     * @param slotId
     * @param EmergencyInfoList
     */
    void GetEmergencyCallListResponse(int32_t slotId, const EmergencyInfoList &eccList);

    /**
     * Get Ecc Call List
     *
     * @param slotId
     * @return std::vector<EmergencyInfo>
     */
    std::vector<EmergencyInfo> GetEccCallList(int32_t slotId);

private:
    static std::map<int32_t, int32_t> modeTempMap_;
    static std::map<int32_t, int32_t> modeMap_;
    static std::map<int32_t, int32_t> activeMap_;
    static std::map<int32_t, std::vector<EmergencyInfo>> eccListMap_;
    ConfigRequest configRequest_;
};
} // namespace Telephony
} // namespace OHOS
#endif // CELLULAR_CALL_CONFIG_H
