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

#ifndef IMS_SMS_HANDLER_H
#define IMS_SMS_HANDLER_H
#include <map>

#include "ims_base_handler.h"
#include "telephony_types.h"

namespace OHOS {
namespace Telephony {
class ImsSmsHandler : public ImsBaseHandler {
public:
    explicit ImsSmsHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner);

    ~ImsSmsHandler();

    void ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event) override;

private:
    using ImsSmsHandlerFunc = void (ImsSmsHandler::*)(const AppExecFwk::InnerEvent::Pointer &);

    void ImsSendMessageResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void ImsSetSmsConfigResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void ImsGetSmsConfigResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void ImsServiceStatusReport(const AppExecFwk::InnerEvent::Pointer &event);

    void InitRequestFuncMap();

    std::map<uint32_t, ImsSmsHandlerFunc> requestFuncMap_;
};
} // Telephony
} // OHOS
#endif // IMS_SMS_HANDLER_H
