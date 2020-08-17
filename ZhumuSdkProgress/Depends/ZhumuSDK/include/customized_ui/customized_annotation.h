/*!
* \文件 customized_annotation.h
* \描述：zhumu自定义标注服务接口
*
*/
#ifndef ZHUMU_CUSTOMIZED_ANNOTATION_H_
#define ZHUMU_CUSTOMIZED_ANNOTATION_H_
#include "..\zhumu_sdk_def.h"
#include "..\meeting_service_components\meeting_annotation_interface.h"

BEGIN_ZHUMU_SDK_NAMESPACE
class ICustomizedShareRender;

/*! \enum CustomizedShareAnnotationStatus
\描述：标注状态
更详细的结构描述。
*/
enum CustomizedShareAnnotationStatus
{
	CS_ANNO_READYTOUSE,//准备使用标注
	CS_ANNO_CLOSE, //标注关闭
};

/// \描述：标注对象回调事件
///
class ICustomizedAnnotationObjEvent
{
public:
	/// \描述：通知应用程序关于标注工具的更改
	virtual void onAnnotationObjToolChange(ZhumuSDK::AnnotationToolType type_) = 0;
};

/// \描述：标注对象接口
///
class ICustomizedAnnotationObj
{
public:
	/// \描述：设置标注对象回调事件
	/// \参数：pEvent 指向接收标注对象事件的ICustomizedAnnotationObjEvent*的指针。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(ICustomizedAnnotationObjEvent* event_) = 0;

	/// \描述：检查能清除标注
	/// \参数：type 清除标注的类型
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CanClear(AnnotationClearType type) = 0;

	/// \描述：清除标注
	/// \参数：type 清除标注的类型
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError Clear(AnnotationClearType type) = 0;

	/// \描述：设置标注工具
	/// \参数：type 标注工具类型
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetTool(AnnotationToolType type) = 0;

	/// \描述：设置标注工具得颜色
	/// \参数：color 标注工具得颜色
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetColor(unsigned long color) = 0;

	/// \描述：设置标注线宽
	/// \参数：lineWidth 标注工具线宽
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetLineWidth(long lineWidth) = 0;

	/// \描述：获取标注工具颜色
	/// \参数：color 当前标注工具得颜色
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError GetCurColor(unsigned long& color) = 0;

	/// \描述：获取标注工具的线宽
	/// \参数：lineWidth the current line width of annotation tool
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError GetCurLineWidth(long& lineWidth) = 0;

	/// \描述：获取标注工具的类型
	/// \参数：type 标注工具的类型
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError GetCurTool(AnnotationToolType& type) = 0;

	/// \描述：取消标注
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError Undo() = 0;

	/// \描述：回复上次操作
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError Redo() = 0;

	/// \描述：检查是否保存快照
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError CanSaveSnapshot() = 0;

	/// \描述：保存快照
	/// \参数：path 保存路径
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SaveSnapshot(const wchar_t* path) = 0;

	/// \brief Determine if can do annotate.
	/// \param [out] bCan, true means can do annotate, false can not. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanDoAnnotation(bool& bCan) = 0;

	/// \brief Determine whether annotations are currently available.
	/// \return true available, false invalid.
	virtual bool IsAnnoataionDisable() = 0;

	virtual ~ICustomizedAnnotationObj(){};


};

/// \描述： 标注控制器回调事件
///
class ICustomizedAnnotationControllerEvent
{
public:
	/// \描述：通知应用程序标注对象已被销毁
	/// \参数：obj_ 指定销毁哪个标注对象
	virtual void onCustomizedAnnotationObjDestroyed(ICustomizedAnnotationObj* obj_) = 0;

	/// \描述：通知应用程序标注状态已更改
	/// \参数：share_render_ 指定更改了哪个共享呈现的标注状态
	/// \参数：status_ status
	virtual void onSharingShareAnnotationStatusChanged(ICustomizedShareRender* share_render_, CustomizedShareAnnotationStatus status_) = 0;
};

/// \描述： 标注控制器接口
///
class ICustomizedAnnotationController
{
public:
	/// \描述：这hi标注控制器回调事件
	/// \参数：pEvent 指向接收标注控制器事件的ICustomizedAnnotationControllerEvent*的指针。 
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError SetEvent(ICustomizedAnnotationControllerEvent* event_) = 0;

	/// \描述：创建标注对象
	/// \参数：view_share_render 指定标注对象的所有者，如果创建用于开始共享的注释，则传递NULL。
	/// \参数：pp_obj 一个指向ICustomizedAnnotationObj*的指针，该指针接收ICustomizedAnnotationObj对象。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	/// \when you got onSharingShareAnnotationStatusChanged with CS_ANNO_READYTOUSE.
	virtual SDKError CreateAnnoObj(ICustomizedShareRender* view_share_render, ICustomizedAnnotationObj** pp_obj) = 0;

	/// \描述：摧毁注释对象
	/// \参数：anno_obj 指向要销毁的ICustomizedAnnotationObj的指针。
	/// \返回：如果函数成功，返回值为SDKErr_Success。
	/// 如果函数失败，返回值不是SDKErr_Success。要获得扩展的错误信息，请参考SDKError enum。
	virtual SDKError DestroyAnnoObj(ICustomizedAnnotationObj* anno_obj) = 0;
	virtual ~ICustomizedAnnotationController() {};
};
END_ZHUMU_SDK_NAMESPACE
#endif