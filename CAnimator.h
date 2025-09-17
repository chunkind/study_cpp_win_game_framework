#pragma once

class CObject;
class CAnimation;

class CAnimator
{
private:
	map<wstring, CAnimation*> m_mapAnim;
	CAnimation* m_pCurAnim;
	CObject* m_pOwner;

public:
	void CreateAnimation();
	void FindAnimation();
	void Play();

	void update();
	void render(HDC _dc);

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};