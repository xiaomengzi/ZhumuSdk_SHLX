/*!
* \�ļ� customized_video_container.h
* \������zhumu �Զ�����Ƶ�ӿ�
*
*/
#ifndef ZHUMU_CUSTOMIZED_VIDEO_CONTAINER_H_
#define ZHUMU_CUSTOMIZED_VIDEO_CONTAINER_H_
#include "..\zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE

/*! \enum VideoRenderElementType
\������ ��Ƶ��ʾԪ�ص����͡�
����ϸ�Ľṹ������
*/
enum VideoRenderElementType
{
	VideoRenderElement_None, /// ��
	VideoRenderElement_PRVIEW, ///  IPreviewVideoRenderElement
	VideoRenderElement_ACTIVE, ///  IActiveVideoRenderElement
	VideoRenderElement_NORMAL, ///  INormalVideoRenderElement
};

/*! \enum VideoRenderDataType
\������ ��Ƶ��ʾԪ�ص��������͡�
����ϸ�Ľṹ������
*/
enum VideoRenderDataType
{
	VideoRenderData_None,/// ��
	VideoRenderData_Video,///��Ƶ����
	VideoRenderData_Avatar,/// avatar (����Ƶ����)
	VideoRenderData_ScreenName,/// screen name (����Ƶ����)
};

/// \��������ƵԪ�ؽӿڵĻ���
///
class IVideoRenderElement
{
public:
	/// \��������ȡ��Ƶ��Ⱦ�����͡�
	/// \���أ���������ɹ�������ֵ���ǳ���Ⱦ���͡��ο�VideoRenderElementType
	/// �������ʧ�ܣ�����ֵ��VideoRenderElement_None��
	virtual VideoRenderElementType GetType() = 0;

	/// \������������Ƶ��ȾԪ�صĿͻ�����������ꡣ
	/// \���أ����տͻ�������ľ��νṹ��
	/// ���������������Ƶ�����Ŀͻ�����������Ͻ�
	virtual RECT     GetPos() = 0;

	/// \������������Ƶ��Ⱦ�Ŀͻ��������λ�á�
	/// \������pos ָ����Ƶ�ڿͻ����ϵ���Ⱦ������λ�á�
	virtual SDKError SetPos(RECT pos) = 0;

	/// \��������ʾ��Ƶ
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError Show() = 0;

	/// \������������Ƶ
	///�������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError Hide() = 0;

	/// \��������ȡ��ƵԪ�ص��û�id��
	/// \���أ�ָ�����ڲ鿴�û����û�id��
	virtual unsigned int GetCurrentRenderUserId() = 0;

	/// \��������ȡ��ƵԪ�ص��������͡�
	/// \���أ���ƵԪ�ص��������͡�
	virtual VideoRenderDataType GetCurrentRenderDataType() = 0;

	/// \���������û���������Ƶ����ʾ��Ļ���ơ�
	/// \������enable_show ���û�����
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError EnableShowScreenNameOnVideo(bool enable_show) = 0;
	virtual ~IVideoRenderElement() {}
};

/// \������Ԥ����Ƶ����(��ǰ)
/// 
class IPreviewVideoRenderElement : public IVideoRenderElement
{
public:
	/// \������ ��ʼԤ��
	virtual SDKError Start() = 0;

	/// \������ ֹͣԤ��
	virtual SDKError Stop() = 0;
	virtual ~IPreviewVideoRenderElement() {}
};

/// \������������Ƶ����(������)
/// 
class IActiveVideoRenderElement : public IVideoRenderElement
{
public:
	/// \��������ʼ�鿴��û�����Ƶ/ͷ��/��Ļ��������
	virtual SDKError Start() = 0;

	/// \������ֹͣ�鿴��û�����Ƶ/ͷ��/��Ļ��������
	virtual SDKError Stop() = 0;
	virtual ~IActiveVideoRenderElement() {}
};

/// \��������ͨ��Ƶ����(������)
/// 
class INormalVideoRenderElement : public IVideoRenderElement
{
public:
	/// \�����������û�����Ƶ/ͷ��/��Ļ��������
	/// \������userid ָ��Ҫ�鿴���û�
	virtual SDKError Subscribe(unsigned int userid) = 0;

	/// \������ȡ�������û�����Ƶ/ͷ��/��Ļ��������
	/// \������userid ָ��Ҫȡ�����ĵ��û�
	/// ��������л��������û���ֻ��ʹ�������û�id����Subscribe
	/// ������������ƵԪ�أ���������API֮ǰ���ô�API
	virtual SDKError Unsubscribe(unsigned int userid) = 0;
	virtual ~INormalVideoRenderElement() {}
};

/// \��������Ƶ�����ص��¼�
///
class ICustomizedVideoContainerEvent
{
public:
	/// \������֪ͨӦ�ó�����ʾ��Ƶ���û�id����
	/// \������pElement ָ���������ĸ���Ƶ���û�id 
	/// \������userid ��ʾ��Ƶ�����û�id 
	virtual void onRenderUserChanged(IVideoRenderElement* pElement, unsigned int userid) = 0;

	/// \������֪ͨӦ�ó�����Ƶ�������͸���
	/// \param pElement ָ���ĸ���Ƶ���������͸�����
	/// \param dataType �µ���Ƶ��������
	virtual void onRenderDataTypeChanged(IVideoRenderElement* pElement, VideoRenderDataType dataType) = 0;

	/// \������֪ͨӦ�ó�����Ƶ���ڵĴ�С�仯
	/// ���յ�����Ϣʱ����Ҫ������Ƶ������������ƵԪ��
	/// \������rc �������εĿͻ������������Ƶ����λ�ã�����ڸ����ڵĿͻ�����������Ͻǡ� 
	virtual void onLayoutNotification(RECT wnd_client_rect) = 0;

	/// \������֪ͨӦ�ó��������Ƶ��ȾԪ�ر����ٵ���Ϣ
	/// \������pElement ָ��Ҫ�����ĸ�������Ƶ
	virtual void onVideoRenderElementDestroyed(IVideoRenderElement* pElement) = 0;

	/// \����������Ϣ��Ϣ���ݸ�app����Ϣ�б����£�
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

/// \������ Video container interface
///
class ICustomizedVideoContainer
{
public:
	/// \������������Ƶ�����ص��¼�
	/// \������pEvent ָ�������Ƶ�����¼���ICustomizedVideoContainerEvent*��ָ�롣
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(ICustomizedVideoContainerEvent* pEvent) = 0;

	/// \������������Ƶ��Ⱦ�ӿ�
	/// \������ppElement һ��ָ��IVideoRenderElement*��ָ�룬������IVideoRenderElement����
	/// \������type_ IVideoRenderElement������
	/// \���أ���������ɹ�������ֵΪSDKErr_Success, ppEmbeddedBrowser��Ϊ��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CreateVideoElement(IVideoRenderElement** ppElement, VideoRenderElementType type_) = 0;

	/// \������������Ƶ��ȾԪ�ؽ���
	/// \������ppElement ָ��Ҫ���ٵ�IVideoRenderElement��ָ�롣
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError DestroyVideoElement(IVideoRenderElement* ppElement) = 0;

	/// \����������������Ƶ��ȾԪ��
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError DestroyAllVideoElement() = 0;

	/// \��������ʾ��Ƶ����
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError Show() = 0;

	/// \������������Ƶ����
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError Hide() = 0;

	/// \������������Ƶ�����Ĵ�С
	/// \������rc ���������εĿͻ������꣬����ڸ����ڵĿͻ�����������Ͻǡ�
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError Resize(RECT rc) = 0;

	/// \��������ȡ��Ƶ��������ƵԪ���б�
	/// \���أ���������ɹ�������ֵ��videoԪ���б�
	/// �������ʧ�ܣ�����ֵΪNULL��
	virtual std::vector<IVideoRenderElement* >* GetVideoElementList() = 0;

	virtual ~ICustomizedVideoContainer() {}
};
END_ZHUMU_SDK_NAMESPACE
#endif