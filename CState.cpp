#include "pch.h"
#include "CState.h"
//new
#include "CMonster.h"
#include "AI.h"

CState::CState(MON_STATE _eState)
	: m_eState(_eState)
{
}

CState::~CState()
{
}

//new
CMonster* CState::GetMonster()
{
	return m_pAI->GetOwner();
}