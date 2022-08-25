/*
 * Copyright (C) 2021-2022 Huawei Device Co., Ltd.
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

#include "cellular_call_config.h"
#include "cellular_call_data_struct.h"
#include "cellular_call_register.h"
#include "common_event.h"
#include "common_event_manager.h"
#include "common_event_support.h"
#include "cs_control.h"
#include "ims_control.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
class CellularCallHandler : public AppExecFwk::EventHandler, public EventFwk::CommonEventSubscriber {
public:
    /**
     * CellularCallHandler constructor
     *
     * @param runner
     * @param subscriberInfo
     */
    explicit CellularCallHandler(const std::shared_ptr<AppExecFwk::EventRunner> &runner,
        const EventFwk::CommonEventSubscribeInfo &subscriberInfo);

    /**
     * ~CellularCallHandler destructor
     */
    ~CellularCallHandler() = default;

    /**
     * ProcessEvent.
     *
     * @param CellularCallRadioResponseEvent, Process Radio Response Event .
     */
    void ProcessEvent(const AppExecFwk::InnerEvent::Pointer &event) override;

    /**
     * Receive Operator Config Change event and process.
     *
     * @param CommonEventData, Process Operator Config Change .
     */
    void OnReceiveEvent(const EventFwk::CommonEventData &data) override;

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
     * RegisterImsCallCallbackHandler()
     */
    void RegisterImsCallCallbackHandler();

    /**
     * SimStateChangeReport
     *
     * @param code process
     */
    void SimStateChangeReport(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SimRecordsLoadedReport
     *
     * @param code process
     */
    void SimRecordsLoadedReport(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * DialResponse
     *
     * @param code process
     */
    void DialResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * Handling quest result event id
     *
     * @param code process
     * @param eventInfo cellularcall event info
     */
    void CommonResultEventHandling(const AppExecFwk::InnerEvent::Pointer &event, CellularCallEventInfo &eventInfo);

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
     * CsCallStatusInfoReport
     *
     * @param event
     */
    void CsCallStatusInfoReport(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * ImsCallStatusInfoReport
     *
     * @param event
     */
    void ImsCallStatusInfoReport(const AppExecFwk::InnerEvent::Pointer &event);

    void ReportEccChanged(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetDomainPreferenceModeResponse
     *
     * @param code process
     */
    void SetDomainPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetDomainPreferenceModeResponse
     *
     * @param code process
     */
    void GetDomainPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetImsSwitchStatusResponse
     *
     * @param code process
     */
    void SetImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetImsSwitchStatusResponse
     *
     * @param code process
     */
    void GetImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * UssdNotifyResponse
     *
     * @param code process
     */
    void UssdNotifyResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SsNotifyResponse
     *
     * @param code process
     */
    void SsNotifyResponse(const AppExecFwk::InnerEvent::Pointer &event);

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
     * SetEmergencyCallListResponse
     *
     * @param code process
     */
    void SetEmergencyCallListResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCallFailReasonResponse
     *
     * @param code process
     */
    void GetCallFailReasonResponse(const AppExecFwk::InnerEvent::Pointer &event);

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
    const uint32_t REGISTER_HANDLER_ID = 10003;
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
     * SendUnlockPinPukResponse
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void SendUnlockPinPukResponse(const AppExecFwk::InnerEvent::Pointer &event);

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
    void ReportImsCallsData(const ImsCurrentCallList &imsCallInfoList);

    /**
     * Handle when receive Operator Config Changed event.
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void HandleOperatorConfigChanged(const AppExecFwk::InnerEvent::Pointer &event);

private:
    void CellularCallIncomingStartTrace(const int32_t state);
    void CellularCallIncomingFinishTrace(const int32_t state);
    int32_t slotId_ = DEFAULT_SIM_SLOT_ID;
    int64_t lastTime_ = 0L;
    const int64_t FAST_DELAY_TIME = 250;
    int64_t lastCallsDataFlag_ = 0L;
    const uint32_t GET_CS_CALL_DATA_ID = 10001;
    const uint32_t GET_IMS_CALL_DATA_ID = 10002;
    const uint32_t OPERATOR_CONFIG_CHANGED_ID = 10004;
    int64_t delayTime_ = 100;
    using RequestFuncType = void (CellularCallHandler::*)(const AppExecFwk::InnerEvent::Pointer &event);
    std::map<uint32_t, RequestFuncType> requestFuncMap_;
    std::shared_ptr<CellularCallRegister> registerInstance_ = DelayedSingleton<CellularCallRegister>::GetInstance();
};
} // namespace Telephony
} // namespace OHOS

#endif
