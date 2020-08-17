/*!
* \文件 meeting_breakout_rooms_interface.h
* \描述： BreakoutRooms of Meeting Service Interface
*
*/
#ifndef ZHUMU_MEETING_BreakoutRooms_INTERFACE_H_
#define ZHUMU_MEETING_BreakoutRooms_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include <vector>
/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
class IBreakoutRoomsInfo
{
public:
	virtual ~IBreakoutRoomsInfo() {};
	/// \描述：获取分会场ID
	/// \返回：如果函数成功，则返回值为分会场ID
	/// 如果函数失败，返回值为NULL。
	virtual const wchar_t* GetBID() = 0;

	/// \描述： Get Breakout Room name
	/// \返回：如果函数成功，则返回值是分会场名称。
	/// 如果函数失败，返回值为NULL。
	virtual const wchar_t* GetBreakoutRoomName() = 0;
};

class IMeetingBreakoutRoomsEvent
{
public:
	//////////////////Callback for ATTENDEES///////////////////
	//接收加入BO请求

	/// \描述：分会场开始回调
	/// \参数：stBID 指定分会场id。
	virtual void OnBreakoutRoomsStartedNotification(const wchar_t* stBID) = 0;
};

/// \描述：分会场管理接口
///
class IMeetingBreakoutRoomsController
{
public:
	/// \描述：设置IBreakoutRoomsEvent通知的处理程序。
	/// \参数：pEvent 当接收到此消息类型时将调用它。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IMeetingBreakoutRoomsEvent* pEvent) = 0;

	/// \描述：加入分会场
	/// \参数：stBID 指定分会场id。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅适用zhumu风格的用户界面模式
	virtual SDKError JoinBreakoutRoom(const wchar_t* stBID) = 0;

	/// \描述：离开分会场
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅适用zhumu风格的用户界面模式
	virtual SDKError LeaveBreakoutRoom() = 0;

	/// \描述：获取可以加入的会议室列表
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅适用zhumu风格的用户界面模式
	virtual std::vector<IBreakoutRoomsInfo* > GetBreakoutRoomsInfoList() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif