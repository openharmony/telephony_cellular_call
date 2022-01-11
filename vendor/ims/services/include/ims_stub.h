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

#ifndef IMS_STUB_H
#define IMS_STUB_H

#include <map>

#include "ims_interface.h"
#include "telephony_log_wrapper.h"
#include "iremote_stub.h"
#include "ims_ril_request.h"

namespace OHOS {
namespace Telephony {
class ImsStub : public IRemoteStub<ImsInterface> {
public:
    /**
     * ImsStub Constructors
     */
    ImsStub();

    /**
     * ~ImsStub Destructor
     */
    virtual ~ImsStub();

    /**
     * OnRemoteRequest
     *
     * @param code
     * @param data
     * @param reply
     * @param option
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option) override;

private:
    /**
     * On Dial Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnDialInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On HangUp Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnHangUpInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Reject Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnRejectInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On Answer Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnAnswerInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On HoldCall Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnHoldCallInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On UnHoldCall Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUnHoldCallInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SwitchCallInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSwitchCallInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On CombineConferenceInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnCombineConferenceInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On InviteToConferenceInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnInviteToConferenceInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On KickOutFromConferenceInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnKickOutFromConferenceInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On UpdateCallMediaModeInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnUpdateCallMediaModeInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On IsEmergencyPhoneNumberInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnIsEmergencyPhoneNumberInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On StartDtmfInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnStartDtmfInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SendDtmfInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSendDtmfInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On StopDtmfInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnStopDtmfInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On OnStartRttInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnStartRttInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On OnStopRttInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnStopRttInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetDomainPreferenceModeInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetDomainPreferenceModeInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On GetDomainPreferenceModeInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnGetDomainPreferenceModeInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetLteImsSwitchStatusInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetLteImsSwitchStatusInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On GetLteImsSwitchStatusInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnGetLteImsSwitchStatusInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetImsConfigStringInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetImsConfigStringInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetImsConfigIntInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetImsConfigIntInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On GetImsConfigInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnGetImsConfigInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetImsFeatureValueInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetImsFeatureValueInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On GetImsFeatureValueInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnGetImsFeatureValueInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetVolteEnhanceModeInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetVolteEnhanceModeInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On GetVolteEnhanceModeInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnGetVolteEnhanceModeInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On CtrlCameraInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnCtrlCameraInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetPreviewWindowInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetPreviewWindowInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetDisplayWindowInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetDisplayWindowInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetCameraZoomInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetCameraZoomInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetPauseImageInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetPauseImageInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetDeviceDirectionInner Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetDeviceDirectionInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On RegisterCallBack Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnRegisterCellularCallBackInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On IsCallBackExists Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnIsCallBackExistsInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On GetImsDataRequest Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnGetImsCallsDataRequestInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetMute Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetMuteInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On GetMute Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnGetMuteInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetMute Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnGetEmergencyCallListInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On GetCallFailReason Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnGetCallFailReasonInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On InquireClip Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnInquireClipInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetClir Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetClirInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On InquireClir Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnInquireClirInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetCallTransfer Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetCallTransferInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On GetCallTransfer Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnGetCallTransferInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetCallRestriction Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetCallRestrictionInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On GetCallRestriction Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnGetCallRestrictionInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On SetCallWaiting Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnSetCallWaitingInner(MessageParcel &data, MessageParcel &reply);

    /**
     * On GetCallWaiting Inner
     *
     * @param data send data
     * @param reply Received data
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t OnGetCallWaitingInner(MessageParcel &data, MessageParcel &reply);

    /**
     * InitBasicCallFuncMap.
     */
    void InitBasicCallFuncMap();

    /**
     * InitSupportCallFuncMap
     */
    void InitSupportCallFuncMap();

private:
    using RequestFuncType = int32_t (ImsStub::*)(MessageParcel &data, MessageParcel &reply);
    std::map<uint32_t, RequestFuncType> requestFuncMap_;
};
} // namespace Telephony
} // namespace OHOS

#endif // IMS_STUB_H
