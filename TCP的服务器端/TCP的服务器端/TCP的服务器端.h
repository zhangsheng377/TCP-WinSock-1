
// TCP�ķ�������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTCP�ķ�������App: 
// �йش����ʵ�֣������ TCP�ķ�������.cpp
//

class CTCP�ķ�������App : public CWinApp
{
public:
	CTCP�ķ�������App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTCP�ķ�������App theApp;