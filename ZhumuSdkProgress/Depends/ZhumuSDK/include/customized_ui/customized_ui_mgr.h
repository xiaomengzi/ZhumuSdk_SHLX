/*!
* \文件 customized_ui_mgr.h
* \描述： zhumu 自定义ui管理接口
*
*/
#ifndef ZHUMU_CUSTOMIZED_UI_MGR_H_
#define ZHUMU_CUSTOMIZED_UI_MGR_H_
#include "..\zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
class ICustomizedVideoContainer;
class ICustomizedShareRender;

/// \描述：自定义ui管理回调事件
///
class ICustomizedUIMgrEvent
{
public:
	/// \描述： 应用程序关于视频容器被销毁的通知消息
	/// \参数： pContainer 指定将销毁哪个视频容器
	virtual void onVideoContainerDestroyed(ICustomizedVideoContainer* pContainer) = 0;

	/// \描述： 应用程序关于共享渲染销毁的通知消息
	/// \参数： pContainer 指定将销毁的共享
	virtual void onShareRenderDestroyed(ICustomizedShareRender* pRender) = 0;
};


/// \描述： 自定义ui管理接口
///
class ICustomizedUIMgr
{
public:
	/// \描述：检查许可证
	/// \返回：如果有license，返回值为SDKErr_Success。
	///	如果没有许可证，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError HasLicense() = 0;

	/// \描述：设置自定义ui管理回调事件
	/// \参数：pEvent 一个指向ICustomizedUIMgrEvent*的指针，该指针接收定制的ui管理器事件。
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(ICustomizedUIMgrEvent* pEvent) = 0;

	/// \描述：创建视频容器接口
	/// \参数：ppContainer 一个指向接收ICustomizedVideoContainer对象的ICustomizedVideoContainer*的指针。
	/// \参数：hParentWnd 指定视频容器的父窗口。
	/// \参数：rc 指定视频渲染的客户端区域的位置。
	/// 客户端坐标相对于父窗口的客户端区域的左上角
	/// \返回：如果函数成功，返回值为SDKErr_Success, ppEmbeddedBrowser不为空
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CreateVideoContainer(ICustomizedVideoContainer** ppContainer, HWND hParentWnd, RECT rc) = 0;

	/// \描述：销毁视频容器接口
	/// \参数：pContainer 指向要销毁的ICustomizedVideoContainer的指针。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError DestroyVideoContainer(ICustomizedVideoContainer* pContainer) = 0;

	/// \描述：销毁所有视频容器
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError DestroyAllVideoContainer() = 0;

	/// \描述：创建共享渲染接口
	/// \参数：ppRender 一个指向ICustomizedShareRender*的指针，该指针接收ICustomizedShareRender对象。
	/// \参数：hParentWnd 指定共享渲染的父窗口。
	/// \参数：rc 指定共享渲染的客户端区域的位置
	/// 客户端坐标相对于父窗口的客户端区域的左上角
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CreateShareRender(ICustomizedShareRender** ppRender, HWND hParentWnd, RECT rc) = 0;

	/// \描述：销毁共享渲染接口
	/// \参数：pRender 指向要销毁的ICustomizedShareRender的指针。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError DestroyShareRender(ICustomizedShareRender* pRender) = 0;

	/// \描述：销毁所有共享渲染
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError DestroyAllShareRender() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif