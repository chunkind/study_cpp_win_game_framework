#pragma once

class CObject
{
//old
//public:
//	POINT	m_ptPos;
//	POINT	m_ptScale;
//new
private:
	Vec2	m_vPos;
	Vec2	m_vScale;

//new
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	//new
	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	CObject();
	~CObject();
};