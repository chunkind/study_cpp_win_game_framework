#pragma once

#include "CObject.h"

class CTexture;

class CPlayer : public CObject
{
private:
    CTexture* m_pTex;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();

    CPlayer* Clone() { return new CPlayer(*this); }

public:
    CPlayer();
    CPlayer(const CPlayer& _origin)
        : CObject(_origin)
        , m_pTex(_origin.m_pTex)
    {

    }
    ~CPlayer();
};