// 03.11.2022.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "03.11.2022.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name



// получаем дескриптор приложения
HINSTANCE hInstance = GetModuleHandle(0);
// загружаем курсоры из ресурсов приложения
HCURSOR hCursor1 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
HCURSOR hCursor2 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
HCURSOR hCursor3 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR3));

RECT rRect;
int iX;
int iY;
TCHAR tcStr[100];
int in = 0;
int on = 0;
int out = 0;




// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY03112022, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY03112022));

    MSG msg;

    // Main message loop:
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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
    wcex.hCursor        = NULL;
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_MOUSEMOVE:
    {
        GetClientRect(hWnd, &rRect);
        iX = LOWORD(lParam);
        iY = HIWORD(lParam);
        if (iX > (rRect.left + 100) && iY > (rRect.top + 100) &&
            iX < (rRect.right - 100) && iY < (rRect.bottom - 100))
        {
            SetCursor(hCursor1);
        }
        else if (iX < (rRect.left + 100) || iY < (rRect.top + 100) ||
            iX >(rRect.right - 100) || iY >(rRect.bottom - 100))
        {
            SetCursor(hCursor2);
        }
        else
            SetCursor(hCursor3);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        GetClientRect(hWnd, &rRect);
        iX = LOWORD(lParam);
        iY = HIWORD(lParam);
        if (iX > (rRect.left + 100) && iY > (rRect.top + 100) &&
            iX < (rRect.right - 100) && iY < (rRect.bottom - 100))
        {
            in++;
        }
        else if (iX < (rRect.left + 100) || iY < (rRect.top + 100) ||
            iX > (rRect.right - 100) || iY >(rRect.bottom - 100))
        {
            out++;
        }
        else
            on++;
        wsprintf(tcStr, _TEXT("in: %d; on: %d; out: %d"), in, on, out);
        MessageBox(0, tcStr, TEXT("Clicked"), MB_OK | MB_ICONINFORMATION);
    }

    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
