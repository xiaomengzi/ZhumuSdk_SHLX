/*!
* \文件：direct_share_service_helper_interface.h
* \描述：直接共享服务帮助接口
*
*/
#ifndef ZHUMU_DIRECT_SHARE_SERVICE_HELPER_INTERFACE_H_
#define ZHUMU_DIRECT_SHARE_SERVICE_HELPER_INTERFACE_H_
#include "zhumu_sdk_def.h"
/// \brief Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*
typedef enum DirectShareStatusType_Enum
{
DirectShare_Unknown = 0,
DirectShare_In_SIP_Call,
//DirectShare_Called_Too_Frequency, //move it to return value as SDKERR_TOO_FREQUENT_CALL
DirectShare_Start_Connecting,
DirectShare_UltraSound_Detect_Failed,
DirectShare_Need_MeetingID_Or_ParingCode,
DirectShare_AccountID_Not_Same,
DirectShare_NetWork_Error,
DirectShare_Target_Version_Old,
DirectShare_Direct_Share_Start,
DirectShare_Direct_Share_Stop,
}DirectShareStatusType;
*/
typedef enum DirectShareStatusStatus_Enum
{
	DirectShare_Unknown = 0,  // 目前没有使用。为了初始化
	DirectShare_Connecting,  // 尝试开始直接分享，等待中
	DirectShare_In_Direct_Share_Mode, //直接共享模式
	DirectShare_Ended,  //直接共享结束
	DirectShare_Need_MeetingID_Or_PairingCode, // 需要用户设置会议id/paring代码
	DirectShare_NetWork_Error, // 网络错误。稍后再试
	DirectShare_Other_Error,   //其他错误。主要发生在SIP呼叫模式
	DirectShare_WrongMeetingID_Or_SharingKey,///<Wrong meeting id or sharing key.
}DirectShareStatus;

/// \描述：通过会议ID或共享码直接共享接口。
///
class IDirectShareViaMeetingIDOrPairingCodeHandler
{
public:
	virtual ~IDirectShareViaMeetingIDOrPairingCodeHandler() {};

	/// \描述：尝试与指定的会议号码匹配。
	/// \参数：meetingNumber 指定会议号。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError \endlink
	virtual SDKError TryWithMeetingNumber(UINT64 meetingNumber) = 0;

	/// \描述：尝试匹配共享码。
	/// \参数：pairingCode 指定共享码。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum
	virtual SDKError TryWithPairingCode(const wchar_t* pairingCode) = 0;

	/// \描述：删除当前的直接共享
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum
	virtual SDKError Cancel() = 0;
};

/// \描述：直接共享助手回调事件
///
class IDirectShareServiceHelperEvent
{
public:
	/// \描述：如果直接共享的状态发生更改，将触发回调事件。
	/// \参数：status 指定直接共享的状态。有关详细信息，请参见DirectShareStatus enum。
	/// \参数：handler 指向IDirectShareViaMeetingIDOrPairingCodeHandler的指针。只有当状态值为DirectShare_Need_MeetingID_Or_ParingCode时才有效。
	/// SDK用户必须通过IDirectShareViaMeetingIDOrPairingCodeHandler函数设置_paring_code或_meeting_number的值才能开始直接共享。有关详细信息，请参见 IDirectShareViaMeetingIDOrPairingCodeHandler
	virtual void OnDirectShareStatusUpdate(DirectShareStatus status, IDirectShareViaMeetingIDOrPairingCodeHandler* handler) = 0;

};

/// \描述：直接共享服务接口
///
class IDirectShareServiceHelper
{
public:

	/// \描述：设置直接共享服务回调事件
	/// \参数：pEvent 指向接收直接共享服务事件的IDirectShareServiceHelperEvent*的指针。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum
	virtual SDKError SetEvent(IDirectShareServiceHelperEvent* pEvent) = 0;

	/// \描述：确定是否可以开始直接共享。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum
	virtual SDKError CanStartDirectShare() = 0;

	/// \描述：确定是否正在进行直接共享。
	/// \返回：TRUE表示直接共享正在进行中
	virtual bool	 IsDirectShareInProgress() = 0;

	/// \描述：开始直接共享
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum
	/// \remarks Only login user can call this API.
	virtual SDKError StartDirectShare() = 0;

	// \描述：停止直接共享
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum
	/// \remarks Only login user can call this API.
	virtual SDKError StopDirectShare() = 0;
};

END_ZHUMU_SDK_NAMESPACE
#endif