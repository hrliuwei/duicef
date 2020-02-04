#include "stdafx.h"
#include "Maindlg.h"
#include "simple_handler.h"
CMaindlg::CMaindlg()
{
}


CMaindlg::~CMaindlg()
{
}

CDuiString CMaindlg::GetSkinFolder()
{
	return _T("skin");
}

CDuiString CMaindlg::GetSkinFile()
{
	return _T("cefmaindlg.xml");
}

LPCTSTR CMaindlg::GetWindowClassName(void) const
{
	return _T("CEFMainWnd");
}

void CMaindlg::InitWindow()
{
	CefWindowInfo info;
	RECT rc;
	::GetClientRect(m_hWnd, &rc);
	rc.top = rc.top + 30;
	info.SetAsChild(m_hWnd, rc);

	CefRefPtr<SimpleHandler> handle = new SimpleHandler(false);
	CefBrowserSettings BrowserSettings;
	CefString(&BrowserSettings.default_encoding).FromWString(_T("GB2312"));
	BrowserSettings.default_encoding.length = wcslen(_T("GB2312"));
	std::string url = "http://www.baidu.com";
	CefBrowserHost::CreateBrowser(info, handle, url, BrowserSettings, NULL, NULL);
}

void CMaindlg::Notify(TNotifyUI& msg)
{

}

void CMaindlg::OnClick(TNotifyUI& msg)
{

}

CControlUI* CMaindlg::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT CMaindlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

void CMaindlg::InitControl()
{
}

LRESULT CMaindlg::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return 0;
}