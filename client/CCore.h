#pragma once

#include "Define.h"

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