#include "stdafx.h"
#include "Maindlg.h"
#include "simple_handler.h"
#include <string>
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
	InitControl();
	CefWindowInfo info;
	RECT rc;
	::GetClientRect(m_hWnd, &rc);
	rc.top = rc.top + 60;
	info.SetAsChild(m_hWnd, rc);

	CefRefPtr<SimpleHandler> handle = new SimpleHandler(_App.GetMainDlg(), false);
	CefBrowserSettings BrowserSettings;
	CefString(&BrowserSettings.default_encoding).FromWString(_T("GB2312"));
	BrowserSettings.default_encoding.length = wcslen(_T("GB2312"));
	std::string url = "http://www.baidu.com";
	CefBrowserHost::CreateBrowser(info, handle, url, BrowserSettings, NULL, NULL);

	/*if (m_pTileLayoutHeadview) {
		COptionLayoutUI* pElement = new COptionLayoutUI(80, 20);
		pElement->CreateChildControls();
		pElement->SetBkColor(0xFF98F5FF);
		pElement->SetBkImage(L"D:\\PersonGit\\duicef\\Release\\skin\\img\\store_effect_bk.png");
		pElement->ShowCloseButton(true);
		pElement->SetText(L"123");
		m_pTileLayoutHeadview->Add(pElement);
		COptionLayoutUI* pElement2 = new COptionLayoutUI(80, 20);
		pElement2->CreateChildControls();
		pElement2->SetBkColor(0xFF98F5FF);
		pElement2->ShowCloseButton(true);
		pElement2->SetText(L"456");
		pElement2->SetBkImage(L"D:\\PersonGit\\duicef\\Release\\skin\\img\\store_effect_bk.png");
		m_pTileLayoutHeadview->Add(pElement2);

	}
	if (m_pTileLayoutHeadview){
		m_pTileLayoutHeadview->SelectItem(0);
	}*/
	/*for (int i = 0; i < 2; i++) {
		if (m_pHeadOptions) {
			COptionUI* pOption = new COptionUI;
			m_pHeadOptions->Add(pOption);
			CDuiString strAttr;
			strAttr.Format(_T("width=\"%d\" group=\"tab_group\" normalimage=\"选项卡1.png\" selectedimage=\"选项卡2.png\" endellipsis=\"true\""), 50);
			pOption->ApplyAttributeList(strAttr);
			pOption->SetText(L"123");
			pOption->SetBkColor(0xFF0000FF);
		}
	}*/
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
	if (msg.pSender->GetParent()->GetParent() == m_pHeadOptions) {
		COptionLayoutUI* pOption = (COptionLayoutUI*)msg.pSender->GetParent();
		std::wstring data = msg.pSender->GetCustomAttribute(L"controltype");
		if (data == L"closebutton"){

		}
		else {
			HWND hWnd = GetHwndByOption(pOption);
			if (hWnd) {
				ShowPage(hWnd);
				OnTitleChange(hWnd, pOption->GetText().GetData());
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
	//CDialogBuilder builder;
	//if (_tcsicmp(pstrClass, _T("TitileHeadView")) == 0){
	//	m_pHeadview = static_cast<CContainerUI*>(builder.Create(_T("Headview.xml"), 0, this, &m_PaintManager));
	//	if (m_pHeadview){
	//		//m_pHeadview->SetFixedHeight(380);
	//		//m_pHeadview->SetFixedWidth(440);
	//	}
	//	return m_pHeadview;
	//}
	return NULL;
}

LRESULT CMaindlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

void CMaindlg::InitControl()
{
	m_btnClose = static_cast <CButtonUI*> (m_PaintManager.FindControl(_T("btnClose")));
	ASSERT(m_btnClose != NULL);

	m_pTileLayoutHeadview = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("Headview")));
	ASSERT(m_pTileLayoutHeadview != NULL);

	m_pHeadOptions = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("options")));
	ASSERT(m_pHeadOptions);

	m_pBody = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("body")));
	ASSERT(m_pBody);

	m_pLabelTitle = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("title")));
	ASSERT(m_pLabelTitle);
}

COptionLayoutUI* CMaindlg::GetOption(HWND hWnd)
{
	std::map<HWND, COptionLayoutUI*>::iterator iter = m_objHwndMap.find(hWnd);
	if (iter != m_objHwndMap.end())
	{
		return iter->second;
	}
	return NULL;
}

HWND CMaindlg::GetHwndByOption(COptionLayoutUI* pOption)
{
	std::map<HWND, COptionLayoutUI*>::iterator iter;
	for (iter = m_objHwndMap.begin(); iter != m_objHwndMap.end(); ++iter) {
		if (iter->second == pOption){
			return iter->first;
		}
	}
	return NULL;
}

void CMaindlg::ShowPage(HWND hWnd)
{
	std::map<HWND, COptionLayoutUI*>::iterator iter;
	for (iter = m_objHwndMap.begin(); iter != m_objHwndMap.end(); ++iter) {
		if (iter->first == hWnd){
			::ShowWindow(hWnd, SW_SHOW);
			iter->second->Selected(true, true);
		}else {
			::ShowWindow(iter->first, SW_HIDE);
			iter->second->Selected(false, false);
		}
	}
}

void CMaindlg::NeedUpdateOptions()
{
	RECT rc = m_pHeadOptions->GetPos();
	int nFramewidth = rc.right - rc.left;
	int nOptionwidth = (nFramewidth - OPTION_FRESH_WIDTH) / m_objHwndMap.size();
	for (auto iter = m_objHwndMap.begin(); iter != m_objHwndMap.end(); ++iter) {
		iter->second->SetFixedWidth(nOptionwidth);
	}
}

void CMaindlg::UpdateOptionUI(COptionLayoutUI* pOption)
{
	pOption->ShowCloseButton(true);
}

LRESULT CMaindlg::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
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
		//-----------------------------------------------------------------------------------------
		COptionLayoutUI* pOption = new  COptionLayoutUI(OPTION_NORMAL_WIDTH, OPTION_NORMAL_HEIGHT);
		pOption->CreateChildControls();
		pOption->SetBkColor(0xFFD3D3D3);
		m_pHeadOptions->Add(pOption);
		m_objHwndMap[hWnd] = pOption;
		m_vecUpdate.push_back(pOption);
		m_NeedUpdate = TRUE;
		break;
		//------------------------------------------------------------------------------------------
		/*COptionUI* pOption = new COptionUI;
		m_pHeadOptions->Add(pOption);
		m_objHwndMap[hWnd] = pOption;
		CDuiString strAttr;
		strAttr.Format(_T("width=\"%d\" group=\"tab_group\" normalimage=\"选项卡1.png\" selectedimage=\"选项卡2.png\" endellipsis=\"true\""), OPTION_NORMAL_WIDTH);
		pOption->ApplyAttributeList(strAttr);
		pOption->SetBkColor(0xFFBEBEBE);
		if (OPTION_NORMAL_WIDTH*m_objHwndMap.size() > rc.right - rc.left){
			NeedUpdateOptions();
		}
		break;*/
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