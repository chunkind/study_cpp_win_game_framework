#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"
#include <tchar.h>

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llFrequency{}
{

}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	::QueryPerformanceCounter(&m_llCurCount);
	::QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	wchar_t szBuffer[255] = {};
	::swprintf_s(szBuffer, L"CurCount : %d, Frequency : %d", m_llCurCount, m_llFrequency);
	SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
}