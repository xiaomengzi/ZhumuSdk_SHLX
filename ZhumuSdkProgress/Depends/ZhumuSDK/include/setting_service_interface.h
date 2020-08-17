/*!
* \�ļ� setting_service_interface.h
* \���� Setting Service Interface
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
/// \����������ͷ�豸��Ϣ�ӿ�
///
class ICameraInfo
{
public:
	/// \��������ȡ����ͷ�豸ID
	/// \���أ�����������óɹ��𣬷���ֵ������ͷ���豸ID.
	/// �������ʧ�ܣ�����ֵ�ǿ�.
	virtual const wchar_t* GetDeviceId() = 0;

	/// \��������ȡ����ͷ�豸��
	/// \���أ�����������óɹ�������ֵ������ͷ���豸���֡�
	/// ���ʧ�ܣ� ����ֵ��NULL.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetDeviceName() = 0;

	/// \��������ѡ����ͷ��־
	/// \���أ���﷽�����óɹ�������ֵ��true,������ͷ�Ǳ�ѡ�������ͷ��
	virtual bool IsSelectedDevice() = 0;

	virtual ~ICameraInfo() {};
};

/// \��������˷��豸��Ϣ�ӿ�
///
class IMicInfo
{
public:
	/// \��������ȡ��˷��豸ID
	/// \���أ�����������óɹ�������ֵ������ͷ�豸ID.
	///	���ʧ�ܣ�����ֵ��NULL.
	virtual const wchar_t* GetDeviceId() = 0;

	/// \��������ȡ����ͷ�豸��
	/// \����:����������óɹ�������ֵ����˷�������.
	/// ���ʧ�ܣ� ����ֵ��NULL.
	virtual const wchar_t* GetDeviceName() = 0;

	/// \��������ѡ�豸��־
	/// \���أ��������true,��ʾ���豸��ѡ��.
	virtual bool IsSelectedDevice() = 0;

	virtual ~IMicInfo() {};
};

/// \��������Ƶ����豸��Ϣ�ӿ�
///
class ISpeakerInfo
{
public:
	/// \��������ȡ����豸ID
	/// \���أ�����������óɹ��� ����ֵ���豸Id.
	/// ���ʧ�ܣ�����ֵ��NULL.
	virtual const wchar_t* GetDeviceId() = 0;

	/// \��������ȡ����豸��
	/// \���أ�����������óɹ�������ֵ���豸��.
	/// �������ʧ�ܣ�����ֵ��NULL.
	virtual const wchar_t* GetDeviceName() = 0;

	/// \��������ѡ�豸��־
	/// \���أ��������ֵ��true, ��ʾ������Ǳ�ѡ����豸.
	virtual bool IsSelectedDevice() = 0;

	virtual ~ISpeakerInfo() {};
};

/*! \enum LimitFPSValue
	\���� ָ����������fps��ֵ.
	�����ǽṹ����ϸ����
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
	SettingTabPage_General,///<��������ҳ.
	SettingTabPage_Audio,///<��������ҳ.
	SettingTabPage_Video,///<��Ƶ����ҳ.
};
/*! \struct tagShowChatDlgParam
    \������չʾ���������촰�ڵĲ���.
	�����ǽṹ����ϸ����
*/
typedef struct tagShowSettingDlgParam
{
	HWND hParent;///< �����ھ��
	int top;///< ���ô��ڶ���λ��
	int left;///< ���ô������λ��
	HWND hSettingWnd;///< �������ô��ھ��
	bool bShow;///< ��ʾ������
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
    \�������������ô����еı�ǩ��ʾ����
    �����ǽṹ����ϸ����
*/
typedef struct tagSettingDlgShowTabPageOption
{
	bool bShowGeneral;///<True ��ʾ��ʾ����ҳ
	bool bShowVideo; ///<True ��ʾ��ʾ��Ƶҳ
	bool bShowAudio;///<True ��ʾ��ʾ��Ƶҳ
	bool bShowShareScreen; ///<True indicates to show share screen page
	bool bShowVirtualBackGround;///<True ��ʾ��ʾ���ⱳ��ҳ 
	bool bSHowRecording;///<True ������ʾ¼��ҳ
	bool bShowAdvancedFeature;///<True ������ʾ�߼�����ҳ
	bool bShowStatistics;///<True ������ʾͳ��ҳ 
	bool bShowFeedback;///<True ��ʾ��ʾ����ҳ
	bool bShowKeyboardShortcuts;///<True indicates to show keyboard shortcuts page
	bool bShowAccessibility;///<True ��ʾ��ʾ��������ҳ
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
    \������ ����ʱ��˷��֪ͨ״̬.
    �����ǽṹ����ϸ����
*/
typedef	enum
{
	enuCanTest = 0, ///< �ܵ��ò���TestMicStartRecording��ʼ��˷���ԣ���ʱ����TestMicStopTesting/TestMicPlayRecording����.
	enuMicRecording,///< �ܵ���TestMicStopTesting/TestMicPlayRecording����ʱ����TestMicStartRecording����.
	enuCanPlay,		///< �ܵ���TestMicStopTesting/TestMicPlayRecording����ʱ����TestMicStartRecording����.
					///< enuCanPlay ״̬��ʾSDK�Ѿ�¼����6s��������������״̬�£����bHandledû������Ϊtrue. SDK����������TestMicStopTesting.
} SDK_TESTMIC_STATUS;

/// \��������Ƶ�豸���Իص��¼�
//
class ITestAudioDeviceHelperEvent
{
public:
	/// \�������ڲ����ڼ䣬֪ͨ��ǰ��˷�������������������С.
	/// \������MicVolume [out] ��˷�����.
	/// \������SpkVolume [out] ����������.
	/// ��Щֵ����������˷�������������ڼ���ʾ����������.
	virtual void OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume) = 0;

	/// \������δ�ҵ���˷��������ʱ��֪ͨ�ص�.
	/// \���� bMicOrSpk True ��ʾû����˷��豸��False ��ʾû���������豸.
	virtual void OnNoAudioDeviceIsUseful(bool bMicOrSpk) = 0; 

	/// ��������˷�����ڼ��״̬֪ͨ.
	/// \���� status �鿴 enum SDK_TESTMIC_STATUS ��ȡ������ϸ��Ϣ
	/// \���� bHandled ����Ϊtrueʱ��ʾ����SDK��Ĭ����˷�״̬�߼�. 
	/// \�鿴 SDK_TESTMIC_STATUS
	virtual void OnTestMicStatusChanged(SDK_TESTMIC_STATUS status,bool& bHandled) = 0; 

	/// \�������ڲ����ڼ�֪ͨ�û�һ����˷ֻ��������豸��ѡ��SDK���رղ��ԣ��û���Ҫ�ֶ�������������.
	virtual void OnSelectedAudioDeviceIsChanged() = 0;
};

/// \������ ��Ƶ�豸���Խӿ�.
///
class ITestAudioDeviceHelper
{
public:
	/// \��������Ƶ�豸���Իص��¼�. 
	/// \������pEvent [in] һ��������Ƶ�豸�����¼���ָ�� ITestAudioDeviceHelperEvent*. 
	/// \���أ�����������óɹ�������SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ����SDKErr_Success, ��ȡ���������Ϣ�鿴��SDKError enum.
	/// \�鿴��ITestAudioDeviceHelperEvent
	/// \ע�⣺�����������ʹ�������������ӿ�֮ǰ����.
	virtual SDKError SetEvent(ITestAudioDeviceHelperEvent* pEvent) = 0;

	/// \��������ʼ������˷�
	/// \���� deviceID [in] ָ��һ����Ҫ���Ե���˷磬���������һ���������˷�ID, SDK����һ�����󣬷���SDK��ʼ������˷磬��������Ϊ��ѡ��.
	/// ���û�в������룬SDK����Ĭ�ϵ��豸.
	///\ע�⣺���eventû������, �������û������.
	virtual SDKError TestMicStartRecording(const wchar_t* deviceID = NULL) = 0;

	/// \������ֹͣ������˷磬���û����˷����ڲ��ԣ�SDK����error.
	///\ע�⣺���eventû������, �������û������.
	virtual SDKError TestMicStopTesting() = 0;

	/// \���������ź���˷�¼�Ƶ����������û����˷ֲ��ԣ�SDK����һ������.
	///\ע�⣺���eventû������, �������û������.
	virtual SDKError TestMicPlayRecording() = 0;
	
	/// \��������ʼ����������.
	/// \ ���� deviceID [in] ָ��һ�����Ե��豸���������ʱһ�������ID,SDK����һ�����󣬷���SDK����ָ�����豸�������ô��豸Ϊ��ѡ�豸.
	/// ���û�����������SDK������Ĭ�ϵ��豸.
	///\ע�⣺���eventû������, �������û������.
	virtual SDKError TestSpeakerStartPlaying(const wchar_t* deviceID = NULL) = 0;
	
	/// \������֪ͨ���������ԣ����û���������ڲ��ԣ�SDK������һ������
	///\ע�⣺���eventû������, �������û������.
	virtual SDKError TestSpeakerStopPlaying() = 0;
	
	/// \���������������ص��������. 
	/// \������timerInterval [in] SDKĬ��ÿ200ms����һ����˷��������������������������û�����������ʱ����..
	/// ʱ�����ĵ�λʱ���룬���ֵ����1000��С��50��SDK�����Ϊ200
	///\ע�⣺ʹ������ӿڽ�ֹͣ��˷�/���������ԣ�����Ӧ���ڲ���֮ǰ���øýӿ�.
	virtual SDKError SetTimerInterval(unsigned int timerInterval) = 0;
};

/// \�������������ýӿ�
///
class IGeneralSettingContext
{
public:
	/// \�����������Ƿ�ʹ��˫��ģʽ.
	/// \������bEnable [in] ָ��ʹ�ܻ�ʧЧ˫��ģʽ.
	/// \���أ�����������óɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success.�������鿴 SDKError enum.
	virtual SDKError EnableDualScreenMode(bool bEnable) = 0;

	/// \��������ȡ˫��ģʽ������״̬
	/// \���أ�ʹ�ܻ���Ч
	virtual bool IsDualScreenModeEnabled() = 0;

	/// \������������Ļʱ�رջ��aeroģʽ
	/// \���� bTurnoff [in] ָ���رջ�򿪼���ģʽ
	/// \���أ�����������óɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success.�������鿴 SDKError enum.
	///��֧��window 7ϵͳ.
	virtual SDKError TurnOffAeroModeInSharing(bool bTurnoff) = 0;

	/// \��������ȡ��Ļ����ʱ�ļ���ģʽ����״̬
	/// \���أ��򿪻�ر�
	virtual bool IsAeroModeInSharingTurnOff() = 0;

	/// \��������������ʱ�������Ƿ��Զ���Ӧ����.
	/// \������bEnable [in] ָ��ʹ�ܻ�ʧ���Զ���Ӧ.
	/// \���أ�����������óɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success.�������鿴 SDKError enum.
	virtual SDKError EnableAutoFitToWindowWhenViewSharing(bool bEnable) = 0;

	/// \��������ȡ�Ƿ�����Ļ�������Զ���Ӧ����.
	/// \���أ�true ���� false
	virtual bool IsAutoFitToWindowWhenViewSharingEnabled() = 0;

	/// \�����������Ƿ�������ʱ�Զ�����ȫ��
	/// \������bEnable [in] ָ��ʹ�ܻ�ʧ���Զ�ȫ��
	/// \���أ�����������óɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success.�������鿴 SDKError enum.
	virtual SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \��������ȡ�������ʱ�Ƿ��Զ�����ȫ��������
	/// \����: true ���� false
	virtual bool IsAutoFullScreenVideoWhenJoinMeetingEnabled() = 0;

	/// \�����������Ƿ��ڹ���ʱ�Զ�����ȫ��.
	/// \������bEnable [in] ָ��ʧ�ܻ�ʹ���Զ�����ȫ��
	/// \���أ�����������óɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success.�������鿴 SDKError enum.
	virtual SDKError EnableAutoFullScreenVideoWhenViewShare(bool bEnable) = 0;

	/// \��������ȡ�Ƿ��ڹ���ʱ����ȫ��.
	/// \���أ�true ���� false
	virtual bool IsAutoFullScreenVideoWhenViewShareEnabled() = 0;

	/// \����������Ļ����ʱ���Ƿ�ʹ�÷���ģʽ
	/// \������bEnable [in] ָ���Ƿ����ģʽ
	/// \���أ�����������óɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success.�������鿴 SDKError enum.
	virtual SDKError EnableSplitScreenMode(bool bEnable) = 0;

	/// \��������ȡ�Ƿ��Ƿ���ģʽ
	/// \���أ�true �� false
	virtual bool IsSplitScreenModeEnabled() = 0;
	
	/// \���������û��˳�����ʱ�������Ƿ���ʾ��ʾ���ڡ�ע�⣺���������λ�����Ч����ȥ������.
	/// \������bEnable TRUE ָ���ܵ�����ʾ��
	/// \���أ�����������óɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success.�������鿴 SDKError enum.
	virtual SDKError EnableDisplayReminderWindowWhenExit(bool bEnable) = 0;
	
	/// \��������ȡ���û��˳�����ʱ�Ƿ񵯳���ʾ��.
	/// \���أ� TRUE ָ�����Ե���. FALSE ������.
	virtual bool IsDisplayReminderWindowWhenExitEnabled() = 0;
	
	/// \�����������Ƿ���ʾ����ʱ��.
	/// \������bEnable TRUE ��ʾ��ʾ. FALSE ����ʾ.
	/// \���أ�����������óɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success.�������鿴 SDKError enum.
	virtual SDKError EnableShowMyMeetingElapseTime(bool bEnable) = 0;
	
	/// \��������ȡ�Ƿ���ʾ����ʱ��.
	/// \���أ�TRUE ��ʾ. FALSE ����ʾ.
	virtual bool IsShowMyMeetingElapseTimeEnabled() = 0;
	
	/// \���������û�����ʱ����ȡ����ϵͳ�Ƿ�֧��GPU����
	/// \���أ�TRUE ֧��. FALSE ��֧��.
	virtual bool IsCurrentOSSupportAccelerateGPUWhenShare() = 0;
	
	/// \�����������Ƿ�ʹ��GPU���㣨�û�����ʱ��.
	/// \������bEnable TRUE ����ʹ�ܼ���. FALSE ��֧��.
	/// \���أ�����������óɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success.�������鿴 SDKError enum.
	virtual SDKError EnableAccelerateGPUWhenShare(bool bEnable) = 0;	
	
	/// \��������ȡ�Ƿ���ʹ��GPU����
	/// \������[out]bEnable TRUE ��ʾʹ��GPU����. FALSE ��ʾ��ʹ��. ��������ֵΪSDKErr_Successʱ��Ч��
	/// \���أ�����������óɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success.�������鿴 SDKError enum.
	virtual SDKError IsAccelerateGPUWhenShareEnabled(bool& bEnable) = 0;
	
	/// \�����������Ƿ���Զ�̿�������Ӧ��.
	/// \������bEnable TRUE ������Զ�̿��ƣ� FALSE ����.
	/// \���أ�����������óɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success.�������鿴 SDKError enum.
	virtual SDKError EnableRemoteControlAllApplications(bool bEnable) = 0;	
	
	/// \��������ȡ�Ƿ���Զ�̿�������Ӧ��.
	/// \���أ�TRUE ��. FALSE ����.
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

///\������Ԥ����Ƶ����ڵ�ǰ���ڵ���ת�Ƕ�֪ͨ.
typedef enum
{
	PREVIEW_VIDEO_ROTATION_ACTION_0, 			///< ����ת
	PREVIEW_VIDEO_ROTATION_ACTION_CLOCK90,		///< ������ת
	PREVIEW_VIDEO_ROTATION_ACTION_CLOCK180,		///< ��ת.
	PREVIEW_VIDEO_ROTATION_ACTION_ANTI_CLOCK90	///< ������ת.
} PREVIEW_VIDEO_ROTATION_ACTION, *PPREVIEW_VIDEO_ROTATION_ACTION;

/// \��������Ƶ�豸���Իص��¼�
///
class ITestVideoDeviceHelperEvent
{
public:
	/// \������δ�ҵ�����ͷ�豸֪ͨ��
	virtual void OnNoVideoDeviceIsUseful() = 0;
	
	/// \�������û��ڲ����ڼ�ѡ������ͷ�豸��֪ͨ��SDK���ر���Ƶ���ԣ��û���Ҫ���¿�ʼ���ԡ�
	virtual void OnSelectedVideoDeviceIsChanged() = 0; 
	
	/// \������SDK��Ҫһ����������ʾ��ƵԤ���� ���֪ͨ��ʾû�д��ھ������ʹ���˴���Ĵ��ھ����
	virtual void OnNoWindowToShowPreview() = 0;
};

/// \�����������豸���Խӿ�
///
class ITestVideoDeviceHelper
{
public:
	/// \��������Ƶ�豸���Իص��¼���ע�⣺������������ڴ���������ӿڷ���֮ǰ���á�
	/// \������pEvent [in] һ��������Ƶ�豸�����¼���ָ�� ITestVideoDeviceHelperEvent* 
	/// \���أ�����������óɹ�������ֵΪ SDKErr_Success.
	/// �������ʧ�ܣ�����ֵ����SDKErr_Success.�������鿴 SDKError enum.
	virtual SDKError SetEvent(ITestVideoDeviceHelperEvent* pEvent) = 0;
	
	/// \������������ʾԤ����Ƶ�Ĵ��ڼ����ڴ�С 
	/// \������ hParentWnd [in] ָ����ʾԤ���Ĵ���
	/// \������ rc [in] ָ��һ����ʾԤ���ľ��Σ�Ĭ��Ϊ{0��0��0��0}��Ĭ�ϱ�ʾʹ�ÿͻ��˵��������ڴ�С��ʾԤ����Ƶ��
	virtual SDKError SetVideoPreviewParentWnd(HWND hParentWnd, RECT rc = _SDK_TEST_VIDEO_INIT_RECT) = 0;
	
	/// \��������ʼ��������ͷ��
	/// \������ deviceID [in] ָ��һ�����Ե�����ͷ�豸�����������һ�����������ͷID,SDK����һ�����󡣷���SDK�����Ը��豸������������Ϊѡ��״̬��
	/// ���û�����������SDK������Ĭ���豸��.
	/// \ע�⣺ ���û������event,����û�����ô��ھ����������������ܹ�����
	virtual SDKError TestVideoStartPreview(const wchar_t* deviceID = NULL) = 0;
	
	/// \������ ֹͣ��������ͷ��
	/// \ע�⣺���û������event,����û�����ô��ھ����������������ܹ�����
	virtual SDKError TestVideoStopPreview() = 0;
	
	/// \������Ԥ����Ƶ��ת.
	/// \������action [in] ָ����ת��������ϸ�鿴 enum PREVIEW_VIDEO_ROTATION_ACTION��
	/// \ע�⣺���û������event,����û�����ô��ھ����������������ܹ�����
	virtual SDKError TestVideoRotate(PREVIEW_VIDEO_ROTATION_ACTION action) = 0;	

	virtual ICameraController* GetTestCameraController() = 0;
};

/// \��������Ƶ�������ݻص��¼���
class IVideoSettingContextEvent
{
public:
	/// \������ ���sdk��⵽�����������豸�Ļص�
	/// \������ pNewCameraList ���²�������������ͷ�豸. 
	virtual void onComputerCamDeviceChanged(std::vector<ICameraInfo*> pNewCameraList) = 0;

	/// \������ ֪ͨ�û���һ������ͷ�豸��ѡ��
	/// \������ deviceId ��ѡ����豸
	/// \������ deviceName ��ѡ���豸���豸��
	virtual void onDefaultCamDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) = 0;
};
/// \��������Ƶ���ýӿڡ�
///
class IVideoSettingContext
{
public:
	/// \��������ȡ����ͷ�豸�б�
	/// \���أ�����������óɹ�������ֵ������ͷ�б�ָ��
	/// �����������ʧ�ܣ�����ֵ��NULL
	virtual std::vector<ICameraInfo* > GetCameraList() = 0;

	/// \������ѡ������ͷ�豸��
	/// \������[in] deviceId ��ѡ���豸���豸ID
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError SelectCamera(const wchar_t* deviceId) = 0;

	/// \����������/������Ƶ����Ч��
	/// \param [in] bEnable ����/������Ƶ����Ч��
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableVideoMirrorEffect(bool bEnable) = 0;

	/// \��������ȡ����/������Ƶ����Ч��
	/// \���أ�����/����
	virtual bool IsVideoMirrorEffectEnabled() = 0;

	/// \��������������/��������Ч��
	/// \������[in] bEnable ����/��������Ч��
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableFaceBeautyEffect(bool bEnable) = 0;

	/// \��������ȡ����/��������Ч��
	/// \���أ�����/����.
	virtual bool IsFaceBeautyEffectEnabled() = 0;

	/// \��������������/���ø�����Ƶ
	/// \������[in] bEnable ָ���������ֹʹ�ø�����Ƶ
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableHDVideo(bool bEnable) = 0;

	/// \��������ȡ�Ƿ�����/���ø�����Ƶ
	/// \���أ�����/����.
	virtual bool IsHDVideoEnabled() = 0;

	// \��������������/��������Ƶ����ʾ����
	/// \param [in] bEnable ����/��������Ƶ����ʾ����
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableAlwaysShowNameOnVideo(bool bEnable) = 0;

	/// \��������ȡ����/��������Ƶ����ʾ����
	/// \���أ�����/����.
	virtual bool IsAlwaysShowNameOnVideoEnabled() = 0;

	/// \�����������Ƿ��ڼ������ʱ�ر���Ƶ
	/// \������[in] bEnable �Ƿ��ڼ������ʱ�ر���Ƶ
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \��������ȡ�Ƿ��ڼ������ʱ�ر���Ƶ
	/// \���أ�Enable or disable.
	virtual bool IsAutoTurnOffVideoWhenJoinMeetingEnabled() = 0;
	
	/// \�����������Ƿ�ʹ��16:9��Ƶģʽ
	/// \������bEnable [in] �Ƿ�ʹ��16:9��Ƶģʽ
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableAlwaysUse16v9(bool bEnable) = 0;

	/// \��������ȡ�Ƿ�ʹ��16:9��Ƶģʽ
	/// \���أ���/��.
	virtual bool IsAlwaysUse16v9() = 0;

	/// \��������������/������Ƶ�۹��.
	/// \������bEnable [in] ����/������Ƶ�۹��.
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableSpotlightSelf(bool bEnable) = 0;

	/// \��������ȡ����/������Ƶ�۹��.
	/// \���أ���/��
	virtual bool IsSpotlightSelfEnabled() = 0;

	/// \�����������Ƿ�ʹ��Ӳ������
	/// \������bEnable [in] �Ƿ�ʹ��Ӳ������
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableHardwareEncode(bool bEnable) = 0;

	/// \��������ȡ�Ƿ�ʹ��Ӳ������
	/// \���أ���/��.
	virtual bool IsHardwareEncodeEnabled() = 0;

	/// \�������������û�����ڻ�����ͼ��ÿ����Ļ�����ʾ49��������.
	/// \������bEnable [in] ���û�����ڻ�����ͼ��ÿ����Ļ�����ʾ49��������.
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError Enable49VideoesInGallaryView(bool bEnable) = 0;

	/// \��������ȡ���û�����ڻ�����ͼ��ÿ����Ļ�����ʾ49��������
	/// \���أ�����/����.
	virtual bool Is49VideoesInGallaryViewEnabled() = 0;

	/// \�����������Ƿ�����û����Ƶ�Ĳλ���.
	/// \������bEnable [in] �Ƿ�����û����Ƶ�Ĳλ���.
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableHideNoVideoUsersOnWallView(bool bEnable) = 0;

	/// \��������ȡ�Ƿ�����û����Ƶ�Ĳλ���״̬.
	/// \���أ���/��.
	virtual bool IsHideNoVideoUsersOnWallViewEnabled() = 0;

	/// \��������ȡ������������ͷ�豸��ָ��ITestVideoDeviceHelper�����ָ��
	/// \���أ�����ɹ�������ָ��ITestVideoDeviceHelper��ָ��.
	/// ���ʧ�ܣ�����NULL.
	/// ������ϸ��Ϣ�鿴ITestVideoDeviceHelper.
	virtual ITestVideoDeviceHelper* GetTestVideoDeviceHelper() = 0;

	/// \��������Ƶ���ü��ӻص��¼�. 
	/// \������pEvent һ��ָ��IVideoSettingContextEvent�����ָ��. 
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	/// ������ϸ��Ϣ�鿴IVideoSettingContextEvent.
	/// \ע�⣺���������²������Ƶ�豸��������ø÷���.
	virtual SDKError SetVideoDeviceEvent(IVideoSettingContextEvent* pEvent) = 0;
};

/// \��������Ƶ���ûص��¼�
///
class IAudioSettingContextEvent
{
public:
	/// \������ SDK��⵽�������˷��豸�仯ʱ�Ļص��¼�.
	/// \������ pNewMicList �²�����������˷��豸�б�. 
	virtual void onComputerMicDeviceChanged(std::vector<IMicInfo*> pNewMicList) = 0;
	
	/// \������ SDK��⵽������������豸�仯ʱ�Ļص��¼�.
	/// \������ pNewSpeakerList �²����������������豸�б�. 
	virtual void onComputerSpeakerDeviceChanged(std::vector<ISpeakerInfo*> pNewSpeakerList) = 0;

	/// \������ һ����˷��豸��ѡ���֪ͨ�¼�.
	/// \������ deviceId ָ��һ���豸��ѡ��.
	/// \������ deviceName ָ����ѡ�������.
	virtual void onDefaultMicDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \������ һ���������豸��ѡ���֪ͨ�¼�.
	/// \������ deviceId ָ��һ���豸��ѡ��.
	/// \������ deviceName ָ����ѡ�������.
	virtual void onDefaultSpeakerDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) = 0;
};

/// \��������Ƶ���ýӿ�
///
class IAudioSettingContext
{
public:
	/// \��������ȡ��˷��豸�б�
	/// \���أ�����������óɹ�������ֵ����Ƶ�豸ָ���б�
	/// �����������ʧ�ܣ�����ֵ��NULL
	virtual std::vector<IMicInfo* > GetMicList() = 0;

	/// \������ѡ����˷�����
	/// \������deviceId [in] ָ����ѡ�豸
	/// \������deviceName [in] ָ�������豸��Ӧ�ú�ָ�����豸Id��ͬ
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError SelectMic(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \������Get speaker device list
	/// \���أ�����������óɹ�������ֵ���������豸ָ���б�
	/// ���ʧ�ܣ�����ֵ��NULL If the function fails, the return value is NULL.
	virtual std::vector<ISpeakerInfo* > GetSpeakerList() = 0;

	/// \������ѡ���������豸
	/// \������deviceId [in] ��ѡ�豸.
	/// \������deviceName [in] ��ѡ�豸���֣�Ӧ�ú�ָ�����豸Id��ͬ
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError SelectSpeaker(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \�����������Ƿ����������Զ�����Ƶ
	/// \������bEnable [in] �Ƿ��Զ�����Ƶ.
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableAutoJoinAudio(bool bEnable) = 0;

	/// \��������ȡ�������ʱ�Ƿ��Զ�����Ƶ��״̬
	/// \���أ��ǻ��
	virtual bool IsAutoJoinAudioEnabled() = 0;

	/// \�����������Ƿ��Զ�������˷�����.
	/// \������bEnable [in] �Ƿ��Զ�������˷�����
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableAutoAdjustMic(bool bEnable) = 0;

	/// \��������ȡ�Ƿ����Զ�������˷�����
	/// \���أ��Ƿ�
	virtual bool IsAutoAdjustMicEnabled() = 0;

	/// \������ �����Ƿ��������
	/// \������ bEnable [in] ָ���Ƿ��������
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableStereoAudio(bool bEnable) = 0;

	/// \��������ȡ�Ƿ񷢴�������
	/// \���أ��Ƿ�
	virtual bool IsStereoAudioEnable() = 0;

	/// \�����������Ƿ�ʹ����˷�ԭʼ����
	/// \������bEnable [in] ָ���Ƿ�ʹ��ԭʼ����
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableMicOriginalInput(bool bEnable) = 0;

	/// \��������ȡ�Ƿ�ʹ����˷�ԭʼ����״̬
	/// \���أ��Ƿ�
	virtual bool IsMicOriginalInputEnable() = 0;
	
 	/// \�����������Ƿ�ʹ�ð��¿ո��˵��
	/// \������bEnable [in] �Ƿ��¿ո��˵��
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableHoldSpaceKeyToSpeak(bool bEnable) = 0;

	/// \��������ȡ�Ƿ�ʹ�ð��¿ո��˵��
	/// \���أ��ǻ��
	virtual bool IsHoldSpaceKeyToSpeakEnabled() = 0;

	/// \���������ü���voip����ʱ���Ǿ���
	/// \������bEnable [in] �Ƿ����Ǿ�������
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableAlwaysMuteMicWhenJoinVoip(bool bEnable) = 0;

	/// \��������ȡ�Ƿ�������voip����
	/// \���أ��Ƿ�
	virtual bool IsAlwaysMuteMicWhenJoinVoipEnabled() = 0;

	/// \�����������Ƿ��������Ƶ����ʱ��ʾ
	/// \������bEnable TRUE ��ʾ��ʾ
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableSuppressAudioNotify(bool bEnable) = 0;

	/// \��������ȡ����������Ƶ����ʱ�Ƿ���ʾ��״̬
	/// \���أ��ǻ��
	virtual bool IsSuppressAudioNotifyEnabled() = 0;

	/// \��������ȡ������Ƶ�豸�����ָ��ITestAudioDeviceHelper*
	/// \���أ�����������óɹ�������ָ��ITestAudioDeviceHelper��ָ��
	/// ���ʧ�ܣ�����NULL
	/// ��ȡ������Ϣ���鿴 ITestAudioDeviceHelper.
	virtual ITestAudioDeviceHelper* GetTestAudioDeviceHelper() = 0;
	
	/// \����������ѡ����˷������
	/// \������value [in] ����. ֵ�� 0 �� 255
	/// ���û����˷类ѡ��SDK��ʹ��Ĭ����˷�
	virtual SDKError	SetMicVol(FLOAT& value) = 0;
	
	/// \��������ȡ��˷�����
	/// \param value [out] ��˷�����ֵ
	virtual SDKError    GetMicVol(FLOAT& value) = 0;
	
	/// \����������ѡ��������������
	/// \������value [in]ָ��������������.ֵ��0��255
	/// ���û������������SDK��ʹ��Ĭ��������
	virtual SDKError	SetSpeakerVol(FLOAT& value) = 0;
	
	/// \��������ȡѡ��������������
	/// \������value [out] ������������
	virtual SDKError    GetSpeakerVol(FLOAT& value) = 0;

	/// \������������Ƶ�豸���ӻص��¼�
	/// \������pEvent һ��ָ�������Ƶ�豸�¼���ָ�� IAudioSettingContextEvent*
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	/// ��ϸ�鿴 IAudioSettingContextEvent
	/// \ע�⣺����������Ƶ�豸�İβ壬������ø÷���
	virtual SDKError SetAudioDeviceEvent(IAudioSettingContextEvent* pEvent) = 0;

	/// \�����������Ƿ�ʹ����������
	/// \������bEnable True ����������, FALSE ����.
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableEchoCancellation(bool bEnable) = 0;
	
	/// \��������ȡ�Ƿ���������
	/// \���أ������TRUE, ��ζ������������
	virtual bool IsEchoCancellationEnabled() = 0;
	

};

class IRecordingSettingContextEvent
{
public:
	/// \��������ǰ��¼�ƴ洢��Ϣ֪ͨ
	/// \�������洢�ܴ�С
	/// \�������洢��ʹ�ô�С
	/// \��������������С
	virtual void onCloudRecordingStorageInfo(INT64 storage_total_size, INT64 storage_used_size, bool allow_exceed_storage) = 0;
};

/// \������¼�����ýӿ�
///
class IRecordingSettingContext
{
public:
	/// \���������������ô����е�¼��·��
	/// \������szPath[in] ָ��¼��·��
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError SetRecordingPath(const wchar_t* szPath) = 0;

	/// \��������ȡ���ô����е�¼��·��
	/// \���أ�¼��·��
	virtual const wchar_t* GetRecordingPath() = 0;
	
	/// \����������¼������event
	/// \������pEvent ¼������event
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError SetRecordingSettingEvent(IRecordingSettingContextEvent* pEvent) = 0;
	
	/// \����������Ƿ��û��л�ȡ��¼����Ϣ��Ȩ��
	/// \���أ�TRUE ��ʾ�û���Ȩ��. FALSE ��ʾûȨ��.
	virtual bool CanGetCloudRecordingStorageInfo() = 0;

	/// \��������ȡ��¼����Ϣ
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	/// �������ֵ��SDKErr_Success, ȡ����Ϣ��IRecordingSettingContextEvent.onCloudRecordingStorageInfo()
	virtual SDKError GetCloudRecordingStorageInfo() = 0;

	/// \��������ȡ¼�ƹ���URL Get the recording management URL.
	/// \���� TRUE ��ʾ���� FALSE ��ʾ����.
	virtual const wchar_t* GetRecordingManagementURL() = 0;
	
	/// \�����������Ƿ��ܻ�ȡ��¼�ƹ���URL
	/// \������[out]bEnable TRUE ��ζ��¼�ƹ���URL�ܱ���ȡ����FALSE��ʾ����. ����������ֵ��SDKErr_Suucessʱ����Ч
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError CanGetRecordingManagementURL(bool& bEnable) = 0;
	
	/// \������ �����Ƿ����ڻ��������ѡ��¼���ļ�����λ��
	/// \���� bEnable TRUE ��ʾ��, FALSE ����.
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableSelectRecordFileLocationAfterMeeting(bool bEnable) = 0;
	
	/// \��������ȡ�Ƿ����ڻ��������ѡ��¼���ļ��ı���λ�� Check if the function of selecting storage path for recording file is enabled.
	/// \���أ�TRUE ��ʾ��. FALSE ��ʾ����.
	virtual bool IsSelectRecordFileLocationAfterMeetingEnabled() = 0;
	
	/// \�����������Ƿ�����·��Ƶ¼��
	/// \������bEnable TRUE ��ʾ����. FALSE ������.
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableMultiAudioStreamRecord(bool bEnable) = 0;
	
	/// \��������ȡ�Ƿ���ʹ�ö�·��Ƶ¼��
	/// \���أ�TRUE ��ʾ��. FALSE ��.
	virtual bool IsMultiAudioStreamRecordEnabled() = 0;
	
	/// \�����������Ƿ�ʹ��ʱ���ˮӡ
	/// \������ bEnable TRUE ��ʾʹ��. FALSE ��ʾ��ʹ��.
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableAddTimestampWatermark(bool bEnable) = 0;
	
	/// \��������ȡ�Ƿ�ʹ��ʱ���ˮӡ
	/// \���أ�TRUE ���� ʹ��. FALSE ��ʹ��.
	virtual bool IsAddTimestampWatermarkEnabled() = 0;
	
	/// \����������ʹ��/���õ�������Ƶ�༭�����Ż� 
	/// \������bEnable TRUE ��ʾʹ��. FALSE ��ʹ��.
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableOptimizeFor3rdPartyVideoEditor(bool bEnable) = 0;
	
	/// \��������ȡʹ��/���õ�������Ƶ�༭�����Ż�
	/// \���أ�TRUE ʹ��. FALSE ����.
	virtual bool IsOptimizeFor3rdPartyVideoEditorEnabled() = 0;
	
	/// \������ ��������/�����ڹ���ʱ��ʾ��Ƶ����ͼ .
	/// \������bEnable TRUE ����. FALSE ����.
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnableShowVideoThumbnailWhenShare(bool bEnable) = 0;
	
	/// \��������ȡ����/�����ڹ���ʱ��ʾ��Ƶ����ͼ
	/// \���أ�TRUE ����. FALSE ����.
	virtual bool IsShowVideoThumbnailWhenShareEnabled() = 0;
	
	/// \��������������/���ý���Ƶ���ַ����ڼ�¼�еĹ��������Ա� 
	/// \������bEnable TRUE ����. FALSE ����.
	/// \���أ�����������óɹ��� ����ֵ�� SDKErr_Success.
	/// �����������ʧ�ܣ�����ֵ������������Ϣ������鿴SDKError enum.
	virtual SDKError EnablePlaceVideoNextToShareInRecord(bool bEnable) = 0;
	
	/// \��������ȡ����/���ý���Ƶ���ַ����ڼ�¼�еĹ��������Ա� 
	/// \���أ�TRUE ����. FALSE ����..
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


/// \������ͳ�����ýӿ�
///
class IStatisticSettingContext
{
public:
	/// \������ ��ѯͳ����Ϣ
	/// \param info_ [out] ͳ����Ϣ���,����鿴 OverallStatisticInfo
	/// �������óɹ�����SDkErr_Success, �������ʧ�ܣ�����ֵ������������Ϣ������鿴 SDKError enum.
	virtual SDKError QueryOverallStatisticInfo(OverallStatisticInfo& info_) = 0;

	/// \������ ��ѯ��Ƶ��Ϣ
	/// \param info_ [out] ��Ƶ��Ϣ���,����鿴 AudioSessionStatisticInfo
	/// �������óɹ�����SDkErr_Success, �������ʧ�ܣ�����ֵ������������Ϣ������鿴 SDKError enum.
	virtual SDKError QueryAudioStatisticInfo(AudioSessionStatisticInfo& info_) = 0;

	/// \��������ѯ��Ƶ��Ϣ
	/// \param info_ [out] ��Ƶ��Ϣ���,����鿴 ASVSessionStatisticInfo
	/// �������óɹ�����SDkErr_Success, �������ʧ�ܣ�����ֵ������������Ϣ������鿴 SDKError enum.
	virtual SDKError QueryVideoStatisticInfo(ASVSessionStatisticInfo& info_) = 0;

	/// \��������ѯ������Ϣ
	/// \param info_ [out] ������Ϣ���,����鿴 ASVSessionStatisticInfo
	/// �������óɹ�����SDkErr_Success, �������ʧ�ܣ�����ֵ������������Ϣ������鿴 SDKError enum.
	virtual SDKError QueryShareStatisticInfo(ASVSessionStatisticInfo& info_) = 0;
};

/// \�������������ýӿ�
///
class IAccessibilitySettingContext
{
public:
	/// \�������Ƿ������ڻ��鴰������ʾ�����������
	/// \������bEnable TRUE ��ʾ��ʾ��FALSE ��ʾ����ʾ��
	/// \���أ�����������óɹ��� ����ֵ��SDKErr_Success.
	/// ���ʧ�ܣ����ش�����Ϣ������鿴SDKError enum.
	virtual SDKError EnableAlwaysShowMeetingControls(bool bEnable) = 0;

	/// \��������ȡ��ǰ�ڻ��鴰��������ʾ�����������״̬��
	/// \������bEnable TRUE ��ʾ��ʾ�� FALSE ��ʾ����ʾ
	/// \���أ����������ʾ������true
	virtual SDKError IsAlwaysShowMeetingControlsEnable(bool& bEnable) = 0;
};

/// \�����������û����Խӿ�
///
class ISettingUIStrategy
{
public:
	/// \�������ڳ������ñ�ǩ����ʾ�߼�������
	/// \������bDisable [in] ������ʾ����ʾ��
	virtual void DisableAdvancedFeatures4GeneralSetting(bool bDisable) = 0;

	/// \����������ʾ�˻����ñ�ǩ��
	/// \������bDisable [in] ����ʾ����ʾ��
	virtual void DisableAccountSettingTabPage(bool bDisable) = 0;

	/// \�������Զ����ǩҳ����ʾ������
	/// \������showOption True ��ʾ��ʾ��Ӧ�ı�ǩҳ��
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

/// \�������������ýӿ�
///
class ISettingService
{
public:

	/// \��������ʾ�������ô���
	/// \������[in] param ָ����ʾ���촰��
	/// ����������óɹ�������ֵ��SDKErr_Success,���ʧ�ܷ���ֵ���� SDKErr_Success��
	/// ��ȡ��ϸ�����������Ϣ�鿴 SDKError enum.
	virtual SDKError ShowSettingDlg(ShowSettingDlgParam& param) = 0;

	/// \���������ػ������ô���
	/// ����������óɹ�������ֵ��SDKErr_Success,���ʧ�ܷ���ֵ���� SDKErr_Success��
	/// ��ȡ��ϸ�����������Ϣ�鿴 SDKError enum.
	virtual SDKError HideSettingDlg() = 0;

	/// \��������ȡ�������ýӿ�
	/// \���أ�������ܵ��óɹ��� ����һ��ָ��IGeneralSettingContext�����ָ�롣
	/// ���ʧ�ܣ�����NULL��
	/// ��ȡ������ϸ���ܣ��鿴 IGeneralSettingContext
	virtual IGeneralSettingContext* GetGeneralSettings() = 0;

	/// \��������ȡ��Ƶ���ýӿ�
	/// \���أ�������ܵ��óɹ��� ����һ��ָ��IAudioSettingContext�����ָ�롣
	/// ���ʧ�ܣ�����NULL��
	/// ��ȡ������ϸ���ܣ��鿴 IAudioSettingContext
	virtual IAudioSettingContext* GetAudioSettings() = 0;

	/// \��������ȡ��Ƶ���ýӿ�
	/// \���أ�������ܵ��óɹ��� ����һ��ָ��IVideoSettingContext�����ָ�롣
	/// ���ʧ�ܣ�����NULL��
	/// ��ȡ������ϸ���ܣ��鿴 IVideoSettingContext
	virtual IVideoSettingContext* GetVideoSettings() = 0;

	/// \��������ȡ¼�����ýӿ�
	/// \���أ�������ܵ��óɹ��� ����һ��ָ��IRecordingSettingContext�����ָ�롣
	/// ���ʧ�ܣ�����NULL��
	/// ��ȡ������ϸ���ܣ��鿴 IRecordingSettingContext
	virtual IRecordingSettingContext* GetRecordingSettings() = 0;

	/// \��������ȡͳ�����ýӿ�
	/// \���أ�������ܵ��óɹ��� ����һ��ָ��IStatisticSettingContext�����ָ�롣
	/// ���ʧ�ܣ�����NULL��
	/// ��ȡ������ϸ���ܣ��鿴 IStatisticSettingContext
	virtual IStatisticSettingContext* GetStatisticSettings() = 0;

	/// \��������ȡ�������ýӿ�
	/// \���أ�����������óɹ�,����һ��ָ��IAccessibilitySettingContext�����ָ�롣
	///	���ʧ�ܣ�����NULL��
	/// ��ȡ������ϸ���ܣ��鿴 IAccessibilitySettingContext.
	virtual IAccessibilitySettingContext* GetAccessibilitySettings() = 0;

	/// \��������ȡ�û����ò��Խӿ�
	/// \���أ�����������óɹ��� ����һ��ָ��ISettingUIStrategy�����ָ��
	///	���ʧ�ܣ� ����NULL��
	/// ��ȡ������ϸ���ܣ��鿴ISettingUIStrategy.
	virtual ISettingUIStrategy* GetSettingUIStrategy() = 0;

	/// \brief Get virtual background interface.
	/// \return If the function succeeds, the return value is an object pointer to IVirtualBGSettingContext.
	///Otherwise failed, returns NULL.
	///For more details, see \link IVirtualBGSettingContext \endlink.
	virtual IVirtualBGSettingContext* GetVirtualBGSettings() = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif