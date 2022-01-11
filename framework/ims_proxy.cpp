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

#include "ims_proxy.h"

#include "call_manager_errors.h"

namespace OHOS {
namespace Telephony {
int32_t ImsProxy::Dial(const ImsCallInfo &callInfo, CLIRMode mode)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::Dial return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteRawData((const void *)&callInfo, sizeof(ImsCallInfo))) {
        TELEPHONY_LOGE("ImsProxy::Dial return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(mode)) {
        TELEPHONY_LOGE("ImsProxy::Dial return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_DIAL, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::HangUp(const ImsCallInfo &callInfo)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::HangUp return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteRawData((const void *)&callInfo, sizeof(ImsCallInfo))) {
        TELEPHONY_LOGE("ImsProxy::HangUp return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_HANG_UP, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::Reject(const ImsCallInfo &callInfo)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::Reject return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteRawData((const void *)&callInfo, sizeof(ImsCallInfo))) {
        TELEPHONY_LOGE("ImsProxy::Reject return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_REJECT, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::Answer(const ImsCallInfo &callInfo)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::Answer return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteRawData((const void *)&callInfo, sizeof(ImsCallInfo))) {
        TELEPHONY_LOGE("ImsProxy::Answer return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_ANSWER, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::HoldCall(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::HoldCall return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::HoldCall return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_HOLD, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::UnHoldCall(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::UnHoldCall return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::UnHoldCall return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_UN_HOLD, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SwitchCall(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SwitchCall return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::SwitchCall return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SWITCH, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::CombineConference(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::CombineConference return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::CombineConference return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_COMBINE_CONFERENCE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::InviteToConference(int32_t slotId, const std::vector<std::string> &numberList)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::InviteToConference return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::InviteToConference return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteStringVector(numberList)) {
        TELEPHONY_LOGE("ImsProxy::InviteToConference return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_INVITE_TO_CONFERENCE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::KickOutFromConference(int32_t slotId, const std::vector<std::string> &numberList)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::KickOutFromConference return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::KickOutFromConference return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteStringVector(numberList)) {
        TELEPHONY_LOGE("ImsProxy::KickOutFromConference return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_KICK_OUT_CONFERENCE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::UpdateCallMediaMode(const ImsCallInfo &callInfo, CallMediaMode mode)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::UpdateCallMediaMode return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteRawData((const void *)&callInfo, sizeof(ImsCallInfo))) {
        TELEPHONY_LOGE("ImsProxy::UpdateCallMediaMode return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(mode)) {
        TELEPHONY_LOGE("ImsProxy::UpdateCallMediaMode return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_UPDATE_CALL_MEDIA_MODE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::IsEmergencyPhoneNumber(int32_t slotId, const std::string &phoneNum)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::IsEmergencyPhoneNumber return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::IsEmergencyPhoneNumber return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString(phoneNum)) {
        TELEPHONY_LOGE("ImsProxy::IsEmergencyPhoneNumber return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_EMERGENCY_CALL, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::GetImsCallsDataRequest(int32_t slotId, int64_t lastCallsDataFlag)
{
    TELEPHONY_LOGI("ImsProxy::GetImsCallsDataRequest entry");
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::GetImsCallsDataRequest return false, write descriptor token fail!");
        return false;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::GetImsCallsDataRequest return false, write slotId fail!");
        return false;
    }
    if (!in.WriteInt64(lastCallsDataFlag)) {
        TELEPHONY_LOGE("ImsProxy::GetImsCallsDataRequest return false, write lastCallsDataFlag fail!");
        return false;
    }
    int32_t ret = Remote()->SendRequest(IMS_GET_CALL_DATA, in, out, option);
    if (ret == ERR_NONE) {
        return out.ReadInt32();
    }
    return false;
}

int32_t ImsProxy::GetCallFailReason(int32_t slotId)
{
    TELEPHONY_LOGI("ImsProxy::GetCallFailReason entry");
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::GetCallFailReason return false, write descriptor token fail!");
        return false;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::GetCallFailReason return false, write slotId fail!");
        return false;
    }
    int32_t ret = Remote()->SendRequest(GET_CALL_FAIL_REASON, in, out, option);
    if (ret == ERR_NONE) {
        return out.ReadInt32();
    }
    return false;
}

int32_t ImsProxy::StartDtmf(int32_t slotId, char cDtmfCode, int32_t index)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::StartDtmf return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::StartDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteCString(&cDtmfCode)) {
        TELEPHONY_LOGE("ImsProxy::StartDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(index)) {
        TELEPHONY_LOGE("ImsProxy::StartDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_START_DTMF, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SendDtmf(int32_t slotId, char cDtmfCode, int32_t index)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SendDtmf return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::SendDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteCString(&cDtmfCode)) {
        TELEPHONY_LOGE("ImsProxy::SendDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(index)) {
        TELEPHONY_LOGE("ImsProxy::SendDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SEND_DTMF, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::StopDtmf(int32_t slotId, int32_t index)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::StopDtmf return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::StopDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(index)) {
        TELEPHONY_LOGE("ImsProxy::StopDtmf return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_STOP_DTMF, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::StartRtt(int32_t slotId, const std::string &msg)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::StartRtt return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::StartRtt return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString(msg)) {
        TELEPHONY_LOGE("ImsProxy::StartRtt return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_START_RTT, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::StopRtt(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::StopRtt return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::StopRtt return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_STOP_RTT, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetDomainPreferenceMode(int32_t mode)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetDomainPreferenceMode return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(mode)) {
        TELEPHONY_LOGE("ImsProxy::SetDomainPreferenceMode return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_DOMAIN_PREFERENCE_MODE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::GetDomainPreferenceMode()
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::GetDomainPreferenceMode return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_GET_DOMAIN_PREFERENCE_MODE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetLteImsSwitchStatus(bool active)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetLteImsSwitchStatus return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteBool(active)) {
        TELEPHONY_LOGE("ImsProxy::SetLteImsSwitchStatus return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_LTE_IMS_SWITCH_STATUS, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::GetLteImsSwitchStatus()
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::GetLteImsSwitchStatus return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_GET_LTE_IMS_SWITCH_STATUS, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetImsConfig(ImsConfigItem item, const std::string &value)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetImsConfig string return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(item)) {
        TELEPHONY_LOGE("ImsProxy::SetImsConfig string return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString(value)) {
        TELEPHONY_LOGE("ImsProxy::SetImsConfig string return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_IMS_CONFIG_STRING, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetImsConfig(ImsConfigItem item, int32_t value)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetImsConfig int return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(item)) {
        TELEPHONY_LOGE("ImsProxy::SetImsConfig int return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(value)) {
        TELEPHONY_LOGE("ImsProxy::SetImsConfig int return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_IMS_CONFIG_INT, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::GetImsConfig(ImsConfigItem item)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::GetImsConfig return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(item)) {
        TELEPHONY_LOGE("ImsProxy::GetImsConfig return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_GET_IMS_CONFIG, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetImsFeatureValue(FeatureType type, int32_t value)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetImsFeatureValue return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(type)) {
        TELEPHONY_LOGE("ImsProxy::SetImsFeatureValue return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(value)) {
        TELEPHONY_LOGE("ImsProxy::SetImsFeatureValue return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_IMS_FEATURE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::GetImsFeatureValue(FeatureType type)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::GetImsFeatureValue return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(type)) {
        TELEPHONY_LOGE("ImsProxy::GetImsFeatureValue return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_GET_IMS_FEATURE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetVolteEnhanceMode(bool value)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetVolteEnhanceMode return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteBool(value)) {
        TELEPHONY_LOGE("ImsProxy::SetVolteEnhanceMode return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_VOLTE_ENHANCE_MODE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::GetVolteEnhanceMode()
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::GetVolteEnhanceMode return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_GET_VOLTE_ENHANCE_MODE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::CtrlCamera(
    const std::u16string &cameraId, const std::u16string &callingPackage, int32_t callingUid, int32_t callingPid)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::CtrlCamera return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteString16(cameraId)) {
        TELEPHONY_LOGE("ImsProxy::CtrlCamera return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString16(callingPackage)) {
        TELEPHONY_LOGE("ImsProxy::CtrlCamera return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(callingUid)) {
        TELEPHONY_LOGE("ImsProxy::CtrlCamera return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(callingPid)) {
        TELEPHONY_LOGE("ImsProxy::CtrlCamera return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_CTRL_CAMERA, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetPreviewWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetPreviewWindow return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(x)) {
        TELEPHONY_LOGE("ImsProxy::SetPreviewWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(y)) {
        TELEPHONY_LOGE("ImsProxy::SetPreviewWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(z)) {
        TELEPHONY_LOGE("ImsProxy::SetPreviewWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(width)) {
        TELEPHONY_LOGE("ImsProxy::SetPreviewWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(height)) {
        TELEPHONY_LOGE("ImsProxy::SetPreviewWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_PREVIEW_WINDOW, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetDisplayWindow(int32_t x, int32_t y, int32_t z, int32_t width, int32_t height)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetDisplayWindow return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(x)) {
        TELEPHONY_LOGE("ImsProxy::SetDisplayWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(y)) {
        TELEPHONY_LOGE("ImsProxy::SetDisplayWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(z)) {
        TELEPHONY_LOGE("ImsProxy::SetDisplayWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(width)) {
        TELEPHONY_LOGE("ImsProxy::SetDisplayWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(height)) {
        TELEPHONY_LOGE("ImsProxy::SetDisplayWindow return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_DISPLAY_WINDOW, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetCameraZoom(float zoomRatio)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetCameraZoom return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteFloat(zoomRatio)) {
        TELEPHONY_LOGE("ImsProxy::SetCameraZoom return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_CAMERA_ZOOM, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetPauseImage(const std::u16string &path)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetPauseImage return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteString16(path)) {
        TELEPHONY_LOGE("ImsProxy::SetPauseImage return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_PAUSE_IMAGE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetDeviceDirection(int32_t rotation)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetDeviceDirection return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(rotation)) {
        TELEPHONY_LOGE("ImsProxy::SetDeviceDirection return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_DEVICE_DIRECTION, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetMute(int32_t slotId, int32_t mute)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetMute return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::SetMute return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(mute)) {
        TELEPHONY_LOGE("ImsProxy::SetMute return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_MUTE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::GetMute(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::GetMute return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::GetMute return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_GET_MUTE, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::GetEmergencyCallList(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::GetEmergencyCallList return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::GetEmergencyCallList return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_GET_EMERGENCY_CALL_LIST, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::InquireClip(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::InquireClip return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::InquireClip return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_INQUIRE_CLIP, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetClir(int32_t slotId, int32_t action)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetClir return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::SetClir return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(action)) {
        TELEPHONY_LOGE("ImsProxy::SetClir return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_CLIR, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::InquireClir(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::InquireClir return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::InquireClir return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_INQUIRE_CLIR, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetCallTransfer(
    int32_t slotId, int32_t reason, int32_t mode, const std::string &transferNum, int32_t classType)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetCallTransfer return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::SetCallTransfer return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(reason)) {
        TELEPHONY_LOGE("ImsProxy::SetCallTransfer return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(mode)) {
        TELEPHONY_LOGE("ImsProxy::SetCallTransfer return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString(transferNum)) {
        TELEPHONY_LOGE("ImsProxy::SetCallTransfer string return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(classType)) {
        TELEPHONY_LOGE("ImsProxy::SetCallTransfer return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_CALL_TRANSFER, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::GetCallTransfer(int32_t slotId, int32_t reason)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::GetCallTransfer return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::GetCallTransfer return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(reason)) {
        TELEPHONY_LOGE("ImsProxy::GetCallTransfer return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_GET_CALL_TRANSFER, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetCallRestriction(int32_t slotId, const std::string &fac, int32_t mode, const std::string &pw)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetCallRestriction return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::SetCallRestriction return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString(fac)) {
        TELEPHONY_LOGE("ImsProxy::SetCallRestriction string return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteInt32(mode)) {
        TELEPHONY_LOGE("ImsProxy::SetCallRestriction return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString(pw)) {
        TELEPHONY_LOGE("ImsProxy::SetCallRestriction string return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_CALL_RESTRICTION, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::GetCallRestriction(int32_t slotId, const std::string &fac)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::GetCallRestriction return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::GetCallRestriction return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteString(fac)) {
        TELEPHONY_LOGE("ImsProxy::GetCallRestriction string return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_GET_CALL_RESTRICTION, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::SetCallWaiting(int32_t slotId, bool activate)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::SetCallWaiting return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::SetCallWaiting return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    if (!in.WriteBool(activate)) {
        TELEPHONY_LOGE("ImsProxy::SetCallWaiting string return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_SET_CALL_WAITING, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::GetCallWaiting(int32_t slotId)
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::GetCallWaiting return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteInt32(slotId)) {
        TELEPHONY_LOGE("ImsProxy::GetCallWaiting return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }
    int32_t error = Remote()->SendRequest(IMS_GET_CALL_WAITING, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

int32_t ImsProxy::RegisterCellularCallBack(const sptr<ImsCallback> &callback)
{
    if (callback == nullptr) {
        TELEPHONY_LOGE("ImsProxy::RegisterCellularCallBack return, callback is nullptr");
        return TELEPHONY_ERR_ARGUMENT_INVALID;
    }
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::RegisterCellularCallBack return, write descriptor token fail!");
        return TELEPHONY_ERR_WRITE_DESCRIPTOR_TOKEN_FAIL;
    }
    if (!in.WriteRemoteObject(callback->AsObject().GetRefPtr())) {
        TELEPHONY_LOGE("ImsProxy::RegisterCellularCallBack return, write data fail!");
        return TELEPHONY_ERR_WRITE_DATA_FAIL;
    }

    int32_t error = Remote()->SendRequest(IMS_REGISTER_CALLBACK, in, out, option);
    if (error == ERR_NONE) {
        return out.ReadInt32();
    }
    return error;
}

bool ImsProxy::IsCallBackExists()
{
    MessageOption option;
    MessageParcel in;
    MessageParcel out;
    if (!in.WriteInterfaceToken(ImsProxy::GetDescriptor())) {
        TELEPHONY_LOGE("ImsProxy::IsCallBackExists return false, write descriptor token fail!");
        return false;
    }
    int32_t ret = Remote()->SendRequest(IMS_IS_CALLBACK_EXISTS, in, out, option);
    if (ret == ERR_NONE) {
        return out.ReadBool();
    }
    return false;
}
} // namespace Telephony
} // namespace OHOS