/*!
* \�ļ���meeting_webinar_interface.h
* \�������������ֻ����ӿ�
*
*/

#ifndef ZHUMU_MEETING_WEBINAR_INTERFACE_H_
#define ZHUMU_MEETING_WEBINAR_INTERFACE_H_
/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/// \������ �������ֻ�ص��¼�
///
class IMeetingWebinarCtrlEvent
{
public:
	/// \�������������߸���ΪС�������߽���ص�
	/// \������result ����ɹ�������Ϊ�㣬����Ϊ������
	virtual void onPromptAttendee2PanelistResult(int result) = 0;

	/// \������change panlist to attendee result callback
	/// \������result if success, result is zero, otherwise is the error code.
	virtual void onDepromptPanelist2AttendeeResult(int result) = 0;

	/// \����������С�������߿�ʼ��Ƶ����ص�
	virtual void onAllowPanelistStartVideoNotification() = 0;

	/// \��������ֹС�������߿�ʼ��Ƶ����ص�
	virtual void onDisallowPanelistStartVideoNotification() = 0;

	/// \�������Լ�������֪ͨ�ص�
	virtual void onSelfAllowTalkNotification() = 0;

	/// \�������Լ���ֹ����֪ͨ�ص�
	virtual void onSelfDisallowTalkNotification() = 0;

	/// \����������λ����������ص�
	virtual void onAllowAttendeeChatNotification() = 0;

	/// \��������ֹ�λ����������ص�
	virtual void onDisallowAttendeeChatNotification() = 0;

	/// \�������������Ƶ״̬֪ͨ�ص�
	/// \������userid ��λ����ߵ�����״̬�ı���
	/// \������can_talk �ܷ�˵��
	/// \������is_muted �Ƿ���, ��� can_talk �� true, ��˵��
	virtual void onAttendeeAudioStatusNotification(unsigned int userid, bool can_talk, bool is_muted) = 0;
};

/*! \struct tagWebinarMeetingStatus
\�������������ֻ�������Ϣ��
����ϸ�Ľṹ������
*/
typedef struct tagWebinarMeetingStatus
{
	bool allow_panellist_start_video;///< С���Ա���Կ�ʼ��Ƶ�򲻿���
	bool allow_attendee_chat;///< �λ����Ƿ��������
	tagWebinarMeetingStatus()
	{
		Reset();
	}

	void Reset()
	{
		allow_panellist_start_video = false;
		allow_attendee_chat = false;
	}
}WebinarMeetingStatus;

/// \�������������ֻ�������ӿ�
///
class IMeetingWebinarController
{
public:
	/// \���������û�������������ص��¼�
	/// \������pEvent һ��ָ��IMeetingWebinarCtrlEvent*��ָ�룬���ڽ�����������¼��� 
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IMeetingWebinarCtrlEvent* pEvent) = 0;

	/// \���������λ��߸���ΪС�����۳�Ա��ֻ�л��������˿��Ե��ô�api
	/// \������userid ָ��Ҫ�ı���û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError PromptAttendee2Panelist(unsigned int userid) = 0;

	/// \��������С�������߸���Ϊ�λ��ߣ�ֻ�л����������Ե��ô�api
	/// \������userid ָ��Ҫ�������û�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError DepromptPanelist2Attendee(unsigned int userid) = 0;

	/// \����������Ƿ�֧�ֲλ���˵��
	/// \���أ�����֧����������߷���, �򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError IsSupportAttendeeTalk() = 0;

	/// \����������λ��߷��ԣ�ֻ�л��������˿��Ե������api
	/// \������userid ָ��Ҫ������û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError AllowAttendeeTalk(unsigned int userid) = 0;

	/// \��������ֹ�λ��߷��ԣ�ֻ�л��������˿��Ե������api
	/// \������userid ָ��Ҫ���õ��û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError DisallowAttendeeTalk(unsigned int userid) = 0;

	/// \����������С��������������Ƶ��ֻ�л��������˿��Ե������api
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError AllowPanelistStartVideo() = 0;

	/// \������������С��������������Ƶ��ֻ�л��������˿��Ե��ô�api
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError DisallowPanelistStartVideo() = 0;

	/// \����������λ������죬ֻ�л��������˿��Ե������api
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError AllowAttendeeChat() = 0;

	/// \������������λ������죬ֻ�л��������˿��Ե������api
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError DisallowAttendeeChat() = 0;

	/// \��������ȡ�������ֻ�״̬��
	/// \���أ��������ֻ�״̬��
	virtual WebinarMeetingStatus* GetWebinarMeetingStatus() = 0;
};

END_ZHUMU_SDK_NAMESPACE
#endif