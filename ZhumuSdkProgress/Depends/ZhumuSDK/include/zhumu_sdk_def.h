/*!
* \文件： zhumu_sdk_def.h
* \描述： Zhumu Windows SDK 公共参数定义
* 
*/
#ifndef _ZHUMU_SDK_DEF_H_
#define _ZHUMU_SDK_DEF_H_
#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <string>

#define PLATFORM_IMPORT	__declspec(dllimport)  
#define PLATFORM_EXPORT	__declspec(dllexport)
#ifdef ZHUMU_SDK_DLL_EXPORT
#define ZHUMU_SDK_API PLATFORM_EXPORT
#elif defined ZHUMU_SDK_DLL_IMPORT
#define ZHUMU_SDK_API PLATFORM_IMPORT
#else
#define ZHUMU_SDK_API
#endif

#define ZHUMU_SDK_NAMESPACE ZhumuSDK
#define BEGIN_ZHUMU_SDK_NAMESPACE namespace ZHUMU_SDK_NAMESPACE {
#define END_ZHUMU_SDK_NAMESPACE };
#define USING_ZHUMU_SDK_NAMESPACE using namespace ZHUMU_SDK_NAMESPACE;

/// \brief Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum SDKError
	\描述 初始化 SDK 使用参数
	及详细的结构体描述.
*/ 
enum SDKError
{
	SDKERR_SUCCESS = 0,///<成功.
	SDKERR_NO_IMPL,///<此功能当前无效. 
	SDKERR_WRONG_USEAGE,///<错误使用功能. 
	SDKERR_INVALID_PARAMETER,///<参数错误.
	SDKERR_MODULE_LOAD_FAILED,///<加载模块失败.
	SDKERR_MEMORY_FAILED,///<内存未申请. 
	SDKERR_SERVICE_FAILED,///<内部服务错误.
	SDKERR_UNINITIALIZE,///<使用前未初始化.
	SDKERR_UNAUTHENTICATION,///<使用前未认证.
	SDKERR_NORECORDINGINPROCESS,///<未录制.
	SDKERR_TRANSCODER_NOFOUND,///<转码模块未找到.
	SDKERR_VIDEO_NOTREADY,///<视频服务模块未就绪.
	SDKERR_NO_PERMISSION,///<无权限.
	SDKERR_UNKNOWN,///<未知错误.
	SDKERR_OTHER_SDK_INSTANCE_RUNNING,///<另外的SDK实例正在运行.
	SDKERR_INTELNAL_ERROR,///<SDK内部错误.
	SDKERR_NO_AUDIODEVICE_ISFOUND,///<未发现音频设备.
	SDKERR_NO_VIDEODEVICE_ISFOUND,///<未发现视频设备.
	SDKERR_TOO_FREQUENT_CALL,///<API调用太频繁.
	SDKERR_FAIL_ASSIGN_USER_PRIVILEGE, ///<无法为用户分配新的权限.
	SDKERR_MEETING_DONT_SUPPORT_FEATURE,///<当前会议不支持给特性.
	SDKERR_MEETING_NOT_SHARE_SENDER,///<当前用户不是演示者.
	SDKERR_MEETING_YOU_HAVE_NO_SHARE,///<没有共享.
	SDKERR_MEETING_VIEWTYPE_PARAMETER_IS_WRONG, ///<非法的 ViewType 参数.
	SDKERR_MEETING_ANNOTATION_IS_OFF, ///<注释不可用.
	SDKERR_SETTING_OS_DONT_SUPPORT, ///<当前系统不支持设置.
};

enum SDK_LANGUAGE_ID
{
	LANGUAGE_Unknow = 0,
	LANGUAGE_English,
	LANGUAGE_Chinese_Simplified,
	LANGUAGE_Chinese_Traditional,
	LANGUAGE_Japanese,
	LANGUAGE_Spanish,
	LANGUAGE_German,
	LANGUAGE_French,
	LANGUAGE_Portuguese,
	LANGUAGE_Russian,
};

/*! \struct tagWndPosition
    \描述：窗口位置 父窗口为null时窗口的坐标位置. 如果父窗口不为空，窗口位置为父窗口的坐标位置.
    \结构体详细参数如下:
*/
typedef struct tagWndPosition 
{
	int left;
	int top;
	HWND hSelfWnd;
	HWND hParent;
	tagWndPosition()
	{
		left = 0;
		top = 0;
		hSelfWnd = NULL;
		hParent = NULL;
	}
}WndPosition;

/*! \enum CustomizedLanguageType
    \描述：SDK使用的自定义资源类型.
    \下面是更详细的结构描述.
*/
enum CustomizedLanguageType
{
	CustomizedLanguage_None,
	CustomizedLanguage_FilePath,
	CustomizedLanguage_Content,
};

/*! \struct CustomizedLanguageType
    \描述：SDK使用的自定义资源信息.
    \下面是更详细的结构描述.
*/ 
typedef struct tagCustomizedLanguageInfo
{
	const char* langName;
	const char* langInfo;
	CustomizedLanguageType langType;
	tagCustomizedLanguageInfo()
	{
		langName = NULL;
		langInfo = NULL;
		langType = CustomizedLanguage_None;
	}

}CustomizedLanguageInfo;

/*! \struct tagConfigurableOptions
    \描述：SDK 配置选项. 
	\备注此结构仅用于SDK初始化，用于配置自定义资源文件并选择是否使用UI模式。
	\下面是更详细的结构描述		
*/
#define ENABLE_CUSTOMIZED_UI_FLAG (1 << 5)
typedef struct tagConfigurableOptions
{
	CustomizedLanguageInfo customizedLang;///自定义资源信息.
	int optionalFeatures;///<其他功能配置. 当前仅支持是否使用自定义UI模式，当optionalFeatures&ENABLE_CUSTOMIZED_UI_FLAG的值为true时，使用自定义UI模式，否则使用普通界面模式。
	const wchar_t* sdkPathPostfix;
	tagConfigurableOptions()
	{
		optionalFeatures = 0;
		sdkPathPostfix = NULL;
	}

}ConfigurableOptions;

/*! \struct tagInitParam
    \ 描述：SDK初始化参数.
    \下面是更详细的结构描述
*/
typedef struct tagInitParam  
{
	const wchar_t* strWebDomain;///<网络域.
	const wchar_t* strBrandingName;///<标题名.
	const wchar_t* strSupportUrl;///<技术支持URL.
	void* hResInstance;///<资源模块句柄.
	unsigned int uiWindowIconSmallID;///<窗口小图标ID.
	unsigned int uiWindowIconBigID;///<窗口大图标ID.
	SDK_LANGUAGE_ID emLanguageID;///<SDK语言ID.
	bool enableLogByDefault;///<使能日志开关.
	unsigned int uiLogFileSize; ///<日志文件大小（单位Mb）, 默认大小为5M. 总共有5个日志文件，文件大小从1M到50M不等. 
	ConfigurableOptions obConfigOpts;///<SDK的配置选项.
	tagInitParam()
	{
		strWebDomain = NULL;
		strBrandingName = NULL;
		strSupportUrl = NULL;
		hResInstance = (void*)-1;
		uiWindowIconSmallID = 0;
		uiWindowIconBigID = 0;
		emLanguageID = LANGUAGE_Unknow;
		enableLogByDefault = false;
		uiLogFileSize = 5;
	}
}InitParam;

/*! \enum LastErrorType
    \描述 SDK最后的错误类型.
    \下面是更详细的结构描述
*/
enum LastErrorType
{
	LastErrorType_None,///<没错.
	LastErrorType_Auth,///<认证期间错误.
	LastErrorType_Login,///<登陆期间错误.
	LastErrorType_Meeting,///<会议关联错误.
	LastErrorType_System,///<SDK底层关联错误.
};

/// \描述：SDK提供的错误机制接口
/// \该特性将逐步得到改进，因此可能不支持某些错误
class IZoomLastError
{
public:
	/// \描述：获取最后错误类型.
	/// \如果函数成功，则返回错误类型. 更多细节, 查看 LastErrorType enum.
	virtual LastErrorType GetErrorType() const = 0 ;
	/// \描述：获取最后的错误代码
	/// \如果函数成功，则返回相应的错误代码.
	virtual UINT64 GetErrorCode() const = 0;

	/// \描述:获取最后错误的描述信息.
	/// \如果函数成功，则返回想相应的错误描述，如果没有错误，将返回一个长度为0的字符串.
	virtual const wchar_t* GetErrorDescription() const = 0;
	virtual ~IZoomLastError(){};
};
template<class T>
class IList
{
public:
	virtual ~IList() {};
	virtual int GetCount() = 0;
	virtual T   GetItem(int index) = 0;
};

#define SDK_NULL_AUDIO_FILE_HANDLE (0xffffffff)
const RECT _SDK_TEST_VIDEO_INIT_RECT = {0,0,0,0};

END_ZHUMU_SDK_NAMESPACE

#endif