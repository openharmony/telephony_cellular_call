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

#include "ims_call_proxy.h"

#include "cellular_call_hisysevent.h"
#include "message_option.h"
#include "message_parcel.h"
#include "telephony_errors.h"

namespace OHOS {
namespace Telephony {
int32_t ImsCallProxy::Dial(const ImsCallInfo &callInfo, CLIRMode mode)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::Dial return, write descriptor token fail!");
        CellularCallHiSysEvent::WriteDialCallFaultEvent(callInfo.slotId, INVALID_PARAMETER, callInfo.videoState,
            TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL, "ims call proxy write descriptor token fail");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteRawData((const void *)&callInfo, sizeof(ImsCallInfo))) {
        TELEPHONY_LOGE("ImsCallProxy::Dial return, write data fail!");
        CellularCallHiSysEvent::WriteDialCallFaultEvent(callInfo.slotId, INVALID_PARAMETER, callInfo.videoState,
            TELEPHONY_ERR_WRITE_DATA_FAIL, "ims call proxy write data fail");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(mode)) {
        TELEPHONY_LOGE("ImsCallProxy::Dial return, write data fail!");
        CellularCallHiSysEvent::WriteDialCallFaultEvent(callInfo.slotId, INVALID_PARAMETER, callInfo.videoState,
            TELEPHONY_ERR_WRITE_DATA_FAIL, "ims call proxy write data fail");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::Dial return, remote is nullptr!");
        CellularCallHiSysEvent::WriteDialCallFaultEvent(callInfo.slotId, INVALID_PARAMETER, callInfo.videoState,
            TELEPHONY_ERR_LOCAL_PTR_NULL, "ims call proxy remote is nullptr");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_DIAL, in, out, option);
    if (error == ERR_NONE) {
        TELEPHONY_LOGI("ImsCallProxy::Dial return, send request success!");
        return out.ReadInt32();
    }
    CellularCallHiSysEvent::WriteDialCallFaultEvent(callInfo.slotId, INVALID_PARAMETER, callInfo.videoState,
        static_cast<int32_t>(CallErrorCode::CALL_ERROR_SEND_REQUEST_FAIL), "ims call proxy send request fail");
    return error;
}

int32_t ImsCallProxy::HangUp(const ImsCallInfo &callInfo)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::HangUp return, write descriptor token fail!");
        CellularCallHiSysEvent::WriteHangUpFaultEvent(callInfo.slotId, INVALID_PARAMETER,
            TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL, "HangUp ims call proxy write descriptor token fail");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteRawData((const void *)&callInfo, sizeof(ImsCallInfo))) {
        TELEPHONY_LOGE("ImsCallProxy::HangUp return, write data fail!");
        CellularCallHiSysEvent::WriteHangUpFaultEvent(callInfo.slotId, INVALID_PARAMETER,
            TELEPHONY_ERR_WRITE_DATA_FAIL, "HangUp ims call proxy write data fail");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::HangUp return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_HANG_UP, in, out, option);
    if (error == ERR_NONE) {
        TELEPHONY_LOGI("ImsCallProxy::HangUp return, send request success!");
        return out.ReadInt32();
    }
    CellularCallHiSysEvent::WriteHangUpFaultEvent(callInfo.slotId, INVALID_PARAMETER,
        static_cast<int32_t>(CallErrorCode::CALL_ERROR_SEND_REQUEST_FAIL), "HangUp ims call proxy send request fail");
    return error;
}

int32_t ImsCallProxy::RejectWithReason(const ImsCallInfo &callInfo, const ImsRejectReason &reason)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::RejectWithReason return, write descriptor token fail!");
        CellularCallHiSysEvent::WriteHangUpFaultEvent(callInfo.slotId, INVALID_PARAMETER,
            TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL, "Reject ims call proxy write descriptor token fail");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteRawData((const void *)&callInfo, sizeof(ImsCallInfo))) {
        TELEPHONY_LOGE("ImsCallProxy::RejectWithReason return, write callInfo fail!");
        CellularCallHiSysEvent::WriteHangUpFaultEvent(callInfo.slotId, INVALID_PARAMETER,
            TELEPHONY_ERR_IPC_CONNECT_STUB_FAIL, "Reject ims call proxy write data fail");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(reason)) {
        TELEPHONY_LOGE("ImsCallProxy::RejectWithReason return, write reason fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::RejectWithReason return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_REJECT_WITH_REASON, in, out, option);
    if (error == ERR_NONE) {
        TELEPHONY_LOGI("ImsCallProxy::RejectWithReason return, send request success!");
        return out.ReadInt32();
    }
    CellularCallHiSysEvent::WriteHangUpFaultEvent(callInfo.slotId, INVALID_PARAMETER,
        static_cast<int32_t>(CallErrorCode::CALL_ERROR_SEND_REQUEST_FAIL), "Reject ims call proxy send request fail");
    return error;
}

int32_t ImsCallProxy::Answer(const ImsCallInfo &callInfo)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::Answer return, write descriptor token fail!");
        CellularCallHiSysEvent::WriteAnswerCallFaultEvent(callInfo.slotId, INVALID_PARAMETER, callInfo.videoState,
            TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL, "ims call proxy write descriptor token fail");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteRawData((const void *)&callInfo, sizeof(ImsCallInfo))) {
        TELEPHONY_LOGE("ImsCallProxy::Answer return, write data fail!");
        CellularCallHiSysEvent::WriteAnswerCallFaultEvent(callInfo.slotId, INVALID_PARAMETER, callInfo.videoState,
            TELEPHONY_ERR_WRITE_DATA_FAIL, "ims call proxy write data fail");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::Answer return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_ANSWER, in, out, option);
    if (error == ERR_NONE) {
        TELEPHONY_LOGI("ImsCallProxy::Answer return, send request success!");
        return out.ReadInt32();
    }
    CellularCallHiSysEvent::WriteAnswerCallFaultEvent(callInfo.slotId, INVALID_PARAMETER, callInfo.videoState,
        static_cast<int32_t>(CallErrorCode::CALL_ERROR_SEND_REQUEST_FAIL), "ims call proxy send request fail");
    return error;
}

int32_t ImsCallProxy::HoldCall(int32_t slotId, int32_t callType)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::HoldCall return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::HoldCall return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(callType)) {
        TELEPHONY_LOGE("ImsCallProxy::HoldCall return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::HoldCall return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_HOLD, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::UnHoldCall(int32_t slotId, int32_t callType)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::UnHoldCall return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::UnHoldCall return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(callType)) {
        TELEPHONY_LOGE("ImsCallProxy::UnHoldCall return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::UnHoldCall return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_UN_HOLD, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SwitchCall(int32_t slotId, int32_t callType)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SwitchCall return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::SwitchCall return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(callType)) {
        TELEPHONY_LOGE("ImsCallProxy::SwitchCall return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SwitchCall return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SWITCH, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::CombineConference(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::CombineConference return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::CombineConference return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::CombineConference return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_COMBINE_CONFERENCE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::InviteToConference(int32_t slotId, const std::vector<std::string> &numberList)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::InviteToConference return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::InviteToConference return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteStringVector(numberList)) {
        TELEPHONY_LOGE("ImsCallProxy::InviteToConference return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::InviteToConference return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_INVITE_TO_CONFERENCE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::KickOutFromConference(int32_t slotId, const std::vector<std::string> &numberList)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::KickOutFromConference return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::KickOutFromConference return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteStringVector(numberList)) {
        TELEPHONY_LOGE("ImsCallProxy::KickOutFromConference return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::KickOutFromConference return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_KICK_OUT_CONFERENCE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::UpdateImsCallMode(const ImsCallInfo &callInfo, ImsCallMode mode)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::UpdateImsCallMode return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteRawData((const void *)&callInfo, sizeof(ImsCallInfo))) {
        TELEPHONY_LOGE("ImsCallProxy::UpdateImsCallMode return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(mode)) {
        TELEPHONY_LOGE("ImsCallProxy::UpdateImsCallMode return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::UpdateImsCallMode return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_UPDATE_CALL_MEDIA_MODE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag)
{
    TELEPHONY_LOGI("ImsCallProxy::GetImsCallsDataRequest entry");
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetImsCallsDataRequest return false, write descriptor token fail!");
        return false;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::GetImsCallsDataRequest return false, write slotId fail!");
        return false;
    }
    if (!in.WriteInt64(lastCallsDataFlag)) {
        TELEPHONY_LOGE("ImsCallProxy::GetImsCallsDataRequest return false, write lastCallsDataFlag fail!");
        return false;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetImsCallsDataRequest return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t ret = remote->SendRequest(IMS_GET_CALL_DATA, in, out, option);
    if (ret == ERR_NONE) {
        return out.ReadInt32();
    }
    return false;
}

int32_t ImsCallProxy::GetLastCallFailReason(int32_t slotId)
{
    TELEPHONY_LOGI("ImsCallProxy::GetLastCallFailReason entry");
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetLastCallFailReason return false, write descriptor token fail!");
        return false;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::GetLastCallFailReason return false, write slotId fail!");
        return false;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetLastCallFailReason return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t ret = remote->SendRequest(IMS_GET_LAST_CALL_FAIL_REASON, in, out, option);
    if (ret == ERR_NONE) {
        return out.ReadInt32();
    }
    return false;
}

int32_t ImsCallProxy::StartDtmf(int32_t slotId, char cDtmfCode, int32_t index)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::StartDtmf return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::StartDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteCString(&cDtmfCode)) {
        TELEPHONY_LOGE("ImsCallProxy::StartDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(index)) {
        TELEPHONY_LOGE("ImsCallProxy::StartDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::StartDtmf return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_START_DTMF, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SendDtmf(int32_t slotId, char cDtmfCode, int32_t index)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SendDtmf return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::SendDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteCString(&cDtmfCode)) {
        TELEPHONY_LOGE("ImsCallProxy::SendDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(index)) {
        TELEPHONY_LOGE("ImsCallProxy::SendDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SendDtmf return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SEND_DTMF, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::StopDtmf(int32_t slotId, int32_t index)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::StopDtmf return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::StopDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(index)) {
        TELEPHONY_LOGE("ImsCallProxy::StopDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::StopDtmf return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_STOP_DTMF, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::StartRtt(int32_t slotId, const std::string &msg)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::StartRtt return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::StartRtt return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString(msg)) {
        TELEPHONY_LOGE("ImsCallProxy::StartRtt return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::StartRtt return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_START_RTT, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::StopRtt(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::StopRtt return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::StopRtt return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::StopRtt return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_STOP_RTT, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetDomainPreferenceMode(int32_t slotId, int32_t mode)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetDomainPreferenceMode return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::SetDomainPreferenceMode return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(mode)) {
        TELEPHONY_LOGE("ImsCallProxy::SetDomainPreferenceMode return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetDomainPreferenceMode return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_DOMAIN_PREFERENCE_MODE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::GetDomainPreferenceMode(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetDomainPreferenceMode return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::GetDomainPreferenceMode return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetDomainPreferenceMode return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_GET_DOMAIN_PREFERENCE_MODE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetImsSwitchStatus(int32_t slotId, int32_t active)
{
    TELEPHONY_LOGI("ImsCallProxy::SetImsSwitchStatus entry");
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsSwitchStatus return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsSwitchStatus return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(active)) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsSwitchStatus return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsSwitchStatus return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_SWITCH_STATUS, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::GetImsSwitchStatus(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetImsSwitchStatus return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::GetImsSwitchStatus return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetImsSwitchStatus return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_GET_SWITCH_STATUS, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetImsConfig(ImsConfigItem item, const std::string &value)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsConfig string return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(item)) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsConfig string return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString(value)) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsConfig string return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsConfig return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_IMS_CONFIG_STRING, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetImsConfig(ImsConfigItem item, int32_t value)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsConfig int return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(item)) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsConfig int return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(value)) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsConfig int return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsConfig return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_IMS_CONFIG_INT, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::GetImsConfig(ImsConfigItem item)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetImsConfig return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(item)) {
        TELEPHONY_LOGE("ImsCallProxy::GetImsConfig return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetImsConfig return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_GET_IMS_CONFIG, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetImsFeatureValue(FeatureType type, int32_t value)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsFeatureValue return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(type)) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsFeatureValue return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(value)) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsFeatureValue return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetImsFeatureValue return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_IMS_FEATURE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::GetImsFeatureValue(FeatureType type, int32_t &value)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetImsFeatureValue return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(type)) {
        TELEPHONY_LOGE("ImsCallProxy::GetImsFeatureValue return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetImsFeatureValue return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_GET_IMS_FEATURE, in, out, option);
    if (error == ERR_NONE) {
        int32_t result = out.ReadInt32();
        value = out.ReadInt32();
        return result;
    }
    return TELEPHONY_ERROR;
}

int32_t ImsCallProxy::SetMute(int32_t slotId, int32_t mute)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetMute return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::SetMute return, write slotId fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(mute)) {
        TELEPHONY_LOGE("ImsCallProxy::SetMute return, write mute fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetMute return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_MUTE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::GetMute(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetMute return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::GetMute return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetMute return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_GET_MUTE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::CtrlCamera(const std::u16string &cameraId, int32_t callingUid, int32_t callingPid)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::CtrlCamera return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteString16(cameraId)) {
        TELEPHONY_LOGE("ImsCallProxy::CtrlCamera return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(callingUid)) {
        TELEPHONY_LOGE("ImsCallProxy::CtrlCamera return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(callingPid)) {
        TELEPHONY_LOGE("ImsCallProxy::CtrlCamera return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::CtrlCamera return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_CTRL_CAMERA, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetPreviewWindow return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(x)) {
        TELEPHONY_LOGE("ImsCallProxy::SetPreviewWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(y)) {
        TELEPHONY_LOGE("ImsCallProxy::SetPreviewWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(z)) {
        TELEPHONY_LOGE("ImsCallProxy::SetPreviewWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(width)) {
        TELEPHONY_LOGE("ImsCallProxy::SetPreviewWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(height)) {
        TELEPHONY_LOGE("ImsCallProxy::SetPreviewWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetPreviewWindow return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_PREVIEW_WINDOW, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetDisplayWindow return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(x)) {
        TELEPHONY_LOGE("ImsCallProxy::SetDisplayWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(y)) {
        TELEPHONY_LOGE("ImsCallProxy::SetDisplayWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(z)) {
        TELEPHONY_LOGE("ImsCallProxy::SetDisplayWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(width)) {
        TELEPHONY_LOGE("ImsCallProxy::SetDisplayWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(height)) {
        TELEPHONY_LOGE("ImsCallProxy::SetDisplayWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetDisplayWindow return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_DISPLAY_WINDOW, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetCameraZoom(float zoomRatio)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetCameraZoom return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteFloat(zoomRatio)) {
        TELEPHONY_LOGE("ImsCallProxy::SetCameraZoom return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetCameraZoom return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_CAMERA_ZOOM, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetPauseImage(const std::u16string &path)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetPauseImage return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteString16(path)) {
        TELEPHONY_LOGE("ImsCallProxy::SetPauseImage return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetPauseImage return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_PAUSE_IMAGE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetDeviceDirection(int32_t rotation)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetDeviceDirection return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(rotation)) {
        TELEPHONY_LOGE("ImsCallProxy::SetDeviceDirection return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetDeviceDirection return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_DEVICE_DIRECTION, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetClip(int32_t slotId, int32_t action)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetClip return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::SetClip return, write slotId data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(action)) {
        TELEPHONY_LOGE("ImsCallProxy::SetClip return, write action data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetClip return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_CLIP, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::GetClip(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetClip return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::GetClip return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetClip return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_GET_CLIP, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetClir(int32_t slotId, int32_t action)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetClir return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::SetClir return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(action)) {
        TELEPHONY_LOGE("ImsCallProxy::SetClir return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetClir return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_CLIR, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::GetClir(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetClir return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::GetClir return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetClir return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_GET_CLIR, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetCallTransfer(
    int32_t slotId, int32_t reason, int32_t mode, const std::string &transferNum, int32_t classType)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallTransfer return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallTransfer return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(reason)) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallTransfer return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(mode)) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallTransfer return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString(transferNum)) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallTransfer string return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(classType)) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallTransfer return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallTransfer return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_CALL_TRANSFER, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::GetCallTransfer(int32_t slotId, int32_t reason)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetCallTransfer return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::GetCallTransfer return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(reason)) {
        TELEPHONY_LOGE("ImsCallProxy::GetCallTransfer return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetCallTransfer return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_GET_CALL_TRANSFER, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetCallRestriction(int32_t slotId, const std::string &fac, int32_t mode, const std::string &pw)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallRestriction return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallRestriction return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString(fac)) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallRestriction string return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(mode)) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallRestriction return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString(pw)) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallRestriction string return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallRestriction return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_CALL_RESTRICTION, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::GetCallRestriction(int32_t slotId, const std::string &fac)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetCallRestriction return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::GetCallRestriction return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString(fac)) {
        TELEPHONY_LOGE("ImsCallProxy::GetCallRestriction string return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetCallRestriction return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_GET_CALL_RESTRICTION, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetCallWaiting(int32_t slotId, bool activate, int32_t classType)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallWaiting return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallWaiting return, write slotId fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteBool(activate)) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallWaiting return, write activate fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(classType)) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallWaiting return, write classType fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetCallWaiting return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_CALL_WAITING, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::GetCallWaiting(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetCallWaiting return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::GetCallWaiting return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetCallWaiting return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_GET_CALL_WAITING, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetColr(int32_t slotId, int32_t presentation)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetColr return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::SetColr return, write slotId data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(presentation)) {
        TELEPHONY_LOGE("ImsCallProxy::SetColr return, write presentation data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetColr return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_COLR, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::GetColr(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetColr return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::GetColr return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetColr return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_GET_COLR, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::SetColp(int32_t slotId, int32_t action)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::SetColp return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::SetColp return, write slotId data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(action)) {
        TELEPHONY_LOGE("ImsCallProxy::SetColp return, write action data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::SetColp return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_SET_COLP, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::GetColp(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::GetColp return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsCallProxy::GetColp return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::GetColp return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_GET_COLP, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::RegisterImsCallCallback(const sptr<ImsCallCallbackInterface> &callback)
{
    if (callback == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::RegisterImsCallCallback return, callback is nullptr");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsCallProxy::RegisterImsCallCallback return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteRemoteObject(callback->AsObject().GetRefPtr())) {
        TELEPHONY_LOGE("ImsCallProxy::RegisterImsCallCallback return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::RegisterImsCallCallback return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_CALL_REGISTER_CALLBACK, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsCallProxy::UpdateImsCapabilities(int32_t slotId, const ImsCapabilityList &imsCapabilityList)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsCallProxy::GetDescriptor())) {
        TELEPHONY_LOGE("write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("write slotId data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteRawData((const void *)&imsCapabilityList, sizeof(ImsCapabilityList))) {
        TELEPHONY_LOGE("write action data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        TELEPHONY_LOGE("ImsCallProxy::UpdateImsCapabilities return, remote is nullptr!");
        return TELEPHONY_ERR_LOCAL_PTR_NULL;
    }
    int32_t error = remote->SendRequest(IMS_UPDATE_CAPABILITY, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}
} // namespace Telephony
} // namespace OHOS