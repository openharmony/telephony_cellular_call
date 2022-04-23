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

#ifndef IMS_CALL_H
#define IMS_CALL_H
#include <map>

#include "iremote_stub.h"
#include "iservice_registry.h"
#include "singleton.h"
#include "system_ability.h"
#include "system_ability_definition.h"
#include "event_runner.h"

#include "telephony_types.h"
#include "ims_core_service_stub.h"
#include "ims_call_interface.h"
#include "ims_call_stub.h"
#include "ims_call_handler.h"
#include "ims_call_register.h"
#include "ims_base.h"

namespace OHOS {
namespace Telephony {
class ImsCall : public ImsCallStub,
    public ImsBase<ImsCallHandler>,
    public std::enable_shared_from_this<ImsCall> {
public:
    ImsCall();

    virtual ~ImsCall();

    bool Init() override;

    /**
     * IMS Dial interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Dial(const ImsCallInfo &callInfo, CLIRMode mode) override;

    /**
     * IMS HangUp interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t HangUp(const ImsCallInfo &callInfo) override;

    /**
     * IMS Reject interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Reject(const ImsCallInfo &callInfo) override;

    /**
     * IMS Reject with reason interface
     *
     * @param ImsCallInfo
     * @param ImsRejectReason
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t RejectWithReason(const ImsCallInfo &callInfo, const ImsRejectReason &reason) override;

    /**
     * IMS Answer interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Answer(const ImsCallInfo &callInfo) override;

    /**
     * IMS HoldCall interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t HoldCall(int32_t slotId) override;

    /**
     * IMS UnHoldCall interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UnHoldCall(int32_t slotId) override;

    /**
     * IMS SwitchCall interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SwitchCall(int32_t slotId) override;

    /**
     * IMS CombineConference interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t CombineConference(int32_t slotId) override;

    /**
     * IMS InviteToConference interface
     *
     * @param slotId
     * @param numberList
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t InviteToConference(int32_t slotId, const std::vector<std::string> &numberList) override;

    /**
     * IMS KickOutFromConference interface
     *
     * @param slotId
     * @param numberList
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t KickOutFromConference(int32_t slotId, const std::vector<std::string> &numberList) override;

    /**
     * IMS UpdateImsCallMode interface
     *
     * @param ImsCallInfo
     * @param ImsCallMode
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateImsCallMode(const ImsCallInfo &callInfo, ImsCallMode mode) override;

    /**
     * IMS IsEmergencyPhoneNumber interface
     *
     * @param slotId
     * @param phoneNum
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t IsEmergencyPhoneNumber(int32_t slotId, const std::string &phoneNum) override;

    /**
     * Get Ims Calls Data Request
     *
     * @param slotId
     * @param lastCallsDataFlag
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag) override;

    /**
     * Get Last Call Fail Reason
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetLastCallFailReason(int32_t slotId) override;

    /**
     * IMS StartDtmf interface
     *
     * @param slotId
     * @param cDTMFCode
     * @param index
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StartDtmf(int32_t slotId, char cDtmfCode, int32_t index) override;

    /**
     * IMS SendDtmf interface
     *
     * @param slotId
     * @param cDtmfCode
     * @param index
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SendDtmf(int32_t slotId, char cDtmfCode, int32_t index) override;

    /**
     * IMS StopDtmf interface
     *
     * @param slotId
     * @param index
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StopDtmf(int32_t slotId, int32_t index) override;
    
    /**
     * IMS StartRtt interface
     *
     * @param slotId
     * @param msg
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StartRtt(int32_t slotId, const std::string &msg) override;

    /**
     * IMS StopRtt interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StopRtt(int32_t slotId) override;

    /**
     * IMS SetDomainPreferenceMode interface
     *
     * @param slotId
     * @param mode
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetDomainPreferenceMode(int32_t slotId, int32_t mode) override;

    /**
     * IMS GetDomainPreferenceMode interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetDomainPreferenceMode(int32_t slotId) override;

    /**
     * IMS SetLteImsSwitchStatus interface
     *
     * @param slotId
     * @param active 1: enable ims, 0: disable ims
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetLteImsSwitchStatus(int32_t slotId, int32_t active) override;

    /**
     * IMS GetLteImsSwitchStatus interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetLteImsSwitchStatus(int32_t slotId) override;

    /**
     * IMS SetImsConfig interface
     *
     * @param ImsConfigItem
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsConfig(ImsConfigItem item, const std::string &value) override;

    /**
     * IMS SetImsConfig interface
     *
     * @param ImsConfigItem
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsConfig(ImsConfigItem item, int32_t value) override;

    /**
     * IMS GetImsConfig interface
     *
     * @param ImsConfigItem
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsConfig(ImsConfigItem item) override;

    /**
     * IMS SetImsFeatureValue interface
     *
     * @param FeatureType
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsFeatureValue(FeatureType type, int32_t value) override;

    /**
     * IMS GetImsFeatureValue interface
     *
     * @param FeatureType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsFeatureValue(FeatureType type) override;

    /**
     * IMS SetImsSwitchEnhanceMode interface
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsSwitchEnhanceMode(bool value) override;

    /**
     * IMS GetImsSwitchEnhanceMode interface
     *
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsSwitchEnhanceMode() override;

    /**
     * IMS SetMute interface
     *
     * @param mute 0: not mute, 1:mute
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetMute(int32_t slotId, int32_t mute) override;

    /**
     * IMS GetMute interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetMute(int32_t slotId) override;

    /**
     * IMS GetEmergencyCallList interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetEmergencyCallList(int32_t slotId) override;

    /**
     * IMS CtrlCamera interface
     *
     * @param cameraId
     * @param callingUid
     * @param callingPid
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t CtrlCamera(const std::u16string &cameraId, int32_t callingUid, int32_t callingPid) override;

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
    int32_t SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height) override;

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
    int32_t SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height) override;

    /**
     * IMS SetCameraZoom interface
     *
     * @param zoomRatio
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCameraZoom(float zoomRatio) override;

    /**
     * IMS SetPauseImage interface
     *
     * @param path
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetPauseImage(const std::u16string &path) override;

    /**
     * IMS SetDeviceDirection interface
     *
     * @param rotation
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetDeviceDirection(int32_t rotation) override;

    /**
     * IMS GetClip interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetClip(int32_t slotId) override;

    /**
     * IMS SetClir interface
     *
     * @param slotId
     * @param action
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetClir(int32_t slotId, int32_t action) override;

    /**
     * IMS GetClir interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetClir(int32_t slotId) override;

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
    int32_t SetCallTransfer(
        int32_t slotId, int32_t reason, int32_t mode, const std::string &transferNum, int32_t classType) override;

    /**
     * IMS GetCallTransfer interface
     *
     * @param slotId
     * @param reason
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallTransfer(int32_t slotId, int32_t reason) override;

    /**
     * IMS SetCallRestriction interface
     *
     * @param slotId
     * @param fac
     * @param mode
     * @param pw
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCallRestriction(
        int32_t slotId, const std::string &fac, int32_t mode, const std::string &pw) override;

    /**
     * IMS GetCallRestriction interface
     *
     * @param slotId
     * @param fac
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallRestriction(int32_t slotId, const std::string &fac) override;

    /**
     * IMS SetCallWaiting interface
     *
     * @param slotId
     * @param activate 0: disabled, 1: enabled
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCallWaiting(int32_t slotId, bool activate) override;

    /**
     * IMS GetCallWaiting interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallWaiting(int32_t slotId) override;

    /**
     * Register CallBack
     *
     * @param sptr<ImsCallback>
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t RegisterImsCallCallback(const sptr<ImsCallCallbackInterface> &callback) override;

private:
    bool RegisterObserver() override;
    void SetSlotIds() override;
};
} // Telephony
} // OHOS
#endif // IMS_CALL_H
