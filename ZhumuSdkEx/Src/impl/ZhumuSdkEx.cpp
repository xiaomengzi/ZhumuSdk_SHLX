// ZhumuSdkEx.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "ZhumuSdkEx.h"


// ���ǵ���������һ��ʾ��
ZHUMUSDKEX_API int nZhumuSdkEx=0;

// ���ǵ���������һ��ʾ����
ZHUMUSDKEX_API int fnZhumuSdkEx(void)
{
    return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� ZhumuSdkEx.h
CZhumuSdkEx::CZhumuSdkEx()
{
    return;
}
