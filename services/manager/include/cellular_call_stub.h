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

#ifndef CELLULAR_CALL_STUB_H
#define CELLULAR_CALL_STUB_H

#include "cellular_call_data_struct.h"
#include "cellular_call_interface.h"
#include "telephony_log_wrapper.h"
#include "iremote_stub.h"
#include "cs_control.h"
#include "ims_control.h"
#include "cellular_call_config.h"
#include "cellular_call_handler.h"
#include "cellular_call_supplement.h"

namespace OHOS {
namespace Telephony {
class CellularCallStub : public IRemoteStub<CellularCallInterface> {
public:
    /**
     * CellularCallStub Constructors
     */
    CellularCallStub();

    /**
     * ~CellularCallStub Destructor
     */
    virtual ~CellularCallStub();

    /**
     * OnRemoteRequest
     *
     * @param code
     * @param data
     * @param reply
     * @param option
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    virtual int32_t OnRemoteRequest(
        uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option) override;

    /**
     * dial
     *
     * @param CellularCallInfo, dial param.
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Dial(const CellularCallInfo &callInfo) override;

    /**
     * HangUp.
     *
     * @param CellularCallInfo, HangUp param.
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t HangUp(const CellularCallInfo &callInfo) override;

    /**
     * Reject.
     *
     * @param CellularCallInfo, Reject param.
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Reject(const CellularCallInfo &callInfo) override;

    /**
     * Answer.
     *
     * @param CellularCallInfo, Answer param.
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t Answer(const CellularCallInfo &callInfo) override;

    /**
     * HoldCall.
     *
     * @param CellularCallInfo, Hold param.
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t HoldCall(const CellularCallInfo &callInfo) override;

    /**
     * UnHoldCall.
     *
     * @param CellularCallInfo, UnHold param.
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UnHoldCall(const CellularCallInfo &callInfo) override;

    /**
     * SwitchCall.
     *
     * @param CellularCallInfo, SwitchCall param.
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t SwitchCall(const CellularCallInfo &callInfo) override;

    /**
     * IsEmergencyPhoneNumber.
     *
     * @param phone number.
     * @param slotId.
     * @param error Code.
     * @return Is Urgent Call.
     */
    int32_t IsEmergencyPhoneNumber(const std::string &phoneNum, int32_t slotId, int32_t &errorCode) override;

    /**
     * Merge into multiple calls
     *
     * @param CellularCallInfo
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t CombineConference(const CellularCallInfo &callInfo) override;

    /**
     * SeparateConference.
     *
     * @param CellularCallInfo
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SeparateConference(const CellularCallInfo &callInfo) override;

    /**
     * CallSupplement.
     *
     * @param CallSupplementType
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t CallSupplement(CallSupplementType type) override;

    /**
     * Register CallManager CallBack
     *
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t RegisterCallManagerCallBack(const sptr<ICallStatusCallback> &callback) override;

    /**
     * UnRegister CallManager CallBack
     *
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UnRegisterCallManagerCallBack() override;

    /**
     * StartDtmf.
     *
     * @param Dtmf Code.
     * @param CellularCallInfo
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t StartDtmf(char cDtmfCode, const CellularCallInfo &callInfo) override;

    /**
     * StopDtmf.
     *
     * @param CellularCallInfo
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t StopDtmf(const CellularCallInfo &callInfo) override;

    /**
     * SendDtmf.
     *
     * @param Dtmf Code.
     * @param CellularCallInfo
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SendDtmf(char cDtmfCode, const CellularCallInfo &callInfo) override;

    /**
     * Send Dtmf String.
     * @param Dtmf Code string.
     * @param phoneNum.
     * @param switchOn.
     * @param switchOff.
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SendDtmfString(
        const std::string &dtmfCodeStr, const std::string &phoneNum, int32_t switchOn, int32_t switchOff) override;

    /**
     * Set Call Transfer
     * @param CallTransferInfo
     * @param slot Id
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetCallTransferInfo(const CallTransferInfo &cfInfo, int32_t slotId) override;

    /**
     * Inquire Call Transfer
     * @param CallTransferType
     * @param slot Id
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t GetCallTransferInfo(CallTransferType type, int32_t slotId) override;

    /**
     * Set Call Waiting
     * @param activate
     * @param slot Id
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetCallWaiting(bool activate, int32_t slotId) override;

    /**
     * Inquire Call Waiting
     * @param slot Id
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t GetCallWaiting(int32_t slotId) override;

    /**
     * Set Call Restriction
     * @param CallRestrictionInfo
     * @param slot Id
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetCallRestriction(const CallRestrictionInfo &crInfo, int32_t slotId) override;

    /**
     * Inquire Call Restriction
     * @param CallRestrictionType
     * @param slot Id
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t GetCallRestriction(CallRestrictionType facType, int32_t slotId) override;

    /**
     * Set Call Preference Mode
     * @param slotId
     * @param mode
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetCallPreferenceMode(int32_t slotId, int32_t mode) override;

    /**
     * Get Call Preference Mode
     * @param slotId
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t GetCallPreferenceMode(int32_t slotId) override;

    /**
     * Set Lte Ims Switch Status
     * @param slotId
     * @param active
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetLteImsSwitchStatus(int32_t slotId, bool active) override;

    /**
     * Get Lte Ims Switch Status
     * @param slotId
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t GetLteImsSwitchStatus(int32_t slotId) override;

    /**
     * CtrlCamera
     *
     * @param cameraId
     * @param callingPackage
     * @param callingUid
     * @param callingPid
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t CtrlCamera(const std::u16string &cameraId, const std::u16string &callingPackage, int32_t callingUid,
        int32_t callingPid) override;

    /**
     * SetPreviewWindow
     *
     * @param x
     * @param y
     * @param z
     * @param width
     * @param height
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height) override;

    /**
     * SetDisplayWindow
     *
     * @param x
     * @param y
     * @param z
     * @param width
     * @param height
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height) override;

    /**
     * SetCameraZoom
     *
     * @param zoomRatio
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetCameraZoom(float zoomRatio) override;

    /**
     * SetPauseImage
     *
     * @param path
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetPauseImage(const std::u16string &path) override;

    /**
     * SetDeviceDirection
     *
     * @param rotation
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t SetDeviceDirection(int32_t rotation) override;

    /**
     * Is need choose IMS for execute
     *
     * @return bool
     */
    bool IsNeedIms() const;

    /**
     * Get CSControl
     * @param slotId
     * @return shared_ptr CSControl
     */
    std::shared_ptr<CSControl> GetCsControl(int32_t slotId);

    /**
     * Get IMControl
     * @param slotId
     * @return shared_ptr CSControl
     */
    std::shared_ptr<IMSControl> GetImsControl(int32_t slotId);

public:
    std::map<int32_t, std::shared_ptr<CellularCallHandler>> handlerMap_;

private:
    /**
     * On Dial Inner.
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnDialInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On HangUp Inner.
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnHangUpInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Reject Inner.
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnRejectInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Answer Inner.
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnAnswerInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Is Emergency Call Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnIsEmergencyPhoneNumberInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On HoldCall Inner.
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnHoldCallInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On UnHoldCall Inner.
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUnHoldCallInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SwitchCall Inner.
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSwitchCallInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On CombineConference Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnCombineConferenceInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SeparateConference Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnSeparateConferenceInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On CallSupplement Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnCallSupplementInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Register Call Back Inner.
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnRegisterCallBackInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On UnRegister Call Back Inner.
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUnRegisterCallBackInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On start Dtmf Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnStartDtmfInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On stop Dtmf Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnStopDtmfInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On send Dtmf Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnSendDtmfInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On send Dtmf String Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnSendDtmfStringInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Set Call Transfer Inner.
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnSetCallTransferInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Inquire Call Transfer Inner.
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnGetCallTransferInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Set Call Waiting
     * @param data  send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnSetCallWaitingInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Inquire Call Waiting
     * @param data  send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnGetCallWaitingInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Set Call Restriction
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnSetCallRestrictionInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Get Call Restriction
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnGetCallRestrictionInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Set Call Preference Mode
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnSetCallPreferenceModeInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Get Call Preference Mode
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnGetCallPreferenceModeInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Set Lte Ims Switch Status
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnSetLteImsSwitchStatusInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Get Lte Ims Switch Status
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnGetLteImsSwitchStatusInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Ctrl Camera Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnCtrlCameraInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Set Preview Window Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnSetPreviewWindowInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Set Display Window Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnSetDisplayWindowInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Set Camera Zoom Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnSetCameraZoomInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Set Pause Image Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnSetPauseImageInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Set Device Direction Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns kTelephonyNoErr on success, others on failure.
     */
    int32_t OnSetDeviceDirectionInner(MessageParcel &data, MessageParcel &reply);

    /**
     * init Control
     */
    void Init();

    /**
     * Is Valid Slot Id
     * @param slotId
     * @return bool
     */
    bool IsValidSlotId(int32_t slotId) const;

    /**
     * Get Handler
     * @param slotId
     * @return CellularCallHandler
     */
    std::shared_ptr<CellularCallHandler> GetHandler(int32_t slotId);

private:
    const int32_t MAX_SIZE = 10;
    CellularCallConfig config_;
    CellularCallSupplement cellularCallSupplement_;
    using RequestFuncType = int32_t (CellularCallStub::*)(MessageParcel &data, MessageParcel &reply);
    std::map<OperationType, RequestFuncType> requestFuncMap_;
    std::map<int32_t, std::shared_ptr<CSControl>> csControlMap_;
    std::map<int32_t, std::shared_ptr<IMSControl>> imsControlMap_;
    int32_t slotId_ = CoreManager::DEFAULT_SLOT_ID;
    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "CellularCallStub"};
};
} // namespace Telephony
} // namespace OHOS

#endif // CELLULAR_CALL_STUB_H
