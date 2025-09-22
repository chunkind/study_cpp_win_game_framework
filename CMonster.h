#pragma once

#include "CObject.h"

class CTexture;

class CMonster : public CObject
{
private:
    float           m_fSpeed;
    int             m_iHP;
    CTexture*       m_pTex;
    AI*             m_pAI;

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetAI(AI* _AI);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual void update();
    virtual void render(HDC _dc);

    CLONE(CMonster)

public:
    CMonster();
    ~CMonster();
};