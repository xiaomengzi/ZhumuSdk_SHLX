/*!
* \文件：meeting_waiting_room_interface.h
* \描述：会议等候室服务接口
* \仅适用于 zhumu 风格的UI
*/
#ifndef ZHUMU_MEETING_WaitingRoom_INTERFACE_H_
#define ZHUMU_MEETING_WaitingRoom_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include "meeting_participants_ctrl_interface.h"
#include <vector>
/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/// \描述：会议室回调事件
///
class IMeetingWaitingRoomEvent
{
public:
	/// \描述：用户加入会议室通知回调
	/// \参数：userID 接入会议室的用户ID.
	virtual void onWatingRoomUserJoin(unsigned int userID) = 0;

	/// \描述：用户离开会议室通知回调
	/// \参数：userID 离开会议室的用户ID
	virtual void onWatingRoomUserLeft(unsigned int userID) = 0;

};
/// \描述：会议室控制器接口
///
class IMeetingWaitingRoomController
{
public:
	/// \描述：设置会议室回叫事件
	/// \参数：pEvent 一个指向IMeetingWaitingRoomEvent*的指针，该指针接收会议室事件。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IMeetingWaitingRoomEvent* pEvent) = 0;

	/// \描述：当前会议是否支持等候室。
	/// \返回：true, 支持等候室。
	virtual bool IsSupportWaitingRoom() = 0;

	/// \描述：当前会议是否能将参会人放入等候房间的状态
	/// \返回：true, 能.
	virtual bool IsWaitingRoomOnEntryFlagOn() = 0;

	/// \描述：设置当前会议是否能将参会人放入等候房间的状态
	/// \参数：bEnable ：启用或不启用等候室。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError EnableWaitingRoomOnEntry(bool bEnable) = 0;

	/// \描述：获取在等候室中的参会者名单
	/// \返回：返回值为当前会议所有等候室参与者列表。如果不在会议中，返回NULL。
	virtual std::vector<unsigned int > GetWaitingRoomLst() = 0;

	/// \描述：通过用户id获取等候室用户信息
	/// \参数：userId 指定要获取的用户信息。
	/// \返回：如果函数成功，则返回值为IUserInfo
	/// 如果函数失败，返回值为NULL。
	virtual IUserInfo* GetWaitingRoomUserInfoByID(unsigned int userid) = 0;

	/// \描述：允许用户参加会议
	/// \参数：userId 指定要允许的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError AdmitToMeeting(unsigned int userid) = 0;

	/// \描述：把用户放到等候室
	/// \参数：userId 指定要放入哪个用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError PutInWaitingRoom(unsigned int userid) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif