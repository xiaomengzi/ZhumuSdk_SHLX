#ifndef _ZHUMUSDKAGENCY_H_
#define _ZHUMUSDKAGENCY_H

#include <string>
#include "zoom_sdk.h"
#include "auth_service_interface.h"

using namespace ZOOM_SDK_NAMESPACE;

class CAuthServiceEvent;

class CZhumuSdkAgency
   : public IAuthServiceEvent
{
private:
    CZhumuSdkAgency();
    ~CZhumuSdkAgency();

public:
    static CZhumuSdkAgency *Initialize();
    static void Uninitialize();
    static CZhumuSdkAgency *GetInstance();
private:
    static  CZhumuSdkAgency    *m_pInstance;

public: // 认证服务回调
    virtual void onAuthenticationReturn(AuthResult ret);
    virtual void onLoginRet(LOGINSTATUS ret, IAccountInfo* pAccountInfo);
    virtual void onLogout();
    virtual void onZoomIdentityExpired();
    virtual void onZoomAuthIdentityExpired();

public:

    // 初始化瞩目SDK
    SDKError InitZhunmuSDK(ZOOM_SDK_NAMESPACE::InitParam& zm_param);

    // 登录验证
    SDKError AuthSDK(wchar_t *key, wchar_t *secret);

    //登录
    SDKError LoginSDK(std::wstring account, std::wstring password);
    
    // 创建认证服务器
    SDKError CreateAuthService();

public:
    void Destory();

private:
    IAuthService* m_pAuthService;

};


#endif // _ZHUMUSDKAGENCY_H
