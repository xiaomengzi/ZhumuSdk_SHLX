/*!
* \�ļ���customized_resource_helper_interface.h
* \�������Զ������ӿ�
* \ע�⣺�ڵ���ZHUMU_SDK_NAMESPACE::InitSDK()֮ǰ�������ȵ�����Щ�����������޷�������
*/
#ifndef _customiezed_resource_helper_interface_h
#define _customiezed_resource_helper_interface_h
#include "zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum SDKCustomizedStringType
\�������Զ����ַ������͡�
�����Ǹ���ϸ�Ľṹ������
\ע�⣺����Ҫ��ϸ�Ķ�ÿ�����͵����������밴�ոø�ʽ�Զ����Լ����ַ����������ʹ�ÿ��ܵ��²���Ԥ֪�ı�����
*/
enum SDKCustomizedStringType
{
	SDK_Customized_LiveStream_MenuString_LiveOn_String = 0,///<���ַ��������ԡ�%s���������Ա�˵��������ȷ��ʾ�����������ڶ���һ���ַ������滻ʵʱ��ý����%S�ϵĲ˵��
	SDK_Customized_LiveStream_MenuString_LiveView_String,///<���ַ��������ԡ�%s���������Ա�˵��������ȷ��ʾ�����������ڶ���һ���ַ������滻ʵʱ��ý����%S�ϵĲ˵�����ͼ����
	SDK_Customized_LiveStream_MenuString_LiveStop_String,///<���ַ��������Ǵ��ַ���������������ȷ��ʾ�����������ڶ���һ���ַ������滻ʵʱ��ý���ϵĲ˵���STOP LIVE STREAM��
	SDK_Customized_LiveStream_MenuString_CopyURL_String,///<���ַ��������Ǵ��ַ���������������ȷ��ʾ�����������ڶ���һ���ַ������滻ʵʱ��ý���ϵĲ˵���������ӡ�
	SDK_Customized_Title_App,	///<���ַ��������Ǵ��ַ���������������ȷ��ʾ�����������ڶ���һ���ַ������滻������ƵUI�ı��⡣
	SDK_Customized_Title_ZoomVideo,  ///<���ַ��������롰Zhumu Participant ID: %s Meeting ID: %s����ʽ��ͬ���Ա��ܹ���ȷ��ʾ�����������ڶ���һ���ַ������滻������ƵUI�ı��⡣
	SDK_Customized_Title_FreeZoomVideo, ///<���ַ��������롰Zhumu������ID:%s %d-Minutes Meeting ID:%s����ʽ��ͬ���Ա��ܹ���ȷ��ʾ�����������ڶ���һ���ַ����������û�Ϊ�����û��Ҵ��ڽ��޲鿴״̬ʱ�滻������ƵUI�ı��⡣
	SDK_Customized_Title_ViewOnly_ZoomVideo, ///<���ַ��������ԡ�%s����β���Ա���ȷ��ʾ�����������ڶ���һ���ַ������滻������ƵUI�ı��⡣
	SDK_Customized_Title_ViewOnly_FreeZoomVideo, ///<���ַ��������롰Zhumu %d-Minutes Meeting ID: %s����ʽ��ͬ���Ա���ȷ��ʾ�����������ڶ���һ���ַ����������û�Ϊ�����û��Ҵ��ڽ��޲鿴״̬ʱ�滻������ƵUI�ı��⡣
};

/*! \enum SDKCustomizedURLType
\�������Զ���URL����.
�����Ǹ���ϸ�Ľṹ������
\ע�⣺URL���뱣������������Ӧ�ð�����http����https����
*/
enum SDKCustomizedURLType
{
	SDKCustomizedURL_VITRULBG_HELP, ///<�ڡ����ⱳ����ѡ�ҳ���������Զ������URL��
	SDKCustomizedURL_VITRULBG_LEARN_MORE,///<�ڡ����ⱳ����ѡ�ҳ���������Զ����˽����URL��
	SDKCustomizedURL_SUPPORTURL, ///<�����ڻ����е�֧��URL��
};
class ICustomizedResourceHelper
{
public:
	///\����������Զ�����Ƭ�ļ���Ŀǰֻ֧��PNG��ʽ��
	///\������key_ ���Զ�����Դ��Ӧ����ԴID��
	///\������absolute_resource_path �Զ�����Դ�ļ���λ�ñ����Ǿ���·��������������׺���ļ�����
	/// \ע�⣺�����ڵ���֮ǰ�ȵ��ú���ZHUMU_SDK_NAMESPACE::InitSDK(), ����, ���������Ч.
	virtual SDKError AddCustomizedPictureResource(const wchar_t* key_, const wchar_t* absolute_resource_path) = 0;
	/// \������ʹ���Զ����ַ����滻ָ�����ַ����
	/// \������customizedType ָ���ַ�������. ������ϸ��Ϣ, �鿴 SDKCustomizedStringType enum.
	/// \������customizedString ָ���ַ���.
	/// \���أ���������ɹ����򷵻�ֵΪ SDKErr_Success.
	/// ����ʧ�ܡ�Ҫ��ȡ��չ�Ĵ�����Ϣ����μ� SDKError enum.
	/// \ע�⣺���customizedStringΪNULL���NULL��������Ϊ0���򷵻�ֵΪSDKERR_INVALID_PARAMETER.
	/// \ע�⣺�ڵ���ZHUMU_SDK_NAMESPACE::InitSDK()֮ǰ�������ȵ��øú���������˷�����Ч��
	virtual SDKError AddCustomizedStringResource(SDKCustomizedStringType customizedType, const wchar_t* customizedString) = 0;
	/// \������ʹ���Զ���URL�滻ָ����URL��
	/// \������customizedTypeָ��URL���͡��йظ�����Ϣ����μ� SDKCustomizedURLType enum.
	/// \������customizedUrlָ���Զ���URL�� 
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺���customizedUrlΪNULL���NULL��������Ϊ0(0)������ֵΪSDKERR_INVALID_PARAMETER��
	/// \ע�⣺�ڵ���ZHUMU_SDK_NAMESPACE::InitSDK()֮ǰ�������ȵ��øú���������˷�����Ч
	virtual SDKError AddCustomizedURLResource(SDKCustomizedURLType customizedType, const wchar_t* customizedUrl) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif
