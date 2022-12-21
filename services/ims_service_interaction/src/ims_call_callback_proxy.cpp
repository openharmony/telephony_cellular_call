/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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

#include "ims_call_callback_proxy.h"

#include "message_option.h"
#include "message_parcel.h"

namespace OHOS {
namespace Telephony {
ImsCallCallbackProxy::ImsCallCallbackProxy(const sptr<IRemoteObject> &impl)
    : IRemoteProxy<ImsCallCallbackInterface>(impl) {}

int32_t ImsCallCallbackProxy::DialResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in, info);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    return SendResponseInfo(IMS_DIAL, in);
}

int32_t ImsCallCallbackProxy::HangUpResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in, info);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    return SendResponseInfo(IMS_HANG_UP, in);
}

int32_t ImsCallCallbackProxy::RejectWithReasonResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in, info);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    return SendResponseInfo(IMS_REJECT, in);
}

int32_t ImsCallCallbackProxy::AnswerResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in, info);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    return SendResponseInfo(IMS_ANSWER, in);
}

int32_t ImsCallCallbackProxy::HoldCallResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in, info);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    return SendResponseInfo(IMS_HOLD, in);
}

int32_t ImsCallCallbackProxy::UnHoldCallResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in, info);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    return SendResponseInfo(IMS_UN_HOLD, in);
}

int32_t ImsCallCallbackProxy::SwitchCallResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in, info);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    return SendResponseInfo(IMS_SWITCH, in);
}

int32_t ImsCallCallbackProxy::StartDtmfResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in, info);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    return SendResponseInfo(IMS_START_DTMF, in);
}

int32_t ImsCallCallbackProxy::SendDtmfResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in, info);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    return SendResponseInfo(IMS_SEND_DTMF, in);
}

int32_t ImsCallCallbackProxy::StopDtmfResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in, info);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    return SendResponseInfo(IMS_STOP_DTMF, in);
}

int32_t ImsCallCallbackProxy::CallStateChangeReport(int32_t slotId)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    return SendResponseInfo(IMS_CALL_STATE_CHANGE, in);
}

int32_t ImsCallCallbackProxy::GetImsCallsDataResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in, info);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    return SendResponseInfo(IMS_GET_CALLS_DATA, in);
}

int32_t ImsCallCallbackProxy::GetImsCallsDataResponse(int32_t slotId, const ImsCurrentCallList &callList)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&callList, sizeof(ImsCurrentCallList))) {
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    return SendResponseInfo(IMS_GET_CALLS_DATA, in);
}

int32_t ImsCallCallbackProxy::SetImsSwitchResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in, info);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }

    return SendResponseInfo(IMS_SET_SWITCH_STATUS, in);
}

int32_t ImsCallCallbackProxy::GetImsSwitchResponse(int32_t slotId, const HRilRadioResponseInfo &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in, info);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }

    return SendResponseInfo(IMS_GET_SWITCH_STATUS, in);
}

int32_t ImsCallCallbackProxy::GetImsSwitchResponse(int32_t slotId, int32_t active)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteInt32(active)) {
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_GET_SWITCH_STATUS, in);
}

int32_t ImsCallCallbackProxy::CallRingBackReport(int32_t slotId, const RingbackVoice &info)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&info, sizeof(RingbackVoice))) {
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_CALL_CRING, in);
}

int32_t ImsCallCallbackProxy::SetMuteResponse(int32_t slotId, const MuteControlResponse &response)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&response, sizeof(MuteControlResponse))) {
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_SET_MUTE, in);
}

int32_t ImsCallCallbackProxy::LastCallFailReasonResponse(int32_t slotId, const DisconnectedDetails &details)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&details, sizeof(DisconnectedDetails))) {
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_LAST_CALL_FAIL_REASON, in);
}

int32_t ImsCallCallbackProxy::SetClipResponse(int32_t slotId, const SsBaseResult &resultInfo)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&resultInfo, sizeof(SsBaseResult))) {
        TELEPHONY_LOGE("[slot%{public}d]Write SsBaseResult fail!", slotId);
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_SET_CALL_CLIP, in);
}

int32_t ImsCallCallbackProxy::GetClipResponse(int32_t slotId, const GetClipResult &result)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&result, sizeof(GetClipResult))) {
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_GET_CALL_CLIP, in);
}

int32_t ImsCallCallbackProxy::GetClirResponse(int32_t slotId, const GetClirResult &result)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&result, sizeof(GetClirResult))) {
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_GET_CALL_CLIR, in);
}

int32_t ImsCallCallbackProxy::SetClirResponse(int32_t slotId, const SsBaseResult &resultInfo)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&resultInfo, sizeof(SsBaseResult))) {
        TELEPHONY_LOGE("[slot%{public}d]Write SsBaseResult fail!", slotId);
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_SET_CALL_CLIR, in);
}

int32_t ImsCallCallbackProxy::GetCallTransferResponse(int32_t slotId, const CallForwardQueryInfoList &cFQueryList)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&cFQueryList, sizeof(CallForwardQueryInfoList))) {
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_GET_CALL_FORWARD, in);
}

int32_t ImsCallCallbackProxy::SetCallTransferResponse(int32_t slotId, const SsBaseResult &resultInfo)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&resultInfo, sizeof(SsBaseResult))) {
        TELEPHONY_LOGE("[slot%{public}d]Write SsBaseResult fail!", slotId);
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_SET_CALL_FORWARD, in);
}

int32_t ImsCallCallbackProxy::GetCallRestrictionResponse(int32_t slotId, const CallRestrictionResult &result)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&result, sizeof(CallRestrictionResult))) {
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_GET_CALL_RESTRICTION, in);
}

int32_t ImsCallCallbackProxy::SetCallRestrictionResponse(int32_t slotId, const SsBaseResult &resultInfo)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&resultInfo, sizeof(SsBaseResult))) {
        TELEPHONY_LOGE("[slot%{public}d]Write SsBaseResult fail!", slotId);
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_SET_CALL_RESTRICTION, in);
}

int32_t ImsCallCallbackProxy::GetCallWaitingResponse(int32_t slotId, const CallWaitResult &result)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&result, sizeof(CallWaitResult))) {
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_GET_CALL_WAIT, in);
}

int32_t ImsCallCallbackProxy::SetCallWaitingResponse(int32_t slotId, const SsBaseResult &resultInfo)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&resultInfo, sizeof(SsBaseResult))) {
        TELEPHONY_LOGE("[slot%{public}d]Write SsBaseResult fail!", slotId);
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_SET_CALL_WAIT, in);
}

int32_t ImsCallCallbackProxy::SetColrResponse(int32_t slotId, const SsBaseResult &resultInfo)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&resultInfo, sizeof(SsBaseResult))) {
        TELEPHONY_LOGE("[slot%{public}d]Write SsBaseResult fail!", slotId);
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_SET_CALL_COLR, in);
}

int32_t ImsCallCallbackProxy::GetColrResponse(int32_t slotId, const GetColrResult &result)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&result, sizeof(GetColrResult))) {
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_GET_CALL_COLR, in);
}

int32_t ImsCallCallbackProxy::SetColpResponse(int32_t slotId, const SsBaseResult &resultInfo)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&resultInfo, sizeof(SsBaseResult))) {
        TELEPHONY_LOGE("[slot%{public}d]Write SsBaseResult fail!", slotId);
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_SET_CALL_COLP, in);
}

int32_t ImsCallCallbackProxy::GetColpResponse(int32_t slotId, const GetColpResult &result)
{
    MessageParcel in;
    int32_t ret = WriteCommonInfo(slotId, __FUNCTION__, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&result, sizeof(GetColpResult))) {
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    return SendResponseInfo(IMS_GET_CALL_COLP, in);
}

int32_t ImsCallCallbackProxy::SendResponseInfo(int32_t eventId, MessageParcel &in)
{
    MessageOption option;
    MessageParcel out;
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(eventId, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL;
}

int32_t ImsCallCallbackProxy::WriteCommonInfo(int32_t slotId, const std::string &funcName, MessageParcel &in)
{
    if (!in.WriteInterfaceToken(ImsCallCallbackProxy::GetDescriptor())) {
        TELEPHONY_LOGE("[slot%{public}d]%{public}s:Write descriptor token fail!", slotId, funcName.c_str());
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("[slot%{public}d]%{public}s:Write slotId fail!", slotId, funcName.c_str());
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    return TELEPHONY_SUCCESS;
}

int32_t ImsCallCallbackProxy::WriteCommonInfo(
    int32_t slotId, const std::string &funcName, MessageParcel &in, const HRilRadioResponseInfo &info)
{
    int32_t ret = WriteCommonInfo(slotId, funcName, in);
    if (ret != TELEPHONY_SUCCESS) {
        return ret;
    }
    if (!in.WriteRawData((const void *)&info, sizeof(HRilRadioResponseInfo))) {
        TELEPHONY_LOGE("[slot%{public}d]%{public}s:Write info fail!", slotId, funcName.c_str());
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    return TELEPHONY_SUCCESS;
}
} // namespace Telephony
} // namespace OHOS
