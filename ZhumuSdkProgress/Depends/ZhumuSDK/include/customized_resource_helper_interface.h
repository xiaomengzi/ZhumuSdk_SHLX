/*!
* \文件：customized_resource_helper_interface.h
* \描述：自定义服务接口
* \注意：在调用ZHUMU_SDK_NAMESPACE::InitSDK()之前，必须先调用这些函数，否则将无法工作。
*/
#ifndef _customiezed_resource_helper_interface_h
#define _customiezed_resource_helper_interface_h
#include "zhumu_sdk_def.h"

BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum SDKCustomizedStringType
\简述：自定义字符串类型。
下面是更详细的结构描述。
\注意：您需要仔细阅读每种类型的描述。必须按照该格式自定义自己的字符串。错误的使用可能导致不可预知的崩溃。
*/
enum SDKCustomizedStringType
{
	SDK_Customized_LiveStream_MenuString_LiveOn_String = 0,///<新字符串必须以“%s”结束，以便菜单项可以正确显示。此类型用于定义一个字符串来替换实时流媒体上%S上的菜单项。
	SDK_Customized_LiveStream_MenuString_LiveView_String,///<新字符串必须以“%s”结束，以便菜单项可以正确显示。此类型用于定义一个字符串来替换实时流媒体上%S上的菜单项视图流。
	SDK_Customized_LiveStream_MenuString_LiveStop_String,///<新字符串必须是纯字符串，这样才能正确显示。此类型用于定义一个字符串来替换实时流媒体上的菜单项STOP LIVE STREAM。
	SDK_Customized_LiveStream_MenuString_CopyURL_String,///<新字符串必须是纯字符串，这样才能正确显示。此类型用于定义一个字符串来替换实时流媒体上的菜单项复制流链接。
	SDK_Customized_Title_App,	///<新字符串必须是纯字符串，这样才能正确显示。此类型用于定义一个字符串来替换会议视频UI的标题。
	SDK_Customized_Title_ZoomVideo,  ///<新字符串必须与“Zhumu Participant ID: %s Meeting ID: %s”格式相同，以便能够正确显示。此类型用于定义一个字符串来替换会议视频UI的标题。
	SDK_Customized_Title_FreeZoomVideo, ///<新字符串必须与“Zhumu参与者ID:%s %d-Minutes Meeting ID:%s”格式相同，以便能够正确显示。此类型用于定义一个字符串，以在用户为自由用户且处于仅限查看状态时替换会议视频UI的标题。
	SDK_Customized_Title_ViewOnly_ZoomVideo, ///<新字符串必须以“%s”结尾，以便正确显示。此类型用于定义一个字符串来替换会议视频UI的标题。
	SDK_Customized_Title_ViewOnly_FreeZoomVideo, ///<新字符串必须与“Zhumu %d-Minutes Meeting ID: %s”格式相同，以便正确显示。此类型用于定义一个字符串，以在用户为自由用户且处于仅限查看状态时替换会议视频UI的标题。
};

/*! \enum SDKCustomizedURLType
\描述：自定义URL类型.
下面是更详细的结构描述。
\注意：URL必须保持完整，并且应该包含“http”或“https”。
*/
enum SDKCustomizedURLType
{
	SDKCustomizedURL_VITRULBG_HELP, ///<在“虚拟背景”选项卡页面中设置自定义帮助URL。
	SDKCustomizedURL_VITRULBG_LEARN_MORE,///<在“虚拟背景”选项卡页面中设置自定义了解更多URL。
	SDKCustomizedURL_SUPPORTURL, ///<设置在会议中的支持URL。
};
class ICustomizedResourceHelper
{
public:
	///\描述：添加自定义照片文件，目前只支持PNG格式。
	///\参数：key_ 与自定义资源对应的资源ID。
	///\参数：absolute_resource_path 自定义资源文件的位置必须是绝对路径，并包含带后缀的文件名。
	/// \注意：必须在调用之前先调用函数ZHUMU_SDK_NAMESPACE::InitSDK(), 否则, 这个方法无效.
	virtual SDKError AddCustomizedPictureResource(const wchar_t* key_, const wchar_t* absolute_resource_path) = 0;
	/// \描述：使用自定义字符串替换指定的字符串项。
	/// \参数：customizedType 指定字符串类型. 更多详细信息, 查看 SDKCustomizedStringType enum.
	/// \参数：customizedString 指定字符串.
	/// \返回：如果函数成功，则返回值为 SDKErr_Success.
	/// 否则失败。要获取扩展的错误信息，请参见 SDKError enum.
	/// \注意：如果customizedString为NULL或非NULL，但长度为0，则返回值为SDKERR_INVALID_PARAMETER.
	/// \注意：在调用ZHUMU_SDK_NAMESPACE::InitSDK()之前，必须先调用该函数，否则此方法无效。
	virtual SDKError AddCustomizedStringResource(SDKCustomizedStringType customizedType, const wchar_t* customizedString) = 0;
	/// \描述：使用自定义URL替换指定的URL。
	/// \参数：customizedType指定URL类型。有关更多信息，请参见 SDKCustomizedURLType enum.
	/// \参数：customizedUrl指定自定义URL。 
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 否则失败。要获得扩展的错误信息，请参见 SDKError enum。
	/// \注意：如果customizedUrl为NULL或非NULL，但长度为0(0)，返回值为SDKERR_INVALID_PARAMETER。
	/// \注意：在调用ZHUMU_SDK_NAMESPACE::InitSDK()之前，必须先调用该函数，否则此方法无效
	virtual SDKError AddCustomizedURLResource(SDKCustomizedURLType customizedType, const wchar_t* customizedUrl) = 0;
};
END_ZHUMU_SDK_NAMESPACE
#endif
