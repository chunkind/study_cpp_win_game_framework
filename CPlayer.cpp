#include "pch.h"
#include "CPlayer.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CGravity.h"

CPlayer::CPlayer()
	: m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_iDir(1)
	, m_iPrevDir(1)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 20.f));
	GetCollider()->SetScale(Vec2(20.f, 20.f));

	CreateRigidBody();

	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link_0.bmp");

	CreateAnimator();

	GetAnimator()->LoadAnimation(L"animation\\player_idle_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_idle_right.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_right.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_jump_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_jump_right.anim");

	/*GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vec2(0.f, 65.f * 1.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(0.f, 65.f * 3.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 65.f * 5.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 65.f * 7.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
	GetAnimator()->CreateAnimation(L"JUMP_LEFT", pTex, Vec2(0.f, 65.f * 4.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
	GetAnimator()->CreateAnimation(L"JUMP_RIGHT", pTex, Vec2(0.f, 65.f * 6.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);*/

	// Animation 저장해보기
	/*GetAnimator()->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player_idle_left.anim");
	GetAnimator()->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player_idle_right.anim");
	GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player_walk_left.anim");
	GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player_walk_right.anim");
	GetAnimator()->FindAnimation(L"JUMP_LEFT")->Save(L"animation\\player_jump_left.anim");
	GetAnimator()->FindAnimation(L"JUMP_RIGHT")->Save(L"animation\\player_jump_right.anim");*/

	CreateGravity();

}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	update_move();

	update_state();

	update_animation();
	
	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2(640.f, 384.f));
	}

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void CPlayer::render(HDC _dc)
{
	component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::update_state()
{
	if (KEY_HOLD(KEY::A))
	{
		m_iDir = -1;
		if (PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}
	if (KEY_HOLD(KEY::D))
	{
		m_iDir = 1;
		if (PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}

	if (0.f == GetRigidBody()->GetSpeed() && PLAYER_STATE::JUMP != m_eCurState)

	{
		m_eCurState = PLAYER_STATE::IDLE;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		m_eCurState = PLAYER_STATE::JUMP;

		if (GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -300.f));
		}
	}
}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-200.f, 0.f));
	}
	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(200.f, 0.f));
	}

	if (KEY_TAP(KEY::A))
	{
		pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
	}
	if (KEY_TAP(KEY::D))
	{
		pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
	}
}

void CPlayer::update_animation()
{
	if (m_ePrevState == m_eCurState && m_iPrevDir == m_iDir)
		return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"IDLE_LEFT", true);
		else
			GetAnimator()->Play(L"IDLE_RIGHT", true);
	}

		break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"WALK_LEFT", true);
		else
			GetAnimator()->Play(L"WALK_RIGHT", true);
	}
		break;
	case PLAYER_STATE::JUMP:
		if (m_iDir == -1)
			GetAnimator()->Play(L"JUMP_LEFT", true);
		else
			GetAnimator()->Play(L"JUMP_RIGHT", true);
		break;
	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DEAD:

		break;
	}
}

void CPlayer::update_gravity()
{
	// 아래 방향으로 힘을 준다.
	GetRigidBody()->AddForce(Vec2(0.f, 500.f));
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == pOtherObj->GetName())
	{
		Vec2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
}