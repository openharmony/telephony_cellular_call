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

#ifndef TELEPHONY_CELLULAR_CALL_MMI_CODE_UTILS_H
#define TELEPHONY_CELLULAR_CALL_MMI_CODE_UTILS_H

#include <string>
#include "cellular_call_data_struct.h"

#include "cellular_call_hilog.h"

namespace OHOS {
namespace CellularCall {
class MMICodeUtils {
public:
    /**
     * MMICodeUtils constructor
     */
    MMICodeUtils();

    /**
     * ~MMICodeUtils deconstructor
     */
    virtual ~MMICodeUtils() = default;

    /**
     * @brief IsNeedExecuteMmi
     * @param analyseString
     * @param clirMode
     * @return Whether to execute the MMI
     */
    bool IsNeedExecuteMmi(const std::string &analyseString, CLIRMode &clirMode);

    /**
     * ExecuteMmiCode
     * @return bool
     */
    bool ExecuteMmiCode();

    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "MMICodeUtils"};

private:
    /**
     * Regex Match Mmi Code
     * @param analyseString
     * @return bool
     */
    bool RegexMatchMmi(std::string analyseString);

    /**
     * Set CliR Mode
     * @param clirMode
     */
    void SetCliRMode(CLIRMode &clirMode);

private:
    std::string fullString_;
    std::string actionStr_;
    std::string serviceCode_;
    std::string serviceInfoA_;
    std::string serviceInfoB_;
    std::string serviceInfoC_;
    std::string pwdString_;
    std::string dialingNumber_;
};
} // namespace CellularCall
} // namespace OHOS

#endif // TELEPHONY_CELLULAR_CALL_MMI_CODE_UTILS_H
