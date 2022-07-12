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

#include "ims_ril_manager.h"

#include "event_runner.h"
#include "telephony_errors.h"

namespace OHOS {
namespace Telephony {
ImsRilManager::ImsRilManager()
{
    Init();
}

ImsRilManager::~ImsRilManager()
{
}

bool ImsRilManager::Init()
{
    return true;
}

int32_t GetImsRegistrationStatus(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::Dial(const ImsCallInfo &callInfo, CLIRMode mode, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::HangUp(const ImsCallInfo &callInfo, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::Reject(const ImsCallInfo &callInfo, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::RejectWithReason(const ImsCallInfo &callInfo, const ImsRejectReason &reason,
                                        const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::Answer(const ImsCallInfo &callInfo, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::HoldCall(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::UnHoldCall(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SwitchCall(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::CombineConference(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::InviteToConference(int32_t slotId, const std::vector<std::string> &numberList,
                                          const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::KickOutFromConference(int32_t slotId, const std::vector<std::string> &numberList,
                                             const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::UpdateImsCallMode(const ImsCallInfo &callInfo, ImsCallMode mode,
                                         const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::IsEmergencyPhoneNumber(int32_t slotId, const std::string &phoneNum,
                                              const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag,
                                              const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetLastCallFailReason(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::StartDtmf(int32_t slotId, char cDtmfCode, int32_t index,
                                 const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SendDtmf(int32_t slotId, char cDtmfCode, int32_t index,
                                const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::StopDtmf(int32_t slotId, int32_t index, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::StartRtt(int32_t slotId, const std::string &msg, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::StopRtt(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetDomainPreferenceMode(int32_t slotId, int32_t mode,
                                               const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetDomainPreferenceMode(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetImsSwitchStatus(int32_t slotId, bool active, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetImsSwitchStatus(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetImsConfig(ImsConfigItem item, const std::string &value,
    const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetImsConfig(ImsConfigItem item, int32_t value, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetImsConfig(ImsConfigItem item, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetImsFeatureValue(FeatureType type,
                                          int32_t value, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetImsFeatureValue(FeatureType type, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetImsSwitchEnhanceMode(bool value, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetImsSwitchEnhanceMode(const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetMute(int32_t slotId, int32_t mute, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetMute(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetEmergencyCallList(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::CtrlCamera(const std::u16string &cameraId, int32_t callingUid, int32_t callingPid,
    const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height,
    const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height,
    const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetCameraZoom(float zoomRatio, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetPauseImage(const std::u16string &path, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetDeviceDirection(int32_t rotation, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetClip(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetClir(int32_t slotId, int32_t action, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetClir(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetCallTransfer(int32_t slotId, int32_t reason, int32_t mode,
    const std::string &transferNum, int32_t classType, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetCallTransfer(int32_t slotId, int32_t reason, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetCallRestriction(int32_t slotId, const std::string &fac, int32_t mode, const std::string &pw,
    const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetCallRestriction(int32_t slotId, const std::string &fac,
    const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::SetCallWaiting(int32_t slotId, bool activate, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::GetCallWaiting(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::ImsSendMessage(int32_t slotId, const ImsMessageInfo &imsMessageInfo,
                                      const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::ImsSetSmsConfig(int32_t slotId, int32_t imsSmsConfig,
                                       const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::ImsGetSmsConfig(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response)
{
    return TELEPHONY_SUCCESS;
}

int32_t ImsRilManager::ImsRegisterObserver(int32_t slotId, int32_t what,
                                           const std::shared_ptr<AppExecFwk::EventHandler> handler)
{
    return TELEPHONY_SUCCESS;
}
} // Telephony
} // OHOS