#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "resource.h"
#include "CUIMgr.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
	CreateTile(5, 5);

	Vec2 vResolution = CCore::GetInst()->GetResolution();

    // 메인 UI
    CUI* pPanelUI = new CPanelUI;
    pPanelUI->SetName(L"ParentUI");
    pPanelUI->SetScale(Vec2(500.f, 300.f));
    pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

    // 자식 UI
    CUI* pBtnUI = new CBtnUI;
    pBtnUI->SetName(L"ChildUI");
    pBtnUI->SetScale(Vec2(100.f, 40.f));
    pBtnUI->SetPos(Vec2(0.f, 0.f));
    pPanelUI->AddChild(pBtnUI);

    // UI 씬에 올리기
    AddObject(pPanelUI, GROUP_TYPE::UI);

    // 복사 UI
    CUI* pClonePanel = pPanelUI->Clone();
    pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));

    // UI 씬에 올리기
    AddObject(pClonePanel, GROUP_TYPE::UI);

    m_pUI = pClonePanel;

	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{

}

void CScene_Tool::update()
{
	CScene::update();

    SetTileIdx();

    if (KEY_TAP(KEY::LSHIFT))
    {
        CUIMgr::GetInst()->SetFocusedUI(m_pUI);
    }
}

void CScene_Tool::SetTileIdx()
{
    if (KEY_TAP(KEY::LBTN))
    {
        Vec2 vMousePos = MOUSE_POS;
        vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

        int iTileX = (int)GetTileX();
        int iTileY = (int)GetTileY();

        int iCol = (int)vMousePos.x / TILE_SIZE;
        int iRow = (int)vMousePos.y / TILE_SIZE;

        if (vMousePos.x < 0 || iTileX <= iCol
            || vMousePos.y < 0.f || iTileY <= iRow)
        {
            return;
        }

        UINT iIdx = iRow * iTileX + iCol;

        const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
        ((CTile*)vecTile[iIdx])->AddImgIdx();
    }
}

// ======================
// Tile Count Window Proc
// ======================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            // GetDlgItemInt(대화상자 핸들, 컨트롤 ID, 변환 성공 여부를 받을 포인터, 부호 있는 정수로 변환할지 여부)
            UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
            UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

            CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

            CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
            assert(pToolScene);

            pToolScene->DeleteGroup(GROUP_TYPE::TILE);
            pToolScene->CreateTile(iXCount, iYCount);

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }

        break;
	}
	return (INT_PTR)FALSE;
}