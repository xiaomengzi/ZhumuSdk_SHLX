/*!
* \�ļ��� zhumu_customized_ui.h
* \������ zhumu �Զ���UI�ӿ�
*
*/
#ifndef ZHUMU_CUSTOMIZED_UI_H_
#define ZHUMU_CUSTOMIZED_UI_H_
#include "..\zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
class ICustomizedUIMgr;
extern "C"
{
	/// \�����������Զ���UI�������ӿ�.
	/// \������ppCustomizedUIMgr һ���������óɹ����ò������洢ָ��ICustomizedUIMgr*��ָ�롣 
	/// \���أ���������ɹ�������ֵΪSDKErr_Success����ppCustomizedUIMgr�ķ���ֵ����NULL
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ�SDKError enum��
	ZHUMU_SDK_API SDKError CreateCustomizedUIMgr(ICustomizedUIMgr** ppCustomizedUIMgr);

	/// \����������ָ�����Զ���UI�������ӿڡ�
	/// \������pCustomizedUIMgr ָ��Ҫ���ٵ�ICustomizedUIMgr��ָ�롣
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ�SDKError enum��
	ZHUMU_SDK_API SDKError DestroyCustomizedUIMgr(ICustomizedUIMgr* pCustomizedUIMgr);
}

END_ZHUMU_SDK_NAMESPACE
#endif