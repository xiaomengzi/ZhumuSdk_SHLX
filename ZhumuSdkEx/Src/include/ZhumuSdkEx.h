// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ZHUMUSDKEX_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZHUMUSDKEX_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ZHUMUSDKEX_EXPORTS
#define ZHUMUSDKEX_API __declspec(dllexport)
#else
#define ZHUMUSDKEX_API __declspec(dllimport)
#endif

// �����Ǵ� ZhumuSdkEx.dll ������
class ZHUMUSDKEX_API CZhumuSdkEx {
public:
	CZhumuSdkEx(void);
	// TODO:  �ڴ�������ķ�����
};

extern ZHUMUSDKEX_API int nZhumuSdkEx;

ZHUMUSDKEX_API int fnZhumuSdkEx(void);
