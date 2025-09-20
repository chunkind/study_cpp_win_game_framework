#include "pch.h"
#include "CUIMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyMgr.h"

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		// 부모 UI 포함, 자식 UI 들 중 실제 타겟팅 된 UI를 가져온다.
		pUI = GetTargetedUI(pUI);

		if (nullptr != pUI)
		{
			pUI->MouseOn();

			if (bLbtnTap)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if (bLbtnAway)
			{
				pUI->MouseLbtnUp();

				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}

				// 왼쪽버튼 떼면, 눌렸던 체크를 다시 해제한다.
				pUI->m_bLbtnDown = false;
			}
		}

		//if (pUI->IsMouseOn())
		//{
		//	pUI->MouseOn();

		//	if (bLbtnTap)
		//	{
		//		pUI->MouseLbtnDown();
		//		pUI->m_bLbtnDown = true;
		//	}
		//	else if (bLbtnAway)
		//	{
		//		pUI->MouseLbtnUp();

		//		if (pUI->m_bLbtnDown)
		//		{
		//			pUI->MouseLbtnClicked();
		//		}

		//		// 왼쪽버튼 떼면, 눌렸던 체크를 다시 해제한다.
		//		pUI->m_bLbtnDown = false;
		//	}
		//}
		//else
		//{
		//	// 왼쪽 버튼 떼면, 눌렸던 체크를 다시 해제한다.
		//	if (bLbtnAway)
		//	{
		//		pUI->m_bLbtnDown = false;
		//	}
		//}
	}
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