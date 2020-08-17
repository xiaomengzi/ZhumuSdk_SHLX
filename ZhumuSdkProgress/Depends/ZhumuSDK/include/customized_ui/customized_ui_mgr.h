/*!
* \�ļ� customized_ui_mgr.h
* \������ zhumu �Զ���ui����ӿ�
*
*/
#ifndef ZHUMU_CUSTOMIZED_UI_MGR_H_
#define ZHUMU_CUSTOMIZED_UI_MGR_H_
#include "..\zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
class ICustomizedVideoContainer;
class ICustomizedShareRender;

/// \�������Զ���ui����ص��¼�
///
class ICustomizedUIMgrEvent
{
public:
	/// \������ Ӧ�ó��������Ƶ���������ٵ�֪ͨ��Ϣ
	/// \������ pContainer ָ���������ĸ���Ƶ����
	virtual void onVideoContainerDestroyed(ICustomizedVideoContainer* pContainer) = 0;

	/// \������ Ӧ�ó�����ڹ�����Ⱦ���ٵ�֪ͨ��Ϣ
	/// \������ pContainer ָ�������ٵĹ���
	virtual void onShareRenderDestroyed(ICustomizedShareRender* pRender) = 0;
};


/// \������ �Զ���ui����ӿ�
///
class ICustomizedUIMgr
{
public:
	/// \������������֤
	/// \���أ������license������ֵΪSDKErr_Success��
	///	���û�����֤������ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError HasLicense() = 0;

	/// \�����������Զ���ui����ص��¼�
	/// \������pEvent һ��ָ��ICustomizedUIMgrEvent*��ָ�룬��ָ����ն��Ƶ�ui�������¼���
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(ICustomizedUIMgrEvent* pEvent) = 0;

	/// \������������Ƶ�����ӿ�
	/// \������ppContainer һ��ָ�����ICustomizedVideoContainer�����ICustomizedVideoContainer*��ָ�롣
	/// \������hParentWnd ָ����Ƶ�����ĸ����ڡ�
	/// \������rc ָ����Ƶ��Ⱦ�Ŀͻ��������λ�á�
	/// �ͻ�����������ڸ����ڵĿͻ�����������Ͻ�
	/// \���أ���������ɹ�������ֵΪSDKErr_Success, ppEmbeddedBrowser��Ϊ��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CreateVideoContainer(ICustomizedVideoContainer** ppContainer, HWND hParentWnd, RECT rc) = 0;

	/// \������������Ƶ�����ӿ�
	/// \������pContainer ָ��Ҫ���ٵ�ICustomizedVideoContainer��ָ�롣
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError DestroyVideoContainer(ICustomizedVideoContainer* pContainer) = 0;

	/// \����������������Ƶ����
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError DestroyAllVideoContainer() = 0;

	/// \����������������Ⱦ�ӿ�
	/// \������ppRender һ��ָ��ICustomizedShareRender*��ָ�룬��ָ�����ICustomizedShareRender����
	/// \������hParentWnd ָ��������Ⱦ�ĸ����ڡ�
	/// \������rc ָ��������Ⱦ�Ŀͻ��������λ��
	/// �ͻ�����������ڸ����ڵĿͻ�����������Ͻ�
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CreateShareRender(ICustomizedShareRender** ppRender, HWND hParentWnd, RECT rc) = 0;

	/// \���������ٹ�����Ⱦ�ӿ�
	/// \������pRender ָ��Ҫ���ٵ�ICustomizedShareRender��ָ�롣
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError DestroyShareRender(ICustomizedShareRender* pRender) = 0;

	/// \�������������й�����Ⱦ
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError DestroyAllShareRender() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif