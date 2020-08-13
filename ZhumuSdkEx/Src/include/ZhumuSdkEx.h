#ifndef _ZHUMUSDKEX_H_
#define _ZHUMUSDKEX_H_

#include "ZhumuSdkEx_def.h"


BEGIN_ZHUMUSDKEX_NAMESPACE

extern "C"
{
    class ISettingService;
    class ZhumuSdkEx_Event;
    /************************************************************************/
    /* 创建sdk                                                              */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_CreateSDK(ZhumuSdkEx_Event* event, const char* exePath);

    /************************************************************************/
    /* 初始化SDK                                                             */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_InitSDK(ZmSdkInitParam initParam);

    /************************************************************************/
    /* 登录瞩目SDK                                                           */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_SLoginSDK(ZmSdkLoginParam loginParam);

    /************************************************************************/
    /* 开启预约会议                                                          */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_StartAppointmentMeeting(ZmStartAppointmentMeetingParam meetingParam);

    /************************************************************************/
    /* 开启即时会议                                                          */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_StartInstantMeeting(ZmStartInstantMeetingParam meetingParam);

    /************************************************************************/
    /* 加入会议                                                              */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_JoinMeeting(ZmJoinMeetingParam meetingParam);

    /************************************************************************/
    /*  匿名加入会议                                                         */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_AnonymityJoinMeeting(ZmAnonymityJoinMeetingParam meetingParam);

    /************************************************************************/
    /* 创建设置服务                                                          */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_CreateSettingService(ISettingService** ppSettingService);

    /************************************************************************/
    /* 销毁设置服务                                                          */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_DestroySettingService(ISettingService* pSettingService);

    /************************************************************************/
    /* 销毁SDK                                                               */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_DestorySDK();
}

END_ZHUMUSDKEX_NAMESPACE

#endif //_ZHUMUSDKEX_H_
