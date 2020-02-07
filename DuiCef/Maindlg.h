#pragma once
#include "UIlib.h"
using namespace DuiLib;
#include "COptionLayoutUI.h"
class CMaindlg :
	public WindowImplBase
{
public:
	CMaindlg();
	virtual ~CMaindlg();
public:
	virtual CDuiString      GetSkinFolder();
	virtual CDuiString		GetSkinFile();
	virtual LPCTSTR			GetWindowClassName(void) const;
	virtual void			InitWindow();
	virtual void			Notify(TNotifyUI& msg);
	virtual void			OnClick(TNotifyUI& msg);
	virtual void			OnSelChanged(TNotifyUI& msg);
	virtual CControlUI*		CreateControl(LPCTSTR pstrClass);
	virtual LRESULT			HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT			MessageHandler(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& bHandled);
	virtual LRESULT		    HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void					OnTitleChange(HWND hwnd, LPCTSTR pstrTitle);


private://程序初始化
	//初始化控件
	void					InitControl();
	COptionLayoutUI*		GetOption(HWND hWnd);
	HWND					GetHwndByOption(COptionLayoutUI* pOption);
	void					ShowPage(HWND hWnd);
	void					NeedUpdateOptions();
	void					UpdateOptionUI(COptionLayoutUI* pOption);

private:
	CLabelUI*				m_pLabelTitle;
	CButtonUI*				m_btnClose;		//关闭应用按钮
	CButtonUI*				m_btnMin;		//最小化应用按钮
	CTabLayoutUI*			m_pTileLayoutHeadview;
	CHorizontalLayoutUI*	m_pHeadOptions;
	CHorizontalLayoutUI*    m_pBody;
	std::map<HWND, COptionLayoutUI*> m_objHwndMap;
	BOOL					m_NeedUpdate;
	std::vector<COptionLayoutUI*> m_vecUpdate;

public:
	BOOL OnIdle(LONG ICount)
	{
		if (m_NeedUpdate) {
			if (!m_vecUpdate.empty()) {
				for (auto iter = m_vecUpdate.begin(); iter != m_vecUpdate.end(); ++iter) {
					UpdateOptionUI(*iter);
				}
				m_vecUpdate.clear();
			}
			m_NeedUpdate = FALSE;
		}
		return FALSE;
	}
	static BOOL IsIdleMessage(MSG* pMsg)
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
	UINT ShowModal()
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
};

