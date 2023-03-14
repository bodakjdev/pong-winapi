// pigegraded1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "pigegraded1.h"
#include "commdlg.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR szBallClass[MAX_LOADSTRING]=L"IDS_BALL";
WCHAR szPaddleClass[MAX_LOADSTRING] = L"IDS_PADDLE";
HWND hWnd, hBall, hPaddle;
int xpos = 80, ypos = 100, counter = 0;
bool xdirection=1, ydirection=0,work=1,bgtype=1;
int screenheight = GetSystemMetrics(1);
int screenwidth = GetSystemMetrics(0);
LPTSTR bitmap;
TCHAR szFile[260] = { 0 };
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
ATOM                MyBallRegisterClass(HINSTANCE hInstance);
ATOM                MyPaddleRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    BallProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    PaddleProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ColorDlgProc(HWND, UINT, WPARAM , LPARAM );
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


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
    LoadStringW(hInstance, IDC_PIGEGRADED1, szWindowClass, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDS_BALL, szBallClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    MyBallRegisterClass(hInstance);
    MyPaddleRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PIGEGRADED1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PIGEGRADED1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(CreateSolidBrush(RGB(250, 250, 10)));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PIGEGRADED1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

ATOM MyBallRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = BallProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = NULL;
    wcex.hCursor = NULL;
    wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(250, 0, 0)));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szBallClass;
    wcex.hIconSm = NULL;

    return RegisterClassExW(&wcex);
}

ATOM MyPaddleRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = PaddleProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = NULL;
    wcex.hCursor = NULL;
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW-1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szPaddleClass;
    wcex.hIconSm = NULL;

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
   RECT rc;
   
   HRGN region = CreateEllipticRgn(0, 0, 20, 20);
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED &~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX | WS_SYSMENU,
       screenwidth / 2 - 100, screenheight / 2 - 150, screenwidth, screenheight, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }
   SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);//changes window style to a layered window
   SetLayeredWindowAttributes(hWnd, 0, (255 * 80) / 100, LWA_ALPHA);//sets the 50% transparency
   //MoveWindow(hWnd, screenwidth / 2 - 100, screenheight / 2 - 150, screenwidth, screenheight, 0);
   
   
   hBall = CreateWindowW(szBallClass, L"pilka", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
       80, 120, 20, 20, hWnd, nullptr, hInst, nullptr);
   if (!hBall)
   {
       return FALSE;
   }
   SetWindowRgn(hBall, region, true);

   hPaddle = CreateWindowW(szPaddleClass, L"paleta", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
       80, 231, 50, 10, hWnd, nullptr, hInst, nullptr);
   if (!hPaddle)
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
    case WM_CREATE:
    { 
    }
    break;
    case WM_GETMINMAXINFO:
    {
        MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
        minMaxInfo->ptMaxSize.x = minMaxInfo->ptMaxTrackSize.x = 200;
        minMaxInfo->ptMaxSize.y = minMaxInfo->ptMaxTrackSize.y = 300;
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case ID_FILE_NEWGAME:
            {
                RECT rc;
                counter = 0;
                work = 1;
                xpos = 80, ypos = 100;
                xdirection = 1, ydirection = 0;
                InvalidateRect(hPaddle, NULL, 1);
                MoveWindow(hBall, xpos, ypos, 20, 20,1);
            }
            break;
            case ID_BACKGROUND_COLOR://https://cpp0x.pl/kursy/Kurs-WinAPI-C++/Podstawy/Okna-dialogowe-cz-4/187
            {
                CHOOSECOLOR ccl;
                COLORREF TabKol[16];
                BOOL bResult;

                ZeroMemory(&ccl, sizeof(CHOOSECOLOR));
                ccl.lStructSize = sizeof(CHOOSECOLOR);
                ccl.hwndOwner = hWnd;
                ccl.lpCustColors = TabKol;
                ccl.Flags = CC_ANYCOLOR;
                bResult = ChooseColor(&ccl);
                HBRUSH brush = CreateSolidBrush(ccl.rgbResult);
                SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)brush);
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
            case ID_BITMAP_UPLOAD://https://cpp0x.pl/kursy/Kurs-WinAPI-C++/Podstawy/Okna-dialogowe-cz-3/186
            {
                OPENFILENAME ofn;
                ZeroMemory(&ofn, sizeof(OPENFILENAME));
                ofn.lStructSize = sizeof(ofn);
                ofn.lpstrFile = szFile;
                ofn.nMaxFile = 260;
                ofn.hwndOwner = hWnd;
                ofn.lpstrFilter = _T("Bitmapy (*.bmp)\0*.bmp");
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                ofn.lpstrDefExt = _T("bmp");
                // jeœli otwieramy plik do odczytu...
                GetOpenFileName(&ofn);
                // ...lub GetSaveFileName (&ofn), jeœli zapisujemy
                //SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, ()
                HANDLE bit = LoadImage(NULL, szFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                HBRUSH brush = CreatePatternBrush((HBITMAP)bit);
                SetClassLong(hWnd, GCLP_HBRBACKGROUND, (LONG)brush);
                InvalidateRect(hWnd, NULL, TRUE);
                EnableMenuItem(GetMenu(hWnd), ID_BITMAP_TILE, MF_ENABLED);
                CheckMenuItem(GetMenu(hWnd), ID_BITMAP_TILE, MF_CHECKED);
                EnableMenuItem(GetMenu(hWnd), ID_BITMAP_STRETCHED, MF_ENABLED);
            }
            break;
            case ID_BITMAP_TILE:
            {
                bgtype = 1;
                HANDLE bit = LoadImage(NULL, szFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                HBRUSH brush = CreatePatternBrush((HBITMAP)bit);
                SetClassLong(hWnd, GCLP_HBRBACKGROUND, (LONG)brush);
                CheckMenuItem(GetMenu(hWnd), ID_BITMAP_TILE, MF_CHECKED);
                CheckMenuItem(GetMenu(hWnd), ID_BITMAP_STRETCHED, MF_UNCHECKED);
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
            case ID_BITMAP_STRETCHED:
            {
                bgtype = 0;
                CheckMenuItem(GetMenu(hWnd), ID_BITMAP_STRETCHED, MF_CHECKED);
                CheckMenuItem(GetMenu(hWnd), ID_BITMAP_TILE, MF_UNCHECKED);
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
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
            // TODO: Add any drawing code that uses hdc here...
            if (bgtype == 0) {
                HANDLE bit = LoadImage(NULL,szFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
                HBRUSH brush = CreatePatternBrush((HBITMAP)bit);
                HDC memDC = CreateCompatibleDC(hdc);//from tutorial
                HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, bit);
                BitBlt(hdc, 0, 0, 48, 48, memDC, 0, 0, SRCCOPY);
                StretchBlt(hdc, 0, 0, 200, 280, memDC,0, 0, 48, 48, SRCCOPY);
                SelectObject(memDC, oldBitmap);
                DeleteObject(bit);
                DeleteDC(memDC);
            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_MOUSEMOVE:
    {
        if (work) {
            RECT rc;
            GetClientRect(hWnd, &rc);
            short x = (short)LOWORD(lParam);
            short y = (short)HIWORD(lParam);
            if (x > rc.right - 50)
                x = rc.right - 50;
            MoveWindow(hPaddle, x, 231, 50, 10, TRUE);
        }
        
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

LRESULT CALLBACK BallProc(HWND HWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        SetTimer(HWnd, 1, 50, NULL);
    }
    break;
    case WM_TIMER:
    {
        if (wParam == 1 && work==1) // check timer id
        {
            
            RECT rc, rcc,rcp;
            GetWindowRect(HWnd, &rc);
            GetWindowRect(hPaddle, &rcp);
            GetClientRect(hWnd, &rcc);
            if (rc.right > rcc.right/2+screenwidth/2) {
                xdirection = 0;
            }
            else if (rc.left < screenwidth/2 - rcc.right/2) {
                xdirection = 1;
            }
            if (rc.top < screenheight/2-(rcc.bottom / 2-22)) {
                ydirection = 1;
            }
            else if (rc.bottom > screenheight/2+(rcc.bottom/2)+13) {
                if ((rc.right + rc.left) / 2 < rcp.left || (rc.right + rc.left) / 2 > rcp.right) {

                    work = 0;
                }
                else {
                    counter++;
                    InvalidateRect(hPaddle, NULL, NULL);
                }
                ydirection = 0;
            }
            if (xdirection) {
                xpos += 3;
            }
            else {
                xpos -= 3;
            }
            if (ydirection) {
                ypos += 3;
            }
            else {
                ypos -= 3;
            }
            MoveWindow(HWnd, xpos, ypos, 20, 20,1);
        }
    }
    break;
    case WM_COMMAND:
    {
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(HWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(HWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(HWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK PaddleProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
    }
    break;
    case WM_COMMAND:
    {
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        TCHAR s[10];
        swprintf_s(s, L"%d", counter);
        RECT rc;
        GetClientRect(hWnd, &rc);
        SetBkMode(hdc,TRANSPARENT);
        DrawText(hdc, s, (int)_tcslen(s), &rc,
            DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        
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

//BOOL CALLBACK ColorDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)//https://cpp0x.pl/kursy/Kurs-WinAPI-C++/167?fbclid=IwAR32lwCdictjyqOIj2PDnfZpmVInZ2tF2Wu-8S2EbRhx38GKmSYBTj_zMrY
//{
//    switch (message)
//    {
//    case WM_INITDIALOG:
//    {
//    }
//    break;
//    case WM_COMMAND:
//    {
//        // reakcja na przyciski
//        switch (LOWORD(wParam))
//        {
//        case IDOK: EndDialog(hWnd, IDOK); break;
//        case IDCANCEL: EndDialog(hWnd, IDCANCEL); break;
//        }
//    }
//    break;
//    default: return FALSE;
//    }
//    return TRUE;
//}
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
