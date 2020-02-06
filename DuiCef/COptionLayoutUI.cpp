#include "stdafx.h"
#include "COptionLayoutUI.h"


COptionLayoutUI::COptionLayoutUI(int width, int height)
	: CElementLayoutUI(width, height)
	, m_pOption(nullptr)
	, m_pLabel(nullptr)
	, m_padding(0,0,0,0)
{
}

COptionLayoutUI::~COptionLayoutUI()
{
}

void COptionLayoutUI::CreateChildControls()
{
	wchar_t value[32];
	m_pOption = new COptionUI;
	::swprintf_s(value, L"%d", m_width);
	m_pOption->SetAttribute(L"width", value);
	m_pOption->SetAttribute(L"controltype", L"option");
	m_pOption->SetPadding(m_padding);
	
	m_pOption->ApplyAttributeList(L"selectedimage=\"file='img/round_corner_cover_border.png' corner='5,5,5,5'\"");

	Add(m_pOption);
	CElementLayoutUI::CreateChildControls();
}

void COptionLayoutUI::SetFont(int index)
{
	if (m_pLabel){
		m_pLabel->SetFont(index);
	}
}

void COptionLayoutUI::SetLabelHeight(int height)
{
	if (m_pLabel) {
		wchar_t value[32];
		::swprintf_s(value, L"%d", height);
		m_pLabel->SetAttribute(L"height", value);
	}
}

void COptionLayoutUI::SetChildHeight(int height)
{
	if (m_pOption) {
		wchar_t value[32];
		::swprintf_s(value, L"%d", height);
		m_pOption->SetAttribute(L"height", value);
	}
}

void COptionLayoutUI::SetBkColor(DWORD dwBackColor)
{
	if (m_pOption) {
		m_pOption->SetBkColor(dwBackColor);
	}
}

void COptionLayoutUI::SetBkImage(LPCTSTR pStrImage)
{
	if (m_pOption) {
		m_pOption->SetBkImage(pStrImage);
	}
}

void COptionLayoutUI::SetNormalImage(LPCTSTR pStrImage)
{
	if (m_pOption) {
		m_pOption->SetNormalImage(pStrImage);
	}
}

void COptionLayoutUI::SetHotImage(LPCTSTR pStrImage)
{
	if (m_pOption) {
		m_pOption->SetHotImage(pStrImage);
	}
}

void COptionLayoutUI::SetSelectedImage(LPCTSTR pStrImage)
{
	if (m_pOption) {
		m_pOption->SetSelectedImage(pStrImage);
	}
}

void COptionLayoutUI::SetForeImage(LPCTSTR pStrImage)
{
	if (m_pOption) {
		m_pOption->SetForeImage(pStrImage);
	}
}

void COptionLayoutUI::SetText(LPCTSTR pstrText)
{
	if (m_pLabel) {
		m_pLabel->SetText(pstrText);
	}
}

void COptionLayoutUI::SetTextColor(DWORD dwColor)
{
	if (m_pLabel) {
		m_pLabel->SetTextColor(dwColor);
	}
}

void COptionLayoutUI::SetToolTip(LPCTSTR pstrText)
{
	if (m_pOption) {
		m_pOption->SetToolTip(pstrText);
	}
}

void COptionLayoutUI::ShowCloseButton(bool show)
{
	if (m_pOption) {
		CElementLayoutUI::ShowCloseButton(m_pOption->GetRelativePos(), show);
	}
}

void COptionLayoutUI::SetPadding(CRect padding)
{
	m_padding = padding;
}

void COptionLayoutUI::SetGroup(LPCTSTR pstrName)
{
	if (m_pOption) {
		m_pOption->SetGroup(pstrName);
	}
}

void COptionLayoutUI::Selected(bool selected, bool bTriggerEvent)
{
	if (m_pOption) {
		m_pOption->Selected(selected, bTriggerEvent);
	}
}

bool COptionLayoutUI::IsSelected(void)
{
	bool ret = false;
	if (m_pOption) {
		ret = m_pOption->IsSelected();
	}
	return ret;
}
