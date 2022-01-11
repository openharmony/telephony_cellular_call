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

#include "config_request.h"

#include "call_manager_errors.h"
#include "cellular_call_service.h"
#include "observer_handler.h"

namespace OHOS {
namespace Telephony {
int32_t ConfigRequest::SetDomainPreferenceModeRequest(int32_t mode)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetDomainPreferenceModeRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetDomainPreferenceMode(mode);
    }

    TELEPHONY_LOGI("SetDomainPreferenceModeRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetDomainPreferenceModeRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_CALL_PREFERENCE_MODE);
    if (event == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetDomainPreferenceModeRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId_));
    core->SetCallPreferenceMode(mode, event);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetDomainPreferenceModeRequest()
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetDomainPreferenceModeRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetDomainPreferenceMode();
    }

    TELEPHONY_LOGI("GetDomainPreferenceModeRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::GetDomainPreferenceModeRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_CALL_PREFERENCE_MODE);
    if (event == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::GetDomainPreferenceModeRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId_));
    core->GetCallPreferenceMode(event);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetLteImsSwitchStatusRequest(bool active)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetLteImsSwitchStatusRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetLteImsSwitchStatus(active);
    }

    TELEPHONY_LOGI("SetLteImsSwitchStatusRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetLteImsSwitchStatusRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_LTE_IMS_SWITCH_STATUS);
    if (event == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetLteImsSwitchStatusRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId_));
    core->SetLteImsSwitchStatus(active, event);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetLteImsSwitchStatusRequest()
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetLteImsSwitchStatusRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetLteImsSwitchStatus();
    }

    TELEPHONY_LOGI("GetLteImsSwitchStatusRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::GetLteImsSwitchStatusRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_LTE_IMS_SWITCH_STATUS);
    if (event == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::GetLteImsSwitchStatusRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId_));
    core->GetLteImsSwitchStatus(event);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetImsConfigRequest(ImsConfigItem item, const std::string &value)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetImsConfigRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetImsConfig(item, value);
    }
    TELEPHONY_LOGI("SetImsConfigRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetImsConfigRequest(ImsConfigItem item, int32_t value)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetImsConfigRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetImsConfig(item, value);
    }
    TELEPHONY_LOGI("SetImsConfigRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetImsConfigRequest(ImsConfigItem item)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetImsConfigRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetImsConfig(item);
    }
    TELEPHONY_LOGI("GetImsConfigRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetImsFeatureValueRequest(FeatureType type, int32_t value)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetImsFeatureValueRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetImsFeatureValue(type, value);
    }
    TELEPHONY_LOGI("SetImsFeatureValueRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetImsFeatureValueRequest(FeatureType type)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetImsFeatureValueRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetImsFeatureValue(type);
    }
    TELEPHONY_LOGI("GetImsFeatureValueRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetVolteEnhanceModeRequest(bool value)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetVolteEnhanceModeRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetVolteEnhanceMode(value);
    }
    TELEPHONY_LOGI("SetVolteEnhanceModeRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetVolteEnhanceModeRequest()
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetVolteEnhanceModeRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetVolteEnhanceMode();
    }
    TELEPHONY_LOGI("GetVolteEnhanceModeRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::CtrlCameraRequest(
    const std::u16string &cameraId, const std::u16string &callingPackage, int32_t callingUid, int32_t callingPid)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("CtrlCameraRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->CtrlCamera(cameraId, callingPackage, callingUid, callingPid);
    }
    TELEPHONY_LOGI("CtrlCameraRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetPreviewWindowRequest(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetPreviewWindowRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetPreviewWindow(x, y, z, width, height);
    }
    TELEPHONY_LOGI("SetPreviewWindowRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetDisplayWindowRequest(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetDisplayWindowRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetDisplayWindow(x, y, z, width, height);
    }
    TELEPHONY_LOGI("SetDisplayWindowRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetCameraZoomRequest(float zoomRatio)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetCameraZoomRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetCameraZoom(zoomRatio);
    }
    TELEPHONY_LOGI("SetCameraZoomRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetPauseImageRequest(const std::u16string &path)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetPauseImageRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetPauseImage(path);
    }
    TELEPHONY_LOGI("SetPauseImageRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetDeviceDirectionRequest(int32_t rotation)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetDeviceDirectionRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetDeviceDirection(rotation);
    }
    TELEPHONY_LOGI("SetDeviceDirectionRequest, ims vendor service does not exist.");
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::SetMuteRequest(int32_t slotId, int32_t mute)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("SetMuteRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->SetMute(slotId, mute);
    }

    TELEPHONY_LOGI("SetMuteRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetMuteRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_SET_CMUT);
    if (event == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::SetMuteRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId_));
    core->SetMute(mute, event);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetMuteRequest(int32_t slotId)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetMuteRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetMute(slotId);
    }

    TELEPHONY_LOGI("GetMuteRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::GetMuteRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_CMUT);
    if (event == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::GetMuteRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId_));
    core->GetMute(event);
    return TELEPHONY_SUCCESS;
}

int32_t ConfigRequest::GetEmergencyCallListRequest(int32_t slotId)
{
    if (moduleUtils_.NeedCallImsService()) {
        TELEPHONY_LOGI("GetEmergencyCallListRequest, call ims service");
        return moduleUtils_.GetImsServiceRemoteObject()->GetEmergencyCallList(slotId);
    }

    TELEPHONY_LOGI("GetEmergencyCallListRequest, ims vendor service does not exist.");
    auto core = GetCore(slotId_);
    if (core == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::GetEmergencyCallListRequest return, error type: core is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto event = AppExecFwk::InnerEvent::Get(ObserverHandler::RADIO_GET_EMERGENCY_CALL_LIST);
    if (event == nullptr) {
        TELEPHONY_LOGE("ConfigRequest::GetEmergencyCallListRequest return, error type: event is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    event->SetOwner(DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId_));
    core->GetEmergencyCallList(event);
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS