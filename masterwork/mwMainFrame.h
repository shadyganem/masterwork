#pragma once

#include "wx/wx.h"
#include "mwStatusBar.h"
#include <wx/infobar.h>



class mwMainFrame : public wxFrame
{
public:
	mwMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~mwMainFrame();
private:
	// private method
	void ShowInfoBarMessage(const wxString& msg);
private:
	// info contols
	wxInfoBar* m_info_bar;
	wxSizer* m_hor_sizer;
	wxSizer* m_ver_sizer;
private:
	// any class wishing to process wxWidgets events must use this macro
	DECLARE_EVENT_TABLE()
};

