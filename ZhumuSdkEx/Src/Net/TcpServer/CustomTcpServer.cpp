#include "stdafx.h"
#include "CustomTcpServer.h"
#include "HPTypeDef.h"
#include "plog\Log.h"


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

    if (m_pTcpServer->Start(L"0.0.0.0", nServerPort) == FALSE)
    {
        int error = m_pTcpServer->GetLastError();
        LOGE << "The TCP service failed to start! error code : " << error << " local listening port: " << nServerPort;
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

    LOGI << "TCP client information dwConnID: " << dwConnID << " client ip: " << szAddress << " client port: " << usPort;
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

    LOGI << "Content received: [" << strReceiveContent << "] form " << dwConnID;
    if (nullptr != m_pEvent)
    {
        m_pEvent->OnReceive(strReceiveContent, strReceiveContent.length());
    }

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