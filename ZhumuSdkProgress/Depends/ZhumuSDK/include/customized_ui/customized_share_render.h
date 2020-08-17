/*!
* \文件 customized_video_container.h
* \描述： zhumu 自定义视频显示接口
*
*/
#ifndef ZHUMU_CUSTOMIZED_SHARE_RENDER_H_
#define ZHUMU_CUSTOMIZED_SHARE_RENDER_H_
#include "..\zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum CustomizedViewShareMode
\描述： 共享显示视图模式。
更详细的结构描述。
*/
enum CustomizedViewShareMode
{
	CSM_FULLFILL, /// 将共享内容扩展到整个窗口大小
	CSM_LETTER_BOX /// 以原始比例显示共享内容
};

/// \描述： 共享回调事件
///
class ICustomizedShareRenderEvent
{
public:
	/// \描述： 通知应用程序开始接收分享内容
	virtual void onSharingContentStartRecving() = 0;

	/// \描述： 通知应用程序共享内容的用户id更改
	/// \参数： userid 共享用户ID 
	virtual void onSharingSourceUserIDNotification(unsigned int userid) = 0;

	/// \描述： 将消息信息传递给app，消息列表如下
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

/// \描述： 共享渲染接口
///
class ICustomizedShareRender
{
public:
	/// \描述：设置共享渲染回调事件
	/// \参数：pEvent 一个指向ICustomizedShareRenderEvent*的指针，该指针接收共享呈现事件。 
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	///	如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(ICustomizedShareRenderEvent* pEvent) = 0;

	/// \描述： Show share render
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	///	如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError Show() = 0;

	/// \描述： Hide share render
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	///	如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError Hide() = 0;

	/// \描述：设置要查看的共享对象的用户id
	/// \参数：userid 共享发送方的用户id
	/// 1.你可以调用IMeetingShareController。获取发送共享用户列表
	/// 2.处理IMeetingShareCtrlEvent。onSharingStatus回调事件，以知道谁开始/停止共享
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	///	如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetUserID(unsigned int userid) = 0;

	/// \描述： 获取正在共享视频的用户ID.
	/// \返回： 如果方法调用成功, 返回值是用户ID.
	/// 如果失败，返回值是0.
	virtual unsigned int GetUserID() = 0;

	/// \描述：调整共享窗口的大小
	/// \参数：rc 它包含矩形的客户端坐标，相对于父窗口的客户端区域的左上角。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	///	如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError Resize(RECT rc) = 0;

	/// \描述：设置共享窗口的模式
	/// \参数：模式参考CustomizedViewShareMode的详细信息
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	///	如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetViewMode(CustomizedViewShareMode mode) = 0;

	/// \描述：获取显示窗口的句柄。
	/// \返回：如果函数成功，返回值是窗口的句柄。
	/// 如果函数失败，返回值为NULL
	virtual HWND GetOwnerWnd() = 0;

	/// \描述： 移动共享窗口
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	///	如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// 需要调用这个api时，父窗口得到WM_MOVE窗口消息。
	virtual SDKError HandleWindowsMoveMsg() = 0;

	virtual ~ICustomizedShareRender() {}
};
END_ZHUMU_SDK_NAMESPACE

#endif