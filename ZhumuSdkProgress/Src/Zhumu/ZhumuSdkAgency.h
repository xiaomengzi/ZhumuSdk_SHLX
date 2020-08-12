#ifndef _ZHUMUSDKAGENCY_H_
#define _ZHUMUSDKAGENCY_H

#include <string>
#include "zoom_sdk.h"
#include "auth_service_interface.h"
#include "meeting_service_interface.h"

using namespace ZOOM_SDK_NAMESPACE;

class CAuthServiceEvent;

class CZhumuSdkAgency
   : public IAuthServiceEvent
   , public IMeetingServiceEvent
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

public: 
    // 认证服务回调
    virtual void onAuthenticationReturn(AuthResult ret);
    virtual void onLoginRet(LOGINSTATUS ret, IAccountInfo* pAccountInfo);
    virtual void onLogout();
    virtual void onZoomIdentityExpired();
    virtual void onZoomAuthIdentityExpired();

    // 会议服务回调
    virtual void onMeetingStatusChanged(MeetingStatus status, int iResult = 0);
    virtual void onMeetingStatisticsWarningNotification(StatisticsWarningType type);
    virtual void onMeetingSecureKeyNotification(const char* key, int len, IMeetingExternalSecureKeyHandler* pHandler);
    virtual void onMeetingParameterNotification(const MeetingParameter* meeting_param);

public:

    // 初始化瞩目SDK
    SDKError InitZhunmuSDK(ZOOM_SDK_NAMESPACE::InitParam& zm_param);

    // 登录验证
    SDKError AuthSDK(wchar_t *key, wchar_t *secret);

    // 登录
    SDKError LoginSDK(std::wstring account, std::wstring password);

    // 开启预约会议
    SDKError StartAppointmentMeeting(ZOOM_SDK_NAMESPACE::StartParam& startParam);

    // 开启即时会议
    SDKError StartInstantMeeting(ZOOM_SDK_NAMESPACE::StartParam& startParam);

    // 快速加入会议
    SDKError JoinMeeting(JoinParam& joinParam);

    // 匿名加入会议
    SDKError AnonymityJoinMeeting(JoinParam& joinParam);
    

    
    // 创建认证服务器
    SDKError CreateAuthService();

    // 创建会议服务器
    SDKError CreateMeetingService();

public:
    void Destory();

private:
    IAuthService* m_pAuthService;
    IMeetingService* m_pMeetingService;

};


#endif // _ZHUMUSDKAGENCY_H
