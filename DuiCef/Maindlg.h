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


private://�����ʼ��
	//��ʼ���ؼ�
	void					InitControl();
	COptionUI*				GetOption(HWND hWnd);
	HWND					GetHwndByOption(COptionUI* pOption);
	void					ShowPage(HWND hWnd);
	void					NeedUpdateOptions();

private:
	CLabelUI*				m_pLabelTitle;
	CButtonUI*				m_btnClose;		//�ر�Ӧ�ð�ť
	CButtonUI*				m_btnMin;		//��С��Ӧ�ð�ť
	CTabLayoutUI*			m_pTileLayoutHeadview;
	CHorizontalLayoutUI*	m_pHeadOptions;
	CHorizontalLayoutUI*    m_pBody;
	std::map<HWND, COptionUI*> m_objHwndMap;
};

