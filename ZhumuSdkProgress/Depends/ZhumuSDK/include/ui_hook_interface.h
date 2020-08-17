/*!
* \�ļ� ui_hook_interface.h
* \���� UI Hook Interface
* 
*/
#ifndef _UI_HOOK_INTERFACE_H_
#define _UI_HOOK_INTERFACE_H_

#include "zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum UIHOOKHWNDTYPE
    \���� SDK hook ����.
	\�����Ǹ���ϸ�Ľṹ����.
*/
enum UIHOOKHWNDTYPE
{
	UIHOOKWNDTYPE_USERDEFIEND,///<�û�����hooking��Ϣ�ʹ�������.
	UIHOOKWNDTYPE_MAINWND,///<������hooking����.
	UIHOOKWNDTYPE_BOTTOMTOOLBAR,///<�ײ�hooking������������.
};
/// \����: UI hooker �ص��¼�.
///
class IUIHookerEvent
{
public:
	/// \������UI��ض���hook�ص����ص�ֻ�ڹ����߳��й����������������߳�.
	/// \������type Hook ����. ��ϸ�鿴 UIHOOKHWNDTYPE enum.
	/// \������msg Hooked ��Ϣ. ��ϸ�鿴 windows MSG structure.
	virtual void onUIActionNotify(UIHOOKHWNDTYPE type, MSG msg) = 0;
};
/// \������ Ƕ��������ӿ�.
///
class IUIHooker
{
public:
	/// \����������UI Hooker�ص��¼����.
	/// \������pEvent һ������Hooker�¼���IUIHookerEventָ��
	/// \���أ�����������óɹ������� SDKErr_Success.
	///	ʧ�ܷ�������ֵ. ��ȡ���������Ϣ���鿴 SDKError enum.
	virtual SDKError SetEvent(IUIHookerEvent* pEvent) = 0;

	/// \��������ӻ�ɾ����hood�Ĵ�����Ϣ.
	/// \������wndmsgid ָ��������Ϣ ID, ���� WM_CREATE.
	/// \������bAdd TRUE ��ʾ���.
	/// \���أ�����������óɹ������� SDKErr_Success.
	///	ʧ�ܷ�������ֵ. ��ȡ���������Ϣ���鿴 SDKError enum.
	virtual SDKError MonitorWndMessage(unsigned int wndmsgid, bool bAdd = true) = 0;

	/// \��������ӻ�ɾ����hook�Ĵ���.
	/// \������ͨ��windows API GetClassName()��ȡҪ�ҽӻ�ȡ���ҽӵ�windows������ֵ.
	/// \������bAdd TRUE ��ʾ���.
	/// \���أ�����������óɹ������� SDKErr_Success.
	///	ʧ�ܷ�������ֵ. ��ȡ���������Ϣ���鿴 SDKError enum.
	virtual SDKError MonitorWnd(const wchar_t* classname, bool bAdd = true) = 0;

	/// \��������ʼ hooking. 
	/// \���أ�����������óɹ������� SDKErr_Success.
	///	ʧ�ܷ�������ֵ. ��ȡ���������Ϣ���鿴 SDKError enum.
	virtual SDKError Start() = 0;
	
	/// \������ֹͣ hooking. 
	/// \���أ�����������óɹ������� SDKErr_Success.
	///	ʧ�ܷ�������ֵ. ��ȡ���������Ϣ���鿴 SDKError enum.
	/// ���øú����������SDK�еĹ����б�ͨ��MonitorWndMessage()��MonitorWnd()ɾ���´β���������Ϣ�򴰿�
	virtual SDKError Stop() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif