/*!
* \�ļ� meeting_breakout_rooms_interface.h
* \������ BreakoutRooms of Meeting Service Interface
*
*/
#ifndef ZHUMU_MEETING_BreakoutRooms_INTERFACE_H_
#define ZHUMU_MEETING_BreakoutRooms_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include <vector>
/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
class IBreakoutRoomsInfo
{
public:
	virtual ~IBreakoutRoomsInfo() {};
	/// \��������ȡ�ֻ᳡ID
	/// \���أ���������ɹ����򷵻�ֵΪ�ֻ᳡ID
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual const wchar_t* GetBID() = 0;

	/// \������ Get Breakout Room name
	/// \���أ���������ɹ����򷵻�ֵ�Ƿֻ᳡���ơ�
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual const wchar_t* GetBreakoutRoomName() = 0;
};

class IMeetingBreakoutRoomsEvent
{
public:
	//////////////////Callback for ATTENDEES///////////////////
	//���ռ���BO����

	/// \�������ֻ᳡��ʼ�ص�
	/// \������stBID ָ���ֻ᳡id��
	virtual void OnBreakoutRoomsStartedNotification(const wchar_t* stBID) = 0;
};

/// \�������ֻ᳡����ӿ�
///
class IMeetingBreakoutRoomsController
{
public:
	/// \����������IBreakoutRoomsEvent֪ͨ�Ĵ������
	/// \������pEvent �����յ�����Ϣ����ʱ����������
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IMeetingBreakoutRoomsEvent* pEvent) = 0;

	/// \����������ֻ᳡
	/// \������stBID ָ���ֻ᳡id��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \������zhumu�����û�����ģʽ
	virtual SDKError JoinBreakoutRoom(const wchar_t* stBID) = 0;

	/// \�������뿪�ֻ᳡
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \������zhumu�����û�����ģʽ
	virtual SDKError LeaveBreakoutRoom() = 0;

	/// \��������ȡ���Լ���Ļ������б�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \������zhumu�����û�����ģʽ
	virtual std::vector<IBreakoutRoomsInfo* > GetBreakoutRoomsInfoList() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif