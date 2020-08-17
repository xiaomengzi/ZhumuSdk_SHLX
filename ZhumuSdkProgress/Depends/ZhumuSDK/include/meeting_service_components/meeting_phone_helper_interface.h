/*!
* \文件：meeting_phone_helper_interface.h
* \描述：Meeting Service Interface
* \支持 zhumu 风格和自定义UI风格
*/
#ifndef ZHUMU_MEETING_PHONE_HELPER_INTERFACE_H_
#define ZHUMU_MEETING_PHONE_HELPER_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include <vector>
/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
class IMeetingPhoneSupportCountryInfo
{
public:
	virtual ~IMeetingPhoneSupportCountryInfo() {}
	virtual const wchar_t* GetCountryID() = 0;
	virtual const wchar_t* GetCountryName() = 0;
	virtual const wchar_t* GetCountryCode() = 0;
};

enum CALLINNUMTYPE
{
	CALLINNUMTYPE_NONE,
	CALLINNUMTYPE_TOLL,
	CALLINNUMTYPE_TOLLFREE,
};
class IMeetingCallInPhoneNumberInfo
{
public:
	virtual ~IMeetingCallInPhoneNumberInfo() {}
	virtual const wchar_t* GetID() = 0;
	virtual const wchar_t* GetCode() = 0;
	virtual const wchar_t* GetName() = 0;
	virtual const wchar_t* GetNumber() = 0;
	virtual const wchar_t* GetDisplayNumber() = 0;
	virtual CALLINNUMTYPE  GetType() = 0;
};

enum PhoneStatus
{
	PhoneStatus_None,
	PhoneStatus_Calling,
	PhoneStatus_Ringing,
	PhoneStatus_Accepted,
	PhoneStatus_Success,
	PhoneStatus_Failed,
	PhoneStatus_Canceling,
	PhoneStatus_Canceled,
	PhoneStatus_Cancel_Failed,
	PhoneStatus_Timeout,
};
enum PhoneFailedReason
{
	PhoneFailedReason_None,
	PhoneFailedReason_Busy,
	PhoneFailedReason_Not_Available,
	PhoneFailedReason_User_Hangup,
	PhoneFailedReason_Other_Fail,
	PhoneFailedReason_No_Answer,
	PhoneFailedReason_Block_No_Host,
	PhoneFailedReason_Block_High_Rate,
	PhoneFailedReason_Block_Too_Frequent,
};
class IMeetingPhoneHelperEvent
{
public:
	/// \描述：邀请callout用户入会的状态改变回调
	/// \参数：status 状态
	/// \参数：reason 如果状态是PhoneStatus_Failed，原因是PhoneStatus_Failed其中一个。
	virtual void onInviteCallOutUserStatus(PhoneStatus status, PhoneFailedReason reason) = 0;

	/// \描述：邀请callme用户入会的状态改变回调
	/// \参数：status 状态
	/// \参数：reason 如果状态是PhoneStatus_Failed，原因是PhoneStatus_Failed其中一个。
	virtual void onCallMeStatus(PhoneStatus status, PhoneFailedReason reason) = 0;
};
/// \描述： 会议电话助手接口
///
class IMeetingPhoneHelper
{
public:
	/// \描述：设置会议电话助手回调事件
	/// \参数：pEvent 指向接收电话事件的IMeetingPhoneHelperEvent*的指针。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IMeetingPhoneHelperEvent* pEvent) = 0;

	/// \描述：判断当前会议支持电话功能或不支持
	/// \返回：是否
	virtual bool IsSupportPhoneFeature() = 0;

	/// \描述：确定电话功能支持的国家
	/// \返回：支持国家列表。
	virtual std::vector<IMeetingPhoneSupportCountryInfo* > GetSupportCountryInfo() = 0;

	/// \描述：邀请用户通过电话参加会议
	/// \参数：countryCode 国家代码，受支持国家的列表之一。
	/// \参数：phoneNumber 邀请的电话号码
	/// \参数：name 会议中显示的名字
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError InviteCallOutUser(const wchar_t* countryCode, const wchar_t* phoneNumber, const wchar_t* name) = 0;

	/// \描述：取消正在进行的外呼请求。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CancelCallOut() = 0;

	/// \描述：获取正在进行的外呼邀请的状态。
	/// \返回：返回值为当前外呼状态。要获取扩展的错误信息，请参考PhoneStatus enum
	virtual PhoneStatus GetInviteCalloutUserStatus() = 0;

	/// \描述：邀请自己通过电话加入会议
	/// \参数：countryCode 国家代码，受支持国家的列表之一。
	/// \参数：phoneNumber 邀请的电话号码
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CallMe(const wchar_t* countryCode, const wchar_t* phoneNumber) = 0;

	/// \描述：取消邀请自己或挂断电话
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError Hangup() = 0;

	/// \描述：获取正在进行的呼叫自己的状态。
	/// \返回：返回值是当前的callme状态。要获取扩展的错误信息，请参考PhoneStatus enum
	virtual PhoneStatus GetCallMeStatus() = 0;

	/// \描述：确定当前会议的呼入号码
	/// \返回：本次会议的来电号码列表。
	virtual std::vector<IMeetingCallInPhoneNumberInfo*> GetCurrentMeetingCallinNumber() = 0;

	/// \描述：获取您当前会议的参与者ID以便在feature中调用。
	/// \返回：参与者ID。
	virtual unsigned int GetCurrentMeetingCallinParticipantID() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif