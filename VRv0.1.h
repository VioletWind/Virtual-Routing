
// VRv0.1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CVRv01App: 
// �йش����ʵ�֣������ VRv0.1.cpp
//

class CVRv01App : public CWinApp
{
public:
	CVRv01App();

// ��д
public:
	virtual BOOL InitInstance();
private:
	CAsyncSocket m_sSock;
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVRv01App theApp;
