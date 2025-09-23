#include "pch.h"
#include "CIdleState.h"
//new
#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"

CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	//new
	// Player�� ��ġ üũ
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	//new
	// ������ ���� �ȿ� ������ �������·� ��ȯ
	CMonster* pMonster = GetMonster();
	Vec2 vMonPos = pMonster->GetPos();

	//new
	Vec2 vDiff = vPlayerPos - vMonPos;
	float fLen = vDiff.Length();

	//new
	// �÷��̾ ������ �νĹ��� ������ ����
	if (fLen < pMonster->GetInfo().fRecogRange)
	{
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}
}

void CIdleState::Enter()
{

}

void CIdleState::Exit()
{

}