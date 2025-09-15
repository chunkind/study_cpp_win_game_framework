#pragma once

class CCore
{
public:
	static CCore* GetInst()
	{
		static CCore core;
		return &core;
	}

private:
	HWND m_hWnd;
	POINT m_ptResolution;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	CCore();
	~CCore();
};