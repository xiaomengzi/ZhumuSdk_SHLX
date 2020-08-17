/*!
* \�ļ���embedded_browser_interface.h
* \������Ƕ��������ӿڡ�
*
*/
#ifndef _EMBEDDED_BROWSER_INTERFACE_H_
#define _EMBEDDED_BROWSER_INTERFACE_H_
#include "zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE

/*! \enum NavigateError
\������������������.
�����Ǹ���ϸ�Ľṹ����
*/
enum NavigateError
{
	NavigateError_Success = 0,///<�������ɹ�.
	NavigateError_HttpStatus = 1,///<HTTP������ش���.
	NavigateError_InvalidUrl,///<INET_E_INVALID_URL (0x800C0002L or -2146697214)
	NavigateError_NoSession,///<INET_E_NO_SESSION (0x800C0003L or -2146697213)
	NavigateError_CannotConnect,///<INET_E_CANNOT_CONNECT (0x800C0004L or -2146697212)
	NavigateError_ResourceNotFound,///<INET_E_RESOURCE_NOT_FOUND (0x800C0005L or -2146697211)
	NavigateError_ObjNotFound,///<INET_E_OBJECT_NOT_FOUND (0x800C0006L or -2146697210)
	NavigateError_DataNotAvailable,///<INET_E_DATA_NOT_AVAILABLE (0x800C0007L or -2146697209)
	NavigateError_DownloadFailure,///<INET_E_DOWNLOAD_FAILURE (0x800C0008L or -2146697208)
	NavigateError_ConnectionTimeout,///<INET_E_CONNECTION_TIMEOUT (0x800C000BL or -2146697205)
	NavigateError_CannotLoadData,///<INET_E_CANNOT_LOAD_DATA (0x800C000FL or -2146697201)
	NavigateError_BrowserContainerError,///<�������������.
	NavigateError_Others,///<��������.
};

/// \������ Ƕ��������ص��¼���
///
class IEmbeddedBrowserEvent
{
public:
	/// \�������ص��¼�����Ƕ���������ʼ����֮ǰ������
	/// \������url Ƕ��ʽ�����ʹ�õ�URL������UTF8�����ʽ
	virtual void NotifyBeforeNavigate(const char* url) = 0;

	/// \������һ��Ƕ��ʽ��������յ�������Ϣ���ͻᴥ���ص��¼���.
	/// \������url Ƕ��ʽ�����ʹ�õ�URL������UTF8�����ʽ��
	virtual void NotifyDocumentComplete(const char* url) = 0;

	/// \��������Ƕ��ʽ�����������վʱ��������ʱ���������ص��¼���
	/// \������url Ƕ��ʽ�����ʹ�õ�URL������UTF8�����ʽ��
	/// \������err ָ��������Ϣ���й���ϸ��Ϣ����μ� NavigateError enum��
	/// \������component_err ԭʼ������.
	virtual void NotifyNavigateError(const char* url, NavigateError err, int component_err) = 0;
};

/// \������ Ƕ���������ӿڡ�
///
class IEmbeddedBrowser
{
public:
	/// \����������Ƕ��ʽ������ص��¼��������
	/// \������pEvent һ��ָ��IEmbeddedBrowserEvent��ָ�룬��ָ�����Ƕ��ʽ������¼���
	/// \���أ� ��������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError SetEvent(IEmbeddedBrowserEvent* pEvent) = 0;

	/// \��������ʼ���������
	/// \������url �������URL��Ҫ���ʵ��ļ�������·������Ҫ��UTF8�����ʽ�򿪵��ļ�������·����
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError Navigate(const char* url) = 0;

	/// \����������Ƕ��ʽ��������ڵĴ�С���Ը��Ǹ����ڵĿͻ�������
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError Resize() = 0;

	/// \��������ȡ�뵱ǰ��ʾ����ƥ���URL�����ȡ�ļ�������·����������ļ���������·����
	/// \���أ�URLƥ�䵱ǰ��ʾ�����ݻ��ļ�������·����������ļ���������·��
	virtual const char* GetURL() = 0;

	/// \��������ȡ��ǰ��ʾ���ݵı��⡣
	/// \���أ���ǰ��ʾ���ݵı��⡣
	///�����Դ��HTML webҳ�棬��ô���ƾ����ĵ��ı��⡣
	///�����Դ������򱾵ؼ�����ϵ��ļ��л��ļ�����������ǲ���ͨ������Լ��(UNC)��ʽ���ļ��л��ļ�������·����. 
	virtual const char* GetTitle() = 0;

	/// \������������ڵ�����ʷ��¼��ͨ��web�ؼ�������ǰ���ҳ�档
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError GoBack() = 0;

	/// \������������ڵ�����ʷ��¼��ͨ��web�ؼ���������һҳ�� 
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError GoForward() = 0;

	/// \���������¼���web���������ʾ�ĵ�ǰ�ĵ���
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError DoRefresh() = 0;

	/// \������ȡ�����й���ĵ�����̬Ԫ�أ��米�������Ͷ�����
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError DoStop() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif