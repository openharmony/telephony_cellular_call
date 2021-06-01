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

#ifndef CELLULAR_CALL_HANDLER_H
#define CELLULAR_CALL_HANDLER_H

#include <memory>

#include "i_tel_ril_manager.h"

#include "event_handler.h"

#include "cellular_call_data_struct.h"
#include "cellular_call_hilog.h"

namespace OHOS {
namespace CellularCall {
class CellularCallHandler : public AppExecFwk::EventHandler {
public:
    /**
     * CellularCallHandler constructor
     * @param runner
     * @param server
     */
    CellularCallHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner);

    /**
     * ~CellularCallHandler deconstructor
     */
    ~CellularCallHandler() = default;

    /**
     * ProcessEvent.
     *
     * @param CellularCallRadioResponseEvent, Process Radio Response Event .
     */
    void ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event);

    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "CellularCallHandler"};

private:
    /**
     * CSControl GetCsCallsData
     * 27007-430_2001 7.18 List current calls +CLCC
     * 3GPP TS 22.030 [19]
     *
     * Returns list of current calls of ME.
     *
     * @return Error Code: Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int GetCsCallsData();

    /**
     * get last flag
     * @return flag
     */
    int GetLastFlag();

    /**
     * Get Manager for core service
     * @param slotId
     */
    IRilManager *GetManager(int32_t slotId);

private:
    int32_t lastFlag_;
    int32_t slotId_ = 1;
};
} // namespace CellularCall
} // namespace OHOS

#endif // CELLULAR_CALL_HANDLE_H
