/*!
* \�ļ� customized_annotation.h
* \������zhumu�Զ����ע����ӿ�
*
*/
#ifndef ZHUMU_CUSTOMIZED_ANNOTATION_H_
#define ZHUMU_CUSTOMIZED_ANNOTATION_H_
#include "..\zhumu_sdk_def.h"
#include "..\meeting_service_components\meeting_annotation_interface.h"

BEGIN_ZHUMU_SDK_NAMESPACE
class ICustomizedShareRender;

/*! \enum CustomizedShareAnnotationStatus
\��������ע״̬
����ϸ�Ľṹ������
*/
enum CustomizedShareAnnotationStatus
{
	CS_ANNO_READYTOUSE,//׼��ʹ�ñ�ע
	CS_ANNO_CLOSE, //��ע�ر�
};

/// \��������ע����ص��¼�
///
class ICustomizedAnnotationObjEvent
{
public:
	/// \������֪ͨӦ�ó�����ڱ�ע���ߵĸ���
	virtual void onAnnotationObjToolChange(ZhumuSDK::AnnotationToolType type_) = 0;
};

/// \��������ע����ӿ�
///
class ICustomizedAnnotationObj
{
public:
	/// \���������ñ�ע����ص��¼�
	/// \������pEvent ָ����ձ�ע�����¼���ICustomizedAnnotationObjEvent*��ָ�롣
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(ICustomizedAnnotationObjEvent* event_) = 0;

	/// \����������������ע
	/// \������type �����ע������
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CanClear(AnnotationClearType type) = 0;

	/// \�����������ע
	/// \������type �����ע������
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError Clear(AnnotationClearType type) = 0;

	/// \���������ñ�ע����
	/// \������type ��ע��������
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetTool(AnnotationToolType type) = 0;

	/// \���������ñ�ע���ߵ���ɫ
	/// \������color ��ע���ߵ���ɫ
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetColor(unsigned long color) = 0;

	/// \���������ñ�ע�߿�
	/// \������lineWidth ��ע�����߿�
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetLineWidth(long lineWidth) = 0;

	/// \��������ȡ��ע������ɫ
	/// \������color ��ǰ��ע���ߵ���ɫ
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError GetCurColor(unsigned long& color) = 0;

	/// \��������ȡ��ע���ߵ��߿�
	/// \������lineWidth the current line width of annotation tool
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError GetCurLineWidth(long& lineWidth) = 0;

	/// \��������ȡ��ע���ߵ�����
	/// \������type ��ע���ߵ�����
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError GetCurTool(AnnotationToolType& type) = 0;

	/// \������ȡ����ע
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError Undo() = 0;

	/// \�������ظ��ϴβ���
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError Redo() = 0;

	/// \����������Ƿ񱣴����
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CanSaveSnapshot() = 0;

	/// \�������������
	/// \������path ����·��
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SaveSnapshot(const wchar_t* path) = 0;

	/// \brief Determine if can do annotate.
	/// \param [out] bCan, true means can do annotate, false can not. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanDoAnnotation(bool& bCan) = 0;

	/// \brief Determine whether annotations are currently available.
	/// \return true available, false invalid.
	virtual bool IsAnnoataionDisable() = 0;

	virtual ~ICustomizedAnnotationObj(){};


};

/// \������ ��ע�������ص��¼�
///
class ICustomizedAnnotationControllerEvent
{
public:
	/// \������֪ͨӦ�ó����ע�����ѱ�����
	/// \������obj_ ָ�������ĸ���ע����
	virtual void onCustomizedAnnotationObjDestroyed(ICustomizedAnnotationObj* obj_) = 0;

	/// \������֪ͨӦ�ó����ע״̬�Ѹ���
	/// \������share_render_ ָ���������ĸ�������ֵı�ע״̬
	/// \������status_ status
	virtual void onSharingShareAnnotationStatusChanged(ICustomizedShareRender* share_render_, CustomizedShareAnnotationStatus status_) = 0;
};

/// \������ ��ע�������ӿ�
///
class ICustomizedAnnotationController
{
public:
	/// \��������hi��ע�������ص��¼�
	/// \������pEvent ָ����ձ�ע�������¼���ICustomizedAnnotationControllerEvent*��ָ�롣 
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(ICustomizedAnnotationControllerEvent* event_) = 0;

	/// \������������ע����
	/// \������view_share_render ָ����ע����������ߣ�����������ڿ�ʼ�����ע�ͣ��򴫵�NULL��
	/// \������pp_obj һ��ָ��ICustomizedAnnotationObj*��ָ�룬��ָ�����ICustomizedAnnotationObj����
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \when you got onSharingShareAnnotationStatusChanged with CS_ANNO_READYTOUSE.
	virtual SDKError CreateAnnoObj(ICustomizedShareRender* view_share_render, ICustomizedAnnotationObj** pp_obj) = 0;

	/// \�������ݻ�ע�Ͷ���
	/// \������anno_obj ָ��Ҫ���ٵ�ICustomizedAnnotationObj��ָ�롣
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError DestroyAnnoObj(ICustomizedAnnotationObj* anno_obj) = 0;
	virtual ~ICustomizedAnnotationController() {};
};
END_ZHUMU_SDK_NAMESPACE
#endif