
// TCP�Ŀͻ���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTCP�Ŀͻ���App: 
// �йش����ʵ�֣������ TCP�Ŀͻ���.cpp
//

class CTCP�Ŀͻ���App : public CWinApp
{
public:
	CTCP�Ŀͻ���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTCP�Ŀͻ���App theApp;