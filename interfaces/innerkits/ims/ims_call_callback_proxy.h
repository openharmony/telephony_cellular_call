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
    int32_t DialResponse(const ImsResponseInfo &info) override;
    int32_t HangUpResponse(const ImsResponseInfo &info) override;
    int32_t RejectResponse(const ImsResponseInfo &info) override;
    int32_t AnswerResponse(const ImsResponseInfo &info) override;
    int32_t HoldResponse(const ImsResponseInfo &info) override;
    int32_t UnHoldResponse(const ImsResponseInfo &info) override;
    int32_t SwitchResponse(const ImsResponseInfo &info) override;
    int32_t CombineConferenceResponse(const ImsResponseInfo &info) override;
    int32_t InviteToConferenceResponse(const ImsResponseInfo &info) override;
    int32_t KickOutFromConferenceResponse(const ImsResponseInfo &info) override;
    int32_t CallMediaModeResponse(const ImsResponseInfo &info) override;
    int32_t IsEmergencyPhoneNumberResponse(const ImsResponseInfo &info) override;
    int32_t IsEmergencyPhoneNumberResponse(bool value) override;
    int32_t CallStatusResponse(int32_t slotId) override;
    int32_t ServiceStatusResponse(int32_t slotId, const CallImsServiceStatus &callImsServiceStatus) override;
    int32_t CallFailReasonResponse(int32_t reason) override;
    int32_t ImsCallsDataResponse(const ImsResponseInfo &info) override;
    int32_t ImsCallsDataResponse(int32_t slotId, const CallInfoList &callList) override;
    int32_t SrvccStateReport(int32_t slotId, SrvccState srvccState) override;
    int32_t VtWfcReport(int32_t slotId, TransferState transferState) override;
    int32_t CallRingBackResponse(const RingbackVoice &info) override;

    /****************** dtmf、rtt ******************/
    int32_t StartDtmfResponse(const ImsResponseInfo &info) override;
    int32_t SendDtmfResponse(const ImsResponseInfo &info) override;
    int32_t StopDtmfResponse(const ImsResponseInfo &info) override;
    int32_t StartRttResponse(const ImsResponseInfo &info) override;
    int32_t StopRttResponse(const ImsResponseInfo &info) override;

    /****************** ims config ******************/
    int32_t SetPreModeResponse(int32_t slotId, const ImsResponseInfo &info) override;
    int32_t GetPreModeResponse(const ImsResponseInfo &info) override;
    int32_t GetPreModeResponse(int32_t slotId, int32_t mode) override;
    int32_t SetImsSwitchResponse(const ImsResponseInfo &info) override;
    int32_t GetImsSwitchResponse(const ImsResponseInfo &info) override;
    int32_t GetImsSwitchResponse(int32_t slotId, int32_t active) override;
    int32_t SetImsConfigResponse(const ImsResponseInfo &info) override;
    int32_t GetImsConfigResponse(int32_t value) override;
    int32_t GetImsConfigResponse(const ImsResponseInfo &info) override;
    int32_t SetImsFeatureValueResponse(const ImsResponseInfo &info) override;
    int32_t GetImsFeatureValueResponse(int32_t value) override;
    int32_t GetImsFeatureValueResponse(const ImsResponseInfo &info) override;
    int32_t SetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info) override;
    int32_t GetImsSwitchEnhanceModeResponse(int32_t value) override;
    int32_t GetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info) override;
    int32_t SetMuteResponse(const MuteControlResponse &response) override;
    int32_t GetMuteResponse(const MuteControlResponse &response) override;
    int32_t GetEccCallListResponse(const EmergencyInfoList &callList) override;

    /****************** video settings ******************/
    int32_t CtrlCameraResponse(const ImsResponseInfo &info) override;
    int32_t SetPreviewWindowResponse(const ImsResponseInfo &info) override;
    int32_t SetDisplayWindowResponse(const ImsResponseInfo &info) override;
    int32_t SetCameraZoomResponse(const ImsResponseInfo &info) override;
    int32_t SetPauseImageResponse(const ImsResponseInfo &info) override;
    int32_t SetDeviceDirectionResponse(const ImsResponseInfo &info) override;

    /****************** supplement ******************/
    int32_t GetClipResponse(const ClipResponse &response) override;
    int32_t GetClirResponse(const ClirResponse &response) override;
    int32_t SetClirResponse(HRilErrType errType) override;
    int32_t GetCallTransferResponse(const CallTransferResponse &response) override;
    int32_t SetCallTransferResponse(HRilErrType errType) override;
    int32_t GetCallRestrictionResponse(const CallRestrictionResponse &response) override;
    int32_t SetCallRestrictionResponse(HRilErrType errType) override;
    int32_t GetCallWaitingResponse(const CallWaitResponse &response) override;
    int32_t SetCallWaitingResponse(HRilErrType errType) override;

private:
    static inline BrokerDelegator<ImsCallCallbackProxy> delegator_;
};
} // namespace Telephony
} // namespace OHOS

#endif // TELEPHONY_IMS_CALL_CALLBACK_PROXY_H
