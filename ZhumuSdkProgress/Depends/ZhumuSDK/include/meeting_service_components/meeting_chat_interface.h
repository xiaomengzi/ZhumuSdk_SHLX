/*!
* \file meeting_chat_interface.h
* \�����������������ӿ�
* \֧��zhumu���Զ����û�����ģʽ
*/
#ifndef ZHUMU_MEETING_CHAT_INTERFACE_H_
#define ZHUMU_MEETING_CHAT_INTERFACE_H_
#include "..\zhumu_sdk_def.h"

/// \������Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/// \������������Ϣ�ӿ�
///
class IChatMsgInfo
{
public:
	/// \��������ȡ�������û�ID
	/// \���أ���������ɹ������ص�ֵ�Ƿ������û�id.
	/// �������ʧ�ܣ��򷵻�ֵΪ-1.
	virtual unsigned int GetSenderUserId() = 0;

	/// \��������ȡ�����ߵ�����
	/// \���أ���������ɹ����򷵻ط����˵����֡�
	/// �������ʧ�ܣ��򷵻�ֵΪNULL.
	virtual const wchar_t* GetSenderDisplayName() = 0;

	/// \����: ��ȡ���շ��û�id
	/// \���أ���������ɹ����򷵻�ֵΪ�������û�id��
	/// �������ֵΪ0���򽫴���Ϣ�Ƿ��͸������˵���Ϣ
	/// �����������ʧ�ܣ��򷵻�ֵΪ-1.
	virtual unsigned int GetReceiverUserId() = 0;

	/// \��������ȡ���շ��û���
	/// \���أ���������ɹ����򷵻�ֵΪ�������û�����
	/// �������ʧ�ܣ�����ֵΪNULL.
	virtual const wchar_t* GetReceiverDisplayName() = 0;

	/// \��������ȡ������Ϣ����
	/// \����: ��������ɹ����򷵻�������Ϣ����
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual const wchar_t* GetContent() = 0;

	/// \��������ȡ������Ϣ��ʱ���
	/// \���أ���������ɹ����򷵻�������Ϣʱ�����
	virtual time_t GetTimeStamp() = 0;

	/// \�������ж��Ƿ��Ƿ��͸������˵���Ϣ
	/// \���أ������true���Ƿ��͸������˵���Ϣ��
	/// �����false����
	virtual bool IsChatToAll() = 0;

	/// \�������ж��Ƿ��Ƿ��͸�����С��������˵���Ϣ
	/// \���أ������true, �Ƿ��͸�����С��������˵���Ϣ, ������
	virtual bool IsChatToAllPanelist() = 0;

	virtual ~IChatMsgInfo() {};
};

/*! \struct tagNormalMeetingChatStaus
\�������������������״̬
����ϸ�Ľṹ������
*/
typedef struct tagNormalMeetingChatStaus
{
	bool can_chat_to_all;///< �Ƿ��ܺ�����������
	bool can_chat_to_individual;///< �Ƿ��ܷ�����
	bool is_only_can_chat_to_host;///< �Ƿ�ֻ�ܺ�����������
}NormalMeetingChatStaus;

/*! \struct tagWebinarAttendeeChatStatus
\�������������ֻ�λ�������״̬,���������������ֻ�
����ϸ�Ľṹ������
*/
typedef struct tagWebinarAttendeeChatStatus
{
	bool can_chat;///< �Ƿ��ܿ�������
	bool can_chat_to_all_panellist_and_attendee;///< �Ƿ���������е�С���Ա�Ͳλ�������
	bool can_chat_to_all_panellist;///< �Ƿ���Ժ����е�С���Ա����
}WebinarAttendeeChatStatus;

/*! \struct tagWebinarOtherUserRoleChatStatus
\�������������ֻ������״̬���������������ֻ��������/��ϯ������/С���Ա
����ϸ�Ľṹ������
*/
typedef struct tagWebinarOtherUserRoleChatStatus
{
	bool can_chat_to_all_panellist;///< �Ƿ���Ժ����е�С���Ա����
	bool can_chat_to_all_panellist_and_attendee;///< �Ƿ���Ժ����е�С���Ա�Ͳλ�������
	bool can_chat_to_individual;///< �Ƿ���Է�����
}WebinarOtherUserRoleChatStatus;

/*! \struct tagChatStatus
\��������ǰ���������״̬
����ϸ�Ľṹ������
*/
typedef struct tagChatStatus
{
	union
	{
		NormalMeetingChatStaus normal_meeting_status;///< ���is_webinar_meetingΪfalse������á��ο� tagNormalMeetingChatStaus
		WebinarAttendeeChatStatus webinar_attendee_status;///< ���is_webinar_meetingΪ�棬is_webinar_attendeeΪ�棬����á��ο� tagWebinarAttendeeChatStatus
		WebinarOtherUserRoleChatStatus webinar_other_status;///< ���is_webinar_meetingΪ�棬is_webinar_attendeeΪ�٣�����á��ο� tagWebinarOtherUserRoleChatStatus
	}ut;
	bool is_chat_off;///< �Ƿ�رյ�ǰ���������
	bool is_webinar_attendee;///< �Ƿ����������ֻ�λ��˽�ɫ
	bool is_webinar_meeting;///< �Ƿ����������ֻ�

	tagChatStatus()
	{
		Reset();
	}

	void Reset()
	{
		memset(this, 0, sizeof(tagChatStatus));
	}
}ChatStatus;

/// \��������������ص��¼�
///
class IMeetingChatCtrlEvent
{
public:
	/// \������������Ϣ�ص��¼�
	/// \������chatMsg ��Ϣ����. �˲����ڴ˺������ý�������Ч.
	/// \������content json��ʽ��������Ϣ������.
	virtual void onChatMsgNotifcation(IChatMsgInfo* chatMsg, const wchar_t* content = NULL) = 0;

	/// \����������״̬�ı�֪ͨ�ص�
	/// \������status_ ����״̬����.  �˲����ڴ˺������ý�������Ч.
	virtual void onChatStautsChangedNotification(ChatStatus* status_) = 0;
};

/*! \enum WebinarChatMsgType
\�������������ֻ�������Ϣ����.
����ϸ�Ľṹ������
*/
enum WebinarChatMsgType
{
	WebinarChatMsgType_None,///< None
	WebinarChatMsgType_ToAllPanelist,///< ������Ϣ������С���Ա
	WebinarChatMsgType_ToAllPanelistAndAttendee,///< ����������Ϣ�����е�С���Ա�Ͳλ���
	WebinarChatMsgType_ToIndividualUser,///< ������Ϣ�������û�
};

/*! \struct tagSendChatItem4Webinar
\�������������ֻ���Ϣ��
����ϸ�Ľṹ������
*/
typedef struct tagSendChatItem4Webinar
{
	WebinarChatMsgType msgType;///< ������Ϣ����
	const wchar_t* content;///< ��Ϣ����
	unsigned int userID;///< ������Ϣ�Ķ���,���msgType��WebinarChatMsgType_ToIndividualUserʱ����
	tagSendChatItem4Webinar()
	{
		msgType = WebinarChatMsgType_None;
		content = NULL;
		userID = -1;
	}
}SendChatItem4Webinar;

/// \��������������������ӿ�
///
class IMeetingChatController
{
public:
	/// \���������û�������ص��¼�
	/// \������pEvent һ��ָ����������¼���IMeetingChatCtrlEvent*��ָ�롣 
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IMeetingChatCtrlEvent* pEvent) = 0;

	/// \����������������Ϣ��ĳ�˻�������
	/// \������receiver ������Ϣ�����ߡ�����˲���Ϊ�㣬�򽫴���Ϣ���͸�������
	/// \������content ������Ϣ���ݡ�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SendChatTo(unsigned int receiver, wchar_t* content) = 0;

	/// \�������������ֻᷢ��������Ϣ��ĳ�˻�������
	/// \������chatIteam ������Ϣ��ο�SendChatItem4Webinar
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SendChat4WebinarMeeting(SendChatItem4Webinar& chatItem) = 0;

	/// \��������ȡ��ǰ����Ự����Ȩ״̬
	/// \���أ���������ɹ����򷵻�ֵΪ����Ự��״̬.
	/// �������ʧ�ܣ�����ֵ��NULL��Ҫ��ȡ��չ�Ĵ�����Ϣ����ο�ChatStatus��
	virtual const ChatStatus GetChatStatus() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif