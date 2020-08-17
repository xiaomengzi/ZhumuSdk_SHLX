/*!
* \文件：meeting_service_interface.h
* \描述：会议服务接口
* \支持zhumu风格和自定义风格的用户界面模式
*/
#ifndef ZHUMU_MEETING_H323_HELPER_INTERFACE_H_
#define ZHUMU_MEETING_H323_HELPER_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include <string>
#include <vector>
/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/// \描述： Meeting H323 helper Callback Event
///

/*! \enum H323CalloutStatus
\描述：H323外呼状态。
更详细的结构描述。
*/
enum H323CalloutStatus
{
	H323Callout_Unknown,
	H323Callout_Success,
	H323Callout_Ring,
	H323Callout_Timeout,
	H323Callout_Failed,
};

/*! \enum H323ParingStatus
\描述：H323 Paring status.
更详细的结构描述。
*/
enum H323ParingResult
{
	H323Paring_Unknown,
	H323Paring_Success,
	H323Paring_Meeting_Not_Exist,
	H323Paring_Paringcode_Not_Exist,
	H323Paring_No_Privilege,
	H323Paring_Other_Error,
};

/// \描述： Meeting H323 Helper callback event
///
class IMeetingH323HelperEvent
{
public:
	/// \描述：H323 设备外呼状态回调
	/// \参数：status H323 device call out status value.
	virtual void onCalloutStatusNotify(H323CalloutStatus status) = 0;

	/// \描述：Paring H323 to meeting status callback
	/// \参数：result Paring result.
	virtual void onParingH323Result(H323ParingResult result, UINT64 meetingNumber) = 0;
};


/*! \enum H323DeviceType
\描述： H323 device type.
更详细的结构描述
*/
enum H323DeviceType
{
	H323DeviceType_Unknown,
	H323DeviceType_H323,
	H323DeviceType_SIP,
	H323DeviceType_BOTH,
};

/// \描述： Meeting H323 device Interface
///
class IH323Device
{
public:
	virtual const wchar_t* GetName() = 0;
	virtual const wchar_t* GetIP() = 0;
	virtual const wchar_t* GetE164Num() = 0;
	virtual H323DeviceType GetDeviceType() = 0;
	virtual bool IsCustomizedH323Device() = 0;
	virtual ~IH323Device() {};
};

/// \描述： Customized Meeting H323 device
///
class CustomizedH323Device : public IH323Device
{
public:
	CustomizedH323Device()
	{
		_type = H323DeviceType_Unknown;
	}

	virtual void SetName(const wchar_t* name_)
	{
		if (name_)
			_name = name_;
	}

	virtual const wchar_t* GetName()
	{
		return _name.c_str();
	}

	virtual void SetIP(const wchar_t* ip_)
	{
		if (ip_)
			_ip = ip_;
	}

	virtual const wchar_t* GetIP()
	{
		return _ip.c_str();
	}

	virtual void SetE164Num(const wchar_t* e164num_)
	{
		if (e164num_)
			_e164num = e164num_;
	}

	virtual const wchar_t* GetE164Num()
	{
		return _e164num.c_str();
	}

	virtual void SetDeviceType(H323DeviceType type_)
	{
		_type = type_;
	}

	virtual H323DeviceType GetDeviceType()
	{
		return _type;
	}

	virtual bool IsCustomizedH323Device()
	{
		return true;
	}

private:
	H323DeviceType _type;
	std::wstring _name;
	std::wstring _ip;
	std::wstring _e164num;
};

/// \描述： Meeting H323 Helper Interface
///
class IMeetingH323Helper
{
public:
	/// \描述：设置h323辅助回调事件
	/// \参数：pEvent 一个指向IMeetingH323HelperEvent*的指针，该指针接收h323帮助事件。
	virtual void SetEvent(IMeetingH323HelperEvent* pEvent) = 0;

	/// \描述：获取当前会议的h323地址
	/// \返回：如果函数成功，则返回值不为空。
	virtual std::vector<const wchar_t*> GetH323Address() = 0;

	/// \描述：获取当前会议的h323密码
	/// \返回：h323 密码
	virtual const wchar_t* GetH323Password() = 0;

	virtual SDKError CanPairingMeeting(UINT64 meetingNum) = 0;
	/// \描述：Send Meeting paring code
	/// \参数：meetingNum Specifies which meeting to paring. 
	/// \参数：paringCode Code for paring
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SendMeetingParingCode(UINT64 meetingNum, wchar_t* paringCode) = 0;

	/// \描述：获取用于当前会议的h323设备
	/// \返回：如果函数成功，则返回值不为空。
	virtual std::vector<IH323Device* > GetCalloutH323DviceList() = 0;

	/// \描述：调用一个H323设备
	/// \参数：deviceInfo 指定要调出的h323设备。
	/// \返回：:如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CallOutH323(IH323Device* deviceInfo) = 0;

	/// \描述：取消一个h323设备呼叫
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CancelCallOutH323() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif