#pragma once

#include "wx/wx.h"
#include "wx/splitter.h"
#include <wx/infobar.h>
#include "mwSidePanel.h"
#include "BottomPanel.h"
#include "mwWorkPanel.h"
#include "mwTopPanel.h"
#include "mwDefines.h"
#include "wx/event.h"
#include "wx/srchctrl.h"
#include "controller/mwController.h"
#include "view/AboutFrame.h"


class mwMainFrame : public wxFrame
{
public:
	mwMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~mwMainFrame();
	
private:
	void InitMenuBar();
	void InitStatusBar();
	void InitInfoBar();
	void InitMainPanel();
	void InitColorScheme();
	// private method
	void ShowInfoBarInfoMessage(const wxString& msg);
	void ShowInfoBarErrorMessage(const wxString& msg);
	void ShowStutusBarMessage(const wxString& msg);
	void SetStatusBarBackgrounColor(const wxColor& color);
public:
	// info contols
	wxInfoBar* m_info_bar;
	wxStatusBar* m_status_bar;
	wxMenuBar* m_menu_bar;
	//wxToolBar* m_tool_bar;
	wxStaticText* m_status_bar_text;
	wxSearchCtrl* m_search_ctrl;
	// initialzing panels
	mwTopPanel* m_top_panel;
	mwSidePanel* m_side_panel;
	mw::BottomPanel* m_bottom_panel;
	mwWorkPanel* m_work_panel;
	wxTimer* m_1sec_timer;

	// panels
	wxPanel* m_main_panel;
	wxColor m_info_bg = wxColor(0, 122, 204);
	wxColor m_err_bg = wxColor(134, 27, 45);
	wxColor m_white_fg = wxColor(255, 255, 255);
	wxColor m_tool_bar_bg = wxColor(61, 61, 61);
	wxColor m_side_panel_bg = wxColor(37, 37, 38);
private:
	// any class wishing to process wxWidgets events must use this macro
	DECLARE_EVENT_TABLE()
	// event handlers
	void OnExit(wxCommandEvent& event);
	void OnProperties(wxCommandEvent& event);
	void On1SecTimer(wxTimerEvent& event);
	void OnNewTaskButton(wxCommandEvent& event);
	void OnSearch(wxCommandEvent& event);
	void OnUpdateUI(wxEvent& event);
	void OnNotification(wxEvent& event);
	void OnAboutClick(wxCommandEvent& event);

private:
	int m_info_bar_timer_couter;
	int m_10_sec_check;
	int m_3_sec_check;
	bool m_ready_msg;
};

