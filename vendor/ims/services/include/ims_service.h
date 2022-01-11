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

#ifndef TELEPHONY_IMS_SERVICE_H
#define TELEPHONY_IMS_SERVICE_H

#include "singleton.h"
#include "event_runner.h"
#include "iremote_broker.h"
#include "system_ability.h"

#include "telephony_log_wrapper.h"
#include "ims_handler.h"
#include "ims_stub.h"

namespace OHOS {
namespace Telephony {
enum class ServiceRunningState { STATE_STOPPED, STATE_RUNNING };

class ImsService : public SystemAbility, public ImsStub, public std::enable_shared_from_this<ImsService> {
    DECLARE_DELAYED_SINGLETON(ImsService)
    DECLEAR_SYSTEM_ABILITY(ImsService)

public:
    /**
     * service OnStart
     */
    void OnStart() override;

    /**
     * service OnStop
     */
    void OnStop() override;

    /**
     * Register Handler
     */
    void RegisterHandler();

    /**
     * Get Handler
     * @return ImsHandler
     */
    std::shared_ptr<ImsHandler> GetHandler(int32_t slot);

    /**
     * IMS Stub dial interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Dial(const ImsCallInfo &callInfo, CLIRMode mode) override;

    /**
     * IMS Stub HangUp interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t HangUp(const ImsCallInfo &callInfo) override;

    /**
     * IMS Stub Reject interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Reject(const ImsCallInfo &callInfo) override;

    /**
     * IMS Stub Answer interface
     *
     * @param ImsCallInfo
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Answer(const ImsCallInfo &callInfo) override;

    /**
     * IMS Stub HoldCall interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t HoldCall(int32_t slotId) override;

    /**
     * IMS Stub UnHoldCall interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UnHoldCall(int32_t slotId) override;

    /**
     * IMS Stub SwitchCall interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SwitchCall(int32_t slotId) override;

    /**
     * IMS Stub CombineConference interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t CombineConference(int32_t slotId) override;

    /**
     * IMS Stub InviteToConference interface
     *
     * @param numberList
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t InviteToConference(int32_t slotId, const std::vector<std::string> &numberList) override;

    /**
     * IMS Stub KickOutFromConference interface
     *
     * @param numberList
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t KickOutFromConference(int32_t slotId, const std::vector<std::string> &numberList) override;

    /**
     * IMS Stub UpdateCallMediaMode interface
     *
     * @param ImsCallInfo
     * @param CallMediaMode
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UpdateCallMediaMode(const ImsCallInfo &callInfo, CallMediaMode mode) override;

    /**
     * IMS Stub IsEmergencyPhoneNumber interface
     *
     * @param phoneNum
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t IsEmergencyPhoneNumber(int32_t slotId, const std::string &phoneNum) override;

    /**
     * IMS Stub StartDtmf interface
     *
     * @param cDtmfCode
     * @param index
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StartDtmf(int32_t slotId, char cDtmfCode, int32_t index) override;

    /**
     * IMS Stub SendDtmf interface
     *
     * @param cDtmfCode
     * @param index
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SendDtmf(int32_t slotId, char cDtmfCode, int32_t index) override;

    /**
     * IMS Stub StopDtmf interface
     *
     * @param index
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StopDtmf(int32_t slotId, int32_t index) override;

    /**
     * IMS Stub StartRtt interface
     *
     * @param msg
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StartRtt(int32_t slotId, const std::string &msg) override;

    /**
     * IMS Stub StopRtt interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t StopRtt(int32_t slotId) override;

    /**
     * IMS Stub SetDomainPreferenceMode interface
     *
     * @param mode
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetDomainPreferenceMode(int32_t mode) override;

    /**
     * IMS Stub GetDomainPreferenceMode interface
     *
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetDomainPreferenceMode() override;

    /**
     * IMS Stub SetLteImsSwitchStatus interface
     *
     * @param active
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetLteImsSwitchStatus(bool active) override;

    /**
     * IMS Stub GetLteImsSwitchStatus interface
     *
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetLteImsSwitchStatus() override;

    /**
     * IMS Stub SetImsConfig interface
     *
     * @param ImsConfigItem
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsConfig(ImsConfigItem item, const std::string &value) override;

    /**
     * IMS Stub SetImsConfig interface
     *
     * @param ImsConfigItem
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsConfig(ImsConfigItem item, int32_t value) override;

    /**
     * IMS Stub GetImsConfig interface
     *
     * @param ImsConfigItem
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsConfig(ImsConfigItem item) override;

    /**
     * IMS Stub SetImsFeatureValue interface
     *
     * @param FeatureType
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetImsFeatureValue(FeatureType type, int32_t value) override;

    /**
     * IMS Stub GetImsFeatureValue interface
     *
     * @param FeatureType
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsFeatureValue(FeatureType type) override;

    /**
     * IMS Stub SetVolteEnhanceMode interface
     *
     * @param value
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetVolteEnhanceMode(bool value) override;

    /**
     * IMS Stub GetVolteEnhanceMode interface
     *
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetVolteEnhanceMode() override;

    /**
     * IMS Stub CtrlCamera interface
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
     * IMS Stub SetPreviewWindow interface
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
     * IMS Stub SetDisplayWindow interface
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
     * IMS Stub SetCameraZoom interface
     *
     * @param zoomRatio
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCameraZoom(float zoomRatio) override;

    /**
     * IMS Stub SetPauseImage interface
     *
     * @param path
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetPauseImage(const std::u16string &path) override;

    /**
     * IMS Stub SetDeviceDirection interface
     *
     * @param rotation
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetDeviceDirection(int32_t rotation) override;

    /**
     * IMS Stub SetMute interface
     *
     * @param mute
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetMute(int32_t slotId, int32_t mute) override;

    /**
     * IMS Stub GetMute interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetMute(int32_t slotId) override;

    /**
     * IMS Stub GetEmergencyCallList interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetEmergencyCallList(int32_t slotId) override;

    /**
     * IMS Stub InquireClip interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t InquireClip(int32_t slotId) override;

    /**
     * IMS Stub SetClir interface
     *
     * @param slotId
     * @param action
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetClir(int32_t slotId, int32_t action) override;

    /**
     * IMS Stub InquireClir interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t InquireClir(int32_t slotId) override;

    /**
     * IMS Stub SetCallTransfer interface
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
     * IMS Stub GetCallTransfer interface
     *
     * @param slotId
     * @param reason
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallTransfer(int32_t slotId, int32_t reason) override;

    /**
     * IMS Stub SetCallRestriction interface
     *
     * @param slotId
     * @param fac
     * @param mode
     * @param pw
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCallRestriction(int32_t slotId, const std::string &fac, int32_t mode, const std::string &pw) override;

    /**
     * IMS Stub GetCallRestriction interface
     *
     * @param slotId
     * @param fac
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallRestriction(int32_t slotId, const std::string &fac) override;

    /**
     * IMS Stub SetCallWaiting interface
     *
     * @param slotId
     * @param activate
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SetCallWaiting(int32_t slotId, bool activate) override;

    /**
     * IMS Stub GetCallWaiting interface
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

    /**
     * IMS Stub GetImsCallsDataRequest interface
     *
     * @param slotId
     * @param lastCallsDataFlag
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag) override;

    /**
     * IMS Stub GetCallFailReason interface
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetCallFailReason(int32_t slotId) override;

public:
    std::map<int32_t, std::shared_ptr<ImsHandler>> handlerMap_;

private:
    /**
     * Init service
     * @return whether init success
     */
    bool Init();

    /**
     * Register Handler
     */
    void RegisterCoreServiceHandler();

    /**
     * Create Handler
     */
    void CreateHandler();

    /**
     * Handler Reset UnRegister
     */
    void HandlerResetUnRegister();

    /**
     * ThreadRegister
     */
    void AsynchronousRegister();

private:
    ImsRilRequest request_;
    ServiceRunningState state_;
    const uint32_t CONNECT_MAX_TRY_COUNT = 20;
    const uint32_t CONNECT_SERVICE_WAIT_TIME = 2000; // ms
    std::shared_ptr<AppExecFwk::EventRunner> eventLoop_;
};
} // namespace Telephony
} // namespace OHOS

#endif // TELEPHONY_IMS_SERVICE_H
