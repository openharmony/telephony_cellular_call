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

#ifndef TELEPHONY_IMS_CALL_CALLBACK_INTERFACE_H
#define TELEPHONY_IMS_CALL_CALLBACK_INTERFACE_H

#include "iremote_broker.h"

#include "hril_call_parcel.h"
#include "ims_call_types.h"

namespace OHOS {
namespace Telephony {
class ImsCallCallbackInterface : public IRemoteBroker {
public:
    virtual ~ImsCallCallbackInterface() = default;

    enum {
        /****************** call basic ******************/
        IMS_DIAL = 0,
        IMS_HANG_UP,
        IMS_REJECT,
        IMS_ANSWER,
        IMS_HOLD,
        IMS_UN_HOLD,
        IMS_SWITCH,
        IMS_COMBINE_CONFERENCE,
        IMS_INVITE_TO_CONFERENCE,
        IMS_KICK_OUT_CONFERENCE,
        IMS_UPDATE_CALL_MEDIA_MODE,
        IMS_EMERGENCY_CALL,
        IMS_CALL_STATE_CHANGE,
        IMS_SERVICE_STATUS,
        IMS_LAST_CALL_FAIL_REASON,
        IMS_GET_CALLS_DATA,
        IMS_SRVCC_STATE,
        IMS_VT_OR_WFC,
        IMS_CALL_CRING,

        /****************** dtmf、rtt ******************/
        IMS_START_DTMF,
        IMS_SEND_DTMF,
        IMS_STOP_DTMF,
        IMS_START_RTT,
        IMS_STOP_RTT,

        /****************** ims config ******************/
        IMS_SET_PRE_MODE,
        IMS_GET_PRE_MODE,
        IMS_SET_LTE_SWITCH_STATUS,
        IMS_GET_LTE_SWITCH_STATUS,
        IMS_SET_CONFIG,
        IMS_GET_CONFIG,
        IMS_SET_FEATURE,
        IMS_GET_FEATURE,
        IMS_SET_LTE_SWITCH_ENHANCE_MODE_STATUS,
        IMS_GET_LTE_SWITCH_ENHANCE_MODE_STATUS,
        IMS_SET_MUTE,
        IMS_GET_MUTE,
        IMS_GET_EMERGENCY_CALL_LIST,

        /****************** video settings ******************/
        IMS_CONTROL_CAMERA,
        IMS_SET_PREVIEW_WINDOW,
        IMS_SET_DISPLAY_WINDOW,
        IMS_SET_CAMERA_ZOOM,
        IMS_SET_PAUSE_IMAGE,
        IMS_SET_DEVICE_DIRECTION,

        /****************** supplement ******************/
        IMS_GET_CALL_CLIP,
        IMS_GET_CALL_CLIR,
        IMS_SET_CALL_CLIR,
        IMS_GET_CALL_FORWARD,
        IMS_SET_CALL_FORWARD,
        IMS_GET_CALL_RESTRICTION,
        IMS_SET_CALL_RESTRICTION,
        IMS_GET_CALL_WAIT,
        IMS_SET_CALL_WAIT,
    };

    /**
     * DialResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t DialResponse(const ImsResponseInfo &info) = 0;

    /**
     * HangUpResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t HangUpResponse(const ImsResponseInfo &info) = 0;

    /**
     * RejectResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t RejectResponse(const ImsResponseInfo &info) = 0;

    /**
     * AnswerResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t AnswerResponse(const ImsResponseInfo &info) = 0;

    /**
     * HoldResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t HoldResponse(const ImsResponseInfo &info) = 0;

    /**
     * UnHoldResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UnHoldResponse(const ImsResponseInfo &info) = 0;

    /**
     * SwitchResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SwitchResponse(const ImsResponseInfo &info) = 0;

    /**
     * CombineConferenceResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t CombineConferenceResponse(const ImsResponseInfo &info) = 0;

    /**
     * InviteToConferenceResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t InviteToConferenceResponse(const ImsResponseInfo &info) = 0;

    /**
     * KickOutFromConferenceResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t KickOutFromConferenceResponse(const ImsResponseInfo &info) = 0;

    /**
     * CallMediaModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t CallMediaModeResponse(const ImsResponseInfo &info) = 0;

    /**
     * IsEmergencyPhoneNumberResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t IsEmergencyPhoneNumberResponse(const ImsResponseInfo &info) = 0;

    /**
     * IsEmergencyPhoneNumberResponse
     *
     * @param bool
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t IsEmergencyPhoneNumberResponse(bool value) = 0;

    /**
     * StartDtmfResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t StartDtmfResponse(const ImsResponseInfo &info) = 0;
    /**
     * SendDtmfResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */

    virtual int32_t SendDtmfResponse(const ImsResponseInfo &info) = 0;

    /**
     * StopDtmfResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t StopDtmfResponse(const ImsResponseInfo &info) = 0;

    /**
     * StartRttResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t StartRttResponse(const ImsResponseInfo &info) = 0;

    /**
     * StopRttResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t StopRttResponse(const ImsResponseInfo &info) = 0;

    /**
     * CallStateChangeReport
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t CallStateChangeReport(int32_t slotId) = 0;

    /**
     * ServiceStatusResponse
     *
     * @param slotId
     * @param CallImsServiceStatus
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t ServiceStatusResponse(int32_t slotId, const CallImsServiceStatus &callImsServiceStatus) = 0;

    /**
     * SetPreModeResponse
     *
     * @param slotId
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetPreModeResponse(int32_t slotId, const ImsResponseInfo &info) = 0;

    /**
     * GetPreModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetPreModeResponse(const ImsResponseInfo &info) = 0;

    /**
     * GetPreModeResponse
     *
     * @param slotId
     * @param int32_t
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetPreModeResponse(int32_t slotId, int32_t mode) = 0;

    /**
     * SetImsSwitchResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetImsSwitchResponse(const ImsResponseInfo &info) = 0;

    /**
     * GetImsSwitchResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetImsSwitchResponse(const ImsResponseInfo &info) = 0;

    /**
     * GetImsSwitchResponse
     *
     * @param slotId
     * @param active 1: ims is enabled, 0: ims is disabled
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetImsSwitchResponse(int32_t slotId, int32_t active) = 0;

    /**
     * ImsCallsDataResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t ImsCallsDataResponse(const ImsResponseInfo &info) = 0;

    /**
     * ImsCallsDataResponse
     *
     * @param slotId
     * @param callList
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t ImsCallsDataResponse(int32_t slotId, const ImsCurrentCallList &callList) = 0;

    /**
     * SetImsConfigResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetImsConfigResponse(const ImsResponseInfo &info) = 0;

    /**
     * GetImsConfigResponse
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetImsConfigResponse(int32_t value) = 0;

    /**
     * GetImsConfigResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetImsConfigResponse(const ImsResponseInfo &info) = 0;

    /**
     * SetImsFeatureValueResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetImsFeatureValueResponse(const ImsResponseInfo &info) = 0;

    /**
     * GetImsFeatureValueResponse
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetImsFeatureValueResponse(int32_t value) = 0;

    /**
     * GetImsFeatureValueResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetImsFeatureValueResponse(const ImsResponseInfo &info) = 0;

    /**
     * SetImsSwitchEnhanceModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info) = 0;

    /**
     * GetImsSwitchEnhanceModeResponse
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetImsSwitchEnhanceModeResponse(int32_t value) = 0;

    /**
     * GetImsSwitchEnhanceModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info) = 0;

    /**
     * CtrlCameraResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t CtrlCameraResponse(const ImsResponseInfo &info) = 0;

    /**
     * SetPreviewWindowResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetPreviewWindowResponse(const ImsResponseInfo &info) = 0;

    /**
     * SetDisplayWindowResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetDisplayWindowResponse(const ImsResponseInfo &info) = 0;

    /**
     * SetCameraZoomResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetCameraZoomResponse(const ImsResponseInfo &info) = 0;

    /**
     * SetPauseImageResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetPauseImageResponse(const ImsResponseInfo &info) = 0;

    /**
     * SetDeviceDirectionResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetDeviceDirectionResponse(const ImsResponseInfo &info) = 0;

    /**
     * SrvccStateReport
     *
     * @param slotId
     * @param SrvccState
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SrvccStateReport(int32_t slotId, SrvccState srvccState) = 0;

    /**
     * VtWfcReport
     *
     * @param slotId
     * @param TransferState
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t VtWfcReport(int32_t slotId, TransferState transferState) = 0;

    /**
     * CallRingBackResponse
     *
     * @param RingbackVoice
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t CallRingBackResponse(const RingbackVoice &info) = 0;

    /**
     * SetMuteResponse
     *
     * @param MuteControlResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetMuteResponse(const MuteControlResponse &response) = 0;

    /**
     * GetMuteResponse
     *
     * @param MuteControlResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetMuteResponse(const MuteControlResponse &response) = 0;

    /**
     * GetEccCallListResponse
     *
     * @param EmergencyInfoList
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetEccCallListResponse(const EmergencyInfoList &callList) = 0;

    /**
     * LastCallFailReasonResponse
     *
     * @param reason
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t LastCallFailReasonResponse(int32_t reason) = 0;

    /**
     * GetClipResponse
     *
     * @param ClipResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetClipResponse(const ClipResponse &response) = 0;

    /**
     * GetClirResponse
     *
     * @param ClirResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetClirResponse(const ClirResponse &response) = 0;

    /**
     * SetClirResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetClirResponse(HRilErrType errType) = 0;

    /**
     * GetCallTransferResponse
     *
     * @param CallTransferResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetCallTransferResponse(const CallTransferResponse &response) = 0;

    /**
     * SetCallTransferResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetCallTransferResponse(HRilErrType errType) = 0;

    /**
     * GetCallRestrictionResponse
     *
     * @param CallRestrictionResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetCallRestrictionResponse(const CallRestrictionResponse &response) = 0;

    /**
     * SetCallRestrictionResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetCallRestrictionResponse(HRilErrType errType) = 0;

    /**
     * GetCallWaitingResponse
     *
     * @param CallWaitResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetCallWaitingResponse(const CallWaitResponse &response) = 0;

    /**
     * SetCallWaitingResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetCallWaitingResponse(HRilErrType errType) = 0;

public:
    DECLARE_INTERFACE_DESCRIPTOR(u"OHOS.Telephony.ImsCallCallback");
};
} // namespace Telephony
} // namespace OHOS

#endif // TELEPHONY_IMS_CALL_CALLBACK_INTERFACE_H
