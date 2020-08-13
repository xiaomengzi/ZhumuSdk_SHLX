#include "stdafx.h"
#include "CustomTcpServer.h"
#include "HPTypeDef.h"
#include "plog\Log.h"
#include "reader.h"


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
        LOGE << "[" << __FUNCTION__ << "]  The TCP service failed to start! error code : " << error << " local listening port: " << nServerPort << std::endl;
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

    LOGI << "[" << __FUNCTION__ << "] TCP client information dwConnID: " << dwConnID << " client ip: " << szAddress << " client port: " << usPort << std::endl;
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

    LOGI << "[" << __FUNCTION__ << "] Content received: [" << strReceiveContent << "] form " << dwConnID << std::endl;
    
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strReceiveContent.c_str(), strReceiveContent.c_str() + strReceiveContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        std::string strMethod = root["method"].asString();

        if ("InitResult" == strMethod)
        {
            auto body = root["body"];
            int nInitResult = body["initResult"].asInt();
            if (nullptr != m_pEvent)
            {
                m_pEvent->OnInitResult(nInitResult);
            }
        }
        else if ("AuthResult" == strMethod)
        {
            auto body = root["body"];
            int nAuthResult = body["authResult"].asInt();
            if (nullptr != m_pEvent)
            {
                m_pEvent->OnAuthResult(nAuthResult);
            }
        }
        else if ("LoginResult" == strMethod)
        {
            auto body = root["body"];
            int nLoginResult = body["loginResult"].asInt();
            if (nullptr != m_pEvent)
            {
                m_pEvent->OnLoginResult(nLoginResult);
            }
        }
        else if ("MeetingStatus" == strMethod)
        {
            auto body = root["body"];
            int nMeetingStatus = body["meetingStatus"].asInt();
            int nResult = body["result"].asInt();
            if (nullptr != m_pEvent)
            {
                m_pEvent->OnMeetingStatusResult(nMeetingStatus, nResult);
            }
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