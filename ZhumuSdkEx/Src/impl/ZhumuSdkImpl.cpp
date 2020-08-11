#include "stdafx.h"
#include <shellapi.h>
#include "ZhumuSdkImpl.h"
#include "plog\Log.h"
#include "Utils.h"
#include "TcpClient\CustomTcpClient.h"
#include "Business\CustomData.h"
#include "json.h"


CZhumuSdkImpl::CZhumuSdkImpl()
{
    m_event = nullptr;
    m_pTcpServer = nullptr;

}

CZhumuSdkImpl::~CZhumuSdkImpl()
{

}

void CZhumuSdkImpl::SetEvent(ZhumuSdkEx_Event* _event)
{
    m_event = _event;
}

bool CZhumuSdkImpl::StartTcpServer()
{
    bool bRet = false;
    if (nullptr == m_pTcpServer)
    {
        m_pTcpServer = new CCustomTcpServer();
        m_pTcpServer->SetEvent(this);
        if (false == m_pTcpServer->StartServer(g_nLocalListeningPort))
        {
            LOGE << "The TCP service failed to start! " << __FUNCTION__;
        }
        else
        {
            LOGE << "The TCP service started successfully! " << __FUNCTION__;
            bRet = true;
        }
    }
    return bRet;
}

bool CZhumuSdkImpl::StopTcpServer()
{
    if (nullptr != m_pTcpServer)
    {
        m_pTcpServer->StopServer();
        m_pTcpServer = nullptr;
    }

    return true;
}

bool CZhumuSdkImpl::StartSdkProcess(std::string strPath /*= ""*/)
{
    std::string strExePath = strPath;
    if (strPath.empty())
    {
        // 未指定则在当前EXE同级目录中
        strExePath = "ZhumuSdkProgress.exe";
    }

    LOGI << strExePath << " " << __FUNCTION__;
    ;
    // 启动进程
    ShellExecute(NULL, L"open", CUtils::s2ws(strExePath).c_str(), NULL, NULL, SW_SHOWNORMAL);
    //WinExec(strExePath.c_str(), SW_HIDE);
    return true;
}

bool CZhumuSdkImpl::InitSDK(ZmSdkInitParam initParam)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "InitSDK";
    // 协议内容
    Json::Value body;
    body["bandingName"] = (nullptr == initParam.bindingName) ? "" : initParam.bindingName;
    body["supportUrl"] = (nullptr == initParam.supportUrl) ? "" : initParam.supportUrl;
    body["sdkLangId"] = initParam.language;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "On failure " << __FUNCTION__;
    }
    return bRet;
}

bool CZhumuSdkImpl::LoginSDK(ZmSdkLoginParam loginParam)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "LoginSDK";
    // 协议内容
    Json::Value body;

    body["account"] = (nullptr == loginParam.account) ? "" : loginParam.account;
    body["password"] = (nullptr == loginParam.password) ? "" : loginParam.password;

    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "On failure " << __FUNCTION__;
    }
    return bRet;
}

bool CZhumuSdkImpl::DestorySDK()
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "DestorySDK";

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "On failure " << __FUNCTION__;
    }
    return bRet;
}
