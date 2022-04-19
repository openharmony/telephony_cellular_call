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

#ifndef IMS_CORE_SERVICE_H
#define IMS_CORE_SERVICE_H
#include <memory>

#include "iremote_stub.h"
#include "iservice_registry.h"
#include "singleton.h"
#include "system_ability.h"
#include "system_ability_definition.h"

#include "ims_core_service_handler.h"
#include "ims_core_service_stub.h"
#include "ims_base.h"

namespace OHOS {
namespace Telephony {
enum class ServiceRunningState { STATE_STOPPED, STATE_RUNNING };

class ImsCoreService : public SystemAbility, public ImsCoreServiceStub,
    public ImsBase<ImsCoreServiceHandler>,
    public std::enable_shared_from_this<ImsCoreService> {
DECLARE_DELAYED_SINGLETON(ImsCoreService)
DECLARE_SYSTEM_ABILITY(ImsService)
public:
    void OnStart() override;

    void OnStop() override;

    bool Init() override;

    /**
     * GetImsRegistrationStatus
     *
     * @param slotId
     * @return Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t GetImsRegistrationStatus(int32_t slotId) override;

    /**
     * Register callback
     * @param sptr<ImsCoreServiceCallbackInterface>
     * #return Returns TELEPHONY_SUCCESS on success, others on failure
     */
    int32_t RegisterImsCoreServiceCallback(const sptr<ImsCoreServiceCallbackInterface> &callback) override;

    /**
     * Get proxy object pointer
     * @param ImsServiceProxyType
     * #return Returns the specify ims service object
     */
    sptr<IRemoteObject> GetProxyObjectPtr(ImsServiceProxyType proxyTpe) override;

private:
    bool InitSubService();
    bool RegisterObserver() override;
    void SetSlotIds() override;
    ServiceRunningState state_;
    std::map<uint32_t, sptr<IRemoteObject>> proxyObjectPtrMap_;
};
} // Telephony
} // OHOS
#endif // IMS_CORE_SERVICE_H
