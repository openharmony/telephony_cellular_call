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
#include "ims_call.h"
#include "ims_radio_event.h"
#include "ims_ril_manager.h"

namespace OHOS {
namespace Telephony {
ImsCall::ImsCall()
{
}

ImsCall::~ImsCall()
{
}

bool ImsCall::Init()
{
    TELEPHONY_LOGI("ImsCall Init");
    SetSlotIds();

    if (!CreateEventLoop("ImsCallLoop")) {
        TELEPHONY_LOGE("ImsCall::CreateEventLoop failed");
        return false;
    }
    if (!CreateHandler()) {
        TELEPHONY_LOGE("ImsCall::CreateHandler failed");
        return false;
    }
    if (!RegisterObserver()) {
        TELEPHONY_LOGE("ImsCall::RegisterHandler failed");
        return false;
    }

    TELEPHONY_LOGI("ImsCall:Init success");
    return true;
}

void ImsCall::SetSlotIds()
{
    slotIds_.emplace_back(DEFAULT_SIM_SLOT_ID);
}

int32_t ImsCall::Dial(const ImsCallInfo &callInfo, CLIRMode mode)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_DIAL);
    auto handler = GetHandler(callInfo.slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", callInfo.slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->Dial(callInfo, mode, response);
}

int32_t ImsCall::HangUp(const ImsCallInfo &callInfo)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_HANGUP);
    auto handler = GetHandler(callInfo.slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", callInfo.slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->HangUp(callInfo, response);
}

int32_t ImsCall::Reject(const ImsCallInfo &callInfo)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_REJECT);
    auto handler = GetHandler(callInfo.slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", callInfo.slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->Reject(callInfo, response);
}

int32_t ImsCall::RejectWithReason(const ImsCallInfo &callInfo, const ImsRejectReason &reason)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_REJECT_WITH_REASON);
    auto handler = GetHandler(callInfo.slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", callInfo.slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->RejectWithReason(callInfo, reason, response);
}

int32_t ImsCall::Answer(const ImsCallInfo &callInfo)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_ANSWER);
    auto handler = GetHandler(callInfo.slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", callInfo.slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->Answer(callInfo, response);
}

int32_t ImsCall::HoldCall(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_HOLD);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->HoldCall(slotId, response);
}

int32_t ImsCall::UnHoldCall(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_UN_HOLD);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->UnHoldCall(slotId, response);
}

int32_t ImsCall::SwitchCall(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SWITCH);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SwitchCall(slotId, response);
}

int32_t ImsCall::CombineConference(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_COMBINE_CONFERENCE);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->CombineConference(slotId, response);
}

int32_t ImsCall::InviteToConference(int32_t slotId, const std::vector<std::string> &numberList)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_INVITE_TO_CONFERENCE);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->InviteToConference(slotId, numberList, response);
}

int32_t ImsCall::KickOutFromConference(int32_t slotId, const std::vector<std::string> &numberList)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_KICK_OUT_CONFERENCE);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->KickOutFromConference(slotId, numberList, response);
}

int32_t ImsCall::UpdateImsCallMode(const ImsCallInfo &callInfo, ImsCallMode mode)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_UPDATE_CALL_MEDIA_MODE);
    auto handler = GetHandler(callInfo.slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", callInfo.slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->UpdateImsCallMode(callInfo, mode, response);
}

int32_t ImsCall::IsEmergencyPhoneNumber(int32_t slotId, const std::string &phoneNum)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_IS_EMERGENCY_NUMBER);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->IsEmergencyPhoneNumber(slotId, phoneNum, response);
}

int32_t ImsCall::GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_CALL_DATA);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetImsCallsDataRequest(slotId, lastCallsDataFlag, response);
}

int32_t ImsCall::GetLastCallFailReason(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_GET_LAST_CALL_FAIL_REASON);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetLastCallFailReason(slotId, response);
}

int32_t ImsCall::StartDtmf(int32_t slotId, char cDtmfCode, int32_t index)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_START_DTMF);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->StartDtmf(slotId, cDtmfCode, index, response);
}

int32_t ImsCall::SendDtmf(int32_t slotId, char cDtmfCode, int32_t index)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SEND_DTMF);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SendDtmf(slotId, cDtmfCode, index, response);
}

int32_t ImsCall::StopDtmf(int32_t slotId, int32_t index)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_STOP_DTMF);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->StopDtmf(slotId, index, response);
}

int32_t ImsCall::StartRtt(int32_t slotId, const std::string &msg)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_START_RTT);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->StartRtt(slotId, msg, response);
}

int32_t ImsCall::StopRtt(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_STOP_RTT);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->StopRtt(slotId, response);
}

int32_t ImsCall::SetDomainPreferenceMode(int32_t slotId, int32_t mode)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_DOMAIN_PREFERENCE_MODE);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetDomainPreferenceMode(slotId, mode, response);
}

int32_t ImsCall::GetDomainPreferenceMode(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_DOMAIN_PREFERENCE_MODE);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetDomainPreferenceMode(slotId, response);
}

int32_t ImsCall::SetLteImsSwitchStatus(int32_t slotId, int32_t active)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_LTE_SWITCH_STATUS);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetLteImsSwitchStatus(slotId, active, response);
}

int32_t ImsCall::GetLteImsSwitchStatus(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_LTE_SWITCH_STATUS);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetLteImsSwitchStatus(slotId, response);
}

int32_t ImsCall::SetImsConfig(ImsConfigItem item, const std::string &value)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_CONFIG);
    auto handler = GetHandler(DEFAULT_SIM_SLOT_ID);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", DEFAULT_SIM_SLOT_ID);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetImsConfig(item, value, response);
}

int32_t ImsCall::SetImsConfig(ImsConfigItem item, int32_t value)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_CONFIG);
    auto handler = GetHandler(DEFAULT_SIM_SLOT_ID);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", DEFAULT_SIM_SLOT_ID);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetImsConfig(item, value, response);
}

int32_t ImsCall::GetImsConfig(ImsConfigItem item)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_CONFIG);
    auto handler = GetHandler(DEFAULT_SIM_SLOT_ID);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", DEFAULT_SIM_SLOT_ID);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetImsConfig(item, response);
}

int32_t ImsCall::SetImsFeatureValue(FeatureType type, int32_t value)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_FEATURE);
    auto handler = GetHandler(DEFAULT_SIM_SLOT_ID);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", DEFAULT_SIM_SLOT_ID);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetImsFeatureValue(type, value, response);
}

int32_t ImsCall::GetImsFeatureValue(FeatureType type)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_FEATURE);
    auto handler = GetHandler(DEFAULT_SIM_SLOT_ID);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", DEFAULT_SIM_SLOT_ID);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetImsFeatureValue(type, response);
}

int32_t ImsCall::SetImsSwitchEnhanceMode(bool value)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_SWITCH_ENHANCE_MODE);
    auto handler = GetHandler(DEFAULT_SIM_SLOT_ID);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", DEFAULT_SIM_SLOT_ID);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetImsSwitchEnhanceMode(value, response);
}

int32_t ImsCall::GetImsSwitchEnhanceMode()
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_SWITCH_ENHANCE_MODE);
    auto handler = GetHandler(DEFAULT_SIM_SLOT_ID);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", DEFAULT_SIM_SLOT_ID);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetImsSwitchEnhanceMode(response);
}

int32_t ImsCall::SetMute(int32_t slotId, int32_t mute)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_MUTE);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetMute(slotId, mute, response);
}

int32_t ImsCall::GetMute(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_MUTE);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetMute(slotId, response);
}

int32_t ImsCall::GetEmergencyCallList(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_ECC_CALL_LIST);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetEmergencyCallList(slotId, response);
}

int32_t ImsCall::CtrlCamera(const std::u16string &cameraId, int32_t callingUid, int32_t callingPid)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_CTRL_CAMERA);
    auto handler = GetHandler(DEFAULT_SIM_SLOT_ID);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", DEFAULT_SIM_SLOT_ID);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->CtrlCamera(cameraId, callingUid, callingPid, response);
}

int32_t ImsCall::SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_PREVIEW_WINDOW);
    auto handler = GetHandler(DEFAULT_SIM_SLOT_ID);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", DEFAULT_SIM_SLOT_ID);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetPreviewWindow(x, y, z, width, height, response);
}

int32_t ImsCall::SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_DISPLAY_WINDOW);
    auto handler = GetHandler(DEFAULT_SIM_SLOT_ID);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", DEFAULT_SIM_SLOT_ID);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetDisplayWindow(x, y, z, width, height, response);
}

int32_t ImsCall::SetCameraZoom(float zoomRatio)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_CAMERA_ZOOM);
    auto handler = GetHandler(DEFAULT_SIM_SLOT_ID);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", DEFAULT_SIM_SLOT_ID);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetCameraZoom(zoomRatio, response);
}

int32_t ImsCall::SetPauseImage(const std::u16string &path)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_PAUSE_IMAGE);
    auto handler = GetHandler(DEFAULT_SIM_SLOT_ID);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", DEFAULT_SIM_SLOT_ID);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetPauseImage(path, response);
}

int32_t ImsCall::SetDeviceDirection(int32_t rotation)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_DEVICE_DIRECTION);
    auto handler = GetHandler(DEFAULT_SIM_SLOT_ID);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", DEFAULT_SIM_SLOT_ID);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetDeviceDirection(rotation, response);
}

int32_t ImsCall::GetClip(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_CLIP);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetClip(slotId, response);
}

int32_t ImsCall::SetClir(int32_t slotId, int32_t action)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_CLIR);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetClir(slotId, action, response);
}

int32_t ImsCall::GetClir(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_CLIR);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetClir(slotId, response);
}


int32_t ImsCall::SetCallTransfer(
    int32_t slotId, int32_t reason, int32_t mode, const std::string &transferNum, int32_t classType)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_CALL_TRANSFER);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetCallTransfer(slotId, reason, mode, transferNum, classType, response);
}

int32_t ImsCall::GetCallTransfer(int32_t slotId, int32_t reason)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_CALL_TRANSFER);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetCallTransfer(slotId, reason, response);
}

int32_t ImsCall::SetCallRestriction(
    int32_t slotId, const std::string &fac, int32_t mode, const std::string &pw)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_CALL_RESTRICTION);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetCallRestriction(slotId, fac, mode, pw, response);
}

int32_t ImsCall::GetCallRestriction(int32_t slotId, const std::string &fac)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_CALL_RESTRICTION);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetCallRestriction(slotId, fac, response);
}

int32_t ImsCall::SetCallWaiting(int32_t slotId, bool activate)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_SET_CALL_WAITING);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->SetCallWaiting(slotId, activate, response);
}

int32_t ImsCall::GetCallWaiting(int32_t slotId)
{
    AppExecFwk::InnerEvent::Pointer response =
        AppExecFwk::InnerEvent::Get(ImsRadioEvent::IMS_RADIO_GET_CALL_WAITING);
    auto handler = GetHandler(slotId);
    if (handler == nullptr) {
        TELEPHONY_LOGE("Get handler failed, slotid = %{public}d", slotId);
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    response->SetOwner(handler);

    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }

    return imsRilManager->GetCallWaiting(slotId, response);
}

int32_t ImsCall::RegisterImsCallCallback(const sptr<ImsCallCallbackInterface> &callback)
{
    auto imsCallRegister = DelayedSingleton<ImsCallRegister>::GetInstance();
    if (imsCallRegister == nullptr) {
        TELEPHONY_LOGE("ImsCallRegister is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    if (imsCallRegister->RegisterImsCallCallBack(callback) != TELEPHONY_SUCCESS) {
        TELEPHONY_LOGE("Register IMS call callback faled");
        return TELEPHONY_ERR_FAIL;
    }
    TELEPHONY_LOGI("Register IMS call callback");
    return TELEPHONY_SUCCESS;
}

bool ImsCall::RegisterObserver()
{
    auto imsRilManager = DelayedSingleton<ImsRilManager>::GetInstance();
    if (imsRilManager == nullptr) {
        TELEPHONY_LOGE("ImsRilManager nullptr");
        return false;
    }
    for (auto &entry : handlerMap_) {
        auto &handler = entry.second;
        imsRilManager->ImsRegisterObserver(handler->GetSlotId(), ImsRadioEvent::IMS_RAIDO_SERVICE_STATUS, handler);
        imsRilManager->ImsRegisterObserver(handler->GetSlotId(), ImsRadioEvent::IMS_SRVCC_STATUS, handler);
        imsRilManager->ImsRegisterObserver(handler->GetSlotId(), ImsRadioEvent::IMS_RADIO_VT_WFC, handler);
    }

    return true;
}
} // Telephony
} // OHOS
