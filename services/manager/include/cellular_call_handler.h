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
#include <mutex>
#include <regex>

#include "cellular_call_config.h"
#include "cellular_call_data_struct.h"
#include "cellular_call_register.h"
#include "common_event.h"
#include "common_event_manager.h"
#include "common_event_support.h"
#include "cs_control.h"
#include "ims_call_types.h"
#include "ims_control.h"
#ifdef CELLULAR_CALL_SUPPORT_SATELLITE
#include "satellite_control.h"
#endif // CELLULAR_CALL_SUPPORT_SATELLITE
#include "tel_event_handler.h"
#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {

constexpr const char *KEY_CONST_TELEPHONY_IS_USE_CLOUD_IMS_NV = "const.telephony.is_use_cloud_ims_nv";
constexpr const char *KEY_PERSIST_TELEPHONY_VOLTE_CAP_IN_CHIP = "persist.telephony.volte_cap_in_chip";
class CellularCallHandler : public TelEventHandler, public EventFwk::CommonEventSubscriber {
public:
    /**
     * CellularCallHandler constructor
     *
     * @param runner
     * @param subscriberInfo
     */
    explicit CellularCallHandler(const EventFwk::CommonEventSubscribeInfo &subscriberInfo);

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

    void RegisterImsCallCallbackHandler();
#ifdef CELLULAR_CALL_SUPPORT_SATELLITE
    void RegisterSatelliteCallCallbackHandler();
#endif // CELLULAR_CALL_SUPPORT_SATELLITE

    void SimStateChangeReport(const AppExecFwk::InnerEvent::Pointer &event);

    void FactoryReset(const AppExecFwk::InnerEvent::Pointer &event);

    void SimRecordsLoadedReport(const AppExecFwk::InnerEvent::Pointer &event);

    void SimAccountLoadedReport(const AppExecFwk::InnerEvent::Pointer &event);

    void ResidentNetworkChangeReport(const AppExecFwk::InnerEvent::Pointer &event);

    void NetworkStateChangeReport(const AppExecFwk::InnerEvent::Pointer &event);

    void DialResponse(const AppExecFwk::InnerEvent::Pointer &event);

#ifdef CELLULAR_CALL_SUPPORT_SATELLITE
    void DialSatelliteResponse(const AppExecFwk::InnerEvent::Pointer &event);
#endif // CELLULAR_CALL_SUPPORT_SATELLITE

    void CommonResultEventHandling(const AppExecFwk::InnerEvent::Pointer &event, CellularCallEventInfo &eventInfo);

    void CommonResultResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void ExecutePostDial(const AppExecFwk::InnerEvent::Pointer &event);

    void SwapCallResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void SendDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void StartDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void StopDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);

#ifdef SUPPORT_RTT_CALL
    void StartRttResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void StopRttResponse(const AppExecFwk::InnerEvent::Pointer &event);
#endif

    void GetCsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void GetImsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void CsCallStatusInfoReport(const AppExecFwk::InnerEvent::Pointer &event);

    void ImsCallStatusInfoReport(const AppExecFwk::InnerEvent::Pointer &event);

#ifdef CELLULAR_CALL_SUPPORT_SATELLITE
    void SatelliteCallStatusInfoReport(const AppExecFwk::InnerEvent::Pointer &event);
#endif // CELLULAR_CALL_SUPPORT_SATELLITE

    void ReportEccChanged(const AppExecFwk::InnerEvent::Pointer &event);

    void SetDomainPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void GetDomainPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void SetImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void GetImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void SetVoNRSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void UssdNotifyResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void SsNotifyResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void CallRingBackVoiceResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void SetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void GetMuteResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void GetEmergencyCallListResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void SetEmergencyCallListResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void GetCallFailReasonResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void UpdateSrvccStateReport(const AppExecFwk::InnerEvent::Pointer &event);

    void SrvccStateCompleted();

    void ReceiveUpdateCallMediaModeRequest(const AppExecFwk::InnerEvent::Pointer &event);

    void ReceiveUpdateCallMediaModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void HandleCallSessionEventChanged(const AppExecFwk::InnerEvent::Pointer &event);

    void HandlePeerDimensionsChanged(const AppExecFwk::InnerEvent::Pointer &event);

    void HandleCallDataUsageChanged(const AppExecFwk::InnerEvent::Pointer &event);

    void HandleCameraCapabilitiesChanged(const AppExecFwk::InnerEvent::Pointer &event);

#ifdef CELLULAR_CALL_SUPPORT_SATELLITE
    void GetSatelliteCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event);
#endif // CELLULAR_CALL_SUPPORT_SATELLITE

    /**
     * request the ut command index which will be used to report the result
     *
     * @param index
     */
    void RequestSsRequestCommandIndex(int32_t &index);

    /**
     * save the ut command which will be used to report the result
     *
     * @param SsRequestCommand
     * @param index
     */
    void SaveSsRequestCommand(const std::shared_ptr<SsRequestCommand> &utCommand, int32_t index);

    int32_t GetSsRequestCommand(int32_t index, SsRequestCommand &ss);

    void NvCfgFinishedIndication(const AppExecFwk::InnerEvent::Pointer &event);

    int32_t GetImsCapabilities(int32_t slotId);

    void GetImsCapResponse(const AppExecFwk::InnerEvent::Pointer &event);

#ifdef SUPPORT_RTT_CALL
    void ReceiveUpdateCallRttEvtResponse(const AppExecFwk::InnerEvent::Pointer &event);

    void ReceiveUpdateCallRttErrResponse(const AppExecFwk::InnerEvent::Pointer &event);
#endif

public:
    const uint32_t REGISTER_HANDLER_ID = 10003;
    const int32_t INTERNATION_CODE = 145;
    int32_t srvccState_ = SrvccState::SRVCC_NONE;

private:
    int64_t CurrentTimeMillis();
    void GetCsCallData(const AppExecFwk::InnerEvent::Pointer &event);
    void GetImsCallData(const AppExecFwk::InnerEvent::Pointer &event);
#ifdef CELLULAR_CALL_SUPPORT_SATELLITE
    void GetSatelliteCallData(const AppExecFwk::InnerEvent::Pointer &event);
#endif // CELLULAR_CALL_SUPPORT_SATELLITE
    void GetCsCallsDataRequest(const AppExecFwk::InnerEvent::Pointer &event);
    void GetImsCallsDataRequest(const AppExecFwk::InnerEvent::Pointer &event);
#ifdef CELLULAR_CALL_SUPPORT_SATELLITE
    void GetSatelliteCallsDataRequest(const AppExecFwk::InnerEvent::Pointer &event);
#endif // CELLULAR_CALL_SUPPORT_SATELLITE
    void RegisterHandler(const AppExecFwk::InnerEvent::Pointer &event);
    void GetMMIResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetCallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetClirResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetClirResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetClipResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetClipResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetColrResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetColrResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetColpResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetColpResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetCallTransferResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetCallTransferInfoResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void GetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetCallRestrictionResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SetBarringPasswordResponse(const AppExecFwk::InnerEvent::Pointer &event);
    int32_t ConfirmAndRemoveSsRequestCommand(int32_t index, int32_t &flag);
    int32_t ConfirmAndRemoveSsRequestCommand(int32_t index, int32_t &flag, int32_t &action);
    void SendUssdResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void SendUnlockPinPukResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void CloseUnFinishedUssdResponse(const AppExecFwk::InnerEvent::Pointer &event);
    void OnRilAdapterHostDied(const AppExecFwk::InnerEvent::Pointer &event);

    void InitBasicFuncMap();
    void InitConfigFuncMap();
    void InitSupplementFuncMap();
    void InitActiveReportFuncMap();
#ifdef CELLULAR_CALL_SUPPORT_SATELLITE
    void InitSatelliteCallFuncMap();
#endif // CELLULAR_CALL_SUPPORT_SATELLITE
    void InitAdditionalFuncMap();
#ifdef SUPPORT_RTT_CALL
    void InitImsRttFuncMap();
#endif

    void ReportCsCallsData(const CallInfoList &callInfoList);
    void ReportNoCsCallsData(const CallInfoList &callInfoList,  const int32_t state,
        const std::shared_ptr<CSControl> &csControl);
    void ReportImsCallsData(const ImsCurrentCallList &imsCallInfoList);
    void ReportNoImsCallsData(const ImsCurrentCallList &imsCallInfoList, const int32_t state,
        const std::shared_ptr<IMSControl> &imsControl);
#ifdef CELLULAR_CALL_SUPPORT_SATELLITE
    void ReportSatelliteCallsData(const SatelliteCurrentCallList &callInfoList);
#endif // CELLULAR_CALL_SUPPORT_SATELLITE
    void HandleOperatorConfigChanged(const AppExecFwk::InnerEvent::Pointer &event);
    void UpdateRsrvccStateReport(const AppExecFwk::InnerEvent::Pointer &event);
    void ProcessRedundantCode(CallInfoList &callInfoList);
    void ProcessCsPhoneNumber(CallInfoList &list);
    void ProcessImsPhoneNumber(ImsCurrentCallList &list);
    void replacePrefix(std::string &number);
    void HandleCallDisconnectReason(RilDisconnectedReason reason, const std::string &message);
    void UpdateImsConfiguration();
    void GetImsSwitchStatusRequest();

    /**
     * If radio state change get call manager service
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void RadioStateChangeProcess(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * If get radio state on, get call manager service
     *
     * @param AppExecFwk::InnerEvent::Pointer
     */
    void GetRadioStateProcess(const AppExecFwk::InnerEvent::Pointer &event);
#ifdef CALL_MANAGER_AUTO_START_OPTIMIZE
    void StartCallManagerService();
#endif

private:
    void CellularCallIncomingStartTrace(const int32_t state);
    void CellularCallIncomingFinishTrace(const int32_t state);
#ifdef BASE_POWER_IMPROVEMENT_FEATURE
    bool IsCellularCallExist();
    void ProcessFinishCommonEvent();
#endif

private:
    int32_t slotId_ = DEFAULT_SIM_SLOT_ID;
    int64_t lastCallsDataFlag_ = 0L;
    using RequestFuncType = std::function<void(const AppExecFwk::InnerEvent::Pointer &event)>;
    std::map<uint32_t, RequestFuncType> requestFuncMap_;
    std::shared_ptr<CellularCallRegister> registerInstance_ = DelayedSingleton<CellularCallRegister>::GetInstance();
    bool isDuringRSRVCC_ = false;
    int32_t indexCommand_ = 0;
    std::map<int32_t, std::shared_ptr<SsRequestCommand>> utCommandMap_;
    std::mutex mutex_;
    ImsCurrentCallList currentCallList_{};
    CallInfoList currentCsCallInfoList_{};
#ifdef BASE_POWER_IMPROVEMENT_FEATURE
    static std::shared_ptr<EventFwk::AsyncCommonEventResult> strEnterEventResult_;
    static bool isNvCfgFinish_;
#endif
};
} // namespace Telephony
} // namespace OHOS

#endif
