#pragma once

#include "CObject.h"

enum class PLAYER_STATE
{
    IDLE,
    WALK,
    ATTACK,
    DEAD,
};

enum class PLAYER_ATTACK_STATE
{
    NORMAL_ATT_1,
    NORMAL_ATT_2,
    NORMAL_ATT_3,

    SKILL_ATT_1,
    // ...
};

class CTexture;

class CPlayer : public CObject
{
private:
    vector<CObject*>    m_vecColObj;

    PLAYER_STATE        m_eCurState; // 현재 상태
    PLAYER_STATE        m_ePrevState; // 이전 상태
    int                 m_iDir;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();
    void update_state();
    void update_move();
    void update_animation();

    CLONE(CPlayer)

public:
    CPlayer();
    ~CPlayer();
};