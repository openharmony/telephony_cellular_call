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

void MmiCodeMessageTest::TearDownTestCase(){}

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
    compareMessage = "";
    resultMessage = "";
    compareMessage.append("\n");
    compareMessage.append(SERVICE_ENABLE_FOR);
    compareMessage.append("\nVoice");
    CreateGetCallWaitingResultMessage(resultMessage, response);
    EXPECT_EQ(resultMessage, compareMessage);
}

/**
 * @tc.number   Telephony_MmiCodeMessageTest_0002
 * @tc.name     Test MmiCodeMessage GetServiceClassName
 * @tc.desc     Function test
 */
HWTEST_F(MmiCodeMessageTest, MmiCodeMessageTest_0002, Function | MediumTest | Level1)
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
 * @tc.number   Telephony_MmiCodeMessageTest_0003
 * @tc.name     Test MmiCodeMessage CreateServiceClassMessage
 * @tc.desc     Function test
 */
HWTEST_F(MmiCodeMessageTest, MmiCodeMessageTest_0003, Function | MediumTest | Level1)
{
    int32_t classex =ServiceClassType::DEDICATED_PAD_ACCESS;
    std::string resultMessage;
    CreateServiceClassMessage(resultMessage, classex);
    EXPECT_EQ(resultMessage, "\nPad");
}

/**
 * @tc.number   Telephony_MmiCodeMessageTest_0004
 * @tc.name     Test MmiCodeMessage CreateSuppSvcQueryResultMessage
 * @tc.desc     Function test
 */
HWTEST_F(MmiCodeMessageTest, MmiCodeMessageTest_0004, Function | MediumTest | Level1)
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
    compareMessage = "";
    resultMessage = "";
    compareMessage.append("\n");
    compareMessage.append(SERVICE_ENABLE);
    CreateSuppSvcQueryResultMessage(resultMessage, result , status);
    EXPECT_EQ(resultMessage, compareMessage);
}
} // namespace Telephony
} // namespace OHOS