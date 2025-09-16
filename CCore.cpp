#include "pch.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CObject.h"

CObject g_obj;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{
}

CCore::~CCore()
{
	::ReleaseDC(m_hWnd, m_hDC);

	::DeleteDC(m_memDC);
	::DeleteObject(m_hBit);
}

int CCore::init(HWND _hWnd, POINT _ptResultution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResultution;

	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	::AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	::SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = ::GetDC(m_hWnd);

	m_hBit = ::CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = ::CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)::SelectObject(m_memDC, m_hBit);
	::DeleteObject(hOldBit);

	CTimeMgr::GetInst()->init();

	g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

void CCore::progress()
{
	CTimeMgr::GetInst()->update();

	update();
	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	if (::GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 100.f * fDT;
	}

	if (::GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 100.f * fDT;
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	::Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	::Rectangle(m_memDC
		, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f));

	::BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}