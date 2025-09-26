#include "framework.h"
#include "client.h"

HINSTANCE hInst;

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

   HWND hWnd = CreateWindowW(L"WinApi", L"Client", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//new
// 포지션이 x:500, y:300, 크기가 가로 100, 세로 100
POINT g_ptObjPos = { 500, 300 };
POINT g_ptObjScale = { 100, 100 };

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
            //Rectangle(hdc, 10, 10, 110, 110);
            //new
            // 직접 펜과 브러쉬를 만들어 DC에 적용
            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // 빨간팬
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255)); // 파란 백그라운드색

            //new
            // 새로만든 펜과 브러쉬를 현재 hdc에 적용
            // 리턴값은 이전에 사용했던 기본 펜과 기본 브러쉬를 리턴함.
            HPEN hOldPen = (HPEN)SelectObject(hdc, hRedPen);
            HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

            //new
            // 사각형을 그리면 새로만든 빨간색 팬과 파란색 브러쉬를 이용하여 그려진다.
            Rectangle(hdc
                , g_ptObjPos.x - g_ptObjScale.x / 2
                , g_ptObjPos.y - g_ptObjScale.y / 2
                , g_ptObjPos.x + g_ptObjScale.x / 2
                , g_ptObjPos.y + g_ptObjScale.y / 2);

            //new
            // DC의 펜과 브러쉬를 원래 것으로 되돌림
            SelectObject(hdc, hOldPen);
            SelectObject(hdc, hOldBrush);

            EndPaint(hWnd, &ps);
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