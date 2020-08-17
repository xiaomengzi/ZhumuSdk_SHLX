/*!
* \�ļ� meeting_recording_interface.h
* \������ ����¼�Ʒ���ӿ�
* \֧��zhumu�����Զ���UI���
*/
#ifndef ZHUMU_MEETING_Recording_INTERFACE_H_
#define ZHUMU_MEETING_Recording_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include <time.h>

/// \������Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum RecordingStatus
\������¼��״̬.
����ϸ�Ľṹ����
*/
enum RecordingStatus
{
	Recording_Start,			 //��ʼ, ����&��¼�ƹ���
	Recording_Stop,				 //����, ����&��¼�ƹ���
	Recording_DiskFull,			 //����, ����&��¼�ƹ���
	Recording_Pause,			 //��ͣ, ����&��¼�ƹ���
	Recording_Connecting,		 //������, ����������¼��
};

class ICustomizedLocalRecordingLayoutHelper;
/// \������ Meeting recording callback event
///
class IMeetingRecordingCtrlEvent
{
public:
	/// \������һ��mp4ת����ɣ��˷��������ص�
	/// \������bsuccess �ɹ���ʧ��.
	/// \������iResult ʧ��ʱ����������ϸ��Ϣ.
	/// \������szPath ����ɹ��������ؼ�¼�ļ�·��������Ϊ��
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath) = 0;

	/// \������֪ͨmp4ת������
	/// \������iPercentage ת�����̵İٷֱȡ�
	virtual void onRecording2MP4Processing(int iPercentage) = 0;

	/// \�������Լ�¼��״̬֪ͨ�ص�
	/// \������status ¼��״̬
	virtual void onRecordingStatus(RecordingStatus status) = 0;

	/// \��������¼��״̬֪ͨ�ص�
	/// \������status ¼��״̬
	virtual void onCloudRecordingStatus(RecordingStatus status) = 0;

	/// \�������Լ�¼��Ȩ�޸ı�ص�
	/// \������bCanRec �ܷ�¼��
	virtual void onRecordPriviligeChanged(bool bCanRec) = 0;

	/// \�����������Զ���uiģʽ�ı���¼��Դ�ص�
	/// \������layout_helper ����¼�ƽӿ�.
	/// layout_helper���ڵ��ý������ͷţ����ڴ˵��ý���ǰ���в��֡�
	virtual void onCustomizedLocalRecordingSourceNotification(ICustomizedLocalRecordingLayoutHelper* layout_helper) = 0;
};

/// \������ ����¼�ƿ��ƽӿ�
///
class IMeetingRecordingController
{
public:
	/// \���������û���¼�ƿ����¼�
	/// \������pEvent һ��ָ��IMeetingRecordingCtrlEvent*��ָ�룬����¼���¼���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IMeetingRecordingCtrlEvent* pEvent) = 0;

	/// \��������ʼ¼��
	/// \������startTimestamp ��ʼ¼�Ƶ�ʱ���
	/// \������recPath ָ��¼�Ƶı���·��,���·��������,����SDKERR_INVALID_����:ETER ������롣
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError StartRecording(time_t& startTimestamp, wchar_t* recPath) = 0;

	/// \������ֹͣ¼��
	/// \������stopTimestamp ֹͣ¼��ʱ�����
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError StopRecording(time_t& stopTimestamp) = 0;

	/// \������ ����Ƿ���Կ�ʼ¼��
	/// \������ cloud_recording ��¼�ƻ��� 
	/// \������ userid ָ��Ҫ�����û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CanStartRecording(bool cloud_recording, unsigned int userid) = 0;

	/// \����������������������ڻ����е������λ��߿�ʼ����¼��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CanAllowDisAllowLocalRecording() = 0;

	/// \��������ʼ��¼��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError StartCloudRecording() = 0;

	/// \������ֹͣ��¼��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError StopCloudRecording() = 0;

	/// \����������Ƿ�֧�ֱ���¼�ƹ���
	/// \������userid ָ��Ҫ�����û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError IsSupportLocalRecording(unsigned int userid) = 0;

	/// \������ Allow to start local recoding
	/// \������ userid Specifies which user you want to allow.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError AllowLocalRecording(unsigned int userid) = 0;

	/// \������������ʼ����¼��
	/// \������userid ָ��Ҫ����¼�Ƶ��û���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError DisAllowLocalRecording(unsigned int userid) = 0;

	/// \�����������Զ��屾��¼��Դ֪ͨ
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// ���������Զ���UIģʽ
	virtual SDKError RequestCustomizedLocalRecordingSource() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif