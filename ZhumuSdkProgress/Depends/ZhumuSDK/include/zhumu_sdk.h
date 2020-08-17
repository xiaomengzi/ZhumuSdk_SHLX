/*!
* 文件： zhumu_sdk.h
* 描述： Zhumu Windows SDK
* 
*/

#ifndef _ZHUMU_SDK_H_
#define _ZHUMU_SDK_H_
#include "zhumu_sdk_def.h"

/// \brief Zhumu SDK Namespace

BEGIN_ZHUMU_SDK_NAMESPACE
extern "C"
{
	class IMeetingService;
	class IAuthService;
	class ISettingService;
	class ICalenderService;
	class IPreMeetingService;
	class INetworkConnectionHelper;

	/************************************************************************/
	//  描述：初始化 Zhumu SDK
	//	参数：初始化 Zhumu SDK 参数
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_InitSDK(InitParam& initParam);

	/************************************************************************/
	//  描述：创建会议服务接口
	//	参数：指向IMeetingService*实例的指针
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CreateMeetingService(IMeetingService** ppMeetingService);

	/************************************************************************/
	//  描述：销毁会议服务接口
	//	参数：无
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_DestroyMeetingService(IMeetingService* pMeetingService);

	/************************************************************************/
	//  描述：创建认证服务接口
	//	参数：指向IAuthService*实例的指针
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CreateAuthService(IAuthService** ppAuthService);

	/************************************************************************/
	//  描述：销毁认证服务接口
	//	参数：无
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_DestroyAuthService(IAuthService* pAuthService);

	/************************************************************************/
	//  描述：创建设置服务接口
	//	参数：指向IAuthService*实例的指针
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CreateSettingService(ISettingService** ppSettingService);

	/************************************************************************/
	//  描述：销毁设置服务接口
	//	参数：无
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_DestroySettingService(ISettingService* pSettingService);

	/************************************************************************/
	//  描述：创建日历服务接口
	//	参数：指向IAuthService*实例的指针
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CreateCalenderService(ICalenderService** ppCalenderService);

	/************************************************************************/
	//  描述：销毁日历服务接口
	//	参数：无
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_DestroyCalenderService(ICalenderService* pCalenderService);

	/************************************************************************/
	//  描述：创建会前服务接口
	//	参数：指向IPreMeetingService*实例的指针
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CreatePreMeetingService(IPreMeetingService** ppPreMeetingService);

	/************************************************************************/
	//  描述：销毁会前服务接口
	//	参数：无
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_DestroyPreMeetingService(IPreMeetingService* pPreMeetingService);

	/************************************************************************/
	//  描述：创建网络连接帮助类服务接口
	//	参数：指向IPreMeetingService*实例的指针
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CreateNetworkConnectionHelper(INetworkConnectionHelper** ppNetworkHelper);

	/************************************************************************/
	//  描述：销毁网络连接帮助类服务接口
	//	参数：无
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_DestroyNetworkConnectionHelper(INetworkConnectionHelper* pNetworkHelper);

	/************************************************************************/
	//  描述：注销Zhumu SDK
	//	参数：无
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CleanUPSDK();

	/************************************************************************/
	//  描述：获取 Zhumu SDK 版本信息
	//	参数：无
	//	返回值：调用成功返回SDKErr_Success, 否则返回其他SDKErr（枚举）错误信息
	/************************************************************************/
	ZHUMU_SDK_API const wchar_t* Zhumu_GetVersion();

}

END_ZHUMU_SDK_NAMESPACE
#endif