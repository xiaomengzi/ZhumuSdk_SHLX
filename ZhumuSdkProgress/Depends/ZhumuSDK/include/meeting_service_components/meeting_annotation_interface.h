/*!
* \�ļ��� meeting_annotation_interface.h
* \������ �����ע����ӿ�
*
*/
#ifndef ZHUMU_MEETING_Annotation_INTERFACE_H_
#define ZHUMU_MEETING_Annotation_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include "..\meeting_service_interface.h"
/// \����: Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum AnnotationToolType
\��������ע��������.
�����Ǹ���ϸ�Ľṹ����
*/
enum AnnotationToolType
{
	ANNOTOOL_NONE_DRAWING,///<�л������

	ANNOTOOL_PEN,///<����.
	ANNOTOOL_HIGHLIGHTER,///<����.
	ANNOTOOL_AUTO_LINE,///<ֱ�߻��������ָ����ƶ����Զ��ı䡣
	ANNOTOOL_AUTO_RECTANGLE,///<���λ��������ָ����ƶ����Զ��ı䡣
	ANNOTOOL_AUTO_ELLIPSE,///<��Բ�����������ƶ����Զ��ı�
	ANNOTOOL_AUTO_ARROW,///<��ͷ�����������ƶ����Զ��ı䡣
	ANNOTOOL_AUTO_RECTANGLE_FILL,///<������
	ANNOTOOL_AUTO_ELLIPSE_FILL,///<�����Բ
	ANNOTOOL_SPOTLIGHT,///<�����
	ANNOTOOL_ARROW,///<��ʾ����������ݵ��˵������ϵļ�ͷ��
	ANNOTOOL_ERASER,///<��Ƥ��.

	ANNOTOOL_TEXTBOX, ///<�����ı������.
	ANNOTOOL_PICKER, ///<ѡ���ע.
	ANNOTOOL_AUTO_RECTANGLE_SEMI_FILL, ///<�����������ƶ����Զ��ı�ľ��Ρ�.
	ANNOTOOL_AUTO_ELLIPSE_SEMI_FILL, ///<�����������ƶ����Զ��ı�ľ��ȵ���Բ.
	ANNOTOOL_AUTO_DOUBLE_ARROW, ///<����˫��ͷ����. 
	ANNOTOOL_AUTO_DIAMOND, ///<���ĵ�����.
	ANNOTOOL_AUTO_STAMP_ARROW, ///<���ڱ�ǵĹ̶���С�ļ�ͷ.
	ANNOTOOL_AUTO_STAMP_CHECK, ///<�����ȷ�ı�־.
	ANNOTOOL_AUTO_STAMP_X, ///<��Ǵ���ı�־.
	ANNOTOOL_AUTO_STAMP_STAR, ///<����õ������
	ANNOTOOL_AUTO_STAMP_HEART, ///<����õ�����
	ANNOTOOL_AUTO_STAMP_QM, ///<�ʺ�.
};

/*! \enum AnnotationClearType
\����: �������.
����ϸ�Ľṹ����
*/
enum AnnotationClearType
{
	ANNOCLEAR_ALL,
	ANNOCLEAR_SELF,
	ANNOCLEAR_OTHER,
};

/// \��������ʾע��״̬���ĵĻص��ӿ�.
class IMeetingAnnotationSupportEvent
{
public:
	/// \�������������ʾ������/���ò�����ע�ͣ�SDK�������˻ص�										
	virtual void onSupportAnnotationStatus(unsigned int userid, bool bSupportAnnotation) = 0;
};

class ICustomizedAnnotationController;
/// \�����������ע���߽ӿ�.
///
class IAnnotationController
{
public:
	/// \����������ע��״̬���ĵĻص�. 
	/// \������pEvent һ��ָ��IMeetingAnnotationSupportEvent�Ķ���ָ�룬�����ձ�ע״̬�ı�ص��¼���
	/// \���أ�����û�ӵ��Ȩ�ޣ��򷵻�ֵΪSDKErr_Success��
	/// ���򷵻�����������Ϣ��Ҫ��ȡ��չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError SetEvent(IMeetingAnnotationSupportEvent* pEvent) = 0;

	/// \������ȷ���ڵ�ǰ�����ڼ��Ƿ������ָ����ͼ�ı�ע���ߡ�
	/// \������viewtype ָ��Ҫȷ������ͼ���й���ϸ��Ϣ����μ� SDKViewType enum��
	/// \���أ�FALSE ��ʾ���ã�TRUE��ʾ���á�
	/// \ע�⣺������zhumu�����û��Զ������ģʽ��
	virtual bool IsAnnoataionDisable(SDKViewType viewtype = SDK_FIRST_VIEW) = 0;

	/// \��������ʼ��ע
	/// \������viewtype ָ��Ҫ���õ���ͼ����һ�����������ǵڶ�����������
	/// \������left ָ����ע�������λ�á�
	/// \������top ָ����ע���Ķ���λ��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��������zhumu�����û�����ģʽ
	virtual SDKError StartAnnotation(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, int left, int top) = 0;

	/// \������ֹͣ��ǰ��ע
	/// \������viewtype ָ��Ҫ���õ���ͼ����һ�����������ǵڶ���������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��������zhumu�����û�����ģʽ
	virtual SDKError StopAnnotation(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype) = 0;

	/// \���������ñ�ע����
	/// \������viewtype ָ��Ҫ���õ���ͼ����һ�����������ǵڶ�����������
	/// \������type ���ڱ�ע�������͵Ĳ�������ο�AnnotationToolType�� 
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��������zhumu�����û�����ģʽ
	virtual SDKError SetTool(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, AnnotationToolType type) = 0;

	/// \�����������ע
	/// \������viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \������ type The parameter to be used for annotation earse operator type, refer to AnnotationClearType. 
	/// \���أ�If the function succeeds, the return value is SDKErr_Success.
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��������zhumu�����û�����ģʽ
	virtual SDKError Clear(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, AnnotationClearType type) = 0;


	/// \���������ñ�ע��ɫ
	/// \������viewtype ָ��Ҫ���õ���ͼ����һ�����������ǵڶ�����������
	/// \������color ����ע����ɫ��ABGR��ʽ�Ĳ�����
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��������zhumu�����û�����ģʽ
	virtual SDKError SetColor(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, unsigned long color) = 0;

	/// \���������ñ�ע�߿�
	/// \������viewtype ָ��Ҫ���õ���ͼ����һ�����������ǵڶ�����������
	/// \����������ע���еĿ�ȵĲ�����
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��������zhumu�����û�����ģʽ
	virtual SDKError SetLineWidth(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, long lineWidth) = 0;

	/// \������ȡ����ע
	/// \������viewtype ָ��Ҫ���õ���ͼ����һ�����������ǵڶ�����������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��������zhumu�����û�����ģʽ
	virtual SDKError Undo(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype) = 0;

	/// \�������ָ���ע
	/// \������viewtype ָ��Ҫ���õ���ͼ����һ�����������ǵڶ�����������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��������zhumu�����û�����ģʽ
	virtual SDKError Redo(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype) = 0;

	/// \��������ȡ�����Զ���uiģʽ��ע�Ϳ�����
	/// \����: ��������ɹ�������ֵΪ�Զ���uiģʽ��annotation controller�ӿڡ�
	/// �������ʧ�ܣ�����ֵΪNULL��
	/// \���������Զ������uiģʽ
	virtual ICustomizedAnnotationController* GetCustomizedAnnotationController() = 0;

	/// \������������/����������ڲ鿴��������ʱ����ע�͡�
	/// \������[in] viewtype: SDK_FIRST_VIEW/SDK_SECOND_VIEW
	/// \������[in] disable TRUE ��ʾ����, FALSE ��ʾ����.
	/// \���أ�����û�ӵ��Ȩ�ޣ��򷵻�ֵΪSDKErr_Success��
	///���򷵻�����������Ϣ��Ҫ��ȡ��չ�Ĵ�����Ϣ����μ�\link SDKError \endlink enum��
	virtual SDKError DisableViewerAnnotation(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, bool bDisable) = 0;

	/// \������ȷ���ۿ��ߵ�ע����Ȩ�Ƿ񱻽��á�
	/// \������[in] viewtype: SDK_FIRST_VIEW/SDK_SECOND_VIEW
	/// \������[out] bDisabled TRUE ��ʾ����, FALSE ��ʾ����. ֻ�ڷ���ֵΪSDKErr_Successʱ��Ч 
	/// \���أ�����û�ӵ��Ȩ�ޣ��򷵻�ֵΪSDKErr_Success��
	///���򷵻�����������Ϣ����Ҫ��ȡ��չ�Ĵ�����Ϣ����μ�\link SDKError \endlink enum��
	virtual SDKError IsViewerAnnotationDisabled(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, bool& bDisabled) = 0;

	/// \����: ȷ���Ƿ�����ۿ��߽��б�ע 
	/// \������[in] viewtype: SDK_FIRST_VIEW/SDK_SECOND_VIEW
	/// \������[out] bCan TRUE ��ʾ����, FALSE ��ʾ����. ֻ�ڷ���ֵΪSDKErr_Successʱ��Ч  
	/// \����: ����û�ӵ��Ȩ�ޣ��򷵻�ֵΪSDKErr_Success��
	///���򷵻�����������Ϣ��Ҫ��ȡ��չ�Ĵ�����Ϣ����μ�\link SDKError \endlink enum��
	virtual SDKError CanDisableViewerAnnotation(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, bool& bCan) = 0;

	/// \������ȷ�����Ƿ��ܹ�ע��(��ʾ�ߺ͹ۿ��߶����Ե��øú���)��
	/// \������[in] viewtype: SDK_FIRST_VIEW/SDK_SECOND_VIEW
	/// \������[out] bCan TRUE ��ʾ����, FALSE ��ʾ����. ֻ�ڷ���ֵΪSDKErr_Successʱ��Ч  
	/// \����: ����û�ӵ��Ȩ�ޣ��򷵻�ֵΪSDKErr_Success��
	///���򷵻�����������Ϣ��Ҫ��ȡ��չ�Ĵ�����Ϣ����μ�\link SDKError \endlink enum��
	virtual SDKError CanDoAnnotation(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, bool& bCan) = 0;

};
END_ZHUMU_SDK_NAMESPACE
#endif