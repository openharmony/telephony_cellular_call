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
#define PRIVATE PUBLIC
#define PROTECTED PUBLIC
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
#include "core_service_client.h"
#include "gtest/gtest.h"
#include "securec.h"
#include "ims_core_service_client.h"

namespace OHOS {
namespace Telephony {
using namespace testing::ext;
const std::string PHONE_NUMBER = "0000000";
const int32_t DEFAULT_INDEX = 1;

class ImsCallbackProxyTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
    bool HasSimCard(int32_t slotId)
    {
        bool hasSimCard = false;
        DelayedRefSingleton<CoreServiceClient>::GetInstance().HasSimCard(slotId, hasSimCard);
        return hasSimCard;
    }
};

void ImsCallbackProxyTest::SetUpTestCase(void)
{
    // step 3: Set Up Test Case
    std::cout << "---------- ImsCoreServiceClient start ------------" << std::endl;
    DelayedSingleton<ImsCoreServiceClient>::GetInstance()->Init();
}

void ImsCallbackProxyTest::TearDownTestCase(void) {}

void ImsCallbackProxyTest::SetUp(void) {}

void ImsCallbackProxyTest::TearDown(void) {}

/**
 * @tc.number   cellular_call_ImsCallCallbackProxy_0001
 * @tc.name     Test for ImsCallCallbackProxy
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackProxyTest, cellular_call_ImsCallCallbackProxy_0001, Function | MediumTest | Level3)
{
    const sptr<ImsCallCallbackInterface> imsCallCallback_ = (std::make_unique<ImsCallCallbackStub>()).release();
    auto callCallbackProxy =
        (std::make_unique<ImsCallCallbackProxy>(imsCallCallback_->AsObject().GetRefPtr())).release();
    ASSERT_TRUE(callCallbackProxy != nullptr);
}

/**
 * @tc.number   cellular_call_ImsCallCallbackProxy_0002
 * @tc.name     Test for ImsCallCallbackProxy
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackProxyTest, cellular_call_ImsCallCallbackProxy_0002, Function | MediumTest | Level3)
{
    const sptr<ImsCallCallbackInterface> imsCallCallback_ = (std::make_unique<ImsCallCallbackStub>()).release();
    auto callCallbackProxy =
        (std::make_unique<ImsCallCallbackProxy>(imsCallCallback_->AsObject().GetRefPtr())).release();
    ASSERT_TRUE(callCallbackProxy != nullptr);
}

/**
 * @tc.number   cellular_call_ImsCallCallbackProxy_0003
 * @tc.name     Test for ImsCallCallbackProxy
 * @tc.desc     Function test
 */
HWTEST_F(ImsCallbackProxyTest, cellular_call_ImsCallCallbackProxy_0003, Function | MediumTest | Level3)
{
    const sptr<ImsCallCallbackInterface> imsCallCallback_ = (std::make_unique<ImsCallCallbackStub>()).release();
    auto callCallbackProxy =
        (std::make_unique<ImsCallCallbackProxy>(imsCallCallback_->AsObject().GetRefPtr())).release();
    ASSERT_TRUE(callCallbackProxy != nullptr);
}
} // namespace Telephony
} // namespace OHOS
