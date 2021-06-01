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

#ifndef TELEPHONY_CELLULAR_CALL_STANDARDIZE_UTILS_H
#define TELEPHONY_CELLULAR_CALL_STANDARDIZE_UTILS_H

#include <string>

#include "cellular_call_hilog.h"

namespace OHOS {
namespace CellularCall {
class StandardizeUtils {
public:
    /**
     * StandardizeUtils constructor
     */
    StandardizeUtils();

    /**
     * ~StandardizeUtils deconstructor
     */
    virtual ~StandardizeUtils() = default;

    /**
     * Strips separators from a phone number string
     * @param string phone number to strip
     * @return phone string stripped of separators.
     */
    std::string RemoveSeparatorsPhoneNumber(const std::string &phoneNum);

    /**
     * @brief Standardize phone number
     * @param string phone number to standardize
     * @return Returns Standardize newString.
     */
    std::string StandardizePhoneNumber(const std::string &phoneNum);

    /**
     * @brief When there are converted maps, convert according to the map configuration
     * @param convertString
     * @return string
     */
    std::string ConvertNumberIfNeed(const std::string &convertString);

    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "StandardizeUtils"};
};
} // namespace CellularCall
} // namespace OHOS
#endif // TELEPHONY_CELLULAR_CALL_STANDARDIZE_UTILS_H
