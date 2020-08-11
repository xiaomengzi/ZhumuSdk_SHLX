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
    // ����tcp����
    void StartTcpServer();

    // �ر�tcp����
    void StopTcpServer();

    /************************************************************************/
    /*                   �ϲ�Э����ô�����                                */
    /************************************************************************/
public:
    // ��ʼ����Ŀsdk
    int InitZhumuSDK(std::string strContent);

    // ��¼��Ŀsdk
    int LoginZhumuSDK(std::string strContent);

    // ������ĿSDK
    void DestroyZhumuSDK();

    /************************************************************************/
    /*                   ִ�н��Э�鷴��������                             */
    /************************************************************************/
public:
    // ������ʼ��SDK���
    bool FeedbackInitResult(ZOOM_SDK_NAMESPACE::SDKError ret);

    // ������֤���
    bool FeedbackAuthResult(ZOOM_SDK_NAMESPACE::AuthResult ret);

    // ������¼���
    bool FeedbackLoginResult(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret);  

    /************************************************************************/
    /*                   ��ĿSDK�ص�������                                 */
    /************************************************************************/
public:
    // ��ĿSDK ��֤�ص��¼�����
    void AuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);

    // ��ĿSDK ��¼�ص��¼�����
    void LoginReturn(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo);

private:
    // ��¼
    void DirectLogin();

public:
    // ע�������ھ��
    void RegisterMainDlgHwnd(HWND hWnd);
    HWND GetMainDlgHwnd();

    // ��ĿSDK�Ƿ��Ѿ���ʼ�� true-��ʼ�� false-δ��ʼ��
    bool GetZhumuSdkAlreadyInit() const;
    void SetZhumuSdkAlreadyInit(bool val);

    // ��ĿSDK�Ƿ����ڵ�½ true-���ڵ�½ false-δ��¼
    bool GetIsLanding() const;
    void SetIsLanding(bool val);

    // ��ĿSDK�Ƿ��Ѿ���¼ true-�Ѿ���¼ false-δ��¼
    bool GetAlreadyLanding() const;
    void SetAlreadyLanding(bool val);
    
    // ��¼SDK 
    bool GetIsDirectLogin() const;
    void SetIsDirectLogin(bool val);
    
    // �Ƿ�Ϊ�������
    bool GetIsAnonymousJoin() const;
    void SetIsAnonymousJoin(bool val);

    // �Ƿ��Ѿ���֤
    bool GetAlreadyAuth() const;
    void SetAlreadyAuth(bool val);

    // ��¼��ĿSDK����
    LoginSDKParam GetLoginSDKParam() const;
    void SetLoginSDKParam(LoginSDKParam val);
private:
    CCustomTcpServer    m_tcpServer;
    HWND                m_hWndMainDlg;
    bool                m_bZhumuSdkAlreadyInit; // ��ĿSDK�Ƿ��Ѿ���ʼ�� true-��ʼ�� false-δ��ʼ��
    bool                m_bIsLanding;           // ��ĿSDK�Ƿ����ڵ�½ true-���ڵ�½ false-δ��¼
    bool                m_bAlreadyLanding;      // ��ĿSDK�Ƿ��Ѿ���¼ true-�Ѿ���¼ false-δ��¼
    bool                m_bIsDirectLogin;       // ��¼SDK 
    bool                m_bIsAnonymousJoin;     // �Ƿ�Ϊ�������
    bool                m_bAlreadyAuth;         // �Ƿ��Ѿ���֤
    LoginSDKParam       m_loginSDKParam;        // ��¼��ĿSDK����

    CZhumuSdkAgency*    m_pZhumuSdkAgency;

};

#endif //_BUSINESSLOGIC_H_
