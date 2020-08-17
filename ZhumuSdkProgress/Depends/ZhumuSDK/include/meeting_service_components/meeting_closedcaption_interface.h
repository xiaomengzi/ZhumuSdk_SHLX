/*!
* \文件：meeting_claosecaptioin_interface.h
* \描述： Meeting Service Closed Caption Interface.
* \注意：适用于zhumu风格和用户自定义界面模式.
*/
#ifndef _MEETING_CLOSEDCAPTION_INTERFACE_H_
#define _MEETING_CLOSEDCAPTION_INTERFACE_H_
#include "..\zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
/// \描述：隐藏字幕控制器回调事件。
///
class IClosedCaptionControllerEvent
{
public:
	/// \描述：指定用户发送隐藏字幕消息时的回调事件。
	virtual void onAssignedToSendCC(bool bAssigned) = 0;
	/// \描述：用户接收到隐藏字幕消息时的回调事件。
	virtual void onClosedCaptionMsgReceived(const wchar_t* ccMsg, time_t time) = 0;
};


class IClosedCaptionController
{
public:
	/// 设置隐藏字幕(CC)的控制器事件
	virtual SDKError SetEvent(IClosedCaptionControllerEvent* pEvent) = 0;
	/// 确定当前会议是否支持CC功能。
	virtual bool IsMeetingSupportCC() = 0;
	/// ：查询是否能够指定他人发送CC。
	virtual bool CanAssignOthersToSendCC() = 0;
	/// 指定一个用户发送CC。
	/// Zero(0)表示自己分配当前用户
	virtual SDKError AssignCCPriviledge(unsigned int userid, bool bAssigned) = 0;
	/// 确定是否可以将该用户指定为CC发送方。
	virtual bool CanBeAssignedToSendCC(unsigned int userid) = 0;
	/// 查询用户是否可以发送CC。
	virtual bool CanSendClosedCaption() = 0;
	/// 发送CC消息。
	virtual SDKError SendClosedCaption(const wchar_t* ccMsg) = 0;
	/// 确定是否能保存CC
	virtual bool IsSaveCCEnabled() = 0;
	/// 保存CC历史。
	virtual SDKError SaveCCHistory() = 0;
	/// 获取保存CC的路径。
	virtual const wchar_t* GetClosedCaptionHistorySavedPath() = 0;
	/// 获取第三方服务使用的CC URL。
	virtual const wchar_t* GetClosedCaptionUrlFor3rdParty() = 0;
};

END_ZHUMU_SDK_NAMESPACE
#endif