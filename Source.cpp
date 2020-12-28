#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
// or, just build with unicode and use wchar_t

#define ID_BUTTON 1

// The main window class name.
static TCHAR szWindowClass[] = _T("ThingiverseLazyExtract");

// The main window title (in title bar)
static TCHAR szTitle[] = _T("ThingiverseLazyExtract");

HINSTANCE hInst;

HWND button;
HWND static_label;

// Forward declarations of functions included
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
  _In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPSTR     lpCmdLine,
  _In_ int       nCmdShow
) {
  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

  if (!RegisterClassEx(&wcex))
  {
    MessageBox(NULL,
      _T("Call to RegisterClassEx failed!"),
      _T("Thingiverse Lazy Extract"),
      NULL);

    return 1;
  }

  // Store instance handle in our global variable
  hInst = hInstance;

  // The parameters to CreateWindow explained:
  // szWindowClass: the name of the application
  // szTitle: the text that appears in the title bar
  // WS_OVERLAPPEDWINDOW: the type of window to create
  // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
  // 500, 100: initial size (width, length)
  // NULL: the parent of this window
  // NULL: this application does not have a menu bar
  // hInstance: the first parameter from WinMain
  // NULL: not used in this application
  HWND hWnd = CreateWindow(
    szWindowClass,
    szTitle,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    500, 500,
    NULL,
    NULL,
    hInstance,
    NULL
  );

  if (!hWnd)
  {
    MessageBox(NULL,
      _T("Call to CreateWindow failed!"),
      _T("Windows Desktop Guided Tour"),
      NULL);

    return 1;
  }



  // The parameters to ShowWindow explained:
  // hWnd: the value returned from CreateWindow
  // nCmdShow: the fourth parameter from WinMain
  ShowWindow(hWnd,
    nCmdShow);
  UpdateWindow(hWnd);

  // Main message loop:
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;
  TCHAR greeting[] = _T("ThingiverseLazyExtract is running.");
  TCHAR buttonClass[] = _T("Button");
  TCHAR buttonDispText[] = _T("Calculate");
  TCHAR labelText[] = _T("Calculate");
  TCHAR labelText2[] = _T("You pressed the button");
  TCHAR labelClass[] = _T("Static");



  switch (message)
  {
  case WM_CREATE:
    button = CreateWindow(buttonClass, buttonDispText,
      BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 140, 70, 100, 25, hWnd, HMENU(ID_BUTTON), hInst, 0);
    static_label = CreateWindow(labelClass,
      labelText, WS_CHILD | WS_VISIBLE, 40, 15, 200, 25, hWnd, 0, hInst, 0);
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    // Here your application is laid out.
    // For this introduction, we just print out "Hello, Windows desktop!"
    // in the top left corner.
    TextOut(hdc,
      5, 5,
      greeting, _tcslen(greeting));
    // End application-specific layout section.

    EndPaint(hWnd, &ps);
    break;
  case WM_COMMAND: //Command from Child windows and menus are under this message
    switch (wParam) //the ID is is wParam
    {
      case ID_BUTTON: //check for our button ID
      {
        // Static labels dont do messages
        //we can set the text directly though
        SetWindowText(static_label, labelText2);
        break;
      }
    }
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
    break;
  }

  return 0;
}
