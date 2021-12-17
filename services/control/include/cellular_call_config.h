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
     * Set Call Preference Mode
     *
     * 3GPP TS 27.007 V17.3.0 (2021-09) 10.1.35	UE's voice domain preference E-UTRAN +CEVDP
     * 3GPP TS 24.167 V17.1.0 (2020-12) 5.27 /<X>/Voice_Domain_Preference_E_UTRAN
     *
     * @param mode
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetCallPreferenceMode(int32_t mode);

    /**
     * Get Call Preference Mode
     *
     * 3GPP TS 27.007 V17.3.0 (2021-09) 10.1.35	UE's voice domain preference E-UTRAN +CEVDP
     * 3GPP TS 24.167 V17.1.0 (2020-12) 5.27 /<X>/Voice_Domain_Preference_E_UTRAN
     *
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t GetCallPreferenceMode();

    /**
     * Set Lte Ims Switch Status
     * @param active
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetLteImsSwitchStatus(bool active);

    /**
     * Get Lte Ims Switch Status
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t GetLteImsSwitchStatus();

    /**
     * Get Lte Ims Switch Status Response
     * @param mode.
     */
    void GetCallPreferenceModeResponse(const std::shared_ptr<int32_t> &mode);

    /**
     * Get Lte Ims Switch Status Response
     * @param active.
     */
    void GetLteImsSwitchStatusResponse(const std::shared_ptr<int32_t> &active);

    /**
     * Get Preference Mode
     * @return mode.
     */
    int32_t GetPreferenceMode() const;

    /**
     * Get  Switch Status
     * @return active.
     */
    int32_t GetSwitchStatus() const;

    /**
     * CtrlCamera
     *
     * @param cameraId
     * @param callingPackage
     * @param callingUid
     * @param callingPid
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t CtrlCamera(
        const std::u16string &cameraId, const std::u16string &callingPackage, int32_t callingUid, int32_t callingPid);

    /**
     * SetPreviewWindow
     *
     * @param x
     * @param y
     * @param z
     * @param width
     * @param height
     * @return Returns kTelephonyNoErr on success, others on failure.
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
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height);

    /**
     * SetCameraZoom
     *
     * @param zoomRatio
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetCameraZoom(float zoomRatio);

    /**
     * SetPauseImage
     *
     * @param path
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetPauseImage(const std::u16string &path);

    /**
     * SetDeviceDirection
     *
     * @param rotation
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetDeviceDirection(int32_t rotation);

    /**
     * SetTempMode
     *
     */
    void SetTempMode();

private:
    static int32_t modeTemp_;
    static int32_t mode_;
    static int32_t active_;
    ConfigRequest configRequest_;
    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "CellularCallConfig"};
};
} // namespace Telephony
} // namespace OHOS
#endif // CELLULAR_CALL_CONFIG_H
