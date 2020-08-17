/*!
* \文件：meeting_audio_interface.h
* \描述：会议音频服务接口
*
*/
#ifndef ZHUMU_MEETING_AUDIO_INTERFACE_H_
#define ZHUMU_MEETING_AUDIO_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include <vector>

/// \brief Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum AudioStatus
\描述：音频状态.
下面是更详细的结构描述
*/
enum AudioStatus
{
	Audio_None,///<初始化.
	Audio_Muted,///<静音状态.
	Audio_UnMuted,///<未静音状态
	Audio_Muted_ByHost,///<被主持人静音.
	Audio_UnMuted_ByHost,///<被主持人接触静音.
	Audio_MutedAll_ByHost,///<主持人全体静音.
	Audio_UnMutedAll_ByHost,///<支持人接触全体静音.
};
/*! \enum AudioType
\描述：定义用户的音频类型
下面是更详细的结构描述。
*/
enum AudioType
{
	AUDIOTYPE_NONE,///<正常的音频类型。
	AUDIOTYPE_VOIP,///< VoIP 模式.
	AUDIOTYPE_PHONE,///< telephone 模式.
	AUDIOTYPE_UNKNOW,///<位置模式.
};

/// \描述：在用户从主机接收到打开音频的要求后进行处理。
class IRequestStartAudioHandler
{
public:
	virtual ~IRequestStartAudioHandler() {};
	/// \描述：获取要求打开音频的用户ID。
	/// \返回：如果函数成功，则返回用户ID。
	virtual unsigned int GetReqFromUserId() = 0;
	/// \描述：实例忽略需求，什么也不返回，最后自毁。
	virtual SDKError Ignore() = 0;
	/// \描述：实例接受要求，打开音频，最后自毁。
	virtual SDKError Accept() = 0;
	/// \描述：忽略在会议中启用视频的请求，最后实例自毁。
	virtual SDKError Cancel() = 0;
};

class IUserAudioStatus
{
public:
	virtual unsigned int GetUserId() = 0;
	virtual AudioStatus GetStatus() = 0;
	virtual AudioType   GetAudioType() = 0;
	virtual ~IUserAudioStatus() {};
};

/// \描述：会议音频回调事件
///
class IMeetingAudioCtrlEvent
{
public:
	/// \描述：进入翻
	/// \参数：lstAudioStatusChange 音频状态改变的用户信息列表。一旦函数调用结束，该列表将被清空。
	/// \参数：strAudioStatusList 音频状态改变的用户信息列表，以json格式保存。此参数目前无效，仅用于保留。
	virtual void onUserAudioStatusChange(std::vector<IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL) = 0;

	/// \描述：音频处于活动状态的用户更改的回调事件。
	/// \参数：plstActiveAudio 存储音频处于活动状态的用户的ID的列表。
	virtual void onUserActiveAudioChange(std::vector<unsigned int>* plstActiveAudio) = 0;

	/// \描述：要求从主机打开音频的回调事件。
	/// \参数：handler_ 一个指向IRequestStartAudioHandler的指针。有关详细信息，请参见IRequestStartAudioHandler
	virtual void onHostRequestStartAudio(IRequestStartAudioHandler* handler_) = 0;
};

/// \描述：会议音频控制器接口。
///
class IMeetingAudioController
{
public:
	/// \描述：设置会议音频设备控制器回调事件
	/// \参数：pEvent 一个指向 IMeetingAudioCtrlEvent* 对象得指针. 
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IMeetingAudioCtrlEvent* pEvent) = 0;

	/// \描述：加入 Voip 音频会议
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError JoinVoip() = 0;

	/// \描述：离开 Voip 音频会议
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError LeaveVoip() = 0;

	/// \描述：静音
	/// \参数：userId 指定要静音哪个用户的音频。如果是零，静音所有用户
	/// \参数：allowUnmuteBySelf 指定当被全体静音时是否能自己取消静音
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError MuteAudio(unsigned int userid, bool allowUnmuteBySelf = true) = 0;

	/// \描述：取消静音
	/// \参数：userId 指定要取消静音的用户音频。如果为0，则取消所有用户的静音
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError UnMuteAudio(unsigned int userid) = 0;

	/// \描述：是否可以被自己解除静音
	/// \返回：是否可以被自己解除静音
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual bool CanUnMuteBySelf() = 0;

	/// \描述：在用户参加会议时启用静音功能
	/// \参数：bEnable 指定静音进入功能启用或禁用。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError EnableMuteOnEntry(bool bEnable) = 0;

	/// \描述：当用户参加或离开会议时，启用播放铃声功能。
	/// \参数: bEnable 指定当用户加入或离开会议时播放铃声功能，启用或禁用。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义风格的用户界面模式
	virtual SDKError EnablePlayChimeWhenEnterOrExit(bool bEnable) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif