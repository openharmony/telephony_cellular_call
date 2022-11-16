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

#include "getcallrestriction_fuzzer.h"

#include <cstddef>
#include <cstdint>
#define private public
#include "addcellularcalltoken_fuzzer.h"
#include "cellular_call_service.h"
#include "system_ability_definition.h"

using namespace OHOS::Telephony;
namespace OHOS {
static bool g_isInited = false;
constexpr int32_t BOOL_NUM = 2;

bool IsServiceInited()
{
    DelayedSingleton<CellularCallService>::GetInstance()->OnStart();
    if (!g_isInited && (static_cast<int32_t>(DelayedSingleton<CellularCallService>::GetInstance()->state_) ==
                           static_cast<int32_t>(ServiceRunningState::STATE_RUNNING))) {
        g_isInited = true;
    }
    return g_isInited;
}

void OnRemoteRequest(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    MessageParcel dataMessageParcel;
    if (!dataMessageParcel.WriteInterfaceToken(CellularCallStub::GetDescriptor())) {
        return;
    }
    size_t dataSize = size - sizeof(uint32_t);
    dataMessageParcel.WriteBuffer(data + sizeof(uint32_t), dataSize);
    dataMessageParcel.RewindRead(0);
    uint32_t code = static_cast<uint32_t>(size);
    MessageParcel reply;
    MessageOption option;
    DelayedSingleton<CellularCallService>::GetInstance()->OnRemoteRequest(code, dataMessageParcel, reply, option);
}

void UnRegisterCallManagerCallBack(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = static_cast<int32_t>(size);
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    size_t dataSize = size - sizeof(int32_t);
    dataMessageParcel.WriteBuffer(data + sizeof(int32_t), dataSize);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnUnRegisterCallBackInner(dataMessageParcel, reply);
}

void IsEmergencyPhoneNumber(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t errorCode = static_cast<int32_t>(size);
    std::string phoneNum(reinterpret_cast<const char *>(data), size);
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(errorCode);
    dataMessageParcel.WriteString(phoneNum);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnIsEmergencyPhoneNumberInner(dataMessageParcel, reply);
}

void HangUpAllConnection(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = static_cast<int32_t>(size);
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    size_t dataSize = size - sizeof(int32_t);
    dataMessageParcel.WriteBuffer(data + sizeof(int32_t), dataSize);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnHangUpAllConnectionInner(dataMessageParcel, reply);
}

void StartRtt(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    std::string msg(reinterpret_cast<const char *>(data), size);
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteString(msg);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnStartRttInner(dataMessageParcel, reply);
}

void StopRtt(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteBuffer(data, size);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnStopRttInner(dataMessageParcel, reply);
}

void GetCallTransferInfo(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t type = static_cast<int32_t>(size);
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(type);
    size_t dataSize = size - sizeof(int32_t);
    dataMessageParcel.WriteBuffer(data + sizeof(int32_t), dataSize);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnGetCallTransferInner(dataMessageParcel, reply);
}

void GetCallWaiting(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteBuffer(data, size);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnGetCallWaitingInner(dataMessageParcel, reply);
}

void SetCallWaiting(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t activate = static_cast<int32_t>(size % BOOL_NUM);
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteBool(activate);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetCallWaitingInner(dataMessageParcel, reply);
}

void GetCallRestriction(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t facType = static_cast<int32_t>(size);
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(facType);
    size_t dataSize = size - sizeof(int32_t);
    dataMessageParcel.WriteBuffer(data + sizeof(int32_t), dataSize);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnGetCallRestrictionInner(dataMessageParcel, reply);
}

void DoSomethingInterestingWithMyAPI(const uint8_t *data, size_t size)
{
    if (data == nullptr || size == 0) {
        return;
    }

    OnRemoteRequest(data, size);
    UnRegisterCallManagerCallBack(data, size);
    IsEmergencyPhoneNumber(data, size);
    HangUpAllConnection(data, size);
    StartRtt(data, size);
    StopRtt(data, size);
    GetCallTransferInfo(data, size);
    GetCallWaiting(data, size);
    SetCallWaiting(data, size);
    GetCallRestriction(data, size);
    return;
}
} // namespace OHOS

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    OHOS::AddCellularCallTokenFuzzer token;
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}
