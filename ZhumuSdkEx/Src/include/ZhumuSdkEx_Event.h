#ifndef _ZHUMUSDKEX_EVENT_H_
#define _ZHUMUSDKEX_EVENT_H_

#include "ZhumuSdkEx_def.h"

//using namespace ZHUMUSDKEX_NAMESPACE;

BEGIN_ZHUMUSDKEX_NAMESPACE

class ZhumuSdkEx_Event
{
public:
    //init event
    virtual void onInitRet(SDKError status) = 0;
    //auth event
    virtual void onAuthRet(AuthResult status) = 0;
    //login event
    virtual void onLoginRet(LOGINSTATUS status) = 0;
    //meeting status event
    virtual void onMeetingStatus(MeetingStatus status, MeetingFailCode code) = 0;
    //exit app
    virtual void onExitApp() = 0;

    virtual void OnMeetingSettingResult(SettingServerType tyep, SDKError errorCode) = 0;

};

END_ZHUMUSDKEX_NAMESPACE

#endif // _ZHUMUSDKEX_EVENT_H_
