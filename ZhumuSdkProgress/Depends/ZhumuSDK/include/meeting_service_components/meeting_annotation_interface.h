/*!
* \文件： meeting_annotation_interface.h
* \描述： 会议标注服务接口
*
*/
#ifndef ZHUMU_MEETING_Annotation_INTERFACE_H_
#define ZHUMU_MEETING_Annotation_INTERFACE_H_
#include "..\zhumu_sdk_def.h"
#include "..\meeting_service_interface.h"
/// \描述: Zhumu SDK Namespace
/// 
///
BEGIN_ZHUMU_SDK_NAMESPACE
/*! \enum AnnotationToolType
\描述：标注工具类型.
下面是更详细的结构描述
*/
enum AnnotationToolType
{
	ANNOTOOL_NONE_DRAWING,///<切换到鼠标

	ANNOTOOL_PEN,///<画笔.
	ANNOTOOL_HIGHLIGHTER,///<高亮.
	ANNOTOOL_AUTO_LINE,///<直线会随着鼠标指针的移动而自动改变。
	ANNOTOOL_AUTO_RECTANGLE,///<矩形会随着鼠标指针的移动而自动改变。
	ANNOTOOL_AUTO_ELLIPSE,///<椭圆会随着鼠标的移动而自动改变
	ANNOTOOL_AUTO_ARROW,///<箭头会随着鼠标的移动而自动改变。
	ANNOTOOL_AUTO_RECTANGLE_FILL,///<填充矩形
	ANNOTOOL_AUTO_ELLIPSE_FILL,///<填充椭圆
	ANNOTOOL_SPOTLIGHT,///<激光笔
	ANNOTOOL_ARROW,///<显示点击共享内容的人的名字上的箭头。
	ANNOTOOL_ERASER,///<橡皮擦.

	ANNOTOOL_TEXTBOX, ///<插入文本输入框.
	ANNOTOOL_PICKER, ///<选择标注.
	ANNOTOOL_AUTO_RECTANGLE_SEMI_FILL, ///<会随着鼠标的移动而自动改变的矩形。.
	ANNOTOOL_AUTO_ELLIPSE_SEMI_FILL, ///<会随着鼠标的移动而自动改变的均匀的椭圆.
	ANNOTOOL_AUTO_DOUBLE_ARROW, ///<带有双箭头的线. 
	ANNOTOOL_AUTO_DIAMOND, ///<空心的菱形.
	ANNOTOOL_AUTO_STAMP_ARROW, ///<用于标记的固定大小的箭头.
	ANNOTOOL_AUTO_STAMP_CHECK, ///<标记正确的标志.
	ANNOTOOL_AUTO_STAMP_X, ///<标记错误的标志.
	ANNOTOOL_AUTO_STAMP_STAR, ///<标记用的五角星
	ANNOTOOL_AUTO_STAMP_HEART, ///<标记用的心形
	ANNOTOOL_AUTO_STAMP_QM, ///<问号.
};

/*! \enum AnnotationClearType
\描述: 清除类型.
更详细的结构描述
*/
enum AnnotationClearType
{
	ANNOCLEAR_ALL,
	ANNOCLEAR_SELF,
	ANNOCLEAR_OTHER,
};

/// \描述：显示注释状态更改的回调接口.
class IMeetingAnnotationSupportEvent
{
public:
	/// \描述：：如果演示者启用/禁用参与者注释，SDK将触发此回调										
	virtual void onSupportAnnotationStatus(unsigned int userid, bool bSupportAnnotation) = 0;
};

class ICustomizedAnnotationController;
/// \描述：会议标注工具接口.
///
class IAnnotationController
{
public:
	/// \描述：设置注释状态更改的回调. 
	/// \参数：pEvent 一个指向IMeetingAnnotationSupportEvent的对象指针，它接收标注状态改变回调事件。
	/// \返回：如果用户拥有权限，则返回值为SDKErr_Success。
	/// 否则返回其他错误信息。要获取扩展的错误信息，请参见 SDKError enum。
	virtual SDKError SetEvent(IMeetingAnnotationSupportEvent* pEvent) = 0;

	/// \描述：确定在当前会议期间是否禁用了指定视图的标注工具。
	/// \参数：viewtype 指定要确定的视图。有关详细信息，请参见 SDKViewType enum。
	/// \返回：FALSE 表示启用，TRUE表示禁用。
	/// \注意：适用于zhumu风格和用户自定义界面模式。
	virtual bool IsAnnoataionDisable(SDKViewType viewtype = SDK_FIRST_VIEW) = 0;

	/// \描述：开始标注
	/// \参数：viewtype 指定要设置的视图，第一个监视器还是第二个监视器。
	/// \参数：left 指定标注栏的左侧位置。
	/// \参数：top 指定标注栏的顶部位置
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅适用于zhumu风格的用户界面模式
	virtual SDKError StartAnnotation(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, int left, int top) = 0;

	/// \描述：停止当前标注
	/// \参数：viewtype 指定要设置的视图，第一个监视器还是第二个监视器
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅适用于zhumu风格的用户界面模式
	virtual SDKError StopAnnotation(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype) = 0;

	/// \描述：设置标注工具
	/// \参数：viewtype 指定要设置的视图，第一个监视器还是第二个监视器。
	/// \参数：type 用于标注工具类型的参数，请参考AnnotationToolType。 
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅适用于zhumu风格的用户界面模式
	virtual SDKError SetTool(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, AnnotationToolType type) = 0;

	/// \描述：清除标注
	/// \参数：viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \参数： type The parameter to be used for annotation earse operator type, refer to AnnotationClearType. 
	/// \返回：If the function succeeds, the return value is SDKErr_Success.
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅适用于zhumu风格的用户界面模式
	virtual SDKError Clear(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, AnnotationClearType type) = 0;


	/// \描述：设置标注颜色
	/// \参数：viewtype 指定要设置的视图，第一个监视器还是第二个监视器。
	/// \参数：color 用于注释颜色、ABGR格式的参数。
	/// \返回：如果函数成功，则返回值为SDKErr_Success。
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅适用于zhumu风格的用户界面模式
	virtual SDKError SetColor(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, unsigned long color) = 0;

	/// \描述：设置标注线宽
	/// \参数：viewtype 指定要设置的视图，第一个监视器还是第二个监视器。
	/// \参数：用于注释行的宽度的参数。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅适用于zhumu风格的用户界面模式
	virtual SDKError SetLineWidth(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, long lineWidth) = 0;

	/// \描述：取消标注
	/// \参数：viewtype 指定要设置的视图，第一个监视器还是第二个监视器。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅适用于zhumu风格的用户界面模式
	virtual SDKError Undo(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype) = 0;

	/// \描述：恢复标注
	/// \参数：viewtype 指定要设置的视图，第一个监视器还是第二个监视器。
	/// \返回：如果函数成功，则返回值为SDKErr_Success
	/// 如果函数失败，则返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \仅适用于zhumu风格的用户界面模式
	virtual SDKError Redo(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype) = 0;

	/// \描述：获取用于自定义ui模式的注释控制器
	/// \返回: 如果函数成功，返回值为自定义ui模式的annotation controller接口。
	/// 如果函数失败，返回值为NULL。
	/// \仅适用于自定义风格的ui模式
	virtual ICustomizedAnnotationController* GetCustomizedAnnotationController() = 0;

	/// \描述：不允许/允许参与者在查看共享内容时进行注释。
	/// \参数：[in] viewtype: SDK_FIRST_VIEW/SDK_SECOND_VIEW
	/// \参数：[in] disable TRUE 表示禁用, FALSE 表示启用.
	/// \返回：如果用户拥有权限，则返回值为SDKErr_Success。
	///否则返回其他错误信息。要获取扩展的错误信息，请参见\link SDKError \endlink enum。
	virtual SDKError DisableViewerAnnotation(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, bool bDisable) = 0;

	/// \描述：确定观看者的注释特权是否被禁用。
	/// \参数：[in] viewtype: SDK_FIRST_VIEW/SDK_SECOND_VIEW
	/// \参数：[out] bDisabled TRUE 表示禁用, FALSE 表示启用. 只在返回值为SDKErr_Success时有效 
	/// \返回：如果用户拥有权限，则返回值为SDKErr_Success。
	///否则返回其他错误信息。。要获取扩展的错误信息，请参见\link SDKError \endlink enum。
	virtual SDKError IsViewerAnnotationDisabled(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, bool& bDisabled) = 0;

	/// \描述: 确定是否不允许观看者进行标注 
	/// \参数：[in] viewtype: SDK_FIRST_VIEW/SDK_SECOND_VIEW
	/// \参数：[out] bCan TRUE 表示禁用, FALSE 表示启用. 只在返回值为SDKErr_Success时有效  
	/// \返回: 如果用户拥有权限，则返回值为SDKErr_Success。
	///否则返回其他错误信息。要获取扩展的错误信息，请参见\link SDKError \endlink enum。
	virtual SDKError CanDisableViewerAnnotation(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, bool& bCan) = 0;

	/// \描述：确定它是否能够注释(演示者和观看者都可以调用该函数)。
	/// \参数：[in] viewtype: SDK_FIRST_VIEW/SDK_SECOND_VIEW
	/// \参数：[out] bCan TRUE 表示禁用, FALSE 表示启用. 只在返回值为SDKErr_Success时有效  
	/// \返回: 如果用户拥有权限，则返回值为SDKErr_Success。
	///否则返回其他错误信息。要获取扩展的错误信息，请参见\link SDKError \endlink enum。
	virtual SDKError CanDoAnnotation(ZHUMU_SDK_NAMESPACE::SDKViewType viewtype, bool& bCan) = 0;

};
END_ZHUMU_SDK_NAMESPACE
#endif