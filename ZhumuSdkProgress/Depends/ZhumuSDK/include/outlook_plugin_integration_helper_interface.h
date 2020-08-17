/*!
* \文件 outlook_plugin_integration_helper_interface.h
* \描述 Outlook插件集成帮助接口。
*
*/
#ifndef ZHUMU_OUTLOOK_PLUGIN_INTEGRATION_HELPER_INTERFACE_H_
#define ZHUMU_OUTLOOK_PLUGIN_INTEGRATION_HELPER_INTERFACE_H_
#include "zhumu_sdk_def.h"
/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/// \描述： Outlook插件集成回调事件
///
class IOutlookPluginIntegrationHelperEvent
{
public:
	/// \描述： outlook插件请求登录通知
	virtual void onOutlookPluginNeedLoginRequestNotification() = 0;

	/// \描述： outlook插件请求日程会议通知
	virtual void onOutlookPluginScheduleMeetingRequestNotification() = 0;

	/// \描述： outlook插件请求默认的会议主题通知
	/// \参数： pScheduleForEmail 电子邮件的时间表
	/// \参数： ppDefaultMeetingTopic 如果您想更改默认会议主题，请更改此值
	virtual void onOutlookPluginDefaultMeetingTopicRequestNotification(const wchar_t* pScheduleForEmail, wchar_t** ppDefaultMeetingTopic) = 0;
};

/// \描述：Outlook插件集成帮助接口
///
class IOutlookPluginIntegrationHelper
{
public:
	/// \描述：设置Outlook插件集成回调事件
	/// \参数；pEvent 一个指向IOutlookPluginIntegrationHelperEvent*的指针，该指针接收outlook插件事件。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IOutlookPluginIntegrationHelperEvent* pEvent) = 0;

	// \描述： 开始outlook插件
	/// \参数：ipc_channel_name IPC通道, 默认使用zhumu outlook插件ipc通道，否则请联系我们
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// 您需要在onAuthenticationReturn返回成功状态后调用此api。
	virtual SDKError Start(const wchar_t* ipc_channel_name = NULL) = 0;

	// \描述： 停止outlook插件
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// 您需要在onAuthenticationReturn返回成功状态后调用此api。
	virtual SDKError Stop() = 0;
};

END_ZHUMU_SDK_NAMESPACE
#endif