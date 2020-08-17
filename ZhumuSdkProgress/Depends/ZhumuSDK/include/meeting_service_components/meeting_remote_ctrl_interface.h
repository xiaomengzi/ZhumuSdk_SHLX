/*!
* \�ļ���meeting_remote_ctrl_interface.h
* \����������Զ�̿��Ʒ���ӿ�
* \֧��zhumu�����Զ���UI���
*/
#ifndef ZHUMU_MEETING_REMOTE_CTRL_INTERFACE_H_
#define ZHUMU_MEETING_REMOTE_CTRL_INTERFACE_H_
#include "..\zhumu_sdk_def.h"

/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum RemoteControlStatus
\������Զ�̿���״̬.
����ϸ�Ľṹ����
*/
enum RemoteControlStatus
{
	Remote_Control_None,
	Remote_Control_I_Can_Request_Control_Who,

	Remote_Control_I_Can_Control_Who_Begin,
	Remote_Control_I_Can_Control_Who_End,

	Remote_Control_I_Control_Who_Begin,
	Remote_Control_I_Control_Who_End,

	Remote_Control_Who_Control_Me,
	Remote_Control_I_Recv_Decline_Msg,
	Remote_Control_I_Recv_Request_Msg,
};

/// \����������Զ�̿��ƻص��¼�
///
class IMeetingRemoteCtrlEvent
{
public:
	/// \������Զ�̿���״̬֪ͨ�ص�
	/// \������status Զ�̿���״ֵ̬��
	/// \������userId Զ�̿����û�id��
	virtual void onRemoteControlStatus(RemoteControlStatus status, unsigned int userId) = 0;
};

/// \������ ����Զ�̿��ƽӿ�
///
class IMeetingRemoteController
{
public:
	/// \���������û���Զ�̿��ƻص��¼�
	/// \������pEvent һ��ָ�����Զ�̿����¼���IMeetingRemoteCtrlEvent*��ָ�롣
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IMeetingRemoteCtrlEvent* pEvent) = 0;

	/// \����������Ƿ����Զ�̿���
	/// \������userid ָ��Ҫ�����û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CanRequestControl(unsigned int userId) = 0;

	/// \����������Ƿ��п���Ȩ��
	/// \������userid ָ��Ҫ�����û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError IsHaveRemoteControlRight(unsigned int userId) = 0;

	/// \���������Զ�̿����˵�״̬
	/// \������userid ָ��Ҫ�����û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError IsInRemoteControllingStatus(unsigned int userId) = 0;

	/// \�������������Ȩ������ʼԶ�̿���ĳ��
	/// \������userid ָ��ҪԶ�̿��Ƶ��û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError EnterRemoteControllingStatus(unsigned int userId) = 0;

	/// \�������������Ȩ����ȡ��Զ�̿���ĳ��
	/// \������userid ָ��Ҫ�뿪���û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError LeaveRemoteControllingStatus(unsigned int userId) = 0;

	/// \�������������ң��
	/// \������userId ָ��ҪԶ�̿��Ƶ��û�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError RequestRemoteControl(unsigned int userId) = 0;

	/// \��������������Զ�̿���
	/// \������userId ָ��Ҫ����Զ�̿���Ȩ���û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError GiveupRemoteControl(unsigned int userId) = 0;

	/// \������������Զ��ң��Ȩ���������λ���
	/// \������userId ָ��Ҫ������Ļ���û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError GiveRemoteControlTo(unsigned int userId) = 0;

	/// \�������ܾ�Զ�̿���Ҫ��
	/// \������userId ָ����Щ�û����ܿ�����Ļ
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError DeclineRemoteControlRequest(unsigned int userId) = 0;

	/// \������������ǰԶ�̿����ߵ�Ȩ��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError RevokeRemoteControl() = 0;

	/// \��������ȡ���鵱ǰԶ�̿�����
	/// \������userId �洢��ǰԶ�̿��Ƶ��û�id�����Ϊ�㣬���ʾ���ڻ���û��Զ�̿����ߡ�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError GetCurrentRemoteController(unsigned int& userId) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif