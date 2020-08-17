/*!
* \�ļ��� zhumu_sdk_def.h
* \������ Zhumu Windows SDK ������������
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
	\���� ��ʼ�� SDK ʹ�ò���
	����ϸ�Ľṹ������.
*/ 
enum SDKError
{
	SDKERR_SUCCESS = 0,///<�ɹ�.
	SDKERR_NO_IMPL,///<�˹��ܵ�ǰ��Ч. 
	SDKERR_WRONG_USEAGE,///<����ʹ�ù���. 
	SDKERR_INVALID_PARAMETER,///<��������.
	SDKERR_MODULE_LOAD_FAILED,///<����ģ��ʧ��.
	SDKERR_MEMORY_FAILED,///<�ڴ�δ����. 
	SDKERR_SERVICE_FAILED,///<�ڲ��������.
	SDKERR_UNINITIALIZE,///<ʹ��ǰδ��ʼ��.
	SDKERR_UNAUTHENTICATION,///<ʹ��ǰδ��֤.
	SDKERR_NORECORDINGINPROCESS,///<δ¼��.
	SDKERR_TRANSCODER_NOFOUND,///<ת��ģ��δ�ҵ�.
	SDKERR_VIDEO_NOTREADY,///<��Ƶ����ģ��δ����.
	SDKERR_NO_PERMISSION,///<��Ȩ��.
	SDKERR_UNKNOWN,///<δ֪����.
	SDKERR_OTHER_SDK_INSTANCE_RUNNING,///<�����SDKʵ����������.
	SDKERR_INTELNAL_ERROR,///<SDK�ڲ�����.
	SDKERR_NO_AUDIODEVICE_ISFOUND,///<δ������Ƶ�豸.
	SDKERR_NO_VIDEODEVICE_ISFOUND,///<δ������Ƶ�豸.
	SDKERR_TOO_FREQUENT_CALL,///<API����̫Ƶ��.
	SDKERR_FAIL_ASSIGN_USER_PRIVILEGE, ///<�޷�Ϊ�û������µ�Ȩ��.
	SDKERR_MEETING_DONT_SUPPORT_FEATURE,///<��ǰ���鲻֧�ָ�����.
	SDKERR_MEETING_NOT_SHARE_SENDER,///<��ǰ�û�������ʾ��.
	SDKERR_MEETING_YOU_HAVE_NO_SHARE,///<û�й���.
	SDKERR_MEETING_VIEWTYPE_PARAMETER_IS_WRONG, ///<�Ƿ��� ViewType ����.
	SDKERR_MEETING_ANNOTATION_IS_OFF, ///<ע�Ͳ�����.
	SDKERR_SETTING_OS_DONT_SUPPORT, ///<��ǰϵͳ��֧������.
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
    \����������λ�� ������Ϊnullʱ���ڵ�����λ��. ��������ڲ�Ϊ�գ�����λ��Ϊ�����ڵ�����λ��.
    \�ṹ����ϸ��������:
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
    \������SDKʹ�õ��Զ�����Դ����.
    \�����Ǹ���ϸ�Ľṹ����.
*/
enum CustomizedLanguageType
{
	CustomizedLanguage_None,
	CustomizedLanguage_FilePath,
	CustomizedLanguage_Content,
};

/*! \struct CustomizedLanguageType
    \������SDKʹ�õ��Զ�����Դ��Ϣ.
    \�����Ǹ���ϸ�Ľṹ����.
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
    \������SDK ����ѡ��. 
	\��ע�˽ṹ������SDK��ʼ�������������Զ�����Դ�ļ���ѡ���Ƿ�ʹ��UIģʽ��
	\�����Ǹ���ϸ�Ľṹ����		
*/
#define ENABLE_CUSTOMIZED_UI_FLAG (1 << 5)
typedef struct tagConfigurableOptions
{
	CustomizedLanguageInfo customizedLang;///�Զ�����Դ��Ϣ.
	int optionalFeatures;///<������������. ��ǰ��֧���Ƿ�ʹ���Զ���UIģʽ����optionalFeatures&ENABLE_CUSTOMIZED_UI_FLAG��ֵΪtrueʱ��ʹ���Զ���UIģʽ������ʹ����ͨ����ģʽ��
	const wchar_t* sdkPathPostfix;
	tagConfigurableOptions()
	{
		optionalFeatures = 0;
		sdkPathPostfix = NULL;
	}

}ConfigurableOptions;

/*! \struct tagInitParam
    \ ������SDK��ʼ������.
    \�����Ǹ���ϸ�Ľṹ����
*/
typedef struct tagInitParam  
{
	const wchar_t* strWebDomain;///<������.
	const wchar_t* strBrandingName;///<������.
	const wchar_t* strSupportUrl;///<����֧��URL.
	void* hResInstance;///<��Դģ����.
	unsigned int uiWindowIconSmallID;///<����Сͼ��ID.
	unsigned int uiWindowIconBigID;///<���ڴ�ͼ��ID.
	SDK_LANGUAGE_ID emLanguageID;///<SDK����ID.
	bool enableLogByDefault;///<ʹ����־����.
	unsigned int uiLogFileSize; ///<��־�ļ���С����λMb��, Ĭ�ϴ�СΪ5M. �ܹ���5����־�ļ����ļ���С��1M��50M����. 
	ConfigurableOptions obConfigOpts;///<SDK������ѡ��.
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
    \���� SDK���Ĵ�������.
    \�����Ǹ���ϸ�Ľṹ����
*/
enum LastErrorType
{
	LastErrorType_None,///<û��.
	LastErrorType_Auth,///<��֤�ڼ����.
	LastErrorType_Login,///<��½�ڼ����.
	LastErrorType_Meeting,///<�����������.
	LastErrorType_System,///<SDK�ײ��������.
};

/// \������SDK�ṩ�Ĵ�����ƽӿ�
/// \�����Խ��𲽵õ��Ľ�����˿��ܲ�֧��ĳЩ����
class IZoomLastError
{
public:
	/// \��������ȡ����������.
	/// \��������ɹ����򷵻ش�������. ����ϸ��, �鿴 LastErrorType enum.
	virtual LastErrorType GetErrorType() const = 0 ;
	/// \��������ȡ���Ĵ������
	/// \��������ɹ����򷵻���Ӧ�Ĵ������.
	virtual UINT64 GetErrorCode() const = 0;

	/// \����:��ȡ�������������Ϣ.
	/// \��������ɹ����򷵻�����Ӧ�Ĵ������������û�д��󣬽�����һ������Ϊ0���ַ���.
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