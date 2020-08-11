#ifndef _CUSTOMDATA_H_
#define _CUSTOMDATA_H_

#include <string>


const int g_nLocalListeningPort = 5551;                         // 本地tcp服务监听端口
const int g_nServerPort = 5550;                                 // 远端tcp服务监听端口
const std::string g_strServerIp = "127.0.0.1";                  // 远端tcp服务ip地址
const std::wstring g_strWebDomain = L"https://launcher.zhumu.me";
const std::wstring g_strAuthAppKey = L"wSP04BXf8rKdh8mFRtuQI32WvEin2TOC3PTw";
const std::wstring g_strAuthAppSecret = L"4iElB4tOdwkHa5qoA3h77fgCRWXC6i6GewTo";

//authParam.appKey = L"wSP04BXf8rKdh8mFRtuQI32WvEin2TOC3PTw";
//authParam.appSecret = L"4iElB4tOdwkHa5qoA3h77fgCRWXC6i6GewTo";

// 自定义消息
#define WMUSER_BUSINESS_QUIT_MSG		 _T("WMUSER_BUSINESS_QUIT-{C9817DD5-4A6F-4AA1-AC0D-9DFA5C0B8599}")
DECLARE_USER_MESSAGE(WMUSER_BUSINESS_QUIT)

#define WMUSER_BUSINESS_CUSTOM_ERROR_MSG		 _T("WMUSER_BUSINESS_CUSTOM_ERROR-{F413935B-D24E-4D4A-8CB4-B49B94719D94}")
DECLARE_USER_MESSAGE(WMUSER_BUSINESS_CUSTOM_ERROR)


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
