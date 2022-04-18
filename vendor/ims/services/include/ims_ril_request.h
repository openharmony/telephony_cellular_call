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

#ifndef IMS_RIL_REQUEST_H
#define IMS_RIL_REQUEST_H

#include "ims_call_types.h"
#include "cellular_call_data_struct.h"
#include "ims_register.h"

namespace OHOS {
namespace Telephony {
class ImsRilRequest {
public:
    /**
     * ImsRilRequest
     */
    ImsRilRequest();

    /**
     * ~ImsRilRequest
     */
    ~ImsRilRequest() = default;

    /**
     * Dial Request
     *
     * @param ImsDialInfoStruct
     * @param CLIRMode
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t DialRequest(const ImsCallInfo &callInfo, CLIRMode mode) const;

    /**
     * HangUp Request
     *
     * @param index
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t HangUpRequest(int32_t slotId, int32_t index) const;

    /**
     * Answer Request
     *
     * @param videoState
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t AnswerRequest(int32_t slotId, int32_t videoState) const;

    /**
     * Reject Request
     *
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t RejectRequest(int32_t slotId) const;

    /**
     * Swap Request
     *
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t SwitchCallRequest(int32_t slotId) const;

    /**
     * Hold Request
     *
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t HoldRequest(int32_t slotId) const;

    /**
     * UnHoldCall Request
     *
     * @param slotId
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t UnHoldCallRequest(int32_t slotId) const;

    /**
     * CombineConference Request
     *
     * @param slotId
     * @param voiceCall
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t CombineConferenceRequest(int32_t slotId, int32_t voiceCall) const;

    /**
     * InviteToConference Request
     *
     * @param numberList
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t InviteToConferenceRequest(int32_t slotId, const std::vector<std::string> &numberList) const;

    /**
     * KickOutFromConference Request
     *
     * @param numberList
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t KickOutFromConferenceRequest(int32_t slotId, const std::vector<std::string> &numberList) const;

    /**
     * UpdateImsCallMode Request
     *
     * @param ImsCallMode
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallMediaModeRequest(int32_t slotId, ImsCallMode mode) const;

    /**
     * IsEmergencyPhoneNumber Request
     *
     * @param phoneNum
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t IsEmergencyPhoneNumberRequest(int32_t slotId, const std::string &phoneNum) const;

    /**
     * Send Dtmf Request
     *
     * @param char cDtmfCode
     * @param index
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SendDtmfRequest(int32_t slotId, char cDtmfCode, int32_t index) const;

    /**
     * Start Dtmf Request
     *
     * @param char cDtmfCode
     * @param index
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StartDtmfRequest(int32_t slotId, char cDtmfCode, int32_t index) const;

    /**
     * Stop Dtmf Request
     *
     * @param index
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StopDtmfRequest(int32_t slotId, int32_t index) const;

    /**
     * Start Rtt Request
     *
     * @param msg
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StartRttRequest(int32_t slotId, const std::string &msg) const;

    /**
     * Stop Rtt Request
     *
     * @param slotId
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StopRttRequest(int32_t slotId) const;

    /**
     *  GetImsCallsDataRequest
     *
     * @param slotId
     * @param lastCallsDataFlag
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag) const;

    /**
     * Set Domain Preference Mode Request
     *
     * @param slotId
     * @param mode
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetDomainPreferenceModeRequest(int32_t slotId, int32_t mode) const;

    /**
     * Get Domain Preference Mode Request
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetDomainPreferenceModeRequest(int32_t slotId) const;

    /**
     * Set Lte Ims Switch Status Request
     *
     * @param slotId
     * @param active
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetLteImsSwitchStatusRequest(int32_t slotId, int32_t active) const;

    /**
     * Get Lte Ims Switch Status Request
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetLteImsSwitchStatusRequest(int32_t slotId) const;

    /**
     * SetImsConfig Request
     *
     * @param ImsConfigItem
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsConfigRequest(ImsConfigItem item, const std::string &value) const;

    /**
     * SetImsConfig Request
     *
     * @param ImsConfigItem
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsConfigRequest(ImsConfigItem item, int32_t value) const;

    /**
     * GetImsConfig Request
     *
     * @param ImsConfigItem
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsConfigRequest(ImsConfigItem item) const;

    /**
     * SetImsFeatureValue Request
     *
     * @param FeatureType
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsFeatureValueRequest(FeatureType type, int32_t value) const;

    /**
     * GetImsFeatureValue Request
     *
     * @param FeatureType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsFeatureValueRequest(FeatureType type) const;

    /**
     * SetImsSwitchEnhanceMode Request
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsSwitchEnhanceModeRequest(bool value) const;

    /**
     * GetImsSwitchEnhanceMode Request
     *
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsSwitchEnhanceModeRequest() const;

    /**
     * CtrlCamera Request
     *
     * @param cameraId
     * @param callingUid
     * @param callingPid
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t CtrlCameraRequest(const std::u16string &cameraId, int32_t callingUid, int32_t callingPid) const;

    /**
     * SetPreviewWindow Request
     *
     * @param x
     * @param y
     * @param z
     * @param width
     * @param height
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetPreviewWindowRequest(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height) const;

    /**
     * SetDisplayWindow Request
     *
     * @param x
     * @param y
     * @param z
     * @param width
     * @param height
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetDisplayWindowRequest(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height) const;

    /**
     * SetCameraZoom Request
     *
     * @param zoomRatio
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCameraZoomRequest(float zoomRatio) const;

    /**
     * SetPauseImage Request
     *
     * @param path
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetPauseImageRequest(const std::u16string &path) const;

    /**
     * SetDeviceDirection Request
     *
     * @param rotation
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetDeviceDirectionRequest(int32_t rotation) const;

    /**
     * SetMute Request
     *
     * @param mute
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetMuteRequest(int32_t slotId, int32_t mute) const;

    /**
     * GetMute Request
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetMuteRequest(int32_t slotId) const;

    /**
     * GetEmergencyCallList Request
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetEmergencyCallListRequest(int32_t slotId) const;

    /**
     * GetCallFailReason Request
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallFailReasonRequest(int32_t slotId) const;

    /**
     * InquireClip Request
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t InquireClipRequest(int32_t slotId) const;

    /**
     * SetClir Request
     *
     * @param slotId
     * @param action
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetClirRequest(int32_t slotId, int32_t action) const;

    /**
     * InquireClir Request
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t InquireClirRequest(int32_t slotId) const;

    /**
     * SetCallTransfer Request
     *
     * @param slotId
     * @param reason
     * @param mode
     * @param transferNum
     * @param classType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCallTransferRequest(
        int32_t slotId, int32_t reason, int32_t mode, const std::string &transferNum, int32_t classType) const;

    /**
     * GetCallTransfer Request
     *
     * @param slotId
     * @param reason
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallTransferRequest(int32_t slotId, int32_t reason) const;

    /**
     * SetCallRestriction Request
     *
     * @param slotId
     * @param fac
     * @param mode
     * @param pw
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCallRestrictionRequest(
        int32_t slotId, const std::string &fac, int32_t mode, const std::string &pw) const;

    /**
     * GetCallRestriction Request
     *
     * @param slotId
     * @param fac
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallRestrictionRequest(int32_t slotId, const std::string &fac) const;

    /**
     * SetCallWaiting Request
     *
     * @param slotId
     * @param activate
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCallWaitingRequest(int32_t slotId, bool activate) const;

    /**
     * GetCallWaiting Request
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallWaitingRequest(int32_t slotId) const;

    /**
     * Asynchronous Register
     */
    void AsynchronousRegister();

private:
    // This is the logic of piling. Variables are temporarily stored.
    // These temporary variables can be removed during subsequent development by the manufacturer.
    std::shared_ptr<ImsRegister> imsRegisterInstance_;
    static bool imsSwitchEnhanceModeTemp_;
    static int32_t itemVideoQualityTemp_;
    static int32_t itemImsSwitchStatusTemp_;
    static int32_t voiceOverLteTemp_;
    static int32_t videoOverLteTemp_;
};
} // namespace Telephony
} // namespace OHOS

#endif // IMS_RIL_REQUEST_H
