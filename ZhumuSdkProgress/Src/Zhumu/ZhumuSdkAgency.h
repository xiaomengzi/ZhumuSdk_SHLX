#ifndef _ZHUMUSDKAGENCY_H_
#define _ZHUMUSDKAGENCY_H

#include "TcpServer\CustomTcpServer.h"
#include "auth_service_interface.h"

using namespace ZOOM_SDK_NAMESPACE;


class CZhumuSdkAgency
   : public IAuthServiceEvent
{
public:
    CZhumuSdkAgency();
    ~CZhumuSdkAgency();

public: // ��֤����ص�
    virtual void onAuthenticationReturn(AuthResult ret);
    virtual void onLoginRet(LOGINSTATUS ret, IAccountInfo* pAccountInfo);
    virtual void onLogout();
    virtual void onZoomIdentityExpired();
    virtual void onZoomAuthIdentityExpired();

public:
    // ��¼��֤
    SDKError AuthSDK(wchar_t *key, wchar_t *secret);
    //��¼
    SDKError LoginSDK(std::string account, std::string password);
    
    SDKError CreateAuthService();

    void Destory();

private:
    IAuthService* m_pAuthService;

};


#endif // _ZHUMUSDKAGENCY_H
