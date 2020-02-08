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
	m_pOption = new COptionUI;
	m_pOption->SetAttribute(L"controltype", L"option");
	m_pOption->SetPadding(m_padding);
	m_pOption->ApplyAttributeList(L"");
	CDuiString strAttr;
	//m_pOption->ApplyAttributeList(L"selectedimage=\"file='img/round_corner_cover_border.png' corner='5,5,5,5'\"");
	strAttr.Format(_T("width=\"%d\" group=\"tab_group\" normalimage=\"ѡ�1.png\" \
		align=\"left\" textpadding=\"0,5,0,0\" endellipsis=\"true\""), m_width - OPTION_CLOSE_SIZE);
	m_pOption->ApplyAttributeList(strAttr);
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

void COptionLayoutUI::SetElnmentFixedWidth(int width)
{
	if (m_pOption){
		m_pOption->SetFixedWidth(width - OPTION_CLOSE_SIZE);
	}
	SetElementWidth(width);
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
	if (m_pOption) {
		m_pOption->SetText(pstrText);
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

CDuiString COptionLayoutUI::GetText()
{
	if (m_pOption){
		return m_pOption->GetText();
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
		//m_pOption->Selected(selected, bTriggerEvent);
		if (selected){
			m_pOption->SetBkColor(0xFF1E90FF);
		}
		else{
			m_pOption->SetBkColor(0xFFD3D3D3);
		}
		
		SelectCloseButton(selected);
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
