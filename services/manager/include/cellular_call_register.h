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

#ifndef CELLULAR_CALL_REGISTER_H
#define CELLULAR_CALL_REGISTER_H

#include <map>

#include "cellular_call_connection_cs.h"
#include "i_call_status_callback.h"
#include "singleton.h"
#include "ims_call_interface.h"

namespace OHOS {
namespace Telephony {
class CellularCallRegister {
    DECLARE_DELAYED_SINGLETON(CellularCallRegister);

public:
    /**
     * ReportCallsInfo
     *
     * @param CallsReportInfo
     */
    void ReportCallsInfo(const CallsReportInfo &callsReportInfo);

    /**
     * ReportSingleCallInfo
     *
     * @param CallReportInfo
     * @param TelCallState
     */
    void ReportSingleCallInfo(const CallReportInfo &info, TelCallState callState);

    /**
     *
     * ReportEventResultInfo
     *
     * @param CellularCallEventInfo
     */
    void ReportEventResultInfo(const CellularCallEventInfo &info);

    /**
     * ReportGetWaitingResult
     *
     * @param CallWaitResponse
     */
    void ReportGetWaitingResult(const CallWaitResponse &response);

    /**
     * ReportSetWaitingResult
     *
     * @param result
     */
    void ReportSetWaitingResult(int32_t result);

    /**
     * ReportGetRestrictionResult
     *
     * @param CallRestrictionResponse
     */
    void ReportGetRestrictionResult(const CallRestrictionResponse &response);

    /**
     * ReportSetRestrictionResult
     *
     * @param result
     */
    void ReportSetRestrictionResult(int32_t result);

    /**
     * ReportGetTransferResult
     *
     * @param CallTransferResponse
     */
    void ReportGetTransferResult(const CallTransferResponse &response);

    /**
     * ReportSetTransferResult
     *
     * @param result
     */
    void ReportSetTransferResult(int32_t result);

    /**
     * ReportGetClipResult
     *
     * @param ClipResponse
     */
    void ReportGetClipResult(const ClipResponse &response);

    /**
     * ReportGetClirResult
     *
     * @param ClirResponse
     */
    void ReportGetClirResult(const ClirResponse &response);

    /**
     * ReportSetClirResult
     *
     * @param result
     */
    void ReportSetClirResult(int32_t result);

    /**
     * ReportGetLteImsSwitchResult
     *
     * @param LteImsSwitchResponse
     */
    void ReportGetLteImsSwitchResult(const LteImsSwitchResponse &lteImsSwitch);

    /**
     * ReportSetLteImsSwitchResult
     *
     * @param int32_t
     */
    void ReportSetLteImsSwitchResult(int32_t result);

    /**
     * ReportGetImsConfigResult
     *
     * @param GetImsConfigResponse
     */
    void ReportGetImsConfigResult(const GetImsConfigResponse &response);

    /**
     * ReportSetImsConfigResult
     *
     * @param int32_t
     */
    void ReportSetImsConfigResult(int32_t result);

    /**
     * ReportGetImsFeatureResult
     *
     * @param GetImsFeatureValueResponse
     */
    void ReportGetImsFeatureResult(const GetImsFeatureValueResponse &response);

    /**
     * ReportSetImsFeatureResult
     *
     * @param int32_t
     */
    void ReportSetImsFeatureResult(int32_t result);

    /**
     * ReportGetImsSwitchEnhanceModeResult
     *
     * @param GetLteEnhanceModeResponse
     */
    void ReportGetImsSwitchEnhanceModeResult(const GetLteEnhanceModeResponse &response);

    /**
     * ReportSetImsSwitchEnhanceModeResult
     *
     * @param int32_t
     */
    void ReportSetImsSwitchEnhanceModeResult(int32_t result);

    /**
     * ReportCallRingBackResult
     *
     * @param status
     */
    void ReportCallRingBackResult(int32_t status);

    /**
     * ReportSetMuteResult
     *
     * @param MuteControlResponse
     */
    void ReportSetMuteResult(const MuteControlResponse &response);

    /**
     * ReportGetMuteResult
     *
     * @param MuteControlResponse
     */
    void ReportGetMuteResult(const MuteControlResponse &response);

    /**
     * ReportCallFailReason
     *
     * @param int32_t
     */
    void ReportCallFailReason(int32_t reason);

    /**
     * ReportInviteToConferenceResult
     *
     * @param int32_t
     */
    void ReportInviteToConferenceResult(int32_t result);

    /**
     * ReportUpdateCallMediaModeResult
     *
     * @param int32_t
     */
    void ReportUpdateCallMediaModeResult(int32_t result);

    /**
     * ReportGetCallDataResult
     *
     * @param int32_t
     */
    void ReportGetCallDataResult(int32_t result);

    /**
     * ReportStartDtmfResult
     *
     * @param int32_t
     */
    void ReportStartDtmfResult(int32_t result);

    /**
     * ReportStopDtmfResult
     *
     * @param int32_t
     */
    void ReportStopDtmfResult(int32_t result);

    /**
     * ReportStartRttResult
     *
     * @param int32_t
     */
    void ReportStartRttResult(int32_t result);

    /**
     * ReportStopRttResult
     *
     * @param int32_t
     */
    void ReportStopRttResult(int32_t result);

    /**
     * ReportSendUssdResult
     *
     * @param int32_t
     */
    void ReportSendUssdResult(int32_t result);

    /**
     * Register CallManagerCallBack
     *
     * @param sptr<ICallStatusCallback>
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t RegisterCallManagerCallBack(const sptr<ICallStatusCallback> &callback);

    /**
     * UnRegister CallManagerCallBack
     *
     * @return Error Code: Returns TELEPHONY_SUCCESS on success, others on failure.
     */
    int32_t UnRegisterCallManagerCallBack();

private:
    sptr<ICallStatusCallback> callManagerCallBack_;
};
} // namespace Telephony
} // namespace OHOS

#endif // CELLULAR_CALL_REGISTER_H
