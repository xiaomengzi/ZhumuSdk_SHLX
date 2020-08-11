#ifndef _BUSINESSLOGIC_H_
#define _BUSINESSLOGIC_H_

#include "TcpServer\CustomTcpServer.h"

#include "auth_service_interface.h"
#include "CustomData.h"

class CZhumuSdkAgency;
class CAuthServiceEvent;

class CBusinessLogic
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
    // 开启tcp服务
    void StartTcpServer();

    // 关闭tcp服务
    void StopTcpServer();

    /************************************************************************/
    /*                   上层协议调用处理函数                                */
    /************************************************************************/
public:
    // 初始化瞩目sdk
    int InitZhumuSDK(std::string strContent);

    // 登录瞩目sdk
    int LoginZhumuSDK(std::string strContent);

    // 销毁瞩目SDK
    void DestroyZhumuSDK();

    /************************************************************************/
    /*                   执行结果协议反馈处理函数                             */
    /************************************************************************/
public:
    // 反馈初始化SDK结果
    bool FeedbackInitResult(ZOOM_SDK_NAMESPACE::SDKError ret);

    // 反馈认证结果
    bool FeedbackAuthResult(ZOOM_SDK_NAMESPACE::AuthResult ret);

    // 反馈登录结果
    bool FeedbackLoginResult(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret);  

    /************************************************************************/
    /*                   瞩目SDK回调处理函数                                 */
    /************************************************************************/
public:
    // 瞩目SDK 验证回调事件处理
    void AuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);

    // 瞩目SDK 登录回调事件处理
    void LoginReturn(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo);

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

    // 是否已经认证
    bool GetAlreadyAuth() const;
    void SetAlreadyAuth(bool val);

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
    bool                m_bAlreadyAuth;         // 是否已经认证
    LoginSDKParam       m_loginSDKParam;        // 登录瞩目SDK参数

    CZhumuSdkAgency*    m_pZhumuSdkAgency;

};

#endif //_BUSINESSLOGIC_H_
