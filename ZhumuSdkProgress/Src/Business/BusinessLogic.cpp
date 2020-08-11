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
    m_pZhumuSdkAgency = nullptr;
    m_pAuthService = nullptr;
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
    if (nullptr == m_pZhumuSdkAgency)
    {
        m_pZhumuSdkAgency = new CZhumuSdkAgency();
    }
}

void CBusinessLogic::UnInitData()
{
    if (nullptr != m_pZhumuSdkAgency)
    {
        m_pZhumuSdkAgency->Destory();
    }
}

void CBusinessLogic::onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret)
{
    LOGI << "AuthenticationReturn Return :" << ret << " " << __FUNCTION__;

    // ����֤����ص����ϲ�
    FeedbackAuthResult(ret);

    //��֤�ɹ������������Դȷ��ִ������
    if (ret == AUTHRET_SUCCESS)
    {
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
        LOGI << " Zhumu SDK authentication failure ! error code:" << ret;
    }
}

void CBusinessLogic::onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo)
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

int CBusinessLogic::InitZhumuSDK(std::string strContent)
{
    int nRet = -1;
    if (true == m_bZhumuSdkAlreadyInit)
    {
        LOGE << "Zhumu SDK Already initialized! ";
        return nRet;
    }
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        std::string strBandingName = root["bandingName"].asString();
        std::string strSupportUrl = root["supportUrl"].asString();
        int         nSdkLangId = root["sdkLangId"].asInt();

        ZOOM_SDK_NAMESPACE::InitParam zm_param;
        zm_param.strWebDomain = g_strWebDomain.c_str();
        zm_param.strBrandingName = CUtils::s2ws(strBandingName).c_str();
        zm_param.emLanguageID = SDK_LANGUAGE_ID(nSdkLangId);
        zm_param.strSupportUrl = CUtils::s2ws(strSupportUrl).c_str();
        zm_param.uiWindowIconSmallID = IDI_ICON1;
        zm_param.uiWindowIconBigID = IDI_ICON1;
        zm_param.enableLogByDefault = true;
        SDKError err = ZOOM_SDK_NAMESPACE::InitSDK(zm_param);
        if (err != SDKError::SDKERR_SUCCESS)
        {
            CString strErrMsg;
            strErrMsg.Format(_T("init SDK error !error code %d"), err);
            CString *pStr = new CString(strErrMsg);
            PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);

            LOGI << " Zhumu SDK Failed to initialize! error code:" << err;
            nRet = err;
        }
        else
        {
            LOGI << " Zhumu SDK Successful initialization! error code:" << err;
            nRet = 0;
            if (nullptr == m_pAuthService)
            {
                SDKError err = ZOOM_SDK_NAMESPACE::CreateAuthService(&m_pAuthService);

                if (err != SDKError::SDKERR_SUCCESS)
                {
                    LOGE << "Failed to create the authentication service interface";
                    return err;
                }

                m_pAuthService->SetEvent(this);
                // ��¼��֤
                AuthParam authParam;
                authParam.appKey = const_cast<wchar_t*>(g_strAuthAppKey.c_str());
                authParam.appSecret = const_cast<wchar_t*>(g_strAuthAppSecret.c_str());

                err = m_pAuthService->SDKAuth(authParam);
                if (err != SDKError::SDKERR_SUCCESS)
                {
                    LOGE << "authentication failure ";
                    return err;
                }
                return SDKERR_SUCCESS;
            }

            m_bZhumuSdkAlreadyInit = true;
        }
    }
    else
    {
        LOGE << "json reader error! content:[" << strContent << "] " << __FUNCTION__;
        nRet = -1;
    }

    delete reader;
    return nRet;
}

int CBusinessLogic::LoginZhumuSDK(std::string strContent)
{
    int nRet = -1;
    if (false == m_bZhumuSdkAlreadyInit)
    {
        LOGE << "The SDK is not initialized! ";
        return nRet;
    }
    if (true == m_bAlreadyLanding || true == m_bIsLanding)
    {
        LOGE << "Logging in or already logged in to the SDK! ";
        return nRet;
    }

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(strContent.c_str(), strContent.c_str() + strContent.length(), &root, &errs);
    if (ok && errs.size() == 0)
    {
        // �����ַ�����ƴ�ӳ�ʼ������
        std::string strAccount = root["account"].asString();
        std::string strPassword = root["password"].asString();
        //std::string strSupportUrl = root["supportUrl"].asString();
        //std::string strApiurl = root["apiurl"].asString();
        //int         nSdkLangId = root["sdkLangId"].asInt();

        // �����¼����SDK����
        m_loginSDKParam.account = strAccount;
        m_loginSDKParam.password = strPassword;
        m_bIsDirectLogin = true;

        // ��¼��֤
        if (nullptr != m_pZhumuSdkAgency)
        {
            SDKError err= m_pZhumuSdkAgency->AuthSDK(const_cast<wchar_t*>(g_strAuthAppKey.c_str()), const_cast<wchar_t*>(g_strAuthAppSecret.c_str()));
            if (err != SDKERR_SUCCESS)
            {
                // ����������Ϣ
                FeedbackAuthResult(AUTHRET_UNKNOWN);
                // ����������ʾ
                CString strErrMsg;
                strErrMsg.Format(_T("authentication failure ! error code %d"), err);
                CString *pStr = new CString(strErrMsg);
                PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
                LOGI << " Zhumu SDK authentication failure ! error code:" << err;
            }
        }
    }
    else
    {
        LOGE << "json reader error! content:[" << strContent << "] " << __FUNCTION__;
        nRet = -1;
    }

    delete reader;
    return nRet;
}

// ע�������ھ��
void CBusinessLogic::DestroyZhumuSDK()
{
    // �˳�sdk
    PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_QUIT, NULL, NULL);
}

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
        LOGE << "On failure " << __FUNCTION__;
    }
    return bRet;
}

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
        LOGE << "On failure " << __FUNCTION__;
    }
    return bRet;
}

//void CBusinessLogic::AuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret)
//{
//    LOGI << "Authentication Return :" << ret << " " << __FUNCTION__;
//
//    // ����֤����ص����ϲ�
//    FeedbackAuthResult(ret);
//
//    //��֤�ɹ������������Դȷ��ִ������
//    if (ret == AUTHRET_SUCCESS)
//    {
//        if (m_bIsDirectLogin)
//        {
//            DirectLogin();
//        }
//    }
//    else
//    {
//        // ����������ʾ
//        CString strErrMsg;
//        strErrMsg.Format(_T("authentication failure ! error code %d"), ret);
//        CString *pStr = new CString(strErrMsg);
//        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
//        LOGI << " Zhumu SDK authentication failure ! error code:" << ret;
//    }
//}
//
//void CBusinessLogic::LoginReturn(LOGINSTATUS ret, IAccountInfo* pAccountInfo)
//{
//    LOGI << "Login Return:" << ret << " " << __FUNCTION__;
//
//    if (ret == AUTHRET_SUCCESS)
//    {
//        // ����֤����ص����ϲ�
//        FeedbackLoginResult(ret);
//    }
//    else if (ret == LOGIN_FAILED)
//    {
//        // ����������ʾ
//        CString strErrMsg;
//        strErrMsg.Format(_T("Login failure ! error code %d"), ret);
//        CString *pStr = new CString(strErrMsg);
//        PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
//        LOGI << " Zhumu SDK Login failure ! error code:" << ret;
//    }
//}

// ��¼
void CBusinessLogic::DirectLogin()
{
    if (nullptr != m_pZhumuSdkAgency)
    {
        SDKError err = m_pZhumuSdkAgency->LoginSDK(m_loginSDKParam.account, m_loginSDKParam.password);
        if (err != SDKERR_SUCCESS)
        {
            // ������¼����
            FeedbackLoginResult(LOGIN_FAILED);
            // ����������ʾ
            CString strErrMsg;
            strErrMsg.Format(_T("login SDK failure ! error code %d"), err);
            CString *pStr = new CString(strErrMsg);
            PostMessage(m_hWndMainDlg, WMUSER_BUSINESS_CUSTOM_ERROR, (WPARAM)pStr, 1);
            LOGI << " Zhumu SDK login SDK failure ! error code:" << err;
        }
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

LoginSDKParam CBusinessLogic::GetLoginSDKParam() const
{
    return m_loginSDKParam;
}

void CBusinessLogic::SetLoginSDKParam(LoginSDKParam val)
{
    m_loginSDKParam = val;
}
