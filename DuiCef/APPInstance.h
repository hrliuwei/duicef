#pragma once
#include "Maindlg.h"
class CAPPInstance
{
public:
	CAPPInstance();
	~CAPPInstance();
public:
	CMaindlg* GetMainDlg() {
		return &m_Maindlg;
	}
private:
	CMaindlg m_Maindlg;
};

