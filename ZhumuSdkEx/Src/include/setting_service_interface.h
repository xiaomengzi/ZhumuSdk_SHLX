#ifndef _SETTING_SERVICE_INTERFACE_H_
#define _SETTING_SERVICE_INTERFACE_H_

#include "ZhumuSdkEx_def.h"


BEGIN_ZHUMUSDKEX_NAMESPACE


class ISettingService
{
public:
    ////////////////////// ͨ������ //////////////////////////////

    /// �������ʱ���û�����Զ�����ȫ����Ƶģʽ
    virtual SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable) = 0;

    /// ����������Ƿ�ʼ����ʾ���������
    virtual SDKError EanbleAlwaysDisplayedMeetingCtrlBar(bool bEnable) = 0;

    /// �޹���Ա���
    virtual SDKError EanbleAlwaysJoinMeetingbeforeAdmin(bool bEnable) = 0;

    ////////////////////// ��Ƶ���� //////////////////////////////

    /// �������ʱ���û�����Զ�������Ƶ
    virtual SDKError EnableAutoJoinAudio(bool bEnable) = 0;

    /// ����λ��˽������
    virtual SDKError EnableParticipantsUnmuteWhenMeeting(bool bEnable) = 0;

    /// �����Ƿ����û�����������
    virtual SDKError EnableEchoCancellation(bool bEnable) = 0;

    ////////////////////// ��Ƶ���� //////////////////////////////

    /// ���û���ø�����Ƶ
    virtual SDKError EnableHDVideo(bool bEnable) = 0;

    /// ���û�����ڼ������ʱ�ر���Ƶ
    virtual SDKError EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable) = 0;

};


END_ZHUMUSDKEX_NAMESPACE
#endif //_SETTING_SERVICE_INTERFACE_H_
