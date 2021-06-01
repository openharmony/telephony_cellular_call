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

#include "cellular_call_stub.h"

#include "cellular_call_register.h"
#include "i_call_status_callback.h"

#include "cs_control.h"

namespace OHOS {
namespace CellularCall {
int CellularCallStub::OnRemoteRequest(
    uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    std::u16string myDescripter = CellularCallStub::GetDescriptor();
    std::u16string remoteDescripter = data.ReadInterfaceToken();
    if (myDescripter != remoteDescripter) {
        HILOG_ERROR("descriptor checked fail");
        return ERR_PARAMETER_INVALID;
    }

    auto itFunc = requestFuncMap_.find(code);
    if (itFunc != requestFuncMap_.end()) {
        auto requestFunc = itFunc->second;
        if (requestFunc != nullptr) {
            return (this->*requestFunc)(data, reply);
        }
    }
    HILOG_WARN("CellularCallStub::OnRemoteRequest, default case, need check.");
    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

CellularCallStub::CellularCallStub()
{
    HILOG_DEBUG("CellularCallStub::CellularCallStub");
    requestFuncMap_[DIAL] = &CellularCallStub::DialInner;
    requestFuncMap_[END] = &CellularCallStub::EndInner;
    requestFuncMap_[REJECT] = &CellularCallStub::RejectInner;
    requestFuncMap_[ANSWER] = &CellularCallStub::AnswerInner;
    requestFuncMap_[EMERGENCY_CALL] = &CellularCallStub::IsUrgentCallInner;
    requestFuncMap_[REGISTER_CALLBACK] = &CellularCallStub::RegisterCallBackInner;
    requestFuncMap_[UNREGISTER_CALLBACK] = &CellularCallStub::UnRegisterCallBackInner;
}

CellularCallStub::~CellularCallStub()
{
    HILOG_DEBUG("CellularCallStub::~CellularCallStub");
    requestFuncMap_.clear();
}

int CellularCallStub::DialInner(MessageParcel &data, MessageParcel &reply)
{
    HILOG_DEBUG("CellularCallStub::DialInner DIAL");
    CellularCallInfo *pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        HILOG_ERROR("DialInner return, pCallInfo is nullptr.");
        return ERR_PARAMETER_INVALID;
    }
    reply.WriteInt32(Dial(*pCallInfo));
    return 0;
}

int CellularCallStub::EndInner(MessageParcel &data, MessageParcel &reply)
{
    HILOG_DEBUG("CellularCallStub::EndInner END");
    CellularCallInfo *pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        HILOG_ERROR("EndInner return, pCallInfo is nullptr.");
        return ERR_PARAMETER_INVALID;
    }
    reply.WriteInt32(End(*pCallInfo));
    return 0;
}

int CellularCallStub::RejectInner(MessageParcel &data, MessageParcel &reply)
{
    HILOG_DEBUG("CellularCallStub::RejectInner REJECT");
    CellularCallInfo *pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        HILOG_ERROR("RejectInner return, pCallInfo is nullptr.");
        return ERR_PARAMETER_INVALID;
    }
    reply.WriteInt32(Reject(*pCallInfo));
    return 0;
}

int CellularCallStub::AnswerInner(MessageParcel &data, MessageParcel &reply)
{
    HILOG_DEBUG("CellularCallStub::AnswerInner ANSWER");
    CellularCallInfo *pCallInfo = (CellularCallInfo *)data.ReadRawData(sizeof(CellularCallInfo));
    if (pCallInfo == nullptr) {
        HILOG_ERROR("AnswerInner return, pCallInfo is nullptr.");
        return ERR_PARAMETER_INVALID;
    }
    reply.WriteInt32(Answer(*pCallInfo));
    return 0;
}

int CellularCallStub::IsUrgentCallInner(MessageParcel &data, MessageParcel &reply)
{
    HILOG_DEBUG("CellularCallStub::IsUrgentCallInner EMERGENCY_CALL entry.");
    std::string phoneNum = data.ReadString();
    int32_t slotId = data.ReadInt32();
    reply.WriteInt32(IsUrgentCall(phoneNum, slotId));
    return 0;
}

int CellularCallStub::RegisterCallBackInner(MessageParcel &data, MessageParcel &reply)
{
    HILOG_DEBUG("CellularCallStub::RegisterCallBackInner REGISTER_CALLBACK entry.");
    int32_t result = ERR_PARAMETER_INVALID;
    sptr<IRemoteObject> remote = data.ReadRemoteObject();
    if (remote == nullptr) {
        HILOG_ERROR("CellularCallStub::RegisterCallBackInner REGISTER_CALLBACK, remote is nullptr.");
        reply.WriteInt32(result);
        return result;
    }
    sptr<OHOS::TelephonyCallManager::ICallStatusCallback> callback =
        iface_cast<OHOS::TelephonyCallManager::ICallStatusCallback>(remote);
    result = DelayedSingleton<CellularCallRegister>::GetInstance()->RegisterCallManagerCallBack(callback);
    reply.WriteInt32(result);
    return result;
}

int CellularCallStub::Dial(const CellularCallInfo &callInfo)
{
    int32_t result = ERR_PARAMETER_INVALID;
    if (TYPE_CS == callInfo.callType) {
        result = DelayedSingleton<CSControl>::GetInstance()->Dial(callInfo);
    } else if (TYPE_IMS == callInfo.callType) {
    }
    return result;
}

int CellularCallStub::End(const CellularCallInfo &callInfo)
{
    int32_t result = ERR_PARAMETER_INVALID;
    if (TYPE_CS == callInfo.callType) {
        result = DelayedSingleton<CSControl>::GetInstance()->End(callInfo);
    } else if (TYPE_IMS == callInfo.callType) {
    }
    return result;
}

int CellularCallStub::Reject(const CellularCallInfo &callInfo)
{
    int32_t result = ERR_PARAMETER_INVALID;
    if (TYPE_CS == callInfo.callType) {
        result = DelayedSingleton<CSControl>::GetInstance()->Reject(callInfo);
    } else if (TYPE_IMS == callInfo.callType) {
    }
    return result;
}

int CellularCallStub::Answer(const CellularCallInfo &callInfo)
{
    int32_t result = ERR_PARAMETER_INVALID;
    if (TYPE_CS == callInfo.callType) {
        result = DelayedSingleton<CSControl>::GetInstance()->Answer(callInfo);
    } else if (TYPE_IMS == callInfo.callType) {
    }
    return result;
}

int CellularCallStub::RegisterCallManagerCallBack(const sptr<TelephonyCallManager::ICallStatusCallback> &callback)
{
    return 0;
}

int CellularCallStub::IsUrgentCall(const std::string &phoneNum, int32_t slotId)
{
    return 0;
}

int CellularCallStub::UnRegisterCallBackInner(MessageParcel &data, MessageParcel &reply)
{
    int result = DelayedSingleton<CellularCallRegister>::GetInstance()->UnRegisterCallManagerCallBack();
    reply.WriteInt32(result);
    return result;
}

int CellularCallStub::UnRegisterCallManagerCallBack()
{
    return 0;
}
} // namespace CellularCall
} // namespace OHOS
