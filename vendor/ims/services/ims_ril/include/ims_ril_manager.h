/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License", const AppExecFwk::InnerEvent::Pointer &response);
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

#ifndef IMS_RIL_MANAGER_H
#define IMS_RIL_MANAGER_H
#include <memory>
#include <unordered_map>

#include "singleton.h"
#include "iremote_stub.h"
#include "event_handler.h"
#include "ims_call_types.h"
#include "ims_sms_types.h"
#include "cellular_call_data_struct.h"

namespace OHOS {
namespace Telephony {
class ImsRilManager {
    DECLARE_DELAYED_SINGLETON(ImsRilManager)
public:
    bool Init();

    /******************* ImsCoreService *******************/
    int32_t GetImsRegistrationStatus(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);

    /******************* ImsCall *******************/
    int32_t Dial(const ImsCallInfo &callInfo, CLIRMode mode, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t HangUp(const ImsCallInfo &callInfo, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t Reject(const ImsCallInfo &callInfo, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t RejectWithReason(const ImsCallInfo &callInfo, const ImsRejectReason &reason,
                             const AppExecFwk::InnerEvent::Pointer &response);
    int32_t Answer(const ImsCallInfo &callInfo, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t HoldCall(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t UnHoldCall(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SwitchCall(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t CombineConference(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t InviteToConference(int32_t slotId, const std::vector<std::string> &numberList,
        const AppExecFwk::InnerEvent::Pointer &response);
    int32_t KickOutFromConference(int32_t slotId, const std::vector<std::string> &numberList,
        const AppExecFwk::InnerEvent::Pointer &response);
    int32_t UpdateImsCallMode(const ImsCallInfo &callInfo, ImsCallMode mode,
        const AppExecFwk::InnerEvent::Pointer &response);
    int32_t IsEmergencyPhoneNumber(int32_t slotId, const std::string &phoneNum,
        const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag,
        const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetLastCallFailReason(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t StartDtmf(int32_t slotId, char cDtmfCode, int32_t index, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SendDtmf(int32_t slotId, char cDtmfCode, int32_t index, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t StopDtmf(int32_t slotId, int32_t index, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t StartRtt(int32_t slotId, const std::string &msg, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t StopRtt(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetDomainPreferenceMode(int32_t slotId, int32_t mode, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetDomainPreferenceMode(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetLteImsSwitchStatus(int32_t slotId, bool active, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetLteImsSwitchStatus(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetImsConfig(ImsConfigItem item, const std::string &value,
        const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetImsConfig(ImsConfigItem item, int32_t value, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetImsConfig(ImsConfigItem item, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetImsFeatureValue(FeatureType type, int32_t value, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetImsFeatureValue(FeatureType type, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetImsSwitchEnhanceMode(bool value, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetImsSwitchEnhanceMode(const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetMute(int32_t slotId, int32_t mute, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetMute(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetEmergencyCallList(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t CtrlCamera(const std::u16string &cameraId, int32_t callingUid, int32_t callingPid,
        const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height,
        const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height,
        const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetCameraZoom(float zoomRatio, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetPauseImage(const std::u16string &path, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetDeviceDirection(int32_t rotation, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetClip(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetClir(int32_t slotId, int32_t action, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetClir(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetCallTransfer(
    int32_t slotId, int32_t reason, int32_t mode, const std::string &transferNum, int32_t classType,
        const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetCallTransfer(int32_t slotId, int32_t reason, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetCallRestriction(
    int32_t slotId, const std::string &fac, int32_t mode, const std::string &pw,
        const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetCallRestriction(int32_t slotId, const std::string &fac,
        const AppExecFwk::InnerEvent::Pointer &response);
    int32_t SetCallWaiting(int32_t slotId, bool activate, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t GetCallWaiting(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);

    /******************* ImsSms *******************/
    int32_t ImsSendMessage(int32_t slotId, const ImsMessageInfo &imsMessageInfo,
                           const AppExecFwk::InnerEvent::Pointer &response);
    int32_t ImsSetSmsConfig(int32_t slotId, int32_t imsSmsConfig, const AppExecFwk::InnerEvent::Pointer &response);
    int32_t ImsGetSmsConfig(int32_t slotId, const AppExecFwk::InnerEvent::Pointer &response);

    int32_t ImsRegisterObserver(int32_t slotId, int32_t what, const std::shared_ptr<AppExecFwk::EventHandler> handler);
};
} // Telephony
} // OHOS
#endif // IMS_RIL_MANAGER_H