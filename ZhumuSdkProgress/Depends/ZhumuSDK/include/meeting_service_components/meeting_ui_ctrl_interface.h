/*!
* \文件：meeting_ui_ctrl_interface.h
* \描述：会议服务接口UI控制器
* \仅适用于zhumu风格的UI模式
*/
#ifndef ZHUMU_MEETING_UI_CTRL_INTERFACE_H_
#define ZHUMU_MEETING_UI_CTRL_INTERFACE_H_
#include "..\zhumu_sdk_def.h"

/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum SDKMeetingUIType
\描述：会议ui的类型。
更详细的结构描述。
*/
enum SDKMeetingUIType
{
	SDK_Meeting_UI_None,
	SDK_Meeting_UI_VideoWall_Mode,
	SDK_Meeting_UI_ActiveRender_Mode,
};

/*! \struct tagVideoWallPageInfoParam
\描述：视频页面的信息。
更详细的结构描述。
*/
typedef struct tagVideoWallPageInfoParam
{
	int nCurrentPage;
	int nTotalPages;
}VideoWallPageInfoParam;

/*! \struct tagShowChatDlgParam
\描述：显示会议聊天对话框参数。
更详细的结构描述。
*/
typedef struct tagShowChatDlgParam
{
	HWND hParent;///<父窗口句柄
	RECT rect;///< 聊天对话框位置
	HWND hChatWnd;///< 返回聊天窗口句柄
	tagShowChatDlgParam()
	{
		hParent = NULL;
		hChatWnd = NULL;
		rect.top = 0;
		rect.bottom = 0;
		rect.left = 0;
		rect.right = 0;
	}
}ShowChatDlgParam;

/*! \enum SDKFloatVideoType
\描述：浮动视频ui的类型。
更详细的结构描述。
*/
enum SDKFloatVideoType
{
	FLOATVIDEO_List,
	FLOATVIDEO_Small,
	FLOATVIDEO_Large,
	FLOATVIDEO_Minimize,
};

/*! \enum SDKMinimizeUIMode
\描述：最小化UI模式的类型。
更详细的结构描述。
*/
enum SDKMinimizeUIMode
{
	MinimizeUIMode_NONE,
	MinimizeUIMode_SHARE,
	MinimizeUIMode_VIDEO,
	MinimizeUIMode_ACTIVESPEAKER,
};

/*! \struct tagSplitScreenInfo
\描述：分屏模式信息。
更详细的结构描述.
*/
typedef struct tagSplitScreenInfo
{
	bool bSupportSplitScreen;
	bool bInSplitScreenMode;
	tagSplitScreenInfo()
	{
		bSupportSplitScreen = false;
		bInSplitScreenMode = false;
	}
}SplitScreenInfo;

/*! \enum AudioCallbackActionInfo
    \描述：用户在获取回调事件"IMeetingUIControllerEvent::onAudioBtnClicked()"后建议采取的操作 
    下面是更详细的结构描述。
*/
enum AudioCallbackActionInfo
{
	ACTION_NONE = 0,///<用于初始化.
	ACTION_CHOOSE_AUDIO_DEVICE_NOAUDIODEVICECONNECTTED,///<选择音频设备，因为尚未连接音频设备。
	ACTION_CHOOSE_AUDIO_DEVICE_COMPUTERAUDIODEVICEERROR,///<选择音频设备，因为在连接计算机音频设备时发生错误。
	ACTION_CHOOSE_AUDIO_DEVICE_PHONECALLDEVICEERROR,///<选择音频设备，因为在连接电话呼叫设备时发生错误。
	ACTION_NEED_JOIN_VOIP,///<需要假如voip
	ACTION_MUTE_UNMUTE_AUDIO,///<根据 "AudioBtnClickedCallbackInfo::userid_MuteUnmute" 静止或开启用户音频
	ACTION_SHOW_AUDIO_SETTING_WINDOW,///<显示音频设置窗口
};

/*! \struct tagAudioBtnClickedCallbackInfo
    \描述: 用户在获取回调事件"IMeetingUIControllerEvent::onAudioBtnClicked()"后建议采取的操作 
    下面是更详细的结构描述。
*/
typedef struct tagAudioBtnClickedCallbackInfo
{
	unsigned int userid_MuteUnmute;///<应禁用或取消禁用的用户的id。当不需要静音或取消静音操作时，该值为0
	AudioCallbackActionInfo audio_clicked_action;///<建议用户采取的操作。
	tagAudioBtnClickedCallbackInfo()
	{
		userid_MuteUnmute = 0;
		audio_clicked_action = ACTION_NONE;
	}

}AudioBtnClickedCallbackInfo;

/// \描述：Meeting UI Controller回调事件.
///
class IMeetingUIControllerEvent
{
public:
	/// \描述：当单击Invite按钮时的回调过程。
	/// \参数：[in out] bHandled 如果应用程序显示自己的invite对话框，则将其设置为TRUE。如果为FLASE，则为默认值。
	/// \注意：如果bhandle未设置为true。无论应用程序是否处理，都会显示默认的Zhumu invite对话框。
	virtual void onInviteBtnClicked(bool& bHandled) = 0;
	virtual void onStartShareBtnClicked() = 0;
	virtual void onEndMeetingBtnClicked() = 0;
	virtual void onParticipantListBtnClicked() = 0;
	virtual void onCustomLiveStreamMenuClicked() = 0;

	/// \描述：只在SDK无法显示默认的ZHUMU INVITE对话框时发出通知。
	virtual void onZoomInviteDialogFailed() = 0;

	/// \描述：单击CC菜单的回调事件。
	/// \注意：除非用户重定向单击CUSTOME LIVE流菜单的进程，否则他不会收到这个回调事件。有关详细信息，请参见IMeetingUIElemConfiguration::RedirectClickCustomLiveStreamMenuEvent();
	virtual void onCCBTNClicked() = 0;

	/// \描述：用于在会议中单击音频按钮的回调事件。
	/// \注意：除非用户设置重定向在会议中单击音频按钮的过程，否则不会接收此回调事件。详细请看: IMeetingUIElemConfiguration::RedirectClickAudioBTNEvent().
	virtual void onAudioBtnClicked(AudioBtnClickedCallbackInfo info) = 0;
	
	/// \描述：用于在会议中单击音频菜单按钮的回调事件。
	/// \注意：除非用户设置重定向在会议中单击音频菜单按钮的过程，否则不会接收此回调事件。详细请看: IMeetingUIElemConfiguration::RedirectClickAudioMenuBTNEvent().
	virtual void onAudioMenuBtnClicked() = 0;

	/// \描述：会议中单击“会议室”按钮的回调事件。
	/// \注意：除非用户设置重定向在会议中单击会议室按钮的过程，否则不会接收此回调事件。详细请看: IMeetingUIElemConfiguration::RedirectClickBreakoutRoomButtonEvent().
	virtual void onBreakoutRoomBtnClicked() = 0;
	
};

/// \描述：会议UI控制器接口
///
class IMeetingUIController
{
public:
	/// \描述：设置会议ui控制器回调事件
	/// \参数：pEvent 一个指向IMeetingUIControllerEvent*的指针，它接收会议ui事件。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IMeetingUIControllerEvent* pEvent) = 0;

	/// \描述：显示会议聊天对话框
	/// \参数：param 指定如何显示聊天对话框。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError ShowChatDlg(ShowChatDlgParam& param) = 0;

	/// \描述：隐藏会议聊天对话框
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError HideChatDlg() = 0;

	/// \描述：进入全屏模式
	/// \参数：firstView 指定第一个屏幕是否进入全屏模式
	/// \参数：secondView 如果启用双显示器模式，指定第二个显示器是否进入全屏模式。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError EnterFullScreen(bool firstView, bool secondView) = 0;

	/// \描述：退出全屏模式
	/// \参数: firstView 指定第一个显示器是否退出全屏模式。
	/// \参数：secondView 如果启用双监视器模式，指定第二个监视器是否退出全屏模式。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError ExitFullScreen(bool firstView, bool secondView) = 0;

	/// \描述：返回到会议中
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError BackToMeeting() = 0;

	/// \描述： Switch to video wall mode. 
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SwitchToVideoWall() = 0;

	/// \描述：切换到主动式扬声器视图
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SwtichToAcitveSpeaker() = 0;

	/// \描述：移动浮动视频窗口
	/// \参数：left 指定浮动视频窗口的左侧位置。
	/// \参数：top 指定浮动视频窗口的顶部位置。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError MoveFloatVideoWnd(int left, int top) = 0;

	/// \描述：显示共享浮动工具栏
	/// \参数：bShow 指定是否显示共享浮动工具栏
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError ShowSharingToolbar(bool bShow) = 0;

	/// \描述：将浮动视频条切换到主动式扬声器视图
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SwitchFloatVideoToActiveSpkMod() = 0;

	/// \描述：改变浮动主动式音箱视频条的大小
	/// \参数：type 指定浮动视频面板视图类型。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError ChangeFloatoActiveSpkVideoSize(SDKFloatVideoType type) = 0;

	/// \描述：将浮动视频栏切换到画廊视图
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SwitchFloatVideoToGalleryMod() = 0;

	/// \描述：显示参与者列表窗口
	/// \参数：bShow Specifies the participants List Window show or not
	/// \参数：hParticipantsListWnd if bShow is true,and api call success, will return the handle of the participants List window
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError ShowParticipantsListWnd(bool bShow, HWND& hParticipantsListWnd) = 0;

	/// \描述：显示底部浮动工具栏窗口
	/// \参数：bShow 指定底部浮动工具栏窗口显示与否
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError ShowBottomFloatToolbarWnd(bool bShow) = 0;

	/// \描述：获取会议UI窗口的句柄
	/// \参数：hFirstView 返回会议UI窗口的第一个视图句柄的变量。
	/// \参数：hSecondView 返回会议UI窗口的第二个视图句柄的变量。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError GetMeetingUIWnd(HWND& hFirstView, HWND& hSecondView) = 0;

	/// \描述：显示连接音频对话框
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError ShowJoinAudioDlg() = 0;

	/// \描述：隐藏连接音频对话框
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError HideJoinAudioDlg() = 0;

	/// \描述：获取网页信息的视频墙模式。
	/// \参数：videoWallPageInfoParam 存储当前页面索引和总页面。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError GetWallViewPageInfo(VideoWallPageInfoParam& videoWallPageInfoParam) = 0;

	/// \描述：显示前一页或下一页视频用户在视频墙模式。
	/// \参数：bPageUp 指定上一页或下一页。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError ShowPreOrNextPageVideo(bool bPageUp) = 0;

	/// \描述：显示或隐藏您共享的应用程序的共享框架窗口。
	/// \参数：bShow 指定显示或隐藏.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError ShowSharingFrameWindows(bool bShow) = 0;

	/// \描述：确定第一个屏幕上会议ui窗口的最小化状态。
	/// \参数：mode 如果第一个屏幕上的会议ui窗口处于最小化状态，则返回最小化模式。
	/// \返回：true 或 false
	virtual bool IsMinimizeModeOfFristScreenMeetingUIWnd(SDKMinimizeUIMode& mode) = 0;

	/// \描述：如果第一个屏幕上的会议ui窗口处于最小化状态，则更改最小化模式。
	/// \参数：mode 指定最小化模式。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SwitchMinimizeUIMode4FristScreenMeetingUIWnd(SDKMinimizeUIMode mode) = 0;

	/// \描述：获取当前分屏模式的信息
	/// \参数：info 当前分屏模式的信息。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError GetCurrentSplitScreenModeInfo(SplitScreenInfo& info) = 0;

	/// \描述：在查看共享和不启用双显示器模式时，请切换分屏模式或不切换分屏模式。
	/// \参数：bSplit 是否分屏模式。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SwitchSplitScreenMode(bool bSplit) = 0;

	/// \描述：当别人分享时，并且会议窗口不是全屏的。你可以调用api来切换视频和共享显示位置。
	/// \参数：bToDisplayShare TRUE means to display share, otherwise video.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SwapToShowShareViewOrVideo(bool bToDisplayShare) = 0;

	/// \描述：确定会议现在是否显示共享屏幕。
	/// \参数：[out] bIsShare TRUE 意思是显示共享屏幕，FALSE 意思是显示视频。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError IsDisplayingShareViewOrVideo(bool& bIsShare) = 0;

	/// \描述：确定用户现在是否可以切换到共享屏幕或视频。
	/// \参数：[out] bCan TRUE 表示可以, 否则不行
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CanSwapToShowShareViewOrVideo(bool& bCan) = 0;
};

END_ZHUMU_SDK_NAMESPACE
#endif