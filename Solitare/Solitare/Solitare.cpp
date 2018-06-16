// Solitare.cpp : Defines the entry point for the application.

#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "stdafx.h"
#include "Solitare.h"
#include "Canvas.h"
#include "Card.h"
#include "BackBuffer.h"
#include "Stack.h"
using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


//-----My Defined Variables
CCanvas*	GlobalCanvasPointer = nullptr;
Card*		GlobalCardPointer = nullptr;
RECT rect;
	//Stacks;
Stack*		GlobalStackPointer = nullptr;
Stack*		Stack1Pointer = nullptr;
Stack*		Stack2Pointer = nullptr;
Stack*		Stack3Pointer = nullptr;
Stack*		Stack4Pointer = nullptr;
Stack*		Stack5Pointer = nullptr;
Stack*		Stack6Pointer = nullptr;
Stack*		Stack7Pointer = nullptr;





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

			if ((GlobalCardPointer->GetLastPositionX() - GlobalCardPointer->GetStartX() > 20 || GlobalCardPointer->GetLastPositionX() - GlobalCardPointer->GetStartX() < -20))	//if X is not within 10 pixels of its last position
			{
				MoveBack = true;
				GlobalCardPointer->SetStartX(GlobalCardPointer->GetStartX() + (GlobalCardPointer->GetLastPositionX() - GlobalCardPointer->GetStartX()) / 20);						//Move Back To it
			}
			else GlobalCardPointer->SetStartX(GlobalCardPointer->GetLastPositionX());																								//If you're really close, move to it

			if ((GlobalCardPointer->GetLastPositionY() - GlobalCardPointer->GetStartY() > 20 || GlobalCardPointer->GetLastPositionY() - GlobalCardPointer->GetStartY() < -20))	//Same For y
			{
				MoveBack = true;
				GlobalCardPointer->SetStartY(GlobalCardPointer->GetStartY() + (GlobalCardPointer->GetLastPositionY() - GlobalCardPointer->GetStartY()) / 20);
			}
			else GlobalCardPointer->SetStartY(GlobalCardPointer->GetLastPositionY());
				
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
		//Initialize random seed
		srand(time(NULL));

		//-----Initialization of canvas
		GlobalCanvasPointer = new CCanvas();
		GetClientRect(hWnd, &rect);
		GlobalCanvasPointer->Initialise(hWnd, 1200, 1000);

		//-----Initialization of Stacks
		Stack1Pointer = new Stack(500, 100); 
		Stack2Pointer = new Stack(700, 100);

		//-----Initializing Cards
		Card* CardArray[52];

		for (int Suit = 0; Suit < 4; Suit++)
		{
			for (int Value = 0; Value < 13; Value++)
			{
				GlobalCardPointer = new Card(Suit, Suit, MousePositionX, MousePositionY, false);
				CardArray[Suit + Value] = GlobalCardPointer;
			}
		}

		for (int Cards = 0; Cards < 52; Cards++)
		{
			int CardToPick;
			CardToPick = rand() % 52;
			
			while (CardArray[CardToPick] != nullptr)
			{
				CardToPick = rand() % 52;
			}

			// TODO Add Cards To deck (queue or deque, not sure yet) 
			//Add CardArray[CardToPick] To deck
			//Move appropriate number of cards to the seven stacks


		}
		

		// TODO Add More Stacks
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		MousePositionX = static_cast<int>(LOWORD(lParam));			// find the pointer location
		MousePositionY = static_cast<int>(HIWORD(lParam));

		if (MousePositionX > Stack1Pointer->GetStackXPosition() && MousePositionX < Stack1Pointer->GetStackXPosition() + 140)
		{
			GlobalCardPointer = Stack1Pointer->Peek();
		}


		if (GlobalCardPointer != nullptr)
		{
			//if (MousePositionX > GlobalCardPointer->GetStartX() && MousePositionX < GlobalCardPointer->GetEndX() && MousePositionY > GlobalCardPointer->GetStartY() && MousePositionY < GlobalCardPointer->GetEndY())
			//{
				PickingUp = true;
				GlobalCardPointer->SetPickUpWidth(MousePositionX - GlobalCardPointer->GetStartX());
				GlobalCardPointer->SetPickUpHeight(MousePositionY - GlobalCardPointer->GetStartY());
			//}
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		if (PickingUp)
		{
			PickingUp = false;
			GlobalCardPointer->SetPickUpWidth(0);
			GlobalCardPointer->SetPickUpHeight(0);

			if (GlobalCardPointer->GetStartX() != GlobalCardPointer->GetLastPositionX() && GlobalCardPointer->GetStartY() != GlobalCardPointer->GetLastPositionY())
			{
				MoveBack = true;
			}
		}
		break;
	}
	case WM_RBUTTONDOWN:
	{
		GlobalStackPointer = Stack1Pointer;
		GlobalCardPointer = new Card(KING, HEARTS, MousePositionX, MousePositionY, false);
		GlobalCanvasPointer->AddCard(GlobalCardPointer);
		GlobalStackPointer->Push(GlobalCardPointer);
		GlobalCardPointer = nullptr;
		break;
	}
	case WM_MOUSEMOVE:
	{
		MousePositionX = static_cast<int>(LOWORD(lParam));			// find the pointer location
		MousePositionY = static_cast<int>(HIWORD(lParam));

		if (PickingUp)
		{	
			GlobalCardPointer->SetStartX(MousePositionX - GlobalCardPointer->GetPickUpWidth());
			GlobalCardPointer->SetStartY(MousePositionY - GlobalCardPointer->GetPickUpHeight());
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

		delete Stack1Pointer;
		delete GlobalCanvasPointer;
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
