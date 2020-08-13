#include "stdafx.h"
#include "Resource.h"
#include "CustomTcpServer.h"
#include "HPTypeDef.h"
#include "plog\Log.h"
#include "reader.h"
#include "Utils.h"
#include "BusinessLogic.h"
#include <stddef.h>



CCustomTcpServer::CCustomTcpServer()
    :m_pTcpServer(this)
{
    m_pEvent = nullptr;
}


CCustomTcpServer::~CCustomTcpServer()
{
}

void CCustomTcpServer::SetEvent(CCustomTcpServerEvent* _event)
{
    m_pEvent = _event;
}

bool CCustomTcpServer::StartServer(int nServerPort)
{
    bool bRet = false;

    m_pTcpServer->SetPackHeaderFlag(0x169);

    if (m_pTcpServer->Start(L"0.0.0.0", nServerPort) == FALSE)
    {
        int error = m_pTcpServer->GetLastError();
        LOGE << "[" << __FUNCTION__ << "] The TCP service failed to start! error code : " << error << " local listening port: " << nServerPort << std::endl;
    }
    else
    {
        bRet = true;
    }

    return bRet;
}

bool CCustomTcpServer::StopServer()
{
    bool bRet = true;

    if (nullptr != m_pTcpServer)
    {
        m_pTcpServer->Stop();
        m_pTcpServer->Wait(100);
    }
    return bRet;
}


EnHandleResult CCustomTcpServer::OnPrepareListen(ITcpServer* pSender, SOCKET soListen)
{
    TCHAR szAddress[50];
    int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
    USHORT usPort;

    pSender->GetListenAddress(szAddress, iAddressLen, usPort);

    return HR_OK;
}

EnHandleResult CCustomTcpServer::OnAccept(ITcpServer* pSender, CONNID dwConnID, SOCKET soClient)
{
    BOOL bPass = TRUE;
    TCHAR szAddress[50];
    int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
    USHORT usPort;
    pSender->GetRemoteAddress(dwConnID, szAddress, iAddressLen, usPort);

    LOGD << "[" << __FUNCTION__ << "] TCP client information dwConnID: " << dwConnID << " client ip: " << szAddress << " client port: " << usPort << std::endl;
    return HR_OK;
}

EnHandleResult CCustomTcpServer::OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
    return HR_OK;
}

EnHandleResult CCustomTcpServer::OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength)
{
    return HR_OK;
}

EnHandleResult CCustomTcpServer::OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
    std::string strReceiveContent((char*)pData + 32, iLength);

    LOGI << "[" << __FUNCTION__ << "] Content received : [" << strReceiveContent << "] form " << dwConnID<< std::endl;

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strReceiveContent.c_str(), strReceiveContent.c_str() + strReceiveContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        std::string strMethod = root["method"].asString();

        if ("InitSDK" == strMethod)
        {
            auto body = root["body"];
            int nRet = CBusinessLogic::GetInstance()->InitZhumuSDK(CUtils::json2Str(body));
            OnResponse(pSender, dwConnID, strMethod, nRet);
        }
        else if ("LoginSDK" == strMethod)
        {
            auto body = root["body"];
            int nRet = CBusinessLogic::GetInstance()->LoginZhumuSDK(CUtils::json2Str(body));
            OnResponse(pSender, dwConnID, strMethod, nRet);
        }
        else if ("StartAppointmentMeeting" == strMethod)
        {
            auto body = root["body"];
            int nRet = CBusinessLogic::GetInstance()->StartAppointmentMeetingZhumuSDK(CUtils::json2Str(body));
            OnResponse(pSender, dwConnID, strMethod, nRet);
        }
        else if ("StartInstantMeeting" == strMethod)
        {
            auto body = root["body"];
            int nRet = CBusinessLogic::GetInstance()->StartInstantMeetingZhumuSDK(CUtils::json2Str(body));
            OnResponse(pSender, dwConnID, strMethod, nRet);
        }
        else if ("JoinMeeting" == strMethod)
        {
            auto body = root["body"];
            int nRet = CBusinessLogic::GetInstance()->JoinMeetingZhumuSDK(CUtils::json2Str(body));
            OnResponse(pSender, dwConnID, strMethod, nRet);
        }
        else if ("AnonymityJoinMeeting" == strMethod)
        {
            auto body = root["body"];
            int nRet = CBusinessLogic::GetInstance()->AnonymityJoinMeetingZhumuSDK(CUtils::json2Str(body));
            OnResponse(pSender, dwConnID, strMethod, nRet);
        }
        else if ("AutoFullScreen" == strMethod
            || "AlwaysShowCtrlBar" == strMethod
            || "AlwaysJoinMeetingbeforeAdmin" == strMethod
            || "AutoJoinAudio" == strMethod
            || "ParticipantsUnmute" == strMethod
            || "EchoCancellation" == strMethod
            || "HDVideo" == strMethod
            || "AutoTurnOffVideo" == strMethod
            )
        {
            int nRet = CBusinessLogic::GetInstance()->SettingMeetingZhumu(strReceiveContent);
            OnResponse(pSender, dwConnID, strMethod, nRet);
        }
        else if ("DirectSharing" == strMethod)
        {
            auto body = root["body"];
            int nRet = CBusinessLogic::GetInstance()->DirectSharingZhumu(CUtils::json2Str(body));
            OnResponse(pSender, dwConnID, strMethod, nRet);
        }
        else if ("SelectMic" == strMethod)
        {
            auto body = root["body"];
            int nRet = CBusinessLogic::GetInstance()->SelectMicZhumuSDK(CUtils::json2Str(body));
            OnResponse(pSender, dwConnID, strMethod, nRet);
        }
        else if ("SetMicVol" == strMethod)
        {
            auto body = root["body"];
            int nRet = CBusinessLogic::GetInstance()->SetMicVolZhumuSDK(CUtils::json2Str(body));
            OnResponse(pSender, dwConnID, strMethod, nRet);
        }
        else if ("SelectSpeaker" == strMethod)
        {
            auto body = root["body"];
            int nRet = CBusinessLogic::GetInstance()->SelectSpeakerZhumuSDK(CUtils::json2Str(body));
            OnResponse(pSender, dwConnID, strMethod, nRet);
        }
        else if ("SetSpeakerVol" == strMethod)
        {
            auto body = root["body"];
            int nRet = CBusinessLogic::GetInstance()->SetSpeakerVolZhumuSDK(CUtils::json2Str(body));
            OnResponse(pSender, dwConnID, strMethod, nRet);
        }
        else if ("SelectCamera" == strMethod)
        {
            auto body = root["body"];
            int nRet = CBusinessLogic::GetInstance()->SelectCameraZhumuSDK(CUtils::json2Str(body));
            OnResponse(pSender, dwConnID, strMethod, nRet);
        }
        else if ("DestorySDK" == strMethod)
        {
            CBusinessLogic::GetInstance()->DestroyZhumuSDK();
            OnResponse(pSender, dwConnID, strMethod, 0);
        }
        else
        {
            LOGE << "[" << __FUNCTION__ << "] Unknown method name! strMethod:[" << strMethod << "]" << std::endl;
        }
    }
    else
    {
        LOGE << "[" << __FUNCTION__ << "] json reader error! content:[" << strReceiveContent << "]" << std::endl;
    }

    delete reader;


    return HR_OK;
}

EnHandleResult CCustomTcpServer::OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
    return HR_OK;
}

EnHandleResult CCustomTcpServer::OnShutdown(ITcpServer* pSender)
{
    /* ::PostOnShutdown();*/

    return HR_OK;
}

void CCustomTcpServer::OnResponse(ITcpServer* pSender, CONNID dwConnID, std::string strMethod, int nErrCode)
{
    // 拼接字符串
    Json::Value root;
    // 接口名
    root["method"] = strMethod;
    root["errorCode"] = nErrCode;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    bool bRet = false;
    LPCSTR name = "suirui_head";
    LPCSTR desc = strSendConteng.c_str();
    int desc_len = (int)strlen(desc) + 1;
    int body_len = offsetof(TPkgBody, desc) + desc_len;

    TPkgBody* pBody = (TPkgBody*)_alloca(body_len);
    memset(pBody, 0, body_len);

    pBody->age = 23;
    strcpy(pBody->name, name);
    strcpy(pBody->desc, desc);

    if (nullptr != pSender)
    {
        pSender->Send(dwConnID, (BYTE*)pBody, body_len);
    }
}
