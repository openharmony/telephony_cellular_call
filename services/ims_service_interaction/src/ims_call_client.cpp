/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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

#include "ims_call_client.h"

#include "iservice_registry.h"
#include "ims_call_callback_stub.h"
#include "telephony_log_wrapper.h"
#include "telephony_errors.h"

namespace OHOS {
namespace Telephony {
ImsCallClient::ImsCallClient() = default;

ImsCallClient::~ImsCallClient()
{
    if (imsCallProxy_ != nullptr) {
        imsCallProxy_.clear();
        imsCallProxy_ = nullptr;
    }
}

void ImsCallClient::Init()
{
    if (!IsConnect()) {
        GetImsCallProxy();
    }
    // register callback
    RegisterImsCallCallback();
}

sptr<ImsCallInterface> ImsCallClient::GetImsCallProxy()
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_;
    }
    auto managerPtr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (managerPtr == nullptr) {
        TELEPHONY_LOGE("GetImsCallProxy return, get system ability manager error.");
        return nullptr;
    }
    auto remoteObjectPtr = managerPtr->CheckSystemAbility(TELEPHONY_IMS_SYS_ABILITY_ID);
    if (remoteObjectPtr == nullptr) {
        TELEPHONY_LOGE("GetImsCallProxy return, remote service not exists.");
        return nullptr;
    }
    imsCoreServiceProxy_ = iface_cast<ImsCoreServiceInterface>(remoteObjectPtr);
    if (imsCoreServiceProxy_ == nullptr) {
        TELEPHONY_LOGE("GetImsCallProxy return, imsCoreServiceProxy_ is nullptr.");
        return nullptr;
    }
    sptr<IRemoteObject> imsCallRemoteObjectPtr = imsCoreServiceProxy_->GetProxyObjectPtr(PROXY_IMS_CALL);
    if (imsCallRemoteObjectPtr == nullptr) {
        TELEPHONY_LOGE("GetImsCallProxy return, ImsCallRemoteObjectPtr is nullptr.");
        return nullptr;
    }
    imsCallProxy_ = iface_cast<ImsCallInterface>(imsCallRemoteObjectPtr);
    if (imsCallProxy_ == nullptr) {
        TELEPHONY_LOGE("GetImsCallProxy return, iface_cast<imsCallProxy_> failed!");
        return nullptr;
    }
    TELEPHONY_LOGI("GetImsCallProxy success.");
    return imsCallProxy_;
}

bool ImsCallClient::IsConnect() const
{
    return (imsCallProxy_ != nullptr);
}

int32_t ImsCallClient::RegisterImsCallCallback()
{
    if (imsCallProxy_ == nullptr) {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    imsCallCallback_ = (std::make_unique<ImsCallCallbackStub>()).release();
    if (imsCallCallback_ == nullptr) {
        TELEPHONY_LOGE("RegisterImsCallCallback return, make unique error.");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t ret = imsCallProxy_->RegisterImsCallCallback(imsCallCallback_);
    if (ret) {
        TELEPHONY_LOGE("RegisterImsCallCallback return, register callback error.");
        return TELEPHONY_ERR_FAIL;
    }
    TELEPHONY_LOGI("RegisterImsCallCallback success.");
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallClient::Dial(const ImsCallInfo &callInfo, CLIRMode mode)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->Dial(callInfo, mode);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::HangUp(const ImsCallInfo &callInfo)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->HangUp(callInfo);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::Reject(const ImsCallInfo &callInfo)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->Reject(callInfo);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::Answer(const ImsCallInfo &callInfo)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->Answer(callInfo);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::HoldCall(int32_t slotId)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->HoldCall(slotId);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::UnHoldCall(int32_t slotId)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->UnHoldCall(slotId);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}
int32_t ImsCallClient::SwitchCall(int32_t slotId)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SwitchCall(slotId);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::CombineConference(int32_t slotId)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->CombineConference(slotId);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}
int32_t ImsCallClient::InviteToConference(int32_t slotId, const std::vector<std::string> &numberList)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->InviteToConference(slotId, numberList);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::KickOutFromConference(int32_t slotId, const std::vector<std::string> &numberList)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->KickOutFromConference(slotId, numberList);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::UpdateImsCallMode(const ImsCallInfo &callInfo, ImsCallMode mode)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->UpdateImsCallMode(callInfo, mode);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::IsEmergencyPhoneNumber(int32_t slotId, const std::string &phoneNum)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->IsEmergencyPhoneNumber(slotId, phoneNum);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetImsCallsDataRequest(slotId, lastCallsDataFlag);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetCallFailReason(int32_t slotId)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetCallFailReason(slotId);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::StartDtmf(int32_t slotId, char cDtmfCode, int32_t index)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->StartDtmf(slotId, cDtmfCode, index);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SendDtmf(int32_t slotId, char cDtmfCode, int32_t index)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SendDtmf(slotId, cDtmfCode, index);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::StopDtmf(int32_t slotId, int32_t index)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->StopDtmf(slotId, index);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::StartRtt(int32_t slotId, const std::string &msg)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->StartRtt(slotId, msg);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::StopRtt(int32_t slotId)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->StopRtt(slotId);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetDomainPreferenceMode(int32_t slotId, int32_t mode)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetDomainPreferenceMode(slotId, mode);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetDomainPreferenceMode(int32_t slotId)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetDomainPreferenceMode(slotId);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetLteImsSwitchStatus(int32_t slotId, bool active)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetLteImsSwitchStatus(slotId, active);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetLteImsSwitchStatus(int32_t slotId)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetLteImsSwitchStatus(slotId);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetImsConfig(ImsConfigItem item, const std::string &value)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetImsConfig(item, value);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetImsConfig(ImsConfigItem item, int32_t value)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetImsConfig(item, value);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetImsConfig(ImsConfigItem item)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetImsConfig(item);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetImsFeatureValue(FeatureType type, int32_t value)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetImsFeatureValue(type, value);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetImsFeatureValue(FeatureType type)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetImsFeatureValue(type);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetImsSwitchEnhanceMode(bool value)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetImsSwitchEnhanceMode(value);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetImsSwitchEnhanceMode()
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetImsSwitchEnhanceMode();
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetMute(int32_t slotId, int32_t mute)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetMute(slotId, mute);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetMute(int32_t slotId)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetMute(slotId);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetEmergencyCallList(int32_t slotId)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetEmergencyCallList(slotId);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::CtrlCamera(const std::u16string &cameraId, int32_t callingUid, int32_t callingPid)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->CtrlCamera(cameraId, callingUid, callingPid);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetPreviewWindow(x, y, z, width, height);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetDisplayWindow(x, y, z, width, height);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetCameraZoom(float zoomRatio)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetCameraZoom(zoomRatio);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetPauseImage(const std::u16string &path)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetPauseImage(path);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetDeviceDirection(int32_t rotation)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetDeviceDirection(rotation);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetClip(int32_t slotId)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetClip(slotId);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetClir(int32_t slotId, int32_t action)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetClir(slotId, action);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetClir(int32_t slotId)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetClir(slotId);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetCallTransfer(
    int32_t slotId, int32_t reason, int32_t mode, const std::string &transferNum, int32_t classType)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetCallTransfer(slotId, reason, mode, transferNum, classType);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetCallTransfer(int32_t slotId, int32_t reason)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetCallTransfer(slotId, reason);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetCallRestriction(int32_t slotId, const std::string &fac, int32_t mode, const std::string &pw)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetCallRestriction(slotId, fac, mode, pw);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetCallRestriction(int32_t slotId, const std::string &fac)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetCallRestriction(slotId, fac);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::SetCallWaiting(int32_t slotId, bool activate)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->SetCallWaiting(slotId, activate);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}

int32_t ImsCallClient::GetCallWaiting(int32_t slotId)
{
    if (imsCallProxy_ != nullptr) {
        return imsCallProxy_->GetCallWaiting(slotId);
    } else {
        TELEPHONY_LOGE("imsCallProxy_ is null!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
}
} // namespace Telephony
} // namespace OHOS
