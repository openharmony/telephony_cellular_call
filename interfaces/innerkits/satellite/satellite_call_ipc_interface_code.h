/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#ifndef TELEPHONY_SATELLITE_CALL_IPC_INTERFACE_CODE_H
#define TELEPHONY_SATELLITE_CALL_IPC_INTERFACE_CODE_H

/* SAID:4015 */
namespace OHOS {
namespace Telephony {
enum class SatelliteCallInterfaceCode {
    /****************** basic ******************/
    SATELLITE_DIAL = 5000,
    SATELLITE_HANG_UP,
    SATELLITE_REJECT,
    SATELLITE_ANSWER,
    SATELLITE_HOLD,
    SATELLITE_UN_HOLD,
    SATELLITE_SWITCH,
    SATELLITE_CALL_STATE_CHANGE,
    SATELLITE_GET_CALL_DATA,
    SATELLITE_CALL_REGISTER_CALLBACK,
};
} // namespace Telephony
} // namespace OHOS
#endif // TELEPHONY_SATELLITE_CALL_IPC_INTERFACE_CODE_H