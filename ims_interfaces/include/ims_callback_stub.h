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

#ifndef TELEPHONY_IMS_CALLBACK_STUB_H
#define TELEPHONY_IMS_CALLBACK_STUB_H

#include <map>

#include "iremote_stub.h"

#include "ims_callback.h"

namespace OHOS {
namespace Telephony {
class ImsCallbackStub : public IRemoteStub<ImsCallback> {
public:
    ImsCallbackStub();
    virtual ~ImsCallbackStub();
    int OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option) override;

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
     * UpdateCallStatusResponse
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallStatusResponse(int32_t slotId) override;

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
     * @param mode
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
    /**
     * OnUpdateDialResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateDialResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateHangUpResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateHangUpResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateRejectResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateRejectResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateAnswerResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateAnswerResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateHoldResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateHoldResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateUnHoldResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateUnHoldResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSwitchResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSwitchResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateCombineConferenceResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateCombineConferenceResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateInviteToConferenceResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateInviteToConferenceResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateKickOutFromConferenceResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateKickOutFromConferenceResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateCallMediaModeResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateCallMediaModeResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateIsEmergencyNumberResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateIsEmergencyNumberResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateStartDtmfResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateStartDtmfResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSendDtmfResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSendDtmfResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateStopDtmfResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateStopDtmfResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateStartRttResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateStartRttResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateStopRttResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateStopRttResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateCallStatusResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateCallStatusResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateServiceStatusResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateServiceStatusResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetPreModeResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetPreModeResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateGetPreModeResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateGetPreModeResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetImsSwitchResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetImsSwitchResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateGetImsSwitchResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateGetImsSwitchResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateImsCallsDataResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateImsCallsDataResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetImsConfigResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetImsConfigResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateGetImsConfigResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateGetImsConfigResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetImsFeatureValueResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetImsFeatureResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateGetImsFeatureResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateGetImsFeatureResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetImsSwitchEnhanceModeResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetImsSwitchEnhanceModeResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateGetImsSwitchEnhanceModeResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateGetImsSwitchEnhanceModeResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateCtrlCameraResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateCtrlCameraResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetPreviewWindowResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetPreviewWindowResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetDisplayWindowResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetDisplayWindowResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetCameraZoomResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetCameraZoomResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetPauseImageResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetPauseImageResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetDeviceDirectionResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetDeviceDirectionResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSrvccStateReportInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSrvccStateReportInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateVtWfcReportInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateVtWfcReportInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetMuteResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetMuteResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateGetMuteResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateGetMuteResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateCallRingBackResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateCallRingBackResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateGetEccListResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateGetEccListResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateCallFailReasonResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateCallFailReasonResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateGetClipResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateGetClipResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateGetClirResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateGetClirResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetClirResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetClirResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateGetCallTransferResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateGetCallTransferResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetCallTransferResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetCallTransferResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateGetCallRestrictionResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateGetCallRestrictionResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetCallRestrictionResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetCallRestrictionResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateGetCallWaitingResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateGetCallWaitingResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * OnUpdateSetCallWaitingResponseInner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateSetCallWaitingResponseInner(MessageParcel &data, MessageParcel &reply);

    /**
     * InitBasicCallFuncMap.
     */
    void InitBasicCallFuncMap();

    /**
     * InitSupportCallFuncMap
     */
    void InitSupportCallFuncMap();

private:
    using RequestFuncType = int32_t (ImsCallbackStub::*)(MessageParcel &data, MessageParcel &reply);
    std::map<uint32_t, RequestFuncType> requestFuncMap_;
};
} // namespace Telephony
} // namespace OHOS

#endif // TELEPHONY_IMS_CALLBACK_STUB_H
