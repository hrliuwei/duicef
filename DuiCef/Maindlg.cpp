#include "stdafx.h"
#include "Maindlg.h"
#include <string>
//#include "simple_handler.h"
CMaindlg::CMaindlg()
{
	m_bInitalsize = TRUE;
	m_bRestore = FALSE;
	m_pSelectedOption = NULL;
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
	InitControl();
	m_NeedUpdate = TRUE;
}

void CMaindlg::ShowDefaultUrl()
{
	CefWindowInfo info;
	RECT rc;
	::GetClientRect(m_hWnd, &rc);
	rc.top = rc.top + 60;
	info.SetAsChild(m_hWnd, rc);

	m_CEFHandle = new SimpleHandler(false);
	CefBrowserSettings BrowserSettings;
	CefString(&BrowserSettings.default_encoding).FromWString(_T("GB2312"));
	BrowserSettings.default_encoding.length = wcslen(_T("GB2312"));
	std::string url =  "http://www.baidu.com";
	Sleep(100);
	CefBrowserHost::CreateBrowser(info, m_CEFHandle, url, BrowserSettings, NULL, NULL);
}

void CMaindlg::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0) {
		OnClick(msg);
	}
}

void CMaindlg::OnClick(TNotifyUI& msg)
{
	if (msg.pSender == m_btnClose){
		PostQuitMessage(0);
	}
	else if (msg.pSender == m_btnMin){
		::ShowWindow(GetHWND(), SW_SHOWMINIMIZED);
	}
	else if (msg.pSender->GetName() == L"btnMax"){
		::ShowWindow(GetHWND(), SW_SHOWMAXIMIZED);
		m_pTabNormalMax->SelectItem(0);
		UpdateChildWndSize();
		CRect rt;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);
		NeedUpdateOptions(rt.right);
	}
	else if (msg.pSender->GetName() == L"btnNormal"){
		::ShowWindow(GetHWND(), SW_SHOWDEFAULT);
		m_pTabNormalMax->SelectItem(1);
		UpdateChildWndSize();
		NeedUpdateOptions(WINDOW_DEFAULT_WIDTH);
	}
	else if (msg.pSender->GetName() == L"reFresh" || msg.pSender->GetName() == L"reFreshLabel"){
		if (m_pSelectedOption && m_CEFHandle) {
			HWND hWnd = GetHwndByOption(m_pSelectedOption);
			if (hWnd){
				m_CEFHandle->ReLoadBrowser(hWnd);
			}
		}
	}
	if (msg.pSender->GetParent()->GetParent() == m_pHeadOptions) {
		COptionLayoutUI* pOption = (COptionLayoutUI*)msg.pSender->GetParent();
		std::wstring data = msg.pSender->GetCustomAttribute(L"controltype");
		if (data == L"closebutton"){
			HWND hWnd = GetHwndByOption(pOption);
			if (hWnd){
				::SetParent(hWnd, GetDesktopWindow());
				if (m_CEFHandle){
					m_CEFHandle->CloseBrowser(hWnd);
				}
				ReMoveOption(pOption);
				if (m_objHwndVec.empty()){
					::PostMessage(GetHWND(), WM_CLOSE, 0, 0);
				}
			}
		}
		else {
			HWND hWnd = GetHwndByOption(pOption);
			if (hWnd) {
				ShowPage(hWnd);
				OnTitleChange(hWnd, pOption->GetText().GetData());
				m_pSelectedOption = pOption;
			}
		}
	}
}

void CMaindlg::OnSelChanged(TNotifyUI& msg)
{
	if (msg.pSender->GetParent() == m_pHeadOptions){
		COptionLayoutUI* pOption = (COptionLayoutUI*)msg.pSender;
	}
}

void CMaindlg::OnTitleChange(HWND hwnd, LPCTSTR pstrTitle)
{
	COptionLayoutUI* pOption = GetOption(hwnd);
	if (pOption == NULL) {
		return;
	}
	pOption->SetText(pstrTitle);
	m_pLabelTitle->SetText(pstrTitle);
}

CControlUI* CMaindlg::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT CMaindlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_SYSCOMMAND && wParam == SC_MAXIMIZE){
		m_pTabNormalMax->SelectItem(0);
	}
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

void CMaindlg::InitControl()
{
	m_btnClose = static_cast <CButtonUI*> (m_PaintManager.FindControl(_T("btnClose")));
	ASSERT(m_btnClose != NULL);

	m_btnMin = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnMin")));
	ASSERT(m_btnMin != NULL);

	m_pTabNormalMax = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tab_normal_max")));
	ASSERT(m_pTabNormalMax != NULL);

	m_pRefresh = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("reFresh")));
	ASSERT(m_pRefresh);

	m_pHeadOptions = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("options")));
	ASSERT(m_pHeadOptions);

	m_pBody = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("body")));
	ASSERT(m_pBody);

	m_pLabelTitle = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("title")));
	ASSERT(m_pLabelTitle);
}

void CMaindlg::UpdateChildWndSize()
{
	RECT frame_rc;
	::GetClientRect(GetHWND(), &frame_rc);
	RECT rc = m_pBody->GetPos();
	for (auto iter = m_objHwndVec.begin(); iter != m_objHwndVec.end(); ++iter) {
		::MoveWindow(iter->hWnd, rc.left, rc.top, frame_rc.right - frame_rc.left, frame_rc.bottom - frame_rc.top - 50, TRUE);
	}
}

COptionLayoutUI* CMaindlg::GetOption(HWND hWnd)
{
	std::vector<CEF_TAB_OPTION>::iterator iter;
	for (iter = m_objHwndVec.begin(); iter != m_objHwndVec.end(); ++iter) {
		if (iter->hWnd == hWnd){
			return iter->pOption;
		}
	}
	return NULL;
}

HWND CMaindlg::GetHwndByOption(COptionLayoutUI* pOption)
{
	std::vector<CEF_TAB_OPTION>::iterator iter;
	for (iter = m_objHwndVec.begin(); iter != m_objHwndVec.end(); ++iter) {
		if (iter->pOption == pOption){
			return iter->hWnd;
		}
	}
	return NULL;
}

void CMaindlg::ShowPage(HWND hWnd)
{
	std::vector<CEF_TAB_OPTION>::iterator iter;
	for (iter = m_objHwndVec.begin(); iter != m_objHwndVec.end(); ++iter) {
		if (iter->hWnd == hWnd){
			::ShowWindow(hWnd, SW_SHOW);
			iter->pOption->Selected(true, false);
		}
		else {
			::ShowWindow(iter->hWnd, SW_HIDE);
			iter->pOption->Selected(false, false);
		}
	}
}

void CMaindlg::NeedUpdateOptions(int nDefaultWidth)
{
	if (m_objHwndVec.empty()){
		return;
	}
	RECT rc = m_pHeadOptions->GetPos();
	int nFramewidth = 0;
	if (nDefaultWidth != 0){
		nFramewidth = nDefaultWidth;
	}
	else{
		nFramewidth = rc.right - rc.left;
	}
	int nOptionwidth = (nFramewidth - OPTION_FRESH_WIDTH) / m_objHwndVec.size();
	if (nOptionwidth > OPTION_NORMAL_WIDTH){
		nOptionwidth = OPTION_NORMAL_WIDTH;
	}
	for (auto iter = m_objHwndVec.begin(); iter != m_objHwndVec.end(); ++iter) {
		iter->pOption->SetElnmentFixedWidth(nOptionwidth);
		m_vecUpdate.push_back(iter->pOption);
	}
	m_NeedUpdate = TRUE;
}

void CMaindlg::UpdateOptionUI(COptionLayoutUI* pOption)
{
	pOption->ShowCloseButton(true);
}

void CMaindlg::ReMoveOption(COptionLayoutUI* pOption)
{
	std::vector<CEF_TAB_OPTION>::iterator iter;
	for (iter = m_objHwndVec.begin(); iter != m_objHwndVec.end(); ++iter) {
		if (iter->pOption == pOption){
			iter = m_objHwndVec.erase(iter);
			break;
		}
	}
	m_pHeadOptions->Remove(pOption);
	if (iter != m_objHwndVec.end()){
		ShowPage(iter->hWnd);
	} 
	else{
		if (!m_objHwndVec.empty()){
			auto iter2 = m_objHwndVec.rbegin();
			ShowPage(iter2->hWnd);
		}
	}
	if (!m_objHwndVec.empty()){
		NeedUpdateOptions();
	}
	
}

BOOL CMaindlg::OnIdle(LONG ICount)
{
	if (m_NeedUpdate) {
		if (!m_vecUpdate.empty()) {
			for (auto iter = m_vecUpdate.begin(); iter != m_vecUpdate.end(); ++iter) {
				UpdateOptionUI(*iter);
			}
			m_vecUpdate.clear();
		}
		if (m_bInitalsize){
			m_bInitalsize = FALSE;
			::ShowWindow(GetHWND(), SW_SHOWMAXIMIZED);
			m_pTabNormalMax->SelectItem(0);
		}
		if (m_bRestore){
			m_bRestore = FALSE;
			UpdateChildWndSize();
		}
		m_NeedUpdate = FALSE;
	}
	return FALSE;
}

BOOL CMaindlg::IsIdleMessage(MSG* pMsg)
{
	// These messages should NOT cause idle processing
	switch (pMsg->message)
	{
	case WM_MOUSEMOVE:
#ifndef _WIN32_WCE
	case WM_NCMOUSEMOVE:
#endif // !_WIN32_WCE
	case WM_PAINT:
	case 0x0118:	// WM_SYSTIMER (caret blink)
		return FALSE;
	}

	return TRUE;
}

UINT CMaindlg::ShowModal()
{
	BOOL bDoIdle = TRUE;
	int nIdleCount = 0;
	ASSERT(::IsWindow(m_hWnd));
	UINT nRet = 0;
	BOOL bRet = 0;
	HWND hWndParent = GetWindowOwner(m_hWnd);
	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	::EnableWindow(hWndParent, FALSE);
	MSG msg = { 0 };
	while (::IsWindow(m_hWnd)) {
		while (bDoIdle && !::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!OnIdle(nIdleCount++))
				bDoIdle = FALSE;
		}
		bRet = ::GetMessage(&msg, NULL, 0, 0);
		if (bRet == -1) {
			continue;
		}
		else if (!bRet) {
			break;
		}

		if (msg.message == WM_CLOSE && msg.hwnd == m_hWnd) {
			nRet = msg.wParam;
			::EnableWindow(hWndParent, TRUE);
			::SetFocus(hWndParent);
		}
		if (!CPaintManagerUI::TranslateMessage(&msg)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT) break;

		if (IsIdleMessage(&msg)) {
			bDoIdle = TRUE;
			nIdleCount = 0;
		}
	}
	::EnableWindow(hWndParent, TRUE);
	::SetFocus(hWndParent);
	if (msg.message == WM_QUIT) ::PostQuitMessage(msg.wParam);
	return nRet;
}

LRESULT CMaindlg::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (uMsg == WM_SYSCOMMAND && wParam == SC_RESTORE){
		m_bRestore = TRUE;
		m_NeedUpdate = TRUE;
	}
	return 0;
}

LRESULT CMaindlg::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;

	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTONEAREST), &oMonitor);
	CDuiRect rcWork = oMonitor.rcWork;
	CDuiRect rcMonitor = oMonitor.rcMonitor;
	rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

	// 计算最大化时，正确的原点坐标
	lpMMI->ptMaxPosition.x = rcWork.left;
	lpMMI->ptMaxPosition.y = rcWork.top;

	CRect rt;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);
	lpMMI->ptMaxSize.y = rt.bottom;

	lpMMI->ptMaxTrackSize.x = rcWork.GetWidth();
	lpMMI->ptMaxTrackSize.y = rcWork.GetHeight();

	lpMMI->ptMinTrackSize.x = m_PaintManager.GetMinInfo().cx;
	lpMMI->ptMinTrackSize.y = m_PaintManager.GetMinInfo().cy;

	bHandled = FALSE;
	return 0;
}

LRESULT CMaindlg::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	switch (uMsg) {
	case WM_CREATE_NEW_PAGE:
	{
		HWND hWnd = HWND(wParam);
		if (!m_pBody){
			break;
		}
		RECT rc = m_pBody->GetPos();
		::MoveWindow(hWnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);
		COptionLayoutUI* pOption = new  COptionLayoutUI(OPTION_NORMAL_WIDTH, OPTION_NORMAL_HEIGHT);
		pOption->CreateChildControls();
		pOption->SetBkColor(0xFFD3D3D3);
		m_pHeadOptions->Add(pOption);
		CEF_TAB_OPTION cef;
		cef.hWnd = hWnd;
		cef.pOption = pOption;
		m_objHwndVec.push_back(cef);
		m_vecUpdate.push_back(pOption);
		m_NeedUpdate = TRUE;
		ShowPage(hWnd);
		if (m_objHwndVec.size()*OPTION_NORMAL_WIDTH >= (rc.right - rc.left)){
			NeedUpdateOptions();
		}
		m_pSelectedOption = pOption;
		break;
	}
	case WM_TITLE_CHANGE:
	{
		HWND hwnd = (HWND)wParam;
		wchar_t* pTile = (wchar_t*)lParam;
		OnTitleChange(hwnd, pTile);
		break;
	}
	default:
		break;
	}
	return 0;
}