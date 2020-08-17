/*!
* \�ļ�zhumu_sdk_def.h
* \������SDK utility Definition of Zhumu windows.
*/

#ifndef _ZHUMU_SDK_UTIL_DEFINE_H_
#define _ZHUMU_SDK_UTIL_DEFINE_H_
#include "zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
class ICameraControllerEvent
{
public:	
	/// ������״̬�ı�ص��¼�
	virtual void onControllerStatusChanged(bool valid) = 0;
};
class ICameraController
{
public:
	/// ��������ͷ�����¼�.
	virtual ~ICameraController(){}
	virtual SDKError SetEvent(ICameraControllerEvent* pEvent) = 0;
	virtual bool	 IsValid() = 0;
	
	/// ��������ͷ����ת.
	virtual SDKError BeginTurnLeft() = 0;
	virtual SDKError ContinueTurnLeft() = 0;
	virtual SDKError EndTurnLeft() = 0;

	/// ��������ͷ����ת.
	virtual SDKError BeginTurnRight() = 0;
	virtual SDKError ContinueTurnRight() = 0;
	virtual SDKError EndTurnRight() = 0;

	/// ��������ͷ��̧ͷ.
	virtual SDKError BeginTurnUp() = 0;
	virtual SDKError ContinueTurnUp() = 0;
	virtual SDKError EndTurnUp() = 0;

	/// ��������ͷ����ͷ.
	virtual SDKError BeginTurnDown() = 0;
	virtual SDKError ContinueTurnDown() = 0;
	virtual SDKError EndTurnDown() = 0;

	/// ��������ͷ���佹������ƶ�����ͷ�Ƕ������û�
	virtual SDKError BeginZoomIn() = 0;
	virtual SDKError ContinueZoomIn() = 0;
	virtual SDKError EndZoomIn() = 0;

	/// ��������ͷ���佹������ƶ�����ͷ�Ƕ�Զ���û�
	virtual SDKError BeginZoomOut() = 0;
	virtual SDKError ContinueZoomOut() = 0;
	virtual SDKError EndZoomOut() = 0;

	/// �ж�����ͷ�Ƿ��ܱ�����
	virtual SDKError CanControlCamera(bool& bCan) = 0;
};
END_ZHUMU_SDK_NAMESPACE

#endif