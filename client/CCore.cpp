#include "pch.h"
#include "CCore.h"

CCore::CCore()
	//new
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)

{

}

CCore::~CCore()
{
	//new
	ReleaseDC(m_hWnd, m_hDC);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	//new
	//해상도에 맞게 윈도우 크기 조절(윈도우 메뉴바, 테투리까지 포함된 크기)
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	//AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); // 마지막인자 메뉴바유무
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false); // 마지막인자 메뉴바유무

	//new
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	//new
	m_hDC = GetDC(m_hWnd);

	return S_OK;
}

void CCore::progress()
{
	//new
	// 그리기 작업
	Rectangle(m_hDC, 10, 10, 110, 110);
}