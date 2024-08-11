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

#define private public
#define protected public

#include "gtest/gtest.h"
#include "cellular_call_data_struct.h"
#include "call_manager_inner_type.h"
#include "mmi_code_message.h"


namespace OHOS {
namespace Telephony {
using namespace testing::ext;
class MmiCodeMessageTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};
void MmiCodeMessageTest::SetUpTestCase() {}

void MmiCodeMessageTest::TearDownTestCase() {}

void MmiCodeMessageTest::SetUp() {}

void MmiCodeMessageTest::TearDown() {}

/**
 * @tc.number   Telephony_MmiCodeMessageTest_0001
 * @tc.name     Test MmiCodeMessage CreateGetCallWaitingResultMessage
 * @tc.desc     Function test
 */
HWTEST_F(MmiCodeMessageTest, MmiCodeMessageTest_0001, Function | MediumTest | Level1)
{
    CallWaitResponse response;
    std::string resultMessage;
    std::string compareMessage;
    compareMessage.append("\n");
    compareMessage.append(SERVICE_DISABLE);
    CreateGetCallWaitingResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);

    response.status = 1;
    response.classCw = ServiceClassType::VOICE;
    resultMessage = "";
    compareMessage = "";
    compareMessage.append("\n");
    compareMessage.append(SERVICE_ENABLE_FOR);
    compareMessage.append("\nVoice");
    CreateGetCallWaitingResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);

    response.classCw = ServiceClassType::FAX;
    resultMessage = "";
    compareMessage = "";
    compareMessage.append("\n");
    compareMessage.append(SERVICE_ENABLE_FOR);
    compareMessage.append("\nFax");
    CreateGetCallWaitingResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);

    response.classCw = ServiceClassType::SHORT_MESSAGE_SERVICE;
    resultMessage = "";
    compareMessage = "";
    compareMessage.append("\n");
    compareMessage.append(SERVICE_ENABLE_FOR);
    compareMessage.append("\nMessage");
    CreateGetCallWaitingResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);

    response.classCw = ServiceClassType::DATA_CIRCUIT_SYNC;
    resultMessage = "";
    compareMessage = "";
    compareMessage.append("\n");
    compareMessage.append(SERVICE_ENABLE_FOR);
    compareMessage.append("\nSync");
    CreateGetCallWaitingResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);
}

/**
 * @tc.number   Telephony_MmiCodeMessageTest_0002
 * @tc.name     Test MmiCodeMessage CreateGetCallWaitingResultMessage
 * @tc.desc     Function test
 */
HWTEST_F(MmiCodeMessageTest, MmiCodeMessageTest_0002, Function | MediumTest | Level1)
{
    CallWaitResponse response;
    std::string resultMessage;
    std::string compareMessage;
 
    response.status = 1;
    response.classCw = ServiceClassType::DATA_CIRCUIT_ASYNC;
    resultMessage = "";
    compareMessage = "";
    compareMessage.append("\n");
    compareMessage.append(SERVICE_ENABLE_FOR);
    compareMessage.append("\nAsync");
    CreateGetCallWaitingResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);

    response.classCw = ServiceClassType::DEDICATED_PACKET_ACCESS;
    resultMessage = "";
    compareMessage = "";
    compareMessage.append("\n");
    compareMessage.append(SERVICE_ENABLE_FOR);
    compareMessage.append("\nPackage");
    CreateGetCallWaitingResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);
    
    response.classCw = ServiceClassType::DEDICATED_PAD_ACCESS;
    resultMessage = "";
    compareMessage = "";
    compareMessage.append("\n");
    compareMessage.append(SERVICE_ENABLE_FOR);
    compareMessage.append("\nPad");
    CreateGetCallWaitingResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);

    response.classCw = 256;
    resultMessage = "";
    compareMessage = "\nService was enabled for:";
    CreateGetCallWaitingResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);
}

/**
 * @tc.number   Telephony_MmiCodeMessageTest_0003
 * @tc.name     Test MmiCodeMessage GetServiceClassName
 * @tc.desc     Function test
 */
HWTEST_F(MmiCodeMessageTest, MmiCodeMessageTest_0003, Function | MediumTest | Level1)
{
    int32_t classex;
    classex = ServiceClassType::VOICE;
    EXPECT_EQ(GetServiceClassName(classex), "Voice");

    classex = ServiceClassType::FAX;
    EXPECT_EQ(GetServiceClassName(classex), "Fax");

    classex = ServiceClassType::SHORT_MESSAGE_SERVICE;
    EXPECT_EQ(GetServiceClassName(classex), "Message");

    classex = ServiceClassType::DATA_CIRCUIT_SYNC;
    EXPECT_EQ(GetServiceClassName(classex), "Sync");

    classex = ServiceClassType::DATA_CIRCUIT_ASYNC;
    EXPECT_EQ(GetServiceClassName(classex), "Async");

    classex = ServiceClassType::DEDICATED_PACKET_ACCESS;
    EXPECT_EQ(GetServiceClassName(classex), "Package");

    classex = ServiceClassType::DEDICATED_PAD_ACCESS;
    EXPECT_EQ(GetServiceClassName(classex), "Pad");

    classex = 256;
    EXPECT_EQ(GetServiceClassName(classex), "Unknow");
}

/**
 * @tc.number   Telephony_MmiCodeMessageTest_0004
 * @tc.name     Test MmiCodeMessage CreateServiceClassMessage
 * @tc.desc     Function test
 */
HWTEST_F(MmiCodeMessageTest, MmiCodeMessageTest_0004, Function | MediumTest | Level1)
{
    std::string resultMessage;
    int32_t classex = ServiceClassType::VOICE;
    CreateServiceClassMessage(resultMessage, classex);
    EXPECT_EQ(resultMessage, "\nVoice");

    classex = ServiceClassType::FAX;
    resultMessage = "";
    CreateServiceClassMessage(resultMessage, classex);
    EXPECT_EQ(resultMessage, "\nFax");

    classex = ServiceClassType::SHORT_MESSAGE_SERVICE;
    resultMessage = "";
    CreateServiceClassMessage(resultMessage, classex);
    EXPECT_EQ(resultMessage, "\nMessage");

    classex = ServiceClassType::DATA_CIRCUIT_SYNC;
    resultMessage = "";
    CreateServiceClassMessage(resultMessage, classex);
    EXPECT_EQ(resultMessage, "\nSync");

    classex = ServiceClassType::DATA_CIRCUIT_ASYNC;
    resultMessage = "";
    CreateServiceClassMessage(resultMessage, classex);
    EXPECT_EQ(resultMessage, "\nAsync");

    classex = ServiceClassType::DEDICATED_PACKET_ACCESS;
    resultMessage = "";
    CreateServiceClassMessage(resultMessage, classex);
    EXPECT_EQ(resultMessage, "\nPackage");

    classex = ServiceClassType::DEDICATED_PAD_ACCESS;
    resultMessage = "";
    CreateServiceClassMessage(resultMessage, classex);
    EXPECT_EQ(resultMessage, "\nPad");

    classex = 256;
    resultMessage = "";
    CreateServiceClassMessage(resultMessage, classex);
    EXPECT_EQ(resultMessage, "");
}

/**
 * @tc.number   Telephony_MmiCodeMessageTest_0005
 * @tc.name     Test MmiCodeMessage CreateSuppSvcQueryResultMessage
 * @tc.desc     Function test
 */
HWTEST_F(MmiCodeMessageTest, MmiCodeMessageTest_0005, Function | MediumTest | Level1)
{
    std::string resultMessage;
    int32_t result = TELEPHONY_SUCCESS;
    int32_t status = SS_DISABLED;
    std::string compareMessage;
    compareMessage.append("\n");
    compareMessage.append(SERVICE_DISABLE);
    CreateSuppSvcQueryResultMessage(resultMessage, result , status);
    EXPECT_EQ(resultMessage, compareMessage);

    status = SS_ENABLED;
    resultMessage = "";
    compareMessage = "";
    compareMessage.append("\n");
    compareMessage.append(SERVICE_ENABLE);
    CreateSuppSvcQueryResultMessage(resultMessage, result , status);
    EXPECT_EQ(resultMessage, compareMessage);

    result = TELEPHONY_ERROR;
    resultMessage = "";
    compareMessage = "";
    CreateSuppSvcQueryResultMessage(resultMessage, result, status);
    EXPECT_EQ(resultMessage, compareMessage);
}

/**
 * @tc.number   Telephony_MmiCodeMessageTest_0006
 * @tc.name     Test MmiCodeMessage CreateGetCallTransferResultMessage
 * @tc.desc     Function test
 */
HWTEST_F(MmiCodeMessageTest, MmiCodeMessageTest_0006, Function | MediumTest | Level1)
{
    std::string resultMessage;
    std::string compareMessage;
    CallTransferResponse response;
    
    response.classx = ServiceClassType::VOICE;
    response.result = TELEPHONY_ERROR;
    CreateGetCallTransferResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);

    response.result = TELEPHONY_SUCCESS;
    resultMessage = "";
    compareMessage = "\nVoice: Not forwarded";
    CreateGetCallTransferResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);

    response.classx = ServiceClassType::FAX;
    compareMessage = "\nFax: Not forwarded";
    resultMessage = "";
    CreateGetCallTransferResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);

    response.classx = ServiceClassType::SHORT_MESSAGE_SERVICE;
    compareMessage = "\nMessage: Not forwarded";
    resultMessage = "";
    CreateGetCallTransferResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);

    response.classx = ServiceClassType::DATA_CIRCUIT_SYNC;
    compareMessage = "\nSync: Not forwarded";
    resultMessage = "";
    CreateGetCallTransferResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);

    response.classx = ServiceClassType::DATA_CIRCUIT_ASYNC;
    compareMessage = "\nAsync: Not forwarded";
    resultMessage = "";
    CreateGetCallTransferResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);
}
 
 /**
 * @tc.number   Telephony_MmiCodeMessageTest_0007
 * @tc.name     Test MmiCodeMessage CreateGetCallTransferResultMessage
 * @tc.desc     Function test
 */
HWTEST_F(MmiCodeMessageTest, MmiCodeMessageTest_0007, Function | MediumTest | Level1)
{
    std::string resultMessage;
    CallTransferResponse response; 

    response.classx = ServiceClassType::DEDICATED_PACKET_ACCESS;
    std::string compareMessage = "\nPackage: Not forwarded";
    CreateGetCallTransferResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);

    response.classx = ServiceClassType::DEDICATED_PAD_ACCESS;
    compareMessage = "\nPad: Not forwarded";
    resultMessage = "";
    CreateGetCallTransferResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);

    response.classx = 256;
    compareMessage = "\n";
    resultMessage = "";
    CreateGetCallTransferResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);
}

/**
 * @tc.number   Telephony_MmiCodeMessageTest_0008
 * @tc.name     Test MmiCodeMessage MakeCallTransferMessageEx
 * @tc.desc     Function test
 */
HWTEST_F(MmiCodeMessageTest, MmiCodeMessageTest_0008, Function | MediumTest | Level1)
{
    std::string resultMessage;
    CallTransferResponse response; 
    response.status = SS_ENABLED;

    int32_t classex = ServiceClassType::VOICE;
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Voice: ");

    classex = ServiceClassType::FAX;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Fax: ");

    classex = ServiceClassType::SHORT_MESSAGE_SERVICE;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Message: ");

    classex = ServiceClassType::DATA_CIRCUIT_SYNC;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Sync: ");

    classex = ServiceClassType::DATA_CIRCUIT_ASYNC;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Async: ");

    classex = ServiceClassType::DEDICATED_PACKET_ACCESS;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Package: ");

    classex = ServiceClassType::DEDICATED_PAD_ACCESS;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Pad: ");

    classex = 256;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Unknow: ");
}

/**
 * @tc.number   Telephony_MmiCodeMessageTest_0009
 * @tc.name     Test MmiCodeMessage MakeCallTransferMessageEx
 * @tc.desc     Function test
 */
HWTEST_F(MmiCodeMessageTest, MmiCodeMessageTest_0009, Function | MediumTest | Level1)
{
    std::string resultMessage;
    CallTransferResponse response; 
    response.status = SS_ENABLED;
    response.reason = TRANSFER_REASON_TYPE_NO_REPLY;

    int32_t classex = ServiceClassType::VOICE;
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Voice:  after 0 seconds");

    classex = ServiceClassType::FAX;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response, classex);
    EXPECT_EQ(resultMessage, "Fax:  after 0 seconds");

    classex = ServiceClassType::SHORT_MESSAGE_SERVICE;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Message:  after 0 seconds");

    classex = ServiceClassType::DATA_CIRCUIT_SYNC;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Sync:  after 0 seconds");

    classex = ServiceClassType::DATA_CIRCUIT_ASYNC;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Async:  after 0 seconds");

    classex = ServiceClassType::DEDICATED_PACKET_ACCESS;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Package:  after 0 seconds");

    classex = ServiceClassType::DEDICATED_PAD_ACCESS;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Pad:  after 0 seconds");

    classex = 256;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Unknow:  after 0 seconds");
}

/**
 * @tc.number   Telephony_MmiCodeMessageTest_0010
 * @tc.name     Test MmiCodeMessage MakeCallTransferMessageEx
 * @tc.desc     Function test
 */
HWTEST_F(MmiCodeMessageTest, MmiCodeMessageTest_0010, Function | MediumTest | Level1)
{
    std::string resultMessage;
    CallTransferResponse response; 
    response.status = SS_DISABLED;
  
    int32_t classex = ServiceClassType::VOICE;
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Voice: Not forwarded");

    classex = ServiceClassType::FAX;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Fax: Not forwarded");

    classex = ServiceClassType::SHORT_MESSAGE_SERVICE;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Message: Not forwarded");

    classex = ServiceClassType::DATA_CIRCUIT_SYNC;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Sync: Not forwarded");

    classex = ServiceClassType::DATA_CIRCUIT_ASYNC;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Async: Not forwarded");

    classex = ServiceClassType::DEDICATED_PACKET_ACCESS;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Package: Not forwarded");

    classex = ServiceClassType::DEDICATED_PAD_ACCESS;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Pad: Not forwarded");

    classex = 256;
    resultMessage = "";
    MakeCallTransferMessageEx(resultMessage, response , classex);
    EXPECT_EQ(resultMessage, "Unknow: Not forwarded");
}
} // namespace Telephony
} // namespace OHOS