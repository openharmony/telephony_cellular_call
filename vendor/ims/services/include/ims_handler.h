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

#ifndef IMS_HANDLER_H
#define IMS_HANDLER_H

#include <memory>
#include <map>

#include "event_handler.h"

#include "telephony_log_wrapper.h"
#include "ims_callback.h"

namespace OHOS {
namespace Telephony {
class ImsHandler : public AppExecFwk::EventHandler {
public:
    /**
     * ImsHandler constructor
     *
     * @param runner
     */
    explicit ImsHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner);

    /**
     * ~ImsHandler destructor
     */
    ~ImsHandler() = default;

    /**
     * ProcessEvent
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallWaitingResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void CallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallConnectResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void CallConnectResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallEndResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void CallEndResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallStatusInfoResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void CallStatusInfoResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallImsServiceStatusResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void CallImsServiceStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetCallPreferenceModeResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetCallPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCallPreferenceModeResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetCallPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetLteImsSwitchStatusResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetLteImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetLteImsSwitchStatusResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetLteImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * DialResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void DialResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * HangUp Response
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void HangUpResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * Reject Response
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void RejectResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * Answer Response
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void AnswerResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * HoldCall Response
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void HoldCallResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * UnHoldCall Response
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void UnHoldCallResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SwitchCall Response
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SwitchCallResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CombineConferenceResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void CombineConferenceResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * InviteToConferenceResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void InviteToConferenceResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * KickOutFromConferenceResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void KickOutFromConferenceResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * UpdateCallMediaModeResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void UpdateCallMediaModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * IsEmergencyPhoneNumberResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void IsEmergencyPhoneNumberResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SendDtmfResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SendDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * StartDtmfResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void StartDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * StopDtmfResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void StopDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * StartRttResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void StartRttResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * StopRttResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void StopRttResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetImsCallsDataResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetImsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetImsConfigResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetImsConfigResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetImsConfigResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetImsConfigResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetImsFeatureValueResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetImsFeatureValueResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetImsFeatureValueResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetImsFeatureValueResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetImsSwitchEnhanceModeResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetImsSwitchEnhanceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetImsSwitchEnhanceModeResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetImsSwitchEnhanceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CtrlCameraResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void CtrlCameraResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetPreviewWindowResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetPreviewWindowResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetDisplayWindowResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetDisplayWindowResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetCameraZoomResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetCameraZoomResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetPauseImageResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetPauseImageResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetDeviceDirectionResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetDeviceDirectionResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallRingBackVoiceResponse
     *
     * @param code process
     */
    void CallRingBackVoiceResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetMuteResponse
     *
     * @param code process
     */
    void SetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetMuteResponse
     *
     * @param code process
     */
    void GetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetEmergencyCallListResponse
     *
     * @param code process
     */
    void GetEmergencyCallListResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCallFailReasonResponse
     *
     * @param code process
     */
    void GetCallFailReasonResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetClipResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetClipResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetClirResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetClirResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetClirResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetClirResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCallTransferResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetCallTransferResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetCallTransferResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetCallTransferResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCallRestrictionResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetCallRestrictionResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCallWaitingResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetCallWaitingResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event);

public:
    const uint32_t ASYNCHRONOUS_REGISTER_ID = 1002;

private:
    /**
     * ThreadRegister
     */
    void AsynchronousRegister(const AppExecFwk::InnerEvent::Pointer &event);

private:
    int32_t slotId_ = DEFAULT_SIM_SLOT_ID;
    using RequestFuncType = void (ImsHandler::*)(const AppExecFwk::InnerEvent::Pointer &event);
    std::map<uint32_t, RequestFuncType> requestFuncMap_;
};
} // namespace Telephony
} // namespace OHOS

#endif
