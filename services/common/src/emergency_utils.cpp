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

#include "emergency_utils.h"

#include "shortnumberinfo.h"

#include "cellular_call_config.h"
#include "mmi_code_utils.h"
#include "module_service_utils.h"

namespace OHOS {
namespace Telephony {
bool EmergencyUtils::IsEmergencyCall(int32_t slotId, const std::string &phoneNum)
{
    if (phoneNum.empty()) {
        TELEPHONY_LOGI("IsEmergencyCall return, phoneNum is empty.");
        return false;
    }

    if (phoneNum.find('@') != std::string::npos || phoneNum.find("%40") != std::string::npos) {
        TELEPHONY_LOGI("IsEmergencyCall return, phoneNum is not emergency.");
        return false;
    }

    if (phoneNum.front() == '+') {
        TELEPHONY_LOGI("IsEmergencyCall return, phoneNum is not emergency.");
        return false;
    }

    return IsEmergencyCallProcessing(slotId, phoneNum);
}

bool EmergencyUtils::IsEmergencyCallProcessing(int32_t slotId, const std::string &formatString)
{
    TELEPHONY_LOGI("IsEmergencyCallProcessing entry.");
    std::vector<std::string> emergencyNumList = {
        "110", "120", "119", "122", "12395", "114", "112", "000", "911", "08", "118", "999",
    };
    if (std::find(emergencyNumList.begin(), emergencyNumList.end(), formatString) != emergencyNumList.end()) {
        TELEPHONY_LOGI("IsEmergencyCallProcessing, Complies with local configuration data.");
        return true;
    }
    CellularCallConfig config;
    ModuleServiceUtils dependDataObtain;
    std::string countryIsoCode = dependDataObtain.GetNetworkCountryCode(slotId);
    std::vector<EmergencyInfo> eccCallList = config.GetEccCallList(slotId);
    for (auto it = eccCallList.begin(); it != eccCallList.end(); it++) {
        if (countryIsoCode == it->mcc && formatString == it->eccNum) {
            TELEPHONY_LOGI("IsEmergencyCallProcessing, Complies with sim data.");
            return true;
        }
    }
    if (!countryIsoCode.empty()) {
        TELEPHONY_LOGI("IsEmergencyCallProcessing countryIsoCode is not empty");
        i18n::phonenumbers::ShortNumberInfo shortNumberInfo;
        transform(countryIsoCode.begin(), countryIsoCode.end(), countryIsoCode.begin(), ::toupper);
        return shortNumberInfo.IsEmergencyNumber(formatString, countryIsoCode);
    }
    TELEPHONY_LOGI("IsEmergencyCallProcessing, not an emergency number.");
    return false;
}
} // namespace Telephony
} // namespace OHOS
