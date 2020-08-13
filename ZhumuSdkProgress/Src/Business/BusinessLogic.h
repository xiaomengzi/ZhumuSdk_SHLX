#ifndef _BUSINESSLOGIC_H_
#define _BUSINESSLOGIC_H_

#include "TcpServer\CustomTcpServer.h"

#include "auth_service_interface.h"
#include "CustomData.h"
#include "meeting_service_interface.h"
#include <map>

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

    // 开启预约会议
    int StartAppointmentMeetingZhumuSDK(std::string strContent);
    
    // 开启即时会议
    int StartInstantMeetingZhumuSDK(std::string strContent);

    // 加入会议
    int JoinMeetingZhumuSDK(std::string strContent);

    // 匿名加入会议
    int AnonymityJoinMeetingZhumuSDK(std::string strContent);

    // 通用设置
    int SettingMeetingZhumu(std::string strContent);

    // 设置默认麦克风
    int SelectMicZhumuSDK(std::string strContent);

    // 设置所选麦克风的音量。0~255
    int SetMicVolZhumuSDK(std::string strContent);

    // 选择扬声器装置。
    int SelectSpeakerZhumuSDK(std::string strContent);

    // 设置所选扬声器的音量。0~255
    int SetSpeakerVolZhumuSDK(std::string strContent);

    // 设置默认摄像头
    int SelectCameraZhumuSDK(std::string strContent);


    // 直接共享
    int DirectSharingZhumu(std::string strContent);

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

    // 反馈会议状态
    bool FeedbackMeetingStatusResult(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);

    // 反馈会议设置结果
    bool FeedbackMeetingSettingResult(SettingServerType settingType, ZOOM_SDK_NAMESPACE::SDKError ret);

    /************************************************************************/
    /*                   瞩目SDK回调处理函数                                 */
    /************************************************************************/
public:
    // 瞩目SDK 验证回调事件处理
    void AuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);

    // 瞩目SDK 登录回调事件处理
    void LoginReturn(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo);

    // 瞩目SDK 会议回调事件处理
    void MeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult /*= 0*/);

private:
    // 登录
    void DirectLogin();

    // 通过错误码获取错误描述
    CString GetErrorDescriptionByErrorCode(ZOOM_SDK_NAMESPACE::MeetingFailCode errCode);
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

    // 是否正在准备会议 true-正在准备会议 false-未准备会议
    bool GetReadyMeeting() const;
    void SetReadyMeeting(bool val);

    // 是否正在准备会议 true-正在准备会议 false-未准备会议
    bool GetAttendMeeting() const;
    void SetAttendMeeting(bool val);
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
    bool                m_bReadyMeeting;        // 是否正在准备会议 true-正在准备会议 false-未准备会议
    bool                m_bAttendMeeting;      // 是否正在准备会议 true-正在准备会议 false-未准备会议
    LoginSDKParam       m_loginSDKParam;        // 登录瞩目SDK参数

    CZhumuSdkAgency*    m_pZhumuSdkAgency;
    std::map<ZOOM_SDK_NAMESPACE::MeetingFailCode, CString> m_mapMeetFailCode;

};

#endif //_BUSINESSLOGIC_H_
