#include "framework.h"
#include "client.h"

HINSTANCE hInst;
HWND g_hWnd;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

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

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
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
//int g_x = 0;
//int g_y = 0;

POINT g_ptObjPos = { 500, 300 };
POINT g_ptObjScale = { 100, 100 };

//new
POINT g_ptLT; // 좌상단
POINT g_ptRB; // 우하단

//new
bool bLbtnDown = false;

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

        HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

        HPEN hOldPen = (HPEN)SelectObject(hdc, hRedPen);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

        //new
        if (bLbtnDown)
        {
            Rectangle(hdc
                , g_ptLT.x , g_ptLT.y
                , g_ptRB.x , g_ptRB.y);
        }

        Rectangle(hdc
            , g_ptObjPos.x - g_ptObjScale.x / 2
            , g_ptObjPos.y - g_ptObjScale.y / 2
            , g_ptObjPos.x + g_ptObjScale.x / 2
            , g_ptObjPos.y + g_ptObjScale.y / 2);

        SelectObject(hdc, hOldPen);
        SelectObject(hdc, hOldBrush);

        DeleteObject(hRedPen);
        DeleteObject(hBlueBrush);

        EndPaint(hWnd, &ps);
    }
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_UP:
            g_ptObjPos.y -= 10;
            break;
        case VK_DOWN:
            g_ptObjPos.y += 10;
            break;
        case VK_LEFT:
            g_ptObjPos.x -= 10;
            break;
        case VK_RIGHT:
            g_ptObjPos.x += 10;
            break;
        }
        InvalidateRect(hWnd, nullptr, true);
    }
        break;
    case WM_LBUTTONDOWN:
    {
        //old
        /*g_x = LOWORD(lParam);
        g_y = HIWORD(lParam);

        HDC hdc = GetDC(hWnd);

        wchar_t szText[256];
        wsprintf(szText, L"Mouse Position: (%d, %d)", g_x, g_y);
        TextOut(hdc, g_x + 10, g_y + 10, szText, lstrlen(szText));

        ReleaseDC(hWnd, hdc);*/
        //new
        g_ptLT.x = LOWORD(lParam);
        g_ptLT.y = HIWORD(lParam);
        bLbtnDown = true;
    }
        break;
    //new
    case WM_MOUSEMOVE:
    {
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);
    }
        break;
    //new
    case WM_LBUTTONUP:
    {
        g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        g_ptObjScale.x = abs(g_ptRB.x - g_ptLT.x);
        g_ptObjScale.y = abs(g_ptRB.y - g_ptLT.y);

        bLbtnDown = false;
        InvalidateRect(hWnd, nullptr, true);
    }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}