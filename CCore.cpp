#include "pch.h"

#include "CCore.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{
}

CCore::~CCore()
{
	::ReleaseDC(m_hWnd, m_hDC);
}

int CCore::init(HWND _hWnd, POINT _ptResultution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResultution;

	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	::AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	::SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	return S_OK;
}

void CCore::progress()
{
	::Rectangle(m_hDC, 10, 10, 110, 110);
}
