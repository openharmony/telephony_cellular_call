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

#ifndef TELEPHONY_CELLULAR_CALL_MMI_HANDLER_H
#define TELEPHONY_CELLULAR_CALL_MMI_HANDLER_H

#include "event_handler.h"
#include "event_runner.h"
#include "cellular_call_hilog.h"

namespace OHOS {
namespace CellularCall {
class MMIHandler : public AppExecFwk::EventHandler {
public:
    /**
     * MMIHandler
     * @param runner
     */
    MMIHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner);

    /**
     * ~MMIHandler
     */
    ~MMIHandler() = default;

    /**
     * ProcessEvent.
     *
     * @param mmi code process
     */
    void ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event);

    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "MMIHandler"};
};
} // namespace CellularCall
} // namespace OHOS
#endif // TELEPHONY_CELLULAR_CALL_MMI_HANDLER_H
