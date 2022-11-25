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

#include "imsclient_fuzzer.h"

#include <cstddef>
#include <cstdint>
#define private public
#include "addcellularcalltoken_fuzzer.h"
#include "cellular_call_service.h"
#include "ims_call_client.h"
#include "ims_call_proxy.h"
#include "securec.h"
#include "system_ability_definition.h"

using namespace OHOS::Telephony;
namespace OHOS {
static bool g_isInited = false;
constexpr size_t MAX_NUMBER_LEN = 100;
constexpr int32_t SERVICE_STATE_RUNNING = 1;

bool IsServiceInited()
{
    auto service = DelayedSingleton<CellularCallService>::GetInstance();
    if (service == nullptr) {
        return g_isInited;
    }
    if (service->GetServiceRunningState() != SERVICE_STATE_RUNNING) {
        service->OnStart();
    }
    if (!g_isInited && service->GetServiceRunningState() == SERVICE_STATE_RUNNING) {
        g_isInited = true;
    }
    return g_isInited;
}

int32_t TestImsCallClientWithCallInfo(
    const uint8_t *data, size_t size, const std::shared_ptr<ImsCallClient> &imsCallClient)
{
    int32_t ret = -1;
    std::string number(reinterpret_cast<const char *>(data), size);
    int32_t mode = static_cast<int32_t>(size % 2);
    int32_t slotId = static_cast<int32_t>(size % 2);
    int32_t videoState = static_cast<int32_t>(size % 3);
    int32_t index = static_cast<int32_t>(size % 3);
    const char *cDtmfCode = number.c_str();
    ImsCallInfo callInfo;
    if (strcpy_s(callInfo.phoneNum, MAX_NUMBER_LEN, number.c_str()) != EOK) {
        return ret;
    }
    callInfo.slotId = slotId;
    callInfo.videoState = videoState;
    callInfo.index = index;
    std::vector<std::string> numberList;
    numberList.push_back(number);
    ret = imsCallClient->Dial(callInfo, static_cast<CLIRMode>(mode));
    ret = imsCallClient->HangUp(callInfo);
    ret = imsCallClient->Answer(callInfo);
    ret = imsCallClient->Reject(callInfo);
    ret = imsCallClient->RejectWithReason(callInfo, ImsRejectReason::USER_DECLINE);
    ret = imsCallClient->UpdateImsCallMode(callInfo, static_cast<ImsCallMode>(mode));
    ret = imsCallClient->InviteToConference(slotId, numberList);
    ret = imsCallClient->KickOutFromConference(slotId, numberList);
    ret = imsCallClient->StartDtmf(slotId, *cDtmfCode, index);
    ret = imsCallClient->SendDtmf(slotId, *cDtmfCode, index);
    ret = imsCallClient->StopDtmf(slotId, index);
    ret = imsCallClient->StartRtt(slotId, number);
    ret = imsCallClient->StopRtt(slotId);
    ret = imsCallClient->SetDomainPreferenceMode(slotId, mode);
    ret = imsCallClient->GetDomainPreferenceMode(slotId);
    ret = imsCallClient->SetImsSwitchStatus(slotId, mode);
    ret = imsCallClient->GetImsSwitchStatus(slotId);
    ret = imsCallClient->SetMute(slotId, mode);
    ret = imsCallClient->GetMute(slotId);
    return ret;
}

int32_t TestImsCallClientWithSlotAndType(
    const uint8_t *data, size_t size, const std::shared_ptr<ImsCallClient> &imsCallClient)
{
    int32_t ret = -1;
    int32_t slotId = static_cast<int32_t>(size % 2);
    int32_t callType = static_cast<int32_t>(size % 2);
    std::string info(reinterpret_cast<const char *>(data), size);
    int32_t x = static_cast<int32_t>(size % 3);
    int32_t y = static_cast<int32_t>(size % 3);
    int32_t z = static_cast<int32_t>(size % 4);
    int32_t width = static_cast<int32_t>(size % 4);
    int32_t height = static_cast<int32_t>(size % 5);
    int32_t callingUid = static_cast<int32_t>(size % 5);
    int32_t callingPid = static_cast<int32_t>(size % 6);
    int32_t mode = static_cast<int32_t>(size % 6);
    ret = imsCallClient->HoldCall(slotId, callType);
    ret = imsCallClient->UnHoldCall(slotId, callType);
    ret = imsCallClient->SwitchCall(slotId, callType);
    ret = imsCallClient->CombineConference(slotId);
    ret = imsCallClient->GetImsCallsDataRequest(slotId, callType);
    ret = imsCallClient->GetLastCallFailReason(slotId);
    ret = imsCallClient->CtrlCamera(Str8ToStr16(info), callingUid, callingPid);
    ret = imsCallClient->SetPreviewWindow(x, y, z, width, height);
    ret = imsCallClient->SetDisplayWindow(x, y, z, width, height);
    ret = imsCallClient->SetPauseImage(Str8ToStr16(info));
    ret = imsCallClient->SetDeviceDirection(mode);
    ret = imsCallClient->SetCameraZoom(mode);
    ImsCapabilityList imsCapabilityList;
    ImsCapability capbility;
    capbility.enable = mode;
    capbility.imsCapabilityType = static_cast<ImsCapabilityType>(callType);
    capbility.imsRadioTech = static_cast<ImsRegTech>(callType);
    imsCapabilityList.imsCapabilities.push_back(capbility);
    ret = imsCallClient->UpdateImsCapabilities(slotId, imsCapabilityList);
    return ret;
}

int32_t TestImsCallClientWithSettingFunction(
    const uint8_t *data, size_t size, const std::shared_ptr<ImsCallClient> &imsCallClient)
{
    int32_t ret = -1;
    std::string number(reinterpret_cast<const char *>(data), size);
    int32_t mode = static_cast<int32_t>(size % 2);
    int32_t slotId = static_cast<int32_t>(size % 2);
    int32_t item = static_cast<int32_t>(size % 3);
    int32_t value = static_cast<int32_t>(size % 4);
    int32_t type = static_cast<int32_t>(size % 4);
    ret = imsCallClient->SetImsConfig(static_cast<ImsConfigItem>(item), number);
    ret = imsCallClient->SetImsConfig(static_cast<ImsConfigItem>(item), value);
    ret = imsCallClient->GetImsConfig(static_cast<ImsConfigItem>(item));
    ret = imsCallClient->SetImsFeatureValue(static_cast<FeatureType>(type), value);
    ret = imsCallClient->GetImsFeatureValue(static_cast<FeatureType>(type), value);
    ret = imsCallClient->SetClip(slotId, mode);
    ret = imsCallClient->GetClip(slotId);
    ret = imsCallClient->SetClir(slotId, mode);
    ret = imsCallClient->GetClir(slotId);
    ret = imsCallClient->SetCallWaiting(slotId, mode, type);
    ret = imsCallClient->GetCallWaiting(slotId);
    ret = imsCallClient->SetColr(slotId, mode);
    ret = imsCallClient->GetColr(slotId);
    ret = imsCallClient->SetColp(slotId, mode);
    ret = imsCallClient->GetColp(slotId);
    ret = imsCallClient->SetCallTransfer(slotId, type, mode, number, type);
    ret = imsCallClient->GetCallTransfer(slotId, type);
    ret = imsCallClient->SetCallRestriction(slotId, number, mode, number);
    ret = imsCallClient->GetCallRestriction(slotId, number);
    return ret;
}

int32_t TestImsCallProxyWithCallInfo(const uint8_t *data, size_t size, const sptr<ImsCallInterface> &proxy)
{
    int32_t ret = -1;
    std::string number(reinterpret_cast<const char *>(data), size);
    int32_t mode = static_cast<int32_t>(size % 2);
    int32_t slotId = static_cast<int32_t>(size % 2);
    int32_t videoState = static_cast<int32_t>(size % 3);
    int32_t index = static_cast<int32_t>(size % 3);
    const char *cDtmfCode = number.c_str();
    ImsCallInfo callInfo;
    if (strcpy_s(callInfo.phoneNum, MAX_NUMBER_LEN, number.c_str()) != EOK) {
        return ret;
    }
    callInfo.slotId = slotId;
    callInfo.videoState = videoState;
    callInfo.index = index;
    std::vector<std::string> numberList;
    numberList.push_back(number);
    ret = proxy->Dial(callInfo, static_cast<CLIRMode>(mode));
    ret = proxy->HangUp(callInfo);
    ret = proxy->Answer(callInfo);
    ret = proxy->RejectWithReason(callInfo, ImsRejectReason::USER_DECLINE);
    ret = proxy->UpdateImsCallMode(callInfo, static_cast<ImsCallMode>(mode));
    ret = proxy->InviteToConference(slotId, numberList);
    ret = proxy->KickOutFromConference(slotId, numberList);
    ret = proxy->StartDtmf(slotId, *cDtmfCode, index);
    ret = proxy->SendDtmf(slotId, *cDtmfCode, index);
    ret = proxy->StopDtmf(slotId, index);
    ret = proxy->StartRtt(slotId, number);
    ret = proxy->StopRtt(slotId);
    ret = proxy->SetDomainPreferenceMode(slotId, mode);
    ret = proxy->GetDomainPreferenceMode(slotId);
    ret = proxy->SetImsSwitchStatus(slotId, mode);
    ret = proxy->GetImsSwitchStatus(slotId);
    ret = proxy->SetMute(slotId, mode);
    ret = proxy->GetMute(slotId);
    return ret;
}

int32_t TestImsCallProxyWithSlotAndType(const uint8_t *data, size_t size, const sptr<ImsCallInterface> &proxy)
{
    int32_t ret = -1;
    int32_t slotId = static_cast<int32_t>(size % 2);
    int32_t callType = static_cast<int32_t>(size % 2);
    std::string info(reinterpret_cast<const char *>(data), size);
    int32_t x = static_cast<int32_t>(size % 3);
    int32_t y = static_cast<int32_t>(size % 3);
    int32_t z = static_cast<int32_t>(size % 4);
    int32_t width = static_cast<int32_t>(size % 4);
    int32_t height = static_cast<int32_t>(size % 5);
    int32_t callingUid = static_cast<int32_t>(size % 5);
    int32_t callingPid = static_cast<int32_t>(size % 6);
    int32_t mode = static_cast<int32_t>(size % 6);
    ret = proxy->HoldCall(slotId, callType);
    ret = proxy->UnHoldCall(slotId, callType);
    ret = proxy->SwitchCall(slotId, callType);
    ret = proxy->CombineConference(slotId);
    ret = proxy->GetImsCallsDataRequest(slotId, callType);
    ret = proxy->GetLastCallFailReason(slotId);
    ret = proxy->CtrlCamera(Str8ToStr16(info), callingUid, callingPid);
    ret = proxy->SetPreviewWindow(x, y, z, width, height);
    ret = proxy->SetDisplayWindow(x, y, z, width, height);
    ret = proxy->SetPauseImage(Str8ToStr16(info));
    ret = proxy->SetDeviceDirection(mode);
    ret = proxy->SetCameraZoom(mode);
    ImsCapabilityList imsCapabilityList;
    ImsCapability capbility;
    capbility.enable = mode;
    capbility.imsCapabilityType = static_cast<ImsCapabilityType>(callType);
    capbility.imsRadioTech = static_cast<ImsRegTech>(callType);
    imsCapabilityList.imsCapabilities.push_back(capbility);
    ret = proxy->UpdateImsCapabilities(slotId, imsCapabilityList);
    return ret;
}

int32_t TestImsCallProxyWithSettingFunction(const uint8_t *data, size_t size, const sptr<ImsCallInterface> &proxy)
{
    int32_t ret = -1;
    std::string number(reinterpret_cast<const char *>(data), size);
    int32_t mode = static_cast<int32_t>(size % 2);
    int32_t slotId = static_cast<int32_t>(size % 2);
    int32_t item = static_cast<int32_t>(size % 3);
    int32_t value = static_cast<int32_t>(size % 4);
    int32_t type = static_cast<int32_t>(size % 4);
    ret = proxy->SetImsConfig(static_cast<ImsConfigItem>(item), number);
    ret = proxy->SetImsConfig(static_cast<ImsConfigItem>(item), value);
    ret = proxy->GetImsConfig(static_cast<ImsConfigItem>(item));
    ret = proxy->SetImsFeatureValue(static_cast<FeatureType>(type), value);
    ret = proxy->GetImsFeatureValue(static_cast<FeatureType>(type), value);
    ret = proxy->SetClip(slotId, mode);
    ret = proxy->GetClip(slotId);
    ret = proxy->SetClir(slotId, mode);
    ret = proxy->GetClir(slotId);
    ret = proxy->SetCallWaiting(slotId, mode, type);
    ret = proxy->GetCallWaiting(slotId);
    ret = proxy->SetColr(slotId, mode);
    ret = proxy->GetColr(slotId);
    ret = proxy->SetColp(slotId, mode);
    ret = proxy->GetColp(slotId);
    ret = proxy->SetCallTransfer(slotId, type, mode, number, type);
    ret = proxy->GetCallTransfer(slotId, type);
    ret = proxy->SetCallRestriction(slotId, number, mode, number);
    ret = proxy->GetCallRestriction(slotId, number);
    return ret;
}

bool DoSomethingInterestingWithMyAPI(const uint8_t *data, size_t size)
{
    bool result = false;
    if (data == nullptr || size == 0) {
        return result;
    }
    auto imsCallClient = DelayedSingleton<ImsCallClient>::GetInstance();
    if (imsCallClient == nullptr) {
        return result;
    }
    if (!IsServiceInited()) {
        return result;
    }
    TestImsCallClientWithCallInfo(data, size, imsCallClient);
    TestImsCallClientWithSlotAndType(data, size, imsCallClient);
    TestImsCallClientWithSettingFunction(data, size, imsCallClient);

    auto managerPtr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (managerPtr == nullptr) {
        return result;
    }
    auto remoteObjectPtr = managerPtr->CheckSystemAbility(TELEPHONY_IMS_SYS_ABILITY_ID);
    if (remoteObjectPtr == nullptr) {
        return result;
    }
    sptr<ImsCallInterface> proxy = iface_cast<ImsCallInterface>(remoteObjectPtr);
    if (proxy == nullptr) {
        return result;
    }
    TestImsCallProxyWithCallInfo(data, size, proxy);
    TestImsCallProxyWithSlotAndType(data, size, proxy);
    TestImsCallProxyWithSettingFunction(data, size, proxy);
    if (proxy != nullptr) {
        proxy.clear();
        proxy = nullptr;
    }
    result = true;
    return result;
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
