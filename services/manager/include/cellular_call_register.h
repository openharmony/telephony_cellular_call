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

#ifndef CELLULAR_CALL_REGISTER_H
#define CELLULAR_CALL_REGISTER_H

#include <map>

#include "cellular_call_connection_cs.h"
#include "i_call_status_callback.h"
#include "singleton.h"
namespace OHOS {
namespace CellularCall {
class CellularCallRegister {
    DECLARE_DELAYED_SINGLETON(CellularCallRegister);

public:
    /**
     * ReportCallsInfo.
     * @param callsReportInfo data list
     */
    void ReportCallsInfo(const OHOS::TelephonyCallManager::CallsReportInfo &callsReportInfo);

    /**
     * ReportCallsInfo.
     * @param Single CallInfo
     */
    void ReportSingleCallInfo(CellularCallConnectionCS &pCs, TelCallStates callState);

    /**
     * Register CallManagerCallBack
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t RegisterCallManagerCallBack(const sptr<OHOS::TelephonyCallManager::ICallStatusCallback> &callback);

    /**
     * UnRegister CallManagerCallBack
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int32_t UnRegisterCallManagerCallBack();

    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "CellularCallRegister"};

private:
    sptr<OHOS::TelephonyCallManager::ICallStatusCallback> callManagerCallBack_;
};
} // namespace CellularCall
} // namespace OHOS

#endif // CELLULAR_CALL_REGISTER_H
