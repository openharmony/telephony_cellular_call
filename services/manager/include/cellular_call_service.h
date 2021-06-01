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

#ifndef CELLULAR_CALL_SERVICE_H
#define CELLULAR_CALL_SERVICE_H

#include <memory>

#include "singleton.h"

#include <event_runner.h>
#include "iremote_broker.h"
#include "system_ability.h"

#include "cellular_call_handler.h"
#include "cellular_call_stub.h"

namespace OHOS {
namespace CellularCall {
enum class ServiceRunningState { STATE_STOPPED, STATE_RUNNING };

class CellularCallService : public SystemAbility,
                            public CellularCallStub,
                            public std::enable_shared_from_this<CellularCallService> {
    DECLARE_DELAYED_SINGLETON(CellularCallService)
    DECLEAR_SYSTEM_ABILITY(CellularCallService)

public:
    /**
     * service OnStart
     */
    void OnStart() override;

    /**
     * service OnStop
     */
    void OnStop() override;

    /**
     * service OnDump
     */
    void OnDump() override;

    /**
     * Get Handler
     * @return CellularCallHandler
     */
    std::shared_ptr<CellularCallHandler> GetHandler();

    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "CellularCallService"};

private:
    /**
     * Init service
     * @return whether init success
     */
    bool Init();

    /**
     * Register Handler
     */
    void RegisterHandler();

private:
    ServiceRunningState state_;
    std::shared_ptr<AppExecFwk::EventRunner> eventLoop_;
    std::shared_ptr<CellularCallHandler> handler_;
    int32_t slotId_ = 1;
};
} // namespace CellularCall
} // namespace OHOS

#endif // CELLULAR_CALL_SERVICE_H
