/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#include "cellular_call_connection_satellite.h"

#include "cellular_call_hisysevent.h"
#include "cellular_call_service.h"
#include "radio_event.h"
#include "satellite_call_client.h"
#include "satellite_call_types.h"
#include "securec.h"
#include "standardize_utils.h"

namespace OHOS {
namespace Telephony {
int32_t CellularCallConnectionSatellite::DialRequest(int32_t slotId, const DialRequestStruct &dialRequest)
{
    TELEPHONY_LOGI("call satellite service");
    SatelliteCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        TELEPHONY_LOGE("return, memset_s error.");
        CellularCallHiSysEvent::WriteDialCallFaultEvent(
            slotId, INVALID_PARAMETER, INVALID_PARAMETER, TELEPHONY_ERR_MEMSET_FAIL, "memset_s error");
        return TELEPHONY_ERR_MEMSET_FAIL;
    }
    UpdateCallNumber(dialRequest.phoneNum);
    size_t cpyLen = strlen(phoneNumber_.c_str()) + 1;
    if (cpyLen > static_cast<size_t>(kMaxNumberLength)) {
        phoneNumber_.clear();
        return TELEPHONY_ERR_STRCPY_FAIL;
    }
    if (strcpy_s(callInfo.phoneNum, cpyLen, phoneNumber_.c_str()) != EOK) {
        TELEPHONY_LOGE("return, strcpy_s fail.");
        phoneNumber_.clear();
        CellularCallHiSysEvent::WriteDialCallFaultEvent(
            slotId, INVALID_PARAMETER, INVALID_PARAMETER, TELEPHONY_ERR_STRCPY_FAIL, "strcpy_s fail");
        return TELEPHONY_ERR_STRCPY_FAIL;
    }
    phoneNumber_.clear();
    callInfo.slotId = slotId;
    if (DelayedSingleton<SatelliteCallClient>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("return, SatelliteCallClient is nullptr.");
        CellularCallHiSysEvent::WriteDialCallFaultEvent(slotId, INVALID_PARAMETER, INVALID_PARAMETER,
            CALL_ERR_RESOURCE_UNAVAILABLE, "satellite vendor service does not exist");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    return DelayedSingleton<SatelliteCallClient>::GetInstance()->Dial(callInfo, dialRequest.clirMode);
}

int32_t CellularCallConnectionSatellite::HangUpRequest(int32_t slotId)
{
    TELEPHONY_LOGI("call satellite service");
    if (DelayedSingleton<SatelliteCallClient>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("return, SatelliteCallClient is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    int32_t index = GetIndex();
    return DelayedSingleton<SatelliteCallClient>::GetInstance()->HangUp(slotId, index);
}

int32_t CellularCallConnectionSatellite::AnswerRequest(int32_t slotId)
{
    TELEPHONY_LOGI("call satellite service");
    if (DelayedSingleton<SatelliteCallClient>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("return, SatelliteCallClient is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    return DelayedSingleton<SatelliteCallClient>::GetInstance()->Answer(slotId);
}

int32_t CellularCallConnectionSatellite::RejectRequest(int32_t slotId)
{
    TELEPHONY_LOGI("call satellite service");
    if (DelayedSingleton<SatelliteCallClient>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("return, SatelliteCallClient is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    return DelayedSingleton<SatelliteCallClient>::GetInstance()->Reject(slotId);
}

int32_t CellularCallConnectionSatellite::GetSatelliteCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag)
{
    TELEPHONY_LOGI("call satellite service");
    if (DelayedSingleton<SatelliteCallClient>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("return, SatelliteCallClient is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    return DelayedSingleton<SatelliteCallClient>::GetInstance()->GetSatelliteCallsDataRequest(
        slotId, lastCallsDataFlag);
}

int32_t CellularCallConnectionSatellite::GetCallFailReasonRequest(int32_t slotId) const
{
    return CALL_ERR_RESOURCE_UNAVAILABLE;
}

void CellularCallConnectionSatellite::RegisterHandler()
{
    DelayedSingleton<CellularCallService>::GetInstance()->RegisterHandler();
}

int32_t CellularCallConnectionSatellite::SendDtmfRequest(int32_t slotId, char cDtmfCode, int32_t index) const
{
    TELEPHONY_LOGI("CellularCallConnectionSatellite::SendDtmfRequest start.");
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("SendDtmfRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("SendDtmfRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().SendDTMF(slotId, RadioEvent::RADIO_SEND_DTMF, cDtmfCode, index, handle);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionSatellite::StartDtmfRequest(int32_t slotId, char cDtmfCode, int32_t index) const
{
    TELEPHONY_LOGD("CellularCallConnectionSatellite::StartDtmfRequest start.");
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("StartDtmfRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("StartDtmfRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().StartDTMF(slotId, RadioEvent::RADIO_START_DTMF, cDtmfCode, index, handle);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionSatellite::StopDtmfRequest(int32_t slotId, int32_t index) const
{
    TELEPHONY_LOGI("CellularCallConnectionSatellite::StopDtmfRequest start.");
    if (DelayedSingleton<CellularCallService>::GetInstance() == nullptr) {
        TELEPHONY_LOGE("StopDtmfRequest return, error type: GetInstance() is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    auto handle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
    if (handle == nullptr) {
        TELEPHONY_LOGE("StopDtmfRequest return, error type: handle is nullptr.");
        return CALL_ERR_RESOURCE_UNAVAILABLE;
    }
    CoreManagerInner::GetInstance().StopDTMF(slotId, RadioEvent::RADIO_STOP_DTMF, index, handle);
    return TELEPHONY_SUCCESS;
}

int32_t CellularCallConnectionSatellite::ProcessPostDialCallChar(int32_t slotId, char c)
{
    if (StandardizeUtils::IsDtmfKey(c)) {
        SendDtmfRequest(slotId, c, GetIndex());
    } else if (StandardizeUtils::IsPauseKey(c)) {
        SetPostDialCallState(PostDialCallState::POST_DIAL_CALL_PAUSE);
        auto cellularCallHandle = DelayedSingleton<CellularCallService>::GetInstance()->GetHandler(slotId);
        if (cellularCallHandle == nullptr) {
            TELEPHONY_LOGE("SendDtmfRequest return, error type: handle is nullptr.");
            return CALL_ERR_RESOURCE_UNAVAILABLE;
        }
        std::shared_ptr<PostDialData> postDial = std::make_shared<PostDialData>();
        postDial->callId = GetIndex();
        postDial->isIms = false;
        cellularCallHandle->SendEvent(EVENT_EXECUTE_POST_DIAL, postDial, PAUSE_DELAY_TIME);
    } else if (StandardizeUtils::IsWaitKey(c)) {
        SetPostDialCallState(PostDialCallState::POST_DIAL_CALL_DELAY);
    }
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS
