
// AutoFoucs.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAutoFoucsApp: 
// �йش����ʵ�֣������ AutoFoucs.cpp
//

class CAutoFoucsApp : public CWinApp
{
public:
	CAutoFoucsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAutoFoucsApp theApp;