#ifndef _ZHUMUSDKIMPL_H_
#define _ZHUMUSDKIMPL_H_

#include "ZhumuSdkEx_Event.h"
#include "TcpServer\CustomTcpServer.h"

using namespace ZHUMUSDKEX_NAMESPACE;

class CZhumuSdkImpl 
    : public ZHUMUSDKEX_NAMESPACE::ZhumuSdkEx_Event
    , public CCustomTcpServerEvent
{
public:
    CZhumuSdkImpl();
    ~CZhumuSdkImpl();

public:
    // 设置监听回调对象
    void SetEvent(ZhumuSdkEx_Event* _event);

    // 开启tcp服务
    bool StartTcpServer();

    // 关闭tcp服务
    bool StopTcpServer();

    // 启动瞩目SDK独立进程
    bool StartSdkProcess(std::string strPath = "");

    // 初始化SDK
    bool InitSDK(ZmSdkInitParam initParam);

    // 登录SDK
    bool LoginSDK(ZmSdkLoginParam loginParam);

    // 开启预约会议
    bool StartAppointmentMeeting(ZmStartAppointmentMeetingParam meetingParam);

    // 开启即时会议
    bool StartInstantMeeting(ZmStartInstantMeetingParam meetingParam);

    // 加入会议
    bool JoinMeeting(ZmJoinMeetingParam meetingParam);

    // 匿名加入会议
    bool AnonymityJoinMeeting(ZmAnonymityJoinMeetingParam meetingParam);

    // 直接共享
    bool DirectSharing(ZmDirectSharingParam directSharingParam);

    // 销毁SDK
    bool DestorySDK();

public: // zhumusdkex event
    virtual void onInitRet(SDKError status);
    //auth event
    virtual void onAuthRet(AuthResult status);
    //login event
    virtual void onLoginRet(LOGINSTATUS status);
    //meeting status event
    virtual void onMeetingStatus(MeetingStatus status, MeetingFailCode code);
    //exit app
    virtual void onExitApp();

    /************************************************************************/
    /*  tcp 服务器接收信息回调                                                */
    /************************************************************************/
public: // tcp server event
    virtual int OnReceive(std::string strReceive, int iLength);
    virtual int OnInitResult(int nInitResult);
    virtual int OnAuthResult(int nAuthResult);
    virtual int OnLoginResult(int nLoginResult);
    virtual int OnMeetingStatusResult(int nMeetingStatus, int nFailCode);


private:
    ZhumuSdkEx_Event* m_event;
    CCustomTcpServer* m_pTcpServer;

};

#endif //_ZHUMUSDKIMPL_H_
