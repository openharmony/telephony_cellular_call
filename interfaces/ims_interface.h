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

#ifndef TELEPHONY_IMS_INTERFACE_H
#define TELEPHONY_IMS_INTERFACE_H

#include "iremote_broker.h"
#include "ims_types.h"
#include "ims_callback.h"
#include "cellular_call_types.h"

namespace OHOS {
namespace Telephony {
class ImsInterface : public IRemoteBroker {
public:
    enum {
        /****************** basic ******************/
        IMS_DIAL = 1,
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
        IMS_GET_CALL_DATA,
        GET_CALL_FAIL_REASON,

        /****************** dtmf、rtt ******************/
        IMS_START_DTMF = 100,
        IMS_SEND_DTMF,
        IMS_STOP_DTMF,
        IMS_START_RTT,
        IMS_STOP_RTT,

        /****************** ims config ******************/
        IMS_SET_DOMAIN_PREFERENCE_MODE = 200,
        IMS_GET_DOMAIN_PREFERENCE_MODE,
        IMS_SET_LTE_IMS_SWITCH_STATUS,
        IMS_GET_LTE_IMS_SWITCH_STATUS,
        IMS_SET_IMS_CONFIG_STRING,
        IMS_SET_IMS_CONFIG_INT,
        IMS_GET_IMS_CONFIG,
        IMS_SET_IMS_FEATURE,
        IMS_GET_IMS_FEATURE,
        IMS_SET_IMS_SWITCH_ENHANCE_MODE,
        IMS_GET_IMS_SWITCH_ENHANCE_MODE,
        IMS_SET_MUTE,
        IMS_GET_MUTE,
        IMS_GET_EMERGENCY_CALL_LIST,

        /****************** video settings ******************/
        IMS_CTRL_CAMERA = 300,
        IMS_SET_PREVIEW_WINDOW,
        IMS_SET_DISPLAY_WINDOW,
        IMS_SET_CAMERA_ZOOM,
        IMS_SET_PAUSE_IMAGE,
        IMS_SET_DEVICE_DIRECTION,

        /****************** Supplement ******************/
        IMS_INQUIRE_CLIP = 400,
        IMS_SET_CLIR,
        IMS_INQUIRE_CLIR,
        IMS_SET_CALL_TRANSFER,
        IMS_GET_CALL_TRANSFER,
        IMS_SET_CALL_RESTRICTION,
        IMS_GET_CALL_RESTRICTION,
        IMS_SET_CALL_WAITING,
        IMS_GET_CALL_WAITING,

        /****************** callback ******************/
        IMS_REGISTER_CALLBACK = 500,
        IMS_IS_CALLBACK_EXISTS,
    };

    /**
     * IMS dial interface
     *
     * @param ImsCallInfo
     * @param CLIRMode
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t Dial(const ImsCallInfo &callInfo, CLIRMode mode) = 0;

    /**
     * IMS HangUp interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t HangUp(const ImsCallInfo &callInfo) = 0;

    /**
     * IMS Reject interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t Reject(const ImsCallInfo &callInfo) = 0;

    /**
     * IMS Answer interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t Answer(const ImsCallInfo &callInfo) = 0;

    /**
     * IMS HoldCall interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t HoldCall(int32_t slotId) = 0;

    /**
     * IMS UnHoldCall interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UnHoldCall(int32_t slotId) = 0;

    /**
     * IMS SwitchCall interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SwitchCall(int32_t slotId) = 0;

    /**
     * IMS CombineConference interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t CombineConference(int32_t slotId) = 0;

    /**
     * IMS InviteToConference interface
     *
     * @param slotId
     * @param numberList
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t InviteToConference(int32_t slotId, const std::vector<std::string> &numberList) = 0;

    /**
     * IMS KickOutFromConference interface
     *
     * @param slotId
     * @param numberList
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t KickOutFromConference(int32_t slotId, const std::vector<std::string> &numberList) = 0;

    /**
     * IMS UpdateImsCallMode interface
     *
     * @param ImsCallInfo
     * @param ImsCallMode
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t UpdateImsCallMode(const ImsCallInfo &callInfo, ImsCallMode mode) = 0;

    /**
     * IMS IsEmergencyPhoneNumber interface
     *
     * @param slotId
     * @param phoneNum
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t IsEmergencyPhoneNumber(int32_t slotId, const std::string &phoneNum) = 0;

    /**
     * Get Ims Calls Data Request
     *
     * @param slotId
     * @param lastCallsDataFlag
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag) = 0;

    /**
     * Get Call Fail Reason
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetCallFailReason(int32_t slotId) = 0;

    /**
     * IMS StartDtmf interface
     *
     * @param slotId
     * @param cDTMFCode
     * @param index
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t StartDtmf(int32_t slotId, char cDtmfCode, int32_t index) = 0;

    /**
     * IMS SendDtmf interface
     *
     * @param slotId
     * @param cDtmfCode
     * @param index
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SendDtmf(int32_t slotId, char cDtmfCode, int32_t index) = 0;

    /**
     * IMS StopDtmf interface
     *
     * @param slotId
     * @param index
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t StopDtmf(int32_t slotId, int32_t index) = 0;

    /**
     * IMS StartRtt interface
     *
     * @param slotId
     * @param msg
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t StartRtt(int32_t slotId, const std::string &msg) = 0;

    /**
     * IMS StopRtt interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t StopRtt(int32_t slotId) = 0;

    /**
     * IMS SetDomainPreferenceMode interface
     *
     * @param slotId
     * @param mode
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetDomainPreferenceMode(int32_t slotId, int32_t mode) = 0;

    /**
     * IMS GetDomainPreferenceMode interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetDomainPreferenceMode(int32_t slotId) = 0;

    /**
     * IMS SetLteImsSwitchStatus interface
     *
     * @param slotId
     * @param active
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetLteImsSwitchStatus(int32_t slotId, bool active) = 0;

    /**
     * IMS GetLteImsSwitchStatus interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetLteImsSwitchStatus(int32_t slotId) = 0;

    /**
     * IMS SetImsConfig interface
     *
     * @param ImsConfigItem
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetImsConfig(ImsConfigItem item, const std::string &value) = 0;

    /**
     * IMS SetImsConfig interface
     *
     * @param ImsConfigItem
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetImsConfig(ImsConfigItem item, int32_t value) = 0;

    /**
     * IMS GetImsConfig interface
     *
     * @param ImsConfigItem
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetImsConfig(ImsConfigItem item) = 0;

    /**
     * IMS SetImsFeatureValue interface
     *
     * @param FeatureType
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetImsFeatureValue(FeatureType type, int32_t value) = 0;

    /**
     * IMS GetImsFeatureValue interface
     *
     * @param FeatureType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetImsFeatureValue(FeatureType type) = 0;

    /**
     * IMS SetImsSwitchEnhanceMode interface
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetImsSwitchEnhanceMode(bool value) = 0;

    /**
     * IMS GetImsSwitchEnhanceMode interface
     *
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetImsSwitchEnhanceMode() = 0;

    /**
     * IMS CtrlCamera interface
     *
     * @param cameraId
     * @param callingUid
     * @param callingPid
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t CtrlCamera(const std::u16string &cameraId, int32_t callingUid, int32_t callingPid) = 0;

    /**
     * IMS SetPreviewWindow interface
     *
     * @param x
     * @param y
     * @param z
     * @param width
     * @param height
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height) = 0;

    /**
     * IMS SetDisplayWindow interface
     *
     * @param x
     * @param y
     * @param z
     * @param width
     * @param height
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height) = 0;

    /**
     * IMS SetCameraZoom interface
     *
     * @param zoomRatio
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetCameraZoom(float zoomRatio) = 0;

    /**
     * IMS SetPauseImage interface
     *
     * @param path
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetPauseImage(const std::u16string &path) = 0;

    /**
     * IMS SetDeviceDirection interface
     *
     * @param rotation
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetDeviceDirection(int32_t rotation) = 0;

    /**
     * IMS SetMute interface
     *
     * @param mute
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetMute(int32_t slotId, int32_t mute) = 0;

    /**
     * IMS GetMute interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetMute(int32_t slotId) = 0;

    /**
     * IMS GetEmergencyCallList interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetEmergencyCallList(int32_t slotId) = 0;

    /**
     * IMS InquireClip interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t InquireClip(int32_t slotId) = 0;

    /**
     * IMS SetClir interface
     *
     * @param slotId
     * @param action
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetClir(int32_t slotId, int32_t action) = 0;

    /**
     * IMS InquireClir interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t InquireClir(int32_t slotId) = 0;

    /**
     * IMS SetCallTransfer interface
     *
     * @param slotId
     * @param reason
     * @param mode
     * @param transferNum
     * @param classType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetCallTransfer(
        int32_t slotId, int32_t reason, int32_t mode, const std::string &transferNum, int32_t classType) = 0;

    /**
     * IMS GetCallTransfer interface
     *
     * @param slotId
     * @param reason
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetCallTransfer(int32_t slotId, int32_t reason) = 0;

    /**
     * IMS SetCallRestriction interface
     *
     * @param slotId
     * @param fac
     * @param mode
     * @param pw
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetCallRestriction(
        int32_t slotId, const std::string &fac, int32_t mode, const std::string &pw) = 0;

    /**
     * IMS GetCallRestriction interface
     *
     * @param slotId
     * @param fac
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetCallRestriction(int32_t slotId, const std::string &fac) = 0;

    /**
     * IMS SetCallWaiting interface
     *
     * @param slotId
     * @param activate
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t SetCallWaiting(int32_t slotId, bool activate) = 0;

    /**
     * IMS GetCallWaiting interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t GetCallWaiting(int32_t slotId) = 0;

    /**
     * Register CallBack
     *
     * @param sptr<ImsCallback>
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t RegisterCellularCallBack(const sptr<ImsCallback> &callback) = 0;

    /**
     * Is CellularCallBack Exists
     *
     * @return bool
     */
    virtual bool IsCallBackExists() = 0;

public:
    DECLARE_INTERFACE_DESCRIPTOR(u"OHOS.Telephony.ImsInterface");
};
} // namespace Telephony
} // namespace OHOS

#endif // TELEPHONY_IMS_INTERFACE_H
