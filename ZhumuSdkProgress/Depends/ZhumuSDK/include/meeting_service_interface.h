/*!
* \文件 meeting_service_interface.h
* \描述 Meeting Service Interface
*
*/
#ifndef ZHUMU_MEETING_SERVICE_INTERFACE_H_
#define ZHUMU_MEETING_SERVICE_INTERFACE_H_
#include "zhumu_sdk_def.h"
/// \简述 Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum MeetingStatus
\描述：会议状态码.
下面是详细的结构描述.
*/
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

/*! \enum MeetingFailCode
\描述：会议失败码.
下面是详细的结构描述.
*/
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

enum MeetingEndReason
{
	EndMeetingReason_None = 0,
	EndMeetingReason_KickByHost = 1,
	EndMeetingReason_EndByHost = 2,
	EndMeetingReason_JBHTimeOut = 3,
	EndMeetingReason_NoAttendee = 4,
	EndMeetingReason_HostStartAnotherMeeting = 5,
	EndMeetingReason_FreeMeetingTimeOut = 6,
	EndMeetingReason_NetworkBroken,
};

/*! \enum MeetingType
\描述：会议类型.
下面是详细的结构描述.
*/
enum MeetingType
{
	MEETING_TYPE_NONE,
	MEETING_TYPE_NORMAL,
	MEETING_TYPE_WEBINAR,
	MEETING_TYPE_BREAKOUTROOM,
};

/*! \enum LeaveMeetingCmd
\描述：离开会议命令.
下面是详细的结构描述.
*/
enum LeaveMeetingCmd
{
	LEAVE_MEETING,///< 离开会议
	END_MEETING,///< 结束会议
};

/*! \enum SDKUserType
\描述：SDK用户类型
下面是详细的结构描述.
*/
enum SDKUserType
{
	SDK_UT_APIUSER = 99,///< API 用户类型, 即将弃用
	SDK_UT_NORMALUSER = 100,///< 正常用户类型
	SDK_UT_WITHOUT_LOGIN, ////< 不登陆开始会议
};

/*! \struct tagJoin参数4APIUser
\描述：API用户的加入会议参数
下面是详细的结构描述.
*/
typedef struct tagJoinParam4APIUser
{
	UINT64		   meetingNumber;///< 会议号
	const wchar_t* vanityID;///< 会议虚拟ID
	const wchar_t* userName;///< 加入名
	const wchar_t* psw;///< 会议密码
	HWND		   hDirectShareAppWnd;///< 直接共享应用
	const wchar_t* toke4enfrocelogin;///< 加入会时强制登陆
	const wchar_t* participantId;///< 对于会议参与者报告列表，需要启用Web后端。
	const wchar_t* webinarToken;///< 网络研讨会token.
	bool		   isDirectShareDesktop;///< 直接共享桌面
	bool		   isVideoOff;
	bool		   isAudioOff;
}JoinParam4APIUser;

/*! \struct tagJoinParam4WithoutLogin
\描述：没有登陆的成员加入会议参数
下面是详细的结构描述.
*/
typedef struct tagJoinParam4WithoutLogin : public tagJoinParam4APIUser
{
}JoinParam4WithoutLogin;

/*! \struct tagJoinParam4NormalUser
\描述： 正常用户加入会议参数.
下面是详细的结构描述.
*/
typedef struct tagJoinParam4NormalUser
{
	UINT64		   meetingNumber;///< 会议号
	const wchar_t* vanityID;///< 会议虚拟ID
	const wchar_t* userName;///< 加入会议名
	const wchar_t* psw;///< 会议密码
	HWND		   hDirectShareAppWnd;///< 直接共享应用窗口ID
	const wchar_t* participantId;///< 对于会议参与者报告列表，需要启用Web后端.
	const wchar_t* webinarToken;///< 网络研讨会token.
	bool		   isVideoOff;
	bool		   isAudioOff;
	bool		   isDirectShareDesktop;///< 直接共享桌面
}JoinParam4NormalUser;

/*! \struct tagJoinParam
\简述：加入会议参数.
下面是详细的结构描述.
*/
typedef struct tagJoinParam
{
	SDKUserType userType;///< 用户类型
	union
	{
		JoinParam4APIUser apiuserJoin;
		JoinParam4NormalUser normaluserJoin;
		JoinParam4WithoutLogin withoutloginuserJoin;
	} param;
	tagJoinParam()
	{
		userType = SDK_UT_APIUSER;
		memset(&param, 0, sizeof(param));
	}
}JoinParam;

/*! \struct tagStartParam4APIUser
\简述：开始会议参数.
下面是详细的结构描述.
*/
typedef struct tagStartParam4APIUser
{
	const wchar_t* userID;///<用户ID.
	const wchar_t* userToken;///<用户token
	const wchar_t* userName;///<登录时的用户名 .
	UINT64		   meetingNumber;///<会议号.
	const wchar_t* vanityID;///<会议虚拟ID.
	HWND		   hDirectShareAppWnd;///<直接开始共享的应用窗口句柄.
	const wchar_t* participantId;///<参会人ID. 当相关设置打开时，SDK将设置这个值.
	bool		   isDirectShareDesktop;///<是否直接开始共享桌面.
	bool		   isVideoOff;///<是否关闭视频，此标志受会议属性的影响.
	bool		   isAudioOff;///<是否关闭音频，此标志受会议属性的影响.
}StartParam4APIUser;


/*! \enum zhumu user type
\简述：SDK用户类型
下面是详细的结构描述.
*/
enum ZhumuUserType
{
	ZhumuUserType_APIUSER,
	ZhumuUserType_EMAIL_LOGIN,
	ZhumuUserType_FACEBOOK,
	ZhumuUserType_GoogleOAuth,
	ZhumuUserType_SSO,
	ZhumuUserType_Unknown,
};

/*! \struct tagStartParam4APIUser
\简述：未登陆用户开始会议参数
下面是详细的结构描述.
*/
typedef struct tagStartParam4WithoutLogin
{
	const wchar_t* userID;///<用户 ID.
	const wchar_t* userToken;///<用户 token.
	const wchar_t* userZAK;///<zhumu 账户token.
	const wchar_t* userName;///<加入会议时的用户名.
	ZhumuUserType   zhumuUserType;///<用户类型.
	UINT64		   meetingNumber;///<会议号.
	const wchar_t* vanityID;///<会议虚拟ID.
	HWND		   hDirectShareAppWnd;///<直接开始共享的应用窗口句柄.
	const wchar_t* participantId;///<参会人ID. 当相关设置打开时，SDK将设置这个值.
	bool		   isDirectShareDesktop;///<是否直接开始共享桌面.
	bool		   isVideoOff;///<是否关闭视频，此标志受会议属性的影响.
	bool		   isAudioOff;///<是否关闭音频，此标志受会议属性的影响.
}StartParam4WithoutLogin;

/*! \struct tagStartParam4NormalUser
\简述：普通用户开始会议参数.
下面是详细的结构描述.
*/
typedef struct tagStartParam4NormalUser
{
	UINT64		   meetingNumber;///<会议号.
	const wchar_t* vanityID;///<会议虚拟ID.
	HWND		   hDirectShareAppWnd;///<直接开始共享的应用窗口句柄.
	const wchar_t* participantId;///<参会人ID. 当相关设置打开时，SDK将设置这个值.
	bool		   isDirectShareDesktop;///<是否直接开始共享桌面.
	bool		   isVideoOff;///<是否关闭视频，此标志受会议属性的影响.
	bool		   isAudioOff;///<是否关闭音频，此标志受会议属性的影响.
}StartParam4NormalUser;


/*! \struct tagStartParam
\简述： 开始回忆参数.
下面是详细的结构描述.
*/
typedef struct tagStartParam
{
	SDKUserType userType;///< 会议类型
	union
	{
		StartParam4APIUser apiuserStart;
		StartParam4NormalUser normaluserStart;
		StartParam4WithoutLogin withoutloginStart;
	} param;
	tagStartParam()
	{
		userType = SDK_UT_APIUSER;
		memset(&param, 0, sizeof(param));
	}
}StartParam;

/*! \enum ConnectionQuality
\简述：连接质量
下面是详细的结构描述.
*/
enum ConnectionQuality
{
	Conn_Quality_Unknow,///<未知连接状态
	Conn_Quality_Very_Bad,///<连接质量非常差
	Conn_Quality_Bad,///<连接质量差
	Conn_Quality_Not_Good,///<连接质量不好
	Conn_Quality_Normal,///<连接质量正常
	Conn_Quality_Good,///<连接质量好.
	Conn_Quality_Excellent,///<连接质量非常好.
};

/*! \enum SDKViewType
\简述：SDK显示类型, 主显示器和副显示器
下面是详细的结构描述.
*/
enum SDKViewType
{
	SDK_FIRST_VIEW,///主显示器.
	SDK_SECOND_VIEW,///<副显示器.
};

/*! \enum MeetingConnType
\简介：会议连接类型.
下面是详细的结构描述.
*/
enum MeetingConnType
{
	Meeting_Conn_None,///<未连接.
	Meeting_Conn_Normal,///<正常连接.
	Meeting_Conn_FailOver,///<失败重连.
};

/// \简介：会议信息接口.
///
class IMeetingInfo
{
public:
	/// \简介：获取会议号
	/// \返回：返回值时当前会议号.
	virtual UINT64 GetMeetingNumber() = 0;

	/// \简介：获取会议ID
	/// \返回：返回值时当前会议ID
	virtual const wchar_t* GetMeetingID() = 0;

	/// \简介：获取会议著主题 
	/// \返回：返回值是当前会议的主题
	virtual const wchar_t* GetMeetingTopic() = 0;

	/// \简介：获取会议密码 
	/// \返回：返回值是当前会议密码 
	virtual const wchar_t* GetMeetingPassword() = 0;

	/// \简介：获取会议类型
	/// \返回：返回值是当前会议类型。获取更多会议类型信息，查看 MeetingType enum
	virtual MeetingType GetMeetingType() = 0;

	/// \简介：获取会议邮件邀请模板
	/// \返回：如果方法调用成功，返回值是会议邮件邀请模板
	/// 如果失败，返回值是NULL.
	virtual const wchar_t* GetInviteEmailTeamplate() = 0;

	/// \简介：回去会议邀请邮件主题
	/// \返回：如果方法调用成功，返回值是邮件主题 
	/// 如果失败，返回值是NULL
	virtual const wchar_t* GetInviteEmailTitle() = 0;

	/// \简介：获取加入会议的邀请URL
	/// \返回：如果方法调用成功，返回值是邀请加入的URL 
	/// 如果失败，返回值是NULL.
	virtual const wchar_t* GetJoinMeetingUrl() = 0;

	/// \简述：获取会议主持人的标签
	/// \返回：如果方法调用成功，会议主持人的标签.
	/// 如果失败，返回值是NULL
	virtual const wchar_t* GetMeetingHostTag() = 0;

	/// \简述：是否是内部会议.
	/// \返回： 会议是否是内部会议.
	virtual bool IsInternalMeeting() = 0;

	/// \简述：获取会议连接类型.
	/// \返回：会议连接类型
	virtual MeetingConnType GetMeetingConnType() = 0;

	virtual ~IMeetingInfo() {};
};

/*! \struct tagMeeting参数eter
\简述：会议参数
下面是详细的结构描述.
*/
typedef struct tagMeetingParameter
{
	MeetingType meeting_type;///<会议类型
	bool is_view_only;///<View only or not. True indicates to view only.
	UINT64 meeting_number;///<会议号.
	wchar_t* meeting_topic;///<会议主题.
	wchar_t* meeting_host;///<会议主持人.
	tagMeetingParameter()
	{
		meeting_type = MEETING_TYPE_NONE;
		is_view_only = true;
		meeting_number = 0;
		meeting_topic = NULL;
		meeting_host = NULL;
	}

	~tagMeetingParameter()
	{
		if (meeting_host)
		{
			delete[] meeting_host;
			meeting_host = NULL;
		}
		if (meeting_topic)
		{
			delete[] meeting_topic;
			meeting_topic = NULL;
		}
	}
}MeetingParameter;

/// \简述：会议外部安全密钥处理程序 
///
class IMeetingExternalSecureKeyHandler
{
public:
	/// \简述 设置新的安全密钥和聊天会话的iv
	virtual void SetChatSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \简述 设置新的安全密钥和文件传输会话的iv
	virtual void SetFileTransferSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \简述 设置新的安全密钥和音频会话的iv
	virtual void SetAudioSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \简述 设置新的安全密钥和视频会话的iv
	virtual void SetVideoSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \简述 设置新的安全密钥和共享会话的iv
	virtual void SetShareSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \简述 离开会议
	virtual void Cancel() = 0;

	/// \简述 继续参加/开始会议
	virtual void Confirm() = 0;

	virtual ~IMeetingExternalSecureKeyHandler() {};
};

/*! \enum StatisticsWarningType
\简述 会议统计警告类型.
下面是详细的结构描述.
*/
enum StatisticsWarningType
{
	Statistics_Warning_None,///<没有任何预警.
	Statistics_Warning_Network_Quality_Bad,///<网络连接质量较差
	Statistics_Warning_Busy_System,
};

/*! \enum OSSessionType
    \brief OS session type.
    Here are more detailed structural descriptions.
*/
enum OSSessionType
{
	OS_SessionType_NotHandle = 0,
	OS_SessionType_Lock, ///<equals to WTS_SESSION_LOCK
	OS_SessionType_Logoff,///<equals to WTS_SESSION_LOGOFF
	OS_SessionType_Remote_DISCONNECT,///<equals to WTS_REMOTE_DISCONNECT
};
/// \简述 会议服务回调事件
///
class IMeetingServiceEvent
{
public:
	/// \简述 会议状态更改回调
	/// \参数 status 会议状值.
	/// \参数 iResult 详细说明会议特殊情况的原因.
	/// 如果状态是 MEETING_STATUS_FAILED, iResult的值是 MeetingFailCode enum中的一个. 
	virtual void onMeetingStatusChanged(MeetingStatus status, int iResult = 0) = 0;

	/// \简述 会议统计警告通知回调
	/// \参数 type 会议统计警告类型.
	virtual void onMeetingStatisticsWarningNotification(StatisticsWarningType type) = 0;

	/// \简述 会议安全密钥通知，需要web后台和特殊帐户类型的支持.
	/// \参数 key 当前会议的安全密钥
	/// \参数 len 安全密钥的长度。
	/// \参数 pHandler 设置外部安全密钥或离开会议的处理程序.
	virtual void onMeetingSecureKeyNotification(const char* key, int len, IMeetingExternalSecureKeyHandler* pHandler) = 0;

	/// \简述 会议参数通知回调
	/// \参数 meeting_param 会议参数.
	/// 此回调将在in-meeting之前调用，此方法回调完成后 meeting_param 将被释放.
	virtual void onMeetingParameterNotification(const MeetingParameter* meeting_param) = 0;
};

class IAnnotationController;
class IMeetingAudioController;
class IMeetingBreakoutRoomsController;
class IMeetingChatController;
class IMeetingConfiguration;
class IMeetingH323Helper;
class IMeetingParticipantsController;
class IMeetingPhoneHelper;
class IMeetingRecordingController;
class IMeetingRemoteController;
class IMeetingShareController;
class IMeetingUIController;
class IMeetingVideoController;
class IMeetingWaitingRoomController;
class IMeetingLiveStreamController;
class IMeetingWebinarController;
class IClosedCaptionController;

/// \简述 会议服务接口
///
class IMeetingService
{
public:
	/// \简述 设置会议服务回调事件
	/// \参数 pEvent 指向接收会议事件的IMeetingServiceEvent*的指针. 
	/// \返回 如果函数成功，返回值为 SDKErr_Success.
	/// 如果函数失败，则返回值不是 SDKErr_Success. 要获取扩展的错误信息，请参考 SDKError enum.
	virtual SDKError SetEvent(IMeetingServiceEvent* pEvent) = 0;

	virtual SDKError HandleZoomWebUriProtocolAction(const wchar_t* protocol_action) = 0;

	/// \简述 加入会议.
	/// \参数 joinParam 加入会议的参数. 更多细节, 参见 joinParam 结构. 
	/// \返回 如果函数成功，返回值为 SDKErr_Success.
	/// 如果函数失败，则返回值不是 SDKErr_Success. 要获取扩展的错误信息，请参考 SDKError enum.
	virtual SDKError Join(JoinParam& joinParam) = 0;

	/// \简述 开始会议
	/// \参数 startParam 开始会议使用的参数, 详细查看 startParam. 
	/// \返回 如果函数成功，返回值为 SDKErr_Success.
	/// 如果函数失败，则返回值不是 SDKErr_Success. 要获取扩展的错误信息，请参考 SDKError enum.
	virtual SDKError Start(StartParam& startParam) = 0;

	/// \简述 离开会议
	/// \参数 leaveCmd 离开会议的命令参数, 详细查看 LeaveMeetingCmd. 
	/// \返回 如果函数成功，返回值为 SDKErr_Success.
	/// 如果函数失败，则返回值不是 SDKErr_Success. 要获取扩展的错误信息，请参考 SDKError enum.
	virtual SDKError Leave(LeaveMeetingCmd leaveCmd) = 0;

	/// \简述 获取会议状态
	/// \返回 返回值为当前会议状态，要获取扩展的错误信息，请参考 MeetingStatus enum
	virtual MeetingStatus GetMeetingStatus() = 0;

	/// \简述 锁定当前会议
	/// \返回 如果函数成功，返回值为 SDKErr_Success.
	/// 如果函数失败，则返回值不是 SDKErr_Success. 要获取扩展的错误信息，请参考 SDKError enum.
	virtual SDKError LockMeeting() = 0;

	/// \简述 解锁当前会议
	/// \返回 如果函数成功，返回值为 SDKErr_Success.
	/// 如果函数失败，则返回值不是 SDKErr_Success. 要获取扩展的错误信息，请参考 SDKError enum.
	virtual SDKError UnlockMeeting() = 0;

	/// \简述 获取会议锁定状态
	/// \返回 当前会议锁定状态.
	virtual bool IsMeetingLocked() = 0;

	/// \简述 获取会议信息
	/// 返回 如果函数成功，返回值为会议信息，否则为空.
	virtual IMeetingInfo* GetMeetingInfo() = 0;

	/// \简述 获取共享连接质量.
	/// \参数 bSending i如果为真，将返回发送状态，否则将返回接收状态.
	/// \返回 如果函数成功，则返回值为 ConnectionQuality enum .
	/// \如果你不在会议中，将返回 Conn_Quality_Unknow
	virtual ConnectionQuality GetSharingConnQuality(bool bSending = true) = 0;

	/// \简述 获得视频连接质量.
	/// \参数 bSending 如果为真，将返回发送状态，否则将返回接收状态.
	/// \返回 如果函数成功，则返回值为 ConnectionQuality enum.
	/// \如果你不在会议中，将返回  Conn_Quality_Unknow
	virtual ConnectionQuality GetVideoConnQuality(bool bSending = true) = 0;

	/// \简述 获得音频连接质量。
	/// \参数 bSending 如果为真，将返回发送状态，否则将返回接收状态。
	/// \返回 如果函数成功，则返回值为 ConnectionQuality enum.
	/// \如果你不在会议中，将返回  Conn_Quality_Unknow
	virtual ConnectionQuality GetAudioConnQuality(bool bSending = true) = 0;

	/// \简述 获取会议配置接口.
	/// \返回 如果函数成功，返回值是会议配置接口.
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingConfiguration* GetMeetingConfiguration() = 0;

	/// \简述 获取会议UI控制器
	/// \返回 如果函数成功，返回值是会议ui控制器接口
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingUIController* GetUIController() = 0;

	/// \简述 Get annotation controller
	/// \返回 如果函数成功，返回值是annotation controller接口。
	/// 如果函数失败，返回值为NULL。
	virtual IAnnotationController* GetAnnotationController() = 0;

	/// \简述 获取视频控制器
	/// \返回 如果函数成功，返回值为视频控制器接口。
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingVideoController* GetMeetingVideoController() = 0;

	/// \简述 获取远程控制器对象
	/// \返回 如果函数成功，返回值为远程控制器对象的指针。
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingRemoteController* GetMeetingRemoteController() = 0;

	/// \简述 获取共享控制器
	/// \返回 如果函数成功，返回值为共享控制器对象指针
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingShareController* GetMeetingShareController() = 0;

	/// \简述 获取音频控制器
	/// \返回 如果函数成功，返回值是音频控制器接口对象指针
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingAudioController* GetMeetingAudioController() = 0;

	/// \简述 获取录制控制器
	/// \返回 如果函数成功，返回值是录制接口
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingRecordingController* GetMeetingRecordingController() = 0;

	/// \简述 获取聊天控制器
	/// \返回 如果函数成功，返回值是聊天控制器接口指针。
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingChatController* GetMeetingChatController() = 0;

	/// \简述 Get waiting room controller
	/// \返回 If the function succeeds, the return value is audio controller interface.
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingWaitingRoomController* GetMeetingWaitingRoomController() = 0;

	/// \简述 获取H323会议帮助接口
	/// \返回 如果函数成功，则返回值是H323会议帮助接口指针.
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingH323Helper* GetH323Helper() = 0;

	/// \简述 获取电话会议帮助接口
	/// \返回 如果函数成功，则返回值是电话会议帮助接口
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingPhoneHelper* GetMeetingPhoneHelper() = 0;

	/// \简述 获取会议外呼控制器接口
	/// \返回 如果函数成功，则返回值是会议外呼控制器接口
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingBreakoutRoomsController* GetMeetingBreakoutRoomsController() = 0;

	/// \简述 获取参会者控制器
	/// \返回 如果函数成功，则返回值是参会者控制器接口.
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingParticipantsController* GetMeetingParticipantsController() = 0;

	/// \简述 获取实时流控制器
	/// \返回 如果函数成功，返回值为实时流控制器接口。
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingLiveStreamController* GetMeetingLiveStreamController() = 0;

	/// \简述 获取网络研讨会控制器
	/// \返回 如果函数成功，返回值为webinar控制器接口.
	/// 如果函数失败，返回值为NULL。
	virtual IMeetingWebinarController* GetMeetingWebinarController() = 0;

	/// \简述 获取关闭的标题控制器接口.
	/// \返回 如果函数成功，返回值是指向IMeetingWebinarController的指针。否则返回NULL。.
	virtual IClosedCaptionController* GetMeetingClosedCaptionController() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif