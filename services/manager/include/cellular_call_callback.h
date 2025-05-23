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

#ifndef TELEPHONY_CELLULAR_CALL_CALLBACK_H
#define TELEPHONY_CELLULAR_CALL_CALLBACK_H

#include "network_search_callback_base.h"
#include "cellular_call_interface.h"

namespace OHOS {
namespace Telephony {
class CellularCallCallback : public NetworkSearchCallBackBase {
public:
    CellularCallCallback();
    ~CellularCallCallback();

    /**
     * Clear the call corresponding to slotId
     *
     * @param slotId
     */
    void ClearCellularCallList(int32_t slotId) override;

    void SetReadyToCall(int32_t slotId, int32_t callType, bool isReadyToCall) override;
};
} // namespace Telephony
} // namespace OHOS
#endif // TELEPHONY_CELLULAR_CALL_CALLBACK_H
