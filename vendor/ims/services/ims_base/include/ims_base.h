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

#ifndef IMS_BASE_H
#define IMS_BASE_H
#include <memory>
#include <string>
#include <vector>

namespace OHOS {
namespace Telephony {
template<typename ImsHandleType>
class ImsBase {
public:
    ImsBase() = default;

    virtual ~ImsBase() = default;

    virtual bool Init() = 0;

    virtual std::shared_ptr<ImsHandleType> GetHandler(int32_t slotId) final
    {
        return handlerMap_[slotId];
    }

    virtual bool CreateEventLoop(std::string loopName)
    {
        eventLoop_ = AppExecFwk::EventRunner::Create(loopName);
        if (eventLoop_ == nullptr) {
            TELEPHONY_LOGE("Failed to create EventRunner");
            return false;
        }
        return true;
    }

    virtual bool CreateHandler()
    {
        for (auto &slotId : slotIds_) {
            auto handler = std::make_shared<ImsHandleType>(eventLoop_);
            if (handler == nullptr) {
                TELEPHONY_LOGE("Create handler failed, it's nullptr");
                return false;
            }
            handlerMap_[slotId] = handler;
        }
        return true;
    }

    virtual bool RegisterObserver() = 0;

    virtual void SetSlotIds() = 0;

    virtual std::vector<int>& GetSlotIdVector() final
    {
        return slotIds_;
    }
protected:
    std::vector<int32_t> slotIds_;
    std::map<int32_t, std::shared_ptr<ImsHandleType>> handlerMap_;
    std::shared_ptr<AppExecFwk::EventRunner> eventLoop_ = nullptr;
};
} // Telephony
} // OHOS
#endif // IMS_BASE_H
