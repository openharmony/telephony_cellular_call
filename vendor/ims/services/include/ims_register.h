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

#ifndef TELEPHONY_IMS_REGISTER_H
#define TELEPHONY_IMS_REGISTER_H

#include "singleton.h"
#include "ims_callback.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
class ImsRegister {
    DECLARE_DELAYED_SINGLETON(ImsRegister);

public:
    /**
     * UpdateDialResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateDialResponse(const ImsResponseInfo &info);

    /**
     * UpdateHangUpResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateHangUpResponse(const ImsResponseInfo &info);

    /**
     * UpdateRejectResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateRejectResponse(const ImsResponseInfo &info);

    /**
     * UpdateAnswerResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateAnswerResponse(const ImsResponseInfo &info);

    /**
     * UpdateHoldResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateHoldResponse(const ImsResponseInfo &info);

    /**
     * UpdateUnHoldResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateUnHoldResponse(const ImsResponseInfo &info);

    /**
     * UpdateSwitchResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSwitchResponse(const ImsResponseInfo &info);

    /**
     * UpdateCombineConferenceResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCombineConferenceResponse(const ImsResponseInfo &info);

    /**
     * UpdateInviteToConferenceResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateInviteToConferenceResponse(const ImsResponseInfo &info);

    /**
     * UpdateKickOutFromConferenceResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateKickOutFromConferenceResponse(const ImsResponseInfo &info);

    /**
     * UpdateCallMediaModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallMediaModeResponse(const ImsResponseInfo &info);

    /**
     * UpdateIsEmergencyPhoneNumberResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateIsEmergencyPhoneNumberResponse(const ImsResponseInfo &info);

    /**
     * UpdateIsEmergencyPhoneNumberResponse
     *
     * @param bool
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateIsEmergencyPhoneNumberResponse(bool value);

    /**
     * UpdateStartDtmfResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateStartDtmfResponse(const ImsResponseInfo &info);

    /**
     * UpdateSendDtmfResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSendDtmfResponse(const ImsResponseInfo &info);

    /**
     * UpdateStopDtmfResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateStopDtmfResponse(const ImsResponseInfo &info);

    /**
     * UpdateStartRttResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateStartRttResponse(const ImsResponseInfo &info);

    /**
     * UpdateStopRttResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateStopRttResponse(const ImsResponseInfo &info);

    /**
     * UpdateCallStatusResponse
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallStatusResponse(int32_t slotId);

    /**
     * UpdateServiceStatusResponse
     *
     * @param slotId
     * @param CallImsServiceStatus
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateServiceStatusResponse(int32_t slotId, const CallImsServiceStatus &callImsServiceStatus);

    /**
     * UpdateSetPreModeResponse
     *
     * @param slotId
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetPreModeResponse(int32_t slotId, const ImsResponseInfo &info);

    /**
     * UpdateGetPreModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetPreModeResponse(const ImsResponseInfo &info);

    /**
     * UpdateGetPreModeResponse
     *
     * @param slotId
     * @param int32_t
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetPreModeResponse(int32_t slotId, int32_t mode);

    /**
     * UpdateSetImsSwitchResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetImsSwitchResponse(const ImsResponseInfo &info);

    /**
     * UpdateGetImsSwitchResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsSwitchResponse(const ImsResponseInfo &info);

    /**
     * UpdateGetImsSwitchResponse
     *
     * @param slotId
     * @param int32_t
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsSwitchResponse(int32_t slotId, int32_t active);

    /**
     * UpdateImsCallsDataResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateImsCallsDataResponse(const ImsResponseInfo &info);

    /**
     * UpdateImsCallsDataResponse
     *
     * @param slotId
     * @param CallInfoList
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateImsCallsDataResponse(int32_t slotId, const CallInfoList &callList);

    /**
     * UpdateSetImsConfigResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetImsConfigResponse(const ImsResponseInfo &info);

    /**
     * UpdateGetImsConfigResponse
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsConfigResponse(int32_t value);

    /**
     * UpdateGetImsConfigResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsConfigResponse(const ImsResponseInfo &info);

    /**
     * UpdateSetImsFeatureValueResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetImsFeatureValueResponse(const ImsResponseInfo &info);

    /**
     * UpdateGetImsFeatureValueResponse
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsFeatureValueResponse(int32_t value);

    /**
     * UpdateGetImsFeatureValueResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsFeatureValueResponse(const ImsResponseInfo &info);

    /**
     * UpdateSetImsSwitchEnhanceModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info);

    /**
     * UpdateGetImsSwitchEnhanceModeResponse
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsSwitchEnhanceModeResponse(int32_t value);

    /**
     * UpdateGetImsSwitchEnhanceModeResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetImsSwitchEnhanceModeResponse(const ImsResponseInfo &info);

    /**
     * UpdateCtrlCameraResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCtrlCameraResponse(const ImsResponseInfo &info);

    /**
     * UpdateSetPreviewWindowResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetPreviewWindowResponse(const ImsResponseInfo &info);

    /**
     * UpdateSetDisplayWindowResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetDisplayWindowResponse(const ImsResponseInfo &info);

    /**
     * UpdateSetCameraZoomResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetCameraZoomResponse(const ImsResponseInfo &info);

    /**
     * UpdateSetPauseImageResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetPauseImageResponse(const ImsResponseInfo &info);

    /**
     * UpdateSetDeviceDirectionResponse
     *
     * @param ImsResponseInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetDeviceDirectionResponse(const ImsResponseInfo &info);

    /**
     * UpdateCallRingBackResponse
     *
     * @param RingbackVoice
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallRingBackResponse(const RingbackVoice &info);

    /**
     * UpdateSetMuteResponse
     *
     * @param MuteControlResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetMuteResponse(const MuteControlResponse &response);

    /**
     * UpdateGetMuteResponse
     *
     * @param MuteControlResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetMuteResponse(const MuteControlResponse &response);

    /**
     * UpdateGetEccCallListResponse
     *
     * @param EmergencyInfoList
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetEccCallListResponse(const EmergencyInfoList &callList);

    /**
     * UpdateCallFailReasonResponse
     *
     * @param int32_t
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallFailReasonResponse(int32_t reason);

    /**
     * UpdateGetClipResponse
     *
     * @param ClipResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetClipResponse(const ClipResponse &response);

    /**
     * UpdateGetClirResponse
     *
     * @param ClirResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetClirResponse(const ClirResponse &response);

    /**
     * UpdateSetClirResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetClirResponse(HRilErrType errType);

    /**
     * UpdateGetCallTransferResponse
     *
     * @param CallTransferResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetCallTransferResponse(const CallTransferResponse &response);

    /**
     * UpdateSetCallTransferResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetCallTransferResponse(HRilErrType errType);

    /**
     * UpdateGetCallRestrictionResponse
     *
     * @param CallRestrictionResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetCallRestrictionResponse(const CallRestrictionResponse &response);

    /**
     * UpdateSetCallRestrictionResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetCallRestrictionResponse(HRilErrType errType);

    /**
     * UpdateGetCallWaitingResponse
     *
     * @param CallWaitResponse
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateGetCallWaitingResponse(const CallWaitResponse &response);

    /**
     * UpdateSetCallWaitingResponse
     *
     * @param HRilErrType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateSetCallWaitingResponse(HRilErrType errType);

    /**
     * Register CellularCallBack
     *
     * @param sptr<ImsCallback>
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t RegisterCellularCallBack(const sptr<ImsCallback> &callback);

    /**
     * Is CellularCallBack Exists
     *
     * @return bool
     */
    bool IsCallBackExists();

private:
    sptr<ImsCallback> cellularCallBack_;
};
} // namespace Telephony
} // namespace OHOS

#endif // TELEPHONY_IMS_REGISTER_H
