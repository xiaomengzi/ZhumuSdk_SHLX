/*!
* \�ļ���meeting_waiting_room_interface.h
* \����������Ⱥ��ҷ���ӿ�
* \�������� zhumu ����UI
*/
#ifndef ZHUMU_MEETING_WaitingRoom_INTERFACE_H_
#define ZHUMU_MEETING_WaitingRoom_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include "meeting_participants_ctrl_interface.h"
#include <vector>
/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/// \�����������һص��¼�
///
class IMeetingWaitingRoomEvent
{
public:
	/// \�������û����������֪ͨ�ص�
	/// \������userID ��������ҵ��û�ID.
	virtual void onWatingRoomUserJoin(unsigned int userID) = 0;

	/// \�������û��뿪������֪ͨ�ص�
	/// \������userID �뿪�����ҵ��û�ID
	virtual void onWatingRoomUserLeft(unsigned int userID) = 0;

};
/// \�����������ҿ������ӿ�
///
class IMeetingWaitingRoomController
{
public:
	/// \���������û����һؽ��¼�
	/// \������pEvent һ��ָ��IMeetingWaitingRoomEvent*��ָ�룬��ָ����ջ������¼���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IMeetingWaitingRoomEvent* pEvent) = 0;

	/// \��������ǰ�����Ƿ�֧�ֵȺ��ҡ�
	/// \���أ�true, ֧�ֵȺ��ҡ�
	virtual bool IsSupportWaitingRoom() = 0;

	/// \��������ǰ�����Ƿ��ܽ��λ��˷���Ⱥ򷿼��״̬
	/// \���أ�true, ��.
	virtual bool IsWaitingRoomOnEntryFlagOn() = 0;

	/// \���������õ�ǰ�����Ƿ��ܽ��λ��˷���Ⱥ򷿼��״̬
	/// \������bEnable �����û����õȺ��ҡ�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError EnableWaitingRoomOnEntry(bool bEnable) = 0;

	/// \��������ȡ�ڵȺ����еĲλ�������
	/// \���أ�����ֵΪ��ǰ�������еȺ��Ҳ������б�������ڻ����У�����NULL��
	virtual std::vector<unsigned int > GetWaitingRoomLst() = 0;

	/// \������ͨ���û�id��ȡ�Ⱥ����û���Ϣ
	/// \������userId ָ��Ҫ��ȡ���û���Ϣ��
	/// \���أ���������ɹ����򷵻�ֵΪIUserInfo
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual IUserInfo* GetWaitingRoomUserInfoByID(unsigned int userid) = 0;

	/// \�����������û��μӻ���
	/// \������userId ָ��Ҫ������û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError AdmitToMeeting(unsigned int userid) = 0;

	/// \���������û��ŵ��Ⱥ���
	/// \������userId ָ��Ҫ�����ĸ��û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError PutInWaitingRoom(unsigned int userid) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif