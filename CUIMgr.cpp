#include "pch.h"
#include "CUIMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	// 1. FocusedUI 확인
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	// 2. FocusedUI 내에서, 부모 UI 포함, 자식 UI 들 중 실제 타겟팅 된 UI 를 가져온다.
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);
	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}

			pTargetUI->m_bLbtnDown = false;
		}
	}
}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 UI를 받아두고 변경되었는지 확인 한다.
	CUI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// 왼쪽 버튼 TAP 이 발생했다는 전제
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// 이번에 Focus 된 UI 가 없다.
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	// 백터 내에서 맨 뒤로 순번 교체
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// 1. 부모 UI포함, 모든 자식들을 검사 한다.
	CUI* pTargetUI = nullptr;
	// 자주 사용할거같으니까 정적변수로
	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front(); // 큐에서 먼저들어오면 데이터 하나 가져온다.
		queue.pop_front(); // 가져왔으면 제거

		// 큐에서 꺼내온 UI 가 targetUI 인지 확인
		// 타겟 UI들 중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}

			pTargetUI = pUI;
		}
		else
		{
			// 타겟이 되지 못한애들은 여기로 이동
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	// 최종적으로 타겟이 되지 않은 애들만
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}