/*!
* \文件 meeting_recording_interface.h
* \描述： 会议录制服务接口
* \支持zhumu风格和自定义UI风格
*/
#ifndef ZHUMU_MEETING_Recording_INTERFACE_H_
#define ZHUMU_MEETING_Recording_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include <time.h>

/// \描述：Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum RecordingStatus
\描述：录制状态.
更详细的结构描述
*/
enum RecordingStatus
{
	Recording_Start,			 //开始, 本地&云录制共用
	Recording_Stop,				 //结束, 本地&云录制共用
	Recording_DiskFull,			 //错误, 本地&云录制共用
	Recording_Pause,			 //暂停, 本地&云录制共用
	Recording_Connecting,		 //连接中, 仅适用于云录制
};

class ICustomizedLocalRecordingLayoutHelper;
/// \描述： Meeting recording callback event
///
class IMeetingRecordingCtrlEvent
{
public:
	/// \描述：一旦mp4转换完成，此方法将被回调
	/// \参数：bsuccess 成功或失败.
	/// \参数：iResult 失败时错误代码的详细信息.
	/// \参数：szPath 如果成功，将返回记录文件路径，否则为空
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath) = 0;

	/// \描述：通知mp4转换处理
	/// \参数：iPercentage 转换过程的百分比。
	virtual void onRecording2MP4Processing(int iPercentage) = 0;

	/// \描述：自己录制状态通知回调
	/// \参数：status 录制状态
	virtual void onRecordingStatus(RecordingStatus status) = 0;

	/// \描述：云录制状态通知回调
	/// \参数：status 录制状态
	virtual void onCloudRecordingStatus(RecordingStatus status) = 0;

	/// \描述：自己录制权限改变回调
	/// \参数：bCanRec 能否录制
	virtual void onRecordPriviligeChanged(bool bCanRec) = 0;

	/// \描述：用于自定义ui模式的本地录制源回调
	/// \参数：layout_helper 本地录制接口.
	/// layout_helper将在调用结束后释放，请在此调用结束前进行布局。
	virtual void onCustomizedLocalRecordingSourceNotification(ICustomizedLocalRecordingLayoutHelper* layout_helper) = 0;
};

/// \描述： 会议录制控制接口
///
class IMeetingRecordingController
{
public:
	/// \描述：设置会议录制控制事件
	/// \描述：pEvent 一个指向IMeetingRecordingCtrlEvent*的指针，接收录制事件。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IMeetingRecordingCtrlEvent* pEvent) = 0;

	/// \描述：开始录制
	/// \描述：startTimestamp 开始录制的时间戳
	/// \描述：recPath 指定录制的保存路径,如果路径不存在,返回SDKERR_INVALID_描述:ETER 错误代码。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError StartRecording(time_t& startTimestamp, wchar_t* recPath) = 0;

	/// \描述：停止录制
	/// \描述：stopTimestamp 停止录制时间戳。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError StopRecording(time_t& stopTimestamp) = 0;

	/// \描述： 检查是否可以开始录制
	/// \描述： cloud_recording 能录制或不能 
	/// \描述： userid 指定要检查的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CanStartRecording(bool cloud_recording, unsigned int userid) = 0;

	/// \描述：检查可以允许或不允许在会议中的其他参会者开始本地录制
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CanAllowDisAllowLocalRecording() = 0;

	/// \描述：开始云录制
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError StartCloudRecording() = 0;

	/// \描述：停止云录制
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError StopCloudRecording() = 0;

	/// \描述：检查是否支持本地录制功能
	/// \描述：userid 指定要检查的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError IsSupportLocalRecording(unsigned int userid) = 0;

	/// \描述： Allow to start local recoding
	/// \描述： userid Specifies which user you want to allow.
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError AllowLocalRecording(unsigned int userid) = 0;

	/// \描述：不允许开始本地录制
	/// \描述：userid 指定要禁用录制的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError DisAllowLocalRecording(unsigned int userid) = 0;

	/// \描述：请求自定义本地录制源通知
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// 仅适用于自定义UI模式
	virtual SDKError RequestCustomizedLocalRecordingSource() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif