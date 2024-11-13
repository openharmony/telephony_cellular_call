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

#include "ims_test.h"

#define private public
#define protected public
#include "cellular_call_config.h"
#include "cellular_call_handler.h"
#include "cellular_call_proxy.h"
#include "cellular_call_register.h"
#include "cellular_call_service.h"
#include "tel_ril_call_parcel.h"
#include "ims_call_callback_proxy.h"
#include "ims_call_callback_stub.h"
#include "ims_call_client.h"
#include "ims_control.h"
#include "ims_error.h"
#include "securec.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
const int32_t SIM1_SLOTID = 0;
const std::string PHONE_NUMBER = "0000000";
const std::string PHONE_NUMBER_SECOND = "1111111";
const std::string PHONE_NUMBER_THIRD = "2222222";
const std::string PHONE_NUMBER_FOUR = "3333333";
const int32_t CELLULAR_CALL_SUCCESS = 0;
const int32_t DEFAULT_INDEX = 1;

void ImsTest::SetUpTestCase(void)
{
    // step 3: Set Up Test Case
    std::cout << "---------- ImsCoreServiceClient start ------------" << std::endl;
    DelayedSingleton<ImsCoreServiceClient>::GetInstance()->Init();
}

void ImsTest::TearDownTestCase(void)
{
    // step 3: Tear Down Test Case
}

void ImsTest::SetUp(void) {}

void ImsTest::TearDown(void)
{
    // step 3: input testcase teardown step
}
} // namespace Telephony
} // namespace OHOS
