
// CFileTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCFileTestApp: 
// �йش����ʵ�֣������ CFileTest.cpp
//

class CCFileTestApp : public CWinApp
{
public:
	CCFileTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCFileTestApp theApp;