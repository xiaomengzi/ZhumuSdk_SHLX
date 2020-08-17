/*!
* \文件 ui_hook_interface.h
* \描述 UI Hook Interface
* 
*/
#ifndef _UI_HOOK_INTERFACE_H_
#define _UI_HOOK_INTERFACE_H_

#include "zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum UIHOOKHWNDTYPE
    \描述 SDK hook 类型.
	\下面是更详细的结构描述.
*/
enum UIHOOKHWNDTYPE
{
	UIHOOKWNDTYPE_USERDEFIEND,///<用户定义hooking信息和窗口类型.
	UIHOOKWNDTYPE_MAINWND,///<主窗口hooking类型.
	UIHOOKWNDTYPE_BOTTOMTOOLBAR,///<底部hooking工具栏的类型.
};
/// \描述: UI hooker 回调事件.
///
class IUIHookerEvent
{
public:
	/// \描述：UI相关动作hook回调。回调只在工作线程中工作，不反馈给主线程.
	/// \参数：type Hook 类型. 详细查看 UIHOOKHWNDTYPE enum.
	/// \参数：msg Hooked 信息. 详细查看 windows MSG structure.
	virtual void onUIActionNotify(UIHOOKHWNDTYPE type, MSG msg) = 0;
};
/// \描述： 嵌入浏览器接口.
///
class IUIHooker
{
public:
	/// \描述：设置UI Hooker回调事件句柄.
	/// \参数：pEvent 一个接收Hooker事件的IUIHookerEvent指针
	/// \返回：如果方法调用成功，返回 SDKErr_Success.
	///	失败返回其他值. 获取更多错误信息，查看 SDKError enum.
	virtual SDKError SetEvent(IUIHookerEvent* pEvent) = 0;

	/// \描述：添加或删除被hood的窗口信息.
	/// \参数：wndmsgid 指定窗口消息 ID, 例如 WM_CREATE.
	/// \参数：bAdd TRUE 表示添加.
	/// \返回：如果方法调用成功，返回 SDKErr_Success.
	///	失败返回其他值. 获取更多错误信息，查看 SDKError enum.
	virtual SDKError MonitorWndMessage(unsigned int wndmsgid, bool bAdd = true) = 0;

	/// \描述：添加或删除被hook的窗口.
	/// \参数：通过windows API GetClassName()获取要挂接或取消挂接的windows类名的值.
	/// \参数：bAdd TRUE 表示添加.
	/// \返回：如果方法调用成功，返回 SDKErr_Success.
	///	失败返回其他值. 获取更多错误信息，查看 SDKError enum.
	virtual SDKError MonitorWnd(const wchar_t* classname, bool bAdd = true) = 0;

	/// \描述：开始 hooking. 
	/// \返回：如果方法调用成功，返回 SDKErr_Success.
	///	失败返回其他值. 获取更多错误信息，查看 SDKError enum.
	virtual SDKError Start() = 0;
	
	/// \描述：停止 hooking. 
	/// \返回：如果方法调用成功，返回 SDKErr_Success.
	///	失败返回其他值. 获取更多错误信息，查看 SDKError enum.
	/// 调用该函数不会清除SDK中的钩子列表。通过MonitorWndMessage()或MonitorWnd()删除下次不想挂起的消息或窗口
	virtual SDKError Stop() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif