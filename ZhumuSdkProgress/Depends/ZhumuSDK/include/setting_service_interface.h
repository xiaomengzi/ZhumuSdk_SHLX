/*!
* \文件 setting_service_interface.h
* \描述 Setting Service Interface
* 
*/
#ifndef _ZHUMU_SETTING_SERVICE_INTERFACE_H_
#define _ZHUMU_SETTING_SERVICE_INTERFACE_H_
#include "zhumu_sdk_def.h"
#include "zhumu_sdk_util_define.h"
#include <vector>
/// \brief Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/// \描述：摄像头设备信息接口
///
class ICameraInfo
{
public:
	/// \描述：获取摄像头设备ID
	/// \返回：如果方法调用成功吗，返回值是摄像头的设备ID.
	/// 如果方法失败，返回值是空.
	virtual const wchar_t* GetDeviceId() = 0;

	/// \描述：获取摄像头设备名
	/// \返回：如果方法调用成功，返回值是摄像头的设备名字。
	/// 如果失败， 返回值是NULL.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetDeviceName() = 0;

	/// \描述：所选摄像头标志
	/// \返回：入伙方法调用成功，返回值是true,该摄像头是被选择的摄像头。
	virtual bool IsSelectedDevice() = 0;

	virtual ~ICameraInfo() {};
};

/// \描述：麦克风设备信息接口
///
class IMicInfo
{
public:
	/// \描述：获取麦克风设备ID
	/// \返回：如果方法调用成功，返回值是摄像头设备ID.
	///	如果失败，返回值是NULL.
	virtual const wchar_t* GetDeviceId() = 0;

	/// \描述：获取摄像头设备名
	/// \返回:如果方法调用成功，返回值是麦克分设置名.
	/// 如果失败， 返回值是NULL.
	virtual const wchar_t* GetDeviceName() = 0;

	/// \描述：所选设备标志
	/// \返回：如果返回true,表示该设备被选择.
	virtual bool IsSelectedDevice() = 0;

	virtual ~IMicInfo() {};
};

/// \描述：音频外放设备信息接口
///
class ISpeakerInfo
{
public:
	/// \描述：获取外放设备ID
	/// \返回：如果方法调用成功， 返回值是设备Id.
	/// 如果失败，返回值是NULL.
	virtual const wchar_t* GetDeviceId() = 0;

	/// \描述：获取外放设备名
	/// \返回：如果方法调用成功，返回值是设备名.
	/// 如果方法失败，返回值是NULL.
	virtual const wchar_t* GetDeviceName() = 0;

	/// \描述：所选设备标志
	/// \返回：如果返回值是true, 表示该设别是被选择的设备.
	virtual bool IsSelectedDevice() = 0;

	virtual ~ISpeakerInfo() {};
};

/*! \enum LimitFPSValue
	\描述 指定可用限制fps的值.
	下面是结构的详细描述
*/
enum LimitFPSValue
{
	limitfps_Not_Enable, ///<The feature is not enabled.
	limitfps_1_frame,///<1 frame per second.
	limitfps_2_frame,///<2 frames per second.
	limitfps_4_frame,///<4 frames per second.
	limitfps_6_frame,///<6 frames per second.
	limitfps_8_frame,///<8 frames per second.
	limitfps_10_frame,///<10 frames per second.
	limitfps_15_frame,///<15 frames per second.
};

enum SettingTabPage
{
	SettingTabPage_General,///<常规设置页.
	SettingTabPage_Audio,///<语音设置页.
	SettingTabPage_Video,///<视频设置页.
};
/*! \struct tagShowChatDlgParam
    \描述：展示会议中聊天窗口的参数.
	下面是结构的详细描述
*/
typedef struct tagShowSettingDlgParam
{
	HWND hParent;///< 父窗口句柄
	int top;///< 设置窗口顶部位置
	int left;///< 设置窗口左边位置
	HWND hSettingWnd;///< 返回设置窗口句柄
	bool bShow;///< 显示或隐藏
	bool bCenter;///<Enable to display the dialog at the center of the screen and discard the value of top and left 
	SettingTabPage eTabPageType;
	tagShowSettingDlgParam()
	{
		hParent = NULL;
 		top = 0;
		left = 0;
		hSettingWnd = NULL;
		bShow = true;
		bCenter = false;
		eTabPageType = SettingTabPage_General;
	}
}ShowSettingDlgParam;

/*! \struct tagSettingDlgShowTabPageOption
    \描述：定义设置窗口中的标签显示策略
    下面是结构的详细描述
*/
typedef struct tagSettingDlgShowTabPageOption
{
	bool bShowGeneral;///<True 表示显示常规页
	bool bShowVideo; ///<True 表示显示视频页
	bool bShowAudio;///<True 表示显示音频页
	bool bShowShareScreen; ///<True indicates to show share screen page
	bool bShowVirtualBackGround;///<True 表示显示虚拟背景页 
	bool bSHowRecording;///<True 表明显示录制页
	bool bShowAdvancedFeature;///<True 表明显示高级属性页
	bool bShowStatistics;///<True 表明显示统计页 
	bool bShowFeedback;///<True 表示显示反馈页
	bool bShowKeyboardShortcuts;///<True indicates to show keyboard shortcuts page
	bool bShowAccessibility;///<True 表示显示辅助功能页
	tagSettingDlgShowTabPageOption()
	{
		bShowGeneral = true;
		bShowVideo = true;
		bShowAudio = true;
		bShowShareScreen = true;
		bShowVirtualBackGround = true;
		bSHowRecording = true;
		bShowStatistics = true;
		bShowAccessibility = true;
		bShowKeyboardShortcuts = true;
		bShowAdvancedFeature = false;
		bShowFeedback = false;
	}

}SettingDlgShowTabPageOption;

/*! \enum SDK_TESTMIC_STATUS
    \描述： 测试时麦克风的通知状态.
    下面是结构的详细描述
*/
typedef	enum
{
	enuCanTest = 0, ///< 能调用测试TestMicStartRecording开始麦克风测试，此时调用TestMicStopTesting/TestMicPlayRecording无用.
	enuMicRecording,///< 能调用TestMicStopTesting/TestMicPlayRecording，此时调用TestMicStartRecording无用.
	enuCanPlay,		///< 能调用TestMicStopTesting/TestMicPlayRecording，此时调用TestMicStartRecording无用.
					///< enuCanPlay 状态表示SDK已经录制了6s的声音。在这种状态下，如果bHandled没有设置为true. SDK将主动调用TestMicStopTesting.
} SDK_TESTMIC_STATUS;

/// \描述：音频设备测试回调事件
//
class ITestAudioDeviceHelperEvent
{
public:
	/// \描述：在测试期间，通知当前麦克分音量和扬声器音量大小.
	/// \参数：MicVolume [out] 麦克风音量.
	/// \参数：SpkVolume [out] 扬声器音量.
	/// 这些值能用于在麦克风或扬声器测试期间显示音量进度条.
	virtual void OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume) = 0;

	/// \描述：未找到麦克风或扬声器时的通知回调.
	/// \参数 bMicOrSpk True 表示没有麦克风设备，False 表示没有扬声器设备.
	virtual void OnNoAudioDeviceIsUseful(bool bMicOrSpk) = 0; 

	/// 描述：麦克风测试期间的状态通知.
	/// \参数 status 查看 enum SDK_TESTMIC_STATUS 获取更多详细信息
	/// \参数 bHandled 设置为true时表示忽略SDK的默认麦克风状态逻辑. 
	/// \查看 SDK_TESTMIC_STATUS
	virtual void OnTestMicStatusChanged(SDK_TESTMIC_STATUS status,bool& bHandled) = 0; 

	/// \描述：在测试期间通知用户一个麦克分或扬声器设备被选择。SDK将关闭测试，用户需要手动重新启动测试.
	virtual void OnSelectedAudioDeviceIsChanged() = 0;
};

/// \描述： 音频设备测试接口.
///
class ITestAudioDeviceHelper
{
public:
	/// \描述：音频设备测试回调事件. 
	/// \参数：pEvent [in] 一个接收音频设备测试事件的指针 ITestAudioDeviceHelperEvent*. 
	/// \返回：如果方法调用成功，返回SDKErr_Success.
	/// 如果方法调用失败，返回值不是SDKErr_Success, 获取更多错误信息查看：SDKError enum.
	/// \查看：ITestAudioDeviceHelperEvent
	/// \注意：这个方必须在使用这个类的其他接口之前调用.
	virtual SDKError SetEvent(ITestAudioDeviceHelperEvent* pEvent) = 0;

	/// \描述：开始测试麦克风
	/// \参数 deviceID [in] 指定一个需要测试的麦克风，如果参数是一个错误的麦克风ID, SDK返回一个错误，否则SDK开始测试麦克风，并且设置为被选择.
	/// 如果没有参数输入，SDK测试默认的设备.
	///\注意：如果event没有设置, 这个方法没有作用.
	virtual SDKError TestMicStartRecording(const wchar_t* deviceID = NULL) = 0;

	/// \描述：停止测试麦克风，如果没有麦克风正在测试，SDK返回error.
	///\注意：如果event没有设置, 这个方法没有作用.
	virtual SDKError TestMicStopTesting() = 0;

	/// \描述：播放和麦克风录制的声音，如果没有麦克分测试，SDK返回一个错误。.
	///\注意：如果event没有设置, 这个方法没有作用.
	virtual SDKError TestMicPlayRecording() = 0;
	
	/// \描述：开始测试扬声器.
	/// \ 参数 deviceID [in] 指定一个测试的设备。如果参数时一个错误的ID,SDK返回一个错误，否则SDK测试指定的设备，并设置此设备为被选设备.
	/// 如果没有输入参数，SDK将测试默认的设备.
	///\注意：如果event没有设置, 这个方法没有作用.
	virtual SDKError TestSpeakerStartPlaying(const wchar_t* deviceID = NULL) = 0;
	
	/// \描述：通知扬声器测试，如果没有扬声器在测试，SDK将返回一个错误。
	///\注意：如果event没有设置, 这个方法没有作用.
	virtual SDKError TestSpeakerStopPlaying() = 0;
	
	/// \描述：设置音量回调间隔次数. 
	/// \参数：timerInterval [in] SDK默认每200ms发送一次麦克风和扬声器音量，这个功能允许用户设置其他的时间间隔..
	/// 时间间隔的单位时毫秒，如果值大于1000或小于50，SDK将会改为200
	///\注意：使用这个接口将停止麦克风/扬声器测试，所以应该在测试之前调用该接口.
	virtual SDKError SetTimerInterval(unsigned int timerInterval) = 0;
};

/// \描述：常规设置接口
///
class IGeneralSettingContext
{
public:
	/// \描述：设置是否使用双屏模式.
	/// \参数：bEnable [in] 指明使能或失效双屏模式.
	/// \返回：如果方法调用成功，返回值为 SDKErr_Success.
	/// 如果调用失败，返回值不是SDKErr_Success.具体错误查看 SDKError enum.
	virtual SDKError EnableDualScreenMode(bool bEnable) = 0;

	/// \描述：获取双屏模式的设置状态
	/// \返回：使能或无效
	virtual bool IsDualScreenModeEnabled() = 0;

	/// \描述：共享屏幕时关闭或打开aero模式
	/// \参数 bTurnoff [in] 指明关闭或打开加速模式
	/// \返回：如果方法调用成功，返回值为 SDKErr_Success.
	/// 如果调用失败，返回值不是SDKErr_Success.具体错误查看 SDKError enum.
	///仅支持window 7系统.
	virtual SDKError TurnOffAeroModeInSharing(bool bTurnoff) = 0;

	/// \描述：获取屏幕共享时的加速模式开关状态
	/// \返回：打开或关闭
	virtual bool IsAeroModeInSharingTurnOff() = 0;

	/// \描述：当共享窗口时，设置是否自动适应窗口.
	/// \参数：bEnable [in] 指明使能或失能自动适应.
	/// \返回：如果方法调用成功，返回值为 SDKErr_Success.
	/// 如果调用失败，返回值不是SDKErr_Success.具体错误查看 SDKError enum.
	virtual SDKError EnableAutoFitToWindowWhenViewSharing(bool bEnable) = 0;

	/// \描述：获取是否在屏幕共享中自动适应窗口.
	/// \返回：true 或者 false
	virtual bool IsAutoFitToWindowWhenViewSharingEnabled() = 0;

	/// \描述：设置是否加入会议时自动进入全屏
	/// \参数：bEnable [in] 指明使能或失能自动全屏
	/// \返回：如果方法调用成功，返回值为 SDKErr_Success.
	/// 如果调用失败，返回值不是SDKErr_Success.具体错误查看 SDKError enum.
	virtual SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \描述：获取加入会议时是否自动进入全屏的属性
	/// \返回: true 或者 false
	virtual bool IsAutoFullScreenVideoWhenJoinMeetingEnabled() = 0;

	/// \描述：设置是否在共享时自动进入全屏.
	/// \参数：bEnable [in] 指明失能或使能自动进入全屏
	/// \返回：如果方法调用成功，返回值为 SDKErr_Success.
	/// 如果调用失败，返回值不是SDKErr_Success.具体错误查看 SDKError enum.
	virtual SDKError EnableAutoFullScreenVideoWhenViewShare(bool bEnable) = 0;

	/// \描述：获取是否在共享时进入全屏.
	/// \返回：true 或者 false
	virtual bool IsAutoFullScreenVideoWhenViewShareEnabled() = 0;

	/// \描述：当屏幕共享时，是否使用分屏模式
	/// \参数：bEnable [in] 指明是否分屏模式
	/// \返回：如果方法调用成功，返回值为 SDKErr_Success.
	/// 如果调用失败，返回值不是SDKErr_Success.具体错误查看 SDKError enum.
	virtual SDKError EnableSplitScreenMode(bool bEnable) = 0;

	/// \描述：获取是否是分屏模式
	/// \返回：true 或 false
	virtual bool IsSplitScreenModeEnabled() = 0;
	
	/// \描述：当用户退出会议时，设置是否显示提示窗口。注意：仅对正常参会者有效，除去主持人.
	/// \参数：bEnable TRUE 指明能弹出提示框
	/// \返回：如果方法调用成功，返回值为 SDKErr_Success.
	/// 如果调用失败，返回值不是SDKErr_Success.具体错误查看 SDKError enum.
	virtual SDKError EnableDisplayReminderWindowWhenExit(bool bEnable) = 0;
	
	/// \描述：获取当用户退出会议时是否弹出提示框.
	/// \返回： TRUE 指明可以弹出. FALSE 不弹出.
	virtual bool IsDisplayReminderWindowWhenExitEnabled() = 0;
	
	/// \描述：设置是否显示会议时长.
	/// \参数：bEnable TRUE 表示显示. FALSE 不显示.
	/// \返回：如果方法调用成功，返回值为 SDKErr_Success.
	/// 如果调用失败，返回值不是SDKErr_Success.具体错误查看 SDKError enum.
	virtual SDKError EnableShowMyMeetingElapseTime(bool bEnable) = 0;
	
	/// \描述：获取是否显示会议时常.
	/// \返回：TRUE 显示. FALSE 不显示.
	virtual bool IsShowMyMeetingElapseTimeEnabled() = 0;
	
	/// \描述：当用户共享时，获取操作系统是否支持GPU计算
	/// \返回：TRUE 支持. FALSE 不支持.
	virtual bool IsCurrentOSSupportAccelerateGPUWhenShare() = 0;
	
	/// \描述：设置是否使用GPU计算（用户共享时）.
	/// \参数：bEnable TRUE 表明使能计算. FALSE 不支持.
	/// \返回：如果方法调用成功，返回值为 SDKErr_Success.
	/// 如果调用失败，返回值不是SDKErr_Success.具体错误查看 SDKError enum.
	virtual SDKError EnableAccelerateGPUWhenShare(bool bEnable) = 0;	
	
	/// \描述：获取是否在使用GPU计算
	/// \参数：[out]bEnable TRUE 表示使用GPU计算. FALSE 表示不使用. 仅当返回值为SDKErr_Success时有效。
	/// \返回：如果方法调用成功，返回值为 SDKErr_Success.
	/// 如果调用失败，返回值不是SDKErr_Success.具体错误查看 SDKError enum.
	virtual SDKError IsAccelerateGPUWhenShareEnabled(bool& bEnable) = 0;
	
	/// \描述：设置是否能远程控制所有应用.
	/// \参数：bEnable TRUE 表述能远程控制， FALSE 不能.
	/// \返回：如果方法调用成功，返回值为 SDKErr_Success.
	/// 如果调用失败，返回值不是SDKErr_Success.具体错误查看 SDKError enum.
	virtual SDKError EnableRemoteControlAllApplications(bool bEnable) = 0;	
	
	/// \描述：获取是否能远程控制所有应用.
	/// \返回：TRUE 能. FALSE 不能.
	virtual bool IsRemoteControlAllApplicationsEnabled() = 0;

	/// \brief Set the visibility of the green border when sharing the application.	/// \param bShow TRUE indicates to display the frame. FALSE hide.	/// \return If the function succeeds, the return value is SDKErr_Success.	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableGreenBorderWhenShare(bool bEnable) = 0;

	/// \brief Determine if the green border is enabled when user shares.
	/// \return TRUE indicates support. FALSE not.
	virtual bool IsGreenBorderEnabledWhenShare() = 0;

	/// \brief Determine if the 'limited sharing fps' feature is enabled when user shares.
	/// \return TRUE indicates support. FALSE not.
	virtual bool IsLimitFPSEnabledWhenShare() = 0;

	/// \brief Enable/disable the 'limited sharing fps' feature when uses shares.	/// \param bEnable TRUE indicates to enable the litmited fps feature. FALSE hide.	/// \return If the function succeeds, the return value is SDKErr_Success.	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableLimitFPSWhenShare(bool bEnable) = 0;

	/// \brief Get the limited sharing fps value when the 'limited sharing fps' feature is enabled.
	virtual ZhumuSDK::LimitFPSValue GetLimitFPSValueWhenShare() = 0;

	/// \brief Set the limited sharing fps value when the 'limited sharing fps' feature is enabled.
	/// \param value Specifies the limited fps value. It validates only when the 'limited sharing fps' feature is enabled.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetLimitFPSValueWhenShare(ZhumuSDK::LimitFPSValue value) = 0;
	
};

///\描述：预览视频相对于当前窗口的旋转角度通知.
typedef enum
{
	PREVIEW_VIDEO_ROTATION_ACTION_0, 			///< 无旋转
	PREVIEW_VIDEO_ROTATION_ACTION_CLOCK90,		///< 向左旋转
	PREVIEW_VIDEO_ROTATION_ACTION_CLOCK180,		///< 翻转.
	PREVIEW_VIDEO_ROTATION_ACTION_ANTI_CLOCK90	///< 向右旋转.
} PREVIEW_VIDEO_ROTATION_ACTION, *PPREVIEW_VIDEO_ROTATION_ACTION;

/// \描述：视频设备测试回调事件
///
class ITestVideoDeviceHelperEvent
{
public:
	/// \描述：未找到摄像头设备通知。
	virtual void OnNoVideoDeviceIsUseful() = 0;
	
	/// \描述：用户在测试期间选择摄像头设备的通知，SDK将关闭视频测试，用户需要重新开始测试。
	virtual void OnSelectedVideoDeviceIsChanged() = 0; 
	
	/// \描述：SDK需要一个窗口来显示视频预览， 这个通知表示没有窗口句柄或者使用了错误的窗口句柄。
	virtual void OnNoWindowToShowPreview() = 0;
};

/// \描述：视屏设备测试接口
///
class ITestVideoDeviceHelper
{
public:
	/// \描述：视频设备测试回调事件，注意：这个方法必须在此类的其他接口方法之前调用。
	/// \参数：pEvent [in] 一个接收视频设备测试事件的指针 ITestVideoDeviceHelperEvent* 
	/// \返回：如果方法调用成功，返回值为 SDKErr_Success.
	/// 如果调用失败，返回值不是SDKErr_Success.具体错误查看 SDKError enum.
	virtual SDKError SetEvent(ITestVideoDeviceHelperEvent* pEvent) = 0;
	
	/// \描述：设置显示预览视频的窗口及窗口大小 
	/// \参数： hParentWnd [in] 指定显示预览的窗口
	/// \参数： rc [in] 指定一个显示预览的矩形，默认为{0，0，0，0}，默认表示使用客户端的整个窗口大小显示预览视频。
	virtual SDKError SetVideoPreviewParentWnd(HWND hParentWnd, RECT rc = _SDK_TEST_VIDEO_INIT_RECT) = 0;
	
	/// \描述：开始测试摄像头。
	/// \参数： deviceID [in] 指定一个测试的摄像头设备。如果参数是一个错误的摄像头ID,SDK返回一个错误。否则SDK将测试改设备，并将其设置为选中状态。
	/// 如果没有输入参数，SDK将测试默认设备。.
	/// \注意： 如果没有设置event,或者没有设置窗口句柄，这个方法都不能工作。
	virtual SDKError TestVideoStartPreview(const wchar_t* deviceID = NULL) = 0;
	
	/// \描述： 停止测试摄像头。
	/// \注意：如果没有设置event,或者没有设置窗口句柄，这个方法都不能工作。
	virtual SDKError TestVideoStopPreview() = 0;
	
	/// \描述：预览视频旋转.
	/// \参数：action [in] 指定旋转动作。详细查看 enum PREVIEW_VIDEO_ROTATION_ACTION。
	/// \注意：如果没有设置event,或者没有设置窗口句柄，这个方法都不能工作。
	virtual SDKError TestVideoRotate(PREVIEW_VIDEO_ROTATION_ACTION action) = 0;	

	virtual ICameraController* GetTestCameraController() = 0;
};

/// \描述：视频设置内容回调事件。
class IVideoSettingContextEvent
{
public:
	/// \描述： 如果sdk检测到计算机摄像机设备的回调
	/// \参数： pNewCameraList 是新插入计算机的摄像头设备. 
	virtual void onComputerCamDeviceChanged(std::vector<ICameraInfo*> pNewCameraList) = 0;

	/// \描述： 通知用户有一个摄像头设备被选择
	/// \参数： deviceId 被选择的设备
	/// \参数： deviceName 备选的设备的设备名
	virtual void onDefaultCamDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) = 0;
};
/// \描述：视频设置接口。
///
class IVideoSettingContext
{
public:
	/// \描述：获取摄像头设备列表。
	/// \返回：如果方法调用成功，返回值是摄像头列表指针
	/// 如果方法调用失败，返回值是NULL
	virtual std::vector<ICameraInfo* > GetCameraList() = 0;

	/// \描述：选择摄像头设备。
	/// \参数：[in] deviceId 被选择设备的设备ID
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError SelectCamera(const wchar_t* deviceId) = 0;

	/// \描述：启用/禁用视频镜像效果
	/// \param [in] bEnable 启用/禁用视频镜像效果
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableVideoMirrorEffect(bool bEnable) = 0;

	/// \描述：获取启用/禁用视频镜像效果
	/// \返回：启用/禁用
	virtual bool IsVideoMirrorEffectEnabled() = 0;

	/// \描述：设置启用/禁用美颜效果
	/// \参数：[in] bEnable 启用/禁用美颜效果
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableFaceBeautyEffect(bool bEnable) = 0;

	/// \描述：获取启用/禁用美颜效果
	/// \返回：启用/禁用.
	virtual bool IsFaceBeautyEffectEnabled() = 0;

	/// \描述：设置启用/禁用高清视频
	/// \参数：[in] bEnable 指明启动或禁止使用高清视频
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableHDVideo(bool bEnable) = 0;

	/// \描述：获取是否启用/禁用高清视频
	/// \返回：启用/禁用.
	virtual bool IsHDVideoEnabled() = 0;

	// \描述：设置启用/禁用在视频上显示名字
	/// \param [in] bEnable 启用/禁用在视频上显示名字
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableAlwaysShowNameOnVideo(bool bEnable) = 0;

	/// \描述：获取启用/禁用在视频上显示名字
	/// \返回：启用/禁用.
	virtual bool IsAlwaysShowNameOnVideoEnabled() = 0;

	/// \描述：设置是否在加入会议时关闭视频
	/// \参数：[in] bEnable 是否在加入会议时关闭视频
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \描述：获取是否在加入会议时关闭视频
	/// \返回：Enable or disable.
	virtual bool IsAutoTurnOffVideoWhenJoinMeetingEnabled() = 0;
	
	/// \描述：设置是否使用16:9视频模式
	/// \参数：bEnable [in] 是否使用16:9视频模式
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableAlwaysUse16v9(bool bEnable) = 0;

	/// \描述：获取是否使用16:9视频模式
	/// \返回：是/否.
	virtual bool IsAlwaysUse16v9() = 0;

	/// \描述：设置启用/禁用视频聚光灯.
	/// \参数：bEnable [in] 启用/禁用视频聚光灯.
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableSpotlightSelf(bool bEnable) = 0;

	/// \描述：获取启用/禁用视频聚光灯.
	/// \返回：是/否
	virtual bool IsSpotlightSelfEnabled() = 0;

	/// \描述：设置是否使用硬件加速
	/// \参数：bEnable [in] 是否使用硬件加速
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableHardwareEncode(bool bEnable) = 0;

	/// \描述：获取是否使用硬件加速
	/// \返回：是/否.
	virtual bool IsHardwareEncodeEnabled() = 0;

	/// \描述：设置启用或禁用在画廊视图中每个屏幕最多显示49个参与者.
	/// \参数：bEnable [in] 启用或禁用在画廊视图中每个屏幕最多显示49个参与者.
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError Enable49VideoesInGallaryView(bool bEnable) = 0;

	/// \描述：获取启用或禁用在画廊视图中每个屏幕最多显示49个参与者
	/// \返回：启用/禁用.
	virtual bool Is49VideoesInGallaryViewEnabled() = 0;

	/// \描述：设置是否隐藏没有视频的参会者.
	/// \参数：bEnable [in] 是否隐藏没有视频的参会者.
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableHideNoVideoUsersOnWallView(bool bEnable) = 0;

	/// \描述：获取是否隐藏没有视频的参会者状态.
	/// \返回：是/否.
	virtual bool IsHideNoVideoUsersOnWallViewEnabled() = 0;

	/// \描述：获取用来测试摄像头设备所指向ITestVideoDeviceHelper对象的指针
	/// \返回：如果成功，返回指向ITestVideoDeviceHelper的指针.
	/// 如果失败，返回NULL.
	/// 更多详细信息查看ITestVideoDeviceHelper.
	virtual ITestVideoDeviceHelper* GetTestVideoDeviceHelper() = 0;

	/// \描述：视频设置监视回调事件. 
	/// \参数：pEvent 一个指向IVideoSettingContextEvent对象的指针. 
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	/// 更多详细信息查看IVideoSettingContextEvent.
	/// \注意：如果想监视新插入的视频设备，必须调用该方法.
	virtual SDKError SetVideoDeviceEvent(IVideoSettingContextEvent* pEvent) = 0;
};

/// \描述：音频设置回调事件
///
class IAudioSettingContextEvent
{
public:
	/// \描述： SDK检测到计算机麦克分设备变化时的回调事件.
	/// \参数： pNewMicList 新插入计算机的麦克风设备列表. 
	virtual void onComputerMicDeviceChanged(std::vector<IMicInfo*> pNewMicList) = 0;
	
	/// \描述： SDK检测到计算机扬声器设备变化时的回调事件.
	/// \参数： pNewSpeakerList 新插入计算机的扬声器设备列表. 
	virtual void onComputerSpeakerDeviceChanged(std::vector<ISpeakerInfo*> pNewSpeakerList) = 0;

	/// \描述： 一个麦克风设备被选择的通知事件.
	/// \参数： deviceId 指定一个设备被选择.
	/// \参数： deviceName 指定被选择的名称.
	virtual void onDefaultMicDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \描述： 一个扬声器设备被选择的通知事件.
	/// \参数： deviceId 指定一个设备被选择.
	/// \参数： deviceName 指定被选择的名称.
	virtual void onDefaultSpeakerDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) = 0;
};

/// \描述：音频设置接口
///
class IAudioSettingContext
{
public:
	/// \描述：获取麦克风设备列表
	/// \返回：如果方法调用成功，返回值是音频设备指针列表
	/// 如果方法调用失败，返回值是NULL
	virtual std::vector<IMicInfo* > GetMicList() = 0;

	/// \简述：选择麦克风设置
	/// \参数：deviceId [in] 指明被选设备
	/// \参数：deviceName [in] 指明被絮设备，应该和指定的设备Id相同
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError SelectMic(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \简述：Get speaker device list
	/// \返回：如果方法调用成功，返回值是扬声器设备指针列表
	/// 如果失败，返回值是NULL If the function fails, the return value is NULL.
	virtual std::vector<ISpeakerInfo* > GetSpeakerList() = 0;

	/// \简述：选择扬声器设备
	/// \参数：deviceId [in] 被选设备.
	/// \参数：deviceName [in] 被选设备名字，应该和指定的设备Id相同
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError SelectSpeaker(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \简述：设置是否加入会议是自动打开音频
	/// \参数：bEnable [in] 是否自动打开音频.
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableAutoJoinAudio(bool bEnable) = 0;

	/// \描述：获取加入会议时是否自动打开音频的状态
	/// \返回：是或否
	virtual bool IsAutoJoinAudioEnabled() = 0;

	/// \描述：设置是否自动调整麦克风音量.
	/// \参数：bEnable [in] 是否自动调整麦克风音量
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableAutoAdjustMic(bool bEnable) = 0;

	/// \描述：获取是否能自动调整麦克风音量
	/// \返回：是否
	virtual bool IsAutoAdjustMicEnabled() = 0;

	/// \描述： 设置是否打开立体声
	/// \参数： bEnable [in] 指定是否打开立体声
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableStereoAudio(bool bEnable) = 0;

	/// \描述：获取是否发打开立体声
	/// \返回：是否
	virtual bool IsStereoAudioEnable() = 0;

	/// \描述：设置是否使用麦克风原始输入
	/// \参数：bEnable [in] 指定是否使用原始输入
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableMicOriginalInput(bool bEnable) = 0;

	/// \描述：获取是否使用麦克风原始输入状态
	/// \返回：是否
	virtual bool IsMicOriginalInputEnable() = 0;
	
 	/// \描述：设置是否使用按下空格键说话
	/// \参数：bEnable [in] 是否按下空格键说话
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableHoldSpaceKeyToSpeak(bool bEnable) = 0;

	/// \描述：获取是否使用按下空格键说话
	/// \返回：是或否
	virtual bool IsHoldSpaceKeyToSpeakEnabled() = 0;

	/// \描述：设置加入voip会议时总是静音
	/// \参数：bEnable [in] 是否总是静音加入
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableAlwaysMuteMicWhenJoinVoip(bool bEnable) = 0;

	/// \描述：获取是否静音加入voip会议
	/// \返回：是否
	virtual bool IsAlwaysMuteMicWhenJoinVoipEnabled() = 0;

	/// \描述：设置是否第三放音频加入时提示
	/// \参数：bEnable TRUE 表示提示
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableSuppressAudioNotify(bool bEnable) = 0;

	/// \描述：获取当第三方音频加入时是否提示的状态
	/// \返回：是或否
	virtual bool IsSuppressAudioNotifyEnabled() = 0;

	/// \描述：获取测试音频设备对象的指针ITestAudioDeviceHelper*
	/// \返回：如果方法调用成功，返回指向ITestAudioDeviceHelper的指针
	/// 如果失败，返回NULL
	/// 获取更多信息，查看 ITestAudioDeviceHelper.
	virtual ITestAudioDeviceHelper* GetTestAudioDeviceHelper() = 0;
	
	/// \描述：设置选择麦克风的音量
	/// \参数：value [in] 音量. 值从 0 到 255
	/// 如果没有麦克风被选择，SDK将使用默认麦克风
	virtual SDKError	SetMicVol(FLOAT& value) = 0;
	
	/// \描述：获取麦克风音量
	/// \param value [out] 麦克风音量值
	virtual SDKError    GetMicVol(FLOAT& value) = 0;
	
	/// \描述：设置选择扬声器的音量
	/// \参数：value [in]指定扬声器的音量.值从0到255
	/// 如果没设置扬声器，SDK将使用默认扬声器
	virtual SDKError	SetSpeakerVol(FLOAT& value) = 0;
	
	/// \描述：获取选择扬声器的音量
	/// \参数：value [out] 扬声器的音量
	virtual SDKError    GetSpeakerVol(FLOAT& value) = 0;

	/// \描述：设置音频设备监视回调事件
	/// \参数表：pEvent 一个指向接受音频设备事件的指针 IAudioSettingContextEvent*
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	/// 详细查看 IAudioSettingContextEvent
	/// \注意：如果想监视音频设备的拔插，必须调用该方法
	virtual SDKError SetAudioDeviceEvent(IAudioSettingContextEvent* pEvent) = 0;

	/// \描述：设置是否使能消除回音
	/// \参数：bEnable True 能消除回音, FALSE 不能.
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableEchoCancellation(bool bEnable) = 0;
	
	/// \描述：获取是否消除回音
	/// \返回：如果是TRUE, 意味着能消除回音
	virtual bool IsEchoCancellationEnabled() = 0;
	

};

class IRecordingSettingContextEvent
{
public:
	/// \描述：当前云录制存储信息通知
	/// \参数：存储总大小
	/// \参数：存储已使用大小
	/// \参数：允许超出大小
	virtual void onCloudRecordingStorageInfo(INT64 storage_total_size, INT64 storage_used_size, bool allow_exceed_storage) = 0;
};

/// \描述：录制设置接口
///
class IRecordingSettingContext
{
public:
	/// \描述：设置在设置窗口中的录制路径
	/// \参数：szPath[in] 指明录制路径
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError SetRecordingPath(const wchar_t* szPath) = 0;

	/// \描述：获取设置窗口中的录制路径
	/// \返回：录制路径
	virtual const wchar_t* GetRecordingPath() = 0;
	
	/// \描述：设置录制设置event
	/// \参数：pEvent 录制设置event
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError SetRecordingSettingEvent(IRecordingSettingContextEvent* pEvent) = 0;
	
	/// \描述：检测是否用户有获取云录制信息的权限
	/// \返回：TRUE 表示用户有权限. FALSE 表示没权限.
	virtual bool CanGetCloudRecordingStorageInfo() = 0;

	/// \描述：获取云录制信息
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	/// 如果返回值是SDKErr_Success, 取回信息后。IRecordingSettingContextEvent.onCloudRecordingStorageInfo()
	virtual SDKError GetCloudRecordingStorageInfo() = 0;

	/// \描述：获取录制管理URL Get the recording management URL.
	/// \返回 TRUE 表示可以 FALSE 表示不能.
	virtual const wchar_t* GetRecordingManagementURL() = 0;
	
	/// \描述：设置是否能获取到录制管理URL
	/// \参数：[out]bEnable TRUE 意味着录制管理URL能被获取到，FALSE表示不能. 仅仅当返回值是SDKErr_Suucess时才有效
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError CanGetRecordingManagementURL(bool& bEnable) = 0;
	
	/// \描述： 设置是否能在会议结束后选择录制文件保存位置
	/// \参数 bEnable TRUE 表示能, FALSE 不能.
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableSelectRecordFileLocationAfterMeeting(bool bEnable) = 0;
	
	/// \描述：获取是否能在会议结束后选择录制文件的保存位置 Check if the function of selecting storage path for recording file is enabled.
	/// \返回：TRUE 表示能. FALSE 表示不能.
	virtual bool IsSelectRecordFileLocationAfterMeetingEnabled() = 0;
	
	/// \描述：设置是否开启多路音频录制
	/// \参数：bEnable TRUE 表示开启. FALSE 不开启.
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableMultiAudioStreamRecord(bool bEnable) = 0;
	
	/// \描述：获取是否在使用多路音频录制
	/// \返回：TRUE 表示是. FALSE 否.
	virtual bool IsMultiAudioStreamRecordEnabled() = 0;
	
	/// \描述：设置是否使用时间戳水印
	/// \参数： bEnable TRUE 表示使用. FALSE 表示不使用.
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableAddTimestampWatermark(bool bEnable) = 0;
	
	/// \描述：获取是否使用时间戳水印
	/// \返回：TRUE 表述 使用. FALSE 不使用.
	virtual bool IsAddTimestampWatermarkEnabled() = 0;
	
	/// \描述：设置使用/禁用第三方视频编辑器的优化 
	/// \参数：bEnable TRUE 表示使用. FALSE 不使用.
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableOptimizeFor3rdPartyVideoEditor(bool bEnable) = 0;
	
	/// \描述：获取使用/禁用第三方视频编辑器的优化
	/// \返回：TRUE 使用. FALSE 禁用.
	virtual bool IsOptimizeFor3rdPartyVideoEditorEnabled() = 0;
	
	/// \描述： 设置启用/禁用在共享时显示视频缩略图 .
	/// \参数：bEnable TRUE 启用. FALSE 禁用.
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnableShowVideoThumbnailWhenShare(bool bEnable) = 0;
	
	/// \描述：获取启用/禁用在共享时显示视频缩略图
	/// \返回：TRUE 启用. FALSE 禁用.
	virtual bool IsShowVideoThumbnailWhenShareEnabled() = 0;
	
	/// \描述：设置启用/禁用将视频布局放置在记录中的共享内容旁边 
	/// \参数：bEnable TRUE 启用. FALSE 禁用.
	/// \返回：如果方法调用成功， 返回值是 SDKErr_Success.
	/// 如果方法调用失败，返回值是其他错误信息，具体查看SDKError enum.
	virtual SDKError EnablePlaceVideoNextToShareInRecord(bool bEnable) = 0;
	
	/// \描述：获取启用/禁用将视频布局放置在记录中的共享内容旁边 
	/// \返回：TRUE 启用. FALSE 禁用..
	virtual bool IsPlaceVideoNextToShareInRecordEnabled() = 0;
	
};

enum SettingsNetWorkType 
{
	SETTINGS_NETWORK_WIRED	= 0,
	SETTINGS_NETWORK_WIFI	= 1,
	SETTINGS_NETWORK_PPP	= 2,
	SETTINGS_NETWORK_3G		= 3,
	SETTINGS_NETWORK_OTHERS	= 4,

	SETTINGS_NETWORK_UNKNOWN = -1,
};

enum SettingConnectionType
{
	SETTINGS_CONNECTION_TYPE_CLOUD,
	SETTINGS_CONNECTION_TYPE_DIRECT,
	SETTINGS_CONNECTION_TYPE_UNKNOWN = -1,
};
typedef struct tagOverallStatisticInfo
{
	SettingsNetWorkType net_work_type_;  	
	SettingConnectionType connection_type_; 
	const wchar_t* proxy_addr_;
	tagOverallStatisticInfo()
	{
		net_work_type_ = SETTINGS_NETWORK_UNKNOWN;
		connection_type_ = SETTINGS_CONNECTION_TYPE_UNKNOWN;
		proxy_addr_ = NULL;
	}
}OverallStatisticInfo;

typedef struct tagAudioSessionStatisticInfo
{
	int frequency_send_; //KHz
	int frequency_recv_; //KHz
	int latency_send_;//ms
	int latency_recv_;//ms
	int jitter_send_;//ms
	int jitter_recv_;//ms
	float packetloss_send_;//%
	float packetloss_recv_;//%

	tagAudioSessionStatisticInfo()
	{
		memset(this, 0, sizeof(tagAudioSessionStatisticInfo));
	}
}AudioSessionStatisticInfo;

typedef struct tagASVSessionStatisticInfo
{
	int latency_send_;//ms
	int latency_recv_;//ms
	int jitter_send_;//ms
	int jitter_recv_;//ms
	float packetloss_send_max_;//%
	float packetloss_recv_max_;//%
	float packetloss_send_avg_;//%
	float packetloss_recv_avg_;//%
	int resolution_send_; //HIWORD->height,LOWORD->width
	int resolution_recv_; //HIWORD->height,LOWORD->width 
	int fps_send_;//fps
	int fps_recv_;//fps
	tagASVSessionStatisticInfo()
	{
		memset(this, 0, sizeof(tagASVSessionStatisticInfo));
	}
}ASVSessionStatisticInfo;


/// \描述：统计设置接口
///
class IStatisticSettingContext
{
public:
	/// \描述： 查询统计信息
	/// \param info_ [out] 统计信息输出,具体查看 OverallStatisticInfo
	/// 方法调用成功返回SDkErr_Success, 如果调用失败，返回值是其他错误信息，具体查看 SDKError enum.
	virtual SDKError QueryOverallStatisticInfo(OverallStatisticInfo& info_) = 0;

	/// \描述： 查询音频信息
	/// \param info_ [out] 音频信息输出,具体查看 AudioSessionStatisticInfo
	/// 方法调用成功返回SDkErr_Success, 如果调用失败，返回值是其他错误信息，具体查看 SDKError enum.
	virtual SDKError QueryAudioStatisticInfo(AudioSessionStatisticInfo& info_) = 0;

	/// \描述：查询视频信息
	/// \param info_ [out] 视频信息输出,具体查看 ASVSessionStatisticInfo
	/// 方法调用成功返回SDkErr_Success, 如果调用失败，返回值是其他错误信息，具体查看 SDKError enum.
	virtual SDKError QueryVideoStatisticInfo(ASVSessionStatisticInfo& info_) = 0;

	/// \描述：查询共享信息
	/// \param info_ [out] 共享信息输出,具体查看 ASVSessionStatisticInfo
	/// 方法调用成功返回SDkErr_Success, 如果调用失败，返回值是其他错误信息，具体查看 SDKError enum.
	virtual SDKError QueryShareStatisticInfo(ASVSessionStatisticInfo& info_) = 0;
};

/// \描述：辅助设置接口
///
class IAccessibilitySettingContext
{
public:
	/// \描述：是否总是在会议窗口中显示会议控制器。
	/// \参数：bEnable TRUE 表示显示，FALSE 表示不显示。
	/// \返回：如果方法调用成功， 返回值是SDKErr_Success.
	/// 如果失败，返回错误信息，具体查看SDKError enum.
	virtual SDKError EnableAlwaysShowMeetingControls(bool bEnable) = 0;

	/// \描述：获取当前在会议窗口总是显示会议控制器的状态。
	/// \参数：bEnable TRUE 表示显示， FALSE 表示不显示
	/// \返回：如果总是显示，返回true
	virtual SDKError IsAlwaysShowMeetingControlsEnable(bool& bEnable) = 0;
};

/// \描述：设置用户策略接口
///
class ISettingUIStrategy
{
public:
	/// \描述：在常规设置标签中显示高级特征。
	/// \参数：bDisable [in] 表明显示或不显示。
	virtual void DisableAdvancedFeatures4GeneralSetting(bool bDisable) = 0;

	/// \描述：不显示账户设置标签。
	/// \参数：bDisable [in] 表显示或不显示。
	virtual void DisableAccountSettingTabPage(bool bDisable) = 0;

	/// \描述：自定义标签页的显示或隐藏
	/// \参数：showOption True 表示显示相应的标签页。
	virtual void ConfSettingDialogShownTabPage(SettingDlgShowTabPageOption showOption) = 0;
};
/// \brief Virtual background image information interface.
///
class IVirtualBGImageInfo
{
public:
	/// \brief Determine the usage of current image.
	/// \return TRUE indicates that current image is used as the virtual background image.
	virtual bool isSelected() = 0;

	/// \brief Get the file path of current image.
	/// \return If the function succeeds, the return value is the file path of current image.
	///Otherwise failed, the return value is NULL.
	virtual const wchar_t* GetImageFilePath() = 0;

	/// \brief Get the name of current image.
	/// \return If the function succeeds, the return value is the name of current image.
	///Otherwise failed, the return value is NULL.
	virtual const wchar_t* GetImageName() = 0;

	virtual ~IVirtualBGImageInfo() {};
};

/// \brief Virtual background context Callback Event.
///
class IVirtualBGSettingContextEvent
{
public:
	/// \brief Callback event of notification that the default virtual background images supplied by ZOOM are downloaded.
	virtual void onVBImageDidDownloaded() = 0;
	
	/// \brief Callback event of notification that the virtual background effect is updated with the selected color.
	/// \param selectedColor The RGB value of the selected color, organized in the format 0xFFRRGGBB. 
	virtual void onGreenVBDidUpdateWithReplaceColor(DWORD selectedColor) = 0;

	/// \brief Callback event of notification that the virtual background image is changed.
	virtual void onSelectedVBImageChanged() = 0;
};

/// \brief Virtual background setting interface.
class IVirtualBGSettingContext
{
public:
	/// \brief Virtual background callback handler. 
	/// \param pEvent A pointer to the IVirtualBGSettingContextEvent that receives virtual background event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Call the function before using any other interface of the same class.
	virtual SDKError SetVirtualBGEvent(IVirtualBGSettingContextEvent* pEvent) = 0;

	/// \brief Determine if the virtual background feature is supported by the meeting.
	/// \return TRUE indicates that the meeting supports the virtual background feature.
	virtual bool IsSupportVirtualBG() = 0;

	/// \brief Determine if the smart virtual background feature can be supported by the machine.
	/// \return TRUE indicates that the machine can supports to use smart virtual background feature.
	virtual bool IsSupportSmartVirtualBG() = 0;

	/// \brief Determine if the green screen is using for the virtual background feature in the meeting.
	/// \return TRUE indicates to use the green screen for the virtual background feature.
	virtual bool IsUsingGreenScreenOn() = 0;

	/// \brief Set to use the green screen for the virtual background feature.
	/// \param bUse Specify to use the green screen or not.TRUE means using the green screen. FALSE means using smart virtual background feature.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///\remarks If the machine can not support smart virtual background feature, Calling of this interface with parameter 'FALSE'will return SDKERR_WRONG_USEAGE.
	virtual SDKError SetUsingGreenScreen(bool bUse) = 0;

	/// \brief Add a new image as the virtual background image and to the image list.
	/// \param file_path Specify the file name of the image. It must be the full path with the file name.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError AddBGImage(const wchar_t* file_path) = 0;

	/// \brief Remove an image from the virtual background image list.
	/// \param pRemoveImage Specify the image to remove. To get extended error information, see \link IVirtualBGImageInfo \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RemoveBGImage(IVirtualBGImageInfo* pRemoveImage) = 0;

	/// \brief Get the list of the virtual background images.
	/// \return If there are images in the list, the return value is a list of the poiters to IVirtualBGImageInfo.
	///Otherwise return NULL. To get extended error information, see \link IVirtualBGImageInfo \endlink enum.
	virtual std::vector<IVirtualBGImageInfo*> GetBGImageList() = 0;

	/// \brief Specify an image to be the virtual background image.
	/// \param pImage Specify the image to use. To get extended error information, see \link IVirtualBGImageInfo \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError UseBGImage(IVirtualBGImageInfo* pImage) = 0;

	/// \brief Get the selected color after called BeginSelectReplaceVBColor() and selected a color.
	/// \return If the function succeeds, the return value is the selected color.
	///Otherwise 0xFF000000. The value is the same one as the callback IVirtualBGSettingContextEvent.onGreenVBDidUpdateWithReplaceColor() does.
	virtual DWORD GetBGReplaceColor() = 0;

	/// \brief Start to capture a color from video preview.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError BeginSelectReplaceVBColor() = 0;

	/// \brief Get the pointer to ITestVideoDeviceHelper which is used to preview the video with virtual background image.
	/// \return If the function succeeds, the return value is the pointer to ITestVideoDeviceHelper.
	///Otherwise failed, returns NULL.
	///For more details, see \link ITestVideoDeviceHelper \endlink.
	virtual ITestVideoDeviceHelper* GetTestVideoDeviceHelper() = 0;
};

/// \描述：会议设置接口
///
class ISettingService
{
public:

	/// \描述：显示会议设置窗口
	/// \参数：[in] param 指明显示聊天窗口
	/// 如果方法调用成功，返回值是SDKErr_Success,如果失败返回值不是 SDKErr_Success，
	/// 获取详细错误五错误信息查看 SDKError enum.
	virtual SDKError ShowSettingDlg(ShowSettingDlgParam& param) = 0;

	/// \描述：隐藏会议设置窗口
	/// 如果方法调用成功，返回值是SDKErr_Success,如果失败返回值不是 SDKErr_Success，
	/// 获取详细错误五错误信息查看 SDKError enum.
	virtual SDKError HideSettingDlg() = 0;

	/// \描述：获取常规设置接口
	/// \返回：如果功能调用成功， 返回一个指向IGeneralSettingContext对象的指针。
	/// 如果失败，返回NULL。
	/// 获取更多详细介绍，查看 IGeneralSettingContext
	virtual IGeneralSettingContext* GetGeneralSettings() = 0;

	/// \描述：获取音频设置接口
	/// \返回：如果功能调用成功， 返回一个指向IAudioSettingContext对象的指针。
	/// 如果失败，返回NULL。
	/// 获取更多详细介绍，查看 IAudioSettingContext
	virtual IAudioSettingContext* GetAudioSettings() = 0;

	/// \描述：获取视频设置接口
	/// \返回：如果功能调用成功， 返回一个指向IVideoSettingContext对象的指针。
	/// 如果失败，返回NULL。
	/// 获取更多详细介绍，查看 IVideoSettingContext
	virtual IVideoSettingContext* GetVideoSettings() = 0;

	/// \描述：获取录制设置接口
	/// \返回：如果功能调用成功， 返回一个指向IRecordingSettingContext对象的指针。
	/// 如果失败，返回NULL。
	/// 获取更多详细介绍，查看 IRecordingSettingContext
	virtual IRecordingSettingContext* GetRecordingSettings() = 0;

	/// \描述：获取统计设置接口
	/// \返回：如果功能调用成功， 返回一个指向IStatisticSettingContext对象的指针。
	/// 如果失败，返回NULL。
	/// 获取更多详细介绍，查看 IStatisticSettingContext
	virtual IStatisticSettingContext* GetStatisticSettings() = 0;

	/// \描述：获取辅助设置接口
	/// \返回：如果方法调用成功,返回一个指向IAccessibilitySettingContext对象的指针。
	///	如果失败，返回NULL。
	/// 获取更多详细介绍，查看 IAccessibilitySettingContext.
	virtual IAccessibilitySettingContext* GetAccessibilitySettings() = 0;

	/// \描述：获取用户设置策略接口
	/// \返回：如果方法调用成功， 返回一个指向ISettingUIStrategy对象的指针
	///	如果失败， 返回NULL。
	/// 获取更多详细介绍，查看ISettingUIStrategy.
	virtual ISettingUIStrategy* GetSettingUIStrategy() = 0;

	/// \brief Get virtual background interface.
	/// \return If the function succeeds, the return value is an object pointer to IVirtualBGSettingContext.
	///Otherwise failed, returns NULL.
	///For more details, see \link IVirtualBGSettingContext \endlink.
	virtual IVirtualBGSettingContext* GetVirtualBGSettings() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif