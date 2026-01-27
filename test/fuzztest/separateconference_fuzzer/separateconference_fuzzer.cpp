/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "separateconference_fuzzer.h"

#include <cstddef>
#include <cstdint>

#define private public
#include "addcellularcalltoken_fuzzer.h"
#include "cs_control.h"
#include "securec.h"
#include "system_ability_definition.h"

using namespace OHOS::Telephony;
namespace OHOS {
constexpr int32_t SLOT_NUM = 2;
constexpr int32_t VEDIO_STATE_NUM = 2;
constexpr size_t MAX_NUMBER_LEN = 99;

void DoSomethingInterestingWithMyAPI(FuzzedDataProvider& provider)
{
    if (data == nullptr || size == 0) {
        return;
    }

    auto cSControl = std::make_shared<CSControl>();
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    int32_t callId = provider.ConsumeIntegral<int32_t>();
    int32_t accountId = provider.ConsumeIntegral<int32_t>();
    int32_t videoState = provider.ConsumeIntegralInRange<int32_t>(0, VEDIO_STATE_NUM);
    int32_t index = provider.ConsumeIntegral<int32_t>();
    CallSupplementType type = CallSupplementType::TYPE_DEFAULT;
    std::string splitString = provider.ConsumeRandomLengthString();
    std::string telNum = "000000000";
    std::string tempNum = provider.ConsumeRandomLengthString();
    if (strlen(tempNum.c_str()) <= MAX_NUMBER_LEN) {
        telNum = tempNum;
    }
    size_t length = strlen(telNum.c_str()) + 1;
    CellularCallInfo callInfo;
    callInfo.slotId = slotId;
    callInfo.callId = callId;
    callInfo.accountId = accountId;
    callInfo.videoState = videoState;
    callInfo.index = index;
    callInfo.callType = CallType::TYPE_CS;
    if (strcpy_s(callInfo.phoneNum, length, telNum.c_str()) != EOK) {
        return;
    }
    cSControl->DialCdma(callInfo);
    cSControl->DialGsm(callInfo);
    cSControl->HangUp(callInfo, type);
    cSControl->Answer(callInfo);
    cSControl->Reject(callInfo);
    cSControl->HoldCall(slotId);
    cSControl->UnHoldCall(slotId);
    cSControl->SwitchCall(slotId);
    cSControl->SeparateConference(slotId, splitString, index);
    cSControl->CombineConference(slotId);
    cSControl->HangUpAllConnection(slotId);
    return;
}
} // namespace OHOS

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    OHOS::AddCellularCallTokenFuzzer token;
    /* Run your code on data */
    FuzzedDataProvider provider(data, size);
    OHOS::DoSomethingInterestingWithMyAPI(provider);
    return 0;
}
