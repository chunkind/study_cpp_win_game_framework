#pragma once

class CTexture;

class CCore
{
	SINGLE(CCore)

private:
	HWND		m_hWnd;
	POINT		m_ptResolution;
	HDC			m_hDC;

	CTexture*	m_pMemTex; // 백버퍼 텍스쳐

	HBRUSH		m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN		m_arrPen[(UINT)PEN_TYPE::END];
	HMENU		m_hMenu;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }

	POINT GetResolution() { return m_ptResolution; }

	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};