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

#include <securec.h>

#include "call_status_callback_proxy.h"

namespace OHOS {
namespace CellularCall {
CellularCallRegister::CellularCallRegister() : callManagerCallBack_(nullptr) {}
CellularCallRegister::~CellularCallRegister() = default;

void CellularCallRegister::ReportCallsInfo(const OHOS::TelephonyCallManager::CallsReportInfo &callsReportInfo)
{
    HILOG_DEBUG("ReportCallsInfo entry.");
    if (callManagerCallBack_ == nullptr) {
        HILOG_ERROR("ReportCallsInfo return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->OnUpdateCallsReportInfo(callsReportInfo);
}

int32_t CellularCallRegister::RegisterCallManagerCallBack(
    const sptr<OHOS::TelephonyCallManager::ICallStatusCallback> &callback)
{
    callManagerCallBack_ = callback;
    return TELEPHONY_NO_ERROR;
}

void CellularCallRegister::ReportSingleCallInfo(CellularCallConnectionCS &pCs, TelCallStates callState)
{
    HILOG_DEBUG("ReportSingleCallInfo entry");
    OHOS::TelephonyCallManager::CallReportInfo cellularCallReportInfo = pCs.callReportInfo_;
    cellularCallReportInfo.state = callState;
    if (callManagerCallBack_ == nullptr) {
        HILOG_ERROR("ReportSingleCallInfo return, callManagerCallBack_ is nullptr, report fail!");
        return;
    }
    callManagerCallBack_->OnUpdateCallReportInfo(cellularCallReportInfo);
}

int32_t CellularCallRegister::UnRegisterCallManagerCallBack()
{
    callManagerCallBack_ = nullptr;
    return 0;
}
} // namespace CellularCall
} // namespace OHOS