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
	HWND		m_hWnd;				// 메인 윈도우 핸들
	POINT		m_ptResolution;		// 메인 윈도우 해상도

private:
	CCore();
	~CCore();
};