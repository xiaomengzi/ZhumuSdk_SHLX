#ifndef _ZHUMUSDKIMPL_H_
#define _ZHUMUSDKIMPL_H_

#include "ZhumuSdkEx_Event.h"
#include "TcpServer\CustomTcpServer.h"

using namespace ZHUMUSDKEX_NAMESPACE;

class CZhumuSdkImpl 
    : public ZhumuSdkEx_Event
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

    // 销毁SDK
    bool DestorySDK();

public: // zhumusdkex event
    //auth event
    virtual void onAuthRet(AuthResult status) {}
    //login event
    virtual void onLoginRet(LOGINSTATUS status) {}
    //meeting status event
    virtual void onMeetingStatus(MeetingStatus status, MeetingFailCode code) {}
    //exit app
    virtual void onExitApp() {}


public: // tcp server event
    virtual int OnReceive(std::string strData, int iLength) { return 0; }

private:
    ZhumuSdkEx_Event* m_event;
    CCustomTcpServer* m_pTcpServer;

};

#endif //_ZHUMUSDKIMPL_H_
