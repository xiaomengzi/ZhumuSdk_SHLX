
// ZhumuSdkExDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZhumuSdkExDemoApp: 
// �йش����ʵ�֣������ ZhumuSdkExDemo.cpp
//

class CZhumuSdkExDemoApp : public CWinApp
{
public:
	CZhumuSdkExDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CZhumuSdkExDemoApp theApp;