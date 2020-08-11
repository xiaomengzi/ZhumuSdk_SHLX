#include "stdafx.h"
#include "BusinessLogic.h"
#include "reader.h"
#include "Utils.h"
#include "Resource.h"
#include "zoom_sdk.h"
#include "zoom_sdk_def.h"
#include "plog\Log.h"
#include "ZhumuSdkAgency.h"
#include "TcpClient\CustomTcpClient.h"

using namespace ZOOM_SDK_NAMESPACE;

CBusinessLogic *CBusinessLogic::m_pInstance = nullptr;


CBusinessLogic::CBusinessLogic()
{
    m_hWndMainDlg = NULL;
    m_bZhumuSdkAlreadyInit = false; // 瞩目SDK是否已经初始化 true-初始化 false-未初始化
    m_bIsLanding = false;           // 瞩目SDK是否正在登陆 true-正在登陆 false-未登录
    m_bAlreadyLanding = false;      // 瞩目SDK是否已经登录 true-已经登录 false-未登录
    m_bIsDirectLogin = false;       // 登录SDK 
    m_bIsAnonymousJoin = false;     // 是否为匿名入会
    m_bAlreadyAuth = false;
}


CBusinessLogic::~CBusinessLogic()
{
}


CBusinessLogic * CBusinessLogic::Initialize()
{
    return CBusinessLogic::GetInstance();
}

void CBusinessLogic::Uninitialize()
{
    if (m_pInstance != nullptr)
    {
        m_pInstance->UnInitData();
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

CBusinessLogic * CBusinessLogic::GetInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new CBusinessLogic;
        m_pInstance->InitData();
    }
    return m_pInstance;
}


void CBusinessLogic::InitData()
{
}

void CBusinessLogic::UnInitData()
{
}

void CBusinessLogic::StartTcpServer()
{
    m_tcpServer.StartServer(g_nLocalListeningPort);
}

void CBusinessLogic::StopTcpServer()
{
    m_tcpServer.StopServer();

}
/************************************************************************/
/*                   上层协议调用处理函数                                */
/************************************************************************/
int CBusinessLogic::InitZhumuSDK(std::string strContent)
{
    int nRet = -1;
    if (true == m_bZhumuSdkAlreadyInit)
    {
        LOGE << "[" << __FUNCTION__ << "] Zhumu SDK Already initialized!" << std::endl;
        return nRet;
    }

    std::string *pStr = new std::string(strContent);
    PostMessage(m_hWndMainDlg, WMUSER_INIT_ZHUMUSDK, (WPARAM)pStr, NULL);
    
    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    return 0;
}

int CBusinessLogic::LoginZhumuSDK(std::string strContent)
{
    int nRet = -1;
    if (false == m_bZhumuSdkAlreadyInit)
    {
        LOGE << "[" << __FUNCTION__ << "] The SDK is not initialized!" << std::endl;
        return nRet;
    }
    if (true == m_bAlreadyLanding || true == m_bIsLanding)
    {
        LOGE << "[" << __FUNCTION__ << "] Logging in or already logged in to the SDK!" << std::endl;
        return nRet;
    }

    std::string *pStr = new std::string(strContent);
    PostMessage(m_hWndMainDlg, WMUSER_LOGIN_ZHUMUSDK, (WPARAM)pStr, NULL);

    LOGI << "[" << __FUNCTION__ << "] content:" << strContent << std::endl;
    return 0;

}

// 注册主窗口句柄
void CBusinessLogic::DestroyZhumuSDK()
{
    // 退出sdk
    PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_QUIT, NULL, NULL);
}

/************************************************************************/
/*                   执行结果协议反馈处理函数                             */
/************************************************************************/
// 反馈初始化SDK结果
bool CBusinessLogic::FeedbackInitResult(ZOOM_SDK_NAMESPACE::SDKError ret)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "InitResult";
    // 协议内容
    Json::Value body;
    body["initResult"] = ret;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure !" << std::endl;
    }
    return bRet;
}

// 反馈认证结果
bool CBusinessLogic::FeedbackAuthResult(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "AuthResult";
    // 协议内容
    Json::Value body;
    body["authResult"] = ret;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure !" << std::endl;
    }
    return bRet;
}

// 反馈登录结果
bool CBusinessLogic::FeedbackLoginResult(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret)
{
    bool bRet = false;

    // 拼接协议
    Json::Value root;
    // 接口名
    root["method"] = "LoginResult";
    // 协议内容
    Json::Value body;
    body["loginResult"] = ret;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //发送数据
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure !" << std::endl;
    }
    return bRet;
}


/************************************************************************/
/*                   瞩目SDK回调处理函数                                 */
/************************************************************************/
void CBusinessLogic::AuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
    LOGI << "[" << __FUNCTION__ << "] Authentication Return :" << ret << std::endl;

    // 将验证结果回调给上层
    FeedbackAuthResult(ret);

    //验证成功则根据任务来源确认执行条件
    if (ret == AUTHRET_SUCCESS)
    {
        m_bAlreadyAuth = true;
        if (m_bIsDirectLogin)
        {
            DirectLogin();
        }
    }
    else 
    {
        // 弹出错误提示
        CString strErrMsg;
        strErrMsg.Format(_T("authentication failure ! error code %d"), ret);
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
        LOGI << "[" << __FUNCTION__ << "] Zhumu SDK authentication failure ! error code:" << ret << std::endl;
    }
}

void CBusinessLogic::LoginReturn(LOGINSTATUS ret, IAccountInfo* pAccountInfo)
{
    LOGI << "[" << __FUNCTION__ << "] Login Return:" << ret << std::endl;

    if (ret == LOGIN_SUCCESS)
    {
        m_bAlreadyLanding = true;
        m_bIsLanding = false;
        // 将验证结果回调给上层
        FeedbackLoginResult(ret);
    }
    else if (ret == LOGIN_FAILED)
    {
        m_bAlreadyLanding = false;
        m_bIsLanding = false;
        FeedbackLoginResult(ret);

        // 弹出错误提示
        CString strErrMsg;
        strErrMsg.Format(_T("Login failure ! error code %d"), ret);
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
    }
}

// 登录
void CBusinessLogic::DirectLogin()
{
    SDKError err = CZhumuSdkAgency::GetInstance()->LoginSDK(CUtils::s2ws(m_loginSDKParam.account), CUtils::s2ws(m_loginSDKParam.password));
    if (err != SDKERR_SUCCESS)
    {
        // 反馈登录错误
        FeedbackLoginResult(LOGIN_FAILED);
        // 弹出错误提示
        CString strErrMsg;
        strErrMsg.Format(_T("login SDK failure ! error code %d"), err);
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
        LOGI << "[" << __FUNCTION__ << "] Zhumu SDK login SDK failure ! error code:" << err << std::endl;
    }
}

// 注册主窗口句柄
void CBusinessLogic::RegisterMainDlgHwnd(HWND hWnd)
{
    m_hWndMainDlg = hWnd;
}

HWND CBusinessLogic::GetMainDlgHwnd()
{
    return m_hWndMainDlg;
}

// 瞩目SDK是否已经初始化 true-初始化 false-未初始化
bool CBusinessLogic::GetZhumuSdkAlreadyInit() const
{
    return m_bZhumuSdkAlreadyInit;
}

void CBusinessLogic::SetZhumuSdkAlreadyInit(bool val)
{
    m_bZhumuSdkAlreadyInit = val;
}

// 瞩目SDK是否正在登陆 true-正在登陆 false-未登录
bool CBusinessLogic::GetIsLanding() const
{
    return m_bIsLanding;
}

void CBusinessLogic::SetIsLanding(bool val)
{
    m_bIsLanding = val;
}

bool CBusinessLogic::GetAlreadyLanding() const
{
    return m_bAlreadyLanding;
}

void CBusinessLogic::SetAlreadyLanding(bool val)
{
    m_bAlreadyLanding = val;
}

bool CBusinessLogic::GetIsDirectLogin() const
{
    return m_bIsDirectLogin;
}

void CBusinessLogic::SetIsDirectLogin(bool val)
{
    m_bIsDirectLogin = val;
}

bool CBusinessLogic::GetIsAnonymousJoin() const
{
    return m_bIsAnonymousJoin;
}

void CBusinessLogic::SetIsAnonymousJoin(bool val)
{
    m_bIsAnonymousJoin = val;
}

bool CBusinessLogic::GetAlreadyAuth() const
{
    return m_bAlreadyAuth;
}

void CBusinessLogic::SetAlreadyAuth(bool val)
{
    m_bAlreadyAuth = val;
}

LoginSDKParam CBusinessLogic::GetLoginSDKParam() const
{
    return m_loginSDKParam;
}

void CBusinessLogic::SetLoginSDKParam(LoginSDKParam val)
{
    m_loginSDKParam = val;
}
