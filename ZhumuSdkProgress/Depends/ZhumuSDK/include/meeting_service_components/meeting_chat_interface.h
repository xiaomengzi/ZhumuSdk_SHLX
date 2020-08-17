/*!
* \file meeting_chat_interface.h
* \描述：会议聊天服务接口
* \支持zhumu和自定义用户界面模式
*/
#ifndef ZHUMU_MEETING_CHAT_INTERFACE_H_
#define ZHUMU_MEETING_CHAT_INTERFACE_H_
#include "..\zhumu_sdk_def.h"

/// \描述：Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/// \描述：聊天消息接口
///
class IChatMsgInfo
{
public:
	/// \描述：获取发送者用户ID
	/// \返回：如果函数成功，返回的值是发送者用户id.
	/// 如果函数失败，则返回值为-1.
	virtual unsigned int GetSenderUserId() = 0;

	/// \描述：获取发送者的名字
	/// \返回：如果函数成功，则返回发送人的名字。
	/// 如果函数失败，则返回值为NULL.
	virtual const wchar_t* GetSenderDisplayName() = 0;

	/// \描述: 获取接收方用户id
	/// \返回：如果函数成功，则返回值为接收者用户id。
	/// 如果返回值为0，则将此消息是发送给所有人的消息
	/// 如果函数调用失败，则返回值为-1.
	virtual unsigned int GetReceiverUserId() = 0;

	/// \描述：获取接收方用户名
	/// \返回：如果函数成功，则返回值为接收者用户名。
	/// 如果函数失败，返回值为NULL.
	virtual const wchar_t* GetReceiverDisplayName() = 0;

	/// \描述：获取聊天消息内容
	/// \返回: 如果函数成功，则返回聊天消息内容
	/// 如果函数失败，返回值为NULL。
	virtual const wchar_t* GetContent() = 0;

	/// \描述：获取聊天消息的时间戳
	/// \返回：如果函数成功，则返回聊天消息时间戳。
	virtual time_t GetTimeStamp() = 0;

	/// \描述：判断是否是发送给所有人的消息
	/// \返回：如果是true则是发送给所有人的消息，
	/// 如果是false则不是
	virtual bool IsChatToAll() = 0;

	/// \描述：判断是否是发送给讨论小组的所有人的消息
	/// \返回：如果是true, 是发送给讨论小组的所有人的消息, 否则不是
	virtual bool IsChatToAllPanelist() = 0;

	virtual ~IChatMsgInfo() {};
};

/*! \struct tagNormalMeetingChatStaus
\描述：正常会议的聊天状态
更详细的结构描述。
*/
typedef struct tagNormalMeetingChatStaus
{
	bool can_chat_to_all;///< 是否能和所有人聊天
	bool can_chat_to_individual;///< 是否能发起单聊
	bool is_only_can_chat_to_host;///< 是否只能和主持人聊天
}NormalMeetingChatStaus;

/*! \struct tagWebinarAttendeeChatStatus
\描述：网络研讨会参会人聊天状态,仅适用于网络研讨会
更详细的结构描述。
*/
typedef struct tagWebinarAttendeeChatStatus
{
	bool can_chat;///< 是否能开起聊天
	bool can_chat_to_all_panellist_and_attendee;///< 是否可以与所有的小组成员和参会者聊天
	bool can_chat_to_all_panellist;///< 是否可以和所有的小组成员聊天
}WebinarAttendeeChatStatus;

/*! \struct tagWebinarOtherUserRoleChatStatus
\描述：网络研讨会的聊天状态，仅用于网络研讨会的主持人/联席主持人/小组成员
更详细的结构描述。
*/
typedef struct tagWebinarOtherUserRoleChatStatus
{
	bool can_chat_to_all_panellist;///< 是否可以和所有的小组成员聊天
	bool can_chat_to_all_panellist_and_attendee;///< 是否可以和所有的小组成员和参会者聊天
	bool can_chat_to_individual;///< 是否可以发起单聊
}WebinarOtherUserRoleChatStatus;

/*! \struct tagChatStatus
\描述：当前会议的聊天状态
更详细的结构描述。
*/
typedef struct tagChatStatus
{
	union
	{
		NormalMeetingChatStaus normal_meeting_status;///< 如果is_webinar_meeting为false，则可用。参考 tagNormalMeetingChatStaus
		WebinarAttendeeChatStatus webinar_attendee_status;///< 如果is_webinar_meeting为真，is_webinar_attendee为真，则可用。参考 tagWebinarAttendeeChatStatus
		WebinarOtherUserRoleChatStatus webinar_other_status;///< 如果is_webinar_meeting为真，is_webinar_attendee为假，则可用。参考 tagWebinarOtherUserRoleChatStatus
	}ut;
	bool is_chat_off;///< 是否关闭当前会议的聊天
	bool is_webinar_attendee;///< 是否是网络研讨会参会人角色
	bool is_webinar_meeting;///< 是否是网络研讨会

	tagChatStatus()
	{
		Reset();
	}

	void Reset()
	{
		memset(this, 0, sizeof(tagChatStatus));
	}
}ChatStatus;

/// \描述：会议聊天回调事件
///
class IMeetingChatCtrlEvent
{
public:
	/// \描述：聊天消息回调事件
	/// \参数：chatMsg 消息对象. 此参数在此函数调用结束后无效.
	/// \参数：content json格式的聊天消息，保留.
	virtual void onChatMsgNotifcation(IChatMsgInfo* chatMsg, const wchar_t* content = NULL) = 0;

	/// \描述：聊天状态改变通知回调
	/// \参数：status_ 聊天状态对象.  此参数在此函数调用结束后无效.
	virtual void onChatStautsChangedNotification(ChatStatus* status_) = 0;
};

/*! \enum WebinarChatMsgType
\描述：网络研讨会聊天消息类型.
更详细的结构描述。
*/
enum WebinarChatMsgType
{
	WebinarChatMsgType_None,///< None
	WebinarChatMsgType_ToAllPanelist,///< 发送消息给所有小组成员
	WebinarChatMsgType_ToAllPanelistAndAttendee,///< 发送聊天消息给所有的小组成员和参会者
	WebinarChatMsgType_ToIndividualUser,///< 发送消息给单个用户
};

/*! \struct tagSendChatItem4Webinar
\描述：网络研讨会信息项
更详细的结构描述。
*/
typedef struct tagSendChatItem4Webinar
{
	WebinarChatMsgType msgType;///< 聊天消息类型
	const wchar_t* content;///< 消息内容
	unsigned int userID;///< 发送消息的对象,如果msgType是WebinarChatMsgType_ToIndividualUser时可用
	tagSendChatItem4Webinar()
	{
		msgType = WebinarChatMsgType_None;
		content = NULL;
		userID = -1;
	}
}SendChatItem4Webinar;

/// \描述：会议聊天控制器接口
///
class IMeetingChatController
{
public:
	/// \描述：设置会议聊天回调事件
	/// \参数：pEvent 一个指向接收聊天事件的IMeetingChatCtrlEvent*的指针。 
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IMeetingChatCtrlEvent* pEvent) = 0;

	/// \描述：发送聊天消息给某人或所有人
	/// \参数：receiver 聊天消息接收者。如果此参数为零，则将此消息发送给所有人
	/// \参数：content 聊天消息内容。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SendChatTo(unsigned int receiver, wchar_t* content) = 0;

	/// \描述：网络研讨会发送聊天消息给某人或所有人
	/// \参数：chatIteam 聊天消息项。参考SendChatItem4Webinar
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SendChat4WebinarMeeting(SendChatItem4Webinar& chatItem) = 0;

	/// \描述：获取当前聊天会话的特权状态
	/// \返回：如果函数成功，则返回值为聊天会话的状态.
	/// 如果函数失败，返回值是NULL。要获取扩展的错误信息，请参考ChatStatus。
	virtual const ChatStatus GetChatStatus() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif