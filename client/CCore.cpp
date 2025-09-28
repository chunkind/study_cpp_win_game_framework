#include "pch.h"
#include "CCore.h"
//new
#include "CObject.h"

//new
CObject g_obj;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	//new
	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	g_obj.m_ptScale = POINT{ 100, 100 };

	return S_OK;
}

void CCore::progress()
{
	//old
	//Rectangle(m_hDC, 10, 10, 110, 110);
	//new
	update();
	render();
}

//new
void CCore::update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		g_obj.m_ptPos.x -= 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 1;
	}
}

//new
void CCore::render()
{
	// ±×¸®±â
	//Rectangle(m_hDC, 10, 10, 110, 110);
	Rectangle(m_hDC
		, g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
		, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}