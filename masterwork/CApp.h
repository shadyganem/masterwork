#pragma once
#include "wx/wx.h"
#include "CMainFrame.h"

class CApp : public wxApp
{
public:
	CApp();
	~CApp();
	virtual bool OnInit();
private:
	CMainFrame* m_main_frame = nullptr;
	const wxString m_app_name = wxString("MasterWork");
};

