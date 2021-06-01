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

#ifndef CELLULAR_CALL_STUB_H
#define CELLULAR_CALL_STUB_H

#include "cellular_call_data_struct.h"
#include "cellular_call_interface.h"
#include "cellular_call_hilog.h"
#include "iremote_stub.h"

namespace OHOS {
namespace CellularCall {
class CellularCallStub : public IRemoteStub<CellularCallInterface> {
public:
    /**
     * CellularCallStub Constructors
     */
    CellularCallStub();

    /**
     * ~CellularCallStub Destructor
     */
    ~CellularCallStub();

    /**
     * OnRemoteRequest
     *
     * @param code
     * @param data
     * @param reply
     * @param option
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    virtual int OnRemoteRequest(
        uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option) override;

    static constexpr HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, LOG_DOMAIN, "CellularCallStub"};

    /**
     * Call management dial interface
     *
     * @param CellularCallInfo, dial param.
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int Dial(const CellularCallInfo &callInfo) override;

    /**
     * End.
     *
     * @param CellularCallInfo, End param.
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int End(const CellularCallInfo &callInfo) override;

    /**
     * Reject.
     *
     * @param CellularCallInfo, Reject param.
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int Reject(const CellularCallInfo &callInfo) override;

    /**
     * Answer.
     *
     * @param CellularCallInfo, Answer param.
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int Answer(const CellularCallInfo &callInfo) override;

    /**
     * IsUrgentCall.
     *
     * @param phoneNum
     * @param slotId
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int IsUrgentCall(const std::string &phoneNum, int32_t slotId) override;

    /**
     * RegisterCallBack
     *
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int RegisterCallManagerCallBack(const sptr<TelephonyCallManager::ICallStatusCallback> &callback) override;

    /**
     * UnRegister CallBack
     *
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int UnRegisterCallManagerCallBack() override;

private:
    /**
     * Dial Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int DialInner(MessageParcel &data, MessageParcel &reply);

    /**
     * End Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int EndInner(MessageParcel &data, MessageParcel &reply);

    /**
     * Reject Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int RejectInner(MessageParcel &data, MessageParcel &reply);

    /**
     * Answer Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int AnswerInner(MessageParcel &data, MessageParcel &reply);

    /**
     * Is Emergency Call Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int IsUrgentCallInner(MessageParcel &data, MessageParcel &reply);

    /**
     * Register Call Back Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int RegisterCallBackInner(MessageParcel &data, MessageParcel &reply);

    /**
     * UnRegister Call Back Inner.
     * @param data  send data
     * @param reply Received data
     * @return Returns TELEPHONY_NO_ERROR on success, others on failure.
     */
    int UnRegisterCallBackInner(MessageParcel &data, MessageParcel &reply);

private:
    using RequestFuncType = int (CellularCallStub::*)(MessageParcel &data, MessageParcel &reply);
    std::map<uint32_t, RequestFuncType> requestFuncMap_;
};
} // namespace CellularCall
} // namespace OHOS

#endif // CELLULAR_CALL_STUB_H
