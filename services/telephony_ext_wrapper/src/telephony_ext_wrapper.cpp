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

#include "telephony_ext_wrapper.h"
#include <dlfcn.h>
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
namespace {
const std::string TELEPHONY_EXT_WRAPPER_PATH = "libtelephony_ext_service.z.sp";
} // namespace

TelephonyExtWrapper::TelephonyExtWrapper() {}
TelephonyExtWrapper::~TelephonyExtWrapper()
{
    TELEPHONY_LOGI("TelephonyExtWrapper::~TelephonyExtWrapper() start");
    if (handler_ != nullptr) {
        dlclose(handler_);
        handler_ = nullptr;
    }
}

void TelephonyExtWrapper::InitTelephonyExtWrapper()
{
    TELEPHONY_LOGI("TelephonyExtWrapper::InitTelephonyExtWrapper() start");
    InitTelephonyExtWrapperForCellularCall();
}

void TelephonyExtWrapper::InitTelephonyExtWrapperForCellularCall()
{
    handler_ = dlopen(TELEPHONY_EXT_WRAPPER_PATH.c_str(), RTLD_NOW);
    if (handler_ == nullptr) {
        TELEPHONY_LOGE("libtelephnoy ext service file load failed!");
        return;
    }
    isNeedRemoveMmi_ = (IsNeedRemoveMmi)dlsym(handler_, "IsNeedRemoveMmiExt");
    isNeedMmiToNormalCall_ =  (IsNeedMmiToNormalCall)dlsym(handler_, "IsNeedChangeMmiToNormalCallExt");
    isUssdOkForRelease_ = (IsUssdOkForRelease)dlsym(handler_, "IsUssdOkForReleaseExt");
    mmiCodeUnescapehtml_ = (MmiCodeUnescapehtml)dlsym(handler_, "MmiCodeUnescapehtmlExt");
    TELEPHONY_LOGI("init success");
}
} // namespace Telephony
} // namespace OHOS