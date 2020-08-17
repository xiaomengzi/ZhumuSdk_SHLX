/*!
* \文件：embedded_browser_interface.h
* \描述：嵌入浏览器接口。
*
*/
#ifndef _EMBEDDED_BROWSER_INTERFACE_H_
#define _EMBEDDED_BROWSER_INTERFACE_H_
#include "zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE

/*! \enum NavigateError
\描述：导航栏错误码.
下面是更详细的结构描述
*/
enum NavigateError
{
	NavigateError_Success = 0,///<导航栏成功.
	NavigateError_HttpStatus = 1,///<HTTP请求相关错误。.
	NavigateError_InvalidUrl,///<INET_E_INVALID_URL (0x800C0002L or -2146697214)
	NavigateError_NoSession,///<INET_E_NO_SESSION (0x800C0003L or -2146697213)
	NavigateError_CannotConnect,///<INET_E_CANNOT_CONNECT (0x800C0004L or -2146697212)
	NavigateError_ResourceNotFound,///<INET_E_RESOURCE_NOT_FOUND (0x800C0005L or -2146697211)
	NavigateError_ObjNotFound,///<INET_E_OBJECT_NOT_FOUND (0x800C0006L or -2146697210)
	NavigateError_DataNotAvailable,///<INET_E_DATA_NOT_AVAILABLE (0x800C0007L or -2146697209)
	NavigateError_DownloadFailure,///<INET_E_DOWNLOAD_FAILURE (0x800C0008L or -2146697208)
	NavigateError_ConnectionTimeout,///<INET_E_CONNECTION_TIMEOUT (0x800C000BL or -2146697205)
	NavigateError_CannotLoadData,///<INET_E_CANNOT_LOAD_DATA (0x800C000FL or -2146697201)
	NavigateError_BrowserContainerError,///<浏览器容器错误.
	NavigateError_Others,///<其他错误.
};

/// \描述： 嵌入浏览器回调事件。
///
class IEmbeddedBrowserEvent
{
public:
	/// \描述：回调事件将在嵌入浏览器开始导航之前触发。
	/// \参数：url 嵌入式浏览器使用的URL，采用UTF8编码格式
	virtual void NotifyBeforeNavigate(const char* url) = 0;

	/// \描述：一旦嵌入式浏览器接收到所有信息，就会触发回调事件。.
	/// \参数：url 嵌入式浏览器使用的URL，采用UTF8编码格式。
	virtual void NotifyDocumentComplete(const char* url) = 0;

	/// \描述：当嵌入式浏览器访问网站时发生错误时，将触发回调事件。
	/// \参数：url 嵌入式浏览器使用的URL，采用UTF8编码格式。
	/// \参数：err 指定错误信息。有关详细信息，请参见 NavigateError enum。
	/// \参数：component_err 原始错误码.
	virtual void NotifyNavigateError(const char* url, NavigateError err, int component_err) = 0;
};

/// \描述： 嵌入的浏览器接口。
///
class IEmbeddedBrowser
{
public:
	/// \描述：设置嵌入式浏览器回调事件处理程序。
	/// \参数：pEvent 一个指向IEmbeddedBrowserEvent的指针，该指针接收嵌入式浏览器事件。
	/// \返回： 如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError SetEvent(IEmbeddedBrowserEvent* pEvent) = 0;

	/// \描述：开始浏览导航。
	/// \参数：url 浏览器的URL或要访问的文件的完整路径，或要以UTF8编码格式打开的文件的完整路径。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError Navigate(const char* url) = 0;

	/// \描述：调整嵌入式浏览器窗口的大小，以覆盖父窗口的客户端区域。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError Resize() = 0;

	/// \描述：获取与当前显示内容匹配的URL，或获取文件的完整路径，或包含文件名的完整路径。
	/// \返回：URL匹配当前显示的内容或文件的完整路径，或包含文件名的完整路径
	virtual const char* GetURL() = 0;

	/// \描述：获取当前显示内容的标题。
	/// \返回：当前显示内容的标题。
	///如果资源是HTML web页面，那么名称就是文档的标题。
	///如果资源是网络或本地计算机上的文件夹或文件，则该名称是采用通用命名约定(UNC)格式的文件夹或文件的完整路径。. 
	virtual const char* GetTitle() = 0;

	/// \描述：如果存在导航历史记录，通过web控件导航到前面的页面。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError GoBack() = 0;

	/// \描述：如果存在导航历史记录，通过web控件导航到下一页。 
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError GoForward() = 0;

	/// \描述：重新加载web浏览器上显示的当前文档。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError DoRefresh() = 0;

	/// \描述：取消所有挂起的导航或动态元素，如背景声音和动画。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError DoStop() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif