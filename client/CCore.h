#pragma once

class CCore
{
public:
	SINGLE(CCore)

private:
	HWND		m_hWnd;
	POINT		m_ptResolution;
	HDC			m_hDC;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

//new
private:
	void update();
	void render();

private:
	CCore();
	~CCore();
};