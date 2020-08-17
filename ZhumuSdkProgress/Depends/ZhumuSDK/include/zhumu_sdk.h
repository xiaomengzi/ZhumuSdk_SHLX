/*!
* �ļ��� zhumu_sdk.h
* ������ Zhumu Windows SDK
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
	//  ��������ʼ�� Zhumu SDK
	//	��������ʼ�� Zhumu SDK ����
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_InitSDK(InitParam& initParam);

	/************************************************************************/
	//  �����������������ӿ�
	//	������ָ��IMeetingService*ʵ����ָ��
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CreateMeetingService(IMeetingService** ppMeetingService);

	/************************************************************************/
	//  ���������ٻ������ӿ�
	//	��������
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_DestroyMeetingService(IMeetingService* pMeetingService);

	/************************************************************************/
	//  ������������֤����ӿ�
	//	������ָ��IAuthService*ʵ����ָ��
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CreateAuthService(IAuthService** ppAuthService);

	/************************************************************************/
	//  ������������֤����ӿ�
	//	��������
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_DestroyAuthService(IAuthService* pAuthService);

	/************************************************************************/
	//  �������������÷���ӿ�
	//	������ָ��IAuthService*ʵ����ָ��
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CreateSettingService(ISettingService** ppSettingService);

	/************************************************************************/
	//  �������������÷���ӿ�
	//	��������
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_DestroySettingService(ISettingService* pSettingService);

	/************************************************************************/
	//  ������������������ӿ�
	//	������ָ��IAuthService*ʵ����ָ��
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CreateCalenderService(ICalenderService** ppCalenderService);

	/************************************************************************/
	//  ������������������ӿ�
	//	��������
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_DestroyCalenderService(ICalenderService* pCalenderService);

	/************************************************************************/
	//  ������������ǰ����ӿ�
	//	������ָ��IPreMeetingService*ʵ����ָ��
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CreatePreMeetingService(IPreMeetingService** ppPreMeetingService);

	/************************************************************************/
	//  ���������ٻ�ǰ����ӿ�
	//	��������
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_DestroyPreMeetingService(IPreMeetingService* pPreMeetingService);

	/************************************************************************/
	//  �����������������Ӱ��������ӿ�
	//	������ָ��IPreMeetingService*ʵ����ָ��
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CreateNetworkConnectionHelper(INetworkConnectionHelper** ppNetworkHelper);

	/************************************************************************/
	//  �����������������Ӱ��������ӿ�
	//	��������
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_DestroyNetworkConnectionHelper(INetworkConnectionHelper* pNetworkHelper);

	/************************************************************************/
	//  ������ע��Zhumu SDK
	//	��������
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API SDKError Zhumu_CleanUPSDK();

	/************************************************************************/
	//  ��������ȡ Zhumu SDK �汾��Ϣ
	//	��������
	//	����ֵ�����óɹ�����SDKErr_Success, ���򷵻�����SDKErr��ö�٣�������Ϣ
	/************************************************************************/
	ZHUMU_SDK_API const wchar_t* Zhumu_GetVersion();

}

END_ZHUMU_SDK_NAMESPACE
#endif