#ifndef _BUSINESSLOGIC_H_
#define _BUSINESSLOGIC_H_

#include "TcpServer\CustomTcpServer.h"

#include "auth_service_interface.h"
#include "CustomData.h"

class CZhumuSdkAgency;

class CBusinessLogic
    : public ZOOM_SDK_NAMESPACE::IAuthServiceEvent
{
private:
    CBusinessLogic();
    ~CBusinessLogic();

public:
    static CBusinessLogic *Initialize();
    static void Uninitialize();
    static CBusinessLogic *GetInstance();
    void InitData();
    void UnInitData();
private:
    static  CBusinessLogic    *m_pInstance;

public:
    virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);
    virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo);
    virtual void onLogout() {}
    virtual void onZoomIdentityExpired() {}
    virtual void onZoomAuthIdentityExpired() {}
public:
    // 开启tcp服务
    void StartTcpServer();

    // 关闭tcp服务
    void StopTcpServer();

    // 初始化瞩目sdk
    int InitZhumuSDK(std::string strContent);

    // 登录瞩目sdk
    int LoginZhumuSDK(std::string strContent);

    // 销毁瞩目SDK
    void DestroyZhumuSDK();

    // 反馈认证结果
    bool FeedbackAuthResult(ZOOM_SDK_NAMESPACE::AuthResult ret);

    // 反馈登录结果
    bool FeedbackLoginResult(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret);  
public:
    //// 瞩目SDK 验证回调事件处理
    //void AuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);

    //// 瞩目SDK 登录回调事件处理
    //void LoginReturn(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo);

private:
    // 登录
    void DirectLogin();

public:
    // 注册主窗口句柄
    void RegisterMainDlgHwnd(HWND hWnd);
    HWND GetMainDlgHwnd();

    // 瞩目SDK是否已经初始化 true-初始化 false-未初始化
    bool GetZhumuSdkAlreadyInit() const;
    void SetZhumuSdkAlreadyInit(bool val);

    // 瞩目SDK是否正在登陆 true-正在登陆 false-未登录
    bool GetIsLanding() const;
    void SetIsLanding(bool val);

    // 瞩目SDK是否已经登录 true-已经登录 false-未登录
    bool GetAlreadyLanding() const;
    void SetAlreadyLanding(bool val);
    
    // 登录SDK 
    bool GetIsDirectLogin() const;
    void SetIsDirectLogin(bool val);
    
    // 是否为匿名入会
    bool GetIsAnonymousJoin() const;
    void SetIsAnonymousJoin(bool val);

    // 登录瞩目SDK参数
    LoginSDKParam GetLoginSDKParam() const;
    void SetLoginSDKParam(LoginSDKParam val);
private:
    CCustomTcpServer    m_tcpServer;
    HWND                m_hWndMainDlg;
    bool                m_bZhumuSdkAlreadyInit; // 瞩目SDK是否已经初始化 true-初始化 false-未初始化
    bool                m_bIsLanding;           // 瞩目SDK是否正在登陆 true-正在登陆 false-未登录
    bool                m_bAlreadyLanding;      // 瞩目SDK是否已经登录 true-已经登录 false-未登录
    bool                m_bIsDirectLogin;       // 登录SDK 
    bool                m_bIsAnonymousJoin;     // 是否为匿名入会
    LoginSDKParam       m_loginSDKParam;        // 登录瞩目SDK参数

    CZhumuSdkAgency*    m_pZhumuSdkAgency;
   ZOOM_SDK_NAMESPACE::IAuthService*       m_pAuthService;

};

#endif //_BUSINESSLOGIC_H_
