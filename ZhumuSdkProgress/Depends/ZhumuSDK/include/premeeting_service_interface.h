/*!
* \�ļ���premeeting_service_interface.h
* \��������ǰ����ӿ�
*
*/
#ifndef ZHUMU_PREMEETING_SERVICE_INTERFACE_H_
#define ZHUMU_PREMEETING_SERVICE_INTERFACE_H_
#include "zhumu_sdk_def.h"
#include <vector>
/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE

/*! \enum PremeetingAPIResult
\��������ǰ�� API ������.
����ϸ�Ľṹ������
*/
enum PremeetingAPIResult
{
	PREMETAPIRET_UNKNOW,
	PREMETAPIRET_SUCCESS,
};

/// \�������ճ̻�����Ŀ�ӿ�
/// �˽ӿ����ڵ��Ⱥͱ༭����api
/// ��������IPreMeetingService��ʹ��createschscheduling emeetingitem��DestoryScheduleMeetingItem�����������������
///
class IQueryMeetingItemDateInfoHelper
{
public:
	/// \��������ȡָ������Ŀ�ʼʱ�䡣
	/// \���أ�ָ������Ŀ�ʼʱ�䡣
	virtual time_t GetCurrentStartTime() = 0;

	/// \��������ȡָ������ĳ���ʱ�䡣
	/// \���أ�ָ������ĳ���ʱ��(�Է���Ϊ��λ)
	virtual int	GetDurationInMinutes() = 0;

	/// \������ָ������ĳ���ʱ��(�Է���Ϊ��λ)
	/// \���أ�TRUE ��ʾ��һ��ѭ������. False ��ʾ����.
	virtual bool IsRecurringMeetingSelected() = 0;
	virtual ~IQueryMeetingItemDateInfoHelper() {}
};
/// \���������������Ϣ���ýӿڡ�
class ISelectMeetingItemDateHelper
{
public:
	/// \����������ָ������Ŀ�ʼʱ�䡣����ʹ�ò���ϵͳ��ʱ����
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError    SelectStartTime(time_t time) = 0;

	/// \����������ָ������ĳ���ʱ��
	/// \�������������ʱ���Է���Ϊ��λ
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError    SetDurationInMinutes(int duration) = 0;

	/// \���������û�������Ϊ�����Ի�ƻ��ԡ�
	/// \������ select_ TRYE ��ʾ�����������ظ����飬FALSE ��ʾ����.
	/// \���أ���������ɹ�������ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError SelectRecurringMeeting(bool select_) = 0;
	virtual ~ISelectMeetingItemDateHelper() {}
};

/// \������ ��ѡ����״̬���ĵĻص��ӿڡ�
class ISelectMeetingItemDateHelperEvent
{
public:
	/// \������ ��ѡ����״̬���ĵĻص��¼���
	/// \������ can_use TRUE ��ʾ���á�
	/// \������ date_select_helper һ��ָ��ISelectMeetingItemDateHelper�Ķ���ָ�롣�й���ϸ��Ϣ����μ� ISelectMeetingItemDateHelper��
	virtual void onSupportSelectDateStatusNotification(bool can_use, ISelectMeetingItemDateHelper* date_select_helper) = 0;
};

/*! \enum SCHEDULEAUDIOTYPE
\������ָ��������Ƶ����
�����Ǹ���ϸ�Ľṹ������
*/
enum SCHEDULEAUDIOTYPE
{
	SCHEDULEAUDIOTYPE_none = 0,///<��ʼ����
	SCHEDULEAUDIOTYPE_telephony = (1 << 1),///<֧�ֵ绰��
	SCHEDULEAUDIOTYPE_voip = (1 << 2),///<֧��VoiP.
	SCHEDULEAUDIOTYPE_both = (1 << 3),///<֧�ֵ绰��VOIP
	SCHEDULEAUDIOTYPE_3rd = (1 << 4),///<֧�ֵ�������Ƶ�豸
};
/// \��������ѯ����绰������Ϣ�Ľ���
class IQueryMeetingItemTelAudioInfoHelper
{
public:
	virtual ~IQueryMeetingItemTelAudioInfoHelper() {}
	/// \��������ȡ�ɵ��ù��ҵĿ��õ绰�����б�
	/// \���أ���������ɹ�������ֵ�ǿ��Ե��õĹ��ҵĵ绰�����б�
	virtual std::vector<const wchar_t*> GetAvailableDialinCountryCode() = 0;

	/// \��������ȡ�ɵ��õ�ѡ�����ҵĵ绰�����б�
	/// \���أ���������ɹ�������ֵ����ѡ���ҵĵ绰���롣
	virtual std::vector<const wchar_t*> GetSelectedDialinCountryCode() = 0;

	/// \������ȷ�����ӿɲ��Ź��ҵĺ����Ƿ������Ѻ��롣
	/// \���أ�TRUE ���ǰ���.
	virtual bool IsIncludeTollFree() = 0;
};

/// \�������ýӿڿ����û���绰������Ϣ��
class ISelectMeetingItemTelAudioHelper
{
public:
	virtual ~ISelectMeetingItemTelAudioHelper() {}
	/// \������ͨ��ָ���Ĺ���IDѡ��绰������ΪĬ�ϵĺ��к��롣
	/// \������countryId ָ�����ҵ�ID��
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError SelectDefaultDialInCountry(const wchar_t* countryId) = 0;

	/// \������ͨ��ָ���Ĺ���IDɾ��Ĭ�Ϻ��к����еĵ绰����
	/// \������countryId ָ�����ҵ�ID��
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError RemoveDefaultDialInCountry(const wchar_t* countryId) = 0;

	/// \����������ں��к����б���������Ѻ��룬�����á�
	/// \������bEnable TRUE ��ʾ����
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError EnableIncludeTollFree(bool bEnable) = 0;
};
/// \������ ��ѡ������Ƶ�������ĵĻص��ӿڡ�
class ISelectMeetingItemAudioOptionHelperEvent
{
public:
	/// \��������ѡ������Ƶ�������ĵĻص��¼���
	/// \������can_use TRUE ������ǰѡ�������еĲ��ſ��á�
	virtual void onSupportTelAudioNotification(bool can_use) = 0;
};

/// \��������ѯ������Ƶ��Ϣ�Ľ��档
class IQueryMeetingItemAudioOptionHelper
{
public:
	virtual ~IQueryMeetingItemAudioOptionHelper() {}
	/// \��������ȡ������Ƶ���͡�
	/// \������[out] type_ ������Ƶ���͡��й���ϸ��Ϣ����μ� SCHEDULEAUDIOTYPE enum
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError GetSelectedAudioType(SCHEDULEAUDIOTYPE& type_) = 0;

	/// \��������ȡ����绰������Ϣ��
	/// \���أ���������ɹ�������ֵ��ָ��IQueryMeetingItemTelAudioInfoHelper��ָ�롣
	/// ����ʧ�ܣ�����NULL��
	/// �й���ϸ��Ϣ����μ� IQueryMeetingItemTelAudioInfoHelper
	virtual IQueryMeetingItemTelAudioInfoHelper* GetQueryTelAudioInfoHelper() = 0;
};

/// \���������û�����Ƶ��Ϣ�Ľӿڡ�
class ISelectMeetingItemAudioOptionHelper
{
public:
	virtual ~ISelectMeetingItemAudioOptionHelper() {}
	/// \������ȷ�������Ƿ�֧��ָ������Ƶ���͡�
	/// \������ָ������Ƶ���͡��й���ϸ��Ϣ����μ� SCHEDULEAUDIOTYPE enum��
	/// \���أ����֧��ָ������Ƶ���ͣ�����ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError  IsSupportAudioType(SCHEDULEAUDIOTYPE audio_type) = 0;

	/// \����������ָ���������Ƶ���͡�
	/// \������audio_type ��Ƶ���͡��й���ϸ��Ϣ����μ� SCHEDULEAUDIOTYPE enum��
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError  SelectAudioType(SCHEDULEAUDIOTYPE audio_type) = 0;

	/// \��������ȡ����绰������Ϣ��
	/// \���أ���������ɹ�������ֵ��ָ��ISelectMeetingItemTelAudioHelper��ָ�롣
	/// ����ʧ�ܣ�����NULL��
	/// �й���ϸ��Ϣ����μ� ISelectMeetingItemTelAudioHelper 
	virtual ISelectMeetingItemTelAudioHelper* GetScheduleTelAudioHelper() = 0;
};
/// \��������ѯ������Ƶ��Ϣ�Ľӿڡ�
class IQueryMeetingItemVideoOptionHelper
{
public:
	virtual ~IQueryMeetingItemVideoOptionHelper() {}
	/// \������ȷ�����������ʱ�Ƿ����������˵���Ƶ��
	/// \���أ�TRUE ��ʾ���������˵���Ƶ��
	virtual bool IsHostVideoOnOrOff() = 0;

	/// \������ȷ���������ʱ�Ƿ����������ߵ���Ƶ��
	/// \���أ�TRUE ��ʾ����
	virtual bool IsAttendeeVideoOnOrOff() = 0;
};

/// \���������û�����Ƶ��Ϣ�Ľӿ�
class ISelectMeetingItemVideoOptionHelper
{
public:
	virtual ~ISelectMeetingItemVideoOptionHelper() {};
	/// \���������û������������Ƶ����
	/// \������ bOn TRUE ���������ֹ�����˵���Ƶ
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError SelectHostVideoOnOrOff(bool bOn) = 0;

	/// \�����������Ƿ������û���ò����ߵ���Ƶ��
	/// \������ bOn TRUE ��ʾ��
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError SelectAttendeeVideoOnOrOff(bool bOn) = 0;
};
/*! \enum SCHEDULERECTYPE
\������ָ������¼�����͡�
�����Ǹ���ϸ�Ľṹ����
*/
enum SCHEDULERECTYPE
{
	SCHEDULERecordType_none = 0,///<��ʼ��
	SCHEDULERecordType_Cloud = 1,///<��¼��
	SCHEDULERecordType_Local = (1 << 1),///<����¼��
};

/// \���������û��������Ϣ�Ļص��ӿ�
class ISelectMeetingItemMeetingOptionHelperEvent
{
public:
	virtual ~ISelectMeetingItemMeetingOptionHelperEvent() {}
	/// \������Ҫ���ڲ����߼������ʱ��д����Ļص��¼�
	/// \������enable TRUE ��ʾҪ��д���롣
	/// \������default_psw  ����ԭ���롣���������enableֵΪ��ʱ��Ч��
	virtual void onMeetingPasswordEnabledStatusNotification(bool enable, const wchar_t* default_psw) = 0;

	/// \������JBH(������֮ǰ�������)״̬���ĵĻص��¼�
	/// \������enable TRUE ��������
	virtual void onJoinBeforeHostEnabledStatusNotification(bool enable) = 0;

	/// \�������������в�����״̬���ĵĻص��¼���
	/// \������enable TRUE ָʾ�������߾���.
	virtual void onMuteUponEntryEnabledStatusNotification(bool enable) = 0;

	/// \������ʹ�ø��˻���IDԤԼ����״̬���ĵĻص��¼���
	/// \������enable TRUE ָʾʹ�ø��˻���ID��
	virtual void onScheduleWithPmiEnabledStatusNotification(bool enable) = 0;

	/// \������������ָ���û��μӻ����״̬���ĵĻص��¼���
	/// \������enable TRUE ָʾֻ����ָ�����û��μӻ��顣
	/// \������default_specified_domain_can_join ָ�����е��û���ֻ����ENABLEֵΪ��ʱ����Ч��
	virtual void onOnlySignedInUserCanJoinEnabledStatusNotification(bool enable, const wchar_t* default_specified_domain_can_join) = 0;

	/// \���������й����ֻ���״̬�ı�Ļؽ��¼���
	/// \������enable TRUE ������.
	virtual void onHostInChinaEnabledStatusNotification(bool enable) = 0;

	/// \�����������Զ�¼��״̬���ĵĻص��¼���
	/// \������enable TRUE ָʾ�����Զ���¼��
	/// \������default_type Ĭ�ϵĻ���¼�����͡��й���ϸ��Ϣ������� SCHEDULERECTYPE enum��
	virtual void onAutoRecordEnabledStatusNotification(bool enable, SCHEDULERECTYPE& default_type) = 0;

	/// \������ָ��������Ϊ�����˵�״̬�ı�Ļص��¼���
	/// \������can_use TRUE ָʾ�ܽ������û�ָ��Ϊ������
	virtual void onSupportScheduleForNotification(bool can_use) = 0;
};

/// \������ ����ָ��Ϊ�����˵��û��Ľӿڡ�
class IScheduleForUser
{
public:
	virtual ~IScheduleForUser() {};
	/// \��������ȡ�û������ʼ�.
	/// \���أ��û��ĵ����ʼ�.
	virtual const wchar_t* GetEmail() = 0;

	/// \��������ȡ�û�����ʾ���֡�
	/// \���أ��û�����ʾ����.
	virtual const wchar_t* GetDisplayName() = 0;

	/// \��������ȡ�û����˻���ID.
	/// \���أ��û����˻���ID.
	virtual UINT64 GetPMINumber() = 0;
};
/// \���������ڲ�ѯָ��Ϊ�����������û�����Ϣ�Ľӿڡ�
class IQueryMeetingItemScheduleForHelper
{
public:
	virtual ~IQueryMeetingItemScheduleForHelper() {}
	/// \��������ȡָ��Ϊ���������˵��û�����Ϣ��
	/// \���أ�һ��ָ��IScheduleForUser��ָ�롣�й���ϸ��Ϣ����μ� IScheduleForUser 
	virtual IScheduleForUser* GetCurrentSelectedScheduleForUser() = 0;
};

/// \������ָ����������Ϊ�����˵Ļ�����Ϣ�ӿڡ�
class ISelectMeetingItemScheduleForHelper
{
public:
	virtual ~ISelectMeetingItemScheduleForHelper() {}
	/// \��������ȡ��ָ��Ϊ֧���˵��û��б�
	/// \������[out] can_select_schedule_for TRUE ָʾ��ǰ�������ָ�������û���Ϊ�����ˡ�
	/// \���أ���������ɹ������ص�ֵ��ָ����������Ϊ�����Ļ����б���ֻ��can_select_schedule_forΪ��ʱ��Ч������ʧ�ܣ�����NULL��
	virtual std::vector<IScheduleForUser*> GetAvailableScheduleForList(bool& can_select_schedule_for) = 0;

	/// \������Ϊ����ָ��һ����������
	/// \������alternateHost ָ��һ���µ������ˡ��й���ϸ��Ϣ����μ� IScheduleForUser 
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError SelectScheduleForUser(IScheduleForUser* alternateHost) = 0;
};
///\��������ѯ�������������Ϣ�Ľӿڡ�
class IQueryMeetingItemMeetingOptionHelper
{
public:
	virtual ~IQueryMeetingItemMeetingOptionHelper() {}
	/// \��������ȡָ����������⡣
	/// \���أ�ָ����������⡣
	virtual const wchar_t* GetMeetingTopic() = 0;

	/// \������ȷ���μӻ���ʱ�Ƿ���Ҫ���롣
	/// \������[out] can_change TRUE ָʾ�������Ƿ�����޸ġ�
	/// \���أ�TRUE ָʾ��Ҫ���롣
	virtual bool IsMeetingPasswordEnabled(bool& can_change) = 0;

	/// \��������ȡָ����������롣
	/// \���أ�ָ����������롣
	virtual const wchar_t* GetMeetingPassword() = 0;

	/// \������ȷ���Ƿ�������������֮ǰ������顣
	/// \������[out] can_change TRUE ָʾ�������Ƿ���Ը��ġ�
	/// \���أ�TRUE ָʾ������������֮ǰ������顣
	virtual bool IsJoinBeforeHostEnabled(bool& can_change) = 0;

	/// \������ȷ�������Ƿ��������ˡ�
	/// \������[out] can_change TRUE ָʾ�˹��ܿ��Ը��ġ�
	/// \���أ�TRUE ָʾ��ǰ�������в����ߡ�
	virtual bool IsMuteUponEntryEnabled(bool& can_change) = 0;

	/// \������ȷ���Ƿ��ڻ�����ʹ���˸��˻���ID��
	/// \������[out] can_change TRUE ָʾ���������Ը��ġ�
	/// \���أ�TRUE ָʾʹ��PMI��
	virtual bool IsScheduleWithPmiEnabled(bool& can_change) = 0;

	/// \������ȷ���Ƿ�ֻ����ָ�����û��μӻ��顣
	/// \������[out] can_change TRUE ָʾ���������Ը��ġ�
	/// \���أ�TRUE ָʾ������ָ���û��μӻ��顣
	virtual bool IsOnlySignedInUserCanJoinEnabled(bool& can_change) = 0;

	/// \��������ȡ��������domain��
	/// \������[out] can_change TRUE ָʾ���������Ը��ġ�
	/// \���أ���������domain.
	virtual const wchar_t* GetSpecifiedDomainCanJoin(bool& can_change) = 0;

	/// \������ȷ���Ƿ�������й����ֻ��顣
	/// \������[out] can_change TRUE ָʾ���������Ը��ġ�
	/// \���أ�TRUE ��ʾ�������й����ֻ��顣
	virtual bool IsHostInChinaEnabled(bool& can_change) = 0;

	/// \������ȷ���Ƿ��ڻ������������Զ�¼�ƹ���
	/// \������[out] can_change TRUE ָʾ���Ը���¼�����͡�
	/// \������[out] support_rec_type ָʾ����֧�ֵ�¼�����͡��й���ϸ��Ϣ������� SCHEDULERECTYPE enum��
	/// \���أ�TRUE ָʾ�����Զ�¼�ơ�
	virtual bool IsAutoRecordEnabled(bool& can_change, int& support_rec_type) = 0;

	/// \��������ȡ����֧�ֵ�¼�����͡�
	/// \���أ�����֧�ֵ�¼�����͡��й���ϸ��Ϣ������� SCHEDULERECTYPE enum��
	virtual SCHEDULERECTYPE GetSelectedAutoRecordType() = 0;

	/// \��������ȡָ������Ļ�����Ϣ�ӿڡ�
	/// \���أ�һ��ָ��IQueryMeetingItemScheduleForHelper��ָ�롣�й���ϸ��Ϣ����μ�IQueryMeetingItemScheduleForHelper
	virtual IQueryMeetingItemScheduleForHelper* GetQueryScheduleForHelper() = 0;
};

///\���������������Ϣ���ýӿڡ�
class ISelectMeetingItemMeetingOptionHelper
{
public:
	virtual ~ISelectMeetingItemMeetingOptionHelper() {};
	virtual SDKError SetMeetingTopic(const wchar_t* topic) = 0;
	/// \���������ü������ʱ�Ƿ���Ҫ���롣
	/// \������bEnable TRUE ָʾ��Ҫ���롣
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ��ȡ��չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺ISelectMeetingItemMeetingOptionHelperEvent::onMeetingPasswordEnabledStatusNotification() ����ÿ�ε��ô˺���ʱ������
	virtual SDKError EnableMeetingPassword(bool bEnable) = 0;

	/// \���������û������롣
	/// \������meetingPsw �������롣
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ��ȡ��չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError SetMeetingPassword(const wchar_t* meetingPsw) = 0;

	/// \�������������Ƿ���������֮ǰ������顣
	/// \������bEnable TRUE ��ʾ����λ�����������֮ǰ�μӻ���t. FALSE ������.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ��ȡ��չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺ISelectMeetingItemMeetingOptionHelperEvent::onJoinBeforeHostEnabledStatusNotification() ����ÿ�ε��ô˺���ʱ������
	virtual SDKError EnableJoinBeforeHost(bool bEnable) = 0;

	/// \�����������Ƿ��ܹ��ڲμӻ���ʱ�Զ������λ��ߡ�
	/// \������bEnable TRUE ��ʾ��λ����ڲμӻ���ʱ���־���. FALSE ������.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ��ȡ��չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺ISelectMeetingItemMeetingOptionHelperEvent::onMuteUponEntryEnabledStatusNotification()	����ÿ�ε��ô˺���ʱ������
	virtual SDKError EnableMuteUponEntry(bool bEnable) = 0;

	/// \�����������Ƿ����ͨ��PMI(���˻���ID)���Ż��顣
	/// \������bEnable TRUE indicates to use the PMI as the meeting ID.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ��ȡ��չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError EnableScheduleWithPmi(bool bEnable) = 0;

	/// \�����������Ƿ�ֻ��ָ�����û����Բμӻ��顣
	/// \������bEnable TRUE ָʾֻ��ָ�����û����Բμӻ��顣
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ��ȡ��չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺ISelectMeetingItemMeetingOptionHelperEvent::onOnlySignedInUserCanJoinEnabledStatusNotification() ����ÿ�ε��ô˺���ʱ������
	virtual SDKError EnableOnlySignedInUserCanJoin(bool bEnable) = 0;

	/// \����������ָ��domain.
	/// \������specified_domain_can_join ָ��domain.
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺ָ�����е��û�.
	virtual SDKError SetSpecifiedDomainCanJoin(const wchar_t* specified_domain_can_join) = 0;

	/// \�����������Ƿ�������й����ֻ���
	/// \������bEnable TRUE ��ʾ�����й����ֻ��顣
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError EnableHostInChina(bool bEnable) = 0;

	/// \�������������Ƿ��ܹ��Զ�¼�ƻ��顣
	/// \������bEnable TRUE ��ʾ���齫�Զ�¼�ơ�FALSE ��ʾ���ᡣ
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��	
	/// \ע�⣺ISelectMeetingItemMeetingOptionHelperEvent::onAutoRecordEnabledStatusNotification() ����ÿ�ε��ô˺���ʱ����	
	virtual SDKError EnableAutoRecord(bool bEnable) = 0;

	/// \���������û����¼�����͡�
	/// \������type_ ָ�������¼�����͡��й���ϸ��Ϣ������� SCHEDULERECTYPE enum��
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError SelectAutoRecordType(SCHEDULERECTYPE type_) = 0;

	/// \��������ȡָ���Ļ�����Ϣ��
	/// \���أ�ָ��ISelectMeetingItemScheduleForHelper��ָ�롣�й���ϸ��Ϣ����μ� ISelectMeetingItemScheduleForHelper
	virtual ISelectMeetingItemScheduleForHelper* GetScheduleForHelper() = 0;
};

///\������������Ŀ��Ϣ�ӿ�
class IMeetingItemInfo
	: public IQueryMeetingItemDateInfoHelper
	, public IQueryMeetingItemVideoOptionHelper
	, public IQueryMeetingItemAudioOptionHelper
	, public IQueryMeetingItemMeetingOptionHelper
{
public:
	/// \��������ȡ����ΨһID��
	/// \���أ���������ɹ����򷵻ط���Ļ����š�
	virtual UINT64 GetUniqueMeetingID() = 0;

	/// \��������ȡ����ID��
	/// \���أ���������ɹ����򷵻ط���Ļ����š�	
	virtual UINT64 GetMeetingID() = 0;

	/// \������ȷ��ָ���Ļ����Ƿ��Ǹ��˻��顣
	/// \���أ�TRUE ��ʾ���Ǹ��˻��顣 False ����.
	virtual bool IsPMI() = 0;

	/// \������ȷ��ָ���Ļ����Ƿ����������ֻᡣ
	/// \���أ�TRUE ��ʾ����һ���������ֻ�. False ����.
	virtual bool IsWebinar() = 0;

	/// \��������ȡ�����û��μӻ���ĵ����ʼ�����.
	/// \���أ���������ɹ����򷵻ص����ʼ������ݡ�����ʧ�ܣ�����NULL��
	virtual const wchar_t* GetInviteEmailContent() = 0;

	/// \��������ȡ�����û��μӻ���ĵ����ʼ�������
	/// \���أ���������ɹ����򷵻�ֵ�ǵ����ʼ������⡣����ʧ�ܣ�����NULL��
	virtual const wchar_t* GetInviteEmailSubject() = 0;

	/// \��������ȡ�����û��μӻ����URL��
	/// \���أ���������ɹ����򷵻ص����ʼ���URL������ʧ�ܣ�����NULL��
	virtual const wchar_t* GetJoinMeetingUrl() = 0;
};

///\��������ѯ������Ϣ�Ľӿڡ�
class IMeetingItemInfoQueryHelper : public IMeetingItemInfo
{
public:
};

class IMeetingItemInfoSelectHelper
	: public ISelectMeetingItemDateHelper
	, public ISelectMeetingItemVideoOptionHelper
	, public ISelectMeetingItemAudioOptionHelper
	, public ISelectMeetingItemMeetingOptionHelper
{
public:
};

/// \���������û�����Ϣ�Ľӿڡ�
class IScheduleMeetingItemStatusCallback
	: public ISelectMeetingItemDateHelperEvent
	, public ISelectMeetingItemAudioOptionHelperEvent
	, public ISelectMeetingItemMeetingOptionHelperEvent
{
public:
	virtual void onScheduleMeetingItemDestroyed() = 0;
};

/// \���������Ż������
/// ��Щapi���ڰ��Ż���ͱ༭���ŵĻ��顣
/// �������IPreMeetingService��ͨ��createsch����emeetingitem��DestoryScheduleMeetingItem������/���ٽӿ�
class IScheduleMeetingItem
	: public IMeetingItemInfoSelectHelper
	, public IMeetingItemInfoQueryHelper
{
public:
	/// \����������Ԥ���Ļ������ص��������
	/// \������callback һ��ָ�����Ԥ����������¼���IScheduleMeetingItemStatusCallbackָ�롣
	virtual SDKError SetEvent(IScheduleMeetingItemStatusCallback* callback) = 0;
};

/// \����������ǰ�����¼��ӿ�
class IPreMeetingServiceEvent
{
public:
	/// \�������б����ص��¼�
	/// \������result ����IPreMeetingService::ListMeeting()�Ľ�����й���ϸ��Ϣ����μ�PremeetingAPIResult enum��
	/// \������lstMeetingList һ��ָ�����ID�б��ָ�롣
	virtual void onListMeeting(PremeetingAPIResult result, std::vector<UINT64 >* lstMeetingList) = 0;

	/// \���������Ż�༭����ص��¼���
	/// \������result ����IPreMeetingService::ScheduleMeeting()�Ľ�����й���ϸ��Ϣ����μ�PremeetingAPIResult enum��
	/// \������meetingUniqueID ���Ż�༭����Ļ���ID��
	virtual void onScheduleOrEditMeeting(PremeetingAPIResult result, UINT64 meetingUniqueID) = 0;

	/// \������ɾ������ص���
	/// \������result ����IPreMeetingService::DeleteMeeting()�Ľ�����й���ϸ��Ϣ����μ�PremeetingAPIResult enum��
	virtual void onDeleteMeeting(PremeetingAPIResult result) = 0;
};

/// \��������ǰ����ӿڡ�
class IPreMeetingService
{
public:
	/// \����������һ����Ŀ�����Ż��顣
	/// \���أ���������ɹ�������ֵ��ָ��IScheduleMeetingItem�����ָ�롣����ʧ�ܣ�����NULL��
	virtual IScheduleMeetingItem* CreateScheduleMeetingItem() = 0;

	/// \����������ͨ��CreateScheduleMeetingItem()�������ճ̰��Ż������Ŀ
	/// \������pMeeting ָ��ͨ��CreateScheduleMeetingItem()���������ָ�� .
	virtual void DestoryScheduleMeetingItem(IScheduleMeetingItem* pMeeting) = 0;

	/// \������meetingUniqueID ָ������ID��
	/// \���أ���������ɹ�������ֵ��ָ��IScheduleMeetingItem�Ķ���ָ�롣����ʧ�ܣ�����NULL��
	virtual IScheduleMeetingItem* CreateEditMeetingItem(UINT64 meetingUniqueID) = 0;

	/// \����������ͨ��CreateEditMeetingItem()�����ı༭�����
	/// \������pMeeting ָ��ͨ��CreateEditMeetingItem()���������ָ�롣.
	virtual void DestoryEditMeetingItem(IScheduleMeetingItem* pMeeting) = 0;

	/// \���������û�ǰ�����¼�
	/// \������pEvent ָ��IPreMeetingServiceEvent��ָ�룬���ڽ��ջ�ǰ����ص��¼����й���ϸ��Ϣ����μ�IPreMeetingServiceEvent
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺SDKʹ�ø��¼����ص��¼����ݸ��û���Ӧ�ó����������δ�����û�ʧ�ܣ��û���Ӧ�ó����޷������ص��¼���
	virtual SDKError SetEvent(IPreMeetingServiceEvent* pEvent) = 0;

	/// \���������Ż��顣
	/// \������pItem ͨ��CreateScheduleMeetingItem()�����Ķ���
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺һ���������ɹ����ã��û���ͨ��IPreMeetingServiceEventreMeetingSer::onScheduleOrEditMeeting()���ջص��¼���
	virtual SDKError ScheduleMeeting(IScheduleMeetingItem* pItem) = 0;

	/// \���������Ż��顣
	/// \������wndParam ͨ��������wndParameter�ڶԻ��򴰿ڿ��а��Ż��顣�й���ϸ��Ϣ����μ�\link WndPosition \endlink�ṹ��
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺һ���������ɹ����ã��û���ͨ��IPreMeetingServiceEventreMeetingSer::onScheduleOrEditMeeting()���ջص��¼���
	virtual SDKError ScheduleMeeting(WndPosition& wndParam) = 0;

	/// \�������༭����
	/// \������pItem ͨ��CreateEditMeetingItem�����Ķ���.
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺һ���������ɹ����ã��û���ͨ��IPreMeetingServiceEvent::onScheduleOrEditMeeting()���ջص��¼���
	///ע��,���ָ���Ļ�����һ���������ֵ�һ����һ���������ֻ�,һ��SDKERR_INVALID_����:һ�ؽ����ش�������Щ�����,�༭����ͨ��IPreMeetingService::EditMeeting (WndPosition& wndparam:,UINT64 meetingUniqueID)��
	virtual SDKError EditMeeting(IScheduleMeetingItem* pItem) = 0;

	/// \�������༭����
	/// \������wndParam �༭����ͨ���Ի��򴰿�����wndParam���й���ϸ��Ϣ����μ� WndPosition �ṹ��
	/// \������meetingUniqueID ����һ������ID�����Ż�༭��ػ���
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺һ���������ɹ����ã��û���ͨ��IPreMeetingServiceEvent::onScheduleOrEditMeeting()���ջص��¼���
	///�ظ�������������ֻ�ֻ��ͨ��������ܽ��б༭��
	virtual SDKError EditMeeting(WndPosition& wndParam, UINT64 meetingUniqueID) = 0;

	/// \������ɾ��ָ����Ԥ�����顣
	/// \������meetingUniqueID ����һ������ID��ɾ������
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺һ���������ɹ����ã��û���ͨ��IPreMeetingServiceEvent::onDeleteMeeting()���ջص��¼�
	///����ɾ�����˻��顢���������ظ��ٿ��Ļ��顣
	virtual SDKError DeleteMeeting(UINT64 meetingUniqueID) = 0;

	/// \��������ȡ��ǰ������б�
	/// \���أ���������ɹ�������ֵΪSDKErr_Success
	/// ����ʧ�ܡ�Ҫ�����չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺һ���������ɹ����ã��û���ͨ��IPreMeetingServiceEvent::onListMeeting()���ջص��¼�
	virtual SDKError ListMeeting() = 0;

	/// \��������ȡָ��IMeetingItemInfo��ָ�롣
	/// \������meetingUniqueID ָ����ȡIMeetingItemInfo����ض���Ļ���ID��
	/// \���أ���������ɹ�������ֵ����NULL������ʧ�ܣ�����NULL��
	virtual IMeetingItemInfo* GetMeeingItem(UINT64 meetingUniqueID) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif