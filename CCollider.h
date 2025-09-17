#pragma once

class CObject;

class CCollider
{
private:
	CObject* m_pOwner;

	friend class CObject;
};