
// LotteryTrend.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLotteryTrendApp:
// �йش����ʵ�֣������ LotteryTrend.cpp
//

class CLotteryTrendApp : public CWinApp
{
public:
	CLotteryTrendApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLotteryTrendApp theApp;