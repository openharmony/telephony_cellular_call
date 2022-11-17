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

#include "setpreviewwindow_fuzzer.h"

#include <cstddef>
#include <cstdint>
#define private public
#include "addcellularcalltoken_fuzzer.h"
#include "cellular_call_service.h"
#include "system_ability_definition.h"

using namespace OHOS::Telephony;
namespace OHOS {
static bool g_isInited = false;
constexpr int32_t INT_NUM = 6;

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

void SetPreviewWindow(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = static_cast<int32_t>(size);
    int32_t x = static_cast<int32_t>(size);
    int32_t y = static_cast<int32_t>(size);
    int32_t z = static_cast<int32_t>(size);
    int32_t width = static_cast<int32_t>(size);
    int32_t height = static_cast<int32_t>(size);
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteInt32(x);
    dataMessageParcel.WriteInt32(y);
    dataMessageParcel.WriteInt32(z);
    dataMessageParcel.WriteInt32(width);
    dataMessageParcel.WriteInt32(height);
    size_t dataSize = size - sizeof(int32_t) * INT_NUM;
    dataMessageParcel.WriteBuffer(data + sizeof(int32_t) * INT_NUM, dataSize);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetPreviewWindowInner(dataMessageParcel, reply);
}

void SetDisplayWindow(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = static_cast<int32_t>(size);
    int32_t x = static_cast<int32_t>(size);
    int32_t y = static_cast<int32_t>(size);
    int32_t z = static_cast<int32_t>(size);
    int32_t width = static_cast<int32_t>(size);
    int32_t height = static_cast<int32_t>(size);
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteInt32(x);
    dataMessageParcel.WriteInt32(y);
    dataMessageParcel.WriteInt32(z);
    dataMessageParcel.WriteInt32(width);
    dataMessageParcel.WriteInt32(height);
    size_t dataSize = size - sizeof(int32_t) * INT_NUM;
    dataMessageParcel.WriteBuffer(data + sizeof(int32_t) * INT_NUM, dataSize);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetDisplayWindowInner(dataMessageParcel, reply);
}

void SetCameraZoom(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = static_cast<int32_t>(size);
    float zoomRatio = static_cast<float>(size);
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteFloat(zoomRatio);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetCameraZoomInner(dataMessageParcel, reply);
}

void SetMute(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t mute = static_cast<int32_t>(size);
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(mute);
    size_t dataSize = size - sizeof(int32_t);
    dataMessageParcel.WriteBuffer(data + sizeof(int32_t), dataSize);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetMuteInner(dataMessageParcel, reply);
}

void GetMute(const uint8_t *data, size_t size)
{
    if (!IsServiceInited()) {
        return;
    }

    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteBuffer(data, size);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnGetMuteInner(dataMessageParcel, reply);
}

void DoSomethingInterestingWithMyAPI(const uint8_t *data, size_t size)
{
    if (data == nullptr || size == 0) {
        return;
    }

    OnRemoteRequest(data, size);
    SetPreviewWindow(data, size);
    SetDisplayWindow(data, size);
    SetCameraZoom(data, size);
    SetMute(data, size);
    GetMute(data, size);
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
