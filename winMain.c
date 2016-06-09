/* --------------------------------------------------------
||
||      	My own generic WinAPI application
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


unsigned short* applicationName = L"HelloKitty";

void* __stdcall
mainWindow(
	void* handle,
	unsigned int msg,
	void* param1,
	void* param2)
{
	switch (msg)
	{
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
	case WM_CLOSE:
		DestroyWindow(handle);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(handle, msg, param1, param2);
}

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

	while (GetMessageW(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return msg.param1;
}