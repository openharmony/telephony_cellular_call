/*
 * Copyright (C) 2024-2024 Huawei Device Co., Ltd.
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

#ifndef TELEPHONY_EXT_WRAPPER_H
#define TELEPHONY_EXT_WRAPPER_H

#include "nocopyable.h"
#include "singleton.h"

namespace OHOS {
namespace Telephony {
class TelephonyExtWrapper final {
DECLARE_DELAYED_REF_SINGLETON(TelephonyExtWrapper);

public:
    DISALLOW_COPY_AND_MOVE(TelephonyExtWrapper);
    void InitTelephonyExtWrapper();

    typedef bool (*IsNeedRemoveMmi)(int32_t slotId);
    typedef bool (*IsNeedMmiToNormalCall)(int32_t slotId, std::string &number);
    typedef bool (*IsUssdOkForRelease)(int32_t slotId);
    typedef void (*MmiCodeUnescapehtml)(int32_t slotId, std::string &content);

    IsNeedRemoveMmi isNeedRemoveMmi_ = nullptr;
    IsNeedMmiToNormalCall isNeedMmiToNormalCall_ = nullptr;
    IsUssdOkForRelease isUssdOkForRelease_ = nullptr;
    MmiCodeUnescapehtml mmiCodeUnescapehtml_ = nullptr;
private:
    void* handler_ = nullptr;

    void InitTelephonyExtWrapperForCellularCall();
};

#define TELEPHONY_EXT_WRAPPER ::OHOS::DelayedRefSingleton<TelephonyExtWrapper>::GetInstance()
} // namespace Telephony
} // namespace OHOS
#endif // TELEPHONY_EXT_WRAPPER_H