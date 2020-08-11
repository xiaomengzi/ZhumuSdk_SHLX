#include "stdafx.h"
#include "ZhumuSdkAgency.h"
#include "Business/CustomData.h"
#include "BusinessLogic.h"
#include "plog/Log.h"
#include "zoom_sdk.h"
#include "Utils.h"


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

void CZhumuSdkAgency::onAuthenticationReturn(AuthResult ret)
{
    //CBusinessLogic::GetInstance()->AuthenticationReturn(ret);
}

void CZhumuSdkAgency::onLoginRet(LOGINSTATUS ret, IAccountInfo* pAccountInfo)
{
    //CBusinessLogic::GetInstance()->LoginReturn(ret, pAccountInfo);
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
            LOGE << "authentication failure ! error code: " << err;
        }
        return err;
    }
    return SDKERR_SUCCESS;
}

SDKError CZhumuSdkAgency::LoginSDK(std::string account, std::string password)
{
    LoginParam emailLoginParam;
    emailLoginParam.loginType = LoginType_Email;
    emailLoginParam.ut.emailLogin.userName = CUtils::s2ws(account).c_str();
    emailLoginParam.ut.emailLogin.password = CUtils::s2ws(password).c_str();
    emailLoginParam.ut.emailLogin.bRememberMe = false;
    SDKError err = SDKERR_SUCCESS;
    /*if (nullptr == m_pAuthService)
    {
        SDKError err = ZOOM_SDK_NAMESPACE::CreateAuthService(&m_pAuthService);

        if (err != SDKError::SDKERR_SUCCESS)
        {
            LOGE << "Failed to create the authentication service interface! " << __FUNCTION__;
            return err;
        }
    }*/
    if (nullptr != m_pAuthService)
    {
        err = m_pAuthService->Login(emailLoginParam);
        return err;
    }
}

ZOOM_SDK_NAMESPACE::SDKError CZhumuSdkAgency::CreateAuthService()
{
    if (nullptr == m_pAuthService)
    {
        SDKError err = ZOOM_SDK_NAMESPACE::CreateAuthService(&m_pAuthService);

        if (err != SDKError::SDKERR_SUCCESS)
        {
            LOGE << "Failed to create the authentication service interface";
            return err;
        }

        m_pAuthService->SetEvent(this);
        // µÇÂ¼ÑéÖ¤
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
    return SDKERR_UNKNOWN;
}
