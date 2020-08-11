#ifndef _ZHUMUSDKEX_H_
#define _ZHUMUSDKEX_H_

#include "ZhumuSdkEx_def.h"

class ZhumuSdkEx_Event;

BEGIN_ZHUMUSDKEX_NAMESPACE

extern "C"
{
    /************************************************************************/
    /* ����sdk                                                              */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_CreateSDK(const ZMSdkCreateParam crateParam);

    /************************************************************************/
    /* ��ʼ��SDK                                                             */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_InitSDK(ZmSdkInitParam initParam);

    /************************************************************************/
    /* SLogin SDK                                                           */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_SLoginSDK(ZmSdkLoginParam loginParam);

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
    /* ����SDK                                                               */
    /************************************************************************/
    ZHUMUSDKEX_API SDKError Zhumu_DestorySDK();
}

END_ZHUMUSDKEX_NAMESPACE

#endif //_ZHUMUSDKEX_H_
