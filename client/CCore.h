#pragma once
//new
#include "Define.h"
#include <Windows.h>

class CCore
{
public:
	//old
	/*static CCore* GetInst()
	{
		static CCore core;
		return &core;
	}*/
	//new
	SINGLE(CCore)

//new
private:
	HWND		m_hWnd;				// ���� ������ �ڵ�
	POINT		m_ptResolution;		// ���� ������ �ػ�

private:
	CCore();
	~CCore();
};