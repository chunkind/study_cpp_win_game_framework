#pragma once

#include "CUI.h"

class CPanelUI : public CUI
{
private:
	Vec2 m_vDragStart;

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();

public:
	CPanelUI();
	~CPanelUI();


};