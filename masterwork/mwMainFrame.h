#pragma once

#include "wx/wx.h"
#include "wx/splitter.h"
#include <wx/infobar.h>
#include "mwSidePanel.h"
#include "mwBottomPanel.h"
#include "mwWorkPanel.h"

enum event_id
{
	OPEN_ID = 10000,
	EXIT_ID, 
	TIMER_ID
};

class mwMainFrame : public wxFrame
{
public:
	mwMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~mwMainFrame();
private:
	void InitMenuBar();
	void InitStatusBar();
	void InitToolBar();
	void InitInfoBar();
	void InitMainPanel();
	// private method
	void ShowInfoBarMessage(const wxString& msg);
	void ShowInfoBarInfoMessage(const wxString& msg);
	void ShowInfoBarErrorMessage(const wxString& msg);
	void ShowStutusBarMessage(const wxString& msg, wxColor& bg_color);
private:
	// info contols
	wxInfoBar* m_info_bar;
	wxStatusBar* m_status_bar;
	wxMenuBar* m_menu_bar;
	wxToolBar* m_tool_bar;
	wxTimer* m_timer;

	// panels
	wxPanel* m_main_panel;
	wxSizer* m_main_ver_sizer;
	wxColor m_info_bg = wxColor(0, 122, 204);
	wxColor m_tool_bar_bg = wxColor(61, 61, 61);
	wxColor m_side_panel_bg = wxColor(37, 37, 38);
private:
	// any class wishing to process wxWidgets events must use this macro
	DECLARE_EVENT_TABLE()
	//event handlers
	void OnOpen(wxCommandEvent& evt);
	void OnExit(wxCommandEvent& evt);
	void OnTimer(wxTimerEvent& event);
};

