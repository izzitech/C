/* --------------------------------------------------------
||
||      			Testing menu bars
||
||
||				Author: Iván E. Sierra
||				Date: 2016-06-09
||
||
//----------------------------------------------------------*/

// Windows default libraries
#include <windows.h>

// DIY handmade libraries for replace crappy WinAPI
#include <winTypes.h>

/*-----------------------------------------------
		Global
-----------------------------------------------*/
#define IDM_FILE_NEW 1
#define IDM_FILE_OPEN 2
#define IDM_FILE_QUIT 3

unsigned short* applicationName = L"HelloKitty";

/*-----------------------------------------------
		Functions
-----------------------------------------------*/
void AddMenus(void* handle)
{
	void* menuBar;
	void* menu;

	menuBar = CreateMenu();
	menu = CreateMenu();

	AppendMenuW(menu, MF_STRING, IDM_FILE_NEW, L"&New");
	AppendMenuW(menu, MF_STRING, IDM_FILE_OPEN, L"&Open");
	AppendMenuW(menu, MF_SEPARATOR, 0, NULL);
	AppendMenuW(menu, MF_STRING, IDM_FILE_QUIT, L"&Quit");
	AppendMenuW(menuBar, MF_POPUP, unsigned int* menu, L"&File");
	SetMenu(handle, menubar);
}

void* __stdcall
mainWindow(
	void* handle,
	unsigned int msg,
	void* param1,
	void* param2)
{
	switch (msg)
	{
	case WM_CREATE:
		AddMenus(handle);
		break;
	case WM_LBUTTONDOWN:
	{
		unsigned short appPath[MAX_PATH];
		void* application = GetModuleHandleW(NULL);
		GetModuleFileNameW(application, appPath, MAX_PATH);

		MessageBoxW(
			NULL,
			appPath,
			L"Application path",
			MB_ICONINFORMATION | MB_OK);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(param1))
		{
		case IDM_FILE_NEW:
		case IDM_FILE_OPEN:
			MessageBeep(MB_ICONINFORMATION);
			break;
		case IDM_FILE_QUIT:
			SendMessage(handle, WM_CLOSE, 0, 0);
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(handle);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(handle, msg, param1, param2);
}

/*-----------------------------------------------
		WinMain
-----------------------------------------------*/
int __stdcall 
wWinMain(
	void* application, 
	void* noUse,
	unsigned short* parameters,
	int startMode) 
{
	struct Window window;
	struct Message msg;
	void* handle;

	window.style = 0;
	window.process = mainWindow;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.handle = application;
	window.icon = LoadIconW(NULL, IDI_APPLICATION);
	window.cursor = LoadCursorW(NULL, IDC_ARROW);
	window.background = (HBRUSH)COLOR_3DFACE;
	window.menuName = NULL;
	window.className = applicationName;
	
	if (!RegisterClassW(&window))
	{
		MessageBoxW(
			NULL,
			L"Window registration failed.\nApplication must end.",
			L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	handle = CreateWindowW(
		applicationName,
		L"New fuckin window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640, 480,
		NULL, NULL,
		application, 0);

	if (!handle)
	{
		MessageBoxW(
			NULL,
			L"Window creation failed.\nApplication must end.",
			L"Error",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(handle, startMode);
	UpdateWindow(handle);

	/*----------------------------
		Message queue
	----------------------------*/
	BOOL answer;
	while ((answer = GetMessageW(&msg, NULL, 0, 0)) != 0)
	{
		if (answer == -1)
		{
			/* 
			MSDN:
			The possibility of a -1 return value in the case that hWnd
			is an invalid parameter (such as referring to a window that
			has already been destroyed) means that such code can lead to
			fatal application errors.
			*/
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	return msg.param1;
}