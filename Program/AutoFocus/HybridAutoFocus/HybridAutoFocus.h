
// HybridAutoFocus.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHybridAutoFocusApp: 
// �йش����ʵ�֣������ HybridAutoFocus.cpp
//

class CHybridAutoFocusApp : public CWinApp
{
public:
	CHybridAutoFocusApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHybridAutoFocusApp theApp;