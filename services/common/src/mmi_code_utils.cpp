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

#include "mmi_code_utils.h"

#include <regex>

#include "securec.h"

#include "cellular_call_hilog.h"

namespace OHOS {
namespace CellularCall {
MMICodeUtils::MMICodeUtils()
{
    fullString_ = "";
    actionStr_ = "";
    serviceCode_ = "";
    serviceInfoA_ = "";
    serviceInfoB_ = "";
    serviceInfoC_ = "";
    pwdString_ = "";
    dialingNumber_ = "";
}

bool MMICodeUtils::IsNeedExecuteMmi(const std::string &analyseString, CLIRMode &clirMode)
{
    if (analyseString.empty()) {
        HILOG_INFO("IsNeedExecuteMmi return, analyseString is empty.");
        return false;
    }
    if (!RegexMatchMmi(analyseString)) {
        return false;
    }
    SetCliRMode(clirMode);
    return false;
}

bool MMICodeUtils::ExecuteMmiCode()
{
    if (fullString_.empty() && actionStr_.empty() && serviceCode_.empty() && serviceInfoA_.empty() &&
        serviceInfoB_.empty() && serviceInfoC_.empty() && pwdString_.empty() && dialingNumber_.empty()) {
        HILOG_INFO("MMICodeUtils::ExecuteMmiCode processCode: all string empty.");
        return false;
    }
    return true;
}

bool MMICodeUtils::RegexMatchMmi(std::string analyseString)
{
    std::string patternStr =
        "((\\*|#|\\*#|\\*\\*|##)(\\d{2,3})(\\*([^*#]*)(\\*([^*#]*)(\\*([^*#]*)(\\*([^*#]*))?)"
        "?)?)?"
        "#)(.*)";
    std::regex pattern(patternStr);
    std::smatch results;
    if (regex_match(analyseString, results, pattern)) {
        int32_t fullString = 0;
        int32_t action = 1;
        int32_t serviceCode = 2;
        int32_t sia = 4;
        int32_t sib = 6;
        int32_t sic = 8;
        int32_t pwdConfirm = 10;
        int32_t dialingNumber = 11;
        fullString_ = results.str(fullString);
        actionStr_ = results.str(action);
        serviceCode_ = results.str(serviceCode);
        serviceInfoA_ = results.str(sia);
        serviceInfoB_ = results.str(sib);
        serviceInfoC_ = results.str(sic);
        pwdString_ = results.str(pwdConfirm);
        dialingNumber_ = results.str(dialingNumber);
    }
    return false;
}

void MMICodeUtils::SetCliRMode(CLIRMode &clirMode)
{
    std::string clip = "30";
    if (!serviceCode_.empty() && serviceCode_ == clip && !dialingNumber_.empty() && !actionStr_.empty()) {
        if (actionStr_ == "*") {
            clirMode = TRANSFER;
        }
        if (actionStr_ == "#") {
            clirMode = INHIBITION;
        }
    }
}
} // namespace CellularCall
} // namespace OHOS
