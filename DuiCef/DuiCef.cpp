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
	CefSettings settings;
	settings.no_sandbox = true;
	settings.multi_threaded_message_loop = true;
	CefInitialize(main_args, settings, app.get(), sandbox_info);
	_App.GetMainDlg()->Create(NULL, L"testcef", UI_WNDSTYLE_DIALOG | WS_SYSMENU | WS_MINIMIZEBOX, 0L);
	_App.GetMainDlg()->CenterWindow();
	_App.GetMainDlg()->ShowModal();
   
	::CoUninitialize();
	CefShutdown();
    return 0;
}