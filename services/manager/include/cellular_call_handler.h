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

namespace OHOS {
namespace Telephony {
class CellularCallHandler : public AppExecFwk::EventHandler {
public:
    /**
     * CellularCallHandler constructor
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
     * @param id
     */
    void SetSlotId(int32_t id);

    /**
     * SetCsControl
     */
    void SetCsControl(std::shared_ptr<CSControl>);

    /**
     * GetCsControl
     * @return std::shared_ptr<CSControl>
     */
    std::shared_ptr<CSControl> GetCsControl();

    /**
     * SetImsControl
     */
    void SetImsControl(std::shared_ptr<IMSControl>);

    /**
     * GetImsControl
     * @return std::shared_ptr<IMSControl>
     */
    std::shared_ptr<IMSControl> GetImsControl();

    /**
     * DialResponse.
     *
     * @param code process
     */
    void DialResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CommonResultResponse
     * @param code process
     */
    void CommonResultResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SendDtmfResponse.
     *
     * @param code process
     */
    void SendDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * StartDtmfResponse.
     *
     * @param code process
     */
    void StartDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * StopDtmfResponse.
     *
     * @param code process
     */
    void StopDtmfResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCsCallsDataResponse.
     *
     * @param code process
     */
    void GetCsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetImsCallsDataResponse.
     *
     * @param code process
     */
    void GetImsCallsDataResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallStateResponse.
     *
     * @param code process
     */
    void CallStateResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallWaitingResponse.
     *
     * @param code process
     */
    void CallWaitingResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallConnectResponse.
     *
     * @param code process
     */
    void CallConnectResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallEndResponse.
     *
     * @param code process
     */
    void CallEndResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallEndResponse.
     *
     * @param code process
     */
    void CallStatusInfoResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * CallEndResponse.
     *
     * @param code process
     */
    void CallImsServiceStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetCallPreferenceModeResponse.
     *
     * @param code process
     */
    void SetCallPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetCallPreferenceModeResponse.
     *
     * @param code process
     */
    void GetCallPreferenceModeResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * SetLteImsSwitchStatusResponse.
     *
     * @param code process
     */
    void SetLteImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * GetLteImsSwitchStatusResponse.
     *
     * @param code process
     */
    void GetLteImsSwitchStatusResponse(const AppExecFwk::InnerEvent::Pointer &event);

    /**
     * Set CallType
     * @param callType
     */
    void SetCallType(CallType callType);

public:
    const uint32_t REGISTER_HANDLER_ID = 1002;

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
     * ThreadRegister
     */
    void RegisterHandler(const AppExecFwk::InnerEvent::Pointer &event);

private:
    int32_t slotId_ = CoreManager::DEFAULT_SLOT_ID;
    std::shared_ptr<CSControl> pCsControl_;
    std::shared_ptr<IMSControl> pImsControl_;
    int64_t lastTime_ = 0L;
    const int64_t FAST_DELAY_TIME = 250;
    int64_t lastCallsDataFlag_ = 0L;
    const uint32_t GET_CS_CALL_DATA_ID = 10001;
    const uint32_t GET_IMS_CALL_DATA_ID = 10002;
    int64_t delayTime_ = 500;
    using RequestFuncType = void (CellularCallHandler::*)(const AppExecFwk::InnerEvent::Pointer &event);
    std::map<uint32_t, RequestFuncType> requestFuncMap_;
    CallType callType_ = CallType::TYPE_ERR_CALL;
    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "CellularCallHandler"};
};
} // namespace Telephony
} // namespace OHOS

#endif
