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
#include <string_ex.h>
#define private public

#include "addcellularcalltoken_fuzzer.h"
#include "cellular_call_service.h"
#include "fuzzer/FuzzedDataProvider.h"
#include "securec.h"
#include "surface_utils.h"
#include "system_ability_definition.h"

using namespace OHOS::Telephony;
namespace OHOS {
static bool g_isInited = false;
constexpr int32_t BOOL_NUM = 2;
constexpr int32_t VEDIO_STATE_NUM = 2;
constexpr int32_t OFFSET_SIZE = 11;
constexpr size_t MAX_NUMBER_LEN = 99;

bool IsServiceInited()
{
    if (!g_isInited) {
        DelayedSingleton<CellularCallService>::GetInstance()->OnStart();
    }
    if (!g_isInited && (static_cast<int32_t>(DelayedSingleton<CellularCallService>::GetInstance()->state_) ==
                           static_cast<int32_t>(ServiceRunningState::STATE_RUNNING))) {
        g_isInited = true;
    }
    return g_isInited;
}

void OnRemoteRequest(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    MessageParcel dataMessageParcel;
    if (!dataMessageParcel.WriteInterfaceToken(CellularCallStub::GetDescriptor())) {
        return;
    }
    int32_t maxSize = provider.ConsumeIntegral<int32_t>() + OFFSET_SIZE;
    dataMessageParcel.WriteInt32(maxSize);
    std::vector<uint8_t> remaining_data = provider.ConsumeRemainingBytes<uint8_t>();
    dataMessageParcel.WriteBuffer(static_cast<void*>(remaining_data.data()), remaining_data.size());
    dataMessageParcel.RewindRead(0);
    uint32_t code = provider.ConsumeIntegral<uint32_t>();
    MessageParcel reply;
    MessageOption option;
    DelayedSingleton<CellularCallService>::GetInstance()->OnRemoteRequest(code, dataMessageParcel, reply, option);
}

void SetPreviewWindow(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t index = provider.ConsumeIntegral<int32_t>();
    std::string surfaceId = provider.ConsumeRandomLengthString();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteInt32(slotId);
    dataMessageParcel.WriteInt32(index);
    int len = static_cast<int>(surfaceId.length());
    std::string subSurfaceId = surfaceId;
    if (len >= 1) {
        subSurfaceId = surfaceId.substr(0, 1);
    }
    if (subSurfaceId.empty() || subSurfaceId[0] < '0' || subSurfaceId[0] > '9') {
        subSurfaceId = "";
        dataMessageParcel.WriteString(subSurfaceId);
    } else {
        dataMessageParcel.WriteString(subSurfaceId);
        uint64_t tmpSurfaceId = std::stoull(subSurfaceId);
        auto surface = SurfaceUtils::GetInstance()->GetSurface(tmpSurfaceId);
        if (surface != nullptr) {
            sptr<IBufferProducer> producer = surface->GetProducer();
            if (producer != nullptr) {
                dataMessageParcel.WriteRemoteObject(producer->AsObject());
            }
        }
    }
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetPreviewWindowInner(dataMessageParcel, reply);
}

void SetDisplayWindow(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t index = provider.ConsumeIntegral<int32_t>();
    std::string surfaceId = provider.ConsumeRandomLengthString();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteInt32(slotId);
    dataMessageParcel.WriteInt32(index);
    int len = static_cast<int>(surfaceId.length());
    std::string subSurfaceId = surfaceId;
    if (len >= 1) {
        subSurfaceId = surfaceId.substr(0, 1);
    }
    if (subSurfaceId.empty() || subSurfaceId[0] < '0' || subSurfaceId[0] > '9') {
        subSurfaceId = "";
        dataMessageParcel.WriteString(subSurfaceId);
    } else {
        dataMessageParcel.WriteString(subSurfaceId);
        uint64_t tmpSurfaceId = std::stoull(subSurfaceId);
        auto surface = SurfaceUtils::GetInstance()->GetSurface(tmpSurfaceId);
        if (surface != nullptr) {
            sptr<IBufferProducer> producer = surface->GetProducer();
            if (producer != nullptr) {
                dataMessageParcel.WriteRemoteObject(producer->AsObject());
            }
        }
    }
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetDisplayWindowInner(dataMessageParcel, reply);
}

void SetCameraZoom(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    float zoomRatio = provider.ConsumeFloatingPoint<float>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteFloat(zoomRatio);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetCameraZoomInner(dataMessageParcel, reply);
}

void ControlCamera(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t index = provider.ConsumeIntegral<int32_t>();
    std::string cameraId = provider.ConsumeRandomLengthString();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteInt32(slotId);
    dataMessageParcel.WriteInt32(index);
    dataMessageParcel.WriteString(cameraId);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnControlCameraInner(dataMessageParcel, reply);
}

void SetPausePicture(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t index = provider.ConsumeIntegral<int32_t>();
    std::string path = provider.ConsumeRandomLengthString();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteInt32(slotId);
    dataMessageParcel.WriteInt32(index);
    dataMessageParcel.WriteString(path);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetPausePictureInner(dataMessageParcel, reply);
}

void SetDeviceDirection(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t index = provider.ConsumeIntegral<int32_t>();
    int32_t rotation = provider.ConsumeIntegral<int32_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteInt32(slotId);
    dataMessageParcel.WriteInt32(index);
    dataMessageParcel.WriteInt32(rotation);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetDeviceDirectionInner(dataMessageParcel, reply);
}

void SendUpdateCallMediaModeRequest(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    CellularCallInfo callInfo;
    callInfo.callId = provider.ConsumeIntegral<int32_t>();
    callInfo.slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    callInfo.accountId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    callInfo.callType = static_cast<CallType>(provider.ConsumeIntegral<int32_t>());
    callInfo.videoState = provider.ConsumeIntegral<int32_t>() % VEDIO_STATE_NUM;
    callInfo.index = provider.ConsumeIntegral<int32_t>();
    std::string telNum = "000000000";
    std::string tempNum = provider.ConsumeRandomLengthString();
    if (strlen(tempNum.c_str()) <= MAX_NUMBER_LEN) {
        telNum = tempNum;
    }
    size_t length = strlen(telNum.c_str()) + 1;
    if (strcpy_s(callInfo.phoneNum, length, telNum.c_str()) != EOK) {
        return;
    }
    int32_t mode = provider.ConsumeIntegral<int32_t>();

    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteRawData(static_cast<const void *>(&callInfo), sizeof(CellularCallInfo));
    dataMessageParcel.WriteInt32(mode);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSendUpdateCallMediaModeRequestInner(
        dataMessageParcel, reply);
}

void SendUpdateCallMediaModeResponse(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    CellularCallInfo callInfo;
    callInfo.callId = provider.ConsumeIntegral<int32_t>();
    callInfo.slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    callInfo.accountId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    callInfo.callType = static_cast<CallType>(provider.ConsumeIntegral<int32_t>());
    callInfo.videoState = provider.ConsumeIntegral<int32_t>() % VEDIO_STATE_NUM;
    callInfo.index = provider.ConsumeIntegral<int32_t>();
    std::string telNum = "000000000";
    std::string tempNum = provider.ConsumeRandomLengthString();
    if (strlen(tempNum.c_str()) <= MAX_NUMBER_LEN) {
        telNum = tempNum;
    }
    size_t length = strlen(telNum.c_str()) + 1;
    if (strcpy_s(callInfo.phoneNum, length, telNum.c_str()) != EOK) {
        return;
    }
    int32_t mode = provider.ConsumeIntegral<int32_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteRawData(static_cast<const void *>(&callInfo), sizeof(CellularCallInfo));
    dataMessageParcel.WriteInt32(mode);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSendUpdateCallMediaModeResponseInner(
        dataMessageParcel, reply);
}

void SetMute(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t mute = provider.ConsumeIntegral<int32_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(mute);
    std::vector<uint8_t> remaining_data = provider.ConsumeRemainingBytes<uint8_t>();
    dataMessageParcel.WriteBuffer(static_cast<void*>(remaining_data.data()), remaining_data.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnSetMuteInner(dataMessageParcel, reply);
}

void GetMute(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    MessageParcel dataMessageParcel;
    std::vector<uint8_t> remaining_data = provider.ConsumeRemainingBytes<uint8_t>();
    dataMessageParcel.WriteBuffer(static_cast<void*>(remaining_data.data()), remaining_data.size());
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnGetMuteInner(dataMessageParcel, reply);
}

void StartDtmf(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t callId = provider.ConsumeIntegral<int32_t>();
    int32_t accountId = provider.ConsumeIntegral<int32_t>();
    int32_t videoState = provider.ConsumeIntegral<int32_t>() % VEDIO_STATE_NUM;
    int32_t index = provider.ConsumeIntegral<int32_t>();
    char cDtmfCode = provider.ConsumeIntegral<char>();
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
    if (strcpy_s(callInfo.phoneNum, length, telNum.c_str()) != EOK) {
        return;
    }
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteInt8(cDtmfCode);
    dataMessageParcel.WriteRawData(static_cast<const void *>(&callInfo), sizeof(CellularCallInfo));
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnStartDtmfInner(dataMessageParcel, reply);
}

void CancelCallUpgrade(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t index = provider.ConsumeIntegral<int32_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteInt32(slotId);
    dataMessageParcel.WriteInt32(index);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnCancelCallUpgradeInner(dataMessageParcel, reply);
}

void RequestCameraCapabilities(FuzzedDataProvider& provider)
{
    if (!IsServiceInited()) {
        return;
    }

    int32_t maxSize = provider.ConsumeIntegral<int32_t>();
    int32_t slotId = provider.ConsumeIntegral<int32_t>() % BOOL_NUM;
    int32_t index = provider.ConsumeIntegral<int32_t>();
    MessageParcel dataMessageParcel;
    dataMessageParcel.WriteInt32(maxSize);
    dataMessageParcel.WriteInt32(slotId);
    dataMessageParcel.WriteInt32(index);
    dataMessageParcel.RewindRead(0);
    MessageParcel reply;
    DelayedSingleton<CellularCallService>::GetInstance()->OnRequestCameraCapabilitiesInner(dataMessageParcel, reply);
}

void DoSomethingInterestingWithMyAPI(const uint8_t *data, size_t size)
{
    if (data == nullptr || size == 0) {
        return;
    }
    FuzzedDataProvider provider(data, size);
    OnRemoteRequest(provider);
    SetPreviewWindow(provider);
    SetDisplayWindow(provider);
    SetCameraZoom(provider);
    ControlCamera(provider);
    SetPausePicture(provider);
    SetDeviceDirection(provider);
    SetMute(provider);
    GetMute(provider);
    StartDtmf(provider);
    SendUpdateCallMediaModeRequest(provider);
    SendUpdateCallMediaModeResponse(provider);
    CancelCallUpgrade(provider);
    RequestCameraCapabilities(provider);
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
