/*!
* \�ļ���meeting_ui_ctrl_interface.h
* \�������������ӿ�UI������
* \��������zhumu����UIģʽ
*/
#ifndef ZHUMU_MEETING_UI_CTRL_INTERFACE_H_
#define ZHUMU_MEETING_UI_CTRL_INTERFACE_H_
#include "..\zhumu_sdk_def.h"

/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum SDKMeetingUIType
\����������ui�����͡�
����ϸ�Ľṹ������
*/
enum SDKMeetingUIType
{
	SDK_Meeting_UI_None,
	SDK_Meeting_UI_VideoWall_Mode,
	SDK_Meeting_UI_ActiveRender_Mode,
};

/*! \struct tagVideoWallPageInfoParam
\��������Ƶҳ�����Ϣ��
����ϸ�Ľṹ������
*/
typedef struct tagVideoWallPageInfoParam
{
	int nCurrentPage;
	int nTotalPages;
}VideoWallPageInfoParam;

/*! \struct tagShowChatDlgParam
\��������ʾ��������Ի��������
����ϸ�Ľṹ������
*/
typedef struct tagShowChatDlgParam
{
	HWND hParent;///<�����ھ��
	RECT rect;///< ����Ի���λ��
	HWND hChatWnd;///< �������촰�ھ��
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
\������������Ƶui�����͡�
����ϸ�Ľṹ������
*/
enum SDKFloatVideoType
{
	FLOATVIDEO_List,
	FLOATVIDEO_Small,
	FLOATVIDEO_Large,
	FLOATVIDEO_Minimize,
};

/*! \enum SDKMinimizeUIMode
\��������С��UIģʽ�����͡�
����ϸ�Ľṹ������
*/
enum SDKMinimizeUIMode
{
	MinimizeUIMode_NONE,
	MinimizeUIMode_SHARE,
	MinimizeUIMode_VIDEO,
	MinimizeUIMode_ACTIVESPEAKER,
};

/*! \struct tagSplitScreenInfo
\����������ģʽ��Ϣ��
����ϸ�Ľṹ����.
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
    \�������û��ڻ�ȡ�ص��¼�"IMeetingUIControllerEvent::onAudioBtnClicked()"�����ȡ�Ĳ��� 
    �����Ǹ���ϸ�Ľṹ������
*/
enum AudioCallbackActionInfo
{
	ACTION_NONE = 0,///<���ڳ�ʼ��.
	ACTION_CHOOSE_AUDIO_DEVICE_NOAUDIODEVICECONNECTTED,///<ѡ����Ƶ�豸����Ϊ��δ������Ƶ�豸��
	ACTION_CHOOSE_AUDIO_DEVICE_COMPUTERAUDIODEVICEERROR,///<ѡ����Ƶ�豸����Ϊ�����Ӽ������Ƶ�豸ʱ��������
	ACTION_CHOOSE_AUDIO_DEVICE_PHONECALLDEVICEERROR,///<ѡ����Ƶ�豸����Ϊ�����ӵ绰�����豸ʱ��������
	ACTION_NEED_JOIN_VOIP,///<��Ҫ����voip
	ACTION_MUTE_UNMUTE_AUDIO,///<���� "AudioBtnClickedCallbackInfo::userid_MuteUnmute" ��ֹ�����û���Ƶ
	ACTION_SHOW_AUDIO_SETTING_WINDOW,///<��ʾ��Ƶ���ô���
};

/*! \struct tagAudioBtnClickedCallbackInfo
    \����: �û��ڻ�ȡ�ص��¼�"IMeetingUIControllerEvent::onAudioBtnClicked()"�����ȡ�Ĳ��� 
    �����Ǹ���ϸ�Ľṹ������
*/
typedef struct tagAudioBtnClickedCallbackInfo
{
	unsigned int userid_MuteUnmute;///<Ӧ���û�ȡ�����õ��û���id��������Ҫ������ȡ����������ʱ����ֵΪ0
	AudioCallbackActionInfo audio_clicked_action;///<�����û���ȡ�Ĳ�����
	tagAudioBtnClickedCallbackInfo()
	{
		userid_MuteUnmute = 0;
		audio_clicked_action = ACTION_NONE;
	}

}AudioBtnClickedCallbackInfo;

/// \������Meeting UI Controller�ص��¼�.
///
class IMeetingUIControllerEvent
{
public:
	/// \������������Invite��ťʱ�Ļص����̡�
	/// \������[in out] bHandled ���Ӧ�ó�����ʾ�Լ���invite�Ի�����������ΪTRUE�����ΪFLASE����ΪĬ��ֵ��
	/// \ע�⣺���bhandleδ����Ϊtrue������Ӧ�ó����Ƿ���������ʾĬ�ϵ�Zhumu invite�Ի���
	virtual void onInviteBtnClicked(bool& bHandled) = 0;
	virtual void onStartShareBtnClicked() = 0;
	virtual void onEndMeetingBtnClicked() = 0;
	virtual void onParticipantListBtnClicked() = 0;
	virtual void onCustomLiveStreamMenuClicked() = 0;

	/// \������ֻ��SDK�޷���ʾĬ�ϵ�ZHUMU INVITE�Ի���ʱ����֪ͨ��
	virtual void onZoomInviteDialogFailed() = 0;

	/// \����������CC�˵��Ļص��¼���
	/// \ע�⣺�����û��ض��򵥻�CUSTOME LIVE���˵��Ľ��̣������������յ�����ص��¼����й���ϸ��Ϣ����μ�IMeetingUIElemConfiguration::RedirectClickCustomLiveStreamMenuEvent();
	virtual void onCCBTNClicked() = 0;

	/// \�����������ڻ����е�����Ƶ��ť�Ļص��¼���
	/// \ע�⣺�����û������ض����ڻ����е�����Ƶ��ť�Ĺ��̣����򲻻���մ˻ص��¼�����ϸ�뿴: IMeetingUIElemConfiguration::RedirectClickAudioBTNEvent().
	virtual void onAudioBtnClicked(AudioBtnClickedCallbackInfo info) = 0;
	
	/// \�����������ڻ����е�����Ƶ�˵���ť�Ļص��¼���
	/// \ע�⣺�����û������ض����ڻ����е�����Ƶ�˵���ť�Ĺ��̣����򲻻���մ˻ص��¼�����ϸ�뿴: IMeetingUIElemConfiguration::RedirectClickAudioMenuBTNEvent().
	virtual void onAudioMenuBtnClicked() = 0;

	/// \�����������е����������ҡ���ť�Ļص��¼���
	/// \ע�⣺�����û������ض����ڻ����е��������Ұ�ť�Ĺ��̣����򲻻���մ˻ص��¼�����ϸ�뿴: IMeetingUIElemConfiguration::RedirectClickBreakoutRoomButtonEvent().
	virtual void onBreakoutRoomBtnClicked() = 0;
	
};

/// \����������UI�������ӿ�
///
class IMeetingUIController
{
public:
	/// \���������û���ui�������ص��¼�
	/// \������pEvent һ��ָ��IMeetingUIControllerEvent*��ָ�룬�����ջ���ui�¼���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IMeetingUIControllerEvent* pEvent) = 0;

	/// \��������ʾ��������Ի���
	/// \������param ָ�������ʾ����Ի���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError ShowChatDlg(ShowChatDlgParam& param) = 0;

	/// \���������ػ�������Ի���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError HideChatDlg() = 0;

	/// \����������ȫ��ģʽ
	/// \������firstView ָ����һ����Ļ�Ƿ����ȫ��ģʽ
	/// \������secondView �������˫��ʾ��ģʽ��ָ���ڶ�����ʾ���Ƿ����ȫ��ģʽ��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError EnterFullScreen(bool firstView, bool secondView) = 0;

	/// \�������˳�ȫ��ģʽ
	/// \����: firstView ָ����һ����ʾ���Ƿ��˳�ȫ��ģʽ��
	/// \������secondView �������˫������ģʽ��ָ���ڶ����������Ƿ��˳�ȫ��ģʽ��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError ExitFullScreen(bool firstView, bool secondView) = 0;

	/// \���������ص�������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError BackToMeeting() = 0;

	/// \������ Switch to video wall mode. 
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SwitchToVideoWall() = 0;

	/// \�������л�������ʽ��������ͼ
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SwtichToAcitveSpeaker() = 0;

	/// \�������ƶ�������Ƶ����
	/// \������left ָ��������Ƶ���ڵ����λ�á�
	/// \������top ָ��������Ƶ���ڵĶ���λ�á�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError MoveFloatVideoWnd(int left, int top) = 0;

	/// \��������ʾ������������
	/// \������bShow ָ���Ƿ���ʾ������������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError ShowSharingToolbar(bool bShow) = 0;

	/// \��������������Ƶ���л�������ʽ��������ͼ
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SwitchFloatVideoToActiveSpkMod() = 0;

	/// \�������ı両������ʽ������Ƶ���Ĵ�С
	/// \������type ָ��������Ƶ�����ͼ���͡�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError ChangeFloatoActiveSpkVideoSize(SDKFloatVideoType type) = 0;

	/// \��������������Ƶ���л���������ͼ
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SwitchFloatVideoToGalleryMod() = 0;

	/// \��������ʾ�������б���
	/// \������bShow Specifies the participants List Window show or not
	/// \������hParticipantsListWnd if bShow is true,and api call success, will return the handle of the participants List window
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError ShowParticipantsListWnd(bool bShow, HWND& hParticipantsListWnd) = 0;

	/// \��������ʾ�ײ���������������
	/// \������bShow ָ���ײ�����������������ʾ���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError ShowBottomFloatToolbarWnd(bool bShow) = 0;

	/// \��������ȡ����UI���ڵľ��
	/// \������hFirstView ���ػ���UI���ڵĵ�һ����ͼ����ı�����
	/// \������hSecondView ���ػ���UI���ڵĵڶ�����ͼ����ı�����
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError GetMeetingUIWnd(HWND& hFirstView, HWND& hSecondView) = 0;

	/// \��������ʾ������Ƶ�Ի���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError ShowJoinAudioDlg() = 0;

	/// \����������������Ƶ�Ի���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError HideJoinAudioDlg() = 0;

	/// \��������ȡ��ҳ��Ϣ����Ƶǽģʽ��
	/// \������videoWallPageInfoParam �洢��ǰҳ����������ҳ�档
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError GetWallViewPageInfo(VideoWallPageInfoParam& videoWallPageInfoParam) = 0;

	/// \��������ʾǰһҳ����һҳ��Ƶ�û�����Ƶǽģʽ��
	/// \������bPageUp ָ����һҳ����һҳ��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError ShowPreOrNextPageVideo(bool bPageUp) = 0;

	/// \��������ʾ�������������Ӧ�ó���Ĺ����ܴ��ڡ�
	/// \������bShow ָ����ʾ������.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError ShowSharingFrameWindows(bool bShow) = 0;

	/// \������ȷ����һ����Ļ�ϻ���ui���ڵ���С��״̬��
	/// \������mode �����һ����Ļ�ϵĻ���ui���ڴ�����С��״̬���򷵻���С��ģʽ��
	/// \���أ�true �� false
	virtual bool IsMinimizeModeOfFristScreenMeetingUIWnd(SDKMinimizeUIMode& mode) = 0;

	/// \�����������һ����Ļ�ϵĻ���ui���ڴ�����С��״̬���������С��ģʽ��
	/// \������mode ָ����С��ģʽ��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SwitchMinimizeUIMode4FristScreenMeetingUIWnd(SDKMinimizeUIMode mode) = 0;

	/// \��������ȡ��ǰ����ģʽ����Ϣ
	/// \������info ��ǰ����ģʽ����Ϣ��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError GetCurrentSplitScreenModeInfo(SplitScreenInfo& info) = 0;

	/// \�������ڲ鿴����Ͳ�����˫��ʾ��ģʽʱ�����л�����ģʽ���л�����ģʽ��
	/// \������bSplit �Ƿ����ģʽ��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SwitchSplitScreenMode(bool bSplit) = 0;

	/// \�����������˷���ʱ�����һ��鴰�ڲ���ȫ���ġ�����Ե���api���л���Ƶ�͹�����ʾλ�á�
	/// \������bToDisplayShare TRUE means to display share, otherwise video.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SwapToShowShareViewOrVideo(bool bToDisplayShare) = 0;

	/// \������ȷ�����������Ƿ���ʾ������Ļ��
	/// \������[out] bIsShare TRUE ��˼����ʾ������Ļ��FALSE ��˼����ʾ��Ƶ��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError IsDisplayingShareViewOrVideo(bool& bIsShare) = 0;

	/// \������ȷ���û������Ƿ�����л���������Ļ����Ƶ��
	/// \������[out] bCan TRUE ��ʾ����, ������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError CanSwapToShowShareViewOrVideo(bool& bCan) = 0;
};

END_ZHUMU_SDK_NAMESPACE
#endif