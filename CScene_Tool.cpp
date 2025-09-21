#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CScene.h"
#include "resource.h"
#include "CUIMgr.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
    : m_pUI(nullptr)
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
    pPanelUI->SetScale(Vec2(300.f, 150.f));
    pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

    // 자식 UI
    CUI* pBtnUI = new CBtnUI;
    pBtnUI->SetName(L"ChildUI");
    pBtnUI->SetScale(Vec2(100.f, 40.f));
    pBtnUI->SetPos(Vec2(0.f, 0.f));
    ((CBtnUI*)pBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SaveTileData);
    pPanelUI->AddChild(pBtnUI);

    // UI 씬에 올리기
    AddObject(pPanelUI, GROUP_TYPE::UI);

	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
    DeleteAll();
}

void CScene_Tool::update()
{
	CScene::update();

    SetTileIdx();

    if (KEY_TAP(KEY::CTRL))
    {
        LoadTileData();
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

void CScene_Tool::SaveTileData()
{
    wchar_t szName[256] = {};

    OPENFILENAME ofn = {};

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
    ofn.lpstrFile = szName;
    ofn.nMaxFile = sizeof(szName);
    ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
    ofn.nFileExtension = 0;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;

    wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
    strTileFolder += L"tile";

    ofn.lpstrInitialDir = strTileFolder.c_str();
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Modal
    if (GetSaveFileName(&ofn))
    {
        // 확인 눌렀을때
        SaveTile(szName);
    }

    
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
    FILE* pFile = nullptr;

    // 쓰기 모드의 특징은 지정한 경로에 파일이 없으면 만들어버린다.
    _wfopen_s(&pFile, _strFilePath.c_str(), L"wb");

    assert(pFile);

    // 타일 가로세로 개수 저장
    UINT xCount = GetTileX();
    UINT yCount = GetTileY();

    fwrite(&xCount, sizeof(UINT), 1, pFile);
    fwrite(&yCount, sizeof(UINT), 1, pFile);

    // 모든 타일들을 개별적으로 저장할 데이터를 저장하게 함
    const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

    for (size_t i = 0; i < vecTile.size(); ++i)
    {
        ((CTile*)vecTile[i])->Save(pFile);
    }

    fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
    wchar_t szName[256] = {};

    OPENFILENAME ofn = {};

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
    ofn.lpstrFile = szName;
    ofn.nMaxFile = sizeof(szName);
    ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
    ofn.nFileExtension = 0;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;

    wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
    strTileFolder += L"tile";

    ofn.lpstrInitialDir = strTileFolder.c_str();
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Modal
    if (GetOpenFileName(&ofn)) // 확인 눌렀을때
    {
        wstring strRelativePath = CPathMgr::GetInst()->GetRelativepath(szName); // 상대경로 얻기
        LoadTile(strRelativePath);
    }
}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
    ChangeScene(SCENE_TYPE::START);
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