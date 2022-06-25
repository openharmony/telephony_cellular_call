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

#ifndef TELEPHONY_IMS_CALL_CALLBACK_PROXY_H
#define TELEPHONY_IMS_CALL_CALLBACK_PROXY_H

#include "iremote_proxy.h"
#include "ims_call_callback_interface.h"
#include "telephony_errors.h"

namespace OHOS {
namespace Telephony {
class ImsCallCallbackProxy : public IRemoteProxy<ImsCallCallbackInterface> {
public:
    explicit ImsCallCallbackProxy(const sptr<IRemoteObject> &impl);
    virtual ~ImsCallCallbackProxy() = default;

    /****************** call basic ******************/
    int32_t DialResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t HangUpResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t RejectWithReasonResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t AnswerResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t HoldCallResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t UnHoldCallResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t SwitchCallResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t CombineConferenceResponse(const HRilRadioResponseInfo &info) override;
    int32_t InviteToConferenceResponse(const HRilRadioResponseInfo &info) override;
    int32_t KickOutFromConferenceResponse(const HRilRadioResponseInfo &info) override;
    int32_t CallMediaModeResponse(const HRilRadioResponseInfo &info) override;
    int32_t CallStateChangeReport(int32_t slotId) override;
    int32_t GetImsCallsDataResponse(const HRilRadioResponseInfo &info) override;
    int32_t GetImsCallsDataResponse(int32_t slotId, const ImsCurrentCallList &callList) override;
    int32_t LastCallFailReasonResponse(int32_t slotId, int32_t reason) override;
    int32_t SrvccStateReport(int32_t slotId, SrvccState srvccState) override;
    int32_t VtWfcReport(int32_t slotId, TransferState transferState) override;
    int32_t CallRingBackResponse(const RingbackVoice &info) override;

    /****************** dtmf、rtt ******************/
    int32_t StartDtmfResponse(const HRilRadioResponseInfo &info) override;
    int32_t SendDtmfResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t StopDtmfResponse(const HRilRadioResponseInfo &info) override;
    int32_t StartRttResponse(const HRilRadioResponseInfo &info) override;
    int32_t StopRttResponse(const HRilRadioResponseInfo &info) override;

    /****************** ims config ******************/
    int32_t SetPreModeResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetPreModeResponse(const HRilRadioResponseInfo &info) override;
    int32_t GetPreModeResponse(int32_t slotId, int32_t mode) override;
    int32_t SetImsSwitchResponse(const HRilRadioResponseInfo &info) override;
    int32_t GetImsSwitchResponse(const HRilRadioResponseInfo &info) override;
    int32_t GetImsSwitchResponse(int32_t slotId, int32_t active) override;
    int32_t SetImsConfigResponse(const HRilRadioResponseInfo &info) override;
    int32_t GetImsConfigResponse(int32_t value) override;
    int32_t GetImsConfigResponse(const HRilRadioResponseInfo &info) override;
    int32_t SetImsFeatureValueResponse(const HRilRadioResponseInfo &info) override;
    int32_t GetImsFeatureValueResponse(int32_t value) override;
    int32_t GetImsFeatureValueResponse(const HRilRadioResponseInfo &info) override;
    int32_t SetImsSwitchEnhanceModeResponse(const HRilRadioResponseInfo &info) override;
    int32_t GetImsSwitchEnhanceModeResponse(int32_t value) override;
    int32_t GetImsSwitchEnhanceModeResponse(const HRilRadioResponseInfo &info) override;
    int32_t SetMuteResponse(const MuteControlResponse &response) override;
    int32_t GetMuteResponse(const MuteControlResponse &response) override;

    /****************** video settings ******************/
    int32_t CtrlCameraResponse(const HRilRadioResponseInfo &info) override;
    int32_t SetPreviewWindowResponse(const HRilRadioResponseInfo &info) override;
    int32_t SetDisplayWindowResponse(const HRilRadioResponseInfo &info) override;
    int32_t SetCameraZoomResponse(const HRilRadioResponseInfo &info) override;
    int32_t SetPauseImageResponse(const HRilRadioResponseInfo &info) override;
    int32_t SetDeviceDirectionResponse(const HRilRadioResponseInfo &info) override;

    /****************** supplement ******************/
    int32_t SetClipResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetClipResponse(int32_t slotId, const ClipResponse &response) override;
    int32_t GetClirResponse(int32_t slotId, const ClirResponse &response) override;
    int32_t SetClirResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetCallTransferResponse(int32_t slotId, const CallTransferResponse &response) override;
    int32_t SetCallTransferResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetCallRestrictionResponse(int32_t slotId, const CallRestrictionResponse &response) override;
    int32_t SetCallRestrictionResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetCallWaitingResponse(int32_t slotId, const CallWaitResponse &response) override;
    int32_t SetCallWaitingResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t SetColrResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetColrResponse(int32_t slotId, const ColrResponse &response) override;
    int32_t SetColpResponse(int32_t slotId, const HRilRadioResponseInfo &info) override;
    int32_t GetColpResponse(int32_t slotId, const ColpResponse &response) override;

private:
    static inline BrokerDelegator<ImsCallCallbackProxy> delegator_;
};
} // namespace Telephony
} // namespace OHOS

#endif // TELEPHONY_IMS_CALL_CALLBACK_PROXY_H