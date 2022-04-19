/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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

#ifndef IMS_BASE_HANDLER_H
#define IMS_BASE_HANDLER_H
#include <map>

#include "event_handler.h"
#include "telephony_log_wrapper.h"
#include "telephony_types.h"

namespace OHOS {
namespace Telephony {
class ImsBaseHandler : public AppExecFwk::EventHandler {
public:
    explicit ImsBaseHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner);

    virtual ~ImsBaseHandler() = default;

    void ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event) override;

    void SetSlotId(int32_t slotId);

    int32_t GetSlotId();

private:
    int32_t slotId_ = DEFAULT_SIM_SLOT_ID;
};
} // Telephony
} // OHOS
#endif // IMS_CORE_SERVICE_HANDLER_H
