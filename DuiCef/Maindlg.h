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
	virtual CControlUI*		CreateControl(LPCTSTR pstrClass);
	virtual LRESULT			HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT			MessageHandler(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& bHandled);


private://程序初始化
	//初始化控件
	void					InitControl();


};

