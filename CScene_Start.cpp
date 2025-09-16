#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::DEFAULT);

	CMonster* pMonsterObj = new CMonster;
	pMonsterObj->SetPos(Vec2(640.f, 50.f));
	pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
	pMonsterObj->SetScale(Vec2(50.f, 50.f));
	AddObject(pMonsterObj, GROUP_TYPE::DEFAULT);
}

void CScene_Start::Exit()
{

}