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

#ifndef IMS_CALL_HANDLER_H
#define IMS_CALL_HANDLER_H
#include <map>

#include "ims_base_handler.h"
#include "telephony_types.h"

namespace OHOS {
namespace Telephony {
class ImsCallHandler : public ImsBaseHandler {
public:
    explicit ImsCallHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner);

    ~ImsCallHandler();

    void ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event) override;

private:
    using ImsCallHandlerFunc = void (ImsCallHandler::*)(const AppExecFwk::InnerEvent::Pointer &);

    /*  --------------  dial call --------------- */
    void DialResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void HangUpResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void RejectResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void AnswerResponse(const AppExecFwk::InnerEvent::Pointer &event);
    
    void CommonResultResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void HoldResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void UnHoldResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SwitchResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void CombineConferenceResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void InviteToConferenceResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void KickOutFromConferenceResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void CallMediaModeResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void IsEmergencyPhoneNumberResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void ImsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void CallStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void CallFailReasonResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void CallRingBackResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetEccCallListResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /*  --------------  dtmf and rtt --------------- */
    void StartDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SendDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void StopDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void StartRttResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void StopRttResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /* ---------------  ims config ----------------- */
    void ServiceStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetPreModeResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetPreModeResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetImsSwitchResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetImsSwitchResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetImsConfigResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetImsConfigResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetImsFeatureValueResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetImsFeatureValueResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetImsSwitchEnhanceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetImsSwitchEnhanceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SrvccStateReport(const AppExecFwk::InnerEvent::Pointer &event);

    /* ---------------  video control ----------------- */
    void CtrlCameraResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetPreviewWindowResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetDisplayWindowResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetCameraZoomResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetPauseImageResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetDeviceDirectionResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void VtWfcReport(const AppExecFwk::InnerEvent::Pointer &event);

    /* --------------  supplyment ------------------- */
    void GetClipResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetClirResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetClirResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetCallTransferResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetCallTransferResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /* --------------- Service status ------------------- */
    void ImsServiceStatusReport(const AppExecFwk::InnerEvent::Pointer &event);

    void InitRequestFuncMap();
    void InitDialRequestFuncMap();
    void InitDtmfRequestFuncMap();
    void InitConfigRequestFuncMap();
    void InitVideoRequestFuncMap();
    void InitSupplymentRequestFuncMap();

    std::map<uint32_t, ImsCallHandlerFunc> requestFuncMap_;
};
} // Telephony
} // OHOS
#endif // IMS_CALL_HANDLER_H
