
// Oculus.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// COculusApp:
// �� Ŭ������ ������ ���ؼ��� Oculus.cpp�� �����Ͻʽÿ�.
//

class COculusApp : public CWinApp
{
public:
	COculusApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern COculusApp theApp;