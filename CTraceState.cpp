#include "pch.h"
#include "CTraceState.h"
//new
#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTimeMgr.h"

CTraceState::CTraceState()
	: CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::update()
{
	//new
	// Å¸°ÙÆÃ µÈ player ¸¦ ÂÑ¾Æ°£´Ù
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMonPos = GetMonster()->GetPos();

	Vec2 vMonDir = vPlayerPos - vMonPos;
	vMonDir.Normalize();

	vMonPos += vMonDir * GetMonster()->GetInfo().fSpeed * fDT;
	GetMonster()->SetPos(vMonPos);
}

void CTraceState::Enter()
{

}

void CTraceState::Exit()
{

}