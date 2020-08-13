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
    // ���ü����ص�����
    void SetEvent(ZhumuSdkEx_Event* _event);

    // ����tcp����
    bool StartTcpServer();

    // �ر�tcp����
    bool StopTcpServer();

    // ������ĿSDK��������
    bool StartSdkProcess(std::string strPath = "");

    // ��ʼ��SDK
    bool InitSDK(ZmSdkInitParam initParam);

    // ��¼SDK
    bool LoginSDK(ZmSdkLoginParam loginParam);

    // ����ԤԼ����
    bool StartAppointmentMeeting(ZmStartAppointmentMeetingParam meetingParam);

    // ������ʱ����
    bool StartInstantMeeting(ZmStartInstantMeetingParam meetingParam);

    // �������
    bool JoinMeeting(ZmJoinMeetingParam meetingParam);

    // �����������
    bool AnonymityJoinMeeting(ZmAnonymityJoinMeetingParam meetingParam);

    // ֱ�ӹ���
    bool DirectSharing(ZmDirectSharingParam directSharingParam);

    // ����SDK
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
    /*  tcp ������������Ϣ�ص�                                                */
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
