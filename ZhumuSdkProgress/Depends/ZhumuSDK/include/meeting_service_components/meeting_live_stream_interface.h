/*!
* \�ļ���meeting_sharing_interface.h
* \���������鹲�����ӿ�
*
*/
#ifndef ZHUMU_MEETING_LIVE_STREAM_INTERFACE_H_
#define ZHUMU_MEETING_LIVE_STREAM_INTERFACE_H_
#include "..\zhumu_sdk_def.h"

/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE

/*! \enum LiveStreamStatus
\������ֱ��״̬
����ϸ�Ľṹ������
*/
enum LiveStreamStatus
{
	LiveStreamStatus_None,///< None
	LiveStreamStatus_InProgress,///< ���ڽ���
	LiveStreamStatus_Connecting,///< ������
	LiveStreamStatus_Start_Failed_Timeout,///< ���ӳ�ʱ
	LiveStreamStatus_Start_Failed,///< ����ʧ��
	LiveStreamStatus_Ended,///< ����
};

/// \����������ֱ�����������ص��¼�
///
class IMeetingLiveStreamCtrlEvent
{
public:
	/// \������ֱ��״̬�ı�ص�
	/// \������status ״̬��
	virtual void onLiveStreamStatusChange(LiveStreamStatus status) = 0;
};

/// \��������ǰ�����ֱ����Ŀ
///
class IMeetingLiveStreamItem
{
public:
	/// \��������ȡֱ����url
	/// \���أ���������ɹ�������ֵ��ֱ����url��
	virtual const wchar_t* GetLiveStreamURL() = 0;

	/// \��������ȡֱ��������
	/// \���أ���������ɹ����򷵻�ֱ����������
	virtual const wchar_t* GetLiveStreamURLDescription() = 0;
	virtual ~IMeetingLiveStreamItem() {};
};

/// \����������ֱ���������ӿ�
///
class IMeetingLiveStreamController
{
public:
	/// \���������û���ֱ���ص��¼�
	/// \������pEvent һ��ָ��IMeetingLiveStreamCtrlEvent*��ָ�룬��ָ�����ʵʱ���¼���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IMeetingLiveStreamCtrlEvent* pEvent) = 0;

	/// \����������Ƿ��������ֱ��
	/// \���أ������������ֱ��������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CanStartLiveStream() = 0;

	/// \����������ֱ��
	/// \������item_ ָ�� IMeetingLiveStreamController::GetSupportLiveStreamURL() API������IMeetingLiveStreamItemָ�롣
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError StartLiveStream(IMeetingLiveStreamItem* item_) = 0;

	/// \����������ֱ��
	/// \������streamingURL ֱ����URL
	/// \������streamingKey ֱ����key��
	/// \������broadcastURL ֱ���Ĺ㲥URL��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// �����Դӵ�����ֱ����������Щ����
	virtual SDKError StartLiveStreamWithSteamingURL(const wchar_t* streamingURL, const wchar_t* streamingKey, const wchar_t* broadcastURL) = 0;

	/// \������ֱֹͣ��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError StopLiveStream() = 0;

	/// \��������ȡ��ǰ����ֱ��ʹ�õ�URL�͹�����Ϣ�б�
	/// \���أ���������ɹ������ص�ֵ����Ҫ����ֱ���Ļ�����Ϣ��
	/// ����ʧ�ܣ�����ֵΪNULL��������Ϣ����μ�IMeetingLiveStreamItem
	virtual IList<IMeetingLiveStreamItem* >* GetSupportLiveStreamURL() = 0;

	/// \��������ȡ��ǰ�����ֱ��״̬��
	/// \���أ���������ɹ����򷵻ص�ǰ�����ֱ��״̬���鿴LiveStreamStatus��
	virtual LiveStreamStatus GetCurrentLiveStreamStatus() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif