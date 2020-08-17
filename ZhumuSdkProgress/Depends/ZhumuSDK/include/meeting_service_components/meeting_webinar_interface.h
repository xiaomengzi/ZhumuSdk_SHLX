/*!
* \文件：meeting_webinar_interface.h
* \描述：网络研讨会服务接口
*
*/

#ifndef ZHUMU_MEETING_WEBINAR_INTERFACE_H_
#define ZHUMU_MEETING_WEBINAR_INTERFACE_H_
/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/// \描述： 网络研讨会回调事件
///
class IMeetingWebinarCtrlEvent
{
public:
	/// \描述：将参与者更改为小组讨论者结果回调
	/// \参数：result 如果成功，则结果为零，否则为错误码
	virtual void onPromptAttendee2PanelistResult(int result) = 0;

	/// \描述：change panlist to attendee result callback
	/// \参数：result if success, result is zero, otherwise is the error code.
	virtual void onDepromptPanelist2AttendeeResult(int result) = 0;

	/// \描述：允许小组讨论者开始视频结果回调
	virtual void onAllowPanelistStartVideoNotification() = 0;

	/// \描述：禁止小组讨论者开始视频结果回调
	virtual void onDisallowPanelistStartVideoNotification() = 0;

	/// \描述：自己打开语音通知回调
	virtual void onSelfAllowTalkNotification() = 0;

	/// \描述：自己禁止语音通知回调
	virtual void onSelfDisallowTalkNotification() = 0;

	/// \描述：允许参会者聊天结果回调
	virtual void onAllowAttendeeChatNotification() = 0;

	/// \描述：禁止参会者聊天结果回调
	virtual void onDisallowAttendeeChatNotification() = 0;

	/// \描述：与会者音频状态通知回调
	/// \参数：userid 哪位与会者的声音状态改变了
	/// \参数：can_talk 能否说话
	/// \参数：is_muted 是否静音, 如果 can_talk 是 true, 能说话
	virtual void onAttendeeAudioStatusNotification(unsigned int userid, bool can_talk, bool is_muted) = 0;
};

/*! \struct tagWebinarMeetingStatus
\描述：网络研讨会聊天信息项
更详细的结构描述。
*/
typedef struct tagWebinarMeetingStatus
{
	bool allow_panellist_start_video;///< 小组成员可以开始视频或不可以
	bool allow_attendee_chat;///< 参会者是否可以聊天
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

/// \描述：网络研讨会控制器接口
///
class IMeetingWebinarController
{
public:
	/// \描述：设置会议网络控制器回调事件
	/// \参数：pEvent 一个指向IMeetingWebinarCtrlEvent*的指针，用于接收网络会议事件。 
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IMeetingWebinarCtrlEvent* pEvent) = 0;

	/// \描述：将参会者更改为小组讨论成员，只有会议主持人可以调用此api
	/// \参数：userid 指定要改变的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError PromptAttendee2Panelist(unsigned int userid) = 0;

	/// \描述：将小组讨论者更改为参会者，只有会议主机可以调用此api
	/// \参数：userid 指定要降级的用户
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError DepromptPanelist2Attendee(unsigned int userid) = 0;

	/// \描述：检查是否支持参会者说话
	/// \返回：如有支持允许与会者发言, 则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError IsSupportAttendeeTalk() = 0;

	/// \描述：允许参会者发言，只有会议主持人可以调用这个api
	/// \参数：userid 指定要允许的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError AllowAttendeeTalk(unsigned int userid) = 0;

	/// \描述：静止参会者发言，只有会议主持人可以调用这个api
	/// \参数：userid 指定要禁用的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError DisallowAttendeeTalk(unsigned int userid) = 0;

	/// \描述：允许小组讨论者启动视频，只有会议主持人可以调用这个api
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError AllowPanelistStartVideo() = 0;

	/// \描述：不允许小组讨论者启动视频，只有会议主持人可以调用此api
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError DisallowPanelistStartVideo() = 0;

	/// \描述：允许参会者聊天，只有会议主持人可以调用这个api
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError AllowAttendeeChat() = 0;

	/// \描述：不允许参会者聊天，只有会议主持人可以调用这个api
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError DisallowAttendeeChat() = 0;

	/// \描述：获取网络研讨会状态。
	/// \返回：网络研讨会状态。
	virtual WebinarMeetingStatus* GetWebinarMeetingStatus() = 0;
};

END_ZHUMU_SDK_NAMESPACE
#endif