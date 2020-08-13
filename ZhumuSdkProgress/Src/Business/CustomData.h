#ifndef _CUSTOMDATA_H_
#define _CUSTOMDATA_H_

#include <string>


const int g_nLocalListeningPort = 5551;                         // ����tcp��������˿�
const int g_nServerPort = 5550;                                 // Զ��tcp��������˿�
const std::string g_strServerIp = "127.0.0.1";                  // Զ��tcp����ip��ַ
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
/*                       �Զ�����Ϣ                                      */
/************************************************************************/
// �˳�����
#define WMUSER_BUSINESS_QUIT_MSG        _T("WMUSER_BUSINESS_QUIT-{C9817DD5-4A6F-4AA1-AC0D-9DFA5C0B8599}")
DECLARE_USER_MESSAGE(WMUSER_BUSINESS_QUIT)

// �Զ��������Ϣ����
#define WMUSER_BUSINESS_CUSTOM_ERROR_MSG        _T("WMUSER_BUSINESS_CUSTOM_ERROR-{F413935B-D24E-4D4A-8CB4-B49B94719D94}")
DECLARE_USER_MESSAGE(WMUSER_BUSINESS_CUSTOM_ERROR)

// ��ʼ��SDK
#define WMUSER_INIT_ZHUMUSDK_MSG         _T("WMUSER_INIT_ZHUMUSDK-{3FEC0490-1690-4D76-9DC2-CC2397A96C3F}")
DECLARE_USER_MESSAGE(WMUSER_INIT_ZHUMUSDK)

// ��¼��ĿSDK
#define WMUSER_LOGIN_ZHUMUSDK_MSG       _T("WMUSER_LOGIN_ZHUMUSDK-{A5272737-9451-461F-B7B3-20FD27741447}")
DECLARE_USER_MESSAGE(WMUSER_LOGIN_ZHUMUSDK)

// ����ԤԼ����
#define WMUSER_START_APPOINTMENTMEETING_ZHUMUSDK_MSG      _T("WMUSER_START_APPOINTMENTMEETING_ZHUMUSDK-{196F27C3-A68A-4C63-85C5-38C40DDB0B19}")
DECLARE_USER_MESSAGE(WMUSER_START_APPOINTMENTMEETING_ZHUMUSDK)

// ������ʱ����
#define WMUSER_START_INSTANTMEETING_ZHUMUSDK_MSG      _T("WMUSER_START_INSTANTMEETING_ZHUMUSDK-{FEDA703A-28CD-4484-BD48-8BBF4FB3B58C}")
DECLARE_USER_MESSAGE(WMUSER_START_INSTANTMEETING_ZHUMUSDK)

// �������
#define WMUSER_JOINMEETING_ZHUMUSDK_MSG      _T("WMUSER_JOINMEETI_ZHUMUSDK_MSG-{CF3D868E-4ACA-4189-873C-6ED65E150B7D}")
DECLARE_USER_MESSAGE(WMUSER_JOINMEETING_ZHUMUSDK)

// �����������
#define WMUSER_ANONYMITY_JOINMEETING_ZHUMUSDK_MSG      _T("WMUSER_ANONYMITY_JOINMEETING_ZHUMUSDK-{AF9969C5-92B7-4317-857A-B1391D475F0A}")
DECLARE_USER_MESSAGE(WMUSER_ANONYMITY_JOINMEETING_ZHUMUSDK)

// �����������
#define WMUSER_SETTINGMEETING_ZHUMUSDK_MSG      _T("WMUSER_SETTINGMEETING_ZHUMUSDK-{B54252FB-8F45-4E9E-A826-508A61ED986D}")
DECLARE_USER_MESSAGE(WMUSER_SETTINGMEETING_ZHUMUSDK)

// ֱ�ӹ���
#define WMUSER_DIRECTSHARING_ZHUMUSDK_MSG      _T("WMUSER_DIRECTSHARING_ZHUMUSDK-{EFAF6462-ECF6-4418-B50D-C9B7E303C387}")
DECLARE_USER_MESSAGE(WMUSER_DIRECTSHARING_ZHUMUSDK)


struct TPkgBody
{
    char name[30];
    short age;
    char desc[1];
};

typedef struct _LoginSDKParam {
    std::string apiurl;
    std::string brandingname;
    int language;
    std::string supporturl;
    std::string account;
    std::string password;
    std::string zcode;
}LoginSDKParam;


enum SettingServerType
{
    SETTIN_TYPE_AUTOFULLSCREEN = 0,                 /// �������ʱ���û�����Զ�����ȫ����Ƶģʽ
    SETTIN_TYPE_ALWAYSSHOWCTRLBAR = 1,              /// ����������Ƿ�ʼ����ʾ���������
    SETTIN_TYPE_ALWAYSJOINMEETINGBEFOREADMIN = 2,   /// �޹���Ա���
    SETTIN_TYPE_AUTOJOINAUDIO = 3,                  /// �������ʱ���û�����Զ�������Ƶ
    SETTIN_TYPE_PARTICIPANTSUNMUTE = 4,             /// ����λ��˽������
    SETTIN_TYPE_ECHOCANCELLATION = 5,               /// �����Ƿ����û�����������
    SETTIN_TYPE_HDVIDEO = 6,                        /// ���û���ø�����Ƶ
    SETTIN_TYPE_AUTOTURNOFFVIDEO = 7                /// ���û�����ڼ������ʱ�ر���Ƶ
};

#endif // _CUSTOMDATA_H_
