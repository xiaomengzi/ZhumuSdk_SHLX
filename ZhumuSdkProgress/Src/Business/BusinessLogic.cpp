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
    m_bZhumuSdkAlreadyInit = false; // ��ĿSDK�Ƿ��Ѿ���ʼ�� true-��ʼ�� false-δ��ʼ��
    m_bIsLanding = false;           // ��ĿSDK�Ƿ����ڵ�½ true-���ڵ�½ false-δ��¼
    m_bAlreadyLanding = false;      // ��ĿSDK�Ƿ��Ѿ���¼ true-�Ѿ���¼ false-δ��¼
    m_bIsDirectLogin = false;       // ��¼SDK 
    m_bIsAnonymousJoin = false;     // �Ƿ�Ϊ�������
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
/*                   �ϲ�Э����ô�������                                */
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

// ע�������ھ��
void CBusinessLogic::DestroyZhumuSDK()
{
    // �˳�sdk
    PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_QUIT, NULL, NULL);
}

/************************************************************************/
/*                   ִ�н��Э�鷴����������                             */
/************************************************************************/
// ������ʼ��SDK���
bool CBusinessLogic::FeedbackInitResult(ZOOM_SDK_NAMESPACE::SDKError ret)
{
    bool bRet = false;

    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "InitResult";
    // Э������
    Json::Value body;
    body["initResult"] = ret;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure !" << std::endl;
    }
    return bRet;
}

// ������֤���
bool CBusinessLogic::FeedbackAuthResult(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
    bool bRet = false;

    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "AuthResult";
    // Э������
    Json::Value body;
    body["authResult"] = ret;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
    CCustomTcpClient tcpClient;
    std::string strReceive;
    bRet = tcpClient.InterfaceCommunicate(g_strServerIp, g_nServerPort, strSendConteng, strReceive);
    if (false == bRet)
    {
        LOGE << "[" << __FUNCTION__ << "] On failure !" << std::endl;
    }
    return bRet;
}

// ������¼���
bool CBusinessLogic::FeedbackLoginResult(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret)
{
    bool bRet = false;

    // ƴ��Э��
    Json::Value root;
    // �ӿ���
    root["method"] = "LoginResult";
    // Э������
    Json::Value body;
    body["loginResult"] = ret;
    root["body"] = body;

    std::string strSendConteng = CUtils::ASCII2UTF_8(CUtils::json2Str(root));

    //��������
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
/*                   ��ĿSDK�ص���������                                 */
/************************************************************************/
void CBusinessLogic::AuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
    LOGI << "[" << __FUNCTION__ << "] Authentication Return :" << ret << std::endl;

    // ����֤����ص����ϲ�
    FeedbackAuthResult(ret);

    //��֤�ɹ������������Դȷ��ִ������
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
        // ����������ʾ
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
        // ����֤����ص����ϲ�
        FeedbackLoginResult(ret);
    }
    else if (ret == LOGIN_FAILED)
    {
        m_bAlreadyLanding = false;
        m_bIsLanding = false;
        FeedbackLoginResult(ret);

        // ����������ʾ
        CString strErrMsg;
        strErrMsg.Format(_T("Login failure ! error code %d"), ret);
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
    }
}

// ��¼
void CBusinessLogic::DirectLogin()
{
    SDKError err = CZhumuSdkAgency::GetInstance()->LoginSDK(CUtils::s2ws(m_loginSDKParam.account), CUtils::s2ws(m_loginSDKParam.password));
    if (err != SDKERR_SUCCESS)
    {
        // ������¼����
        FeedbackLoginResult(LOGIN_FAILED);
        // ����������ʾ
        CString strErrMsg;
        strErrMsg.Format(_T("login SDK failure ! error code %d"), err);
        CString *pStr = new CString(strErrMsg);
        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
        LOGI << "[" << __FUNCTION__ << "] Zhumu SDK login SDK failure ! error code:" << err << std::endl;
    }
}

// ע�������ھ��
void CBusinessLogic::RegisterMainDlgHwnd(HWND hWnd)
{
    m_hWndMainDlg = hWnd;
}

HWND CBusinessLogic::GetMainDlgHwnd()
{
    return m_hWndMainDlg;
}

// ��ĿSDK�Ƿ��Ѿ���ʼ�� true-��ʼ�� false-δ��ʼ��
bool CBusinessLogic::GetZhumuSdkAlreadyInit() const
{
    return m_bZhumuSdkAlreadyInit;
}

void CBusinessLogic::SetZhumuSdkAlreadyInit(bool val)
{
    m_bZhumuSdkAlreadyInit = val;
}

// ��ĿSDK�Ƿ����ڵ�½ true-���ڵ�½ false-δ��¼
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