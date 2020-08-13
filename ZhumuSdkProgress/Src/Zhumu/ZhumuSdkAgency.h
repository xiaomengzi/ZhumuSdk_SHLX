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
    // ��֤����ص�
    virtual void onAuthenticationReturn(AuthResult ret);
    virtual void onLoginRet(LOGINSTATUS ret, IAccountInfo* pAccountInfo);
    virtual void onLogout();
    virtual void onZoomIdentityExpired();
    virtual void onZoomAuthIdentityExpired();

    // �������ص�
    virtual void onMeetingStatusChanged(MeetingStatus status, int iResult = 0);
    virtual void onMeetingStatisticsWarningNotification(StatisticsWarningType type);
    virtual void onMeetingSecureKeyNotification(const char* key, int len, IMeetingExternalSecureKeyHandler* pHandler);
    virtual void onMeetingParameterNotification(const MeetingParameter* meeting_param);

public:

    // ��ʼ����ĿSDK
    SDKError InitZhunmuSDK(ZOOM_SDK_NAMESPACE::InitParam& zm_param);

    // ��¼��֤
    SDKError AuthSDK(wchar_t *key, wchar_t *secret);

    // ��¼
    SDKError LoginSDK(std::wstring account, std::wstring password);

    // ����ԤԼ����
    SDKError StartAppointmentMeeting(ZOOM_SDK_NAMESPACE::StartParam& startParam);

    // ������ʱ����
    SDKError StartInstantMeeting(ZOOM_SDK_NAMESPACE::StartParam& startParam);

    // ���ټ������
    SDKError JoinMeeting(JoinParam& joinParam);

    // �����������
    SDKError AnonymityJoinMeeting(JoinParam& joinParam);

    ////////////////////// ͨ������ //////////////////////////////

    /// �������ʱ���û�����Զ�����ȫ����Ƶģʽ
    SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable);

    /// ����������Ƿ�ʼ����ʾ���������
    SDKError EanbleAlwaysDisplayedMeetingCtrlBar(bool bEnable);

    /// �޹���Ա���
    SDKError EanbleAlwaysJoinMeetingbeforeAdmin(bool bEnable);

    ////////////////////// ��Ƶ���� //////////////////////////////

    /// �������ʱ���û�����Զ�������Ƶ
    SDKError EnableAutoJoinAudio(bool bEnable);

    /// ����λ��˽������
    SDKError EnableParticipantsUnmuteWhenMeeting(bool bEnable);

    /// �����Ƿ����û�����������
    SDKError EnableEchoCancellation(bool bEnable);

    ////////////////////// ��Ƶ���� //////////////////////////////

    /// ���û���ø�����Ƶ
    SDKError EnableHDVideo(bool bEnable);

    /// ���û�����ڼ������ʱ�ر���Ƶ
    SDKError EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable);
    
    // ������֤����
    SDKError CreateAuthService();

    // ������֤����
    SDKError DestroyAuthService();

    // �����������
    SDKError CreateMeetingService();
    
    // ���ٻ������
    SDKError DestroyMeetingService();

    // �������÷���
    SDKError CreateSettingService();

    // �������÷���
    SDKError DestroySettingService();
public:
    void Destory();

private:
    IAuthService* m_pAuthService;
    IMeetingService* m_pMeetingService;
    ISettingService* m_pSettingService;

};


#endif // _ZHUMUSDKAGENCY_H
