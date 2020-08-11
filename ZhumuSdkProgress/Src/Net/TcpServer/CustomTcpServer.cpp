#include "stdafx.h"
#include "Resource.h"
#include "CustomTcpServer.h"
#include "HPTypeDef.h"
#include "plog\Log.h"
#include "reader.h"
#include "Utils.h"
#include "BusinessLogic.h"



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
            CBusinessLogic::GetInstance()->InitZhumuSDK(CUtils::json2Str(body));
        }
        else if ("LoginSDK" == strMethod)
        {
            auto body = root["body"];
            CBusinessLogic::GetInstance()->LoginZhumuSDK(CUtils::json2Str(body));
        }
        else if ("DestorySDK" == strMethod)
        {
            CBusinessLogic::GetInstance()->DestroyZhumuSDK();
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
