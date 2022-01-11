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

#ifndef IMS_CALLBACK_H
#define IMS_CALLBACK_H

#include "iremote_broker.h"

#include "hril_call_parcel.h"
#include "ims_types.h"

namespace OHOS {
namespace Telephony {
class ImsCallback : public IRemoteBroker {
public:
    virtual ~ImsCallback() = default;

    /**
     * UpdateDialResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateDialResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateHangUpResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateHangUpResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateRejectResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateRejectResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateAnswerResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateAnswerResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateHoldResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateHoldResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateUnHoldResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateUnHoldResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateSwitchResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSwitchResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateCombineConferenceResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateCombineConferenceResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateInviteToConferenceResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateInviteToConferenceResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateKickOutFromConferenceResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateKickOutFromConferenceResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateCallMediaModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateCallMediaModeResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateIsEmergencyPhoneNumberResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateIsEmergencyPhoneNumberResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateIsEmergencyPhoneNumberResponse
     *
     * @param bool
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateIsEmergencyPhoneNumberResponse(bool value) = 0;

    /**
     * UpdateStartDtmfResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateStartDtmfResponse(const ImsResponseInfo &info) = 0;
    /**
     * UpdateSendDtmfResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */

    virtual int32_t UpdateSendDtmfResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateStopDtmfResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateStopDtmfResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateStartRttResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateStartRttResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateStopRttResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateStopRttResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateCallWaitingResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateCallWaitingResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateCallConnectResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateCallConnectResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateCallEndResponse
     *
     * @param CallEndInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateCallEndResponse(int32_t slotId, const CallEndInfo &callEndInfo) = 0;

    /**
     * UpdateCallStatusResponse
     *
     * @param slotId
     * @param CallStatusInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateCallStatusResponse(int32_t slotId, const CallStatusInfo &callStatusInfo) = 0;

    /**
     * UpdateServiceStatusResponse
     *
     * @param slotId
     * @param CallImsServiceStatus
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateServiceStatusResponse(int32_t slotId, const CallImsServiceStatus &callImsServiceStatus) = 0;

    /**
     * UpdateSetPreModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetPreModeResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateGetPreModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetPreModeResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateGetPreModeResponse
     *
     * @param slotId
     * @param int32_t
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetPreModeResponse(int32_t slotId, int32_t mode) = 0;

    /**
     * UpdateSetImsSwitchResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetImsSwitchResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateGetImsSwitchResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetImsSwitchResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateGetImsSwitchResponse
     *
     * @param slotId
     * @param int32_t
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetImsSwitchResponse(int32_t slotId, int32_t active) = 0;

    /**
     * UpdateImsCallsDataResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateImsCallsDataResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateImsCallsDataResponse
     *
     * @param slotId
     * @param CallInfoList
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateImsCallsDataResponse(int32_t slotId, const CallInfoList &callList) = 0;

    /**
     * UpdateSetImsConfigResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetImsConfigResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateGetImsConfigResponse
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetImsConfigResponse(int32_t value) = 0;

    /**
     * UpdateGetImsConfigResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetImsConfigResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateSetImsFeatureValueResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetImsFeatureValueResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateGetImsFeatureValueResponse
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetImsFeatureValueResponse(int32_t value) = 0;

    /**
     * UpdateGetImsFeatureValueResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetImsFeatureValueResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateSetVolteEnhanceModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetVolteEnhanceModeResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateGetVolteEnhanceModeResponse
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetVolteEnhanceModeResponse(int32_t value) = 0;

    /**
     * UpdateGetVolteEnhanceModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetVolteEnhanceModeResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateCtrlCameraResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateCtrlCameraResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateSetPreviewWindowResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetPreviewWindowResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateSetDisplayWindowResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetDisplayWindowResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateSetCameraZoomResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetCameraZoomResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateSetPauseImageResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetPauseImageResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateSetDeviceDirectionResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetDeviceDirectionResponse(const ImsResponseInfo &info) = 0;

    /**
     * UpdateSrvccStateReport
     *
     * @param slotId
     * @param SrvccState
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSrvccStateReport(int32_t slotId, SrvccState srvccState) = 0;

    /**
     * UpdateVtWfcReport
     *
     * @param slotId
     * @param TransferState
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateVtWfcReport(int32_t slotId, TransferState transferState) = 0;

    /**
     * UpdateCallRingBackResponse
     *
     * @param RingbackVoice
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateCallRingBackResponse(const RingbackVoice &info) = 0;

    /**
     * UpdateSetMuteResponse
     *
     * @param MuteControlResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetMuteResponse(const MuteControlResponse &response) = 0;

    /**
     * UpdateGetMuteResponse
     *
     * @param MuteControlResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetMuteResponse(const MuteControlResponse &response) = 0;

    /**
     * UpdateGetEccCallListResponse
     *
     * @param EmergencyInfoList
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetEccCallListResponse(const EmergencyInfoList &callList) = 0;

    /**
     * UpdateCallFailReasonResponse
     *
     * @param int32_t
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateCallFailReasonResponse(int32_t reason) = 0;

    /**
     * UpdateGetClipResponse
     *
     * @param ClipResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetClipResponse(const ClipResponse &response) = 0;

    /**
     * UpdateGetClirResponse
     *
     * @param ClirResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetClirResponse(const ClirResponse &response) = 0;

    /**
     * UpdateSetClirResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetClirResponse(HRilErrType errType) = 0;

    /**
     * UpdateGetCallTransferResponse
     *
     * @param CallTransferResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetCallTransferResponse(const CallTransferResponse &response) = 0;

    /**
     * UpdateSetCallTransferResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetCallTransferResponse(HRilErrType errType) = 0;

    /**
     * UpdateGetCallRestrictionResponse
     *
     * @param CallRestrictionResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetCallRestrictionResponse(const CallRestrictionResponse &response) = 0;

    /**
     * UpdateSetCallRestrictionResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetCallRestrictionResponse(HRilErrType errType) = 0;

    /**
     * UpdateGetCallWaitingResponse
     *
     * @param CallWaitResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateGetCallWaitingResponse(const CallWaitResponse &response) = 0;

    /**
     * UpdateSetCallWaitingResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateSetCallWaitingResponse(HRilErrType errType) = 0;

    enum {
        /****************** basic ******************/
        UPDATE_IMS_DIAL = 0,
        UPDATE_IMS_HANG_UP,
        UPDATE_IMS_REJECT,
        UPDATE_IMS_ANSWER,
        UPDATE_IMS_HOLD,
        UPDATE_IMS_UN_HOLD,
        UPDATE_IMS_SWITCH,
        UPDATE_IMS_COMBINE_CONFERENCE,
        UPDATE_IMS_INVITE_TO_CONFERENCE,
        UPDATE_IMS_KICK_OUT_CONFERENCE,
        UPDATE_IMS_UPDATE_CALL_MEDIA_MODE,
        UPDATE_IMS_EMERGENCY_CALL,
        UPDATE_IMS_CALL_WAITING,
        UPDATE_IMS_CALL_CONNECT,
        UPDATE_IMS_CALL_END,
        UPDATE_IMS_CALL_STATUS,
        UPDATE_IMS_SERVICE_STATUS,
        UPDATE_CALL_FAIL_REASON,
        UPDATE_IMS_GET_CALLS_DATA,
        UPDATE_SRVCC_STATE,
        UPDATE_VT_OR_WFC,
        UPDATE_CALL_CRING,

        /****************** dtmf、rtt ******************/
        UPDATE_IMS_START_DTMF,
        UPDATE_IMS_SEND_DTMF,
        UPDATE_IMS_STOP_DTMF,
        UPDATE_START_RTT,
        UPDATE_STOP_RTT,

        /****************** ims config ******************/
        UPDATE_IMS_SET_PRE_MODE,
        UPDATE_IMS_GET_PRE_MODE,
        UPDATE_IMS_SET_LTE_SWITCH,
        UPDATE_IMS_GET_LTE_SWITCH,
        UPDATE_SET_CONFIG,
        UPDATE_GET_CONFIG,
        UPDATE_SET_FEATURE,
        UPDATE_GET_FEATURE,
        UPDATE_SET_VOLTE_ENHANCE,
        UPDATE_GET_VOLTE_ENHANCE,
        UPDATE_SET_MUTE,
        UPDATE_GET_MUTE,
        UPDATE_GET_EMERGENCY_CALL_LIST,

        /****************** video settings ******************/
        UPDATE_CONTROL_CAMERA,
        UPDATE_SET_PREVIEW_WINDOW,
        UPDATE_SET_DISPLAY_WINDOW,
        UPDATE_SET_CAMERA_ZOOM,
        UPDATE_SET_PAUSE_IMAGE,
        UPDATE_SET_DEVICE_DIRECTION,

        /****************** supplement ******************/
        UPDATE_GET_CALL_CLIP,
        UPDATE_GET_CALL_CLIR,
        UPDATE_SET_CALL_CLIR,
        UPDATE_GET_CALL_FORWARD,
        UPDATE_SET_CALL_FORWARD,
        UPDATE_GET_CALL_RESTRICTION,
        UPDATE_SET_CALL_RESTRICTION,
        UPDATE_GET_CALL_WAIT,
        UPDATE_SET_CALL_WAIT,
    };

public:
    DECLARE_INTERFACE_DESCRIPTOR(u"OHOS.Telephony.ImsCallback");
};
} // namespace Telephony
} // namespace OHOS

#endif
