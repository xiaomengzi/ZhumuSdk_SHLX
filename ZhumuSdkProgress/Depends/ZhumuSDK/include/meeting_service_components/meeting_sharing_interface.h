/*!
* \�ļ���meeting_sharing_interface.h
* \���������鹲�����ӿ�
*
*/
#ifndef ZHUMU_MEETING_SHARING_INTERFACE_H_
#define ZHUMU_MEETING_SHARING_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include <vector>
/// \������ Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum SharingStatus
\����������״̬��
����ϸ�Ľṹ����
*/
enum SharingStatus
{
	Sharing_Self_Send_Begin,
	Sharing_Self_Send_End,
	Sharing_Other_Share_Begin,
	Sharing_Other_Share_End,
	Sharing_View_Other_Sharing,
	Sharing_Pause,
	Sharing_Resume,
};

/*! \struct tagViewableShareSource
\�������ɲ鿴�Ĺ���Դ��Ϣ��
����ϸ�Ľṹ����
*/
typedef struct tagViewableShareSource
{
	unsigned int userid;
	bool isShowingInFirstView;
	bool isShowingInSecondView;
	bool isCanBeRemoteControl;
	tagViewableShareSource()
	{
		userid = 0;
		isShowingInFirstView = false;
		isShowingInSecondView = false;
		isCanBeRemoteControl = false;
	}
}ViewableShareSource;

/*! \enum ��ǰ���������.
����ϸ�Ľṹ����
*/
enum ShareType
{
	SHARE_TYPE_UNKNOWN, //δ֪
	SHARE_TYPE_AS,	//����Ӧ��
	SHARE_TYPE_DS,	//��������
	SHARE_TYPE_WB,	//�װ干��
	SHARE_TYPE_AIRHOST,	//PC�Ϲ����ֻ��豸
	SHARE_TYPE_CAMERA,	//����ͷ����
	SHARE_TYPE_DATA,	//���ݹ���
};
/*! \enum AdvanceShareOption
��ǰ���͸����˵Ĺ����������͡�
�����и���ϸ�Ľṹ������
*/
enum AdvanceShareOption
{
	AdvanceShareOption_ShareFrame,///<��������ѡ������
	AdvanceShareOption_PureComputerAudio,///<ֻ����������Ƶ��
	AdvanceShareOption_ShareCamera,///<��������ͷ
};
/*! \struct tagShareInfo
\��������ǰ�������Ϣ��
����ϸ�Ľṹ����.
*/
enum MultiShareOption
{
	Enable_Multi_Share = 0, ///<��������߿���ͬʱ����
	Enable_Only_HOST_Start_Share, ///<һ��ֻ������������
	Enable_Only_HOST_Grab_Share, ///<һ�������߿���һ�η������������ֻ���������Կ�ʼ�µķ���֮ǰ�ķ�����ȡ����
	Enable_All_Grab_Share, ///<һ�������߿���һ�η����ڷ���Ĺ����У�ÿ���˶����Կ�ʼһ���µķ���֮ǰ�ķ�����ȡ����
};

typedef struct tagShareInfo
{
	ShareType eShareType;  //�������ͣ��ο�ShareType
	union
	{
		HWND hwndSharedApp;  //����Ӧ�ó����װ�ľ��������eShareTypeΪSHARE_TYPE_AS��SHARE_TYPE_WBʱ��Ч
		const wchar_t* monitorID;  //�����������ʾ��id��ֻ�е�eShareTypeΪSHARE_TYPE_DSʱ����Ч
	}ut;
	tagShareInfo()
	{
		eShareType = SHARE_TYPE_UNKNOWN;
		memset(&ut, 0, sizeof(ut));
	}
}ShareInfo;

/// \���������Ѵ������Ӷ�������л�����������
///
class IShareSwitchMultiToSingleConfirmHandler
{
public:
	/// \������ȡ���Ӷ๲���л�Ϊ���������з���������
	virtual SDKError Cancel() = 0;

	/// \���������๲���л�Ϊ���������з���������
	virtual SDKError Confirm() = 0;

	virtual ~IShareSwitchMultiToSingleConfirmHandler() {};
};

/// \���������鹲��������Ļص��¼���
///
class IMeetingShareCtrlEvent
{
public:
	/// \����������״̬֪ͨ�ص�
	/// \������status ����״ֵ̬��
	/// \������userId �����û�id
	virtual void onSharingStatus(SharingStatus status, unsigned int userId) = 0;

	/// \��������������״̬֪ͨ�ؽ�
	/// \������bLocked ָ�������Ƿ�������
	virtual void onLockShareStatus(bool bLocked) = 0;

	/// \���������Ĺ�����Ϣ�Ļص��¼���
	/// \������shareInfo ������Ϣ���й���ϸ��Ϣ����μ� ShareInfo �ṹ��
	virtual void onShareContentNotification(ShareInfo& shareInfo) = 0;

	/// \����������������߹����л���һ�������߹���Ļص��¼���
	/// \������handler_ An �û��������������ز����Ķ���ָ�롣�йظ���ϸ�ڣ���μ�IShareSwitchMultiToSingleConfirmHandler��
	virtual void onMultiShareSwitchToSingleShareNeedConfirm(IShareSwitchMultiToSingleConfirmHandler* handler_) = 0;
};

/// \���������鹲��������ӿ�
///
class IMeetingShareController
{
public:
	/// \���������û��鹲��������ص��¼�
	/// \������pEvent һ��ָ����չ����¼���IMeetingShareCtrlEvent*��ָ�롣
	/// \����: ��������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetEvent(IMeetingShareCtrlEvent* pEvent) = 0;

	/// \����������Ӧ�ó�����
	/// \������hwndSharedApp ָ��Ҫ�����ĸ����ڡ�
	/// ���hwndSharedApp���ܹ�������SDKERR_INVALID_BRIEF:ETER������롣���hwndSharedAppΪ�գ�����ʾѡ��Ӧ�ó���Ի���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError StartAppShare(HWND hwndSharedApp) = 0;

	/// \��������ʼ���湲��
	/// \������ monitorID ��ָ��Ҫ�����ĸ���ʾ����ʹ��EnumDisplayMonitorsϵͳapi����ȡ���ֵ��
	/// ��ο�MONITORINFOEX�ṹ�е�szDevice�����monitorIDΪ�գ�����ʾѡ��Ӧ�ó���Ի���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError StartMonitorShare(const wchar_t* monitorID) = 0;

	/// \��������ʼIOS�豸����
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError StartAirPlayShare() = 0;

	/// \��������ʼ�װ干��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	/// ��������Զ���ģʽ��ʹ�����ǵ�sdk������ʹ��SHARE_TYPE_WB���onShareContentNotificationʱ�����Լ���ע����
	virtual SDKError StartWhiteBoardShare() = 0;

	/// \��������ʾ����Ӧ��ѡ�񴰿ڡ�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��֧��zhumu����UI
	virtual SDKError ShowSharingAppSelectWnd() = 0;

	/// \������ Determine if the specified ADVANCE SHARE OPTION is supported. 
	/// \������ option_ The ADVANCE SHARE OPTION to be determined. For more information, see \link AdvanceShareOption \endlink enum.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError IsSupportAdvanceShareOption(AdvanceShareOption option_) = 0;

	/// \��������ʼ�����ڡ�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError StartShareFrame() = 0;

	/// \����������ʼ����������Ƶ��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError StartSharePureComputerAudio() = 0;

	/// \��������ʼ���������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError StartShareCamera() = 0;

	/// \������ֹͣ��ǰ����
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError StopShare() = 0;

	/// \������ ��Ļ��������ֹ���ڹ���
	/// ���api���ı䴰�ڵ����ԡ����ǲ�����ʹ�á�
	/// ���ô�api����Ҫ���»��ƴ˴��ڲ�����Ч��
	/// \������ bBlock ����Ļ������ֹ���ڡ�.
	/// \������ hWnd ָ��Ҫ�����ĸ����ڡ�.
	/// \������ bChangeWindowStyle ���Ϊfalse������StartMonitorShare api֮����ô�api
	/// ����������Sharing_Self_Send_Begin���sharingstatus�ص�֮��
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��֧��zhumu����UI
	virtual SDKError BlockWindowFromScreenshare(bool bBlock, HWND hWnd, bool bChangeWindowStyle = true) = 0;

	/// \������������ǰ����Ĺ���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError LockShare() = 0;

	/// \������������ǰ����Ĺ���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError UnlockShare() = 0;

	/// \����������ͼ����ʱ����������ͼ�����л�Ϊ�ʺϴ���ģʽ��
	/// \������type ָ��Ҫ���õ���ͼ����һ�����������ǵڶ�����������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��֧��zhumu����UI
	virtual SDKError SwitchToFitWindowModeWhenViewShare(SDKViewType type) = 0;

	/// \����������ͼ����ʱ����������ͼ�����л���ԭʼ��Сģʽ��
	/// \������type ָ��Ҫ���õ���ͼ����һ�����������ǵڶ�����������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��֧��zhumu����UI
	virtual SDKError SwitchToOriginalSizeModeWhenViewShare(SDKViewType type) = 0;

	/// \��������ͣ��ǰ�ķ���
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError PauseCurrentSharing() = 0;

	/// \���������µ�ǰ����
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError ResumeCurrentSharing() = 0;

	/// \��������ȡ��ǰ�ɼ��Ĺ���Դ�б�
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual std::vector<unsigned int> GetViewableShareSourceList() = 0;

	/// \������ͨ��userid��ȡ�ɲ鿴�Ĺ���Դ��
	/// \������userid ָ��Ҫ��ȡ�Ŀɲ鿴����Դ��Ϣ��
	/// \������shareSource �洢�ɲ鿴�Ĺ���Դ��Ϣ
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError GetViewabltShareSourceByUserID(unsigned int userid, ViewableShareSource& shareSource) = 0;

	/// \������ͨ��userid������ͼ��
	/// \������userid ָ��Ҫ�鿴�Ķ���
	/// \������type ָ��Ҫ�鿴������ĸ���ͼ����һ�����������ǵڶ�����������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��֧��zhumu����UI
	virtual SDKError ViewShare(unsigned int userid, SDKViewType type) = 0;

	/// \��������ʾ��������Ի���.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \��֧��zhumu����UI
	virtual SDKError ShowShareOptionDialog() = 0;

	/// \�������ж��Ƿ���Կ�������
	/// \���أ��Ƿ���Կ�������
	/// \֧��zhumu�����Զ���UI���
	virtual bool CanStartShare() = 0;

	/// \��������ѯ�����Ƿ�������
	/// \������bLocked �洢����ʱ������
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError IsShareLocked(bool& bLocked) = 0;

	/// \��������ѯ����֧�ֹ��������������
	/// \������bCurEnableOrNot �洢�����Ƿ�֧�ֹ�����������
	/// \���أ�֧�ֹ��������������
	/// \֧��zhumu�����Զ���UI���
	virtual bool IsSupportEnableShareComputerSound(bool& bCurEnableOrNot) = 0;

	/// \��������ѯ�����Ƿ�֧���Ż�ȫ����Ƶ������
	/// \������bCurEnableOrNot �Ƿ�֧���Ż�ȫ����Ƶ����.
	/// \���أ��Ƿ�֧���Ż�ȫ����Ƶ����.
	/// \֧��zhumu�����Զ���UI���
	virtual bool IsSupportEnableOptimizeForFullScreenVideoClip(bool& bCurEnableOrNot) = 0;

	/// \���������ù�����������.
	/// \������bEnable �Ƿ�����.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError EnableShareComputerSound(bool bEnable) = 0;

	/// \�����������Ż�ȫ����Ƶ������
	/// \������bEnable �Ƿ�����.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	/// \֧��zhumu�����Զ���UI���
	virtual SDKError EnableOptimizeForFullScreenVideoClip(bool bEnable) = 0;

	/// \���������ö�����߹���ѡ��
	/// \������shareOption �鿴 MultiShareOption enum.
	/// \���أ���������ɹ����򷵻�ֵΪSDKErr_Success��
	/// �������ʧ�ܣ��򷵻�ֵ����SDKErr_Success��Ҫ�����չ�Ĵ�����Ϣ����ο�SDKError enum��
	virtual SDKError SetMultiShareSettingOptions(MultiShareOption shareOption) = 0;

	/// \brief Get the options for multi-participants share.
	/// \param [out] shareOption Options for sharing, see \link MultiShareOption \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GetMultiShareSettingOptions(MultiShareOption& shareOption) = 0;

	/// \brief Determine whether can switch to next camera, when share camera. 
	/// \param [Out] bCan, if bCan is true it means you can switch, else can not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanSwitchToShareNextCamera(bool& bCan) = 0;

	/// \brief switch to next camera, when you are sharing the camera.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SwitchToShareNextCamera() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif