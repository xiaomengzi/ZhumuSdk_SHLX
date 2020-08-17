/*!
* \文件； zhumu_customized_ui.h
* \描述： zhumu 自定义UI接口
*
*/
#ifndef ZHUMU_CUSTOMIZED_UI_H_
#define ZHUMU_CUSTOMIZED_UI_H_
#include "..\zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
class ICustomizedUIMgr;
extern "C"
{
	/// \描述：创建自定义UI管理器接口.
	/// \参数：ppCustomizedUIMgr 一旦函数调用成功，该参数将存储指向ICustomizedUIMgr*的指针。 
	/// \返回：如果函数成功，返回值为SDKErr_Success，而ppCustomizedUIMgr的返回值不是NULL
	/// 否则失败。要获得扩展的错误信息，请参见SDKError enum。
	ZHUMU_SDK_API SDKError CreateCustomizedUIMgr(ICustomizedUIMgr** ppCustomizedUIMgr);

	/// \描述：销毁指定的自定义UI管理器接口。
	/// \参数：pCustomizedUIMgr 指向要销毁的ICustomizedUIMgr的指针。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见SDKError enum。
	ZHUMU_SDK_API SDKError DestroyCustomizedUIMgr(ICustomizedUIMgr* pCustomizedUIMgr);
}

END_ZHUMU_SDK_NAMESPACE
#endif