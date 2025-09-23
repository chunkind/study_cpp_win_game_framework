#pragma once

#include "CMonFactory.h"

class CObject;

class CScene
{
protected:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName;

	UINT				m_iTileX; // 타일 가로 개수
	UINT				m_iTileY; // 타일 세로 개수

	//new
	CObject*			m_pPlayer;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	//new
	CObject* GetPlayer() { return m_pPlayer; }

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void render_tile(HDC _dc);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }
	//new
	void RegisterPlayer(CObject* _pPlayer) { m_pPlayer = _pPlayer; }

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

public:
	CScene();
	virtual ~CScene();
};