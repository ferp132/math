// Solitare.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Solitare.h"
#include "Canvas.h"
#include "Card.h"
#include "BackBuffer.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//-----My Defined Enums
enum SUIT
{
	CLUBS		= 0,
	DIAMONDS	= 1,
	HEARTS		= 2,
	SPADES		= 3
	
};

enum CARDNAME
{
	ACE		= 0,
	TWO		= 1,
	THREE	= 2,
	FOUR	= 3,
	FIVE	= 4,
	SIX		= 5,
	SEVEN	= 6,
	EIGHT	= 7,
	NINE	= 8,
	TEN		= 9,
	JACK	= 10,
	QUEEN	= 11,
	KING	= 12
};

//-----My Defined Variables
CCanvas*	GlobalCanvasPointer = nullptr;
Card*		GlobalShapePointer = nullptr;
RECT rect;

int		MousePositionX;
int		MousePositionY;
bool	PickingUp = false;
bool	MoveBack = false;

//Main Game Loop Where Draw Gets Called
void GameLoop()
{
	if (GlobalCanvasPointer != nullptr)
	{
		if (MoveBack && !PickingUp)
		{
			MoveBack = false;

			if ((GlobalShapePointer->GetLastPositionX() - GlobalShapePointer->GetStartX() > 10 || GlobalShapePointer->GetLastPositionX() - GlobalShapePointer->GetStartX() < -10))	//if X is not within 10 pixels of its last position
			{
				MoveBack = true;
				GlobalShapePointer->SetStartX(GlobalShapePointer->GetStartX() + (GlobalShapePointer->GetLastPositionX() - GlobalShapePointer->GetStartX())/25);						//Move Back To it
			}
			else GlobalShapePointer->SetStartX(GlobalShapePointer->GetLastPositionX());																								//If you're really close, move to it

			if ((GlobalShapePointer->GetLastPositionY() - GlobalShapePointer->GetStartY() > 10 || GlobalShapePointer->GetLastPositionY() - GlobalShapePointer->GetStartY() < -10))	//Same For y
			{
				MoveBack = true;
				GlobalShapePointer->SetStartY(GlobalShapePointer->GetStartY() + (GlobalShapePointer->GetLastPositionY() - GlobalShapePointer->GetStartY()) / 25);
			}
			else GlobalShapePointer->SetStartY(GlobalShapePointer->GetLastPositionY());
				
		}

		GlobalCanvasPointer->Draw();
	}
}

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
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
    LoadStringW(hInstance, IDC_SOLITARE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOLITARE));

    MSG msg;

    //// Main message loop:
    //while (GetMessage(&msg, nullptr, 0, 0))
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //}

	// Enter main event loop
	while (true)
	{
		// Test if there is a message in queue, if so get it.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Test if this is a quit.
			if (msg.message == WM_QUIT)
			{
				break;
			}

			// Translate any accelerator keys.
			TranslateMessage(&msg);
			// Send the message to the window proc.
			DispatchMessage(&msg);
		}
		GameLoop();
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOLITARE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SOLITARE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
      CW_USEDEFAULT, 0, 1600, 900, nullptr, nullptr, hInstance, nullptr);

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
//  PURPOSE:  Processes messages for the main window.
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
		//initialisation of canvas
		GlobalCanvasPointer = new CCanvas();
		GetClientRect(hWnd, &rect);
		GlobalCanvasPointer->Initialise(hWnd, 1200, 1000);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		MousePositionX = static_cast<int>(LOWORD(lParam));			// find the pointer location
		MousePositionY = static_cast<int>(HIWORD(lParam));

		if (GlobalShapePointer == nullptr)
		{
			GlobalShapePointer = new Card(KING, HEARTS, MousePositionX, MousePositionY);
			GlobalCanvasPointer->AddCard(GlobalShapePointer);
		}
		else if (GlobalShapePointer != nullptr)
		{
			if (MousePositionX > GlobalShapePointer->GetStartX() && MousePositionX < GlobalShapePointer->GetEndX() && MousePositionY > GlobalShapePointer->GetStartY() && MousePositionY < GlobalShapePointer->GetEndY())
			{
				PickingUp = true;
				GlobalShapePointer->SetPickUpWidth(MousePositionX - GlobalShapePointer->GetStartX());
				GlobalShapePointer->SetPickUpHeight(MousePositionY - GlobalShapePointer->GetStartY());
			}
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		if (PickingUp)
		{
			PickingUp = false;
			GlobalShapePointer->SetPickUpWidth(0);
			GlobalShapePointer->SetPickUpHeight(0);

			if (GlobalShapePointer->GetStartX() != GlobalShapePointer->GetLastPositionX() && GlobalShapePointer->GetStartY() != GlobalShapePointer->GetLastPositionY())
			{
				MoveBack = true;
			}
		}
		break;
	}
	case WM_RBUTTONDOWN:
	{

		break;
	}
	case WM_MOUSEMOVE:
	{
		MousePositionX = static_cast<int>(LOWORD(lParam));			// find the pointer location
		MousePositionY = static_cast<int>(HIWORD(lParam));

		if (PickingUp)
		{	
			GlobalShapePointer->SetStartX(MousePositionX - GlobalShapePointer->GetPickUpWidth());
			GlobalShapePointer->SetStartY(MousePositionY - GlobalShapePointer->GetPickUpHeight());
		}
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
