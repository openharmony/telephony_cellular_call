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

#include "answerrequest_fuzzer.h"

#include <cstddef>
#include <cstdint>

#include "addcellularcalltoken_fuzzer.h"
#include "cellular_call_connection_ims.h"
#include "system_ability_definition.h"
#include "fuzzer/FuzzedDataProvider.h"

using namespace OHOS::Telephony;
namespace OHOS {
constexpr int32_t SLOT_NUM = 2;
constexpr int32_t VEDIO_STATE_NUM = 2;

void DoSomethingInterestingWithMyAPI(FuzzedDataProvider& provider)
{
    auto cellularCallConnectionIMS = std::make_shared<CellularCallConnectionIMS>();
    std::string phoneNum = provider.ConsumeRandomLengthString();
    int32_t slotId = provider.ConsumeIntegralInRange<int32_t>(0, SLOT_NUM);
    int32_t videoState = provider.ConsumeIntegralInRange<int32_t>(0, VEDIO_STATE_NUM);
    int32_t index = provider.ConsumeIntegral<int32_t>();
    std::vector<std::string> numberList;
    numberList.push_back(phoneNum);
    cellularCallConnectionIMS->HangUpRequest(slotId, phoneNum, index);
    cellularCallConnectionIMS->AnswerRequest(slotId, phoneNum, videoState, index);
    cellularCallConnectionIMS->RejectRequest(slotId, phoneNum, index);
    cellularCallConnectionIMS->HoldCallRequest(slotId);
    cellularCallConnectionIMS->UnHoldCallRequest(slotId);
    cellularCallConnectionIMS->InviteToConferenceRequest(slotId, numberList);
    cellularCallConnectionIMS->KickOutFromConferenceRequest(slotId, index);
#ifdef SUPPORT_RTT_CALL
    cellularCallConnectionIMS->UpdateImsRttCallModeRequest(slotId, index, ImsRTTCallMode::LOCAL_REQUEST_UPGRADE);
#endif
    return;
}
} // namespace OHOS

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    OHOS::AddCellularCallTokenFuzzer token;
    if (data == nullptr || size == 0) {
        return 0;
    }
    /* Run your code on data */
    FuzzedDataProvider provider(data, size);
    OHOS::DoSomethingInterestingWithMyAPI(provider);
    return 0;
}
