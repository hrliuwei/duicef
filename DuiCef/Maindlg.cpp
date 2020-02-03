#include "stdafx.h"
#include "Maindlg.h"

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