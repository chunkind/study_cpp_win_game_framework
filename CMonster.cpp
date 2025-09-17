#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h";

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_iHP(5)
	, m_pTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"EnemyTex", L"texture\\Enemy.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	Vec2 vCurPos = GetPos();

	vCurPos.x += fDT * m_fSpeed * m_iDir;

	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;

	if (0.f < fDist)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}

void CMonster::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	HDC hdcTmp = CreateCompatibleDC(_dc);
	HBITMAP hbmTmp = CreateCompatibleBitmap(_dc, iWidth, iHeight);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcTmp, hbmTmp);

	Vec2 vPos = GetPos();

	StretchBlt(hdcTmp
		, 0, 0
		, iWidth, iHeight
		, m_pTex->GetDC()
		, iWidth - 1, iHeight - 1
		, -iWidth, -iHeight
		, SRCCOPY);

	TransparentBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, hdcTmp
		, 0, 0
		, iWidth, iHeight
		, RGB(255, 0, 255)
	);

	SelectObject(hdcTmp, hbmOld);
	DeleteObject(hbmTmp);
	DeleteDC(hdcTmp);

	component_render(_dc);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_iHP -= 1;

		if (m_iHP <= 0)
			DeleteObject(this);
	}
}