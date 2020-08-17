/*!
* \文件zhumu_sdk_def.h
* \描述：SDK utility Definition of Zhumu windows.
*/

#ifndef _ZHUMU_SDK_UTIL_DEFINE_H_
#define _ZHUMU_SDK_UTIL_DEFINE_H_
#include "zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
class ICameraControllerEvent
{
public:	
	/// 控制器状态改变回调事件
	virtual void onControllerStatusChanged(bool valid) = 0;
};
class ICameraController
{
public:
	/// 设置摄像头控制事件.
	virtual ~ICameraController(){}
	virtual SDKError SetEvent(ICameraControllerEvent* pEvent) = 0;
	virtual bool	 IsValid() = 0;
	
	/// 调整摄像头：左转.
	virtual SDKError BeginTurnLeft() = 0;
	virtual SDKError ContinueTurnLeft() = 0;
	virtual SDKError EndTurnLeft() = 0;

	/// 调整摄像头：右转.
	virtual SDKError BeginTurnRight() = 0;
	virtual SDKError ContinueTurnRight() = 0;
	virtual SDKError EndTurnRight() = 0;

	/// 调整摄像头：抬头.
	virtual SDKError BeginTurnUp() = 0;
	virtual SDKError ContinueTurnUp() = 0;
	virtual SDKError EndTurnUp() = 0;

	/// 调整摄像头：低头.
	virtual SDKError BeginTurnDown() = 0;
	virtual SDKError ContinueTurnDown() = 0;
	virtual SDKError EndTurnDown() = 0;

	/// 调整摄像头：变焦相机，移动摄像头角度贴近用户
	virtual SDKError BeginZoomIn() = 0;
	virtual SDKError ContinueZoomIn() = 0;
	virtual SDKError EndZoomIn() = 0;

	/// 调整摄像头：变焦相机，移动摄像头角度远离用户
	virtual SDKError BeginZoomOut() = 0;
	virtual SDKError ContinueZoomOut() = 0;
	virtual SDKError EndZoomOut() = 0;

	/// 判断摄像头是否能被控制
	virtual SDKError CanControlCamera(bool& bCan) = 0;
};
END_ZHUMU_SDK_NAMESPACE

#endif