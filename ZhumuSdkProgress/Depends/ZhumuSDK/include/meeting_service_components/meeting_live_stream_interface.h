/*!
* \文件：meeting_sharing_interface.h
* \描述：会议共享服务接口
*
*/
#ifndef ZHUMU_MEETING_LIVE_STREAM_INTERFACE_H_
#define ZHUMU_MEETING_LIVE_STREAM_INTERFACE_H_
#include "..\zhumu_sdk_def.h"

/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE

/*! \enum LiveStreamStatus
\描述：直播状态
更详细的结构描述。
*/
enum LiveStreamStatus
{
	LiveStreamStatus_None,///< None
	LiveStreamStatus_InProgress,///< 正在进行
	LiveStreamStatus_Connecting,///< 连接中
	LiveStreamStatus_Start_Failed_Timeout,///< 连接超时
	LiveStreamStatus_Start_Failed,///< 连接失败
	LiveStreamStatus_Ended,///< 结束
};

/// \描述：会议直播流控制器回调事件
///
class IMeetingLiveStreamCtrlEvent
{
public:
	/// \描述：直播状态改变回调
	/// \参数：status 状态。
	virtual void onLiveStreamStatusChange(LiveStreamStatus status) = 0;
};

/// \描述：当前会议的直播项目
///
class IMeetingLiveStreamItem
{
public:
	/// \描述：获取直播的url
	/// \返回：如果函数成功，返回值是直播的url。
	virtual const wchar_t* GetLiveStreamURL() = 0;

	/// \描述：获取直播的描述
	/// \返回：如果函数成功，则返回直播的描述。
	virtual const wchar_t* GetLiveStreamURLDescription() = 0;
	virtual ~IMeetingLiveStreamItem() {};
};

/// \描述：会议直播控制器接口
///
class IMeetingLiveStreamController
{
public:
	/// \描述：设置会议直播回调事件
	/// \参数：pEvent 一个指向IMeetingLiveStreamCtrlEvent*的指针，该指针接收实时流事件。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IMeetingLiveStreamCtrlEvent* pEvent) = 0;

	/// \描述：检查是否可以启动直播
	/// \返回：如果可以启动直播，返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CanStartLiveStream() = 0;

	/// \描述：开启直播
	/// \参数：item_ 指向 IMeetingLiveStreamController::GetSupportLiveStreamURL() API创建的IMeetingLiveStreamItem指针。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError StartLiveStream(IMeetingLiveStreamItem* item_) = 0;

	/// \描述：开启直播
	/// \参数：streamingURL 直播的URL
	/// \参数：streamingKey 直播的key。
	/// \参数：broadcastURL 直播的广播URL。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// 您可以从第三方直播服务获得这些参数
	virtual SDKError StartLiveStreamWithSteamingURL(const wchar_t* streamingURL, const wchar_t* streamingKey, const wchar_t* broadcastURL) = 0;

	/// \描述：停止直播
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError StopLiveStream() = 0;

	/// \描述：获取当前会议直播使用的URL和关联信息列表。
	/// \返回：如果函数成功，返回的值就是要进行直播的会议信息。
	/// 否则失败，返回值为NULL。更多信息，请参见IMeetingLiveStreamItem
	virtual IList<IMeetingLiveStreamItem* >* GetSupportLiveStreamURL() = 0;

	/// \描述：获取当前会议的直播状态。
	/// \返回：如果函数成功，则返回当前会议的直播状态，查看LiveStreamStatus。
	virtual LiveStreamStatus GetCurrentLiveStreamStatus() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif