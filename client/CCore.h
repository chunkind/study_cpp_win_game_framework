#pragma once

class CCore
{
public:
	SINGLE(CCore)

private:
	HWND		m_hWnd;
	POINT		m_ptResolution;
	//new
	HDC			m_hDC; // 메인 윈도우에 Draw할 DC

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	CCore();
	~CCore();
};