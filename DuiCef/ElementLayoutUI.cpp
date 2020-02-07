#include "StdAfx.h"
#include "ElementLayoutUI.h"

#define CLOSE_BUTTON_WIDTH		(16)
#define CLOSE_BUTTON_HEIGHT		(16)


CElementLayoutUI::CElementLayoutUI(int width, int height)
	: m_width(width)
	, m_height(height)
	, m_pCloseButton(NULL)
{
	SetAttribute(L"enabled", L"true");
	wchar_t value[32];
	::swprintf_s(value, L"%d", m_width + CLOSE_BUTTON_WIDTH/2);
	SetAttribute(L"width", value);
	::swprintf_s(value, L"%d", m_height + CLOSE_BUTTON_HEIGHT/2);
	SetAttribute(L"height", value);
}

CElementLayoutUI::~CElementLayoutUI(void)
{
}

void CElementLayoutUI::CreateChildControls(void)
{
	m_pCloseButton = CreateCloseButton();
	Add(m_pCloseButton);
}

CButtonUI* CElementLayoutUI::CreateCloseButton(void)
{
	CButtonUI*	closeButton = new CButtonUI;
	closeButton->SetAttribute(L"controltype", L"closebutton");
	closeButton->SetFloat(true);
	
	wchar_t attributeList[128];
	::wsprintf(attributeList, L"width=\"%d\" height=\"%d\"", CLOSE_BUTTON_WIDTH, CLOSE_BUTTON_HEIGHT);
	closeButton->ApplyAttributeList(attributeList);
	
	closeButton->SetNormalImage(L"img/btn_close.png");
	closeButton->SetHotImage(L"img/btn_close.png");

	closeButton->SetVisible(false);
	
	return closeButton;
}

void CElementLayoutUI::SetName(LPCTSTR pstrName)
{
	CVerticalLayoutUI::SetName(pstrName);
	for (int i = 0; i < GetCount(); i++){
		CControlUI* pCtrl = GetItemAt(i);
		pCtrl->SetTag((UINT_PTR)this);
	}
}

void CElementLayoutUI::ShowCloseButton(RECT rect, bool show, int padding)
{
	if (m_pCloseButton){
		CRect rtBase(rect);
		rtBase.left = rect.right - padding;
		rtBase.right = rtBase.left + 20 - padding;
		rtBase.top = rect.top;
		rtBase.bottom = rect.bottom;
		/*CRect rtBase(rect);
		rtBase.right += 10;
		rtBase.left = rtBase.right - 10;
		rtBase.top -= 4;
		rtBase.bottom = rtBase.top + 16;*/
		m_pCloseButton->SetPos(rtBase, false);
		m_pCloseButton->SetVisible(show);
	}
}

void CElementLayoutUI::SelectCloseButton(bool selected)
{
	if (m_pCloseButton){
		if (selected){
			m_pCloseButton->SetBkColor(0xFF1E90FF);
		}
		else {
			m_pCloseButton->SetBkColor(0xFFD3D3D3);
		}
		
	}
}