#include <windows.h>

#include "CCore.h"

CCore::CCore()
{
}

CCore::~CCore()
{
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	return S_OK;
}

void CCore::progress()
{
}

