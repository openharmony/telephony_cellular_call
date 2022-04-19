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

#ifndef IMS_CORE_SERVICE_HANDLER_H
#define IMS_CORE_SERVICE_HANDLER_H
#include <map>

#include "telephony_types.h"
#include "ims_base_handler.h"

namespace OHOS {
namespace Telephony {
class ImsCoreServiceHandler : public ImsBaseHandler {
public:
    explicit ImsCoreServiceHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner);

    ~ImsCoreServiceHandler();

    void ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event) override;

private:
    void ImsServiceStatusReport(const AppExecFwk::InnerEvent::Pointer &event);
    void ImsNetworkStateChange(const AppExecFwk::InnerEvent::Pointer &event);
    void ImsRegistrationStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    using ImsCoreServiceHandlerFunc = void (ImsCoreServiceHandler::*)(const AppExecFwk::InnerEvent::Pointer &);
    void InitRequestFuncMap();
    std::map<uint32_t, ImsCoreServiceHandlerFunc> requestFuncMap_;
};
} // Telephony
} // OHOS
#endif // IMS_CORE_SERVICE_HANDLER_H
