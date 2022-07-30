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

#include "config_request.h"

#include "call_manager_errors.h"
#include "cellular_call_service.h"
#include "ims_call_client.h"
#include "radio_event.h"

namespace OHOS {
namespace Telephony {
int32_t ConfigRequest::SetDomainPreferenceModeRequest(int32_t slotId, int32_t mode)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetDomainPreferenceModeRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetDomainPreferenceMode(slotId, mode);
    }

    TELEPHONY_LOGI("SetDomainPreferenceModeRequest, ims vendor service does not exist.");
    auto handle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("SetDomainPreferenceModeRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().SetCallPreferenceMode(
        slotId, RadioEvent::RADIO_SET_CALL_PREFERENCE_MODE, mode, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetDomainPreferenceModeRequest(int32_t slotId)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetDomainPreferenceModeRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->GetDomainPreferenceMode(slotId);
    }

    TELEPHONY_LOGI("GetDomainPreferenceModeRequest, ims vendor service does not exist.");
    auto handle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("GetDomainPreferenceModeRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().GetCallPreferenceMode(slotId, RadioEvent::RADIO_GET_CALL_PREFERENCE_MODE, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetImsSwitchStatusRequest(int32_t slotId, bool active)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetImsSwitchStatusRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetImsSwitchStatus(slotId, active);
    }

    TELEPHONY_LOGI("SetImsSwitchStatusRequest, ims vendor service does not exist.");
    return TELEPHONY_ERROR;
}

int32_t ConfigRequest::GetImsSwitchStatusRequest(int32_t slotId)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetImsSwitchStatusRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->GetImsSwitchStatus(slotId);
    }

    TELEPHONY_LOGI("GetImsSwitchStatusRequest, ims vendor service does not exist.");
    return TELEPHONY_ERROR;
}

int32_t ConfigRequest::SetImsConfigRequest(ImsConfigItem item, const std::string &value)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetImsConfigRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetImsConfig(item, value);
    }
    TELEPHONY_LOGI("SetImsConfigRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetImsConfigRequest(ImsConfigItem item, int32_t value)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetImsConfigRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetImsConfig(item, value);
    }
    TELEPHONY_LOGI("SetImsConfigRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetImsConfigRequest(ImsConfigItem item)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetImsConfigRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->GetImsConfig(item);
    }
    TELEPHONY_LOGI("GetImsConfigRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetImsFeatureValueRequest(FeatureType type, int32_t value)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetImsFeatureValueRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetImsFeatureValue(type, value);
    }
    TELEPHONY_LOGI("SetImsFeatureValueRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetImsFeatureValueRequest(FeatureType type, int32_t &value)
{
    if (!moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGE("ims vendor service does not exist.");
        return TELEPHONY_ERROR;
    }
    TELEPHONY_LOGI("call ims service");
    if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("ImsCallClient is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    return DelayedSingleton<ImsCallClient>::GetInstance()->GetImsFeatureValue(type, value);
}

int32_t ConfigRequest::CtrlCameraRequest(const std::u16string &cameraId, int32_t callingUid, int32_t callingPid)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("CtrlCameraRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->CtrlCamera(cameraId, callingUid, callingPid);
    }
    TELEPHONY_LOGI("CtrlCameraRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetPreviewWindowRequest(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetPreviewWindowRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetPreviewWindow(x, y, z, width, height);
    }
    TELEPHONY_LOGI("SetPreviewWindowRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetDisplayWindowRequest(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetDisplayWindowRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetDisplayWindow(x, y, z, width, height);
    }
    TELEPHONY_LOGI("SetDisplayWindowRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetCameraZoomRequest(float zoomRatio)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetCameraZoomRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetCameraZoom(zoomRatio);
    }
    TELEPHONY_LOGI("SetCameraZoomRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetPauseImageRequest(const std::u16string &path)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetPauseImageRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetPauseImage(path);
    }
    TELEPHONY_LOGI("SetPauseImageRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetDeviceDirectionRequest(int32_t rotation)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetDeviceDirectionRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetDeviceDirection(rotation);
    }
    TELEPHONY_LOGI("SetDeviceDirectionRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetMuteRequest(int32_t slotId, int32_t mute)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetMuteRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->SetMute(slotId, mute);
    }

    TELEPHONY_LOGI("SetMuteRequest, ims vendor service does not exist.");
    auto handle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("SetMuteRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().SetMute(slotId, RadioEvent::RADIO_SET_CMUT, mute, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetMuteRequest(int32_t slotId)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetMuteRequest, call ims service");
        if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
            TELEPHONY_LOGE("ImsCallClient is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        return DelayedSingleton<ImsCallClient>::GetInstance()->GetMute(slotId);
    }

    TELEPHONY_LOGI("GetMuteRequest, ims vendor service does not exist.");
    auto handle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("GetMuteRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().GetMute(slotId, RadioEvent::RADIO_GET_CMUT, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetEmergencyCallListRequest(int32_t slotId)
{
    auto handle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("GetEmergencyCallListRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().GetEmergencyCallList(slotId, RadioEvent::RADIO_GET_EMERGENCY_CALL_LIST, handle);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetEmergencyCallListRequest(int32_t slotId, std::vector<EmergencyCall> &eccVec)
{
    TELEPHONY_LOGI("SetEmergencyCallListRequest start ");
    auto handle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("SetEmergencyCallListRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    int32_t errorCode = TELEPHONY_ERR_FAIL;
    errorCode = CoreManagerInner::GetInstance().SetEmergencyCallList(
        slotId, RadioEvent::RADIO_SET_EMERGENCY_CALL_LIST, eccVec, handle);
    TELEPHONY_LOGI("SetEmergencyCallListRequest end %{public}d", errorCode);
    return errorCode;
}

int32_t ConfigRequest::UpdateImsCapabilities(int32_t slotId, const ImsCapabilityList &imsCapabilityList)
{
    if (!moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGE("ims vendor service does not exist.");
        return TELEPHONY_ERROR;
    }
    TELEPHONY_LOGI("call ims service");
    if (DelayedSingleton<ImsCallClient>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("ImsCallClient is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    for (auto it : imsCapabilityList.imsCapabilities) {
        TELEPHONY_LOGI("ImsCapabilityType:%{public}d imsRadioTech:%{public}d enable:%{public}d", it.imsCapabilityType,
            it.imsRadioTech, it.enable);
    }
    return DelayedSingleton<ImsCallClient>::GetInstance()->UpdateImsCapabilities(slotId, imsCapabilityList);
}
} // namespace Telephony
} // namespace OHOS
