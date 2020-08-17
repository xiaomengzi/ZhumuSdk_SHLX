/*!
* \文件 customized_video_container.h
* \描述：zhumu 自定义视频接口
*
*/
#ifndef ZHUMU_CUSTOMIZED_VIDEO_CONTAINER_H_
#define ZHUMU_CUSTOMIZED_VIDEO_CONTAINER_H_
#include "..\zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE

/*! \enum VideoRenderElementType
\描述： 视频显示元素的类型。
更详细的结构描述。
*/
enum VideoRenderElementType
{
	VideoRenderElement_None, /// 无
	VideoRenderElement_PRVIEW, ///  IPreviewVideoRenderElement
	VideoRenderElement_ACTIVE, ///  IActiveVideoRenderElement
	VideoRenderElement_NORMAL, ///  INormalVideoRenderElement
};

/*! \enum VideoRenderDataType
\描述： 视频显示元素的数据类型。
更详细的结构描述。
*/
enum VideoRenderDataType
{
	VideoRenderData_None,/// 无
	VideoRenderData_Video,///视频数据
	VideoRenderData_Avatar,/// avatar (无视频数据)
	VideoRenderData_ScreenName,/// screen name (无视频数据)
};

/// \描述：视频元素接口的基类
///
class IVideoRenderElement
{
public:
	/// \描述：获取视频渲染的类型。
	/// \返回：如果函数成功，返回值就是呈渲染类型。参考VideoRenderElementType
	/// 如果函数失败，返回值是VideoRenderElement_None。
	virtual VideoRenderElementType GetType() = 0;

	/// \描述：检索视频渲染元素的客户端区域的坐标。
	/// \返回：接收客户端坐标的矩形结构。
	/// 户端坐标相对于视频容器的客户端区域的左上角
	virtual RECT     GetPos() = 0;

	/// \描述：更改视频渲染的客户端区域的位置。
	/// \参数：pos 指定视频在客户端上的渲染的区域位置。
	virtual SDKError SetPos(RECT pos) = 0;

	/// \描述：显示视频
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError Show() = 0;

	/// \描述：隐藏视频
	///如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError Hide() = 0;

	/// \描述：获取视频元素的用户id。
	/// \返回：指定正在查看用户的用户id。
	virtual unsigned int GetCurrentRenderUserId() = 0;

	/// \描述：获取视频元素的数据类型。
	/// \返回：视频元素的数据类型。
	virtual VideoRenderDataType GetCurrentRenderDataType() = 0;

	/// \描述：启用或不启用在视频上显示屏幕名称。
	/// \参数：enable_show 启用或不启用
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError EnableShowScreenNameOnVideo(bool enable_show) = 0;
	virtual ~IVideoRenderElement() {}
};

/// \描述：预览视频界面(会前)
/// 
class IPreviewVideoRenderElement : public IVideoRenderElement
{
public:
	/// \描述： 开始预览
	virtual SDKError Start() = 0;

	/// \描述： 停止预览
	virtual SDKError Stop() = 0;
	virtual ~IPreviewVideoRenderElement() {}
};

/// \描述：激活视频界面(会议内)
/// 
class IActiveVideoRenderElement : public IVideoRenderElement
{
public:
	/// \描述：开始查看活动用户的视频/头像/屏幕名称数据
	virtual SDKError Start() = 0;

	/// \描述：停止查看活动用户的视频/头像/屏幕名称数据
	virtual SDKError Stop() = 0;
	virtual ~IActiveVideoRenderElement() {}
};

/// \描述：普通视频界面(会议内)
/// 
class INormalVideoRenderElement : public IVideoRenderElement
{
public:
	/// \描述：订阅用户的视频/头像/屏幕名称数据
	/// \参数：userid 指定要查看的用户
	virtual SDKError Subscribe(unsigned int userid) = 0;

	/// \描述：取消订阅用户的视频/头像/屏幕名称数据
	/// \参数：userid 指定要取消订阅的用户
	/// 如果您想切换到其他用户，只需使用其他用户id调用Subscribe
	/// 如果您想回收视频元素，请在隐藏API之前调用此API
	virtual SDKError Unsubscribe(unsigned int userid) = 0;
	virtual ~INormalVideoRenderElement() {}
};

/// \描述：视频容器回调事件
///
class ICustomizedVideoContainerEvent
{
public:
	/// \描述：通知应用程序显示视频的用户id更改
	/// \参数：pElement 指定更改了哪个视频的用户id 
	/// \参数：userid 显示视频的新用户id 
	virtual void onRenderUserChanged(IVideoRenderElement* pElement, unsigned int userid) = 0;

	/// \描述：通知应用程序视频数据类型更改
	/// \param pElement 指定哪个视频的数据类型更改了
	/// \param dataType 新的视频数据类型
	virtual void onRenderDataTypeChanged(IVideoRenderElement* pElement, VideoRenderDataType dataType) = 0;

	/// \描述：通知应用程序视频窗口的大小变化
	/// 当收到此消息时，需要布局视频容器的所有视频元素
	/// \参数：rc 包含矩形的客户端坐标的新视频容器位置，相对于父窗口的客户端区域的左上角。 
	virtual void onLayoutNotification(RECT wnd_client_rect) = 0;

	/// \描述：通知应用程序关于视频渲染元素被销毁的消息
	/// \参数：pElement 指定要销毁哪个呈是视频
	virtual void onVideoRenderElementDestroyed(IVideoRenderElement* pElement) = 0;

	/// \描述：将消息信息传递给app，消息列表如下，
	///WM_MOUSEMOVE
	///WM_MOUSEENTER
	///WM_MOUSELEAVE
	///WM_LBUTTONDOWN
	///WM_LBUTTONUP
	///WM_RBUTTONUP
	///WM_LBUTTONDBLCLK
	///WM_KEYDOWN
	virtual void onWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};

/// \描述： Video container interface
///
class ICustomizedVideoContainer
{
public:
	/// \描述：设置视频容器回调事件
	/// \参数：pEvent 指向接收视频容器事件的ICustomizedVideoContainerEvent*的指针。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(ICustomizedVideoContainerEvent* pEvent) = 0;

	/// \描述：创建视频渲染接口
	/// \参数：ppElement 一个指向IVideoRenderElement*的指针，它接收IVideoRenderElement对象。
	/// \参数；type_ IVideoRenderElement的类型
	/// \返回：如果函数成功，返回值为SDKErr_Success, ppEmbeddedBrowser不为空
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CreateVideoElement(IVideoRenderElement** ppElement, VideoRenderElementType type_) = 0;

	/// \描述：销毁视频渲染元素界面
	/// \参数：ppElement 指向要销毁的IVideoRenderElement的指针。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError DestroyVideoElement(IVideoRenderElement* ppElement) = 0;

	/// \描述：销毁所有视频渲染元素
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError DestroyAllVideoElement() = 0;

	/// \描述：显示视频容器
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError Show() = 0;

	/// \描述：隐藏视频容器
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError Hide() = 0;

	/// \描述：调整视频容器的大小
	/// \参数：rc 它包含矩形的客户端坐标，相对于父窗口的客户端区域的左上角。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError Resize(RECT rc) = 0;

	/// \描述：获取视频容器的视频元素列表。
	/// \返回：如果函数成功，返回值是video元素列表。
	/// 如果函数失败，返回值为NULL。
	virtual std::vector<IVideoRenderElement* >* GetVideoElementList() = 0;

	virtual ~ICustomizedVideoContainer() {}
};
END_ZHUMU_SDK_NAMESPACE
#endif