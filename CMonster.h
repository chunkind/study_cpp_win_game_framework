#pragma once

#include "CObject.h"

struct tMonInfo
{
    float fSpeed; // 속도
    float fHP; // 체력
    float fRecogRange; // 인지 범위
    float fAttRange; // 공격 범위
    float fAtt; // 공격력
};

class AI;
class CTexture;

class CMonster : public CObject
{
private:
    tMonInfo        m_tInfo;

    CTexture*       m_pTex;
    AI*             m_pAI;

public:
    float GetSpeed() { return m_tInfo.fSpeed; }
    void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
    void SetAI(AI* _AI);

private:
    void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual void update();
    virtual void render(HDC _dc);

    CLONE(CMonster)

public:
    CMonster();
    ~CMonster();

    friend class CMonFactory;
};