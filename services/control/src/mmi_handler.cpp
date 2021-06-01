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
#include "mmi_handler.h"

#include "mmi_code_utils.h"

#include "cellular_call_data_struct.h"

namespace OHOS {
namespace CellularCall {
MMIHandler::MMIHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner) : AppExecFwk::EventHandler(runner)
{
    HILOG_INFO("CellularCallHandler::CellularCallHandler::instance created.");
}

void MMIHandler::ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event)
{
    if (event == nullptr) {
        HILOG_ERROR("MMIHandler::ProcessEvent, event is nullptr");
        return;
    }
    switch (event->GetInnerEventId()) {
        case MMIHandlerId::MMI_EVENT_Id: {
            std::unique_ptr<MMICodeUtils> mmiCodeUtils = event->GetUniqueObject<MMICodeUtils>();
            if (mmiCodeUtils == nullptr) {
                HILOG_ERROR("MMIHandler::ProcessEvent, mmiCodeUtils is nullptr");
                return;
            }
            mmiCodeUtils->ExecuteMmiCode();
            break;
        }
        default:
            HILOG_WARN("ProcessEvent, default case, need check.");
            break;
    }
}
} // namespace CellularCall
} // namespace OHOS