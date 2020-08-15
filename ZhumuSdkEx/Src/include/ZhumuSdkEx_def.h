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
    SDKERR_SUCCESS = 0,///<成功.
    SDKERR_NO_IMPL,///<此功能当前无效. 
    SDKERR_WRONG_USEAGE,///<错误使用功能. 
    SDKERR_INVALID_PARAMETER,///<参数错误.
    SDKERR_MODULE_LOAD_FAILED,///<加载模块失败.
    SDKERR_MEMORY_FAILED,///<内存未申请. 
    SDKERR_SERVICE_FAILED,///<内部服务错误.
    SDKERR_UNINITIALIZE,///<使用前未初始化.
    SDKERR_UNAUTHENTICATION,///<使用前未认证.
    SDKERR_NORECORDINGINPROCESS,///<未录制.
    SDKERR_TRANSCODER_NOFOUND,///<转码模块未找到.
    SDKERR_VIDEO_NOTREADY,///<视频服务模块未就绪.
    SDKERR_NO_PERMISSION,///<无权限.
    SDKERR_UNKNOWN,///<未知错误.
    SDKERR_OTHER_SDK_INSTANCE_RUNNING,///<另外的SDK实例正在运行.
    SDKERR_INTELNAL_ERROR,///<SDK内部错误.
    SDKERR_NO_AUDIODEVICE_ISFOUND,///<未发现音频设备.
    SDKERR_NO_VIDEODEVICE_ISFOUND,///<未发现视频设备.
    SDKERR_TOO_FREQUENT_CALL,///<API调用太频繁.
    SDKERR_FAIL_ASSIGN_USER_PRIVILEGE, ///<无法为用户分配新的权限.
    SDKERR_MEETING_DONT_SUPPORT_FEATURE,///<当前会议不支持给特性.
    SDKERR_MEETING_NOT_SHARE_SENDER,///<当前用户不是演示者.
    SDKERR_MEETING_YOU_HAVE_NO_SHARE,///<没有共享.
    SDKERR_MEETING_VIEWTYPE_PARAMETER_IS_WRONG, ///<非法的 ViewType 参数.
    SDKERR_MEETING_ANNOTATION_IS_OFF, ///<注释不可用.
    SDKERR_SETTING_OS_DONT_SUPPORT, ///<当前系统不支持设置.
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
    LOGIN_IDLE,///< 未登录
    LOGIN_PROCESSING,///< 正在登陆
    LOGIN_SUCCESS,///< 登陆成功
    LOGIN_FAILED,///< 登陆失败
};

/************************************************************************/
/* meeting status                                                       */
/************************************************************************/
enum MeetingStatus
{
    MEETING_STATUS_IDLE,///< 空闲状态
    MEETING_STATUS_CONNECTING,///< 连接会议服务中
    MEETING_STATUS_WAITINGFORHOST,///< 等待主持人开始会议
    MEETING_STATUS_INMEETING,///< 会议已就绪，正在会议中
    MEETING_STATUS_DISCONNECTING,///<断开会议服务状态
    MEETING_STATUS_RECONNECTING,///<重新连接中
    MEETING_STATUS_FAILED,///< 会议连接错误
    MEETING_STATUS_ENDED,///< 会议结束
    MEETING_STATUS_UNKNOW,///<未知状态
    MEETING_STATUS_LOCKED,///<会议锁定
    MEETING_STATUS_UNLOCKED,///<会议未锁定
    MEETING_STATUS_IN_WAITING_ROOM,///<等待会议室
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
    MEETING_SUCCESS = 0,///<开始会议成功
    MEETING_FAIL_NETWORK_ERR = 1,///<网络错误
    MEETING_FAIL_RECONNECT_ERR = 2,///<重连失败
    MEETING_FAIL_MMR_ERR = 3,///<多媒体路由器错误
    MEETING_FAIL_PASSWORD_ERR = 4,///<密码错误
    MEETING_FAIL_SESSION_ERR = 5,///<会话错误
    MEETING_FAIL_MEETING_OVER = 6,///<会议结束
    MEETING_FAIL_MEETING_NOT_START = 7,///<会议未开始
    MEETING_FAIL_MEETING_NOT_EXIST = 8,///<会议不存在
    MEETING_FAIL_MEETING_USER_FULL = 9,///<会议成员已满
    MEETING_FAIL_CLIENT_INCOMPATIBLE = 10,///<客户端不兼容
    MEETING_FAIL_NO_MMR = 11,///<多媒体路由未找到
    MEETING_FAIL_CONFLOCKED = 12,///<会议被锁定
    MEETING_FAIL_MEETING_RESTRICTED = 13,///<因为相同账号限制，开启会议失败
    MEETING_FAIL_MEETING_RESTRICTED_JBH = 14,///<当参会者被允许在主持人之前加入会议时因为相同账号被限制
    MEETING_FAIL_CANNOT_EMIT_WEBREQUEST = 15,///<不能发送web请求
    MEETING_FAIL_CANNOT_START_TOKENEXPIRE = 16,///需要
    SESSION_VIDEO_ERR = 17,///<视频硬件或软件错误
    SESSION_AUDIO_AUTOSTARTERR = 18,///<音频自动开启错误
    MEETING_FAIL_REGISTERWEBINAR_FULL = 19,///<注册的网络研讨会数量已达到上限
    MEETING_FAIL_REGISTERWEBINAR_HOSTREGISTER = 20,///<以网络研讨会主持人的身份注册网络研讨会 .
    MEETING_FAIL_REGISTERWEBINAR_PANELISTREGISTER = 21,///<以小组成员的身份注册网络研讨会 .
    MEETING_FAIL_REGISTERWEBINAR_DENIED_EMAIL = 22,///<使用被拒绝的电子邮件注册网络研讨会.
    MEETING_FAIL_ENFORCE_LOGIN = 23,///<网络研讨会登录请求 .
    CONF_FAIL_ZC_CERTIFICATE_CHANGED = 24,  ///<无效的windows SDK.
    CONF_FAIL_VANITY_NOT_EXIST = 27, ///<虚拟会议ID不存在.
    CONF_FAIL_JOIN_WEBINAR_WITHSAMEEMAIL = 28, ///<使用相同的email加入网络研讨会.
    CONF_FAIL_DISALLOW_HOST_MEETING = 29, ///<会议设置不被允许开始一个会议
    MEETING_FAIL_WRITE_CONFIG_FILE = 50,	///<配置文件不可写
    MEETING_FAIL_FORBID_TO_JOIN_INTERNAL_MEETING = 60, ///<禁止加入内部会议
    CONF_FAIL_REMOVED_BY_HOST = 61, ///<被主持人移除
};

enum SettingServerType
{
    SETTIN_TYPE_AUTOFULLSCREEN = 0,                 /// 加入会议时启用或禁用自动进入全屏视频模式
    SETTIN_TYPE_ALWAYSSHOWCTRLBAR = 1,              /// 会议过程中是否始终显示会议控制栏
    SETTIN_TYPE_ALWAYSJOINMEETINGBEFOREADMIN = 2,   /// 无管理员入会
    SETTIN_TYPE_AUTOJOINAUDIO = 3,                  /// 加入会议时启用或禁用自动加入音频
    SETTIN_TYPE_PARTICIPANTSUNMUTE = 4,             /// 允许参会人解除静音
    SETTIN_TYPE_ECHOCANCELLATION = 5,               /// 设置是否启用回声消除功能
    SETTIN_TYPE_HDVIDEO = 6,                        /// 启用或禁用高清视频
    SETTIN_TYPE_AUTOTURNOFFVIDEO = 7                /// 启用或禁用在加入会议时关闭视频
};

/************************************************************************/
/* 初始化SDK参数                                                         */
/************************************************************************/
typedef struct stZmSdkInitParam
{
    char* bindingName;              // 标题名
    char* supportUrl;               // 技术支持URL
    char* webDomain;                // 网络域
    bool  asynchronous;             // 是否异步反馈 true-异步 false-同步
    int   timeOut;                  // 同步超时时间 单位毫秒 默认10秒
    SDK_LANGUAGE_ID language;       // 语言id

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
/* 登录SDK参数                                                         */
/************************************************************************/
typedef struct stZmSdkLoginParam
{
    char* account;      // 用户名 邮箱
    char* password;     // 密码

    stZmSdkLoginParam()
    {
        account = nullptr; 
        password = nullptr;
    }

}ZmSdkLoginParam;

/************************************************************************/
/* 开始预约会议                                                          */
/************************************************************************/
typedef struct stZmStartAppointmentMeetingParam
{
    UINT64  meetingNumber;          /// 会议号码。.
    char*   participantId;          ///<参会者ID。当相关设置打开时，SDK将设置此值。
    bool    isVideoOff;             ///<关闭或不关闭视频。True表示关闭。另外，这个标志会受到会议属性的影响。
    bool    isAudioOff;             ///<关闭或不关闭音频。True表示关闭。另外，这个标志会受到会议属性的影响。
    bool    isDirectShareDesktop;   ///<是否直接共享桌面。True表示分享。
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
/* 开始即时会议                                                          */
/************************************************************************/
typedef struct stZmStartInstantMeetingParam
{
    char*	meetingTopic;			///< 会议主题
    char*	meetingParticipants;	///< 会议参与人,通讯录用户Id,以逗号分割 "1039022079703897890,1038722079703891234"
    bool	isVideoOff;				///< 是否关闭视频
    bool	isAudioOff;				///< 是否关闭音频
    bool    isDirectShareDesktop;   ///<是否直接共享桌面。True表示分享。

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
/* 加入会议                                                    */
/************************************************************************/
typedef struct stZmJoinMeetingParam
{
    UINT64  meetingNumber;          ///会议号码。
    char*   userName;               /// 会议显示名称
    char*   psw;                    /// 会议密码。
    bool    isVideoOff;             /// 关闭或不关闭视频。True表示关闭。另外，这个标志会受到会议属性的影响。
    bool    isAudioOff;             /// 关闭或不关闭音频。True表示关闭。另外，这个标志会受到会议属性的影响。
    bool    isDirectShareDesktop;   /// 是否直接共享桌面。True表示分享。

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
    UINT64  meetingNumber;          ///会议号码。
    char*   userName;               /// 会议显示名称
    char*   psw;                    /// 会议密码。
    bool    isVideoOff;             /// 关闭或不关闭视频。True表示关闭。另外，这个标志会受到会议属性的影响。
    bool    isAudioOff;             /// 关闭或不关闭音频。True表示关闭。另外，这个标志会受到会议属性的影响。
    bool    isDirectShareDesktop;   /// 是否直接共享桌面。True表示分享。

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
    UINT64  meetingNumber;          ///会议号码。

    stZmDirectSharingParam()
    {
        meetingNumber = 0;
    }
}ZmDirectSharingParam;


END_ZHUMUSDKEX_NAMESPACE

#endif //_ZHUMUSDKEX_DEF_H_
