/*!
* \�ļ���meeting_service_interface.h
* \�������������ӿ�
* \֧��zhumu�����Զ�������û�����ģʽ
*/
#ifndef ZHUMU_MEETING_H323_HELPER_INTERFACE_H_
#define ZHUMU_MEETING_H323_HELPER_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include <string>
#include <vector>
/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/// \������ Meeting H323 helper Callback Event
///

/*! \enum H323CalloutStatus
\������H323���״̬��
����ϸ�Ľṹ������
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
\������H323 Paring status.
����ϸ�Ľṹ������
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

/// \������ Meeting H323 Helper callback event
///
class IMeetingH323HelperEvent
{
public:
	/// \������H323 �豸���״̬�ص�
	/// \������status H323 device call out status value.
	virtual void onCalloutStatusNotify(H323CalloutStatus status) = 0;

	/// \������Paring H323 to meeting status callback
	/// \������result Paring result.
	virtual void onParingH323Result(H323ParingResult result, UINT64 meetingNumber) = 0;
};


/*! \enum H323DeviceType
\������ H323 device type.
����ϸ�Ľṹ����
*/
enum H323DeviceType
{
	H323DeviceType_Unknown,
	H323DeviceType_H323,
	H323DeviceType_SIP,
	H323DeviceType_BOTH,
};

/// \������ Meeting H323 device Interface
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

/// \������ Customized Meeting H323 device
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

/// \������ Meeting H323 Helper Interface
///
class IMeetingH323Helper
{
public:
	/// \����������h323�����ص��¼�
	/// \������pEvent һ��ָ��IMeetingH323HelperEvent*��ָ�룬��ָ�����h323�����¼���
	virtual void SetEvent(IMeetingH323HelperEvent* pEvent) = 0;

	/// \��������ȡ��ǰ�����h323��ַ
	/// \���أ���������ɹ����򷵻�ֵ��Ϊ�ա�
	virtual std::vector<const wchar_t*> GetH323Address() = 0;

	/// \��������ȡ��ǰ�����h323����
	/// \���أ�h323 ����
	virtual const wchar_t* GetH323Password() = 0;

	virtual SDKError CanPairingMeeting(UINT64 meetingNum) = 0;
	/// \������Send Meeting paring code
	/// \������meetingNum Specifies which meeting to paring. 
	/// \������paringCode Code for paring
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SendMeetingParingCode(UINT64 meetingNum, wchar_t* paringCode) = 0;

	/// \��������ȡ���ڵ�ǰ�����h323�豸
	/// \���أ���������ɹ����򷵻�ֵ��Ϊ�ա�
	virtual std::vector<IH323Device* > GetCalloutH323DviceList() = 0;

	/// \����������һ��H323�豸
	/// \������deviceInfo ָ��Ҫ������h323�豸��
	/// \���أ�:��������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CallOutH323(IH323Device* deviceInfo) = 0;

	/// \������ȡ��һ��h323�豸����
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CancelCallOutH323() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif