#ifndef ZHUMU_CALENDER_SERVICE_INTERFACE_H_
#define ZHUMU_CALENDER_SERVICE_INTERFACE_H_
#include "zhumu_sdk_def.h"
/// \简介： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE


class ICalenderEvent
{
public:
	virtual UINT64 GetMeetingNum() = 0;
	virtual const wchar_t* GetEventID() = 0;
	virtual const wchar_t* GetSummary() = 0;
	virtual const wchar_t* GetStartTime() = 0;
	virtual const wchar_t* GetEndTime() = 0;
	virtual const wchar_t* GetCreatorEmail() = 0;
	virtual const wchar_t* GetCreatorName() = 0;
	virtual const wchar_t* GetDescription() = 0;
	virtual ~ICalenderEvent() {};
};
enum CalenderResult
{
	CALENDER_SUCCESS,
	CALENDER_AUTH_ERROR,
	CALENDER_WEBAPI_ERROR,
	CALENDER_UNKNOW,
};

enum CalenderAuthType
{
	CalenderAuth_None,
	CalenderAuth_OutlookExchage,
	CalenderAuth_Goole,
};

/// \描述：日历服务回调事件
///
class ICalenderServiceEvent
{
public:
	/// \brief calendar service callback.
	/// \param type The type of authority. For more details, see \link CalenderAuthType \endlink enum.
	/// \param result The result of authority. For more details, see \link CalenderResult \endlink enum.
	/// \param plstEvents A pointer to the ICalenderEvent* list. For more details, see \link ICalenderEvent \endlink.
	/// \remarks The plstEvents* will be destroyed once the function calls end.
	virtual void onCalenderEventsNotifcation(CalenderAuthType type, CalenderResult result, std::vector<ICalenderEvent*> plstEvents) = 0;
};

/*! \struct tagOutlookExchageAuth
\描述：outlook exchange的SDK日历认证参数。
更详细的结构描述。
*/
typedef struct tagOutlookExchageAuth
{
	const wchar_t* serverUrl;
	const wchar_t* userName;
	const wchar_t* password;
	const wchar_t* calendaremail;
}OutlookExchageAuth;

/// \描述：日历服务接口
class ICalenderService
{
public:
	/// \brief Set the calendar service callback event handler, and initialize the calendar service.
	/// \param pEvent Specifies a pointer to ICalenderServiceEvent which will handle the callback events.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Init(ICalenderServiceEvent* pEvent) = 0;
	
	/// \brief Uninitialized the calendar service.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Uninit() = 0;
	
	/// \brief Schedule the meeting by the calendar of Outlook Exchange.
	/// \param param Specifies the parameter. For more details, see \link OutlookExchageAuth \endlink structure.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StartOutlookExchangeCalender(OutlookExchageAuth& param) = 0;
	
	/// \brief Stop using the Outlook Exchange to schedule the meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StopOutlookExchangeCalender() = 0;
	
	/// \brief Get the calendar event. The SDK will inform the user via ICalenderServiceEvent::onCalenderEventsNotifcation().
	/// \param type Specifies the type to get. The only type supported for the moment is the CalenderAuth_OutlookExchage. For more details, see \link CalenderAuthType \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RetrieveCalEvents(CalenderAuthType type) = 0;
};
///
END_ZHUMU_SDK_NAMESPACE
#endif