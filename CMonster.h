#pragma once

#include "CObject.h"

struct tMonInfo
{
    float fSpeed; // �ӵ�
    float fHP; // ü��
    float fRecogRange; // ���� ����
    float fAttRange; // ���� ����
    float fAtt; // ���ݷ�
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