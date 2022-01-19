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

#ifndef CELLULAR_CALL_HANDLER_H
#define CELLULAR_CALL_HANDLER_H

#include <memory>

#include "cellular_call_data_struct.h"
#include "telephony_log_wrapper.h"
#include "cs_control.h"
#include "ims_control.h"
#include "cellular_call_register.h"

namespace OHOS {
namespace Telephony {
class CellularCallHandler : public AppExecFwk::EventHandler {
public:
    /**
     * CellularCallHandler constructor
     *
     * @param runner
     * @param server
     */
    explicit CellularCallHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner);

    /**
     * ~CellularCallHandler destructor
     */
    ~CellularCallHandler() = default;

    /**
     * ProcessEvent.
     *
     * @param CellularCallRadioResponseEvent, Process Radio Response Event .
     */
    void ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * Set Slot Id
     *
     * @param id
     */
    void SetSlotId(int32_t id);

    /**
     * Get Slot Id
     * @return id
     */
    int32_t GetSlotId();

    /**
     * DialResponse
     *
     * @param code process
     */
    void DialResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CommonResultResponse
     *
     * @param code process
     */
    void CommonResultResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SendDtmfResponse
     *
     * @param code process
     */
    void SendDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * StartDtmfResponse
     *
     * @param code process
     */
    void StartDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * StopDtmfResponse
     *
     * @param code process
     */
    void StopDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCsCallsDataResponse
     *
     * @param code process
     */
    void GetCsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetImsCallsDataResponse
     *
     * @param code process
     */
    void GetImsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallStateResponse
     *
     * @param code process
     */
    void CallStateResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallWaitingResponse
     *
     * @param code process
     */
    void CallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallConnectResponse
     *
     * @param code process
     */
    void CallConnectResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallEndResponse
     *
     * @param code process
     */
    void CallEndResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallStatusInfoResponse
     *
     * @param code process
     */
    void CallStatusInfoResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallImsServiceStatusResponse
     *
     * @param code process
     */
    void CallImsServiceStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetCallPreferenceModeResponse
     *
     * @param code process
     */
    void SetCallPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCallPreferenceModeResponse
     *
     * @param code process
     */
    void GetCallPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetLteImsSwitchStatusResponse
     *
     * @param code process
     */
    void SetLteImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetLteImsSwitchStatusResponse
     *
     * @param code process
     */
    void GetLteImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * UssdNotifyResponse
     *
     * @param code process
     */
    void UssdNotifyResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallRingBackVoiceResponse
     *
     * @param code process
     */
    void CallRingBackVoiceResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetMuteResponse
     *
     * @param code process
     */
    void SetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetMuteResponse
     *
     * @param code process
     */
    void GetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetEmergencyCallListResponse
     *
     * @param code process
     */
    void GetEmergencyCallListResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCallFailReasonResponse
     *
     * @param code process
     */
    void GetCallFailReasonResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * Set CallType
     *
     * @param callType
     */
    void SetCallType(CallType callType);

    /**
     * Update Srvcc State Report
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void UpdateSrvccStateReport(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SrvccState Completed
     */
    void SrvccStateCompleted();

public:
    const uint32_t REGISTER_HANDLER_ID = 1002;
    const uint32_t REGISTER_IMS_CALLBACK_ID = 1003;
    int32_t srvccState_ = SrvccState::SRVCC_NONE;

private:
    /**
     * Prevent violent requests
     * @return bool
     */
    bool IsCanRequestCallsData();

    /**
     * Current Time Millis
     * @return int64_t Time Millis
     */
    int64_t CurrentTimeMillis();

    /**
     * GetCsCallData
     */
    void GetCsCallData(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetImsCallData
     */
    void GetImsCallData(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * DealCsCallsDataRequest
     */
    void GetCsCallsDataRequest(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetImsCallsDataRequest.
     *
     * @param code process
     */
    void GetImsCallsDataRequest(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * Register Handler
     */
    void RegisterHandler(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * Register Ims Callback
     */
    void RegisterImsCallback(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetMMIResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetMMIResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCallWaitingResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetCallWaitingResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetClirResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetClirResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetClirResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetClirResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetClipResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetClipResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCallTransferResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetCallTransferResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetCallTransferInfoResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetCallTransferInfoResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCallRestrictionResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetCallRestrictionResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SendUssdResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SendUssdResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * InitBasicFuncMap
     */
    void InitBasicFuncMap();

    /**
     * InitConfigFuncMap
     */
    void InitConfigFuncMap();

    /**
     * InitSupplementFuncMap
     */
    void InitSupplementFuncMap();

    /**
     * InitActiveReportFuncMap
     */
    void InitActiveReportFuncMap();

    /**
     * ReportCsCallsData
     *
     * @param CallInfoList
     */
    void ReportCsCallsData(const CallInfoList &callInfoList);

    /**
     * ReportImsCallsData
     *
     * @param CallInfoList
     */
    void ReportImsCallsData(const CallInfoList &imsCallInfoList);

private:
    int32_t slotId_ = DEFAULT_SIM_SLOT_ID;
    int64_t lastTime_ = 0L;
    const int64_t FAST_DELAY_TIME = 250;
    int64_t lastCallsDataFlag_ = 0L;
    const uint32_t GET_CS_CALL_DATA_ID = 10001;
    const uint32_t GET_IMS_CALL_DATA_ID = 10002;
    int64_t delayTime_ = 500;
    using RequestFuncType = void (CellularCallHandler::*)(const AppExecFwk::InnerEvent::Pointer &event);
    std::map<uint32_t, RequestFuncType> requestFuncMap_;
    CallType callType_ = CallType::TYPE_ERR_CALL;
    std::shared_ptr<CellularCallRegister> registerInstance_ = DelayedSingleton<CellularCallRegister>::GetInstance();
};
} // namespace Telephony
} // namespace OHOS

#endif
