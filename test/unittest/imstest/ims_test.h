/*
 * Copyright (C) 2021-2022 Huawei Device Co., Ltd.
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
#include "core_manager_inner.h"
#include "core_service_client.h"
#include "gtest/gtest.h"
#include "iservice_registry.h"
#include "system_ability_definition.h"
#include "token_setproc.h"

namespace OHOS {
namespace Telephony {
using namespace Security::AccessToken;
using Security::AccessToken::AccessTokenID;

HapInfoParams testInfoParams = {
    .bundleName = "tel_cellular_call_ims_gtest",
    .userID = 1,
    .instIndex = 0,
    .appIDDesc = "test",
};

PermissionDef testPermPlaceCallDef = {
    .permissionName = "ohos.permission.CONNECT_CELLULAR_CALL_SERVICE",
    .bundleName = "tel_cellular_call_ims_gtest",
    .grantMode = 1, // SYSTEM_GRANT
    .label = "label",
    .labelId = 1,
    .description = "Test cellular call",
    .descriptionId = 1,
    .availableLevel = APL_SYSTEM_BASIC,
};

PermissionStateFull testPlaceCallState = {
    .grantFlags = { 2 }, // PERMISSION_USER_SET
    .grantStatus = { PermissionState::PERMISSION_GRANTED },
    .isGeneral = true,
    .permissionName = "ohos.permission.CONNECT_CELLULAR_CALL_SERVICE",
    .resDeviceID = { "local" },
};

HapPolicyParams testPolicyParams = {
    .apl = APL_SYSTEM_BASIC,
    .domain = "test.domain",
    .permList = { testPermPlaceCallDef },
    .permStateList = { testPlaceCallState },
};

class AccessToken {
public:
    AccessToken()
    {
        currentID_ = GetSelfTokenID();
        AccessTokenIDEx tokenIdEx = AccessTokenKit::AllocHapToken(testInfoParams, testPolicyParams);
        accessID_ = tokenIdEx.tokenIdExStruct.tokenID;
        SetSelfTokenID(accessID_);
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

class ImsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();

    int32_t SetDomainPreferenceMode(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t GetDomainPreferenceMode(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetImsSwitchStatus(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t GetImsSwitchStatus(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetImsConfigString(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetImsConfigInt(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t GetImsConfig(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetImsFeatureValue(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t GetImsFeatureValue(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t CtrlCamera(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetPreviewWindow(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetDisplayWindow(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetCameraZoom(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetPauseImage(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t SetDeviceDirection(const sptr<CellularCallInterface> &telephonyService) const;
    int32_t InputNumForInterface(const sptr<CellularCallInterface> &telephonyService) const;

    bool HasSimCard(int32_t slotId)
    {
        bool hasSimCard = false;
        DelayedRefSingleton<CoreServiceClient>::GetInstance().HasSimCard(slotId, hasSimCard);
        return hasSimCard;
    }
    bool CanUseImsService(int32_t slotId, ImsServiceType type)
    {
        ImsRegInfo info;
        CoreManagerInner::GetInstance().GetImsRegStatus(slotId, type, info);
        return info.imsRegState == ImsRegState::IMS_REGISTERED;
    }

    int32_t InitCellularCallInfo(int32_t accountId, std::string phonenumber, CellularCallInfo &callInfo)
    {
        callInfo.accountId = accountId;
        callInfo.slotId = accountId;
        callInfo.index = accountId;
        callInfo.callType = CallType::TYPE_IMS;
        callInfo.videoState = 0; // 0 means audio
        if (memset_s(callInfo.phoneNum, kMaxNumberLen, 0, kMaxNumberLen) != EOK) {
            return TELEPHONY_ERR_MEMSET_FAIL;
        }
        if (phonenumber.length() > static_cast<size_t>(kMaxNumberLen)) {
            return CALL_ERR_NUMBER_OUT_OF_RANGE;
        }
        if (memcpy_s(callInfo.phoneNum, kMaxNumberLen, phonenumber.c_str(), phonenumber.length()) != EOK) {
            return TELEPHONY_ERR_MEMCPY_FAIL;
        }
        return TELEPHONY_SUCCESS;
    };

    int32_t TestDialCallByIms(int32_t slotId, std::string code)
    {
        AccessToken token;
        auto saMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
        if (saMgr == nullptr) {
            return TELEPHONY_ERR_FAIL;
        }
        auto remote = saMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
        if (remote == nullptr) {
            return TELEPHONY_ERR_FAIL;
        }
        auto telephonyService = iface_cast<CellularCallInterface>(remote);
        if (telephonyService == nullptr) {
            return TELEPHONY_ERR_FAIL;
        }
        CellularCallInfo imsCellularCallInfo;
        int32_t ret = TELEPHONY_SUCCESS;
        ret = InitCellularCallInfo(slotId, code, imsCellularCallInfo);
        if (ret != TELEPHONY_SUCCESS) {
            return ret;
        }
        // open ims, make this time use ims to test
        ret = telephonyService->SetImsSwitchStatus(slotId, true);
        if (ret != TELEPHONY_SUCCESS) {
            return ret;
        }
        ret = telephonyService->Dial(imsCellularCallInfo);
        return ret;
    };

    int32_t WriteSsBaseResult(MessageParcel &in, const SsBaseResult &ssResult)
    {
        if (!in.WriteInt32(ssResult.index)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        if (!in.WriteInt32(ssResult.result)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        if (!in.WriteInt32(ssResult.reason)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        if (!in.WriteString(ssResult.message)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        return TELEPHONY_SUCCESS;
    };

    int32_t WriteSsResult(MessageParcel &in, const SsBaseResult &ssResult, const int32_t action, const int32_t state)
    {
        int32_t ret = WriteSsBaseResult(in, ssResult);
        if (ret != TELEPHONY_SUCCESS) {
            return ret;
        }
        if (!in.WriteInt32(action)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        if (!in.WriteInt32(state)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        return TELEPHONY_SUCCESS;
    };

    int32_t WriteCallForwardResult(MessageParcel &in, const CallForwardQueryInfoList &cFQueryList )
    {
        int32_t ret = WriteSsBaseResult(in, cFQueryList.result);
        if (ret != TELEPHONY_SUCCESS) {
            return ret;
        }
        if (!in.WriteInt32(cFQueryList.callSize) || !in.WriteInt32(cFQueryList.flag)) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        if (!in.WriteInt32(static_cast<int32_t>(cFQueryList.calls.size()))) {
            return TELEPHONY_ERR_WRITE_DATA_FAIL;
        }
        for (auto call : cFQueryList.calls) {
            if (!in.WriteInt32(call.serial) || !in.WriteInt32(call.result) || !in.WriteInt32(call.status) ||
                !in.WriteInt32(call.classx) || !in.WriteString(call.number) || !in.WriteInt32(call.type) ||
                !in.WriteInt32(call.reason) || !in.WriteInt32(call.time) || !in.WriteInt32(call.startHour) ||
                !in.WriteInt32(call.startMinute) || !in.WriteInt32(call.endHour) || !in.WriteInt32(call.endMinute)) {
                return TELEPHONY_ERR_WRITE_DATA_FAIL;
            }
        }
        return TELEPHONY_SUCCESS;
    }

private:
    using RequestFuncType = int32_t (ImsTest::*)(const sptr<CellularCallInterface> &telephonyService) const;
    std::map<int32_t, RequestFuncType> requestFuncMap_;
};
} // namespace Telephony
} // namespace OHOS

#endif // TELEPHONY_IMS_TEST_H
