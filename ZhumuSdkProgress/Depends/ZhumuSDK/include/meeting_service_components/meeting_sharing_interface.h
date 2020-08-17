/*!
* \文件：meeting_sharing_interface.h
* \描述：会议共享服务接口
*
*/
#ifndef ZHUMU_MEETING_SHARING_INTERFACE_H_
#define ZHUMU_MEETING_SHARING_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include <vector>
/// \描述： Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum SharingStatus
\描述：共享状态。
更详细的结构描述
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
\描述：可查看的共享源信息。
更详细的结构描述
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

/*! \enum 当前共享的类型.
更详细的结构描述
*/
enum ShareType
{
	SHARE_TYPE_UNKNOWN, //未知
	SHARE_TYPE_AS,	//共享应用
	SHARE_TYPE_DS,	//共享桌面
	SHARE_TYPE_WB,	//白板共享
	SHARE_TYPE_AIRHOST,	//PC上共享手机设备
	SHARE_TYPE_CAMERA,	//摄像头共享
	SHARE_TYPE_DATA,	//数据共享
};
/*! \enum AdvanceShareOption
当前发送给他人的共享其他类型。
这里有更详细的结构描述。
*/
enum AdvanceShareOption
{
	AdvanceShareOption_ShareFrame,///<共享桌面选定区域
	AdvanceShareOption_PureComputerAudio,///<只共享计算机音频。
	AdvanceShareOption_ShareCamera,///<共享摄像头
};
/*! \struct tagShareInfo
\描述：当前共享的信息。
更详细的结构描述.
*/
enum MultiShareOption
{
	Enable_Multi_Share = 0, ///<多个参与者可以同时共享。
	Enable_Only_HOST_Start_Share, ///<一次只能由主机共享。
	Enable_Only_HOST_Grab_Share, ///<一个参与者可以一次分享，分享过程中只有主机可以开始新的分享，之前的分享将被取代。
	Enable_All_Grab_Share, ///<一个参与者可以一次分享，在分享的过程中，每个人都可以开始一个新的分享，之前的分享将被取代。
};

typedef struct tagShareInfo
{
	ShareType eShareType;  //共享类型，参考ShareType
	union
	{
		HWND hwndSharedApp;  //共享应用程序或白板的句柄，仅当eShareType为SHARE_TYPE_AS或SHARE_TYPE_WB时有效
		const wchar_t* monitorID;  //共享桌面的显示器id，只有当eShareType为SHARE_TYPE_DS时才有效
	}ut;
	tagShareInfo()
	{
		eShareType = SHARE_TYPE_UNKNOWN;
		memset(&ut, 0, sizeof(ut));
	}
}ShareInfo;

/// \描述：提醒处理程序从多个共享切换到单个共享。
///
class IShareSwitchMultiToSingleConfirmHandler
{
public:
	/// \描述：取消从多共享切换为单共享。所有分享将保留。
	virtual SDKError Cancel() = 0;

	/// \描述：将多共享切换为单共享。所有分享将保留。
	virtual SDKError Confirm() = 0;

	virtual ~IShareSwitchMultiToSingleConfirmHandler() {};
};

/// \描述：会议共享控制器的回调事件。
///
class IMeetingShareCtrlEvent
{
public:
	/// \描述：共享状态通知回调
	/// \参数：status 共享状态值。
	/// \参数：userId 共享用户id
	virtual void onSharingStatus(SharingStatus status, unsigned int userId) = 0;

	/// \描述：锁定共享状态通知回叫
	/// \参数：bLocked 指定共享是否被锁定。
	virtual void onLockShareStatus(bool bLocked) = 0;

	/// \描述：更改共享信息的回调事件。
	/// \参数：shareInfo 共享信息。有关详细信息，请参见 ShareInfo 结构。
	virtual void onShareContentNotification(ShareInfo& shareInfo) = 0;

	/// \描述：将多个参与者共享切换到一个参与者共享的回调事件。
	/// \参数：handler_ An 用户用来完成所有相关操作的对象指针。有关更多细节，请参见IShareSwitchMultiToSingleConfirmHandler。
	virtual void onMultiShareSwitchToSingleShareNeedConfirm(IShareSwitchMultiToSingleConfirmHandler* handler_) = 0;
};

/// \描述：会议共享控制器接口
///
class IMeetingShareController
{
public:
	/// \描述：设置会议共享控制器回调事件
	/// \描述：pEvent 一个指向接收共享事件的IMeetingShareCtrlEvent*的指针。
	/// \返回: 如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(IMeetingShareCtrlEvent* pEvent) = 0;

	/// \描述：启动应用程序共享
	/// \描述：hwndSharedApp 指定要共享哪个窗口。
	/// 如果hwndSharedApp不能共享，返回SDKERR_INVALID_BRIEF:ETER错误代码。如果hwndSharedApp为空，将显示选择应用程序对话框。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError StartAppShare(HWND hwndSharedApp) = 0;

	/// \描述：开始桌面共享
	/// \描述： monitorID ：指定要共享哪个显示器。使用EnumDisplayMonitors系统api来获取这个值。
	/// 请参考MONITORINFOEX结构中的szDevice。如果monitorID为空，将显示选择应用程序对话框。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError StartMonitorShare(const wchar_t* monitorID) = 0;

	/// \描述：开始IOS设备共享。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError StartAirPlayShare() = 0;

	/// \描述：开始白板共享。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	/// 如果您在自定义模式下使用我们的sdk，请在使用SHARE_TYPE_WB获得onShareContentNotification时绘制自己的注释栏
	virtual SDKError StartWhiteBoardShare() = 0;

	/// \描述：显示分享应用选择窗口。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅支持zhumu风格的UI
	virtual SDKError ShowSharingAppSelectWnd() = 0;

	/// \描述： Determine if the specified ADVANCE SHARE OPTION is supported. 
	/// \描述： option_ The ADVANCE SHARE OPTION to be determined. For more information, see \link AdvanceShareOption \endlink enum.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError IsSupportAdvanceShareOption(AdvanceShareOption option_) = 0;

	/// \描述：开始共享窗口。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError StartShareFrame() = 0;

	/// \描述：仅开始共享计算机音频。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError StartSharePureComputerAudio() = 0;

	/// \描述：开始分享相机。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError StartShareCamera() = 0;

	/// \描述：停止当前共享。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError StopShare() = 0;

	/// \描述： 屏幕共享中阻止窗口共享
	/// 这个api将改变窗口的属性。我们不建议使用。
	/// 调用此api后，需要重新绘制此窗口才能生效。
	/// \描述： bBlock 从屏幕共享阻止窗口。.
	/// \描述： hWnd 指定要阻塞哪个窗口。.
	/// \描述： bChangeWindowStyle 如果为false，请在StartMonitorShare api之后调用此api
	/// 或者在你用Sharing_Self_Send_Begin获得sharingstatus回调之后。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅支持zhumu风格的UI
	virtual SDKError BlockWindowFromScreenshare(bool bBlock, HWND hWnd, bool bChangeWindowStyle = true) = 0;

	/// \描述：锁定当前会议的共享
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError LockShare() = 0;

	/// \描述：解锁当前会议的共享
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError UnlockShare() = 0;

	/// \描述：在视图共享时，将共享视图窗口切换为适合窗口模式。
	/// \描述：type 指定要设置的视图，第一个监视器还是第二个监视器。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅支持zhumu风格的UI
	virtual SDKError SwitchToFitWindowModeWhenViewShare(SDKViewType type) = 0;

	/// \描述：在视图共享时，将共享视图窗口切换到原始大小模式。
	/// \描述：type 指定要设置的视图，第一个监视器还是第二个监视器。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅支持zhumu风格的UI
	virtual SDKError SwitchToOriginalSizeModeWhenViewShare(SDKViewType type) = 0;

	/// \描述：暂停当前的分享
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError PauseCurrentSharing() = 0;

	/// \描述：重新当前共享
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError ResumeCurrentSharing() = 0;

	/// \描述：获取当前可见的共享源列表。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual std::vector<unsigned int> GetViewableShareSourceList() = 0;

	/// \描述：通过userid获取可查看的共享源。
	/// \描述：userid 指定要获取的可查看共享源信息。
	/// \描述：shareSource 存储可查看的共享源信息
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError GetViewabltShareSourceByUserID(unsigned int userid, ViewableShareSource& shareSource) = 0;

	/// \描述：通过userid共享视图。
	/// \描述：userid 指定要查看的对象。
	/// \描述：type 指定要查看共享的哪个视图，第一个监视器还是第二个监视器。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅支持zhumu风格的UI
	virtual SDKError ViewShare(unsigned int userid, SDKViewType type) = 0;

	/// \描述：显示共享操作对话框.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅支持zhumu风格的UI
	virtual SDKError ShowShareOptionDialog() = 0;

	/// \描述：判断是否可以开启共享
	/// \返回：是否可以开启共享
	/// \支持zhumu风格和自定义UI风格
	virtual bool CanStartShare() = 0;

	/// \描述：查询共享是否被锁定。
	/// \描述：bLocked 存储共享时候被锁定
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError IsShareLocked(bool& bLocked) = 0;

	/// \描述：查询共享支持共享计算机声音与否。
	/// \描述：bCurEnableOrNot 存储共享是否支持共享计算机声音
	/// \返回：支持共享计算机声音与否
	/// \支持zhumu风格和自定义UI风格
	virtual bool IsSupportEnableShareComputerSound(bool& bCurEnableOrNot) = 0;

	/// \描述：查询共享是否支持优化全屏视频剪辑。
	/// \描述：bCurEnableOrNot 是否支持优化全屏视频剪辑.
	/// \返回：是否支持优化全屏视频剪辑.
	/// \支持zhumu风格和自定义UI风格
	virtual bool IsSupportEnableOptimizeForFullScreenVideoClip(bool& bCurEnableOrNot) = 0;

	/// \描述：启用共享计算机声音.
	/// \描述：bEnable 是否启用.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError EnableShareComputerSound(bool bEnable) = 0;

	/// \描述：启用优化全屏视频剪辑。
	/// \描述：bEnable 是否启用.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \支持zhumu风格和自定义UI风格
	virtual SDKError EnableOptimizeForFullScreenVideoClip(bool bEnable) = 0;

	/// \描述：设置多参与者共享选项
	/// \描述：shareOption 查看 MultiShareOption enum.
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
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