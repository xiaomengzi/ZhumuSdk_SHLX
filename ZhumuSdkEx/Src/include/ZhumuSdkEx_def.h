#ifndef _ZHUMUSDKEX_DEF_H_
#define _ZHUMUSDKEX_DEF_H_
#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>


#ifdef ZHUMUSDKEX_EXPORTS
#define ZHUMUSDKEX_API __declspec(dllexport)
#else
#define ZHUMUSDKEX_API __declspec(dllimport)
#endif

#define ZHUMUSDKEX_NAMESPACE ZhumuSdkEx
#define BEGIN_ZHUMUSDKEX_NAMESPACE namespace ZHUMUSDKEX_NAMESPACE {
#define END_ZHUMUSDKEX_NAMESPACE };
#define USING_ZHUMUSDKEX_NAMESPACE using namespace ZHUMUSDKEX_NAMESPACE;


BEGIN_ZHUMUSDKEX_NAMESPACE

/************************************************************************/
/* enum SDKError                                                        */
/************************************************************************/
enum SDKError
{
    SDKERR_SUCCESS = 0,///<�ɹ�.
    SDKERR_NO_IMPL,///<�˹��ܵ�ǰ��Ч. 
    SDKERR_WRONG_USEAGE,///<����ʹ�ù���. 
    SDKERR_INVALID_PARAMETER,///<��������.
    SDKERR_MODULE_LOAD_FAILED,///<����ģ��ʧ��.
    SDKERR_MEMORY_FAILED,///<�ڴ�δ����. 
    SDKERR_SERVICE_FAILED,///<�ڲ��������.
    SDKERR_UNINITIALIZE,///<ʹ��ǰδ��ʼ��.
    SDKERR_UNAUTHENTICATION,///<ʹ��ǰδ��֤.
    SDKERR_NORECORDINGINPROCESS,///<δ¼��.
    SDKERR_TRANSCODER_NOFOUND,///<ת��ģ��δ�ҵ�.
    SDKERR_VIDEO_NOTREADY,///<��Ƶ����ģ��δ����.
    SDKERR_NO_PERMISSION,///<��Ȩ��.
    SDKERR_UNKNOWN,///<δ֪����.
    SDKERR_OTHER_SDK_INSTANCE_RUNNING,///<�����SDKʵ����������.
    SDKERR_INTELNAL_ERROR,///<SDK�ڲ�����.
    SDKERR_NO_AUDIODEVICE_ISFOUND,///<δ������Ƶ�豸.
    SDKERR_NO_VIDEODEVICE_ISFOUND,///<δ������Ƶ�豸.
    SDKERR_TOO_FREQUENT_CALL,///<API����̫Ƶ��.
    SDKERR_FAIL_ASSIGN_USER_PRIVILEGE, ///<�޷�Ϊ�û������µ�Ȩ��.
    SDKERR_MEETING_DONT_SUPPORT_FEATURE,///<��ǰ���鲻֧�ָ�����.
    SDKERR_MEETING_NOT_SHARE_SENDER,///<��ǰ�û�������ʾ��.
    SDKERR_MEETING_YOU_HAVE_NO_SHARE,///<û�й���.
    SDKERR_MEETING_VIEWTYPE_PARAMETER_IS_WRONG, ///<�Ƿ��� ViewType ����.
    SDKERR_MEETING_ANNOTATION_IS_OFF, ///<ע�Ͳ�����.
    SDKERR_SETTING_OS_DONT_SUPPORT, ///<��ǰϵͳ��֧������.
};

/************************************************************************/
/*enum SDK_LANGUAGE_ID                                                  */
/************************************************************************/
enum SDK_LANGUAGE_ID
{
    LANGUAGE_Unknow = 0,
    LANGUAGE_English,
    LANGUAGE_Chinese_Simplified,
    LANGUAGE_Chinese_Traditional,
    LANGUAGE_Japanese,
    LANGUAGE_Spanish,
    LANGUAGE_German,
    LANGUAGE_French,
    LANGUAGE_Portuguese,
    LANGUAGE_Russian,
};

/************************************************************************/
/* auth result                                                          */
/************************************************************************/
enum AuthResult
{
    AUTHRET_SUCCESS,///<Authentication is successful.
    AUTHRET_KEYORSECRETEMPTY,///<The key or secret to authenticate is empty.
    AUTHRET_KEYORSECRETWRONG,///<The key or secret to authenticate is wrong.
    AUTHRET_ACCOUNTNOTSUPPORT,///<The user account does not support.
    AUTHRET_ACCOUNTNOTENABLESDK,///<The user account is not enabled for SDK.
    AUTHRET_UNKNOWN,///<Unknown error.
    AUTHRET_SERVICE_BUSY,///<Service is busy.
    AUTHRET_NONE,///<Initial status.
    AUTHRET_OVERTIME,///<Time out.
    AUTHRET_NETWORKISSUE,///<Network issues.
};

/************************************************************************/
/* enum Login status                                                    */
/************************************************************************/
enum LOGINSTATUS
{
    LOGIN_IDLE,///< δ��¼
    LOGIN_PROCESSING,///< ���ڵ�½
    LOGIN_SUCCESS,///< ��½�ɹ�
    LOGIN_FAILED,///< ��½ʧ��
};

/************************************************************************/
/* meeting status                                                       */
/************************************************************************/
enum MeetingStatus
{
    MEETING_STATUS_IDLE,///< ����״̬
    MEETING_STATUS_CONNECTING,///< ���ӻ��������
    MEETING_STATUS_WAITINGFORHOST,///< �ȴ������˿�ʼ����
    MEETING_STATUS_INMEETING,///< �����Ѿ��������ڻ�����
    MEETING_STATUS_DISCONNECTING,///<�Ͽ��������״̬
    MEETING_STATUS_RECONNECTING,///<����������
    MEETING_STATUS_FAILED,///< �������Ӵ���
    MEETING_STATUS_ENDED,///< �������
    MEETING_STATUS_UNKNOW,///<δ֪״̬
    MEETING_STATUS_LOCKED,///<��������
    MEETING_STATUS_UNLOCKED,///<����δ����
    MEETING_STATUS_IN_WAITING_ROOM,///<�ȴ�������
    MEETING_STATUS_WEBINAR_PROMOTE,
    MEETING_STATUS_WEBINAR_DEPROMOTE,
    MEETING_STATUS_JOIN_BREAKOUT_ROOM,
    MEETING_STATUS_LEAVE_BREAKOUT_ROOM,
    MEETING_STATUS_WAITING_EXTERNAL_SESSION_KEY,
};

/************************************************************************/
/* meeting failed code                                                  */
/************************************************************************/
enum MeetingFailCode
{
    MEETING_SUCCESS = 0,///<��ʼ����ɹ�
    MEETING_FAIL_NETWORK_ERR = 1,///<�������
    MEETING_FAIL_RECONNECT_ERR = 2,///<����ʧ��
    MEETING_FAIL_MMR_ERR = 3,///<��ý��·��������
    MEETING_FAIL_PASSWORD_ERR = 4,///<�������
    MEETING_FAIL_SESSION_ERR = 5,///<�Ự����
    MEETING_FAIL_MEETING_OVER = 6,///<�������
    MEETING_FAIL_MEETING_NOT_START = 7,///<����δ��ʼ
    MEETING_FAIL_MEETING_NOT_EXIST = 8,///<���鲻����
    MEETING_FAIL_MEETING_USER_FULL = 9,///<�����Ա����
    MEETING_FAIL_CLIENT_INCOMPATIBLE = 10,///<�ͻ��˲�����
    MEETING_FAIL_NO_MMR = 11,///<��ý��·��δ�ҵ�
    MEETING_FAIL_CONFLOCKED = 12,///<���鱻����
    MEETING_FAIL_MEETING_RESTRICTED = 13,///<��Ϊ��ͬ�˺����ƣ���������ʧ��
    MEETING_FAIL_MEETING_RESTRICTED_JBH = 14,///<���λ��߱�������������֮ǰ�������ʱ��Ϊ��ͬ�˺ű�����
    MEETING_FAIL_CANNOT_EMIT_WEBREQUEST = 15,///<���ܷ���web����
    MEETING_FAIL_CANNOT_START_TOKENEXPIRE = 16,///��Ҫ
    SESSION_VIDEO_ERR = 17,///<��ƵӲ�����������
    SESSION_AUDIO_AUTOSTARTERR = 18,///<��Ƶ�Զ���������
    MEETING_FAIL_REGISTERWEBINAR_FULL = 19,///<ע����������ֻ������Ѵﵽ����
    MEETING_FAIL_REGISTERWEBINAR_HOSTREGISTER = 20,///<���������ֻ������˵����ע���������ֻ� .
    MEETING_FAIL_REGISTERWEBINAR_PANELISTREGISTER = 21,///<��С���Ա�����ע���������ֻ� .
    MEETING_FAIL_REGISTERWEBINAR_DENIED_EMAIL = 22,///<ʹ�ñ��ܾ��ĵ����ʼ�ע���������ֻ�.
    MEETING_FAIL_ENFORCE_LOGIN = 23,///<�������ֻ��¼���� .
    CONF_FAIL_ZC_CERTIFICATE_CHANGED = 24,  ///<��Ч��windows SDK.
    CONF_FAIL_VANITY_NOT_EXIST = 27, ///<�������ID������.
    CONF_FAIL_JOIN_WEBINAR_WITHSAMEEMAIL = 28, ///<ʹ����ͬ��email�����������ֻ�.
    CONF_FAIL_DISALLOW_HOST_MEETING = 29, ///<�������ò�������ʼһ������
    MEETING_FAIL_WRITE_CONFIG_FILE = 50,	///<�����ļ�����д
    MEETING_FAIL_FORBID_TO_JOIN_INTERNAL_MEETING = 60, ///<��ֹ�����ڲ�����
    CONF_FAIL_REMOVED_BY_HOST = 61, ///<���������Ƴ�
};

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

/************************************************************************/
/* ��ʼ��SDK����                                                         */
/************************************************************************/
typedef struct stZmSdkInitParam
{
    char* bindingName;              // ������
    char* supportUrl;               // ����֧��URL
    char* webDomain;                // ������
    bool  asynchronous;             // �Ƿ��첽���� true-�첽 false-ͬ��
    int   timeOut;                  // ͬ����ʱʱ�� ��λ���� Ĭ��10��
    SDK_LANGUAGE_ID language;       // ����id

    stZmSdkInitParam()
    {
        bindingName = "TiYiYun";
        supportUrl = "https://www.cloudmeeting.com";
        webDomain = "https://launcher.zhumu.me";
        asynchronous = true;
        timeOut = 10000;
        language = LANGUAGE_Chinese_Simplified;

    }

}ZmSdkInitParam;

/************************************************************************/
/* ��¼SDK����                                                         */
/************************************************************************/
typedef struct stZmSdkLoginParam
{
    char* account;      // �û��� ����
    char* password;     // ����

    stZmSdkLoginParam()
    {
        account = nullptr; 
        password = nullptr;
    }

}ZmSdkLoginParam;

/************************************************************************/
/* ��ʼԤԼ����                                                          */
/************************************************************************/
typedef struct stZmStartAppointmentMeetingParam
{
    UINT64  meetingNumber;          /// ������롣.
    char*   participantId;          ///<�λ���ID����������ô�ʱ��SDK�����ô�ֵ��
    bool    isVideoOff;             ///<�رջ򲻹ر���Ƶ��True��ʾ�رա����⣬�����־���ܵ��������Ե�Ӱ�졣
    bool    isAudioOff;             ///<�رջ򲻹ر���Ƶ��True��ʾ�رա����⣬�����־���ܵ��������Ե�Ӱ�졣
    bool    isDirectShareDesktop;   ///<�Ƿ�ֱ�ӹ������档True��ʾ����
    stZmStartAppointmentMeetingParam()
    {
        meetingNumber = 0;
        participantId = nullptr;
        isVideoOff = true;
        isAudioOff = false;
        isDirectShareDesktop = false;
    }

}ZmStartAppointmentMeetingParam;

/************************************************************************/
/* ��ʼ��ʱ����                                                          */
/************************************************************************/
typedef struct stZmStartInstantMeetingParam
{
    char*	meetingTopic;			///< ��������
    char*	meetingParticipants;	///< ���������,ͨѶ¼�û�Id,�Զ��ŷָ� "1039022079703897890,1038722079703891234"
    bool	isVideoOff;				///< �Ƿ�ر���Ƶ
    bool	isAudioOff;				///< �Ƿ�ر���Ƶ
    bool    isDirectShareDesktop;   ///<�Ƿ�ֱ�ӹ������档True��ʾ����

    stZmStartInstantMeetingParam()
    {
        meetingTopic = nullptr;
        meetingParticipants = nullptr;
        isVideoOff = true;
        isAudioOff = false;
        isDirectShareDesktop = false;
    }

}ZmStartInstantMeetingParam;


/************************************************************************/
/* �������                                                    */
/************************************************************************/
typedef struct stZmJoinMeetingParam
{
    UINT64  meetingNumber;          ///������롣
    char*   userName;               /// ������ʾ����
    char*   psw;                    /// �������롣
    bool    isVideoOff;             /// �رջ򲻹ر���Ƶ��True��ʾ�رա����⣬�����־���ܵ��������Ե�Ӱ�졣
    bool    isAudioOff;             /// �رջ򲻹ر���Ƶ��True��ʾ�رա����⣬�����־���ܵ��������Ե�Ӱ�졣
    bool    isDirectShareDesktop;   /// �Ƿ�ֱ�ӹ������档True��ʾ����

    stZmJoinMeetingParam()
    {
        meetingNumber = 0;
        userName = nullptr;
        psw = nullptr;
        isVideoOff = true;
        isAudioOff = false;
        isDirectShareDesktop = false;
    }
}ZmJoinMeetingParam;

typedef struct stZmAnonymityJoinMeetingParam
{
    UINT64  meetingNumber;          ///������롣
    char*   userName;               /// ������ʾ����
    char*   psw;                    /// �������롣
    bool    isVideoOff;             /// �رջ򲻹ر���Ƶ��True��ʾ�رա����⣬�����־���ܵ��������Ե�Ӱ�졣
    bool    isAudioOff;             /// �رջ򲻹ر���Ƶ��True��ʾ�رա����⣬�����־���ܵ��������Ե�Ӱ�졣
    bool    isDirectShareDesktop;   /// �Ƿ�ֱ�ӹ������档True��ʾ����

    stZmAnonymityJoinMeetingParam()
    {
        meetingNumber = 0;
        userName = nullptr;
        psw = nullptr;
        isVideoOff = true;
        isAudioOff = false;
        isDirectShareDesktop = false;
    }
}ZmAnonymityJoinMeetingParam;


typedef struct stZmDirectSharingParam
{
    UINT64  meetingNumber;          ///������롣

    stZmDirectSharingParam()
    {
        meetingNumber = 0;
    }
}ZmDirectSharingParam;


END_ZHUMUSDKEX_NAMESPACE

#endif //_ZHUMUSDKEX_DEF_H_
