/*!
* \�ļ� meeting_service_interface.h
* \���� Meeting Service Interface
*
*/
#ifndef ZHUMU_MEETING_SERVICE_INTERFACE_H_
#define ZHUMU_MEETING_SERVICE_INTERFACE_H_
#include "zhumu_sdk_def.h"
/// \���� Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum MeetingStatus
\����������״̬��.
��������ϸ�Ľṹ����.
*/
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

/*! \enum MeetingFailCode
\����������ʧ����.
��������ϸ�Ľṹ����.
*/
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
\��������������.
��������ϸ�Ľṹ����.
*/
enum MeetingType
{
	MEETING_TYPE_NONE,
	MEETING_TYPE_NORMAL,
	MEETING_TYPE_WEBINAR,
	MEETING_TYPE_BREAKOUTROOM,
};

/*! \enum LeaveMeetingCmd
\�������뿪��������.
��������ϸ�Ľṹ����.
*/
enum LeaveMeetingCmd
{
	LEAVE_MEETING,///< �뿪����
	END_MEETING,///< ��������
};

/*! \enum SDKUserType
\������SDK�û�����
��������ϸ�Ľṹ����.
*/
enum SDKUserType
{
	SDK_UT_APIUSER = 99,///< API �û�����, ��������
	SDK_UT_NORMALUSER = 100,///< �����û�����
	SDK_UT_WITHOUT_LOGIN, ////< ����½��ʼ����
};

/*! \struct tagJoin����4APIUser
\������API�û��ļ���������
��������ϸ�Ľṹ����.
*/
typedef struct tagJoinParam4APIUser
{
	UINT64		   meetingNumber;///< �����
	const wchar_t* vanityID;///< ��������ID
	const wchar_t* userName;///< ������
	const wchar_t* psw;///< ��������
	HWND		   hDirectShareAppWnd;///< ֱ�ӹ���Ӧ��
	const wchar_t* toke4enfrocelogin;///< �����ʱǿ�Ƶ�½
	const wchar_t* participantId;///< ���ڻ�������߱����б���Ҫ����Web��ˡ�
	const wchar_t* webinarToken;///< �������ֻ�token.
	bool		   isDirectShareDesktop;///< ֱ�ӹ�������
	bool		   isVideoOff;
	bool		   isAudioOff;
}JoinParam4APIUser;

/*! \struct tagJoinParam4WithoutLogin
\������û�е�½�ĳ�Ա����������
��������ϸ�Ľṹ����.
*/
typedef struct tagJoinParam4WithoutLogin : public tagJoinParam4APIUser
{
}JoinParam4WithoutLogin;

/*! \struct tagJoinParam4NormalUser
\������ �����û�����������.
��������ϸ�Ľṹ����.
*/
typedef struct tagJoinParam4NormalUser
{
	UINT64		   meetingNumber;///< �����
	const wchar_t* vanityID;///< ��������ID
	const wchar_t* userName;///< ���������
	const wchar_t* psw;///< ��������
	HWND		   hDirectShareAppWnd;///< ֱ�ӹ���Ӧ�ô���ID
	const wchar_t* participantId;///< ���ڻ�������߱����б���Ҫ����Web���.
	const wchar_t* webinarToken;///< �������ֻ�token.
	bool		   isVideoOff;
	bool		   isAudioOff;
	bool		   isDirectShareDesktop;///< ֱ�ӹ�������
}JoinParam4NormalUser;

/*! \struct tagJoinParam
\����������������.
��������ϸ�Ľṹ����.
*/
typedef struct tagJoinParam
{
	SDKUserType userType;///< �û�����
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
\��������ʼ�������.
��������ϸ�Ľṹ����.
*/
typedef struct tagStartParam4APIUser
{
	const wchar_t* userID;///<�û�ID.
	const wchar_t* userToken;///<�û�token
	const wchar_t* userName;///<��¼ʱ���û��� .
	UINT64		   meetingNumber;///<�����.
	const wchar_t* vanityID;///<��������ID.
	HWND		   hDirectShareAppWnd;///<ֱ�ӿ�ʼ�����Ӧ�ô��ھ��.
	const wchar_t* participantId;///<�λ���ID. ��������ô�ʱ��SDK���������ֵ.
	bool		   isDirectShareDesktop;///<�Ƿ�ֱ�ӿ�ʼ��������.
	bool		   isVideoOff;///<�Ƿ�ر���Ƶ���˱�־�ܻ������Ե�Ӱ��.
	bool		   isAudioOff;///<�Ƿ�ر���Ƶ���˱�־�ܻ������Ե�Ӱ��.
}StartParam4APIUser;


/*! \enum zhumu user type
\������SDK�û�����
��������ϸ�Ľṹ����.
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
\������δ��½�û���ʼ�������
��������ϸ�Ľṹ����.
*/
typedef struct tagStartParam4WithoutLogin
{
	const wchar_t* userID;///<�û� ID.
	const wchar_t* userToken;///<�û� token.
	const wchar_t* userZAK;///<zhumu �˻�token.
	const wchar_t* userName;///<�������ʱ���û���.
	ZhumuUserType   zhumuUserType;///<�û�����.
	UINT64		   meetingNumber;///<�����.
	const wchar_t* vanityID;///<��������ID.
	HWND		   hDirectShareAppWnd;///<ֱ�ӿ�ʼ�����Ӧ�ô��ھ��.
	const wchar_t* participantId;///<�λ���ID. ��������ô�ʱ��SDK���������ֵ.
	bool		   isDirectShareDesktop;///<�Ƿ�ֱ�ӿ�ʼ��������.
	bool		   isVideoOff;///<�Ƿ�ر���Ƶ���˱�־�ܻ������Ե�Ӱ��.
	bool		   isAudioOff;///<�Ƿ�ر���Ƶ���˱�־�ܻ������Ե�Ӱ��.
}StartParam4WithoutLogin;

/*! \struct tagStartParam4NormalUser
\��������ͨ�û���ʼ�������.
��������ϸ�Ľṹ����.
*/
typedef struct tagStartParam4NormalUser
{
	UINT64		   meetingNumber;///<�����.
	const wchar_t* vanityID;///<��������ID.
	HWND		   hDirectShareAppWnd;///<ֱ�ӿ�ʼ�����Ӧ�ô��ھ��.
	const wchar_t* participantId;///<�λ���ID. ��������ô�ʱ��SDK���������ֵ.
	bool		   isDirectShareDesktop;///<�Ƿ�ֱ�ӿ�ʼ��������.
	bool		   isVideoOff;///<�Ƿ�ر���Ƶ���˱�־�ܻ������Ե�Ӱ��.
	bool		   isAudioOff;///<�Ƿ�ر���Ƶ���˱�־�ܻ������Ե�Ӱ��.
}StartParam4NormalUser;


/*! \struct tagStartParam
\������ ��ʼ�������.
��������ϸ�Ľṹ����.
*/
typedef struct tagStartParam
{
	SDKUserType userType;///< ��������
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
\��������������
��������ϸ�Ľṹ����.
*/
enum ConnectionQuality
{
	Conn_Quality_Unknow,///<δ֪����״̬
	Conn_Quality_Very_Bad,///<���������ǳ���
	Conn_Quality_Bad,///<����������
	Conn_Quality_Not_Good,///<������������
	Conn_Quality_Normal,///<������������
	Conn_Quality_Good,///<����������.
	Conn_Quality_Excellent,///<���������ǳ���.
};

/*! \enum SDKViewType
\������SDK��ʾ����, ����ʾ���͸���ʾ��
��������ϸ�Ľṹ����.
*/
enum SDKViewType
{
	SDK_FIRST_VIEW,///����ʾ��.
	SDK_SECOND_VIEW,///<����ʾ��.
};

/*! \enum MeetingConnType
\��飺������������.
��������ϸ�Ľṹ����.
*/
enum MeetingConnType
{
	Meeting_Conn_None,///<δ����.
	Meeting_Conn_Normal,///<��������.
	Meeting_Conn_FailOver,///<ʧ������.
};

/// \��飺������Ϣ�ӿ�.
///
class IMeetingInfo
{
public:
	/// \��飺��ȡ�����
	/// \���أ�����ֵʱ��ǰ�����.
	virtual UINT64 GetMeetingNumber() = 0;

	/// \��飺��ȡ����ID
	/// \���أ�����ֵʱ��ǰ����ID
	virtual const wchar_t* GetMeetingID() = 0;

	/// \��飺��ȡ���������� 
	/// \���أ�����ֵ�ǵ�ǰ���������
	virtual const wchar_t* GetMeetingTopic() = 0;

	/// \��飺��ȡ�������� 
	/// \���أ�����ֵ�ǵ�ǰ�������� 
	virtual const wchar_t* GetMeetingPassword() = 0;

	/// \��飺��ȡ��������
	/// \���أ�����ֵ�ǵ�ǰ�������͡���ȡ�������������Ϣ���鿴 MeetingType enum
	virtual MeetingType GetMeetingType() = 0;

	/// \��飺��ȡ�����ʼ�����ģ��
	/// \���أ�����������óɹ�������ֵ�ǻ����ʼ�����ģ��
	/// ���ʧ�ܣ�����ֵ��NULL.
	virtual const wchar_t* GetInviteEmailTeamplate() = 0;

	/// \��飺��ȥ���������ʼ�����
	/// \���أ�����������óɹ�������ֵ���ʼ����� 
	/// ���ʧ�ܣ�����ֵ��NULL
	virtual const wchar_t* GetInviteEmailTitle() = 0;

	/// \��飺��ȡ������������URL
	/// \���أ�����������óɹ�������ֵ����������URL 
	/// ���ʧ�ܣ�����ֵ��NULL.
	virtual const wchar_t* GetJoinMeetingUrl() = 0;

	/// \��������ȡ���������˵ı�ǩ
	/// \���أ�����������óɹ������������˵ı�ǩ.
	/// ���ʧ�ܣ�����ֵ��NULL
	virtual const wchar_t* GetMeetingHostTag() = 0;

	/// \�������Ƿ����ڲ�����.
	/// \���أ� �����Ƿ����ڲ�����.
	virtual bool IsInternalMeeting() = 0;

	/// \��������ȡ������������.
	/// \���أ�������������
	virtual MeetingConnType GetMeetingConnType() = 0;

	virtual ~IMeetingInfo() {};
};

/*! \struct tagMeeting����eter
\�������������
��������ϸ�Ľṹ����.
*/
typedef struct tagMeetingParameter
{
	MeetingType meeting_type;///<��������
	bool is_view_only;///<View only or not. True indicates to view only.
	UINT64 meeting_number;///<�����.
	wchar_t* meeting_topic;///<��������.
	wchar_t* meeting_host;///<����������.
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

/// \�����������ⲿ��ȫ��Կ������� 
///
class IMeetingExternalSecureKeyHandler
{
public:
	/// \���� �����µİ�ȫ��Կ������Ự��iv
	virtual void SetChatSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \���� �����µİ�ȫ��Կ���ļ�����Ự��iv
	virtual void SetFileTransferSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \���� �����µİ�ȫ��Կ����Ƶ�Ự��iv
	virtual void SetAudioSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \���� �����µİ�ȫ��Կ����Ƶ�Ự��iv
	virtual void SetVideoSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \���� �����µİ�ȫ��Կ�͹���Ự��iv
	virtual void SetShareSessionKey(const char* key, int key_len, const char* iv, int iv_len) = 0;

	/// \���� �뿪����
	virtual void Cancel() = 0;

	/// \���� �����μ�/��ʼ����
	virtual void Confirm() = 0;

	virtual ~IMeetingExternalSecureKeyHandler() {};
};

/*! \enum StatisticsWarningType
\���� ����ͳ�ƾ�������.
��������ϸ�Ľṹ����.
*/
enum StatisticsWarningType
{
	Statistics_Warning_None,///<û���κ�Ԥ��.
	Statistics_Warning_Network_Quality_Bad,///<�������������ϲ�
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
/// \���� �������ص��¼�
///
class IMeetingServiceEvent
{
public:
	/// \���� ����״̬���Ļص�
	/// \���� status ����״ֵ.
	/// \���� iResult ��ϸ˵���������������ԭ��.
	/// ���״̬�� MEETING_STATUS_FAILED, iResult��ֵ�� MeetingFailCode enum�е�һ��. 
	virtual void onMeetingStatusChanged(MeetingStatus status, int iResult = 0) = 0;

	/// \���� ����ͳ�ƾ���֪ͨ�ص�
	/// \���� type ����ͳ�ƾ�������.
	virtual void onMeetingStatisticsWarningNotification(StatisticsWarningType type) = 0;

	/// \���� ���鰲ȫ��Կ֪ͨ����Ҫweb��̨�������ʻ����͵�֧��.
	/// \���� key ��ǰ����İ�ȫ��Կ
	/// \���� len ��ȫ��Կ�ĳ��ȡ�
	/// \���� pHandler �����ⲿ��ȫ��Կ���뿪����Ĵ������.
	virtual void onMeetingSecureKeyNotification(const char* key, int len, IMeetingExternalSecureKeyHandler* pHandler) = 0;

	/// \���� �������֪ͨ�ص�
	/// \���� meeting_param �������.
	/// �˻ص�����in-meeting֮ǰ���ã��˷����ص���ɺ� meeting_param �����ͷ�.
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

/// \���� �������ӿ�
///
class IMeetingService
{
public:
	/// \���� ���û������ص��¼�
	/// \���� pEvent ָ����ջ����¼���IMeetingServiceEvent*��ָ��. 
	/// \���� ��������ɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ��򷵻�ֵ���� SDKErr_Success. Ҫ��ȡ��չ�Ĵ�����Ϣ����ο� SDKError enum.
	virtual SDKError SetEvent(IMeetingServiceEvent* pEvent) = 0;

	virtual SDKError HandleZoomWebUriProtocolAction(const wchar_t* protocol_action) = 0;

	/// \���� �������.
	/// \���� joinParam �������Ĳ���. ����ϸ��, �μ� joinParam �ṹ. 
	/// \���� ��������ɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ��򷵻�ֵ���� SDKErr_Success. Ҫ��ȡ��չ�Ĵ�����Ϣ����ο� SDKError enum.
	virtual SDKError Join(JoinParam& joinParam) = 0;

	/// \���� ��ʼ����
	/// \���� startParam ��ʼ����ʹ�õĲ���, ��ϸ�鿴 startParam. 
	/// \���� ��������ɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ��򷵻�ֵ���� SDKErr_Success. Ҫ��ȡ��չ�Ĵ�����Ϣ����ο� SDKError enum.
	virtual SDKError Start(StartParam& startParam) = 0;

	/// \���� �뿪����
	/// \���� leaveCmd �뿪������������, ��ϸ�鿴 LeaveMeetingCmd. 
	/// \���� ��������ɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ��򷵻�ֵ���� SDKErr_Success. Ҫ��ȡ��չ�Ĵ�����Ϣ����ο� SDKError enum.
	virtual SDKError Leave(LeaveMeetingCmd leaveCmd) = 0;

	/// \���� ��ȡ����״̬
	/// \���� ����ֵΪ��ǰ����״̬��Ҫ��ȡ��չ�Ĵ�����Ϣ����ο� MeetingStatus enum
	virtual MeetingStatus GetMeetingStatus() = 0;

	/// \���� ������ǰ����
	/// \���� ��������ɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ��򷵻�ֵ���� SDKErr_Success. Ҫ��ȡ��չ�Ĵ�����Ϣ����ο� SDKError enum.
	virtual SDKError LockMeeting() = 0;

	/// \���� ������ǰ����
	/// \���� ��������ɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ��򷵻�ֵ���� SDKErr_Success. Ҫ��ȡ��չ�Ĵ�����Ϣ����ο� SDKError enum.
	virtual SDKError UnlockMeeting() = 0;

	/// \���� ��ȡ��������״̬
	/// \���� ��ǰ��������״̬.
	virtual bool IsMeetingLocked() = 0;

	/// \���� ��ȡ������Ϣ
	/// ���� ��������ɹ�������ֵΪ������Ϣ������Ϊ��.
	virtual IMeetingInfo* GetMeetingInfo() = 0;

	/// \���� ��ȡ������������.
	/// \���� bSending i���Ϊ�棬�����ط���״̬�����򽫷��ؽ���״̬.
	/// \���� ��������ɹ����򷵻�ֵΪ ConnectionQuality enum .
	/// \����㲻�ڻ����У������� Conn_Quality_Unknow
	virtual ConnectionQuality GetSharingConnQuality(bool bSending = true) = 0;

	/// \���� �����Ƶ��������.
	/// \���� bSending ���Ϊ�棬�����ط���״̬�����򽫷��ؽ���״̬.
	/// \���� ��������ɹ����򷵻�ֵΪ ConnectionQuality enum.
	/// \����㲻�ڻ����У�������  Conn_Quality_Unknow
	virtual ConnectionQuality GetVideoConnQuality(bool bSending = true) = 0;

	/// \���� �����Ƶ����������
	/// \���� bSending ���Ϊ�棬�����ط���״̬�����򽫷��ؽ���״̬��
	/// \���� ��������ɹ����򷵻�ֵΪ ConnectionQuality enum.
	/// \����㲻�ڻ����У�������  Conn_Quality_Unknow
	virtual ConnectionQuality GetAudioConnQuality(bool bSending = true) = 0;

	/// \���� ��ȡ�������ýӿ�.
	/// \���� ��������ɹ�������ֵ�ǻ������ýӿ�.
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingConfiguration* GetMeetingConfiguration() = 0;

	/// \���� ��ȡ����UI������
	/// \���� ��������ɹ�������ֵ�ǻ���ui�������ӿ�
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingUIController* GetUIController() = 0;

	/// \���� Get annotation controller
	/// \���� ��������ɹ�������ֵ��annotation controller�ӿڡ�
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IAnnotationController* GetAnnotationController() = 0;

	/// \���� ��ȡ��Ƶ������
	/// \���� ��������ɹ�������ֵΪ��Ƶ�������ӿڡ�
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingVideoController* GetMeetingVideoController() = 0;

	/// \���� ��ȡԶ�̿���������
	/// \���� ��������ɹ�������ֵΪԶ�̿����������ָ�롣
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingRemoteController* GetMeetingRemoteController() = 0;

	/// \���� ��ȡ���������
	/// \���� ��������ɹ�������ֵΪ�������������ָ��
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingShareController* GetMeetingShareController() = 0;

	/// \���� ��ȡ��Ƶ������
	/// \���� ��������ɹ�������ֵ����Ƶ�������ӿڶ���ָ��
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingAudioController* GetMeetingAudioController() = 0;

	/// \���� ��ȡ¼�ƿ�����
	/// \���� ��������ɹ�������ֵ��¼�ƽӿ�
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingRecordingController* GetMeetingRecordingController() = 0;

	/// \���� ��ȡ���������
	/// \���� ��������ɹ�������ֵ������������ӿ�ָ�롣
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingChatController* GetMeetingChatController() = 0;

	/// \���� Get waiting room controller
	/// \���� If the function succeeds, the return value is audio controller interface.
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingWaitingRoomController* GetMeetingWaitingRoomController() = 0;

	/// \���� ��ȡH323��������ӿ�
	/// \���� ��������ɹ����򷵻�ֵ��H323��������ӿ�ָ��.
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingH323Helper* GetH323Helper() = 0;

	/// \���� ��ȡ�绰��������ӿ�
	/// \���� ��������ɹ����򷵻�ֵ�ǵ绰��������ӿ�
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingPhoneHelper* GetMeetingPhoneHelper() = 0;

	/// \���� ��ȡ��������������ӿ�
	/// \���� ��������ɹ����򷵻�ֵ�ǻ�������������ӿ�
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingBreakoutRoomsController* GetMeetingBreakoutRoomsController() = 0;

	/// \���� ��ȡ�λ��߿�����
	/// \���� ��������ɹ����򷵻�ֵ�ǲλ��߿������ӿ�.
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingParticipantsController* GetMeetingParticipantsController() = 0;

	/// \���� ��ȡʵʱ��������
	/// \���� ��������ɹ�������ֵΪʵʱ���������ӿڡ�
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingLiveStreamController* GetMeetingLiveStreamController() = 0;

	/// \���� ��ȡ�������ֻ������
	/// \���� ��������ɹ�������ֵΪwebinar�������ӿ�.
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IMeetingWebinarController* GetMeetingWebinarController() = 0;

	/// \���� ��ȡ�رյı���������ӿ�.
	/// \���� ��������ɹ�������ֵ��ָ��IMeetingWebinarController��ָ�롣���򷵻�NULL��.
	virtual IClosedCaptionController* GetMeetingClosedCaptionController() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif