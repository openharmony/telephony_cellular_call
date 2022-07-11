/*
 * Copyright (C) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef TELEPHONY_IMS_UNIT_TEST_H
#define TELEPHONY_IMS_UNIT_TEST_H

#include "gtest/gtest.h"

#include "ims_interface.h"

namespace OHOS {
namespace Telephony {
class ImsUnitTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();

    int32_t Dial(const sptr<ImsInterface> &telephonyService) const;
    int32_t HangUp(const sptr<ImsInterface> &telephonyService) const;
    int32_t Reject(const sptr<ImsInterface> &telephonyService) const;
    int32_t Answer(const sptr<ImsInterface> &telephonyService) const;
    int32_t HoldCall(const sptr<ImsInterface> &telephonyService) const;
    int32_t UnHoldCall(const sptr<ImsInterface> &telephonyService) const;
    int32_t SwitchCall(const sptr<ImsInterface> &telephonyService) const;
    int32_t CombineConference(const sptr<ImsInterface> &telephonyService) const;
    int32_t InviteToConference(const sptr<ImsInterface> &telephonyService) const;
    int32_t KickOutFromConference(const sptr<ImsInterface> &telephonyService) const;
    int32_t UpdateImsCallMode(const sptr<ImsInterface> &telephonyService) const;
    int32_t IsEmergencyPhoneNumber(const sptr<ImsInterface> &telephonyService) const;
    int32_t GetCallFailReason(const sptr<ImsInterface> &telephonyService) const;
    int32_t StartDtmf(const sptr<ImsInterface> &telephonyService) const;
    int32_t SendDtmf(const sptr<ImsInterface> &telephonyService) const;
    int32_t StopDtmf(const sptr<ImsInterface> &telephonyService) const;
    int32_t StartRtt(const sptr<ImsInterface> &telephonyService) const;
    int32_t StopRtt(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetDomainPreferenceMode(const sptr<ImsInterface> &telephonyService) const;
    int32_t GetDomainPreferenceMode(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetImsSwitchStatus(const sptr<ImsInterface> &telephonyService) const;
    int32_t GetImsSwitchStatus(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetImsConfigString(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetImsConfigInt(const sptr<ImsInterface> &telephonyService) const;
    int32_t GetImsConfig(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetImsFeatureValue(const sptr<ImsInterface> &telephonyService) const;
    int32_t GetImsFeatureValue(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetImsSwitchEnhanceMode(const sptr<ImsInterface> &telephonyService) const;
    int32_t GetImsSwitchEnhanceMode(const sptr<ImsInterface> &telephonyService) const;
    int32_t CtrlCamera(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetPreviewWindow(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetDisplayWindow(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetCameraZoom(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetPauseImage(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetDeviceDirection(const sptr<ImsInterface> &telephonyService) const;
    int32_t RegisterCellularCallBack(const sptr<ImsInterface> &telephonyService) const;
    int32_t IsCallBackExists(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetMute(const sptr<ImsInterface> &telephonyService) const;
    int32_t GetMute(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetCallTransfer(const sptr<ImsInterface> &telephonyService) const;
    int32_t GetCallTransfer(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetCallRestriction(const sptr<ImsInterface> &telephonyService) const;
    int32_t GetCallRestriction(const sptr<ImsInterface> &telephonyService) const;
    int32_t SetCallWaiting(const sptr<ImsInterface> &telephonyService) const;
    int32_t GetCallWaiting(const sptr<ImsInterface> &telephonyService) const;

    int32_t InputNumForInterface(const sptr<ImsInterface> &telephonyService) const;

private:
    using RequestFuncType = int32_t (ImsUnitTest::*)(const sptr<ImsInterface> &telephonyService) const;
    std::map<int32_t, RequestFuncType> requestFuncMap_;
};
} // namespace Telephony
} // namespace OHOS

#endif // TELEPHONY_IMS_UNIT_TEST_H
