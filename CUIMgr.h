#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr)

private:
	CUI* m_pFocusedUI;

public:
	void update();

private:
	CUI* GetFocusedUI();

private:
	CUI* GetTargetedUI(CUI* _pParentUI); // �θ� UI ������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ.
};