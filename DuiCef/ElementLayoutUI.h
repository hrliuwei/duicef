#pragma once
#include <atltypes.h>
class CElementLayoutUI : 
	public CVerticalLayoutUI
{
public:
	CElementLayoutUI(int width, int height);
	virtual ~CElementLayoutUI(void);

public:
	virtual void CreateChildControls(void);
	virtual void SetChildHeight(int height) {}
	virtual void SetBkColor(DWORD dwBackColor) {}

	void SetName(LPCTSTR pstrName);
	
	virtual void SetBkImage(LPCTSTR pStrImage) {}

	virtual void SetText(LPCTSTR pstrText) {}
	virtual void SetTextColor(DWORD dwColor) {}
	virtual void SetFont(int index){}

	virtual void SetToolTip(LPCTSTR pstrText) {}
	virtual void ShowCloseButton(RECT rect, bool show, int padding);

	void  SelectCloseButton(bool selected);

protected:
	CButtonUI*		CreateCloseButton(void);

protected:
	int m_width;
	int m_height;

	// controls
	CButtonUI*	m_pCloseButton;	
};

