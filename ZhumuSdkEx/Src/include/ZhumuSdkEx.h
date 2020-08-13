#ifndef _ZHUMUSDKEX_H_
#define _ZHUMUSDKEX_H_

#include "ZhumuSdkEx_def.h"


BEGIN_ZHUMUSDKEX_NAMESPACE

extern "C"
{
    class ISettingService;
    class ZhumuSdkEx_Event;
    /************************************************************************/
    /* ����sdk                                                              */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_CreateSDK(ZhumuSdkEx_Event* event, const char* exePath);

    /************************************************************************/
    /* ��ʼ��SDK                                                             */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_InitSDK(ZmSdkInitParam initParam);

    /************************************************************************/
    /* ��¼��ĿSDK                                                           */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_SLoginSDK(ZmSdkLoginParam loginParam);

    /************************************************************************/
    /* ����ԤԼ����                                                          */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_StartAppointmentMeeting(ZmStartAppointmentMeetingParam meetingParam);

    /************************************************************************/
    /* ������ʱ����                                                          */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_StartInstantMeeting(ZmStartInstantMeetingParam meetingParam);

    /************************************************************************/
    /* �������                                                              */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_JoinMeeting(ZmJoinMeetingParam meetingParam);

    /************************************************************************/
    /*  �����������                                                         */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_AnonymityJoinMeeting(ZmAnonymityJoinMeetingParam meetingParam);

    /************************************************************************/
    /* �������÷���                                                          */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_CreateSettingService(ISettingService** ppSettingService);

    /************************************************************************/
    /* �������÷���                                                          */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_DestroySettingService(ISettingService* pSettingService);

    /************************************************************************/
    /* ����SDK                                                               */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_DestorySDK();
}

END_ZHUMUSDKEX_NAMESPACE

#endif //_ZHUMUSDKEX_H_
