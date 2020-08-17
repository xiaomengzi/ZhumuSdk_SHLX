/*!
* \文件 meeting_configuration_interface.h
* \描述 会议配置服务接口
* \仅适用于zhumu类型的用户界面模式
*/
#ifndef ZHUMU_MEETING_Configuration_INTERFACE_H_
#define ZHUMU_MEETING_Configuration_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include "..\customized_resource_helper_interface.h"
/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE

/*! \enum RequiredInfoType
\描述：参加会议的必要信息的类型。
下面是更详细的结构描述。
*/
enum RequiredInfoType
{
	REQUIRED_INFO_TYPE_NONE,///<初始化.
	REQUIRED_INFO_TYPE_Password, ///<用户在参加会议时需要输入密码。通过InputMeetingPasswordAndScreenName()来指定密码信息。
	REQUIRED_INFO_TYPE_Password4WrongPassword,///<如果密码无效，用户需要重新输入。通过InputMeetingPasswordAndScreenName()来指定密码信息。
	REQUIRED_INFO_TYPE_PasswordAndScreenName,///<用户需要通过InputMeetingPasswordAndScreenName()输入屏幕名和密码来指定必要的信息。
	REQUIRED_INFO_TYPE_ScreenName,///<用户需要输入屏幕名。通过InputMeetingPasswordAndScreenName()来指定屏幕名信息。
};

class IMeetingPasswordAndScreenNameHandler
{
public:

	/// \描述：获取完成的请求信息的类型
	/// \返回：如果函数成功，则返回值是RequiredInfoType enum中的值。
	virtual RequiredInfoType GetRequiredInfoType() = 0;

	/// \描述：输入会议密码和屏幕名，然后释放该对象
	virtual bool InputMeetingPasswordAndScreenName(const wchar_t* meetingPassword, const wchar_t* screenName) = 0;

	/// \描述：输入会议屏幕名，然后释放该对象
	virtual bool InputMeetingScreenName(const wchar_t* screenName) = 0;

	/// \描述：取消输入会议密码和屏幕名称，然后释放此对象
	virtual void Cancel() = 0;
	virtual ~IMeetingPasswordAndScreenNameHandler() {};
};

/// \描述：注册网络研讨会的处理程序
///
class IWebinarNeedRegisterHandler
{
public:
	enum WebinarNeedRegisterType
	{
		WebinarReg_NONE,
		WebinarReg_By_Register_Url, //dynamic_cast to IWebinarNeedRegisterHandlerByUrl
		WebinarReg_By_Email_and_DisplayName,//dynamic_cast to IWebinarNeedRegisterHandlerByEmail
	};

	virtual WebinarNeedRegisterType GetWebinarNeedRegisterType() = 0;
	virtual ~IWebinarNeedRegisterHandler() {};
};

/// \描述：使用url注册网络研讨会的处理程序
///
class IWebinarNeedRegisterHandlerByUrl : public IWebinarNeedRegisterHandler
{
public:
	/// \描述：获取网络研讨会注册URL
	virtual const wchar_t* GetWebinarRegisterUrl() = 0;

	/// \描述：释放对象
	virtual void Release() = 0;
	virtual ~IWebinarNeedRegisterHandlerByUrl() {};
};

/// \描述：使用电子邮件和屏幕名称注册网络研讨会的处理程序
///
class IWebinarNeedRegisterHandlerByEmail : public IWebinarNeedRegisterHandler
{
public:
	/// \描述：输入注册邮箱和网名，并释放该对象
	virtual SDKError InputWebinarRegisterEmailAndScreenName(const wchar_t* email, const wchar_t* screenName) = 0;

	/// \描述：取消输入的邮箱和屏幕名称，并释放此对象
	virtual void Cancel() = 0;
	virtual ~IWebinarNeedRegisterHandlerByEmail() {};
};

/// \描述：结束其他会议，加入新的会议的处理程序
///
class IEndOtherMeetingToJoinMeetingHandler
{
public:
	virtual bool EndOtherMeeting() = 0;
	virtual void Cancel() = 0;
	virtual ~IEndOtherMeetingToJoinMeetingHandler() {};
};


/// \描述：免费会议结束提醒的处理程序
///
class IFreeMeetingEndingReminderHandler
{
public:
	enum FreeMeetingEndingReminderType
	{
		FreeMeetingEndingReminder_NONE,
		FreeMeetingEndingReminder_Can_UpgradeMeeting_ToPro_Once,
		FreeMeetingEndingReminder_Can_UpgradeAccount,
		FreeMeetingEndingReminder_Reminder,
		FreeMeetingEndingReminder_UpgradeMeeting_ToPro_Failed,
		FreeMeetingEndingReminder_UpgradeMeeting_ToPro_Success,
	};

	/// \描述：获取提醒类型
	virtual FreeMeetingEndingReminderType GetType() = 0;

	/// \描述：升级会议并释放这个对象，只针对freemeetingendingder_can_upgrademeeting_topro_once
	virtual SDKError UpgradeMeeting() = 0;

	/// \描述：升级帐户并释放此对象，仅针对freemeetingendingder_can_upgradeaccount
	virtual SDKError UpgradeAccount() = 0;

	/// \描述：取消并释放此对象
	virtual SDKError Cancel() = 0;
	virtual ~IFreeMeetingEndingReminderHandler() {};
};

enum SDKInviteDlgTabPage
{
	SDK_INVITEDLG_TAB_EMAILCONTACT = 0, ///<“通过电子邮件邀请”标签页
	SDK_INVITEDLG_TAB_PHONECONTACT, ///<“通过电话邀请”标签页
	SDK_INVITEDLG_TAB_ROOMSYSTEM, ///<“邀请一个会议室系统”标签页
};

enum SDKH323TabPage
{
	SDK_INVITEDLG_H323_DIALIN = 0, ///<“拨入”会议室系统标签页的子标签页
	SDK_INVITEDLG_H323_CALLOUT, ///<“拨出”会议室系统标签页的子标签页
};
/// \描述：免费会议事件处理程序。
///
class IMeetingConfigurationFreeMeetingEvent
{

public:
	/*! \enum FreeMeetingNeedUpgradeType
	\描述：免费会议的升级类型。
	下面是更详细的结构描述。
	*/
	enum FreeMeetingNeedUpgradeType
	{
		FreeMeetingNeedUpgradeType_NONE,///<初始化.
		FreeMeetingNeedUpgradeType_BY_ADMIN,///<管理员升级免费会议。
		FreeMeetingNeedUpgradeType_BY_GIFTURL,///<通过连接升级免费会议。
	};
	/// \描述：SDK会在免费会议期间触发这个回调事件，通知用户还有多少时间可以免费会议。
	/// \参数: leftTime 会议剩余时间（秒为单位）
	virtual void onFreeMeetingRemainTime(unsigned int leftTime) = 0;
	/// \描述：免费会议的倒计时停止的回调。
	virtual void onFreeMeetingRemainTimeStopCountDown() = 0;

	/// \弃用：后端设计更改，该函数将被删除。
	virtual void onFreeMeetingEndingReminderNotification(IFreeMeetingEndingReminderHandler* handler_) = 0;

	/// \描述：升级免费会议的回调。
	/// \参数: type_ 免费会议的升级类型，详见 freemeetingneepgradetype enum。
	/// \参数: gift_url 通过链接升级免费会议。当且仅当type_的值为FreeMeetingNeedUpgradeType_BY_GIFTURL时，该参数才有意义。
	virtual void onFreeMeetingNeedToUpgrade(FreeMeetingNeedUpgradeType type_, const wchar_t* gift_url) = 0;

	/// \描述：通过链接升级免费会议开始的回调方法。
	virtual void onFreeMeetingUpgradeToGiftFreeTrialStart() = 0;

	/// \描述：通过链接升级免费会议结束的回调方法。
	virtual void onFreeMeetingUpgradeToGiftFreeTrialStop() = 0;

	/// \描述：免费会议成功升级的回调函数。
	virtual void onFreeMeetingUpgradeToProMeeting() = 0;
};
/// \描述：会议配置回调事件。
///

class IMeetingConfigurationEvent : public IMeetingConfigurationFreeMeetingEvent
{
public:
	/// \描述：如果需要密码或屏幕名，SDK将触发回调事件。
	/// \参数：pHandler 一个指向实例的指针，用户可以使用该对象进行操作。有关详细信息，请参见IMeetingPasswordAndScreenNameHandler。
	virtual void onInputMeetingPasswordAndScreenNameNotification(IMeetingPasswordAndScreenNameHandler* pHandler) = 0;

	/// \描述：会议需要密码或屏幕名称的回调事件
	/// \参数：bShow 指定显示或隐藏您自己的指令显示窗口。
	/// \参数：airhostName 显示在ios设备上的云主机名称
	virtual void onAirPlayInstructionWndNotification(bool bShow, const wchar_t* airhostName) = 0;

	/// \描述：网络研讨会需要注册回调
	/// \参数：handler_ 当接收到此消息时将被调用的处理程序。
	virtual void onWebinarNeedRegisterNotification(IWebinarNeedRegisterHandler* handler_) = 0;

	/// \描述：会议需要结束其他会议才能加入本次会议的回调
	/// \参数：handler_ 当接收到此消息时将被调用的处理程序。
	virtual void onEndOtherMeetingToJoinMeetingNotification(IEndOtherMeetingToJoinMeetingHandler* handler_) = 0;
};

typedef struct tagRedirectWarningMsgOption
{
	bool bRedirectBadNetwork;
	bool bRedirectWarnHighCPU;
	tagRedirectWarningMsgOption()
	{
		bRedirectBadNetwork = false;
		bRedirectWarnHighCPU = false;
	}

}RedirectWarningMsgOption;

/// \描述： 会议用户配置界面。
///
class IMeetingUIElemConfiguration
{
public:
	/// \描述：设置会议UI位置
	/// \参数：pos 指定UI显示会议的位置。
	virtual void SetMeetingUIPos(WndPosition pos) = 0;

	/// \描述：设置浮动视频面板的位置
	/// \参数：pos 指定浮动视频面板显示的位置。
	virtual void SetFloatVideoPos(WndPosition pos) = 0;

	/// \描述：设置共享工具栏可见性标志
	/// \参数：bShow 指定共享期间显示或不显示浮动工具栏。
	virtual void SetSharingToolbarVisibility(bool bShow) = 0;

	/// \描述：设置底部浮动工具栏可见性标志
	/// \参数：bShow 指定共享期间显示或不显示底部浮动工具栏。
	virtual void SetBottomFloatToolbarWndVisibility(bool bShow) = 0;

	/// \描述：会议UI中隐藏会议信息
	/// \参数：bHide 指定是否隐藏会议UI的会议信息。
	virtual void HideMeetingInfoFromMeetingUITitle(bool bHide) = 0;

	/// \描述：将会议ID设置为在会议ui标题中显示
	/// \参数：meetingNumber 指定要在会议ui标题中显示的会议ID。
	virtual void SetMeetingIDForMeetingUITitle(UINT64 meetingNumber) = 0;

	/// \描述：当您收到他人的远程控制请求时，启用“批准远程控制”对话框。
	/// \参数：bEnable 指定当您收到他人的远程控制请求时，将显示“批准远程控制”对话框，默认为“启用”，
	/// 如果您禁用此功能，请处理onRemoteControlStatus回调事件。
	virtual void EnableApproveRemoteControlDlg(bool bEnable) = 0;

	/// \描述：启用拒绝远程控制响应对话框
	/// \参数：bEnable 指定退订远程控制响应对话框，当你收到别人的退订消息时显示，默认为启用，
	/// 如果您禁用此功能，请处理onRemoteControlStatus回调事件。
	virtual void EnableDeclineRemoteControlResponseDlg(bool bEnable) = 0;

	/// \描述：启用“离开会议”窗口中的“离开会议”按钮
	/// \参数：bEnable 指定离开会议按钮显示或不显示在主机离开会议窗口，默认是启用，
	virtual void EnableLeaveMeetingOptionForHost(bool bEnable) = 0;

	/// \描述：启用会议窗口中的邀请按钮
	/// \参数：bEnable 指定在会议窗口中显示或不显示邀请按钮，默认为禁用，
	/// 如果启用此功能，则需要处理onInviteBtnClicked事件回调
	virtual void EnableInviteButtonOnMeetingUI(bool bEnable) = 0;

	/// \描述：在会议中设置工具栏中的视频按钮的可见性。默认值:真的。
	/// \参数：bEnable TRUE 表示显示按钮. 否则不显示.
	virtual void EnableVideoButtonOnMeetingUI(bool bEnable) = 0;
	
	/// \brief Set the visibility of the Audio button in the toolbar during the meeting. Default value: TRUE.
	/// \param bEnable TRUE indicates to display the button. Otherwise not.
	virtual void EnableAudioButtonOnMeetingUI(bool bEnable) = 0;

	/// \描述：设置在会议窗口中进入或退出全屏按钮的可见性，默认值:真的。
	/// \参数：bEnable TRUE 表示显示按钮. 否则不显示.
	virtual void EnableEnterAndExitFullScreenButtonOnMeetingUI(bool bEnable) = 0;

	/// \描述：启用左键双击进入和退出全屏功能。 
	/// \参数：bEnable 指定启用或禁用通过左键双击开关全屏模式，默认是启用。
	virtual void EnableLButtonDBClick4SwitchFullScreenMode(bool bEnable) = 0;

	/// \描述：设置浮动视频窗口的可见性标志
	/// \参数: bShow 指定在共享期间显示或不显示浮动视频窗口。
	virtual void SetFloatVideoWndVisibility(bool bShow) = 0;

	/// \描述：将启动共享btn的点击事件重定向到IMeetingUIControllerEvent
	/// \参数：bRedirect 重定向或否。如果为true，则在IMeetingUIControllerEvent中接收回调事件 onStartShareBtnClicked
	virtual void RedirectClickShareBTNEvent(bool bRedirect) = 0;

	/// \描述：将结束会议btn的点击事件重定向到IMeetingUIControllerEvent
	/// \参数：bRedirect 重定向或否。如果为true，则在IMeetingUIControllerEvent中接收回调事件 onEndMeetingBtnClicked
	virtual void RedirectClickEndMeetingBTNEvent(bool bRedirect) = 0;

	/// \描述：重定向免费会议即将结束消息到IMeetingConfigurationEvent
	/// \参数：bRedirect 重定向或否。如果为true，则在IMeetingConfigurationEvent 中接收回调事件 onFreeMeetingEndingReminderNotification
	virtual void RedirectFreeMeetingEndingReminderDlg(bool bRedirect) = 0;

	/// \描述：重定向自定义直播菜单的单击事件到IMeetingUIControllerEvent
	/// \参数：bRedirect 重定向或否。如果为true，则在IMeetingUIControllerEvent中接收回调事件 onCustomLiveStreamMenuClicked
	virtual void RedirectClickCustomLiveStreamMenuEvent(bool bRedirect) = 0;

	/// \描述：重定向参与者列表btn的点击事件到IMeetingUIControllerEvent
	/// \参数：bRedirect 重定向或否。如果为true，则在IMeetingUIControllerEvent 中接收回调事件 onParticipantListBtnClicked
	virtual void RedirectClickParticipantListBTNEvent(bool bRedirect) = 0;

	/// \描述：设置是否可以用SDK用户自己的程序处理在会议中点击闭合字幕按钮的事件。默认值:FALSE。
	/// \参数：bRedirect TRUE:表示使用用户自己的程序处理事件。FLASE:不使用。
	/// \注意：如果用户调用该函数进行转换，SDK将触发IMeetingUIControllerEvent::onCCBTNClicked()，后续逻辑由用户自己处理。
	virtual void RedirectClickCCBTNEvent(bool bRedirect) = 0;

	/// \描述：设置能否用SDK用户自己的程序处理在会议中的警告消息。默认值:没有。
	/// \参数：redirectOption 该参数指示要用用户自己的程序处理的警告消息。
	/// \注意：如果用户调用此函数进行转换，则SDK将触发IMeetingServiceEvent::onMeetingStatisticsWarningNotification()，随后的逻辑由用户自己处理。
	virtual void RedirectMeetingWarningMsg(RedirectWarningMsgOption redirectOption) = 0;

	/// \描述：设置是否可以在会议工具栏中暂时显示按钮的工具提示，用户可以通过点击“x”关闭按钮。默认值:真的。
	/// \参数：bEnable TRUE表示允许在会议中显示工具提示。FALSE表示不允许。
	virtual void EnableToolTipsShow(bool bEnable) = 0;

	/// \描述：配置隐藏或显示IOS设备共享的指令窗口。
	/// \参数：bEnable 指定隐藏或显示IOS设备共享的指令窗口，默认为启用。
	/// 如果禁用此选项，您需要处理onAirPlayInstructionWndNotification事件回调来显示或隐藏您自己的窗口。
	virtual void EnableAirplayInstructionWindow(bool bEnable) = 0;

	/// \描述： enable claim host feature.
	/// \param bEnable specify claim host feature enable or not, default is enable.
	virtual void EnableClaimHostFeature(bool bEnable) = 0;

	/// \描述：启用自动隐藏连接音频对话框
	/// \参数：bEnable 指定此功能启用与否，默认为禁用
	virtual void EnableAutoHideJoinAudioDialog(bool bEnable) = 0;

	/// \描述：应用程序图标总是显示在任务栏列表上
	/// \参数：bAlwaysShow 指定总是显示或不显示，默认是不显示
	virtual void AlwaysShowIconOnTaskBar(bool bAlwaysShow) = 0;

	/// \描述：禁用分屏模式的UI元素。
	/// \参数: bDisable 指定此功能禁用与否，默认为启用。
	virtual void DisableSplitScreenModeUIElements(bool bDisable) = 0;

	/// \描述：显示“共享计算机声音”复选框
	/// \参数：bShow 指定是否显示复选框，默认为true。
	virtual void SetShowAudioUseComputerSoundChkbox(bool bShow) = 0;

	/// \描述：显示“全屏视频优化”复选框
	/// \参数：bShow 指定是否显示复选框，默认为true。
	virtual void SetShowVideoOptimizeChkbox(bool bShow) = 0;

	/// \描述：显示“Phone Call”选项卡
	/// \参数：bShow 指定在值为false时隐藏选项卡，默认值为true。
	virtual void SetShowCallInTab(bool bShow) = 0;

	/// \描述：显示 'Call Me' 选项库
	/// \参数: bShow 指定在值为false时隐藏选项卡，默认值为true。
	virtual void SetShowCallMeTab(bool bShow) = 0;

	/// \描述：始终在主视频窗口的标题栏上显示会议ID信息
	/// \参数：bAlwaysShow 指定是否始终在窗口的标题栏上显示会议id信息。如果bAlwaysShow为false，则行为将遵循Zhumu的默认逻辑。默认是false。
	virtual void SetAlwaysShowMeetingIDOnTitle(bool bAlwaysShow) = 0;

	///	\弃用：这个函数将被弃用，请使用ICustomizedResourceHelper.AddCustomizedStringResouce()代替。
	/// \描述：使用自定义字符串替换指定的菜单项。
	/// \参数: customizedType 指定菜单项类型。有关更多信息，请参见 SDKCustomizedStringType enum。
	/// \参数：customizedString 指定自定义字符串。可以将其设置为NULL以删除指定项的自定义字符串。
	/// \返回: 如果函数成功，则返回值为SDKErr_Success。
	/// 否则失败。要获取扩展的错误信息，请参见 SDKError enum。
	/// \注意：如果customizedString不是长度为0(0)的NULL，则返回值为SDKERR_INVALID_PARAMETER。
	virtual SDKError SetUICustomizedString(SDKCustomizedStringType customizedType, const wchar_t* customizedString) = 0;

	/// \描述：是否删除设置对话框的最上面属性。默认不删除。
	/// \参数：bDisable TRUE 表示删除. FALSE 表示不删除.
	/// \返回: 如果函数成功，则返回值为SDKErr_Success。
	/// 否则失败。要获取扩展的错误信息，请参见 SDKError enum。
	virtual SDKError DisableTopMostAttr4SettingDialog(bool bDisable) = 0;

	/// \描述：设置是否在没有提示的情况下关闭当前共享内容并直接开始新的共享内容。默认值:FALSE(提示)。
	/// \参数：bEnable TRUE 表示提示. FALSE 不提示.
	/// \返回: 如果函数成功，则返回值为SDKErr_Success。
	/// 否则失败。要获取扩展的错误信息，请参见 SDKError enum。
	virtual SDKError EnableGrabShareWithoutReminder(bool bEnable) = 0;

	/// \描述：当多个参与者正在共享并且用户试图将设置更改为单个共享时，将切换的可见性设置为单个参与者共享对话框。默认值: TURE. 
	/// \参数：bEnable TRUE 指示在加入会议时显示对话框. FALSE 不显示.
	/// \注意：如果对话框被禁用显示，你将接收到IMeetingShareCtrlEvent::onMultiShareSwitchToSingleShareNeedConfirm回调事件。
	virtual void EnableShowShareSwitchMultiToSingleConfirmDlg(bool bEnable) = 0;

	/// \描述：设置会议中剩余会议时间按钮的可见性。默认值:FALSE。
	/// \参数：bDisable TRUE表示在空闲会议需要提醒时隐藏按钮。FALSE 不隐藏.
	/// \注意：如果该按钮被禁用显示，您将接收到IMeetingConfigurationEvent::onfreemeetingtime回调事件。
	virtual void DisableFreeMeetingRemainTimeNotify(bool bDisable) = 0;

	/// \描述：设置是否显示聊天按钮和菜单项。默认显示。
	/// \参数：bHide TRUE 表示隐藏, 否则显示.
	virtual void HideChatItemOnMeetingUI(bool bHide) = 0;

	/// \描述：设置是否显示录制按钮和菜单项。默认显示。
	/// \参数：bHide TRUE 表示隐藏, 否则显示.
	virtual void HideRecordItemOnMeetingUI(bool bHide) = 0;

	/// \描述：设置提示工具提示免费会议倒计时是否显示升级按钮。默认显示。
	/// \参数：bHide TRUE 表示隐藏, 否则显示.
	virtual void HideUpgradeFreeMeetingButton(bool bHide) = 0;

	/// \描述：在显示对话框时，在invite对话框中设置指定选项卡的可见性。默认值:全部显示。
	/// \参数：tabPage 指定一个标签，见SDKInviteDlgTabPage enum。
	/// \参数：bShow TRUE 指示要显示选项卡。FALSE 不显示.
	virtual void SetShowInviteDlgTabPage(SDKInviteDlgTabPage tabPage, bool bShow) = 0;

	/// \描述：在显示对话框时，在“邀请”对话框的“会议室系统”选项卡页中设置指定选项卡的可见性。默认值:全部显示
	/// \参数：tabPage 指定一个标签，见 SDKH323TabPage enum.
	/// \参数：bShow TRUE 指示要显示选项卡。FALSE 不显示.
	virtual void SetShowH323SubTabPage(SDKH323TabPage tabPage, bool bShow) = 0;

	/// \描述：当用户安排会议时，为免费用户设置升级警告消息的可见性。默认值:FALSE。
	/// \参数：bHide TRUE 指示隐藏警告消息。FALSE 显示.
	virtual void HideUpgradeWarningMsgForFreeUserWhenSchedule(bool bHide) = 0;

	/// \描述：设置本地记录转换进度条对话框的可见性。默认值:TRUE。
	/// \参数：bShow TRUE 指示显示对话框 FALSE 不显示.
	virtual void EnableLocalRecordingConvertProgressBarDialog(bool bShow) = 0;

	/// \描述：设置第二个相机共享窗口的相机切换按钮的可见性，默认为TRUE。
	/// \参数：bHide TRUE 表示隐藏摄像机切换按钮。FALSE 显示.
	virtual void HideSwitchCameraButton(bool bHide) = 0;

	// \brief Set the visibility of CopyURL button on invite window, Default: TRUE. 
	/// \param bHide TRUE indicates to hide, FALSE not.
	virtual void HideCopyUrlOnInviteWindow(bool bHide) = 0;

	// \brief Set the visibility of CopyInvitation button on invite window, Default: TRUE. 
	/// \param bHide TRUE indicates to hide, FALSE not.
	virtual void HideCopyInvitationOnInviteWindow(bool bHide) = 0;

	// \brief Set the visibility of Keypad button on meeting window, Default: TRUE. 
	/// \param bHide TRUE indicates to hide, FALSE not.
	virtual void HideKeypadButtonOnMeetingWindow(bool bHide) = 0;

	/// \brief Set whether to display the button REMOTE CONTROL and menu item. Default is displaying.
	/// \param [in] bHide TRUE means hiding, otherwise not.
	/// \remarks If the calling of API with parameter TRUE is successful, SDK will call EnableApproveRemoteControlDlg(false) by default.
	virtual void HideRemoteControlOnMeetingUI(bool bHide) = 0;
	
	/// \brief Set the visibility of Q&A on meeting UI. Default is displaying.
	/// \param [in] bHide TRUE means hiding, otherwise not.
	virtual void HideQAOnMeetingUI(bool bHide) = 0;

	/// \brief Set the visibility of poll on meeting UI. Default is displaying.
	/// \param [in] bHide TRUE means hiding, otherwise not.
	virtual void HidePollOnMeetingUI(bool bHide) = 0;

	/// \brief Set the ability to control the audio device in the meeting. Default is having the ability.
	/// \param [in] bDisable TRUE means having no ability, otherwise not.
	/// \This API is not recommended to call because once the bDsialbe is true, Zoom meeting may lose the control of the audio devices.
	virtual void DisableAdvanceAudioDeivceCtrl(bool bDisable) = 0;

	/// \brief Set if it is able to handle the event with SDK user's own program by clicking Audio button in the meeting. Default value: FALSE.
	/// \param bRedirect TRUE indicates to handle with user's own program. FALSE not.
	/// \remarks If the user calls this function to convert, the SDK will trigger the IMeetingUIControllerEvent::onAudioBtnClicked(AudioBtnClickedCallbackInfo info), and the user shall deal with the subsequent logic himself.
	virtual void RedirectClickAudioBTNEvent(bool bRedirect) = 0;

	/// \brief Set if it is able to handle the event with SDK user's own program by clicking Audio Menu button in the meeting. Default value: FALSE.
	/// \param bRedirect TRUE indicates to handle with user's own program. FALSE not.
	/// \remarks If the user calls this function to convert, the SDK will trigger the IMeetingUIControllerEvent::onAudioMenuBtnClicked(), and the user shall deal with the subsequent logic himself.
	virtual void RedirectClickAudioMenuBTNEvent(bool bRedirect) = 0;

	/// \brief Set if it is able to handle the event with SDK user's own program by clicking Breakout Room button in the meeting. Default value: FALSE.
	/// \param bRedirect TRUE indicates to handle with user's own program. FALSE not.
	/// \remarks If the user calls this function to convert, the SDK will trigger the IMeetingUIControllerEvent::onBreakoutRoomBtnClicked(), and the user shall deal with the subsequent logic himself.
	virtual void RedirectClickBreakoutRoomButtonEvent(bool bRedirect) = 0;

	/// \brief Set the visibility of reaction on meeting UI. Default is displaying.
	/// \param [in] bHide TRUE means hiding, otherwise not.
	virtual void HideReactionsOnMeetingUI(bool bHide) = 0;

	/// \brief Set the visibility of meeting info button on meeting UI. Default is displaying.
	/// \param [in] bHide TRUE means hiding, otherwise not.
	virtual void HideMeetingInfoOnMeetingUI(bool bHide) = 0;
};

/// \描述：加入会议行为配置接口
///
class IJoinMeetingBehaviorConfiguration
{
public:
	/// \描述：禁用加入会议错误密码的错误提示框。
	/// \参数：bDisable 指定错误的密码错误对话框的显示与否，如果禁用，您将得到MEETING_FAIL_PASSWORD_ERR会议失败错误。
	virtual void DisablePopupMeetingWrongPSWDlg(bool bDisable) = 0;

	/// \描述：禁用等待主持人入会对话框
	/// \参数：bDisable 指定等待主机人对话框显示或不显示
	virtual void DisableWaitingForHostDialog(bool bDisable) = 0;

	/// \描述：当启动新会议时，是否能自动结束其他会议。
	/// \参数：bEnable 指定是否自动结束其他会议。
	virtual void EnableAutoEndOtherMeetingWhenStartMeeting(bool bEnable) = 0;

	/// \描述：配置隐藏或显示输入会议密码对话框
	/// \参数：bEnable 指定“隐藏或显示输入会议密码”对话框，默认为“启用”。.
	/// 如果禁用此选项，您需要处理onInputMeetingPasswordAndScreenNameNotification事件回调。
	virtual void EnableInputMeetingPasswordDlg(bool bEnable) = 0;

	/// \描述：配置隐藏或显示输入会议屏幕名称对话框
	/// \参数：bEnable 指定“隐藏或显示输入会议屏幕名称”对话框，默认为“启用”。
	/// 如果禁用此选项，您需要处理onInputMeetingPasswordAndScreenNameNotification事件回调
	virtual void EnableInputMeetingScreenNameDlg(bool bEnable) = 0;

	/// \描述：重定向网络研讨会注册逻辑到IMeetingConfigurationEvent
	/// \参数：bRedirect 重定向或不重定向。如果是，你将在IMeetingConfigurationEvent中重新发送webinarneedregisternotification
	/// \默认是禁用的。
	virtual void RedirectWebinarNeedRegister(bool bRedirect) = 0;

	/// \描述：预填充网络研讨会的注册信息
	/// \参数：email 指定默认的电子邮件。
	/// \参数：username 指定默认的用户名。
	virtual void PrePopulateWebinarRegistrationInfo(const wchar_t* email, const wchar_t* username) = 0;

	/// \描述：重定向end other到IMeetingConfigurationEvent
	/// \参数：bRedirect 重定向与否。如果是，你将会在IMeetingConfigurationEvent中加入一个endothermeetingjoinmeetingnotification
	/// \默认是禁用的.
	virtual void RedirectEndOtherMeeting(bool bRedirect) = 0;

	/// \描述：设置是否能够强制参与者加入会议时开始视频。
	/// \参数：bEnable TRUE 指定强制参加者开始视频。
	/// \注意：默认行为取决于会议的配置。
	virtual void EnableForceAutoStartMyVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \描述：设置是否能够强制参与者加入会议时关闭视频。
	/// \参数：bEnable TRUE 指示强制参与者关闭视频。
	/// \注意：默认行为取决于会议的配置。
	virtual void EnableForceAutoStopMyVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \描述：设置在加入会议时选择加入音频对话框的可见性。默认值:FALSE。
	/// \参数：bDisable TRUE 指示隐藏对话框。
	virtual void DisableAutoShowSelectJoinAudioDlgWhenJoinMeeting(bool bDisable) = 0;

	/// \brief Set the visibility of the dialog box of joining a meeting. Default: FALSE.
	/// \param bDisable TRUE indicates to hide the dialog box. FALSE not.
	virtual void DisableShowJoinMeetingWnd(bool bDisable) = 0;
};

/// \描述： Meeting Configuration Interface
///
class IMeetingConfiguration :
	public IMeetingUIElemConfiguration,
	public IJoinMeetingBehaviorConfiguration
{
public:
	/// \描述：设置会议配置通知的处理程序。
	/// \参数：pEvent 将在接收此消息类型被调用
	virtual void SetEvent(IMeetingConfigurationEvent* pEvent) = 0;

	/// \描述：重置会议配置
	virtual void Reset() = 0;

	/// \描述：设置直接共享的显示器的id。
	/// \参数：monitorID 指定要共享哪个显示器。使用EnumDisplayMonitors系统api来获取这个值
	/// 请参考MONITORINFOEX结构中的szDevice。
	virtual void SetDirectShareMonitorID(const wchar_t* monitorID) = 0;

	/// \描述：当加入会议时，是否能自动调整扬声器的音量。
	/// \参数：bEnable 指定自动调整扬声器音量启用与否，默认为启用。
	virtual void EnableAutoAdjustSpeakerVolumeWhenJoinAudio(bool bEnable) = 0;

	/// \描述：当加入会议时，是否能自动调整麦克风的音量。
	/// \参数：bEnable 指定自动调整麦克风音量启用与否，默认为启用。
	virtual void EnableAutoAdjustMicVolumeWhenJoinAudio(bool bEnable) = 0;

	/// \描述：配置DSCP。
	/// \参数：dscpAudio 音频的DSCP值。
	/// \参数：dscpVideo 视频的DSCP值。
	/// \参数：bReset 重置DSCP值。
	virtual void ConfigDSCP(int dscpAudio, int dscpVideo, bool bReset) = 0;

	/// \描述：远程控制时禁用复制和粘贴功能
	/// \参数：bDisable 指定此功能禁用与否，默认为启用。
	virtual void DisableRemoteCtrlCopyPasteFeature(bool bDisable) = 0;

	/// \描述：启用隐藏纯电话用户的完整电话号码
	/// \参数：bHide 指定此功能是否启用，默认情况下不隐藏。
	virtual void EnableHideFullPhoneNumber4PureCallinUser(bool bHide) = 0;

	/// \描述：Enable the length limitation of meeting number
	/// \参数：bEnable specify this feature enable or not, default is enable.
	virtual void EnableLengthLimitationOfMeetingNumber(bool bEnable) = 0;

	/// \描述：启用IOS设备共享
	/// \参数：bEnable 指定此功能启用与否，默认为启用。
	virtual void EnableShareIOSDevice(bool bEnable) = 0;

	/// \描述：启用白板共享
	/// \参数：bEnable 指定此功能启用与否，默认为启用。
	virtual void EnableShareWhiteBoard(bool bEnable) = 0;

	/// \描述：强制禁用多人共享
	/// \参数：bDisable 指定此功能禁用与否，默认为启用。
	virtual void ForceDisableMultiShare(bool bDisable) = 0;

	/// \描述：当没有参会者时，设置会议的最大持续时间。默认值:24 * 60。
	/// \参数：nDuration 指定最大持续时间(以分钟为单位)。
	virtual void SetMaxDurationForOnlyHostInMeeting(int nDuration) = 0;

	/// \brief Set if it is able to leave the meeting when the screen is locked or the screen saver is shown. Default: TRUE.
	/// \param bEnable TRUE indicates to enable to share on the white board. FALSE not.
	/// \remarks No matter what value you set for API, the callback IMeetingServiceEvent::onOSSessionChangedNotification will be triggered.
	virtual void EnableLeaveMeetingWhenScreenLocked(bool bEnable) = 0;
};

END_ZHUMU_SDK_NAMESPACE
#endif