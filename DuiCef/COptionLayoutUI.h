#pragma once
#include "ElementLayoutUI.h"
class COptionLayoutUI :
	public CElementLayoutUI
{
public:
	COptionLayoutUI(int width, int height);
	~COptionLayoutUI();

public:
	virtual void CreateChildControls();
	virtual void SetFont(int index);
	virtual void SetChildHeight(int height);
	virtual void SetFixedWidth(int width);
	virtual void SetBkColor(DWORD dwBackColor);
	virtual void SetBkImage(LPCTSTR pStrImage);
	virtual void SetNormalImage(LPCTSTR pStrImage);
	virtual void SetHotImage(LPCTSTR pStrImage);
	virtual void SetSelectedImage(LPCTSTR pStrImage);
	virtual void SetForeImage(LPCTSTR pStrImage);

	virtual void SetText(LPCTSTR pstrText);
	virtual void SetTextColor(DWORD dwColor);
	virtual void SetToolTip(LPCTSTR pstrText);
	virtual void ShowCloseButton(bool show, int padding=0);
	virtual CDuiString GetText();

	void SetPadding(CRect padding);

	void SetLabelHeight(int height);
	void SetGroup(LPCTSTR pstrName);
	
	void Selected(bool selected, bool bTriggerEvent = true);
	bool IsSelected(void);

private:
	COptionUI*	m_pOption;
	CLabelUI*	m_pLabel;
	CRect		m_padding;
};

