#ifndef _CUSTOMDATA_H_
#define _CUSTOMDATA_H_

#include <string>


const int g_nLocalListeningPort = 5551;                         // 本地tcp服务监听端口
const int g_nServerPort = 5550;                                 // 远端tcp服务监听端口
const std::string g_strServerIp = "127.0.0.1";                  // 远端tcp服务ip地址
const std::wstring g_strWebDomain = L"https://launcher.zhumu.me";
const std::wstring g_strAuthAppKey = L"kaiM02SkFATpUuPrvAXvEFN2qVOAhHlH3UQc";
const std::wstring g_strAuthAppSecret = L"frmtL8kBo6vlcpUn2JNbqoicT3jxdnDnSM5e";

//authParam.appKey = L"wSP04BXf8rKdh8mFRtuQI32WvEin2TOC3PTw";
//authParam.appSecret = L"4iElB4tOdwkHa5qoA3h77fgCRWXC6i6GewTo";

//authParam.appKey = L"kaiM02SkFATpUuPrvAXvEFN2qVOAhHlH3UQc";
//authParam.appSecret = L"frmtL8kBo6vlcpUn2JNbqoicT3jxdnDnSM5e";

//SdkKey = YIGHOLxzjr25DfncCtkpsrjErKQOG7z7D1g0
//SdkSecret = MfKkVGAl0EEbdPFoW56H2yMbHqJU7ePy0df1

//SdkKey = cveMm1R3wVbMr8CAMlbsrZ3i3WRjOB0vPBca
//SdkSecret = 2ejROvF23dIxOMbOzmtmgTJ16pEVBSEdeVQU

/************************************************************************/
/*                       自定义消息                                      */
/************************************************************************/
// 退出程序
#define WMUSER_BUSINESS_QUIT_MSG		 _T("WMUSER_BUSINESS_QUIT-{C9817DD5-4A6F-4AA1-AC0D-9DFA5C0B8599}")
DECLARE_USER_MESSAGE(WMUSER_BUSINESS_QUIT)

// 自定义错误消息弹出
#define WMUSER_BUSINESS_CUSTOM_ERROR_MSG		 _T("WMUSER_BUSINESS_CUSTOM_ERROR-{F413935B-D24E-4D4A-8CB4-B49B94719D94}")
DECLARE_USER_MESSAGE(WMUSER_BUSINESS_CUSTOM_ERROR)

// 初始化SDK
#define WMUSER_INIT_ZHUMUSDK_MSG		 _T("WMUSER_INIT_ZHUMUSDK-{3FEC0490-1690-4D76-9DC2-CC2397A96C3F}")
DECLARE_USER_MESSAGE(WMUSER_INIT_ZHUMUSDK)

// 登录瞩目SDK
#define WMUSER_LOGIN_ZHUMUSDK_MSG		 _T("WMUSER_LOGIN_ZHUMUSDK-{A5272737-9451-461F-B7B3-20FD27741447}")
DECLARE_USER_MESSAGE(WMUSER_LOGIN_ZHUMUSDK)


typedef struct _LoginSDKParam {
    std::string apiurl;
    std::string brandingname;
    int language;
    std::string supporturl;
    std::string account;
    std::string password;
    std::string zcode;
}LoginSDKParam;


#endif // _CUSTOMDATA_H_
