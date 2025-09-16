#pragma once

class CCore
{
	SINGLE(CCore)
private:
	HWND	m_hWnd;
	POINT	m_ptResolution;
	HDC		m_hDC;

	HBITMAP	m_hBit;
	HDC		m_memDC;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:

public:
	HWND GetMainHwnd() { return m_hWnd; }
};