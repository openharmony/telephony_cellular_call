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

#ifndef IMS_PROXY_H
#define IMS_PROXY_H

#include "ims_interface.h"
#include "iremote_proxy.h"

#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
class ImsProxy : public IRemoteProxy<ImsInterface> {
public:
    /**
     * ImsProxy
     *
     * @param impl
     */
    explicit ImsProxy(const sptr<IRemoteObject> &impl) : IRemoteProxy<ImsInterface>(impl) {}

    /**
     * ~ImsProxy
     *
     */
    ~ImsProxy() = default;

    /**
     * IMS proxy dial interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Dial(const ImsCallInfo &callInfo, CLIRMode mode) override;

    /**
     * IMS proxy HangUp interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t HangUp(const ImsCallInfo &callInfo) override;

    /**
     * IMS proxy Reject interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Reject(const ImsCallInfo &callInfo) override;

    /**
     * IMS proxy Answer interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Answer(const ImsCallInfo &callInfo) override;

    /**
     * IMS proxy HoldCall interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t HoldCall(int32_t slotId) override;

    /**
     * IMS proxy UnHoldCall interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UnHoldCall(int32_t slotId) override;

    /**
     * IMS proxy SwitchCall interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SwitchCall(int32_t slotId) override;

    /**
     * IMS proxy CombineConference interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t CombineConference(int32_t slotId) override;

    /**
     * IMS proxy InviteToConference interface
     *
     * @param numberList
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t InviteToConference(int32_t slotId, const std::vector<std::string> &numberList) override;

    /**
     * IMS proxy KickOutFromConference interface
     *
     * @param numberList
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t KickOutFromConference(int32_t slotId, const std::vector<std::string> &numberList) override;

    /**
     * IMS proxy UpdateCallMediaMode interface
     *
     * @param ImsCallInfo
     * @param CallMediaMode
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallMediaMode(const ImsCallInfo &callInfo, CallMediaMode mode) override;

    /**
     * IMS proxy IsEmergencyPhoneNumber interface
     *
     * @param phoneNum
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t IsEmergencyPhoneNumber(int32_t slotId, const std::string &phoneNum) override;

    /**
     * IMS proxy GetImsCallsDataRequest interface
     *
     * @param slotId
     * @param lastCallsDataFlag
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag) override;

    /**
     * IMS proxy GetCallFailReason interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallFailReason(int32_t slotId) override;

    /**
     * IMS proxy StartDtmf interface
     *
     * @param cDtmfCode
     * @param index
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StartDtmf(int32_t slotId, char cDtmfCode, int32_t index) override;

    /**
     * IMS proxy SendDtmf interface
     *
     * @param cDtmfCode
     * @param index
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SendDtmf(int32_t slotId, char cDtmfCode, int32_t index) override;

    /**
     * IMS proxy StopDtmf interface
     *
     * @param index
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StopDtmf(int32_t slotId, int32_t index) override;

    /**
     * IMS proxy StartRtt interface
     *
     * @param msg
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StartRtt(int32_t slotId, const std::string &msg) override;

    /**
     * IMS proxy StopRtt interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StopRtt(int32_t slotId) override;

    /**
     * IMS proxy SetDomainPreferenceMode interface
     *
     * @param mode
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetDomainPreferenceMode(int32_t mode) override;

    /**
     * IMS proxy GetDomainPreferenceMode interface
     *
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetDomainPreferenceMode() override;

    /**
     * IMS proxy SetLteImsSwitchStatus interface
     *
     * @param active
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetLteImsSwitchStatus(bool active) override;

    /**
     * IMS proxy GetLteImsSwitchStatus interface
     *
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetLteImsSwitchStatus() override;

    /**
     * IMS proxy SetImsConfig interface
     *
     * @param ImsConfigItem
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsConfig(ImsConfigItem item, const std::string &value) override;

    /**
     * IMS proxy SetImsConfig interface
     *
     * @param ImsConfigItem
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsConfig(ImsConfigItem item, int32_t value) override;

    /**
     * IMS proxy GetImsConfig interface
     *
     * @param ImsConfigItem
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsConfig(ImsConfigItem item) override;

    /**
     * IMS proxy SetImsFeatureValue interface
     *
     * @param FeatureType
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsFeatureValue(FeatureType type, int32_t value) override;

    /**
     * IMS proxy GetImsFeatureValue interface
     *
     * @param FeatureType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsFeatureValue(FeatureType type) override;

    /**
     * IMS proxy SetVolteEnhanceMode interface
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetVolteEnhanceMode(bool value) override;

    /**
     * IMS proxy GetVolteEnhanceMode interface
     *
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetVolteEnhanceMode() override;

    /**
     * IMS proxy CtrlCamera interface
     *
     * @param cameraId
     * @param callingPackage
     * @param callingUid
     * @param callingPid
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t CtrlCamera(const std::u16string &cameraId, const std::u16string &callingPackage, int32_t callingUid,
        int32_t callingPid) override;

    /**
     * IMS proxy SetPreviewWindow interface
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
     * IMS proxy SetDisplayWindow interface
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
     * IMS proxy SetCameraZoom interface
     *
     * @param zoomRatio
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCameraZoom(float zoomRatio) override;

    /**
     * IMS proxy SetPauseImage interface
     *
     * @param path
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetPauseImage(const std::u16string &path) override;

    /**
     * IMS proxy SetDeviceDirection interface
     *
     * @param rotation
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetDeviceDirection(int32_t rotation) override;

    /**
     * IMS proxy SetMute interface
     *
     * @param mute
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetMute(int32_t slotId, int32_t mute) override;

    /**
     * IMS proxy GetMute interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetMute(int32_t slotId) override;

    /**
     * IMS proxy GetEmergencyCallList interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetEmergencyCallList(int32_t slotId) override;

    /**
     * IMS proxy InquireClip interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t InquireClip(int32_t slotId) override;

    /**
     * IMS proxy SetClir interface
     *
     * @param slotId
     * @param action
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetClir(int32_t slotId, int32_t action) override;

    /**
     * IMS proxy InquireClir interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t InquireClir(int32_t slotId) override;

    /**
     * IMS proxy SetCallTransfer interface
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
     * IMS proxy GetCallTransfer interface
     *
     * @param slotId
     * @param reason
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallTransfer(int32_t slotId, int32_t reason) override;

    /**
     * IMS proxy SetCallRestriction interface
     *
     * @param slotId
     * @param fac
     * @param mode
     * @param pw
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCallRestriction(int32_t slotId, const std::string &fac, int32_t mode, const std::string &pw) override;

    /**
     * IMS proxy GetCallRestriction interface
     *
     * @param slotId
     * @param fac
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallRestriction(int32_t slotId, const std::string &fac) override;

    /**
     * IMS proxy SetCallWaiting interface
     *
     * @param slotId
     * @param activate
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCallWaiting(int32_t slotId, bool activate) override;

    /**
     * IMS proxy GetCallWaiting interface
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
    int32_t RegisterCellularCallBack(const sptr<ImsCallback> &callback) override;

    /**
     * Is CellularCallBack Exists
     *
     * @return bool
     */
    bool IsCallBackExists() override;

private:
    static inline BrokerDelegator<ImsProxy> delegator_;
};
} // namespace Telephony
} // namespace OHOS
#endif // CELLULAR_CALL_PROXY_H
