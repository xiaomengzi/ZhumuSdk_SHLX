/*!
* \�ļ���meeting_phone_helper_interface.h
* \������Meeting Service Interface
* \֧�� zhumu �����Զ���UI���
*/
#ifndef ZHUMU_MEETING_PHONE_HELPER_INTERFACE_H_
#define ZHUMU_MEETING_PHONE_HELPER_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include <vector>
/// \������ Zhumu SDK Namespace
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
	/// \����������callout�û�����״̬�ı�ص�
	/// \������status ״̬
	/// \������reason ���״̬��PhoneStatus_Failed��ԭ����PhoneStatus_Failed����һ����
	virtual void onInviteCallOutUserStatus(PhoneStatus status, PhoneFailedReason reason) = 0;

	/// \����������callme�û�����״̬�ı�ص�
	/// \������status ״̬
	/// \������reason ���״̬��PhoneStatus_Failed��ԭ����PhoneStatus_Failed����һ����
	virtual void onCallMeStatus(PhoneStatus status, PhoneFailedReason reason) = 0;
};
/// \������ ����绰���ֽӿ�
///
class IMeetingPhoneHelper
{
public:
	/// \���������û���绰���ֻص��¼�
	/// \������pEvent ָ����յ绰�¼���IMeetingPhoneHelperEvent*��ָ�롣
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IMeetingPhoneHelperEvent* pEvent) = 0;

	/// \�������жϵ�ǰ����֧�ֵ绰���ܻ�֧��
	/// \���أ��Ƿ�
	virtual bool IsSupportPhoneFeature() = 0;

	/// \������ȷ���绰����֧�ֵĹ���
	/// \���أ�֧�ֹ����б�
	virtual std::vector<IMeetingPhoneSupportCountryInfo* > GetSupportCountryInfo() = 0;

	/// \�����������û�ͨ���绰�μӻ���
	/// \������countryCode ���Ҵ��룬��֧�ֹ��ҵ��б�֮һ��
	/// \������phoneNumber ����ĵ绰����
	/// \������name ��������ʾ������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError InviteCallOutUser(const wchar_t* countryCode, const wchar_t* phoneNumber, const wchar_t* name) = 0;

	/// \������ȡ�����ڽ��е��������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CancelCallOut() = 0;

	/// \��������ȡ���ڽ��е���������״̬��
	/// \���أ�����ֵΪ��ǰ���״̬��Ҫ��ȡ��չ�Ĵ�����Ϣ����ο�PhoneStatus enum
	virtual PhoneStatus GetInviteCalloutUserStatus() = 0;

	/// \�����������Լ�ͨ���绰�������
	/// \������countryCode ���Ҵ��룬��֧�ֹ��ҵ��б�֮һ��
	/// \������phoneNumber ����ĵ绰����
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CallMe(const wchar_t* countryCode, const wchar_t* phoneNumber) = 0;

	/// \������ȡ�������Լ���Ҷϵ绰
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError Hangup() = 0;

	/// \��������ȡ���ڽ��еĺ����Լ���״̬��
	/// \���أ�����ֵ�ǵ�ǰ��callme״̬��Ҫ��ȡ��չ�Ĵ�����Ϣ����ο�PhoneStatus enum
	virtual PhoneStatus GetCallMeStatus() = 0;

	/// \������ȷ����ǰ����ĺ������
	/// \���أ����λ������������б�
	virtual std::vector<IMeetingCallInPhoneNumberInfo*> GetCurrentMeetingCallinNumber() = 0;

	/// \��������ȡ����ǰ����Ĳ�����ID�Ա���feature�е��á�
	/// \���أ�������ID��
	virtual unsigned int GetCurrentMeetingCallinParticipantID() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif