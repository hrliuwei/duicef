#pragma once
#include "UIlib.h"

using namespace DuiLib;
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
	COptionUI*				GetOption(HWND hWnd);
	HWND					GetHwndByOption(COptionUI* pOption);
	void					ShowPage(HWND hWnd);
	void					NeedUpdateOptions();

private:
	CLabelUI*				m_pLabelTitle;
	CButtonUI*				m_btnClose;		//关闭应用按钮
	CButtonUI*				m_btnMin;		//最小化应用按钮
	CTabLayoutUI*			m_pTileLayoutHeadview;
	CHorizontalLayoutUI*	m_pHeadOptions;
	CHorizontalLayoutUI*    m_pBody;
	std::map<HWND, COptionUI*> m_objHwndMap;
};

