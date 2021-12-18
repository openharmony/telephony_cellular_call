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

#ifndef TELEPHONY_CS_TEST_H
#define TELEPHONY_CS_TEST_H

#include "gtest/gtest.h"

#include "cellular_call_data_struct.h"
#include "cellular_call_interface.h"

namespace OHOS {
namespace Telephony {
class CsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();

    int32_t Dial(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t HangUp(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t Answer(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t Reject(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t HoldCall(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t UnHoldCall(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SwitchCall(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t IsEmergencyPhoneNumber(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t CombineConference(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SeparateConference(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t CallSupplement(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t StartDtmf(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t StopDtmf(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SendDtmf(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SendDtmfString(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetCallTransferInfo(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t GetCallTransferInfo(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetCallWaiting(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t GetCallWaiting(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetCallRestriction(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t GetCallRestriction(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t RegisterCallBack(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t InputNumForInterface(const sptr<CellularCallInterface> &telephonyService) const;

private:
    using RequestFuncType = int32_t (CsTest::*)(const sptr<CellularCallInterface> &telephonyService) const;
    std::map<char, RequestFuncType> requestFuncMap_;
};
} // namespace Telephony
} // namespace OHOS
#endif // TELEPHONY_CS_TEST_H
