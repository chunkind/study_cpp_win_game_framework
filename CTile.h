#pragma once

#include "CObject.h"

class CTile : public CObject
{
private:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(CTile)

public:
	CTile();
	~CTile();

};

