/*
 * Copyright (C) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef TELEPHONY_IMS_TEST_H
#define TELEPHONY_IMS_TEST_H
#include <securec.h>

#include "accesstoken_kit.h"
#include "call_manager_errors.h"
#include "cellular_call_interface.h"
#include "cellular_call_ipc_interface_code.h"
#include "core_manager_inner.h"
#include "core_service_client.h"
#include "gtest/gtest.h"
#include "ims_core_service_client.h"
#include "ims_core_service_proxy.h"
#include "iservice_registry.h"
#include "surface_utils.h"
#include "system_ability_definition.h"
#include "telephony_log_wrapper.h"
#include "telephony_permission.h"
#include "token_setproc.h"
#include "ims_video_call_control.h"

namespace OHOS {
namespace Telephony {
using namespace Security::AccessToken;
using Security::AccessToken::AccessTokenID;

inline HapInfoParams testInfoParams = {
    .bundleName = "tel_cellular_call_ims_gtest",
    .userID = 1,
    .instIndex = 0,
    .appIDDesc = "test",
    .isSystemApp = true,
};

inline PermissionDef testConnectImsServiceDef = {
    .permissionName = "ohos.permission.CONNECT_IMS_SERVICE",
    .bundleName = "tel_cellular_call_ims_gtest",
    .grantMode = 1, // SYSTEM_GRANT
    .label = "label",
    .labelId = 1,
    .description = "Test cellular call",
    .descriptionId = 1,
    .availableLevel = APL_SYSTEM_BASIC,
};

inline PermissionStateFull testConnectImsServiceState = {
    .grantFlags = { 2 }, // PERMISSION_USER_SET
    .grantStatus = { PermissionState::PERMISSION_GRANTED },
    .isGeneral = true,
    .permissionName = "ohos.permission.CONNECT_IMS_SERVICE",
    .resDeviceID = { "local" },
};

inline PermissionDef testPermPlaceCallDef = {
    .permissionName = "ohos.permission.CONNECT_CELLULAR_CALL_SERVICE",
    .bundleName = "tel_cellular_call_ims_gtest",
    .grantMode = 1, // SYSTEM_GRANT
    .label = "label",
    .labelId = 1,
    .description = "Test cellular call",
    .descriptionId = 1,
    .availableLevel = APL_SYSTEM_BASIC,
};

inline PermissionStateFull testPlaceCallState = {
    .grantFlags = { 2 }, // PERMISSION_USER_SET
    .grantStatus = { PermissionState::PERMISSION_GRANTED },
    .isGeneral = true,
    .permissionName = "ohos.permission.CONNECT_CELLULAR_CALL_SERVICE",
    .resDeviceID = { "local" },
};

inline PermissionDef testGetTelephonyStateDef = {
    .permissionName = "ohos.permission.GET_TELEPHONY_STATE",
    .bundleName = "tel_cellular_call_ims_gtest",
    .grantMode = 1, // SYSTEM_GRANT
    .label = "label",
    .labelId = 1,
    .description = "Test cellular call",
    .descriptionId = 1,
    .availableLevel = APL_SYSTEM_BASIC,
};

inline PermissionStateFull testGetTelephonyState = {
    .grantFlags = { 2 }, // PERMISSION_USER_SET
    .grantStatus = { PermissionState::PERMISSION_GRANTED },
    .isGeneral = true,
    .permissionName = "ohos.permission.GET_TELEPHONY_STATE",
    .resDeviceID = { "local" },
};

inline HapPolicyParams testPolicyParams = {
    .apl = APL_SYSTEM_BASIC,
    .domain = "test.domain",
    .permList = { testPermPlaceCallDef, testConnectImsServiceDef, testGetTelephonyStateDef },
    .permStateList = { testPlaceCallState, testConnectImsServiceState, testGetTelephonyState },
};

class AccessToken {
public:
    AccessToken()
    {
        currentID_ = GetSelfTokenID();
        AccessTokenIDEx tokenIdEx = AccessTokenKit::AllocHapToken(testInfoParams, testPolicyParams);
        accessID_ = tokenIdEx.tokenIdExStruct.tokenID;
        SetSelfTokenID(tokenIdEx.tokenIDEx);
    }
    ~AccessToken()
    {
        AccessTokenKit::DeleteToken(accessID_);
        SetSelfTokenID(currentID_);
    }

private:
    AccessTokenID currentID_ = 0;
    AccessTokenID accessID_ = 0;
};
} // namespace Telephony
} // namespace OHOS

#endif // TELEPHONY_IMS_TEST_H
