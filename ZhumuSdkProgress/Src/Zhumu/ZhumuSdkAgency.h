#ifndef _ZHUMUSDKAGENCY_H_
#define _ZHUMUSDKAGENCY_H

#include <string>
#include "zoom_sdk.h"
#include "auth_service_interface.h"
#include "meeting_service_interface.h"
#include "setting_service_interface.h"

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

    ////////////////////// 通用设置 //////////////////////////////

    /// 加入会议时启用或禁用自动进入全屏视频模式
    SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable);

    /// 会议过程中是否始终显示会议控制栏
    SDKError EanbleAlwaysDisplayedMeetingCtrlBar(bool bEnable);

    /// 无管理员入会
    SDKError EanbleAlwaysJoinMeetingbeforeAdmin(bool bEnable);

    ////////////////////// 音频设置 //////////////////////////////

    /// 加入会议时启用或禁用自动加入音频
    SDKError EnableAutoJoinAudio(bool bEnable);

    /// 允许参会人解除静音
    SDKError EnableParticipantsUnmuteWhenMeeting(bool bEnable);

    /// 设置是否启用回声消除功能
    SDKError EnableEchoCancellation(bool bEnable);

    ////////////////////// 视频设置 //////////////////////////////

    /// 启用或禁用高清视频
    SDKError EnableHDVideo(bool bEnable);

    /// 启用或禁用在加入会议时关闭视频
    SDKError EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable);
    
    // 创建认证服务
    SDKError CreateAuthService();

    // 销毁认证服务
    SDKError DestroyAuthService();

    // 创建会议服务
    SDKError CreateMeetingService();
    
    // 销毁会议服务
    SDKError DestroyMeetingService();

    // 创建设置服务
    SDKError CreateSettingService();

    // 销毁设置服务
    SDKError DestroySettingService();
public:
    void Destory();

private:
    IAuthService* m_pAuthService;
    IMeetingService* m_pMeetingService;
    ISettingService* m_pSettingService;

};


#endif // _ZHUMUSDKAGENCY_H
