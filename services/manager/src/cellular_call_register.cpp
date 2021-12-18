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

#include "cellular_call_register.h"

#include "call_status_callback_proxy.h"

namespace OHOS {
namespace Telephony {
CellularCallRegister::CellularCallRegister() : callManagerCallBack_(nullptr) {}
CellularCallRegister::~CellularCallRegister() = default;

void CellularCallRegister::ReportCallsInfo(const CallsReportInfo &callsReportInfo)
{
    TELEPHONY_LOGI("ReportCallsInfo entry.");
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportCallsInfo return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->UpdateCallsReportInfo(callsReportInfo);
}

int32_t CellularCallRegister::RegisterCallManagerCallBack(const sptr<ICallStatusCallback> &callback)
{
    callManagerCallBack_ = callback;
    return TELEPHONY_SUCCESS;
}

void CellularCallRegister::ReportSingleCallInfo(CellularCallConnectionCS &pCs, TelCallState callState)
{
    TELEPHONY_LOGI("ReportSingleCallInfo entry");
    CallReportInfo cellularCallReportInfo = pCs.GetCallReportInfo();
    cellularCallReportInfo.state = callState;
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportSingleCallInfo return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->UpdateCallReportInfo(cellularCallReportInfo);
}

int32_t CellularCallRegister::UnRegisterCallManagerCallBack()
{
    callManagerCallBack_ = nullptr;
    return TELEPHONY_SUCCESS;
}

void CellularCallRegister::ReportEventResultInfo(const CellularCallEventInfo &info)
{
    TELEPHONY_LOGI("ReportEventResultInfo entry eventId:%{public}d", info.eventId);
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportEventResultInfo return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->UpdateEventResultInfo(info);
}

void CellularCallRegister::ReportGetWaitingResult(const CallWaitResponse &response)
{
    TELEPHONY_LOGI("ReportGetWaitingResult entry");
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportGetWaitingResult return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->UpdateGetWaitingResult(response);
}

void CellularCallRegister::ReportSetWaitingResult(const CallWaitResponse &response)
{
    TELEPHONY_LOGI("ReportSetWaitingResult entry");
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportSetWaitingResult return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->UpdateSetWaitingResult(response.result);
}

void CellularCallRegister::ReportGetRestrictionResult(const CallRestrictionResponse &response)
{
    TELEPHONY_LOGI("ReportGetRestrictionResult entry");
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportGetRestrictionResult return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->UpdateGetRestrictionResult(response);
}

void CellularCallRegister::ReportSetRestrictionResult(int32_t result)
{
    TELEPHONY_LOGI("ReportSetRestrictionResult entry");
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportSetRestrictionResult return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->UpdateSetRestrictionResult(result);
}

void CellularCallRegister::ReportGetTransferResult(const CallTransferResponse &response)
{
    TELEPHONY_LOGI("ReportGetTransferResult entry");
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportGetTransferResult return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->UpdateGetTransferResult(response);
}

void CellularCallRegister::ReportSetTransferResult(int32_t result)
{
    TELEPHONY_LOGI("ReportSetTransferResult entry");
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportSetTransferResult return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->UpdateSetTransferResult(result);
}

void CellularCallRegister::ReportGetClipResult(const ClipResponse &clipResponse)
{
    TELEPHONY_LOGI("ReportGetClipResult entry");
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportGetClipResult return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->UpdateGetCallClipResult(clipResponse);
}

void CellularCallRegister::ReportGetClirResult(const ClirResponse &clirResponse)
{
    TELEPHONY_LOGI("ReportGetClirResult entry");
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportSetTransferResult return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->UpdateGetCallClirResult(clirResponse);
}

void CellularCallRegister::ReportSetClirResult(const ClirResponse &clirResponse)
{
    TELEPHONY_LOGI("ReportSetClirResult entry");
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportSetTransferResult return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->UpdateSetCallClirResult(clirResponse.result);
}

void CellularCallRegister::ReportGetCallPreferenceResult(const CallPreferenceResponse &callPreference)
{
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportGetCallPreferenceResult return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
}

void CellularCallRegister::ReportGetLteImsSwitchResult(const LteImsSwitchResponse &lteImsSwitch)
{
    if (callManagerCallBack_ == nullptr) {
        TELEPHONY_LOGE("ReportGetLteImsSwitchResult return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
}
} // namespace Telephony
} // namespace OHOS