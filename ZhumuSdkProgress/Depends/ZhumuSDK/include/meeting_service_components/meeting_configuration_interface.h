/*!
* \�ļ� meeting_configuration_interface.h
* \���� �������÷���ӿ�
* \��������zhumu���͵��û�����ģʽ
*/
#ifndef ZHUMU_MEETING_Configuration_INTERFACE_H_
#define ZHUMU_MEETING_Configuration_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include "..\customized_resource_helper_interface.h"
/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE

/*! \enum RequiredInfoType
\�������μӻ���ı�Ҫ��Ϣ�����͡�
�����Ǹ���ϸ�Ľṹ������
*/
enum RequiredInfoType
{
	REQUIRED_INFO_TYPE_NONE,///<��ʼ��.
	REQUIRED_INFO_TYPE_Password, ///<�û��ڲμӻ���ʱ��Ҫ�������롣ͨ��InputMeetingPasswordAndScreenName()��ָ��������Ϣ��
	REQUIRED_INFO_TYPE_Password4WrongPassword,///<���������Ч���û���Ҫ�������롣ͨ��InputMeetingPasswordAndScreenName()��ָ��������Ϣ��
	REQUIRED_INFO_TYPE_PasswordAndScreenName,///<�û���Ҫͨ��InputMeetingPasswordAndScreenName()������Ļ����������ָ����Ҫ����Ϣ��
	REQUIRED_INFO_TYPE_ScreenName,///<�û���Ҫ������Ļ����ͨ��InputMeetingPasswordAndScreenName()��ָ����Ļ����Ϣ��
};

class IMeetingPasswordAndScreenNameHandler
{
public:

	/// \��������ȡ��ɵ�������Ϣ������
	/// \���أ���������ɹ����򷵻�ֵ��RequiredInfoType enum�е�ֵ��
	virtual RequiredInfoType GetRequiredInfoType() = 0;

	/// \��������������������Ļ����Ȼ���ͷŸö���
	virtual bool InputMeetingPasswordAndScreenName(const wchar_t* meetingPassword, const wchar_t* screenName) = 0;

	/// \���������������Ļ����Ȼ���ͷŸö���
	virtual bool InputMeetingScreenName(const wchar_t* screenName) = 0;

	/// \������ȡ����������������Ļ���ƣ�Ȼ���ͷŴ˶���
	virtual void Cancel() = 0;
	virtual ~IMeetingPasswordAndScreenNameHandler() {};
};

/// \������ע���������ֻ�Ĵ������
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

/// \������ʹ��urlע���������ֻ�Ĵ������
///
class IWebinarNeedRegisterHandlerByUrl : public IWebinarNeedRegisterHandler
{
public:
	/// \��������ȡ�������ֻ�ע��URL
	virtual const wchar_t* GetWebinarRegisterUrl() = 0;

	/// \�������ͷŶ���
	virtual void Release() = 0;
	virtual ~IWebinarNeedRegisterHandlerByUrl() {};
};

/// \������ʹ�õ����ʼ�����Ļ����ע���������ֻ�Ĵ������
///
class IWebinarNeedRegisterHandlerByEmail : public IWebinarNeedRegisterHandler
{
public:
	/// \����������ע����������������ͷŸö���
	virtual SDKError InputWebinarRegisterEmailAndScreenName(const wchar_t* email, const wchar_t* screenName) = 0;

	/// \������ȡ��������������Ļ���ƣ����ͷŴ˶���
	virtual void Cancel() = 0;
	virtual ~IWebinarNeedRegisterHandlerByEmail() {};
};

/// \�����������������飬�����µĻ���Ĵ������
///
class IEndOtherMeetingToJoinMeetingHandler
{
public:
	virtual bool EndOtherMeeting() = 0;
	virtual void Cancel() = 0;
	virtual ~IEndOtherMeetingToJoinMeetingHandler() {};
};


/// \��������ѻ���������ѵĴ������
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

	/// \��������ȡ��������
	virtual FreeMeetingEndingReminderType GetType() = 0;

	/// \�������������鲢�ͷ��������ֻ���freemeetingendingder_can_upgrademeeting_topro_once
	virtual SDKError UpgradeMeeting() = 0;

	/// \�����������ʻ����ͷŴ˶��󣬽����freemeetingendingder_can_upgradeaccount
	virtual SDKError UpgradeAccount() = 0;

	/// \������ȡ�����ͷŴ˶���
	virtual SDKError Cancel() = 0;
	virtual ~IFreeMeetingEndingReminderHandler() {};
};

enum SDKInviteDlgTabPage
{
	SDK_INVITEDLG_TAB_EMAILCONTACT = 0, ///<��ͨ�������ʼ����롱��ǩҳ
	SDK_INVITEDLG_TAB_PHONECONTACT, ///<��ͨ���绰���롱��ǩҳ
	SDK_INVITEDLG_TAB_ROOMSYSTEM, ///<������һ��������ϵͳ����ǩҳ
};

enum SDKH323TabPage
{
	SDK_INVITEDLG_H323_DIALIN = 0, ///<�����롱������ϵͳ��ǩҳ���ӱ�ǩҳ
	SDK_INVITEDLG_H323_CALLOUT, ///<��������������ϵͳ��ǩҳ���ӱ�ǩҳ
};
/// \��������ѻ����¼��������
///
class IMeetingConfigurationFreeMeetingEvent
{

public:
	/*! \enum FreeMeetingNeedUpgradeType
	\��������ѻ�����������͡�
	�����Ǹ���ϸ�Ľṹ������
	*/
	enum FreeMeetingNeedUpgradeType
	{
		FreeMeetingNeedUpgradeType_NONE,///<��ʼ��.
		FreeMeetingNeedUpgradeType_BY_ADMIN,///<����Ա������ѻ��顣
		FreeMeetingNeedUpgradeType_BY_GIFTURL,///<ͨ������������ѻ��顣
	};
	/// \������SDK������ѻ����ڼ䴥������ص��¼���֪ͨ�û����ж���ʱ�������ѻ��顣
	/// \����: leftTime ����ʣ��ʱ�䣨��Ϊ��λ��
	virtual void onFreeMeetingRemainTime(unsigned int leftTime) = 0;
	/// \��������ѻ���ĵ���ʱֹͣ�Ļص���
	virtual void onFreeMeetingRemainTimeStopCountDown() = 0;

	/// \���ã������Ƹ��ģ��ú�������ɾ����
	virtual void onFreeMeetingEndingReminderNotification(IFreeMeetingEndingReminderHandler* handler_) = 0;

	/// \������������ѻ���Ļص���
	/// \����: type_ ��ѻ�����������ͣ���� freemeetingneepgradetype enum��
	/// \����: gift_url ͨ������������ѻ��顣���ҽ���type_��ֵΪFreeMeetingNeedUpgradeType_BY_GIFTURLʱ���ò����������塣
	virtual void onFreeMeetingNeedToUpgrade(FreeMeetingNeedUpgradeType type_, const wchar_t* gift_url) = 0;

	/// \������ͨ������������ѻ��鿪ʼ�Ļص�������
	virtual void onFreeMeetingUpgradeToGiftFreeTrialStart() = 0;

	/// \������ͨ������������ѻ�������Ļص�������
	virtual void onFreeMeetingUpgradeToGiftFreeTrialStop() = 0;

	/// \��������ѻ���ɹ������Ļص�������
	virtual void onFreeMeetingUpgradeToProMeeting() = 0;
};
/// \�������������ûص��¼���
///

class IMeetingConfigurationEvent : public IMeetingConfigurationFreeMeetingEvent
{
public:
	/// \�����������Ҫ�������Ļ����SDK�������ص��¼���
	/// \������pHandler һ��ָ��ʵ����ָ�룬�û�����ʹ�øö�����в������й���ϸ��Ϣ����μ�IMeetingPasswordAndScreenNameHandler��
	virtual void onInputMeetingPasswordAndScreenNameNotification(IMeetingPasswordAndScreenNameHandler* pHandler) = 0;

	/// \������������Ҫ�������Ļ���ƵĻص��¼�
	/// \������bShow ָ����ʾ���������Լ���ָ����ʾ���ڡ�
	/// \������airhostName ��ʾ��ios�豸�ϵ�����������
	virtual void onAirPlayInstructionWndNotification(bool bShow, const wchar_t* airhostName) = 0;

	/// \�������������ֻ���Ҫע��ص�
	/// \������handler_ �����յ�����Ϣʱ�������õĴ������
	virtual void onWebinarNeedRegisterNotification(IWebinarNeedRegisterHandler* handler_) = 0;

	/// \������������Ҫ��������������ܼ��뱾�λ���Ļص�
	/// \������handler_ �����յ�����Ϣʱ�������õĴ������
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

/// \������ �����û����ý��档
///
class IMeetingUIElemConfiguration
{
public:
	/// \���������û���UIλ��
	/// \������pos ָ��UI��ʾ�����λ�á�
	virtual void SetMeetingUIPos(WndPosition pos) = 0;

	/// \���������ø�����Ƶ����λ��
	/// \������pos ָ��������Ƶ�����ʾ��λ�á�
	virtual void SetFloatVideoPos(WndPosition pos) = 0;

	/// \���������ù��������ɼ��Ա�־
	/// \������bShow ָ�������ڼ���ʾ����ʾ������������
	virtual void SetSharingToolbarVisibility(bool bShow) = 0;

	/// \���������õײ������������ɼ��Ա�־
	/// \������bShow ָ�������ڼ���ʾ����ʾ�ײ�������������
	virtual void SetBottomFloatToolbarWndVisibility(bool bShow) = 0;

	/// \����������UI�����ػ�����Ϣ
	/// \������bHide ָ���Ƿ����ػ���UI�Ļ�����Ϣ��
	virtual void HideMeetingInfoFromMeetingUITitle(bool bHide) = 0;

	/// \������������ID����Ϊ�ڻ���ui��������ʾ
	/// \������meetingNumber ָ��Ҫ�ڻ���ui��������ʾ�Ļ���ID��
	virtual void SetMeetingIDForMeetingUITitle(UINT64 meetingNumber) = 0;

	/// \�����������յ����˵�Զ�̿�������ʱ�����á���׼Զ�̿��ơ��Ի���
	/// \������bEnable ָ�������յ����˵�Զ�̿�������ʱ������ʾ����׼Զ�̿��ơ��Ի���Ĭ��Ϊ�����á���
	/// ��������ô˹��ܣ��봦��onRemoteControlStatus�ص��¼���
	virtual void EnableApproveRemoteControlDlg(bool bEnable) = 0;

	/// \���������þܾ�Զ�̿�����Ӧ�Ի���
	/// \������bEnable ָ���˶�Զ�̿�����Ӧ�Ի��򣬵����յ����˵��˶���Ϣʱ��ʾ��Ĭ��Ϊ���ã�
	/// ��������ô˹��ܣ��봦��onRemoteControlStatus�ص��¼���
	virtual void EnableDeclineRemoteControlResponseDlg(bool bEnable) = 0;

	/// \���������á��뿪���顱�����еġ��뿪���顱��ť
	/// \������bEnable ָ���뿪���鰴ť��ʾ����ʾ�������뿪���鴰�ڣ�Ĭ�������ã�
	virtual void EnableLeaveMeetingOptionForHost(bool bEnable) = 0;

	/// \���������û��鴰���е����밴ť
	/// \������bEnable ָ���ڻ��鴰������ʾ����ʾ���밴ť��Ĭ��Ϊ���ã�
	/// ������ô˹��ܣ�����Ҫ����onInviteBtnClicked�¼��ص�
	virtual void EnableInviteButtonOnMeetingUI(bool bEnable) = 0;

	/// \�������ڻ��������ù������е���Ƶ��ť�Ŀɼ��ԡ�Ĭ��ֵ:��ġ�
	/// \������bEnable TRUE ��ʾ��ʾ��ť. ������ʾ.
	virtual void EnableVideoButtonOnMeetingUI(bool bEnable) = 0;
	
	/// \brief Set the visibility of the Audio button in the toolbar during the meeting. Default value: TRUE.
	/// \param bEnable TRUE indicates to display the button. Otherwise not.
	virtual void EnableAudioButtonOnMeetingUI(bool bEnable) = 0;

	/// \�����������ڻ��鴰���н�����˳�ȫ����ť�Ŀɼ��ԣ�Ĭ��ֵ:��ġ�
	/// \������bEnable TRUE ��ʾ��ʾ��ť. ������ʾ.
	virtual void EnableEnterAndExitFullScreenButtonOnMeetingUI(bool bEnable) = 0;

	/// \�������������˫��������˳�ȫ�����ܡ� 
	/// \������bEnable ָ�����û����ͨ�����˫������ȫ��ģʽ��Ĭ�������á�
	virtual void EnableLButtonDBClick4SwitchFullScreenMode(bool bEnable) = 0;

	/// \���������ø�����Ƶ���ڵĿɼ��Ա�־
	/// \����: bShow ָ���ڹ����ڼ���ʾ����ʾ������Ƶ���ڡ�
	virtual void SetFloatVideoWndVisibility(bool bShow) = 0;

	/// \����������������btn�ĵ���¼��ض���IMeetingUIControllerEvent
	/// \������bRedirect �ض��������Ϊtrue������IMeetingUIControllerEvent�н��ջص��¼� onStartShareBtnClicked
	virtual void RedirectClickShareBTNEvent(bool bRedirect) = 0;

	/// \����������������btn�ĵ���¼��ض���IMeetingUIControllerEvent
	/// \������bRedirect �ض��������Ϊtrue������IMeetingUIControllerEvent�н��ջص��¼� onEndMeetingBtnClicked
	virtual void RedirectClickEndMeetingBTNEvent(bool bRedirect) = 0;

	/// \�������ض�����ѻ��鼴��������Ϣ��IMeetingConfigurationEvent
	/// \������bRedirect �ض��������Ϊtrue������IMeetingConfigurationEvent �н��ջص��¼� onFreeMeetingEndingReminderNotification
	virtual void RedirectFreeMeetingEndingReminderDlg(bool bRedirect) = 0;

	/// \�������ض����Զ���ֱ���˵��ĵ����¼���IMeetingUIControllerEvent
	/// \������bRedirect �ض��������Ϊtrue������IMeetingUIControllerEvent�н��ջص��¼� onCustomLiveStreamMenuClicked
	virtual void RedirectClickCustomLiveStreamMenuEvent(bool bRedirect) = 0;

	/// \�������ض���������б�btn�ĵ���¼���IMeetingUIControllerEvent
	/// \������bRedirect �ض��������Ϊtrue������IMeetingUIControllerEvent �н��ջص��¼� onParticipantListBtnClicked
	virtual void RedirectClickParticipantListBTNEvent(bool bRedirect) = 0;

	/// \�����������Ƿ������SDK�û��Լ��ĳ������ڻ����е���պ���Ļ��ť���¼���Ĭ��ֵ:FALSE��
	/// \������bRedirect TRUE:��ʾʹ���û��Լ��ĳ������¼���FLASE:��ʹ�á�
	/// \ע�⣺����û����øú�������ת����SDK������IMeetingUIControllerEvent::onCCBTNClicked()�������߼����û��Լ�����
	virtual void RedirectClickCCBTNEvent(bool bRedirect) = 0;

	/// \�����������ܷ���SDK�û��Լ��ĳ������ڻ����еľ�����Ϣ��Ĭ��ֵ:û�С�
	/// \������redirectOption �ò���ָʾҪ���û��Լ��ĳ�����ľ�����Ϣ��
	/// \ע�⣺����û����ô˺�������ת������SDK������IMeetingServiceEvent::onMeetingStatisticsWarningNotification()�������߼����û��Լ�����
	virtual void RedirectMeetingWarningMsg(RedirectWarningMsgOption redirectOption) = 0;

	/// \�����������Ƿ�����ڻ��鹤��������ʱ��ʾ��ť�Ĺ�����ʾ���û�����ͨ�������x���رհ�ť��Ĭ��ֵ:��ġ�
	/// \������bEnable TRUE��ʾ�����ڻ�������ʾ������ʾ��FALSE��ʾ������
	virtual void EnableToolTipsShow(bool bEnable) = 0;

	/// \�������������ػ���ʾIOS�豸�����ָ��ڡ�
	/// \������bEnable ָ�����ػ���ʾIOS�豸�����ָ��ڣ�Ĭ��Ϊ���á�
	/// ������ô�ѡ�����Ҫ����onAirPlayInstructionWndNotification�¼��ص�����ʾ���������Լ��Ĵ��ڡ�
	virtual void EnableAirplayInstructionWindow(bool bEnable) = 0;

	/// \������ enable claim host feature.
	/// \param bEnable specify claim host feature enable or not, default is enable.
	virtual void EnableClaimHostFeature(bool bEnable) = 0;

	/// \�����������Զ�����������Ƶ�Ի���
	/// \������bEnable ָ���˹����������Ĭ��Ϊ����
	virtual void EnableAutoHideJoinAudioDialog(bool bEnable) = 0;

	/// \������Ӧ�ó���ͼ��������ʾ���������б���
	/// \������bAlwaysShow ָ��������ʾ����ʾ��Ĭ���ǲ���ʾ
	virtual void AlwaysShowIconOnTaskBar(bool bAlwaysShow) = 0;

	/// \���������÷���ģʽ��UIԪ�ء�
	/// \����: bDisable ָ���˹��ܽ������Ĭ��Ϊ���á�
	virtual void DisableSplitScreenModeUIElements(bool bDisable) = 0;

	/// \��������ʾ������������������ѡ��
	/// \������bShow ָ���Ƿ���ʾ��ѡ��Ĭ��Ϊtrue��
	virtual void SetShowAudioUseComputerSoundChkbox(bool bShow) = 0;

	/// \��������ʾ��ȫ����Ƶ�Ż�����ѡ��
	/// \������bShow ָ���Ƿ���ʾ��ѡ��Ĭ��Ϊtrue��
	virtual void SetShowVideoOptimizeChkbox(bool bShow) = 0;

	/// \��������ʾ��Phone Call��ѡ�
	/// \������bShow ָ����ֵΪfalseʱ����ѡ���Ĭ��ֵΪtrue��
	virtual void SetShowCallInTab(bool bShow) = 0;

	/// \��������ʾ 'Call Me' ѡ���
	/// \����: bShow ָ����ֵΪfalseʱ����ѡ���Ĭ��ֵΪtrue��
	virtual void SetShowCallMeTab(bool bShow) = 0;

	/// \������ʼ��������Ƶ���ڵı���������ʾ����ID��Ϣ
	/// \������bAlwaysShow ָ���Ƿ�ʼ���ڴ��ڵı���������ʾ����id��Ϣ�����bAlwaysShowΪfalse������Ϊ����ѭZhumu��Ĭ���߼���Ĭ����false��
	virtual void SetAlwaysShowMeetingIDOnTitle(bool bAlwaysShow) = 0;

	///	\���ã���������������ã���ʹ��ICustomizedResourceHelper.AddCustomizedStringResouce()���档
	/// \������ʹ���Զ����ַ����滻ָ���Ĳ˵��
	/// \����: customizedType ָ���˵������͡��йظ�����Ϣ����μ� SDKCustomizedStringType enum��
	/// \������customizedString ָ���Զ����ַ��������Խ�������ΪNULL��ɾ��ָ������Զ����ַ�����
	/// \����: ��������ɹ����򷵻�ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ��ȡ��չ�Ĵ�����Ϣ����μ� SDKError enum��
	/// \ע�⣺���customizedString���ǳ���Ϊ0(0)��NULL���򷵻�ֵΪSDKERR_INVALID_PARAMETER��
	virtual SDKError SetUICustomizedString(SDKCustomizedStringType customizedType, const wchar_t* customizedString) = 0;

	/// \�������Ƿ�ɾ�����öԻ�������������ԡ�Ĭ�ϲ�ɾ����
	/// \������bDisable TRUE ��ʾɾ��. FALSE ��ʾ��ɾ��.
	/// \����: ��������ɹ����򷵻�ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ��ȡ��չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError DisableTopMostAttr4SettingDialog(bool bDisable) = 0;

	/// \�����������Ƿ���û����ʾ������¹رյ�ǰ�������ݲ�ֱ�ӿ�ʼ�µĹ������ݡ�Ĭ��ֵ:FALSE(��ʾ)��
	/// \������bEnable TRUE ��ʾ��ʾ. FALSE ����ʾ.
	/// \����: ��������ɹ����򷵻�ֵΪSDKErr_Success��
	/// ����ʧ�ܡ�Ҫ��ȡ��չ�Ĵ�����Ϣ����μ� SDKError enum��
	virtual SDKError EnableGrabShareWithoutReminder(bool bEnable) = 0;

	/// \��������������������ڹ������û���ͼ�����ø���Ϊ��������ʱ�����л��Ŀɼ�������Ϊ���������߹���Ի���Ĭ��ֵ: TURE. 
	/// \������bEnable TRUE ָʾ�ڼ������ʱ��ʾ�Ի���. FALSE ����ʾ.
	/// \ע�⣺����Ի��򱻽�����ʾ���㽫���յ�IMeetingShareCtrlEvent::onMultiShareSwitchToSingleShareNeedConfirm�ص��¼���
	virtual void EnableShowShareSwitchMultiToSingleConfirmDlg(bool bEnable) = 0;

	/// \���������û�����ʣ�����ʱ�䰴ť�Ŀɼ��ԡ�Ĭ��ֵ:FALSE��
	/// \������bDisable TRUE��ʾ�ڿ��л�����Ҫ����ʱ���ذ�ť��FALSE ������.
	/// \ע�⣺����ð�ť��������ʾ���������յ�IMeetingConfigurationEvent::onfreemeetingtime�ص��¼���
	virtual void DisableFreeMeetingRemainTimeNotify(bool bDisable) = 0;

	/// \�����������Ƿ���ʾ���찴ť�Ͳ˵��Ĭ����ʾ��
	/// \������bHide TRUE ��ʾ����, ������ʾ.
	virtual void HideChatItemOnMeetingUI(bool bHide) = 0;

	/// \�����������Ƿ���ʾ¼�ư�ť�Ͳ˵��Ĭ����ʾ��
	/// \������bHide TRUE ��ʾ����, ������ʾ.
	virtual void HideRecordItemOnMeetingUI(bool bHide) = 0;

	/// \������������ʾ������ʾ��ѻ��鵹��ʱ�Ƿ���ʾ������ť��Ĭ����ʾ��
	/// \������bHide TRUE ��ʾ����, ������ʾ.
	virtual void HideUpgradeFreeMeetingButton(bool bHide) = 0;

	/// \����������ʾ�Ի���ʱ����invite�Ի���������ָ��ѡ��Ŀɼ��ԡ�Ĭ��ֵ:ȫ����ʾ��
	/// \������tabPage ָ��һ����ǩ����SDKInviteDlgTabPage enum��
	/// \������bShow TRUE ָʾҪ��ʾѡ���FALSE ����ʾ.
	virtual void SetShowInviteDlgTabPage(SDKInviteDlgTabPage tabPage, bool bShow) = 0;

	/// \����������ʾ�Ի���ʱ���ڡ����롱�Ի���ġ�������ϵͳ��ѡ�ҳ������ָ��ѡ��Ŀɼ��ԡ�Ĭ��ֵ:ȫ����ʾ
	/// \������tabPage ָ��һ����ǩ���� SDKH323TabPage enum.
	/// \������bShow TRUE ָʾҪ��ʾѡ���FALSE ����ʾ.
	virtual void SetShowH323SubTabPage(SDKH323TabPage tabPage, bool bShow) = 0;

	/// \���������û����Ż���ʱ��Ϊ����û���������������Ϣ�Ŀɼ��ԡ�Ĭ��ֵ:FALSE��
	/// \������bHide TRUE ָʾ���ؾ�����Ϣ��FALSE ��ʾ.
	virtual void HideUpgradeWarningMsgForFreeUserWhenSchedule(bool bHide) = 0;

	/// \���������ñ��ؼ�¼ת���������Ի���Ŀɼ��ԡ�Ĭ��ֵ:TRUE��
	/// \������bShow TRUE ָʾ��ʾ�Ի��� FALSE ����ʾ.
	virtual void EnableLocalRecordingConvertProgressBarDialog(bool bShow) = 0;

	/// \���������õڶ�����������ڵ�����л���ť�Ŀɼ��ԣ�Ĭ��ΪTRUE��
	/// \������bHide TRUE ��ʾ����������л���ť��FALSE ��ʾ.
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

/// \���������������Ϊ���ýӿ�
///
class IJoinMeetingBehaviorConfiguration
{
public:
	/// \���������ü�������������Ĵ�����ʾ��
	/// \������bDisable ָ��������������Ի������ʾ���������ã������õ�MEETING_FAIL_PASSWORD_ERR����ʧ�ܴ���
	virtual void DisablePopupMeetingWrongPSWDlg(bool bDisable) = 0;

	/// \���������õȴ����������Ի���
	/// \������bDisable ָ���ȴ������˶Ի�����ʾ����ʾ
	virtual void DisableWaitingForHostDialog(bool bDisable) = 0;

	/// \�������������»���ʱ���Ƿ����Զ������������顣
	/// \������bEnable ָ���Ƿ��Զ������������顣
	virtual void EnableAutoEndOtherMeetingWhenStartMeeting(bool bEnable) = 0;

	/// \�������������ػ���ʾ�����������Ի���
	/// \������bEnable ָ�������ػ���ʾ����������롱�Ի���Ĭ��Ϊ�����á���.
	/// ������ô�ѡ�����Ҫ����onInputMeetingPasswordAndScreenNameNotification�¼��ص���
	virtual void EnableInputMeetingPasswordDlg(bool bEnable) = 0;

	/// \�������������ػ���ʾ���������Ļ���ƶԻ���
	/// \������bEnable ָ�������ػ���ʾ���������Ļ���ơ��Ի���Ĭ��Ϊ�����á���
	/// ������ô�ѡ�����Ҫ����onInputMeetingPasswordAndScreenNameNotification�¼��ص�
	virtual void EnableInputMeetingScreenNameDlg(bool bEnable) = 0;

	/// \�������ض����������ֻ�ע���߼���IMeetingConfigurationEvent
	/// \������bRedirect �ض�����ض�������ǣ��㽫��IMeetingConfigurationEvent�����·���webinarneedregisternotification
	/// \Ĭ���ǽ��õġ�
	virtual void RedirectWebinarNeedRegister(bool bRedirect) = 0;

	/// \������Ԥ����������ֻ��ע����Ϣ
	/// \������email ָ��Ĭ�ϵĵ����ʼ���
	/// \������username ָ��Ĭ�ϵ��û�����
	virtual void PrePopulateWebinarRegistrationInfo(const wchar_t* email, const wchar_t* username) = 0;

	/// \�������ض���end other��IMeetingConfigurationEvent
	/// \������bRedirect �ض����������ǣ��㽫����IMeetingConfigurationEvent�м���һ��endothermeetingjoinmeetingnotification
	/// \Ĭ���ǽ��õ�.
	virtual void RedirectEndOtherMeeting(bool bRedirect) = 0;

	/// \�����������Ƿ��ܹ�ǿ�Ʋ����߼������ʱ��ʼ��Ƶ��
	/// \������bEnable TRUE ָ��ǿ�Ʋμ��߿�ʼ��Ƶ��
	/// \ע�⣺Ĭ����Ϊȡ���ڻ�������á�
	virtual void EnableForceAutoStartMyVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \�����������Ƿ��ܹ�ǿ�Ʋ����߼������ʱ�ر���Ƶ��
	/// \������bEnable TRUE ָʾǿ�Ʋ����߹ر���Ƶ��
	/// \ע�⣺Ĭ����Ϊȡ���ڻ�������á�
	virtual void EnableForceAutoStopMyVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \�����������ڼ������ʱѡ�������Ƶ�Ի���Ŀɼ��ԡ�Ĭ��ֵ:FALSE��
	/// \������bDisable TRUE ָʾ���ضԻ���
	virtual void DisableAutoShowSelectJoinAudioDlgWhenJoinMeeting(bool bDisable) = 0;

	/// \brief Set the visibility of the dialog box of joining a meeting. Default: FALSE.
	/// \param bDisable TRUE indicates to hide the dialog box. FALSE not.
	virtual void DisableShowJoinMeetingWnd(bool bDisable) = 0;
};

/// \������ Meeting Configuration Interface
///
class IMeetingConfiguration :
	public IMeetingUIElemConfiguration,
	public IJoinMeetingBehaviorConfiguration
{
public:
	/// \���������û�������֪ͨ�Ĵ������
	/// \������pEvent ���ڽ��մ���Ϣ���ͱ�����
	virtual void SetEvent(IMeetingConfigurationEvent* pEvent) = 0;

	/// \���������û�������
	virtual void Reset() = 0;

	/// \����������ֱ�ӹ������ʾ����id��
	/// \������monitorID ָ��Ҫ�����ĸ���ʾ����ʹ��EnumDisplayMonitorsϵͳapi����ȡ���ֵ
	/// ��ο�MONITORINFOEX�ṹ�е�szDevice��
	virtual void SetDirectShareMonitorID(const wchar_t* monitorID) = 0;

	/// \���������������ʱ���Ƿ����Զ�������������������
	/// \������bEnable ָ���Զ����������������������Ĭ��Ϊ���á�
	virtual void EnableAutoAdjustSpeakerVolumeWhenJoinAudio(bool bEnable) = 0;

	/// \���������������ʱ���Ƿ����Զ�������˷��������
	/// \������bEnable ָ���Զ�������˷������������Ĭ��Ϊ���á�
	virtual void EnableAutoAdjustMicVolumeWhenJoinAudio(bool bEnable) = 0;

	/// \����������DSCP��
	/// \������dscpAudio ��Ƶ��DSCPֵ��
	/// \������dscpVideo ��Ƶ��DSCPֵ��
	/// \������bReset ����DSCPֵ��
	virtual void ConfigDSCP(int dscpAudio, int dscpVideo, bool bReset) = 0;

	/// \������Զ�̿���ʱ���ø��ƺ�ճ������
	/// \������bDisable ָ���˹��ܽ������Ĭ��Ϊ���á�
	virtual void DisableRemoteCtrlCopyPasteFeature(bool bDisable) = 0;

	/// \�������������ش��绰�û��������绰����
	/// \������bHide ָ���˹����Ƿ����ã�Ĭ������²����ء�
	virtual void EnableHideFullPhoneNumber4PureCallinUser(bool bHide) = 0;

	/// \������Enable the length limitation of meeting number
	/// \������bEnable specify this feature enable or not, default is enable.
	virtual void EnableLengthLimitationOfMeetingNumber(bool bEnable) = 0;

	/// \����������IOS�豸����
	/// \������bEnable ָ���˹����������Ĭ��Ϊ���á�
	virtual void EnableShareIOSDevice(bool bEnable) = 0;

	/// \���������ðװ干��
	/// \������bEnable ָ���˹����������Ĭ��Ϊ���á�
	virtual void EnableShareWhiteBoard(bool bEnable) = 0;

	/// \������ǿ�ƽ��ö��˹���
	/// \������bDisable ָ���˹��ܽ������Ĭ��Ϊ���á�
	virtual void ForceDisableMultiShare(bool bDisable) = 0;

	/// \��������û�вλ���ʱ�����û����������ʱ�䡣Ĭ��ֵ:24 * 60��
	/// \������nDuration ָ��������ʱ��(�Է���Ϊ��λ)��
	virtual void SetMaxDurationForOnlyHostInMeeting(int nDuration) = 0;

	/// \brief Set if it is able to leave the meeting when the screen is locked or the screen saver is shown. Default: TRUE.
	/// \param bEnable TRUE indicates to enable to share on the white board. FALSE not.
	/// \remarks No matter what value you set for API, the callback IMeetingServiceEvent::onOSSessionChangedNotification will be triggered.
	virtual void EnableLeaveMeetingWhenScreenLocked(bool bEnable) = 0;
};

END_ZHUMU_SDK_NAMESPACE
#endif