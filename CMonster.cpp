#include "pch.h"
#include "CMonster.h"
#include "AI.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"

CMonster::CMonster()
	: m_fSpeed(100.f)
	, m_iHP(5)
	, m_pTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"EnemyTex", L"texture\\Enemy.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}

void CMonster::update()
{
	m_pAI->update();
}

void CMonster::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	HDC hdcTmp = CreateCompatibleDC(_dc);
	HBITMAP hbmTmp = CreateCompatibleBitmap(_dc, iWidth, iHeight);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcTmp, hbmTmp);

	Vec2 vPos = GetPos();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);

	::StretchBlt(hdcTmp
		, 0, 0
		, iWidth, iHeight
		, m_pTex->GetDC()
		, iWidth - 1, iHeight - 1
		, -iWidth, -iHeight
		, SRCCOPY);

	::TransparentBlt(_dc
		, int(vRenderPos.x - (float)(iWidth / 2))
		, int(vRenderPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, hdcTmp
		, 0, 0
		, iWidth, iHeight
		, RGB(255, 0, 255)
	);

	::SelectObject(hdcTmp, hbmOld);
	::DeleteObject(hbmTmp);
	::DeleteDC(hdcTmp);

	component_render(_dc);
}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
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