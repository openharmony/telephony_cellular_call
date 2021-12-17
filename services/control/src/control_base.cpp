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

#include "control_base.h"

#include "standardize_utils.h"

namespace OHOS {
namespace Telephony {
ControlBase::ControlBase()
{
    TELEPHONY_LOGI("ControlBase::ControlBase");
    eventLoop_ = AppExecFwk::EventRunner::Create("ControlBase");
    if (eventLoop_ == nullptr) {
        TELEPHONY_LOGE("failed to create EventRunner");
    }
    handler_ = std::make_shared<MMIHandler>(eventLoop_);
    if (handler_ == nullptr) {
        TELEPHONY_LOGE("failed to make_shared handler_");
    }
}

bool ControlBase::IsNeedExecuteMMI(std::string &phoneString, CLIRMode &clirMode)
{
    TELEPHONY_LOGI("IsNeedExecuteMMI start");
    // Also supplementary services may be controlled using dial command according to 3GPP TS 22.030 [19].
    // An example of call forwarding on no reply for telephony with the adjustment of the
    // no reply condition timer on 25 seconds:
    // Parse the MMI code from the string
    std::unique_ptr<MMICodeUtils> mmiCodeUtils = std::make_unique<MMICodeUtils>();
    // Parse the MMI code from the string
    if (mmiCodeUtils == nullptr) {
        TELEPHONY_LOGE("IsNeedExecuteMMI return, mmiCodeUtils is nullptr");
        return false;
    }
    if (!mmiCodeUtils->IsNeedExecuteMmi(phoneString)) {
        TELEPHONY_LOGI("IsNeedExecuteMMI return, dial DEFAULT number");
        return false;
    }
    if (mmiCodeUtils->GetMMIData().serviceCode == "30" && !mmiCodeUtils->GetMMIData().dialString.empty()) {
        TELEPHONY_LOGI("IsNeedExecuteMMI, handle additional CLIR mode");
        if (mmiCodeUtils->GetMMIData().actionString == "*") {
            phoneString = mmiCodeUtils->GetMMIData().dialString;
            clirMode = CLIRMode::TRANSFER;
            return false;
        } else if (mmiCodeUtils->GetMMIData().actionString == "#") {
            phoneString = mmiCodeUtils->GetMMIData().dialString;
            clirMode = CLIRMode::INHIBITION;
            return false;
        }
    }
    if (handler_ == nullptr) {
        TELEPHONY_LOGE("IsNeedExecuteMMI return, handler_ is nullptr.");
        return false;
    }
    handler_->SendEvent(MMIHandlerId::EVENT_MMI_Id, mmiCodeUtils);
    return true;
}

bool ControlBase::IsDtmfKey(char c) const
{
    /**
     * 1. <DTMF>. A single ASCII character in the set 0 9, #,*,A D. This is interpreted as a single ASCII character
     * whose duration is set by the +VTD command. NOTE 2:	In GSM this operates only in voice mode.
     */
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'D') || c == '*' || c == '#';
}

std::shared_ptr<MMIHandler> ControlBase::GetMMIHandler()
{
    return handler_;
}

void ControlBase::SetSlotId(int32_t id)
{
    slotId_ = id;
}

int32_t ControlBase::GetSlotId() const
{
    return slotId_;
}
} // namespace Telephony
} // namespace OHOS