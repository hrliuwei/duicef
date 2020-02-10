// DuiCef.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DuiCef.h"

#pragma comment(lib,"Ole32.lib")

#define MAX_LOADSTRING 100
CAPPInstance _App;


CDuiCef::CDuiCef()
{

}

CDuiCef::~CDuiCef()
{

}

BOOL CDuiCef::InitInstance()
{
	return TRUE;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	CPaintManagerUI::SetInstance(hInstance);

	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;
	//cef
	void* sandbox_info = NULL;
	CefMainArgs main_args(hInstance);
	CefRefPtr<SimpleApp> app(new SimpleApp);
	int exit_code = CefExecuteProcess(main_args, app.get(), sandbox_info);
	if (exit_code >= 0){
		return exit_code;
	}
	CefSettings settings;
	settings.no_sandbox = true;
	settings.multi_threaded_message_loop = true;
	CefInitialize(main_args, settings, app.get(), sandbox_info);
	//mutex
	HANDLE hMutext = ::CreateMutex(NULL, FALSE, _T("cef"));
	if (GetLastError() == ERROR_ALREADY_EXISTS){
		CloseHandle(hMutext);
		HWND hWnd = FindWindow(_T("CEFMainWnd"), NULL);
		if (hWnd){
			::ShowWindow(hWnd, SW_SHOW);
			::PostMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, NULL);
			::PostMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, NULL);
			::SetForegroundWindow(hWnd);
			::SetActiveWindow(hWnd);
		}
		return 0;
	}
	_App.GetMainDlg()->Create(NULL, L"cefbrowser", UI_WNDSTYLE_DIALOG | WS_SYSMENU | WS_MINIMIZEBOX, 0L);
	_App.GetMainDlg()->CenterWindow();
	_App.GetMainDlg()->ShowModal();
	
	CloseHandle(hMutext);
	::CoUninitialize();
	CefShutdown();
    return 0;
}