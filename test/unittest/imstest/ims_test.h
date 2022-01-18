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

#ifndef TELEPHONY_IMS_TEST_H
#define TELEPHONY_IMS_TEST_H

#include "gtest/gtest.h"

#include "cellular_call_interface.h"

namespace OHOS {
namespace Telephony {
class ImsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();

    int32_t SetDomainPreferenceMode(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t GetDomainPreferenceMode(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetLteImsSwitchStatus(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t GetLteImsSwitchStatus(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetImsConfigString(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetImsConfigInt(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t GetImsConfig(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetImsFeatureValue(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t GetImsFeatureValue(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetImsSwitchEnhanceMode(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t GetImsSwitchEnhanceMode(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t CtrlCamera(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetPreviewWindow(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetDisplayWindow(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetCameraZoom(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetPauseImage(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetDeviceDirection(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t InputNumForInterface(const sptr<CellularCallInterface> &telephonyService) const;

private:
    using RequestFuncType = int32_t (ImsTest::*)(const sptr<CellularCallInterface> &telephonyService) const;
    std::map<int32_t, RequestFuncType> requestFuncMap_;
};
} // namespace Telephony
} // namespace OHOS

#endif // TELEPHONY_IMS_TEST_H
