/*!
* \�ļ� customized_video_container.h
* \������ zhumu �Զ�����Ƶ��ʾ�ӿ�
*
*/
#ifndef ZHUMU_CUSTOMIZED_SHARE_RENDER_H_
#define ZHUMU_CUSTOMIZED_SHARE_RENDER_H_
#include "..\zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum CustomizedViewShareMode
\������ ������ʾ��ͼģʽ��
����ϸ�Ľṹ������
*/
enum CustomizedViewShareMode
{
	CSM_FULLFILL, /// ������������չ���������ڴ�С
	CSM_LETTER_BOX /// ��ԭʼ������ʾ��������
};

/// \������ ����ص��¼�
///
class ICustomizedShareRenderEvent
{
public:
	/// \������ ֪ͨӦ�ó���ʼ���շ�������
	virtual void onSharingContentStartRecving() = 0;

	/// \������ ֪ͨӦ�ó��������ݵ��û�id����
	/// \������ userid �����û�ID 
	virtual void onSharingSourceUserIDNotification(unsigned int userid) = 0;

	/// \������ ����Ϣ��Ϣ���ݸ�app����Ϣ�б�����
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

/// \������ ������Ⱦ�ӿ�
///
class ICustomizedShareRender
{
public:
	/// \���������ù�����Ⱦ�ص��¼�
	/// \������pEvent һ��ָ��ICustomizedShareRenderEvent*��ָ�룬��ָ����չ�������¼��� 
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	///	�������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(ICustomizedShareRenderEvent* pEvent) = 0;

	/// \������ Show share render
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	///	�������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError Show() = 0;

	/// \������ Hide share render
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	///	�������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError Hide() = 0;

	/// \����������Ҫ�鿴�Ĺ��������û�id
	/// \������userid �����ͷ����û�id
	/// 1.����Ե���IMeetingShareController����ȡ���͹����û��б�
	/// 2.����IMeetingShareCtrlEvent��onSharingStatus�ص��¼�����֪��˭��ʼ/ֹͣ����
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	///	�������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetUserID(unsigned int userid) = 0;

	/// \������ ��ȡ���ڹ�����Ƶ���û�ID.
	/// \���أ� ����������óɹ�, ����ֵ���û�ID.
	/// ���ʧ�ܣ�����ֵ��0.
	virtual unsigned int GetUserID() = 0;

	/// \���������������ڵĴ�С
	/// \������rc ���������εĿͻ������꣬����ڸ����ڵĿͻ�����������Ͻǡ�
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	///	�������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError Resize(RECT rc) = 0;

	/// \���������ù����ڵ�ģʽ
	/// \������ģʽ�ο�CustomizedViewShareMode����ϸ��Ϣ
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	///	�������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetViewMode(CustomizedViewShareMode mode) = 0;

	/// \��������ȡ��ʾ���ڵľ����
	/// \���أ���������ɹ�������ֵ�Ǵ��ڵľ����
	/// �������ʧ�ܣ�����ֵΪNULL
	virtual HWND GetOwnerWnd() = 0;

	/// \������ �ƶ�������
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	///	�������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// ��Ҫ�������apiʱ�������ڵõ�WM_MOVE������Ϣ��
	virtual SDKError HandleWindowsMoveMsg() = 0;

	virtual ~ICustomizedShareRender() {}
};
END_ZHUMU_SDK_NAMESPACE

#endif