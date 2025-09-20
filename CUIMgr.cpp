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

		// �θ� UI ����, �ڽ� UI �� �� ���� Ÿ���� �� UI�� �����´�.
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

				// ���ʹ�ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
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

		//		// ���ʹ�ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
		//		pUI->m_bLbtnDown = false;
		//	}
		//}
		//else
		//{
		//	// ���� ��ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
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

	// 1. �θ� UI����, ��� �ڽĵ��� �˻� �Ѵ�.
	CUI* pTargetUI = nullptr;
	// ���� ����ҰŰ����ϱ� ����������
	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front(); // ť���� ���������� ������ �ϳ� �����´�.
		queue.pop_front(); // ���������� ����

		// ť���� ������ UI �� targetUI ���� Ȯ��
		// Ÿ�� UI�� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ� UI
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
			// Ÿ���� ���� ���Ѿֵ��� ����� �̵�
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	// ���������� Ÿ���� ���� ���� �ֵ鸸
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}