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

#include "control_base.h"

#include "cellular_call_config.h"
#include "cellular_call_hisysevent.h"
#include "cellular_call_service.h"
#include "core_service_client.h"
#include "core_manager_inner.h"
#include "emergency_utils.h"
#include "module_service_utils.h"
#include "standardize_utils.h"
#include "telephony_ext_wrapper.h"

namespace OHOS {
namespace Telephony {
const uint32_t WAIT_TIME_SECOND = 5;

int32_t ControlBase::DialPreJudgment(const CellularCallInfo &callInfo, bool isEcc)
{
    bool isRadioOn = false;
    HandleEcc(callInfo, isEcc, CheckAirplaneModeScene(callInfo), CheckActivateSimScene(callInfo.slotId));
    std::string dialString(callInfo.phoneNum);
    if (dialString.empty()) {
        TELEPHONY_LOGE("DialPreJudgment return, dialString is empty.");
        CellularCallHiSysEvent::WriteDialCallFaultEvent(callInfo.accountId, static_cast<int32_t>(callInfo.callType),
            callInfo.videoState, CALL_ERR_PHONE_NUMBER_EMPTY, "dialString is empty");
        return CALL_ERR_PHONE_NUMBER_EMPTY;
    }

//The wearer does not register satellite radio status. Currently, the wearer does not support SkyTone satellite calls.
#ifdef BASE_POWER_IMPROVEMENT_FEATURE
    auto serviceInstance = DelayedSingleton<CellularCallService>::GetInstance();
    if (serviceInstance == nullptr) {
        TELEPHONY_LOGE("serviceInstance get failed!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    isRadioOn = serviceInstance->isRadioOnFlag(callInfo.slotId);
#else
    ModuleServiceUtils moduleServiceUtils;
    isRadioOn = moduleServiceUtils.GetRadioState(callInfo.slotId);
#endif
    if (!isRadioOn) {
        TELEPHONY_LOGE("DialPreJudgment return, radio state error.");
        CellularCallHiSysEvent::WriteDialCallFaultEvent(callInfo.accountId, static_cast<int32_t>(callInfo.callType),
            callInfo.videoState, CALL_ERR_GET_RADIO_STATE_FAILED, "radio state error");
        return CALL_ERR_GET_RADIO_STATE_FAILED;
    }
    return TELEPHONY_SUCCESS;
}

bool ControlBase::IsNeedExecuteMMI(int32_t slotId, std::string &phoneString, CLIRMode &clirMode, bool isNeedUseIms)
{
    TELEPHONY_LOGI("IsNeedExecuteMMI start");
    if (IsEmergencyCall(slotId, phoneString)) {
        return false;
    }
    // Also supplementary services may be controlled using dial command according to 3GPP TS 22.030 [19].
    // An example of call forwarding on no reply for telephony with the adjustment of the
    // no reply condition timer on 25 seconds:
    // Parse the MMI code from the string
    std::unique_ptr<MMICodeUtils> mmiCodeUtils = std::make_unique<MMICodeUtils>();
    // Parse the MMI code from the string
    if (mmiCodeUtils == nullptr) {
        TELEPHONY_LOGE("IsNeedExecuteMMI return, mmiCodeUtils is nullptr");
        return false;
    }
    if (TELEPHONY_EXT_WRAPPER.isMmiCode_ != nullptr) {
        bool isMmiCode = TELEPHONY_EXT_WRAPPER.isMmiCode_(slotId, phoneString);
        if (!isMmiCode) {
            TELEPHONY_LOGI("don't need to execute mmi");
            return false;
        }
    }
    if (!mmiCodeUtils->IsNeedExecuteMmi(phoneString, isNeedUseIms)) {
        TELEPHONY_LOGI("IsNeedExecuteMMI return, isn't need to execute mmi");
        return false;
    }
    if (!mmiCodeUtils->GetMMIData().serviceCode.empty() && !mmiCodeUtils->GetMMIData().dialString.empty()) {
        TELEPHONY_LOGI("IsNeedExecuteMMI, handle additional CLIR mode");
        if (mmiCodeUtils->GetMMIData().actionString == "*") {
            phoneString = mmiCodeUtils->GetMMIData().dialString;
            if (mmiCodeUtils->GetMMIData().serviceCode == "31") {
                clirMode = CLIRMode::TRANSFER;
            }
            return false;
        } else if (mmiCodeUtils->GetMMIData().actionString == "#") {
            phoneString = mmiCodeUtils->GetMMIData().dialString;
            if (mmiCodeUtils->GetMMIData().serviceCode == "31") {
                clirMode = CLIRMode::INHIBITION;
            }
            return false;
        }
    }
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGI("IsNeedExecuteMMI return, GetInstance is nullptr");
        return false;
    }
    if (DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId) == nullptr) {
        TELEPHONY_LOGI("IsNeedExecuteMMI return, GetHandler is nullptr");
        return false;
    }
    return DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId)->SendEvent(
        MMIHandlerId::EVENT_MMI_Id, mmiCodeUtils);
}

bool ControlBase::IsEmergencyCall(int32_t slotId, std::string &phoneString)
{
    EmergencyUtils emergencyUtils;
    bool isEmergencyCall = false;
    emergencyUtils.IsEmergencyCall(slotId, phoneString, isEmergencyCall);
    return isEmergencyCall;
}

bool ControlBase::IsDtmfKey(char c) const
{
    /**
     * 1. <DTMF>. A single ASCII character in the set 0 9, #,*,A D. This is interpreted as a single ASCII character
     * whose duration is set by the +VTD command. NOTE 2:	In GSM this operates only in voice mode.
     */
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'D') || c == '*' || c == '#';
}

bool ControlBase::IsConnectedOut(TelCallState preState, TelCallState curState)
{
    if ((preState == TelCallState::CALL_STATUS_DIALING || preState == TelCallState::CALL_STATUS_ALERTING) &&
        !(curState == TelCallState::CALL_STATUS_DIALING || curState == TelCallState::CALL_STATUS_ALERTING)) {
        return true;
    }
    return false;
}

bool ControlBase::CheckAirplaneModeScene(const CellularCallInfo &callInfo)
{
    bool isAirplaneModeOn = false;
    ModuleServiceUtils moduleServiceUtils;
    return moduleServiceUtils.GetAirplaneMode(isAirplaneModeOn) == TELEPHONY_SUCCESS && isAirplaneModeOn;
}

bool ControlBase::CheckActivateSimScene(int32_t slotId)
{
    bool hasSimCard = false;
    CoreManagerInner::GetInstance().HasSimCard(slotId, hasSimCard);
    bool isActivateSim = true;
    if (hasSimCard) {
        isActivateSim = CoreManagerInner::GetInstance().IsSimActive(slotId);
    }
    return isActivateSim;
}

int32_t ControlBase::HandleEcc(const CellularCallInfo &callInfo, bool isEcc, bool isAirplaneModeOn, bool isActivateSim)
{
    if (!isEcc) {
        TELEPHONY_LOGE("HandleEcc airplane mode is not ecc");
        return TELEPHONY_ERR_AIRPLANE_MODE_ON;
    }

    if (isAirplaneModeOn) {
        ModuleServiceUtils moduleServiceUtils;
        int32_t ret = moduleServiceUtils.UpdateRadioOn(callInfo.slotId);
        if (ret != TELEPHONY_SUCCESS) {
            TELEPHONY_LOGE("UpdateRadioOn fail");
            return ret;
        }
    }
    if (!isActivateSim) {
        int32_t ret = DelayedRefSingleton<CoreServiceClient>::GetInstance().SetActiveSim(callInfo.slotId, true);
        if (ret != TELEPHONY_SUCCESS) {
            TELEPHONY_LOGE("UpdateSimState fail");
            return ret;
        }
        int32_t otherSlotId = callInfo.slotId == SLOT_0 ? SLOT_1 : SLOT_0;
        if (!CheckActivateSimScene(otherSlotId)) {
            ret = DelayedRefSingleton<CoreServiceClient>::GetInstance().SetActiveSim(otherSlotId, true);
            if (ret != TELEPHONY_SUCCESS) {
                TELEPHONY_LOGE("UpdateSecondSimCardState fail");
                return ret;
            }
        }
    }
    std::unique_lock<std::mutex> lock(mutex_);
    CellularCallConfig cellularCallConfig;
    while (!cellularCallConfig.IsReadyToCall(callInfo.slotId)) {
        if (cv_.wait_for(lock, std::chrono::seconds(WAIT_TIME_SECOND)) == std::cv_status::timeout) {
            TELEPHONY_LOGE("HandleEcc network in service timeout");
            return CALL_ERR_DIAL_FAILED;
        }
    }

    return TELEPHONY_SUCCESS;
}

int32_t ControlBase::SetReadyToCall(int32_t slotId, bool isReadyToCall)
{
    std::unique_lock<std::mutex> lock(mutex_);
    CellularCallConfig cellularCallConfig;
    if (!cellularCallConfig.IsReadyToCall(slotId) && isReadyToCall) {
        cellularCallConfig.SetReadyToCall(slotId, isReadyToCall);
        cv_.notify_all();
    }
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS
