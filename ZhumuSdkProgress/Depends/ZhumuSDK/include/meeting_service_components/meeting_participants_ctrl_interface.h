/*!
* \�ļ� meeting_participants_ctrl_interface.h
* \����������λ��߷���������ӿ�
*
*/
#ifndef ZHUMU_MEETING_ParticipantsCtrl_INTERFACE_H_
#define ZHUMU_MEETING_ParticipantsCtrl_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include "meeting_audio_interface.h"
#include <vector>
/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum UserRole
\�������û���ɫ.
����ϸ�Ľṹ������
*/
enum UserRole
{
	USERROLE_NONE,///< None
	USERROLE_HOST,///< ������
	USERROLE_COHOST,///< ��ϵ������
	USERROLE_PANELIST,///< �������Ա, ���������������ֻ�
	USERROLE_BREAKOUTROOM_MODERATOR,///< BO����������
	USERROLE_ATTENDEE,///< �λ���
};

/*! \struct tagWebinarAttendeeStatus
\���������ֻ�λ���״̬
����ϸ�Ľṹ������
*/
typedef struct tagWebinarAttendeeStatus
{
	bool allow_talk;///< �Ƿ�����˵��
	tagWebinarAttendeeStatus()
	{
		allow_talk = false;
	}
}WebinarAttendeeStatus;

/// \�������û���Ϣ�ӿ�
///
class IUserInfo
{
public:
	/// \����������û���
	/// \���أ���������ɹ����򷵻��û�����
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual const wchar_t* GetUserName() = 0;

	/// \�������Ƿ�Ϊ������
	/// \���أ��Ƿ�
	virtual bool IsHost() = 0;

	/// \��������ȡ�û�ID
	/// \���أ���������ɹ����򷵻�ֵΪ�û�ID��
	/// �������ʧ�ܣ�����ֵΪ0��
	virtual unsigned int GetUserID() = 0;

	/// \�������ж���Ƶ�ǿ��Ż��ǹ���
	/// \���أ��Ƿ�
	virtual bool IsVideoOn() = 0;

	/// \�������ж���Ƶ�Ǿ������ǷǾ���
	/// \���أ��Ƿ�
	virtual bool IsAudioMuted() = 0;

	/// \��������Ƶ����
	/// \���أ���Ƶ��������
	virtual ZHUMU_SDK_NAMESPACE::AudioType GetAudioJoinType() = 0;

	/// \�������Ƿ����Լ�
	/// \���أ��Ƿ�
	virtual bool IsMySelf() = 0;

	/// \�������Ƿ��ڵȴ�����
	/// \���أ��Ƿ�
	virtual bool IsInWaitingRoom() = 0;

	/// \�������Ƿ��ھ���
	/// \���أ��Ƿ�
	virtual bool IsRaiseHand() = 0;

	/// \��������ȡ�û���ɫ
	/// \���أ��û���ɫ
	virtual UserRole GetUserRole() = 0;

	/// \������ Is pure phone user or not
	/// \return Is pure phone user or not
	virtual bool IsPurePhoneUser() = 0;

	/// \��������ȡ��Ƶ������
	/// \���أ�����
	virtual int GetAudioVoiceLevel() = 0;

	/// \������ȷ����ǰ��Ϣ��Ӧ���û��Ƿ���������Ļ�ķ��ͷ���
	/// \���أ�TRUE ָʾ�û���������Ļ�ķ��ͷ���
	virtual bool IsClosedCaptionSender() = 0;
	
    /// \brief Determine whether the user specified by the current information is talking or not.
	/// \return TRUE indicates that the specified user is talking.
	virtual bool IsTalking() = 0;

	/// \��������ȡ��ǰ��Ϣָ�����û����������ֻ�״̬��
	/// \���أ�ָ���û���״̬���й���ϸ��Ϣ����μ� WebinarAttendeeStatus �ṹ��
	virtual WebinarAttendeeStatus* GetWebinarAttendeeStauts() = 0;

	virtual ~IUserInfo() {};
};

/// \������ ��������߿������ؽ��¼�
///
class IMeetingParticipantsCtrlEvent
{
public:
	/// \���������ڿ�����û���֪ͨ�ص��¼���
	/// \������lstUserID �û�ID���б� 
	/// \������strUserList json��ʽ���û��б��˹���Ŀǰ��Ч���ش˽���������
	virtual void onUserJoin(std::vector<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;

	/// \�������û��뿪����֪ͨ�Ļص��¼���
	/// \������lstUserID �뿪������û�ID�б�
	/// \������strUserList json��ʽ���û��б��˹���Ŀǰ��Ч���ش˽���������
	virtual void onUserLeft(std::vector<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;

	/// \�����������˸ı�ص�
	/// \������userId 
	virtual void onHostChangeNotification(unsigned int userId) = 0;

	/// \����������״̬�ı�ص�
	/// \������bLow �Ƿ����
	/// \������userid �����û�ID
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid) = 0;

	/// \�������û����ı�ص�
	/// \������userId �ı���û�ID
	/// \������userName �ı������
	virtual void onUserNameChanged(unsigned int userId, const wchar_t* userName) = 0;

	/// \��������ϯ�����˸ı�ص�
	/// \������userId �ı���û�ID
	/// \������isCoHost �Ƿ�����ϯ������
	virtual void onCoHostChangeNotification(unsigned int userId, bool isCoHost) = 0;
};

/// \����������λ��߷��������
///
class IMeetingParticipantsController
{
public:
	/// \���������ò����߿������ص��¼�
	/// \����: pEvent һ��ָ����ղ������¼���IParticipantsControllerEvent*��ָ�롣
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IMeetingParticipantsCtrlEvent* pEvent) = 0;

	/// \��������ȡ�������������
	/// \���أ�����ֵ�ǵ�ǰ��������в������б�������ڻ����У�����NULL��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual std::vector<unsigned int> GetParticipantsList() = 0;

	/// \������ͨ���û�id��ȡ�û���Ϣ
	/// \������userId ָ��Ҫ��ȡ���û���Ϣ�����Ϊ0�����ȡ��ǰ�û���Ϣ��
	/// \���أ���������ɹ����򷵻�ֵΪ�û���Ϣ�ӿڡ�
	/// �������ʧ�ܣ�����ֵΪNULL��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual IUserInfo* GetUserByUserID(unsigned int userid) = 0;

	/// \�������ڻ�����ȡ�����вλ��ߵľ���״̬��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError LowerAllHands() = 0;

	/// \�������ı��û��������������������û�������Ӧ���������˻���ϯ������
	/// \������userId ָ����Ҫ�����û������û�ID��
	/// \������userName ָ�����û�����
	/// \������bSaveUserName ָ���´βμӻ���ʱ�û�ʹ���ĸ����ơ�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError ChangeUserName(const unsigned int userid, const wchar_t* userName, bool bSaveUserName) = 0;

	/// \���������²λ��ߵľ���״̬
	/// \������userId ָ���ĸ��û��ķ��¾��֡�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError LowerHand(unsigned int userid) = 0;

	/// \�������ڻ����о���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError RaiseHand() = 0;

	/// \������ָ��������.
	/// \������userId ָ���ĸ��û���Ϊ�����ˡ�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError MakeHost(unsigned int userid) = 0;

	/// \����������ܷ���Ϊ��ϯ������ .
	/// \������userId ָ���ĸ��û�������Ϊ��ϯ�����ˡ�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError CanbeCohost(unsigned int userid) = 0;

	/// \������������ϯ֧����
	/// \������userId Specifies which the user to be the co-host.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError AssignCoHost(unsigned int userid) = 0;

	/// \������������ϯ������.
	/// \������userId ָ����Ҫ��������ϯ������ID.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError RevokeCoHost(unsigned int userid) = 0;

	/// \�������Ƴ��û�
	/// \������userId ָ��Ҫ�Ƴ����û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError ExpelUser(unsigned int userid) = 0;

	/// \����������������.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��֧��zhumu�����û�����ģʽ
	virtual SDKError ReclaimHost() = 0;

	/// \����������Ƿ��ܻ���������
	/// \������bCanReclaimHost �ܷ��ܻ���������Ȩ�ޡ�.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError CanReclaimHost(bool& bCanReclaimHost) = 0;

	/// \������ ͨ����Կ����������.
	/// \������host_key ������ key.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ�������û�����ģʽ
	virtual SDKError ReclaimHostByHostKey(const wchar_t* host_key) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif