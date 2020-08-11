#include "stdafx.h"
#include "CustomTcpClient.h"
#include <string>
#include "Utils.h"
#include "plog\Log.h"



CCustomTcpClient::CCustomTcpClient()
    :m_pClient(this)
{
    m_bCanReturn = false;
}


CCustomTcpClient::~CCustomTcpClient()
{
}


bool CCustomTcpClient::InterfaceCommunicate(const std::string strIp, const int nPort, const std::string strSend, std::string& strReceive)
{
    bool bRet = false;
    if (strIp.empty() || nPort <= 0|| strSend.empty())
    {
        LOGE << "parameter error! ";
        return false;
    }
    LOGI << "Send content :[ " << strSend << " ]";
    if (true == StartTcpClient(strIp,nPort))
    {
        if (true == SendContentTcpClient(strSend))
        {
            // 等待接收服务器反馈
            while (!m_bCanReturn)
            {
                Sleep(1);
            }
            // 关闭服务
            StopTcpClient();
            bRet = true;
        }
        else
        {
            LOGE << "Failed to send data! serverIp: " << strIp << " server port: " << nPort;
        }
    }
    else
    {
        LOGE << "Connect to the server failed! serverIp: " << strIp << " server port: " << nPort;
    }
    return bRet;
}

bool CCustomTcpClient::SendContentTcpClient(std::string strContent)
{
    bool bRet = false;
    LPCSTR name = "suirui_head";
    LPCSTR desc = strContent.c_str();
    int desc_len = (int)strlen(desc) + 1;
    int body_len = offsetof(TPkgBody, desc) + desc_len;

    TPkgBody* pBody = (TPkgBody*)_alloca(body_len);
    memset(pBody, 0, body_len);

    pBody->age = 23;
    strcpy(pBody->name, name);
    strcpy(pBody->desc, desc);

    if (m_pClient->Send((BYTE*)pBody, body_len))
    {
        bRet = true;
    }
    return bRet;
}

bool CCustomTcpClient::StartTcpClient(const std::string strIp, const int nPort)
{
    bool bRet = false;
    m_pClient->SetMaxPackSize(0x01FFF);
    m_pClient->SetPackHeaderFlag(0x169);

    if (m_pClient->Start(L"127.0.0.1", nPort, false))
    {
        bRet = true;
    }
    return bRet;
}

void CCustomTcpClient::StopTcpClient()
{
    if (m_pClient->Stop())
    {

    }
    else
    {

    }
}

EnHandleResult CCustomTcpClient::OnConnect(ITcpClient* pSender, CONNID dwConnID)
{
    TCHAR szAddress[50];
    int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
    USHORT usPort;

    pSender->GetLocalAddress(szAddress, iAddressLen, usPort);

    //::PostOnConnect(dwConnID, szAddress, usPort);
    //SetAppState(ST_STARTED);

    return HR_OK;
}

EnHandleResult CCustomTcpClient::OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
    if (false == m_bCanReturn)
    {
        m_bCanReturn = true;
    }
    return HR_OK;
}

EnHandleResult CCustomTcpClient::OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
    //::PostOnReceive(dwConnID, pData, iLength);
    return HR_OK;
}

EnHandleResult CCustomTcpClient::OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
    //iErrorCode == SE_OK ? ::PostOnClose(dwConnID) :
    //    ::PostOnError(dwConnID, enOperation, iErrorCode);

    //SetAppState(ST_STOPPED);
    m_bCanReturn = true;
    return HR_OK;
}
