#include "pch.h"
#include "CUI.h"

CUI::CUI()
{

}

CUI::~CUI()
{

}

void CUI::update()
{

}

void CUI::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));
}