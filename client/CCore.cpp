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
	//�ػ󵵿� �°� ������ ũ�� ����(������ �޴���, ���������� ���Ե� ũ��)
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	//AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); // ���������� �޴�������
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false); // ���������� �޴�������

	//new
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	//new
	m_hDC = GetDC(m_hWnd);

	return S_OK;
}

void CCore::progress()
{
	//new
	// �׸��� �۾�
	Rectangle(m_hDC, 10, 10, 110, 110);
}