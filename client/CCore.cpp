#include "pch.h"
#include "CCore.h"
#include "CObject.h"
//old
//#include <tchar.h>

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

	//old
	//g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	//g_obj.m_ptScale = POINT{ 100, 100 };
	//new
	g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

void CCore::progress()
{
	//old
	/*static int callcount = 0;
	++callcount;

	static int iPrevCount = GetTickCount();
	int iCurCount = GetTickCount();
	if (iCurCount - iPrevCount > 1000)
	{
		iPrevCount = iCurCount;
		callcount = 0;
	}

	wchar_t szBuff[500] = {};

	swprintf_s(szBuff, L"callcount: %d, iPrevCount: %d, iCurCount: %d", callcount, iPrevCount, iCurCount);
	SetWindowText(m_hWnd, szBuff);*/

	update();
	render();
}

void CCore::update()
{
	//new
	Vec2 vPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		//old
		//g_obj.m_ptPos.x -= 1;
		//new
		vPos.x -= 0.01f;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		//old
		//g_obj.m_ptPos.x += 1;
		//new
		vPos.x += 0.01f;
	}

	//new
	g_obj.SetPos(vPos);
}

void CCore::render()
{
	//old
	//Rectangle(m_hDC
		//, g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2
		//, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
		//, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
		//, g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
	//new
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	//new
	Rectangle(m_hDC
		, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f));
}