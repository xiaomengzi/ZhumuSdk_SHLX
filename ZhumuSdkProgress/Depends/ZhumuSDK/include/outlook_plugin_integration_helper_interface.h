/*!
* \�ļ� outlook_plugin_integration_helper_interface.h
* \���� Outlook������ɰ����ӿڡ�
*
*/
#ifndef ZHUMU_OUTLOOK_PLUGIN_INTEGRATION_HELPER_INTERFACE_H_
#define ZHUMU_OUTLOOK_PLUGIN_INTEGRATION_HELPER_INTERFACE_H_
#include "zhumu_sdk_def.h"
/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/// \������ Outlook������ɻص��¼�
///
class IOutlookPluginIntegrationHelperEvent
{
public:
	/// \������ outlook��������¼֪ͨ
	virtual void onOutlookPluginNeedLoginRequestNotification() = 0;

	/// \������ outlook��������ճ̻���֪ͨ
	virtual void onOutlookPluginScheduleMeetingRequestNotification() = 0;

	/// \������ outlook�������Ĭ�ϵĻ�������֪ͨ
	/// \������ pScheduleForEmail �����ʼ���ʱ���
	/// \������ ppDefaultMeetingTopic ����������Ĭ�ϻ������⣬����Ĵ�ֵ
	virtual void onOutlookPluginDefaultMeetingTopicRequestNotification(const wchar_t* pScheduleForEmail, wchar_t** ppDefaultMeetingTopic) = 0;
};

/// \������Outlook������ɰ����ӿ�
///
class IOutlookPluginIntegrationHelper
{
public:
	/// \����������Outlook������ɻص��¼�
	/// \������pEvent һ��ָ��IOutlookPluginIntegrationHelperEvent*��ָ�룬��ָ�����outlook����¼���
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IOutlookPluginIntegrationHelperEvent* pEvent) = 0;

	// \������ ��ʼoutlook���
	/// \������ipc_channel_name IPCͨ��, Ĭ��ʹ��zhumu outlook���ipcͨ������������ϵ����
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// ����Ҫ��onAuthenticationReturn���سɹ�״̬����ô�api��
	virtual SDKError Start(const wchar_t* ipc_channel_name = NULL) = 0;

	// \������ ֹͣoutlook���
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// ����Ҫ��onAuthenticationReturn���سɹ�״̬����ô�api��
	virtual SDKError Stop() = 0;
};

END_ZHUMU_SDK_NAMESPACE
#endif