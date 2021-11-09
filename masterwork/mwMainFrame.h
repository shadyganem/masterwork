#pragma once

#include "wx/wx.h"
#include <wx/infobar.h>



class mwMainFrame : public wxFrame
{
public:
	mwMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~mwMainFrame();
private:
	void InitMenuBar();
	// private method
	void ShowInfoBarMessage(const wxString& msg);
	void ShowStutusBarMessage(const wxString& msg, wxColor& bg_color);
private:
	// info contols
	wxInfoBar* m_info_bar;
	wxStatusBar* m_status_bar;
	wxMenuBar* m_menu_bar;

	wxSizer* m_hor_sizer;
	wxSizer* m_ver_sizer;
	wxColor m_info_bg = wxColor(0, 50, 100);
private:
	// any class wishing to process wxWidgets events must use this macro
	DECLARE_EVENT_TABLE()
};

