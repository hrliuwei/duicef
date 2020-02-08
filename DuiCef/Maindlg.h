#pragma once
#include "UIlib.h"
using namespace DuiLib;
#include "COptionLayoutUI.h"
#include "simple_handler.h"

typedef struct _CEF_TAB_OPTION
{
	HWND hWnd;
	COptionLayoutUI* pOption;
}CEF_TAB_OPTION;
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
	virtual UINT			ShowModal();
	virtual LRESULT			OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private://�����ʼ��
	//��ʼ���ؼ�
	void					InitControl();
	void					UpdateChildWndSize();
	void					OnTitleChange(HWND hwnd, LPCTSTR pstrTitle);
	COptionLayoutUI*		GetOption(HWND hWnd);
	HWND					GetHwndByOption(COptionLayoutUI* pOption);
	void					ShowPage(HWND hWnd);
	void					NeedUpdateOptions(int nDefaultWidth = 0);
	void					UpdateOptionUI(COptionLayoutUI* pOption);
	void					ReMoveOption(COptionLayoutUI* pOption);
	BOOL					OnIdle(LONG ICount);
	BOOL				    IsIdleMessage(MSG* pMsg);

private:
	CLabelUI*				m_pLabelTitle;
	CButtonUI*				m_pRefresh;
	CButtonUI*				m_btnClose;		//�ر�Ӧ�ð�ť
	CButtonUI*				m_btnMin;		//��С��Ӧ�ð�ť
	CTabLayoutUI*			m_pTabNormalMax;//���h��ԭӦ�ð�ť
	COptionLayoutUI*        m_pSelectedOption;
	CHorizontalLayoutUI*	m_pHeadOptions;
	CHorizontalLayoutUI*    m_pBody;


	BOOL	m_NeedUpdate;
	BOOL    m_bInitalsize;
	BOOL    m_bRestore;
	std::vector<CEF_TAB_OPTION> m_objHwndVec;
	std::vector<COptionLayoutUI*> m_vecUpdate;
	CefRefPtr<SimpleHandler>    m_CEFHandle;

};

