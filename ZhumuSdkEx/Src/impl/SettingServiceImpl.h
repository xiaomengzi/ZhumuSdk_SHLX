#ifndef _SETTINGSERVICEIMPL_H_
#define _SETTINGSERVICEIMPL_H_

#include "setting_service_interface.h"

using namespace ZHUMUSDKEX_NAMESPACE;

class CSettingServiceImpl
    :public ZHUMUSDKEX_NAMESPACE::ISettingService
{
public:
    CSettingServiceImpl();
    ~CSettingServiceImpl();

public:
    ////////////////////// ͨ������ //////////////////////////////

    /// �������ʱ���û�����Զ�����ȫ����Ƶģʽ
    virtual SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable);

    /// ����������Ƿ�ʼ����ʾ���������
    virtual SDKError EanbleAlwaysDisplayedMeetingCtrlBar(bool bEnable);

    /// �޹���Ա���
    virtual SDKError EanbleAlwaysJoinMeetingbeforeAdmin(bool bEnable);

    ////////////////////// ��Ƶ���� //////////////////////////////

    /// �������ʱ���û�����Զ�������Ƶ
    virtual SDKError EnableAutoJoinAudio(bool bEnable);

    /// ����λ��˽������
    virtual SDKError EnableParticipantsUnmuteWhenMeeting(bool bEnable);

    /// �����Ƿ����û�����������
    virtual SDKError EnableEchoCancellation(bool bEnable);

    ////////////////////// ��Ƶ���� //////////////////////////////

    /// ���û���ø�����Ƶ
    virtual SDKError EnableHDVideo(bool bEnable);

    /// ���û�����ڼ������ʱ�ر���Ƶ
    virtual SDKError EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable);

};

#endif //_SETTINGSERVICEIMPL_H_

