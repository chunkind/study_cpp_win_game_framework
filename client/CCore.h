#pragma once

#include "Define.h"
#include <Windows.h>

class CCore
{
public:
	SINGLE(CCore)

private:
	HWND		m_hWnd;
	POINT		m_ptResolution;

private:
	CCore();
	~CCore();
};