#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera)

private:
	Vec2 m_vLookAt;
	CObject* m_pTargetObj;

	Vec2 m_vDiff;

public:
	void SetLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

public:
	void update();

private:
	void CalDiff();
};