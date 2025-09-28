#pragma once

class CCore
{
public:
	SINGLE(CCore)

private:
	HWND		m_hWnd;
	POINT		m_ptResolution;
	//new
	HDC			m_hDC; // ���� �����쿡 Draw�� DC

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	CCore();
	~CCore();
};