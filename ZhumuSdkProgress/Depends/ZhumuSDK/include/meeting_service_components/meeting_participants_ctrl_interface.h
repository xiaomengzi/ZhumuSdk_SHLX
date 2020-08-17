/*!
* \文件 meeting_participants_ctrl_interface.h
* \描述：会议参会者服务控制器接口
*
*/
#ifndef ZHUMU_MEETING_ParticipantsCtrl_INTERFACE_H_
#define ZHUMU_MEETING_ParticipantsCtrl_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include "meeting_audio_interface.h"
#include <vector>
/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum UserRole
\描述：用户角色.
更详细的结构描述。
*/
enum UserRole
{
	USERROLE_NONE,///< None
	USERROLE_HOST,///< 主持人
	USERROLE_COHOST,///< 联系主持人
	USERROLE_PANELIST,///< 讨论组成员, 仅适用用网络研讨会
	USERROLE_BREAKOUTROOM_MODERATOR,///< BO会议主持人
	USERROLE_ATTENDEE,///< 参会人
};

/*! \struct tagWebinarAttendeeStatus
\描述：研讨会参会者状态
更详细的结构描述。
*/
typedef struct tagWebinarAttendeeStatus
{
	bool allow_talk;///< 是否允许说话
	tagWebinarAttendeeStatus()
	{
		allow_talk = false;
	}
}WebinarAttendeeStatus;

/// \描述：用户信息接口
///
class IUserInfo
{
public:
	/// \描述：获得用户名
	/// \返回：如果函数成功，则返回用户名。
	/// 如果函数失败，返回值为NULL。
	virtual const wchar_t* GetUserName() = 0;

	/// \描述：是否为主持人
	/// \返回：是否
	virtual bool IsHost() = 0;

	/// \描述：获取用户ID
	/// \返回：如果函数成功，则返回值为用户ID。
	/// 如果函数失败，返回值为0。
	virtual unsigned int GetUserID() = 0;

	/// \描述：判断视频是开着还是关着
	/// \返回：是否
	virtual bool IsVideoOn() = 0;

	/// \描述：判断音频是静音还是非静音
	/// \返回：是否
	virtual bool IsAudioMuted() = 0;

	/// \描述：音频类型
	/// \返回：音频连接类型
	virtual ZHUMU_SDK_NAMESPACE::AudioType GetAudioJoinType() = 0;

	/// \描述：是否是自己
	/// \返回：是否
	virtual bool IsMySelf() = 0;

	/// \描述：是否在等待房间
	/// \返回：是否
	virtual bool IsInWaitingRoom() = 0;

	/// \描述：是否在举手
	/// \返回：是否
	virtual bool IsRaiseHand() = 0;

	/// \描述：获取用户角色
	/// \返回：用户角色
	virtual UserRole GetUserRole() = 0;

	/// \描述： Is pure phone user or not
	/// \return Is pure phone user or not
	virtual bool IsPurePhoneUser() = 0;

	/// \描述：获取音频的音量
	/// \返回：音量
	virtual int GetAudioVoiceLevel() = 0;

	/// \描述：确定当前信息对应的用户是否是隐藏字幕的发送方。
	/// \返回：TRUE 指示用户是隐藏字幕的发送方。
	virtual bool IsClosedCaptionSender() = 0;
	
    /// \brief Determine whether the user specified by the current information is talking or not.
	/// \return TRUE indicates that the specified user is talking.
	virtual bool IsTalking() = 0;

	/// \描述：获取当前信息指定的用户的网络研讨会状态。
	/// \返回：指定用户的状态。有关详细信息，请参见 WebinarAttendeeStatus 结构。
	virtual WebinarAttendeeStatus* GetWebinarAttendeeStauts() = 0;

	virtual ~IUserInfo() {};
};

/// \描述： 会议参与者控制器回叫事件
///
class IMeetingParticipantsCtrlEvent
{
public:
	/// \描述：正在开会的用户的通知回调事件。
	/// \参数：lstUserID 用户ID的列表。 
	/// \参数：strUserList json格式的用户列表。此功能目前无效，特此仅作保留。
	virtual void onUserJoin(std::vector<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;

	/// \描述：用户离开会议通知的回调事件。
	/// \参数：lstUserID 离开会议的用户ID列表。
	/// \参数：strUserList json格式的用户列表。此功能目前无效，特此仅作保留。
	virtual void onUserLeft(std::vector<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;

	/// \描述：主持人改变回调
	/// \参数：userId 
	virtual void onHostChangeNotification(unsigned int userId) = 0;

	/// \描述：举手状态改变回调
	/// \参数：bLow 是否举手
	/// \参数：userid 举手用户ID
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid) = 0;

	/// \描述：用户名改变回调
	/// \参数：userId 改变的用户ID
	/// \参数：userName 改变的名字
	virtual void onUserNameChanged(unsigned int userId, const wchar_t* userName) = 0;

	/// \描述：联席主持人改变回调
	/// \参数：userId 改变的用户ID
	/// \参数：isCoHost 是否是联席主持人
	virtual void onCoHostChangeNotification(unsigned int userId, bool isCoHost) = 0;
};

/// \描述：会议参会者服务控制器
///
class IMeetingParticipantsController
{
public:
	/// \描述：设置参与者控制器回调事件
	/// \参数: pEvent 一个指向接收参与者事件的IParticipantsControllerEvent*的指针。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IMeetingParticipantsCtrlEvent* pEvent) = 0;

	/// \描述：获取会议参与者名单
	/// \返回：返回值是当前会议的所有参与者列表。如果不在会议中，返回NULL。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual std::vector<unsigned int> GetParticipantsList() = 0;

	/// \描述：通过用户id获取用户信息
	/// \参数：userId 指定要获取的用户信息。如果为0，则获取当前用户信息。
	/// \返回：如果函数成功，则返回值为用户信息接口。
	/// 如果函数失败，返回值为NULL。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual IUserInfo* GetUserByUserID(unsigned int userid) = 0;

	/// \描述：在会议中取消所有参会者的举手状态。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError LowerAllHands() = 0;

	/// \描述：改变用户名。如果您想更改其他用户名，您应该是主持人或联席主机。
	/// \参数：userId 指定需要更改用户名的用户ID。
	/// \参数：userName 指定新用户名。
	/// \参数：bSaveUserName 指定下次参加会议时用户使用哪个名称。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError ChangeUserName(const unsigned int userid, const wchar_t* userName, bool bSaveUserName) = 0;

	/// \描述：放下参会者的举手状态
	/// \参数：userId 指定哪个用户的放下举手。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError LowerHand(unsigned int userid) = 0;

	/// \描述：在会议中举手
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError RaiseHand() = 0;

	/// \描述：指定主持人.
	/// \参数：userId 指定哪个用户作为主持人。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError MakeHost(unsigned int userid) = 0;

	/// \描述：检测能否最为联席主持人 .
	/// \参数：userId 指定哪个用户可以作为联席主持人。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError CanbeCohost(unsigned int userid) = 0;

	/// \描述：分配联席支持人
	/// \参数：userId Specifies which the user to be the co-host.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError AssignCoHost(unsigned int userid) = 0;

	/// \描述：撤销联席主持人.
	/// \参数：userId 指定将要撤销的联席主持人ID.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError RevokeCoHost(unsigned int userid) = 0;

	/// \描述：移除用户
	/// \参数：userId 指定要移除的用户。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError ExpelUser(unsigned int userid) = 0;

	/// \描述：回收主持人.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅支持zhumu风格的用户界面模式
	virtual SDKError ReclaimHost() = 0;

	/// \描述：检查是否能回收主持人
	/// \参数：bCanReclaimHost 能否能回收主持人权限。.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError CanReclaimHost(bool& bCanReclaimHost) = 0;

	/// \描述： 通过密钥回收主持人.
	/// \参数：host_key 主持人 key.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError ReclaimHostByHostKey(const wchar_t* host_key) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif