/*!
* \文件：premeeting_service_interface.h
* \描述：会前服务接口
*
*/
#ifndef ZHUMU_PREMEETING_SERVICE_INTERFACE_H_
#define ZHUMU_PREMEETING_SERVICE_INTERFACE_H_
#include "zhumu_sdk_def.h"
#include <vector>
/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE

/*! \enum PremeetingAPIResult
\描述：会前的 API 请求结果.
更详细的结构描述。
*/
enum PremeetingAPIResult
{
	PREMETAPIRET_UNKNOW,
	PREMETAPIRET_SUCCESS,
};

/// \描述：日程会议项目接口
/// 此接口用于调度和编辑会议api
/// 您可以在IPreMeetingService中使用createschscheduling emeetingitem和DestoryScheduleMeetingItem创建和销毁这个对象
///
class IQueryMeetingItemDateInfoHelper
{
public:
	/// \描述：获取指定会议的开始时间。
	/// \返回：指定会议的开始时间。
	virtual time_t GetCurrentStartTime() = 0;

	/// \描述：获取指定会议的持续时间。
	/// \返回：指定会议的持续时间(以分钟为单位)
	virtual int	GetDurationInMinutes() = 0;

	/// \描述：指定会议的持续时间(以分钟为单位)
	/// \返回：TRUE 表示是一个循环会议. False 表示不是.
	virtual bool IsRecurringMeetingSelected() = 0;
	virtual ~IQueryMeetingItemDateInfoHelper() {}
};
/// \描述：会议基本信息设置接口。
class ISelectMeetingItemDateHelper
{
public:
	/// \描述：设置指定会议的开始时间。建议使用操作系统的时区。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError    SelectStartTime(time_t time) = 0;

	/// \描述：设置指定会议的持续时间
	/// \参数：会议持续时间以分钟为单位
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError    SetDurationInMinutes(int duration) = 0;

	/// \描述：设置会议类型为经常性或计划性。
	/// \参数： select_ TRYE 表示会议类型是重复会议，FALSE 表示不是.
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError SelectRecurringMeeting(bool select_) = 0;
	virtual ~ISelectMeetingItemDateHelper() {}
};

/// \描述： 所选会议状态更改的回调接口。
class ISelectMeetingItemDateHelperEvent
{
public:
	/// \描述： 所选会议状态更改的回调事件。
	/// \参数： can_use TRUE 表示可用。
	/// \参数： date_select_helper 一个指向ISelectMeetingItemDateHelper的对象指针。有关详细信息，请参见 ISelectMeetingItemDateHelper。
	virtual void onSupportSelectDateStatusNotification(bool can_use, ISelectMeetingItemDateHelper* date_select_helper) = 0;
};

/*! \enum SCHEDULEAUDIOTYPE
\描述：指定会议音频类型
下面是更详细的结构描述。
*/
enum SCHEDULEAUDIOTYPE
{
	SCHEDULEAUDIOTYPE_none = 0,///<初始化。
	SCHEDULEAUDIOTYPE_telephony = (1 << 1),///<支持电话。
	SCHEDULEAUDIOTYPE_voip = (1 << 2),///<支持VoiP.
	SCHEDULEAUDIOTYPE_both = (1 << 3),///<支持电话和VOIP
	SCHEDULEAUDIOTYPE_3rd = (1 << 4),///<支持第三方音频设备
};
/// \描述：查询会议电话号码信息的界面
class IQueryMeetingItemTelAudioInfoHelper
{
public:
	virtual ~IQueryMeetingItemTelAudioInfoHelper() {}
	/// \描述：获取可调用国家的可用电话号码列表。
	/// \返回：如果函数成功，返回值是可以调用的国家的电话号码列表。
	virtual std::vector<const wchar_t*> GetAvailableDialinCountryCode() = 0;

	/// \描述：获取可调用的选定国家的电话号码列表。
	/// \返回：如果函数成功，返回值是所选国家的电话号码。
	virtual std::vector<const wchar_t*> GetSelectedDialinCountryCode() = 0;

	/// \描述：确定可视可拨号国家的号码是否包含免费号码。
	/// \返回：TRUE 包是包含.
	virtual bool IsIncludeTollFree() = 0;
};

/// \描述：该接口可设置会议电话号码信息。
class ISelectMeetingItemTelAudioHelper
{
public:
	virtual ~ISelectMeetingItemTelAudioHelper() {}
	/// \描述：通过指定的国家ID选择电话号码作为默认的呼叫号码。
	/// \参数：countryId 指定国家的ID。
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError SelectDefaultDialInCountry(const wchar_t* countryId) = 0;

	/// \描述：通过指定的国家ID删除默认呼叫号码中的电话号码
	/// \参数：countryId 指定国家的ID。
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError RemoveDefaultDialInCountry(const wchar_t* countryId) = 0;

	/// \描述：如果在呼叫号码列表中启用免费号码，则设置。
	/// \参数：bEnable TRUE 表示启用
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError EnableIncludeTollFree(bool bEnable) = 0;
};
/// \描述： 所选会议音频函数更改的回调接口。
class ISelectMeetingItemAudioOptionHelperEvent
{
public:
	/// \描述：所选会议音频函数更改的回调事件。
	/// \参数：can_use TRUE 表明当前选定会议中的拨号可用。
	virtual void onSupportTelAudioNotification(bool can_use) = 0;
};

/// \描述：查询会议音频信息的界面。
class IQueryMeetingItemAudioOptionHelper
{
public:
	virtual ~IQueryMeetingItemAudioOptionHelper() {}
	/// \描述：获取会议音频类型。
	/// \参数：[out] type_ 会议音频类型。有关详细信息，请参见 SCHEDULEAUDIOTYPE enum
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError GetSelectedAudioType(SCHEDULEAUDIOTYPE& type_) = 0;

	/// \描述：获取会议电话号码信息。
	/// \返回：如果函数成功，返回值是指向IQueryMeetingItemTelAudioInfoHelper的指针。
	/// 否则失败，返回NULL。
	/// 有关详细信息，请参见 IQueryMeetingItemTelAudioInfoHelper
	virtual IQueryMeetingItemTelAudioInfoHelper* GetQueryTelAudioInfoHelper() = 0;
};

/// \描述：设置会议音频信息的接口。
class ISelectMeetingItemAudioOptionHelper
{
public:
	virtual ~ISelectMeetingItemAudioOptionHelper() {}
	/// \描述：确定会议是否支持指定的音频类型。
	/// \参数：指定的音频类型。有关详细信息，请参见 SCHEDULEAUDIOTYPE enum。
	/// \返回：如果支持指定的音频类型，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError  IsSupportAudioType(SCHEDULEAUDIOTYPE audio_type) = 0;

	/// \描述：设置指定会议的音频类型。
	/// \参数：audio_type 音频类型。有关详细信息，请参见 SCHEDULEAUDIOTYPE enum。
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError  SelectAudioType(SCHEDULEAUDIOTYPE audio_type) = 0;

	/// \描述：获取会议电话号码信息。
	/// \返回：如果函数成功，返回值是指向ISelectMeetingItemTelAudioHelper的指针。
	/// 否则失败，返回NULL。
	/// 有关详细信息，请参见 ISelectMeetingItemTelAudioHelper 
	virtual ISelectMeetingItemTelAudioHelper* GetScheduleTelAudioHelper() = 0;
};
/// \描述：查询会议视频信息的接口。
class IQueryMeetingItemVideoOptionHelper
{
public:
	virtual ~IQueryMeetingItemVideoOptionHelper() {}
	/// \描述：确定加入会议是时是否启用主持人的视频。
	/// \返回：TRUE 表示启用主持人的视频。
	virtual bool IsHostVideoOnOrOff() = 0;

	/// \描述：确定加入会议时是否启动参与者的视频。
	/// \返回：TRUE 表示启动
	virtual bool IsAttendeeVideoOnOrOff() = 0;
};

/// \描述：设置会议视频信息的接口
class ISelectMeetingItemVideoOptionHelper
{
public:
	virtual ~ISelectMeetingItemVideoOptionHelper() {};
	/// \描述：启用或禁用主持人视频功能
	/// \参数： bOn TRUE 能启动或禁止主持人的视频
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError SelectHostVideoOnOrOff(bool bOn) = 0;

	/// \描述：设置是否能启用或禁用参与者的视频。
	/// \参数： bOn TRUE 表示能
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError SelectAttendeeVideoOnOrOff(bool bOn) = 0;
};
/*! \enum SCHEDULERECTYPE
\描述：指定会议录制类型。
下面是更详细的结构描述
*/
enum SCHEDULERECTYPE
{
	SCHEDULERecordType_none = 0,///<初始化
	SCHEDULERecordType_Cloud = 1,///<云录制
	SCHEDULERecordType_Local = (1 << 1),///<本地录制
};

/// \描述：配置会议基本信息的回调接口
class ISelectMeetingItemMeetingOptionHelperEvent
{
public:
	virtual ~ISelectMeetingItemMeetingOptionHelperEvent() {}
	/// \描述：要求在参与者加入会议时填写密码的回调事件
	/// \参数：enable TRUE 表示要填写密码。
	/// \参数：default_psw  会议原密码。此密码仅在enable值为真时有效。
	virtual void onMeetingPasswordEnabledStatusNotification(bool enable, const wchar_t* default_psw) = 0;

	/// \描述：JBH(主持人之前加入会议)状态更改的回调事件
	/// \参数：enable TRUE 表明启用
	virtual void onJoinBeforeHostEnabledStatusNotification(bool enable) = 0;

	/// \描述：静音所有参与者状态更改的回调事件。
	/// \参数：enable TRUE 指示将参与者静音.
	virtual void onMuteUponEntryEnabledStatusNotification(bool enable) = 0;

	/// \描述：使用个人会议ID预约会议状态更改的回调事件。
	/// \参数：enable TRUE 指示使用个人会议ID。
	virtual void onScheduleWithPmiEnabledStatusNotification(bool enable) = 0;

	/// \描述：仅允许指定用户参加会议的状态更改的回调事件。
	/// \参数：enable TRUE 指示只允许指定的用户参加会议。
	/// \参数：default_specified_domain_can_join 指定域中的用户。只有在ENABLE值为真时才有效。
	virtual void onOnlySignedInUserCanJoinEnabledStatusNotification(bool enable, const wchar_t* default_specified_domain_can_join) = 0;

	/// \描述：在中国主持会议状态改变的回叫事件。
	/// \参数：enable TRUE 表明能.
	virtual void onHostInChinaEnabledStatusNotification(bool enable) = 0;

	/// \描述：会议自动录制状态更改的回调事件。
	/// \参数：enable TRUE 指示启用自动记录。
	/// \参数：default_type 默认的会议录制类型。有关详细信息，请参阅 SCHEDULERECTYPE enum。
	virtual void onAutoRecordEnabledStatusNotification(bool enable, SCHEDULERECTYPE& default_type) = 0;

	/// \描述：指定其他人为主持人的状态改变的回调事件。
	/// \参数：can_use TRUE 指示能将其他用户指定为主持人
	virtual void onSupportScheduleForNotification(bool can_use) = 0;
};

/// \描述： 可以指定为主持人的用户的接口。
class IScheduleForUser
{
public:
	virtual ~IScheduleForUser() {};
	/// \描述：获取用户电子邮件.
	/// \返回：用户的电子邮件.
	virtual const wchar_t* GetEmail() = 0;

	/// \描述：获取用户的显示名字。
	/// \返回：用户的显示名字.
	virtual const wchar_t* GetDisplayName() = 0;

	/// \描述：获取用户个人会议ID.
	/// \返回：用户个人会议ID.
	virtual UINT64 GetPMINumber() = 0;
};
/// \描述：用于查询指定为会议主机的用户的信息的接口。
class IQueryMeetingItemScheduleForHelper
{
public:
	virtual ~IQueryMeetingItemScheduleForHelper() {}
	/// \描述：获取指定为会议主持人的用户的信息。
	/// \返回：一个指向IScheduleForUser的指针。有关详细信息，请参见 IScheduleForUser 
	virtual IScheduleForUser* GetCurrentSelectedScheduleForUser() = 0;
};

/// \描述：指定其他人作为主持人的会议信息接口。
class ISelectMeetingItemScheduleForHelper
{
public:
	virtual ~ISelectMeetingItemScheduleForHelper() {}
	/// \描述：获取可指定为支持人的用户列表。
	/// \参数：[out] can_select_schedule_for TRUE 指示当前会议可以指定其他用户作为主持人。
	/// \返回：如果函数成功，返回的值是指定其他人作为主机的会议列表。它只在can_select_schedule_for为真时有效。否则失败，返回NULL。
	virtual std::vector<IScheduleForUser*> GetAvailableScheduleForList(bool& can_select_schedule_for) = 0;

	/// \描述：为会议指定一个新主持人
	/// \参数：alternateHost 指定一个新的主持人。有关详细信息，请参见 IScheduleForUser 
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError SelectScheduleForUser(IScheduleForUser* alternateHost) = 0;
};
///\描述：查询会议基本配置信息的接口。
class IQueryMeetingItemMeetingOptionHelper
{
public:
	virtual ~IQueryMeetingItemMeetingOptionHelper() {}
	/// \描述：获取指定会议的主题。
	/// \返回：指定会议的主题。
	virtual const wchar_t* GetMeetingTopic() = 0;

	/// \描述：确定参加会议时是否需要密码。
	/// \参数：[out] can_change TRUE 指示此特征是否可以修改。
	/// \返回：TRUE 指示需要密码。
	virtual bool IsMeetingPasswordEnabled(bool& can_change) = 0;

	/// \描述：获取指定会议的密码。
	/// \返回：指定会议的密码。
	virtual const wchar_t* GetMeetingPassword() = 0;

	/// \描述：确定是否允许在主持人之前加入会议。
	/// \参数：[out] can_change TRUE 指示此特征是否可以更改。
	/// \返回：TRUE 指示启用在主持人之前加入会议。
	virtual bool IsJoinBeforeHostEnabled(bool& can_change) = 0;

	/// \描述：确定会议是否静音所有人。
	/// \参数：[out] can_change TRUE 指示此功能可以更改。
	/// \返回：TRUE 指示当前静音所有参与者。
	virtual bool IsMuteUponEntryEnabled(bool& can_change) = 0;

	/// \描述：确定是否在会议中使用了个人会议ID。
	/// \参数：[out] can_change TRUE 指示此特征可以更改。
	/// \返回：TRUE 指示使用PMI。
	virtual bool IsScheduleWithPmiEnabled(bool& can_change) = 0;

	/// \描述：确定是否只允许指定的用户参加会议。
	/// \参数：[out] can_change TRUE 指示此特征可以更改。
	/// \返回：TRUE 指示仅允许指定用户参加会议。
	virtual bool IsOnlySignedInUserCanJoinEnabled(bool& can_change) = 0;

	/// \描述：获取加入会议的domain。
	/// \参数：[out] can_change TRUE 指示此特征可以更改。
	/// \返回：加入会议的domain.
	virtual const wchar_t* GetSpecifiedDomainCanJoin(bool& can_change) = 0;

	/// \描述：确定是否可以在中国主持会议。
	/// \参数：[out] can_change TRUE 指示此特征可以更改。
	/// \返回：TRUE 表示可以在中国主持会议。
	virtual bool IsHostInChinaEnabled(bool& can_change) = 0;

	/// \描述：确定是否在会议中启用了自动录制功能
	/// \参数：[out] can_change TRUE 指示可以更改录制类型。
	/// \参数：[out] support_rec_type 指示会议支持的录制类型。有关详细信息，请参阅 SCHEDULERECTYPE enum。
	/// \返回：TRUE 指示启用自动录制。
	virtual bool IsAutoRecordEnabled(bool& can_change, int& support_rec_type) = 0;

	/// \描述：获取会议支持的录制类型。
	/// \返回：会议支持的录制类型。有关详细信息，请参阅 SCHEDULERECTYPE enum。
	virtual SCHEDULERECTYPE GetSelectedAutoRecordType() = 0;

	/// \描述：获取指定会议的会议信息接口。
	/// \返回：一个指向IQueryMeetingItemScheduleForHelper的指针。有关详细信息，请参见IQueryMeetingItemScheduleForHelper
	virtual IQueryMeetingItemScheduleForHelper* GetQueryScheduleForHelper() = 0;
};

///\描述：会议基本信息配置接口。
class ISelectMeetingItemMeetingOptionHelper
{
public:
	virtual ~ISelectMeetingItemMeetingOptionHelper() {};
	virtual SDKError SetMeetingTopic(const wchar_t* topic) = 0;
	/// \描述：设置加入会议时是否需要密码。
	/// \参数：bEnable TRUE 指示需要密码。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 否则失败。要获取扩展的错误信息，请参见 SDKError enum。
	/// \注意：ISelectMeetingItemMeetingOptionHelperEvent::onMeetingPasswordEnabledStatusNotification() 将在每次调用此函数时触发。
	virtual SDKError EnableMeetingPassword(bool bEnable) = 0;

	/// \描述：设置会议密码。
	/// \参数：meetingPsw 会议密码。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 否则失败。要获取扩展的错误信息，请参见 SDKError enum。
	virtual SDKError SetMeetingPassword(const wchar_t* meetingPsw) = 0;

	/// \描述：设置它是否能在主人之前加入会议。
	/// \参数：bEnable TRUE 表示允许参会者在主持人之前参加会议t. FALSE 不允许.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 否则失败。要获取扩展的错误信息，请参见 SDKError enum。
	/// \注意：ISelectMeetingItemMeetingOptionHelperEvent::onJoinBeforeHostEnabledStatusNotification() 将在每次调用此函数时触发。
	virtual SDKError EnableJoinBeforeHost(bool bEnable) = 0;

	/// \描述：设置是否能够在参加会议时自动静音参会者。
	/// \参数：bEnable TRUE 表示与参会者在参加会议时保持静音. FALSE 不静音.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 否则失败。要获取扩展的错误信息，请参见 SDKError enum。
	/// \注意：ISelectMeetingItemMeetingOptionHelperEvent::onMuteUponEntryEnabledStatusNotification()	将在每次调用此函数时触发。
	virtual SDKError EnableMuteUponEntry(bool bEnable) = 0;

	/// \描述：设置是否可以通过PMI(个人会议ID)安排会议。
	/// \参数：bEnable TRUE indicates to use the PMI as the meeting ID.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 否则失败。要获取扩展的错误信息，请参见 SDKError enum。
	virtual SDKError EnableScheduleWithPmi(bool bEnable) = 0;

	/// \描述：设置是否只有指定的用户可以参加会议。
	/// \参数：bEnable TRUE 指示只有指定的用户可以参加会议。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 否则失败。要获取扩展的错误信息，请参见 SDKError enum。
	/// \注意：ISelectMeetingItemMeetingOptionHelperEvent::onOnlySignedInUserCanJoinEnabledStatusNotification() 将在每次调用此函数时触发。
	virtual SDKError EnableOnlySignedInUserCanJoin(bool bEnable) = 0;

	/// \描述：设置指定domain.
	/// \参数：specified_domain_can_join 指定domain.
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	/// \注意：指定域中的用户.
	virtual SDKError SetSpecifiedDomainCanJoin(const wchar_t* specified_domain_can_join) = 0;

	/// \描述：设置是否可以在中国主持会议
	/// \参数：bEnable TRUE 表示能在中国主持会议。
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError EnableHostInChina(bool bEnable) = 0;

	/// \描述：设置它是否能够自动录制会议。
	/// \参数：bEnable TRUE 表示会议将自动录制。FALSE 表示不会。
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。	
	/// \注意：ISelectMeetingItemMeetingOptionHelperEvent::onAutoRecordEnabledStatusNotification() 将在每次调用此函数时触发	
	virtual SDKError EnableAutoRecord(bool bEnable) = 0;

	/// \描述：设置会议记录制类型。
	/// \参数：type_ 指定会议的录制类型。有关详细信息，请参阅 SCHEDULERECTYPE enum。
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	virtual SDKError SelectAutoRecordType(SCHEDULERECTYPE type_) = 0;

	/// \描述：获取指定的会议信息。
	/// \返回：指向ISelectMeetingItemScheduleForHelper的指针。有关详细信息，请参见 ISelectMeetingItemScheduleForHelper
	virtual ISelectMeetingItemScheduleForHelper* GetScheduleForHelper() = 0;
};

///\描述：会议项目信息接口
class IMeetingItemInfo
	: public IQueryMeetingItemDateInfoHelper
	, public IQueryMeetingItemVideoOptionHelper
	, public IQueryMeetingItemAudioOptionHelper
	, public IQueryMeetingItemMeetingOptionHelper
{
public:
	/// \描述：获取会议唯一ID。
	/// \返回：如果函数成功，则返回非零的会议编号。
	virtual UINT64 GetUniqueMeetingID() = 0;

	/// \描述：获取会议ID。
	/// \返回：如果函数成功，则返回非零的会议编号。	
	virtual UINT64 GetMeetingID() = 0;

	/// \描述：确定指定的会议是否是个人会议。
	/// \返回：TRUE 表示这是个人会议。 False 不是.
	virtual bool IsPMI() = 0;

	/// \描述：确定指定的会议是否是网络研讨会。
	/// \返回：TRUE 表示这是一个网络研讨会. False 不是.
	virtual bool IsWebinar() = 0;

	/// \描述：获取邀请用户参加会议的电子邮件内容.
	/// \返回：如果函数成功，则返回电子邮件的内容。否则失败，返回NULL。
	virtual const wchar_t* GetInviteEmailContent() = 0;

	/// \描述：获取邀请用户参加会议的电子邮件的主题
	/// \返回：如果函数成功，则返回值是电子邮件的主题。否则失败，返回NULL。
	virtual const wchar_t* GetInviteEmailSubject() = 0;

	/// \描述：获取邀请用户参加会议的URL。
	/// \返回：如果函数成功，则返回电子邮件的URL。否则失败，返回NULL。
	virtual const wchar_t* GetJoinMeetingUrl() = 0;
};

///\描述：查询会议信息的接口。
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

/// \描述：配置会议信息的接口。
class IScheduleMeetingItemStatusCallback
	: public ISelectMeetingItemDateHelperEvent
	, public ISelectMeetingItemAudioOptionHelperEvent
	, public ISelectMeetingItemMeetingOptionHelperEvent
{
public:
	virtual void onScheduleMeetingItemDestroyed() = 0;
};

/// \描述：安排会议事项。
/// 这些api用于安排会议和编辑安排的会议。
/// 你可以在IPreMeetingService中通过createsch调度emeetingitem和DestoryScheduleMeetingItem来创建/销毁接口
class IScheduleMeetingItem
	: public IMeetingItemInfoSelectHelper
	, public IMeetingItemInfoQueryHelper
{
public:
	/// \描述：设置预定的会议服务回调处理程序。
	/// \参数：callback 一个指向接收预定会议服务事件的IScheduleMeetingItemStatusCallback指针。
	virtual SDKError SetEvent(IScheduleMeetingItemStatusCallback* callback) = 0;
};

/// \描述：会议前服务事件接口
class IPreMeetingServiceEvent
{
public:
	/// \描述：列表会议回调事件
	/// \参数：result 调用IPreMeetingService::ListMeeting()的结果。有关详细信息，请参见PremeetingAPIResult enum。
	/// \参数：lstMeetingList 一个指向会议ID列表的指针。
	virtual void onListMeeting(PremeetingAPIResult result, std::vector<UINT64 >* lstMeetingList) = 0;

	/// \描述：安排或编辑会议回调事件。
	/// \参数：result 调用IPreMeetingService::ScheduleMeeting()的结果。有关详细信息，请参见PremeetingAPIResult enum。
	/// \参数：meetingUniqueID 安排或编辑会议的会议ID。
	virtual void onScheduleOrEditMeeting(PremeetingAPIResult result, UINT64 meetingUniqueID) = 0;

	/// \描述：删除会议回调。
	/// \参数：result 调用IPreMeetingService::DeleteMeeting()的结果。有关详细信息，请参见PremeetingAPIResult enum。
	virtual void onDeleteMeeting(PremeetingAPIResult result) = 0;
};

/// \描述：会前服务接口。
class IPreMeetingService
{
public:
	/// \描述：创建一个项目来安排会议。
	/// \返回：如果函数成功，返回值是指向IScheduleMeetingItem对象的指针。否则失败，返回NULL。
	virtual IScheduleMeetingItem* CreateScheduleMeetingItem() = 0;

	/// \描述：销毁通过CreateScheduleMeetingItem()创建的日程安排会议的项目
	/// \参数：pMeeting 指向通过CreateScheduleMeetingItem()创建的项的指针 .
	virtual void DestoryScheduleMeetingItem(IScheduleMeetingItem* pMeeting) = 0;

	/// \参数：meetingUniqueID 指定会议ID。
	/// \返回：如果函数成功，返回值是指向IScheduleMeetingItem的对象指针。否则失败，返回NULL。
	virtual IScheduleMeetingItem* CreateEditMeetingItem(UINT64 meetingUniqueID) = 0;

	/// \描述：销毁通过CreateEditMeetingItem()创建的编辑会议项。
	/// \参数：pMeeting 指向通过CreateEditMeetingItem()创建的项的指针。.
	virtual void DestoryEditMeetingItem(IScheduleMeetingItem* pMeeting) = 0;

	/// \描述：设置会前服务事件
	/// \参数：pEvent 指向IPreMeetingServiceEvent的指针，用于接收会前服务回调事件。有关详细信息，请参见IPreMeetingServiceEvent
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	/// \注意：SDK使用该事件将回调事件传递给用户的应用程序。如果函数未被调用或失败，用户的应用程序将无法检索回调事件。
	virtual SDKError SetEvent(IPreMeetingServiceEvent* pEvent) = 0;

	/// \描述：安排会议。
	/// \参数：pItem 通过CreateScheduleMeetingItem()创建的对象。
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	/// \注意：一旦函数被成功调用，用户将通过IPreMeetingServiceEventreMeetingSer::onScheduleOrEditMeeting()接收回调事件。
	virtual SDKError ScheduleMeeting(IScheduleMeetingItem* pItem) = 0;

	/// \描述：安排会议。
	/// \参数：wndParam 通过设置其wndParameter在对话框窗口框中安排会议。有关详细信息，请参见\link WndPosition \endlink结构。
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	/// \注意：一旦函数被成功调用，用户将通过IPreMeetingServiceEventreMeetingSer::onScheduleOrEditMeeting()接收回调事件。
	virtual SDKError ScheduleMeeting(WndPosition& wndParam) = 0;

	/// \描述：编辑会议
	/// \参数：pItem 通过CreateEditMeetingItem创建的对象.
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	/// \注意：一旦函数被成功调用，用户将通过IPreMeetingServiceEvent::onScheduleOrEditMeeting()接收回调事件。
	///注意,如果指定的会议是一个反复出现的一个或一个网络研讨会,一个SDKERR_INVALID_参数:一特将返回错误。在这些情况下,编辑会议通过IPreMeetingService::EditMeeting (WndPosition& wndparam:,UINT64 meetingUniqueID)。
	virtual SDKError EditMeeting(IScheduleMeetingItem* pItem) = 0;

	/// \描述：编辑会议
	/// \参数：wndParam 编辑会议通过对话框窗口设置wndParam。有关详细信息，请参见 WndPosition 结构。
	/// \参数：meetingUniqueID 分配一个会议ID来安排或编辑相关会议
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	/// \注意：一旦函数被成功调用，用户将通过IPreMeetingServiceEvent::onScheduleOrEditMeeting()接收回调事件。
	///重复会议和网络研讨会只能通过这个功能进行编辑。
	virtual SDKError EditMeeting(WndPosition& wndParam, UINT64 meetingUniqueID) = 0;

	/// \描述：删除指定的预定会议。
	/// \参数：meetingUniqueID 分配一个会议ID来删除会议
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	/// \注意：一旦函数被成功调用，用户将通过IPreMeetingServiceEvent::onDeleteMeeting()接收回调事件
	///不能删除个人会议、网络会议或重复召开的会议。
	virtual SDKError DeleteMeeting(UINT64 meetingUniqueID) = 0;

	/// \描述：获取当前会议的列表
	/// \返回：如果函数成功，返回值为SDKErr_Success
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	/// \注意：一旦函数被成功调用，用户将通过IPreMeetingServiceEvent::onListMeeting()接收回调事件
	virtual SDKError ListMeeting() = 0;

	/// \描述：获取指向IMeetingItemInfo的指针。
	/// \参数：meetingUniqueID 指定获取IMeetingItemInfo的相关对象的会议ID。
	/// \返回：如果函数成功，返回值不是NULL。否则失败，返回NULL。
	virtual IMeetingItemInfo* GetMeeingItem(UINT64 meetingUniqueID) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif