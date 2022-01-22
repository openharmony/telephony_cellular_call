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

#ifndef IMS_CALLBACK_PROXY_H
#define IMS_CALLBACK_PROXY_H

#include "iremote_proxy.h"
#include "ims_callback.h"
#include "telephony_errors.h"
#include "call_manager_errors.h"

namespace OHOS {
namespace Telephony {
class ImsCallbackProxy : public IRemoteProxy<ImsCallback> {
public:
    explicit ImsCallbackProxy(const sptr<IRemoteObject> &impl);
    virtual ~ImsCallbackProxy() = default;

    /**
     * UpdateDialResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateDialResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateHangUpResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateHangUpResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateRejectResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateRejectResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateAnswerResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateAnswerResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateHoldResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateHoldResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateUnHoldResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateUnHoldResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateSwitchResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSwitchResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateCombineConferenceResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCombineConferenceResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateInviteToConferenceResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateInviteToConferenceResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateKickOutFromConferenceResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateKickOutFromConferenceResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateCallMediaModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallMediaModeResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateIsEmergencyPhoneNumberResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateIsEmergencyPhoneNumberResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateIsEmergencyPhoneNumberResponse
     *
     * @param bool
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateIsEmergencyPhoneNumberResponse(bool value) override;

    /**
     * UpdateStartDtmfResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateStartDtmfResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateSendDtmfResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSendDtmfResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateStopDtmfResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateStopDtmfResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateStartRttResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateStartRttResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateStopRttResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateStopRttResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateCallWaitingResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallWaitingResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateCallConnectResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallConnectResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateCallEndResponse
     *
     * @param slotId
     * @param CallEndInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallEndResponse(int32_t slotId, const CallEndInfo &callEndInfo) override;

    /**
     * UpdateCallStatusResponse
     *
     * @param slotId
     * @param CallStatusInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallStatusResponse(int32_t slotId, const CallStatusInfo &callStatusInfo) override;

    /**
     * UpdateServiceStatusResponse
     *
     * @param slotId
     * @param CallImsServiceStatus
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateServiceStatusResponse(int32_t slotId, const CallImsServiceStatus &callImsServiceStatus) override;

    /**
     * UpdateSetPreModeResponse
     *
     * @param slotId
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetPreModeResponse(int32_t slotId, const ImsResponseInfo &info) override;

    /**
     * UpdateGetPreModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetPreModeResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateGetPreModeResponse
     *
     * @param slotId
     * @param int32_t
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetPreModeResponse(int32_t slotId, int32_t mode) override;

    /**
     * UpdateSetImsSwitchResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetImsSwitchResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateGetImsSwitchResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsSwitchResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateGetImsSwitchResponse
     *
     * @param slotId
     * @param active
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsSwitchResponse(int32_t slotId, int32_t active) override;

    /**
     * UpdateImsCallsDataResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateImsCallsDataResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateImsCallsDataResponse
     *
     * @param slotId
     * @param CallInfoList
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateImsCallsDataResponse(int32_t slotId, const CallInfoList &callList) override;

    /**
     * UpdateSetImsConfigResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetImsConfigResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateGetImsConfigResponse
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsConfigResponse(int32_t value) override;

    /**
     * UpdateGetImsConfigResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsConfigResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateSetImsFeatureValueResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetImsFeatureValueResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateGetImsFeatureValueResponse
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsFeatureValueResponse(int32_t value) override;

    /**
     * UpdateGetImsFeatureValueResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsFeatureValueResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateSetImsSwitchEnhanceModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateGetImsSwitchEnhanceModeResponse
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsSwitchEnhanceModeResponse(int32_t value) override;

    /**
     * UpdateGetImsSwitchEnhanceModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateCtrlCameraResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCtrlCameraResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateSetPreviewWindowResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetPreviewWindowResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateSetDisplayWindowResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetDisplayWindowResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateSetCameraZoomResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetCameraZoomResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateSetPauseImageResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetPauseImageResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateSetDeviceDirectionResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetDeviceDirectionResponse(const ImsResponseInfo &info) override;

    /**
     * UpdateSrvccStateReport
     *
     * @param slotId
     * @param SrvccState
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSrvccStateReport(int32_t slotId, SrvccState srvccState) override;

    /**
     * UpdateVtWfcReport
     *
     * @param slotId
     * @param TransferState
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateVtWfcReport(int32_t slotId, TransferState transferState) override;

    /**
     * UpdateCallRingBackResponse
     *
     * @param RingbackVoice
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallRingBackResponse(const RingbackVoice &info) override;

    /**
     * UpdateSetMuteResponse
     *
     * @param MuteControlResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetMuteResponse(const MuteControlResponse &response) override;

    /**
     * UpdateGetMuteResponse
     *
     * @param MuteControlResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetMuteResponse(const MuteControlResponse &response) override;

    /**
     * UpdateGetEccCallListResponse
     *
     * @param EmergencyInfoList
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetEccCallListResponse(const EmergencyInfoList &callList) override;

    /**
     * UpdateCallFailReasonResponse
     *
     * @param int32_t
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallFailReasonResponse(int32_t reason) override;

    /**
     * UpdateGetClipResponse
     *
     * @param ClipResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetClipResponse(const ClipResponse &response) override;

    /**
     * UpdateGetClirResponse
     *
     * @param ClirResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetClirResponse(const ClirResponse &response) override;

    /**
     * UpdateSetClirResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetClirResponse(HRilErrType errType) override;

    /**
     * UpdateGetCallTransferResponse
     *
     * @param CallTransferResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetCallTransferResponse(const CallTransferResponse &response) override;

    /**
     * UpdateSetCallTransferResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetCallTransferResponse(HRilErrType errType) override;

    /**
     * UpdateGetCallRestrictionResponse
     *
     * @param CallRestrictionResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetCallRestrictionResponse(const CallRestrictionResponse &response) override;

    /**
     * UpdateSetCallRestrictionResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetCallRestrictionResponse(HRilErrType errType) override;

    /**
     * UpdateGetCallWaitingResponse
     *
     * @param CallWaitResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetCallWaitingResponse(const CallWaitResponse &response) override;

    /**
     * UpdateSetCallWaitingResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetCallWaitingResponse(HRilErrType errType) override;

private:
    static inline BrokerDelegator<ImsCallbackProxy> delegator_;
};
} // namespace Telephony
} // namespace OHOS

#endif
