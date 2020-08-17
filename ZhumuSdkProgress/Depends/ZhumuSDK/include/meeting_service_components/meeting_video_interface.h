/*!
* \文件：meeting_video_interface.h
* \描述：会议视频服务接口
*
*/
#ifndef ZHUMU_MEETING_VIDEO_INTERFACE_H_
#define ZHUMU_MEETING_VIDEO_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include "..\zhumu_sdk_util_define.h"
/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
enum VideoStatus
{
	Video_ON,
	Video_OFF,
};

class IRequestStartVideoHandler
{
public:
	virtual ~IRequestStartVideoHandler() {};

	virtual unsigned int GetReqFromUserId() = 0;
	virtual SDKError Ignore() = 0;
	virtual SDKError Accept() = 0;
	virtual SDKError Cancel() = 0;
};

/// \描述：会议视频控制器回调事件
///
class IMeetingVideoCtrlEvent
{
public:
	/// \描述：用户的视频状态变化回调
	/// \参数：userId 
	/// \参数：status
	virtual void onUserVideoStatusChange(unsigned int userId, VideoStatus status) = 0;

	/// \描述：焦点视频变化回调
	/// \参数：userId 
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid) = 0;

	/// \描述：主持人请求开始视频回调
	/// \参数：handler_
	virtual void onHostRequestStartVideo(IRequestStartVideoHandler* handler_) = 0;

	/// \描述：音频活动者变化回调
	/// \参数：userId 
	virtual void onActiveSpeakerVideoUserChanged(unsigned int userid) = 0;

	/// \描述：视频活动者变化回调
	/// \参数：userId 
	virtual void onActiveVideoUserChanged(unsigned int userid) = 0;
};

/// \描述：会议视频控制器接口
///
class IMeetingVideoController
{
public:
	/// \描述：设置会议视频控制器回调事件
	/// \参数：pEvent 一个指向IMeetingVideoCtrlEvent*的接收视频事件的指针。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IMeetingVideoCtrlEvent* pEvent) = 0;

	/// \描述：静音视频
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义Ui风格
	virtual SDKError MuteVideo() = 0;

	/// \描述：取消静音视频
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义Ui风格
	virtual SDKError UnmuteVideo() = 0;

	/// \描述：固定或不固定视频
	/// \参数：bPin 固定或不固定视频
	/// \参数：bFirstView 第一个屏幕或不固定的视频.
	/// \参数：userid 指定要固定哪个用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅支持zhumu UI风格
	virtual SDKError PinVideo(bool bPin, bool bFirstView, unsigned int userid) = 0;

	/// \描述：焦点视频
	/// \参数：bSpotlight 焦点视频
	/// \参数：userid 指定要焦点视频显示的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义Ui风格
	virtual SDKError SpotlightVideo(bool bSpotlight, unsigned int userid) = 0;

	/// \描述：隐藏或显示没有视频用户在视频墙模式
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅支持zhumu UI风格
	virtual SDKError HideOrShowNoVideoUserOnVideoWall(bool bHide) = 0;

	/// \描述：检测是否能要求参会者打开视频
	/// \参数：userid 指定要检查的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义Ui风格
	virtual SDKError CanAskAttendeeToStartVideo(unsigned int userid) = 0;

	/// \描述：要求参会者打开视频
	/// \参数：userid 指定要求的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义Ui风格
	virtual SDKError AskAttendeeToStartVideo(unsigned int userid) = 0;

	/// \描述：检测是否能停止参会者的视频
	/// \参数：userid Specifies which user you want to check.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义Ui风格
	virtual SDKError CanStopAttendeeVideo(unsigned int userid) = 0;

	/// \描述：停止参会者的视频
	/// \参数：userid 指定要停止的用户
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义Ui风格
	virtual SDKError StopAttendeeVideo(unsigned int userid) = 0;

	virtual ICameraController* GetMyCameraController() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif