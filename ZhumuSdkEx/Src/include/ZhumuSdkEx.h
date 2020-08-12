#ifndef _ZHUMUSDKEX_H_
#define _ZHUMUSDKEX_H_

#include "ZhumuSdkEx_def.h"
#include "ZhumuSdkEx_Event.h"


BEGIN_ZHUMUSDKEX_NAMESPACE

extern "C"
{
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
    /* SJoin Meeting                                                        */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_SJoinMeeting(const char* meegtingNumber, const char* joinName, const char* meetingPassword = "", const bool videoon = true, const bool audioon = true, const char*bandingName = "zhumu", SDK_LANGUAGE_ID language = LANGUAGE_Chinese_Simplified);

    /************************************************************************/
    /* start App exit                                                       */
    /************************************************************************/
    ZHUMUSDKEX_API void Zhumu_AppExit();

    /************************************************************************/
    /* Set Active Window                                                    */
    /************************************************************************/
    ZHUMUSDKEX_API void SetWindowShowTop();

    /************************************************************************/
    /* Clean Up                                                              */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_CleanUp();

    /************************************************************************/
    /* 销毁SDK                                                               */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_DestorySDK();
}

END_ZHUMUSDKEX_NAMESPACE

#endif //_ZHUMUSDKEX_H_
