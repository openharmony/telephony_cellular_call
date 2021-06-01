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

#include <iostream>

#include "securec.h"

#include "cellular_call_interface.h"
#include "ipc_skeleton.h"
#include "iservice_registry.h"
#include "system_ability_definition.h"

namespace OHOS {
namespace CellularCall {
int Dial(sptr<CellularCall::CellularCallInterface> telephonyService)
{
    printf("test Dial entry.\n");
    OHOS::CellularCall::CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        printf("CellularCallService return, memset_s failed. \n");
        return -1;
    }
    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    callInfo.callType = OHOS::TYPE_CS;
    callInfo.slotId = 1;
    callInfo.phoneNetType = OHOS::PHONE_TYPE_GSM;
    telephonyService->Dial(callInfo);
    return 0;
}

int End(sptr<CellularCall::CellularCallInterface> telephonyService)
{
    printf("test End entry.\n");
    OHOS::CellularCall::CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        printf("CellularCallService return, memset_s failed. \n");
        return -1;
    }

    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    callInfo.callType = OHOS::TYPE_CS;
    callInfo.slotId = 1;
    callInfo.phoneNetType = OHOS::PHONE_TYPE_GSM;

    telephonyService->End(callInfo);
    return 0;
}

int Answer(sptr<CellularCall::CellularCallInterface> telephonyService)
{
    printf("test Answer entry.\n");
    OHOS::CellularCall::CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        printf("CellularCallService return, memset_s failed. \n");
        return -1;
    }

    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    callInfo.callType = OHOS::TYPE_CS;
    callInfo.slotId = 1;
    callInfo.phoneNetType = OHOS::PHONE_TYPE_GSM;

    telephonyService->Answer(callInfo);
    return 0;
}

int Reject(sptr<CellularCall::CellularCallInterface> telephonyService)
{
    printf("test Reject entry.\n");
    OHOS::CellularCall::CellularCallInfo callInfo;
    if (memset_s(&callInfo, sizeof(callInfo), 0, sizeof(callInfo)) != EOK) {
        printf("CellularCallService return, memset_s failed. \n");
        return -1;
    }

    std::cout << "please enter the phone number:";
    std::cin >> callInfo.phoneNum;
    callInfo.videoState = 1;
    callInfo.callType = OHOS::TYPE_CS;
    callInfo.slotId = 1;
    callInfo.phoneNetType = OHOS::PHONE_TYPE_GSM;

    telephonyService->Reject(callInfo);
    return 0;
}

int IsUrgentCall(sptr<CellularCall::CellularCallInterface> telephonyService)
{
    printf("test IsUrgentCall entry.\n");
    std::cout << "please enter the phone number:";
    std::string phoneNum("");
    std::cin >> phoneNum;
    int32_t slotId = 1;
    telephonyService->IsUrgentCall(phoneNum, slotId);
    return 0;
}

int RegisterCallBack(sptr<CellularCall::CellularCallInterface> telephonyService)
{
    printf("test RegisterCallBack entry.\n");
    return 0;
}

int InputNumForInterface(sptr<CellularCall::CellularCallInterface> telephonyService)
{
    char interfaceNum = '0';
    bool loopFlag = true;
    while (loopFlag) {
        printf(
            "\n**********Unit Test Start**********\n"
            "usage: please input a cmd num:\n"
            "A:Dial\n"
            "B:End\n"
            "C:Answer\n"
            "D:Reject\n"
            "E:IsUrgentCall\n"
            "F:RegisterCallBack\n"
            "W:exit\n"
            "***********************************\n"
            "your choice: ");
        std::cin >> interfaceNum;
        switch (interfaceNum) {
            case 'A':
                Dial(telephonyService);
                break;
            case 'B':
                End(telephonyService);
                break;
            case 'C':
                Answer(telephonyService);
                break;
            case 'D':
                Reject(telephonyService);
                break;
            case 'E':
                IsUrgentCall(telephonyService);
                break;
            case 'F':
                RegisterCallBack(telephonyService);
                break;
            case 'W':
                loopFlag = false;
                std::cout << "exit..." << std::endl;
                break;
            default:
                std::cout << "please input correct cmd number..." << std::endl;
                break;
        }
    }
    return 0;
}
} // namespace CellularCall
} // namespace OHOS

using namespace OHOS;
int main()
{
    sptr<ISystemAbilityManager> systemAbilityMgr =
        SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemAbilityMgr == nullptr) {
        printf("CellularCallService Get ISystemAbilityManager failed.\n");
        return 0;
    }
    sptr<IRemoteObject> remote = systemAbilityMgr->CheckSystemAbility(TELEPHONY_CELLULAR_CALL_SYS_ABILITY_ID);
    if (remote == nullptr) {
        printf("CellularCallService Remote service not exists.\n");
        return 0;
    }
    sptr<CellularCall::CellularCallInterface> telephonyService =
        iface_cast<CellularCall::CellularCallInterface>(remote);
    CellularCall::InputNumForInterface(telephonyService);
    return 0;
}
