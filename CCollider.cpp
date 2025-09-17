#include "pch.h"
#include "CCollider.h"
#include "CCore.h"
#include "CObject.h"

CCollider::CCollider()
	: m_pOwner(nullptr)
{
}

CCollider::~CCollider()
{
}

void CCollider::finalupdate()
{
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	HPEN hGreenPen = CCore::GetInst()->GetPen(PEN_TYPE::GREEN);
	HPEN hDefaultPen = (HPEN)::SelectObject(_dc, hGreenPen);

	HBRUSH hHolowBrush = CCore::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW);
	HBRUSH hDefaultBrush = (HBRUSH)::SelectObject(_dc, hHolowBrush);

	::Rectangle(_dc
		, (int)(m_vFinalPos.x - m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y - m_vScale.y / 2.f)
		, (int)(m_vFinalPos.x + m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y + m_vScale.y / 2.f)
	);

	::SelectObject(_dc, hDefaultPen);
	::SelectObject(_dc, hDefaultBrush);
}