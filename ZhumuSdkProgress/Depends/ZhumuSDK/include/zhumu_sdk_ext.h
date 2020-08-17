/*!
* \file zhumu_sdk_ext.h
* \brief  ZHUMU SDK Embedded Browser Interface.
* 
*/

#ifndef _ZHUMU_SDK_EXT_H_
#define _ZHUMU_SDK_EXT_H_
#include "zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
extern "C"
{
	class IEmbeddedBrowser;
	class IUIHooker;
	class ICustomizedResourceHelper;
	/// \brief Create an embedded browser interface.
	/// \param ppEmbeddedBrowser An object pointer to the IEmbeddedBrowser*. 
	/// \param hwnd The handle of the window in which the browser object is embedded. 
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppEmbeddedBrowser is not NULL
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	ZHUMU_SDK_API SDKError CreateEmbeddedBrowser(IEmbeddedBrowser** ppEmbeddedBrowser, HWND hwnd);

	/// \brief Destroy the embedded browser interface.
	/// \param pEmbeddedBrowser A pointer to the IEmbeddedBrowser to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	ZHUMU_SDK_API SDKError DestroyEmbeddedBrowser(IEmbeddedBrowser* pEmbeddedBrowser);

	/// \brief Retrieve user Hooker interface.
	/// \param ppUIHooker A pointer to the IUIHooker*. 
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppEmbeddedBrowser is not NULL
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	ZHUMU_SDK_API SDKError RetrieveUIHooker(IUIHooker** ppUIHooker);

	/// \brief Retrieve customized resource helper interface.
	/// \param ppCustomiezedResourceHelper A pointer to the ICustomizedResourceHelper*. 
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppCustomiezedResourceHelper is not NULL
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	ZHUMU_SDK_API SDKError RetrieveCustomizedResourceHelper(ICustomizedResourceHelper** ppCustomiezedResourceHelper);
}

END_ZHUMU_SDK_NAMESPACE
#endif