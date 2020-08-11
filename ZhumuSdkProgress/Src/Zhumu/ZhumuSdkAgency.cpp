#include "stdafx.h"
#include "ZhumuSdkAgency.h"
#include "Business/CustomData.h"
#include "BusinessLogic.h"
#include "plog/Log.h"
#include "Utils.h"


CZhumuSdkAgency *CZhumuSdkAgency::m_pInstance = nullptr;

CZhumuSdkAgency::CZhumuSdkAgency()
{
    m_pAuthService = nullptr;
}


CZhumuSdkAgency::~CZhumuSdkAgency()
{
}

void CZhumuSdkAgency::Destory()
{

}


CZhumuSdkAgency * CZhumuSdkAgency::Initialize()
{
    return CZhumuSdkAgency::GetInstance();
}

void CZhumuSdkAgency::Uninitialize()
{
    if (m_pInstance != nullptr)
    {
        delete m_pInstance;
    }
}

CZhumuSdkAgency * CZhumuSdkAgency::GetInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new CZhumuSdkAgency;
    }
    return m_pInstance;
}


void CZhumuSdkAgency::onAuthenticationReturn(AuthResult ret)
{
    CBusinessLogic::GetInstance()->AuthenticationReturn(ret);
    
}

void CZhumuSdkAgency::onLoginRet(LOGINSTATUS ret, IAccountInfo* pAccountInfo)
{
    CBusinessLogic::GetInstance()->LoginReturn(ret, pAccountInfo);
}

void CZhumuSdkAgency::onLogout()
{

}

void CZhumuSdkAgency::onZoomIdentityExpired()
{

}

void CZhumuSdkAgency::onZoomAuthIdentityExpired()
{

}

SDKError CZhumuSdkAgency::InitZhunmuSDK(ZOOM_SDK_NAMESPACE::InitParam& zm_param)
{
    return ZOOM_SDK_NAMESPACE::InitSDK(zm_param);
}

ZOOM_SDK_NAMESPACE::SDKError CZhumuSdkAgency::AuthSDK(wchar_t *key, wchar_t *secret)
{
    if (nullptr != m_pAuthService)
    {
        AuthParam authParam;
        authParam.appKey = key;
        authParam.appSecret = secret;

        SDKError err = m_pAuthService->SDKAuth(authParam);
        if (err != SDKError::SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] authentication failure ! error code: " << err;
        }
        return err;
    }
    return SDKERR_SUCCESS;
}

ZOOM_SDK_NAMESPACE::SDKError CZhumuSdkAgency::LoginSDK(std::wstring account, std::wstring password)
{
    LoginParam emailLoginParam;
    emailLoginParam.loginType = LoginType_Email;
    emailLoginParam.ut.emailLogin.userName = account.c_str();
    emailLoginParam.ut.emailLogin.password = password.c_str();
    //emailLoginParam.ut.emailLogin.userName = L"mengxw@suirui.com";
    //emailLoginParam.ut.emailLogin.password = L"zm123456";
    emailLoginParam.ut.emailLogin.bRememberMe = false;
    SDKError err = SDKERR_SUCCESS;
    
    if (nullptr != m_pAuthService)
    {
        err = m_pAuthService->Login(emailLoginParam);
        if (err != SDKError::SDKERR_SUCCESS)
        {
            LOGE << "[" << __FUNCTION__ << "] login SDK failure ! error code: " << err;
        }
        return err;
    }
    return SDKERR_UNKNOWN;
}

ZOOM_SDK_NAMESPACE::SDKError CZhumuSdkAgency::CreateAuthService()
{
    if (nullptr == m_pAuthService)
    {
        SDKError err = ZOOM_SDK_NAMESPACE::CreateAuthService(&m_pAuthService);

        if (err != SDKError::SDKERR_SUCCESS)
        {
            //LOGE << "Failed to create the authentication service interface";
            return err;
        }

        m_pAuthService->SetEvent(this);
        
        return SDKERR_SUCCESS;
    }
    return SDKERR_UNKNOWN;
}
