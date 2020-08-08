// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ZHUMUSDKEX_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ZHUMUSDKEX_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef ZHUMUSDKEX_EXPORTS
#define ZHUMUSDKEX_API __declspec(dllexport)
#else
#define ZHUMUSDKEX_API __declspec(dllimport)
#endif

// 此类是从 ZhumuSdkEx.dll 导出的
class ZHUMUSDKEX_API CZhumuSdkEx {
public:
	CZhumuSdkEx(void);
	// TODO:  在此添加您的方法。
};

extern ZHUMUSDKEX_API int nZhumuSdkEx;

ZHUMUSDKEX_API int fnZhumuSdkEx(void);
