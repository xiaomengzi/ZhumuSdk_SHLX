
// ZhumuSdkProgress.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZhumuSdkProgressApp: 
// �йش����ʵ�֣������ ZhumuSdkProgress.cpp
//

class CZhumuSdkProgressApp : public CWinApp
{
public:
	CZhumuSdkProgressApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CZhumuSdkProgressApp theApp;