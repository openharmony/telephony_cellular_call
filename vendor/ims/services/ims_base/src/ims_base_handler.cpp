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
#include "ims_base_handler.h"

namespace OHOS {
namespace Telephony {
ImsBaseHandler::ImsBaseHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner)
    : AppExecFwk::EventHandler(runner)
{
}

void ImsBaseHandler::ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event)
{
    TELEPHONY_LOGI("Get event id %{public}d", event->GetInnerEventId());
}

void ImsBaseHandler::SetSlotId(int32_t slotId)
{
    slotId_ = slotId;
}

int32_t ImsBaseHandler::GetSlotId()
{
    return slotId_;
}
} // Telephony
} // OHOS

