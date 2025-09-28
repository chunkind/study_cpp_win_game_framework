#include "framework.h"
#include "client.h"

HINSTANCE hInst;
HWND g_hWnd;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

//old
//int count = 0;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    //old
    /*DWORD dwPrevCount = GetTickCount();
    DWORD dwAccCount = 0;*/

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            //old
            //int iTime = GetTickCount();

            if (WM_QUIT == msg.message)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);

            //old
            //dwAccCount += (GetTickCount() - iTime);
        }
        else
        {
            //old
            /*DWORD dwCurCount = GetTickCount();
            if (dwCurCount - dwPrevCount > 1000)
            {
                float fRatio = (float)dwAccCount / 1000.f;

                wchar_t szBuff[50] = {};

                swprintf_s(szBuff, L"비율 : %f", fRatio);
                SetWindowText(g_hWnd, szBuff);

                dwPrevCount = dwCurCount;
                dwAccCount = 0;
            }*/
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = L"WinApi";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    g_hWnd = CreateWindowW(L"WinApi", L"Client", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!g_hWnd)

    {
        return FALSE;
    }

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

    return TRUE;
}

//old
//#include <vector>
//using std::vector;
//
//struct tObjInfo
//{
//    POINT g_ptObjPos;
//    POINT g_ptObjScale;
//};
//
//vector<tObjInfo> g_vecInfo;
//
//POINT g_ptLT;
//POINT g_ptRB;
//
//bool bLbtnDown = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        //old
        /*HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

        HPEN hOldPen = (HPEN)SelectObject(hdc, hRedPen);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

        if (bLbtnDown)
        {
            Rectangle(hdc
                , g_ptLT.x , g_ptLT.y
                , g_ptRB.x , g_ptRB.y);
        }

        for (size_t i = 0; i < g_vecInfo.size(); ++i)
        {
            Rectangle(hdc
                , g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x / 2
                , g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2
                , g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2
                , g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2
            );
        }

        SelectObject(hdc, hOldPen);
        SelectObject(hdc, hOldBrush);

        DeleteObject(hRedPen);
        DeleteObject(hBlueBrush);*/

        EndPaint(hWnd, &ps);
    }
        break;
    case WM_KEYDOWN:
    //old
    /*{
        switch (wParam)
        {
        case VK_UP:
            break;
        case VK_DOWN:
            break;
        case VK_LEFT:
            break;
        case VK_RIGHT:
            break;
        }
    }*/
        break;
    case WM_LBUTTONDOWN:
    //old
    /*{
        g_ptLT.x = LOWORD(lParam);
        g_ptLT.y = HIWORD(lParam);
        bLbtnDown = true;
    }*/
        break;
    case WM_MOUSEMOVE:
    //old
    /*{
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
    }*/
        break;
    case WM_LBUTTONUP:
    //old
    /*{
        tObjInfo info = {};
        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;
        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);

        bLbtnDown = false;
    }*/
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}