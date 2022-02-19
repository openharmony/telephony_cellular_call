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

#include "ims_service.h"

#include "system_ability_definition.h"

#include "core_manager_inner.h"
#include "radio_event.h"

namespace OHOS {
namespace Telephony {
bool g_registerResult = SystemAbility::MakeAndRegisterAbility(DelayedSingleton<ImsService>::GetInstance().get());

ImsService::ImsService() : SystemAbility(TELEPHONY_IMS_SYS_ABILITY_ID, true)
{
    state_ = ServiceRunningState::STATE_STOPPED;
}

ImsService::~ImsService()
{
    state_ = ServiceRunningState::STATE_STOPPED;
}

bool ImsService::Init()
{
    TELEPHONY_LOGI("ImsService Init");
    eventLoop_ = AppExecFwk::EventRunner::Create("ImsService");
    if (eventLoop_ == nullptr) {
        TELEPHONY_LOGE("failed to create EventRunner");
        return false;
    }
    CreateHandler();
    AsynchronousRegister();
    TELEPHONY_LOGI("init success");
    return true;
}

void ImsService::OnStart()
{
    TELEPHONY_LOGI("ImsService OnStart");
    if (state_ == ServiceRunningState::STATE_RUNNING) {
        TELEPHONY_LOGE("ImsService has already started.");
        return;
    }
    if (!Init()) {
        TELEPHONY_LOGE("failed to init service.");
        return;
    }
    state_ = ServiceRunningState::STATE_RUNNING;
    if (eventLoop_ != nullptr) {
        eventLoop_->Run();
    }
    bool ret = Publish(DelayedSingleton<ImsService>::GetInstance().get());
    if (!ret) {
        TELEPHONY_LOGE("ImsService::OnStart Publish failed!");
    }
    TELEPHONY_LOGI("ImsService start success.");
}

void ImsService::OnStop()
{
    TELEPHONY_LOGI("ImsService stop service");
    if (eventLoop_ != nullptr) {
        eventLoop_.reset();
    }

    state_ = ServiceRunningState::STATE_STOPPED;

    HandlerResetUnRegister();
}

void ImsService::CreateHandler()
{
    int32_t slotId = DEFAULT_SIM_SLOT_ID;
    auto handler = std::make_shared<ImsHandler>(eventLoop_);
    handlerMap_.insert(std::make_pair(slotId, handler));
    const int32_t slotDouble = 2;
    if (SIM_SLOT_COUNT == slotDouble) {
        int32_t slotId1 = SIM_SLOT_1;
        auto handler1 = std::make_shared<ImsHandler>(eventLoop_);
        handlerMap_.insert(std::make_pair(slotId1, handler1));
    }
}

void ImsService::RegisterHandler()
{
    TELEPHONY_LOGI("connect core service RegisterHandler start  ");
    for (uint32_t i = 0; i < CONNECT_MAX_TRY_COUNT; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(CONNECT_SERVICE_WAIT_TIME));
        if (CoreManagerInner::GetInstance().IsInitFinished()) {
            RegisterCoreServiceHandler();
            break;
        }
        TELEPHONY_LOGW("connect core service RegisterHandler null or not init ");
    }
    TELEPHONY_LOGI("connect core service RegisterHandler end ");
}

void ImsService::HandlerResetUnRegister()
{
    for (const auto &it : handlerMap_) {
        auto handler = it.second;
        if (handler != nullptr) {
            handler.reset();
        }
    }
}

void ImsService::RegisterCoreServiceHandler()
{
    for (const auto &it : handlerMap_) {
        auto handler = it.second;
        if (handler != nullptr) {
            TELEPHONY_LOGI("RegisterCoreServiceHandler, RegisterCoreNotify handler");
        }
    }
}

void ImsService::AsynchronousRegister()
{
    TELEPHONY_LOGI("ImsService::AsynchronousRegister entry");
    int64_t delayTime = 1000;
    int32_t slot = DEFAULT_SIM_SLOT_ID;
    auto handler = handlerMap_[slot];
    if (handler == nullptr) {
        TELEPHONY_LOGE("AsynchronousRegister return, handler is nullptr");
        return;
    }
    handler->SendEvent(handler->ASYNCHRONOUS_REGISTER_ID, delayTime, ImsHandler::Priority::HIGH);
}

std::shared_ptr<ImsHandler> ImsService::GetHandler(int32_t slot)
{
    return handlerMap_[slot];
}

int32_t ImsService::Dial(const ImsCallInfo &callInfo, CLIRMode mode)
{
    TELEPHONY_LOGI("ImsService::Dial entry");
    return request_.DialRequest(callInfo, mode);
}

int32_t ImsService::HangUp(const ImsCallInfo &callInfo)
{
    TELEPHONY_LOGI("ImsService::HangUp entry");
    return request_.HangUpRequest(callInfo.slotId, callInfo.index);
}

int32_t ImsService::Reject(const ImsCallInfo &callInfo)
{
    TELEPHONY_LOGI("ImsService::Reject entry");
    return request_.RejectRequest(callInfo.slotId);
}

int32_t ImsService::Answer(const ImsCallInfo &callInfo)
{
    TELEPHONY_LOGI("ImsService::Answer entry");
    return request_.AnswerRequest(callInfo.slotId, callInfo.videoState);
}

int32_t ImsService::HoldCall(int32_t slotId)
{
    TELEPHONY_LOGI("ImsService::HoldCall entry");
    return request_.HoldRequest(slotId);
}

int32_t ImsService::UnHoldCall(int32_t slotId)
{
    TELEPHONY_LOGI("ImsService::UnHoldCall entry");
    return request_.UnHoldCallRequest(slotId);
}

int32_t ImsService::SwitchCall(int32_t slotId)
{
    TELEPHONY_LOGI("ImsService::SwitchCall entry");
    return request_.SwitchCallRequest(slotId);
}

int32_t ImsService::CombineConference(int32_t slotId)
{
    TELEPHONY_LOGI("ImsService::CombineConference entry");
    int32_t voiceCall = 0;
    return request_.CombineConferenceRequest(slotId, voiceCall);
}

int32_t ImsService::InviteToConference(int32_t slotId, const std::vector<std::string> &numberList)
{
    TELEPHONY_LOGI("ImsService::InviteToConference entry");
    return request_.InviteToConferenceRequest(slotId, numberList);
}

int32_t ImsService::KickOutFromConference(int32_t slotId, const std::vector<std::string> &numberList)
{
    TELEPHONY_LOGI("ImsService::KickOutFromConference entry");
    return request_.KickOutFromConferenceRequest(slotId, numberList);
}

int32_t ImsService::UpdateImsCallMode(const ImsCallInfo &callInfo, ImsCallMode mode)
{
    TELEPHONY_LOGI("ImsService::UpdateImsCallMode entry");
    return request_.UpdateCallMediaModeRequest(callInfo.slotId, mode);
}

int32_t ImsService::IsEmergencyPhoneNumber(int32_t slotId, const std::string &phoneNum)
{
    TELEPHONY_LOGI("ImsService::IsEmergencyPhoneNumber entry");
    return request_.IsEmergencyPhoneNumberRequest(slotId, phoneNum);
}

int32_t ImsService::StartDtmf(int32_t slotId, char cDtmfCode, int32_t index)
{
    TELEPHONY_LOGI("ImsService::StartDtmf entry");
    return request_.StartDtmfRequest(slotId, cDtmfCode, index);
}

int32_t ImsService::SendDtmf(int32_t slotId, char cDtmfCode, int32_t index)
{
    TELEPHONY_LOGI("ImsService::SendDtmf entry");
    return request_.SendDtmfRequest(slotId, cDtmfCode, index);
}

int32_t ImsService::StopDtmf(int32_t slotId, int32_t index)
{
    TELEPHONY_LOGI("ImsService::StopDtmf entry");
    return request_.StopDtmfRequest(slotId, index);
}

int32_t ImsService::StartRtt(int32_t slotId, const std::string &msg)
{
    TELEPHONY_LOGI("ImsService::StartRtt entry");
    return request_.StartRttRequest(slotId, msg);
}

int32_t ImsService::StopRtt(int32_t slotId)
{
    TELEPHONY_LOGI("ImsService::StopRtt entry");
    return request_.StopRttRequest(slotId);
}

int32_t ImsService::SetDomainPreferenceMode(int32_t slotId, int32_t mode)
{
    TELEPHONY_LOGI("ImsService::SetDomainPreferenceMode entry");
    return request_.SetDomainPreferenceModeRequest(slotId, mode);
}

int32_t ImsService::GetDomainPreferenceMode(int32_t slotId)
{
    TELEPHONY_LOGI("ImsService::GetDomainPreferenceMode entry");
    return request_.GetDomainPreferenceModeRequest(slotId);
}

int32_t ImsService::SetLteImsSwitchStatus(int32_t slotId, bool active)
{
    TELEPHONY_LOGI("ImsService::SetLteImsSwitchStatus entry");
    return request_.SetLteImsSwitchStatusRequest(slotId, active);
}

int32_t ImsService::GetLteImsSwitchStatus(int32_t slotId)
{
    TELEPHONY_LOGI("ImsService::GetLteImsSwitchStatus entry");
    return request_.GetLteImsSwitchStatusRequest(slotId);
}

int32_t ImsService::SetImsConfig(ImsConfigItem item, const std::string &value)
{
    TELEPHONY_LOGI("ImsService::SetImsConfig string entry");
    return request_.SetImsConfigRequest(item, value);
}

int32_t ImsService::SetImsConfig(ImsConfigItem item, int32_t value)
{
    TELEPHONY_LOGI("ImsService::SetImsConfig int entry");
    return request_.SetImsConfigRequest(item, value);
}

int32_t ImsService::GetImsConfig(ImsConfigItem item)
{
    TELEPHONY_LOGI("ImsService::GetImsConfig entry");
    return request_.GetImsConfigRequest(item);
}

int32_t ImsService::SetImsFeatureValue(FeatureType type, int32_t value)
{
    TELEPHONY_LOGI("ImsService::SetImsFeatureValue entry");
    return request_.SetImsFeatureValueRequest(type, value);
}

int32_t ImsService::GetImsFeatureValue(FeatureType type)
{
    TELEPHONY_LOGI("ImsService::GetImsFeatureValue entry");
    return request_.GetImsFeatureValueRequest(type);
}

int32_t ImsService::SetImsSwitchEnhanceMode(bool value)
{
    TELEPHONY_LOGI("ImsService::SetImsSwitchEnhanceMode entry");
    return request_.SetImsSwitchEnhanceModeRequest(value);
}

int32_t ImsService::GetImsSwitchEnhanceMode()
{
    TELEPHONY_LOGI("ImsService::GetImsSwitchEnhanceMode entry");
    return request_.GetImsSwitchEnhanceModeRequest();
}

int32_t ImsService::CtrlCamera(const std::u16string &cameraId, int32_t callingUid, int32_t callingPid)
{
    TELEPHONY_LOGI("ImsService::CtrlCamera entry");
    return request_.CtrlCameraRequest(cameraId, callingUid, callingPid);
}

int32_t ImsService::SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    TELEPHONY_LOGI("ImsService::SetPreviewWindow entry");
    return request_.SetPreviewWindowRequest(x, y, z, width, height);
}

int32_t ImsService::SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    TELEPHONY_LOGI("ImsService::SetDisplayWindow entry");
    return request_.SetDisplayWindowRequest(x, y, z, width, height);
}

int32_t ImsService::SetCameraZoom(float zoomRatio)
{
    TELEPHONY_LOGI("ImsService::SetCameraZoom entry");
    return request_.SetCameraZoomRequest(zoomRatio);
}

int32_t ImsService::SetPauseImage(const std::u16string &path)
{
    TELEPHONY_LOGI("ImsService::SetPauseImage entry");
    return request_.SetPauseImageRequest(path);
}

int32_t ImsService::SetDeviceDirection(int32_t rotation)
{
    TELEPHONY_LOGI("ImsService::SetDeviceDirection entry");
    return request_.SetDeviceDirectionRequest(rotation);
}

int32_t ImsService::RegisterCellularCallBack(const sptr<ImsCallback> &callback)
{
    TELEPHONY_LOGI("ImsService::RegisterCellularCallBack entry");
    if (DelayedSingleton<ImsRegister>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("RegisterCellularCallBackInner return, error type: GetInstance() is nullptr.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    return DelayedSingleton<ImsRegister>::GetInstance()->RegisterCellularCallBack(callback);
}

bool ImsService::IsCallBackExists()
{
    TELEPHONY_LOGI("ImsService::IsCallBackExists entry");
    return DelayedSingleton<ImsRegister>::GetInstance()->IsCallBackExists();
}

int32_t ImsService::GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag)
{
    TELEPHONY_LOGI("ImsService::GetImsCallsDataRequest entry");
    return request_.GetImsCallsDataRequest(slotId, lastCallsDataFlag);
}

int32_t ImsService::SetMute(int32_t slotId, int32_t mute)
{
    TELEPHONY_LOGI("ImsService::SetMute entry");
    TELEPHONY_LOGI("ImsService::SetMute entry slotId:%{public}d mute:%{public}d", slotId, mute);
    return request_.SetMuteRequest(slotId, mute);
}

int32_t ImsService::GetMute(int32_t slotId)
{
    TELEPHONY_LOGI("ImsService::GetMute entry");
    return request_.GetMuteRequest(slotId);
}

int32_t ImsService::GetEmergencyCallList(int32_t slotId)
{
    TELEPHONY_LOGI("ImsService::GetEmergencyCallList entry");
    return request_.GetEmergencyCallListRequest(slotId);
}

int32_t ImsService::GetCallFailReason(int32_t slotId)
{
    TELEPHONY_LOGI("ImsService::GetCallFailReason entry");
    return request_.GetCallFailReasonRequest(slotId);
}

int32_t ImsService::InquireClip(int32_t slotId)
{
    TELEPHONY_LOGI("ImsService::InquireClip entry");
    return request_.InquireClipRequest(slotId);
}

int32_t ImsService::SetClir(int32_t slotId, int32_t action)
{
    TELEPHONY_LOGI("ImsService::SetClir entry");
    return request_.SetClirRequest(slotId, action);
}

int32_t ImsService::InquireClir(int32_t slotId)
{
    TELEPHONY_LOGI("ImsService::InquireClir entry");
    return request_.InquireClirRequest(slotId);
}

int32_t ImsService::SetCallTransfer(
    int32_t slotId, int32_t reason, int32_t mode, const std::string &transferNum, int32_t classType)
{
    TELEPHONY_LOGI("ImsService::SetCallTransfer entry");
    return request_.SetCallTransferRequest(slotId, reason, mode, transferNum, classType);
}

int32_t ImsService::GetCallTransfer(int32_t slotId, int32_t reason)
{
    TELEPHONY_LOGI("ImsService::GetCallTransfer entry");
    return request_.GetCallTransferRequest(slotId, reason);
}

int32_t ImsService::SetCallRestriction(int32_t slotId, const std::string &fac, int32_t mode, const std::string &pw)
{
    TELEPHONY_LOGI("ImsService::SetCallRestriction entry");
    return request_.SetCallRestrictionRequest(slotId, fac, mode, pw);
}

int32_t ImsService::GetCallRestriction(int32_t slotId, const std::string &fac)
{
    TELEPHONY_LOGI("ImsService::GetCallRestriction entry");
    return request_.GetCallRestrictionRequest(slotId, fac);
}

int32_t ImsService::SetCallWaiting(int32_t slotId, bool activate)
{
    TELEPHONY_LOGI("ImsService::SetCallWaiting entry");
    return request_.SetCallWaitingRequest(slotId, activate);
}

int32_t ImsService::GetCallWaiting(int32_t slotId)
{
    TELEPHONY_LOGI("ImsService::GetCallWaiting entry");
    return request_.GetCallWaitingRequest(slotId);
}
} // namespace Telephony
} // namespace OHOS
