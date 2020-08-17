/*!
* \文件：meeting_remote_ctrl_interface.h
* \描述：会议远程控制服务接口
* \支持zhumu风格和自定义UI风格
*/
#ifndef ZHUMU_MEETING_REMOTE_CTRL_INTERFACE_H_
#define ZHUMU_MEETING_REMOTE_CTRL_INTERFACE_H_
#include "..\zhumu_sdk_def.h"

/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum RemoteControlStatus
\描述：远程控制状态.
更详细的结构描述
*/
enum RemoteControlStatus
{
	Remote_Control_None,
	Remote_Control_I_Can_Request_Control_Who,

	Remote_Control_I_Can_Control_Who_Begin,
	Remote_Control_I_Can_Control_Who_End,

	Remote_Control_I_Control_Who_Begin,
	Remote_Control_I_Control_Who_End,

	Remote_Control_Who_Control_Me,
	Remote_Control_I_Recv_Decline_Msg,
	Remote_Control_I_Recv_Request_Msg,
};

/// \描述：会议远程控制回调事件
///
class IMeetingRemoteCtrlEvent
{
public:
	/// \描述：远程控制状态通知回调
	/// \参数：status 远程控制状态值。
	/// \参数：userId 远程控制用户id。
	virtual void onRemoteControlStatus(RemoteControlStatus status, unsigned int userId) = 0;
};

/// \描述： 会议远程控制接口
///
class IMeetingRemoteController
{
public:
	/// \描述：设置会议远程控制回调事件
	/// \参数：pEvent 一个指向接收远程控制事件的IMeetingRemoteCtrlEvent*的指针。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IMeetingRemoteCtrlEvent* pEvent) = 0;

	/// \描述：检查是否可以远程控制
	/// \参数：userid 指定要检查的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CanRequestControl(unsigned int userId) = 0;

	/// \描述：检查是否有控制权限
	/// \参数：userid 指定要检查的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError IsHaveRemoteControlRight(unsigned int userId) = 0;

	/// \描述：检查远程控制人的状态
	/// \参数：userid 指定要检查的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError IsInRemoteControllingStatus(unsigned int userId) = 0;

	/// \描述：如果您有权利，开始远程控制某人
	/// \参数：userid 指定要远程控制的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError EnterRemoteControllingStatus(unsigned int userId) = 0;

	/// \描述：如果你有权利，取消远程控制某人
	/// \参数：userid 指定要离开的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError LeaveRemoteControllingStatus(unsigned int userId) = 0;

	/// \描述：请求会议遥控
	/// \参数：userId 指定要远程控制的用户
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError RequestRemoteControl(unsigned int userId) = 0;

	/// \描述：放弃会议远程控制
	/// \参数：userId 指定要放弃远程控制权的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError GiveupRemoteControl(unsigned int userId) = 0;

	/// \描述：将会议远程遥控权交给其他参会者
	/// \参数：userId 指定要控制屏幕的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError GiveRemoteControlTo(unsigned int userId) = 0;

	/// \描述：拒绝远程控制要求
	/// \参数：userId 指定哪些用户不能控制屏幕
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError DeclineRemoteControlRequest(unsigned int userId) = 0;

	/// \描述：撤销当前远程控制者的权限
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError RevokeRemoteControl() = 0;

	/// \描述：获取会议当前远程控制者
	/// \参数：userId 存储当前远程控制的用户id，如果为零，则表示现在会议没有远程控制者。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError GetCurrentRemoteController(unsigned int& userId) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif