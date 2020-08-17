/*!
* \�ļ���meeting_video_interface.h
* \������������Ƶ����ӿ�
*
*/
#ifndef ZHUMU_MEETING_VIDEO_INTERFACE_H_
#define ZHUMU_MEETING_VIDEO_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include "..\zhumu_sdk_util_define.h"
/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
enum VideoStatus
{
	Video_ON,
	Video_OFF,
};

class IRequestStartVideoHandler
{
public:
	virtual ~IRequestStartVideoHandler() {};

	virtual unsigned int GetReqFromUserId() = 0;
	virtual SDKError Ignore() = 0;
	virtual SDKError Accept() = 0;
	virtual SDKError Cancel() = 0;
};

/// \������������Ƶ�������ص��¼�
///
class IMeetingVideoCtrlEvent
{
public:
	/// \�������û�����Ƶ״̬�仯�ص�
	/// \������userId 
	/// \������status
	virtual void onUserVideoStatusChange(unsigned int userId, VideoStatus status) = 0;

	/// \������������Ƶ�仯�ص�
	/// \������userId 
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid) = 0;

	/// \����������������ʼ��Ƶ�ص�
	/// \������handler_
	virtual void onHostRequestStartVideo(IRequestStartVideoHandler* handler_) = 0;

	/// \��������Ƶ��߱仯�ص�
	/// \������userId 
	virtual void onActiveSpeakerVideoUserChanged(unsigned int userid) = 0;

	/// \��������Ƶ��߱仯�ص�
	/// \������userId 
	virtual void onActiveVideoUserChanged(unsigned int userid) = 0;
};

/// \������������Ƶ�������ӿ�
///
class IMeetingVideoController
{
public:
	/// \���������û�����Ƶ�������ص��¼�
	/// \������pEvent һ��ָ��IMeetingVideoCtrlEvent*�Ľ�����Ƶ�¼���ָ�롣
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IMeetingVideoCtrlEvent* pEvent) = 0;

	/// \������������Ƶ
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���Ui���
	virtual SDKError MuteVideo() = 0;

	/// \������ȡ��������Ƶ
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���Ui���
	virtual SDKError UnmuteVideo() = 0;

	/// \�������̶��򲻹̶���Ƶ
	/// \������bPin �̶��򲻹̶���Ƶ
	/// \������bFirstView ��һ����Ļ�򲻹̶�����Ƶ.
	/// \������userid ָ��Ҫ�̶��ĸ��û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��֧��zhumu UI���
	virtual SDKError PinVideo(bool bPin, bool bFirstView, unsigned int userid) = 0;

	/// \������������Ƶ
	/// \������bSpotlight ������Ƶ
	/// \������userid ָ��Ҫ������Ƶ��ʾ���û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���Ui���
	virtual SDKError SpotlightVideo(bool bSpotlight, unsigned int userid) = 0;

	/// \���������ػ���ʾû����Ƶ�û�����Ƶǽģʽ
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��֧��zhumu UI���
	virtual SDKError HideOrShowNoVideoUserOnVideoWall(bool bHide) = 0;

	/// \����������Ƿ���Ҫ��λ��ߴ���Ƶ
	/// \������userid ָ��Ҫ�����û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���Ui���
	virtual SDKError CanAskAttendeeToStartVideo(unsigned int userid) = 0;

	/// \������Ҫ��λ��ߴ���Ƶ
	/// \������userid ָ��Ҫ����û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���Ui���
	virtual SDKError AskAttendeeToStartVideo(unsigned int userid) = 0;

	/// \����������Ƿ���ֹͣ�λ��ߵ���Ƶ
	/// \������userid Specifies which user you want to check.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���Ui���
	virtual SDKError CanStopAttendeeVideo(unsigned int userid) = 0;

	/// \������ֹͣ�λ��ߵ���Ƶ
	/// \������userid ָ��Ҫֹͣ���û�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���Ui���
	virtual SDKError StopAttendeeVideo(unsigned int userid) = 0;

	virtual ICameraController* GetMyCameraController() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif