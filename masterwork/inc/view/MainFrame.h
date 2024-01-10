#pragma once

#include "wx/wx.h"
#include "wx/splitter.h"
#include <wx/infobar.h>
#include "SidePanel.h"
#include "BottomPanel.h"
#include "WorkPanel.h"
#include "TopPanel.h"
#include "mwDefines.h"
#include "wx/event.h"
#include "wx/srchctrl.h"
#include "controller/Controller.h"
#include "view/AboutFrame.h"
#include "view/NewUserFrame.h"
#include "controller/StagehandThread.h"
#include <wx/notifmsg.h>
#include <wx/icon.h>
#include <wx/artprov.h>
#include "controller/NotificationThread.h"
#include "view/PreferencesFrame.h"


namespace mw
{
	class MainFrame : public wxFrame
	{
	public:
		MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
		~MainFrame();

	private:
		void InitMenuBar();
		void InitStatusBar();
		void InitColorScheme();
		void InitStagehandThread();
		void PauseStagehandThread();
		void ResumeStagehandThread();
		void TerminateStagehandThread();
		// private method
		void ShowStutusBarMessage(const wxString& msg);
		void SetStatusBarBackgrounColor(const wxColor& color);
	public:
		// info contols
		wxStatusBar* m_status_bar;
		wxMenuBar* m_menu_bar;
		//wxToolBar* m_tool_bar;
		wxStaticText* m_status_bar_text;
		wxSearchCtrl* m_search_ctrl;
		// initialzing panels
		TopPanel* m_top_panel;
		SidePanel* m_side_panel;
		mw::BottomPanel* m_bottom_panel;
		WorkPanel* m_work_panel;
		wxTimer* m_1sec_timer;
		wxTimer* m_notification_timer;
		wxBoxSizer* m_main_panel_hor_sizer1;

		// panels
		wxPanel* m_main_panel;
		wxColor m_info_bg = wxColor(0, 122, 204);
		wxColor m_success_bg = wxColor(0, 128, 0);
		wxColor m_err_bg = wxColor(134, 27, 45);
		wxColor m_white_fg = wxColor(255, 255, 255);
		wxColor m_tool_bar_bg = wxColor(61, 61, 61);
		wxColor m_side_panel_bg = wxColor(37, 37, 38);
	private:
		mw::StagehandThread* m_stagehand_thread;
		// any class wishing to process wxWidgets events must use this macro
		DECLARE_EVENT_TABLE()
		// event handlers
		void OnExit(wxCommandEvent& event);
		void OnCharHook(wxKeyEvent& event);
		void OnProperties(wxCommandEvent& event);
		void OnPreferences(wxCommandEvent& event);
		void OnRefresh(wxCommandEvent& event);
		void OnNewProject(wxCommandEvent& event);
		void OnNewUser(wxCommandEvent& event);
		void On1SecTimer(wxTimerEvent& event);
		void OnNotificationTimer(wxTimerEvent& event);
		void OnNotificationThread(wxThreadEvent& even);
		void OnNewTaskButton(wxCommandEvent& event);
		void OnSearch(wxCommandEvent& event);
		void OnUpdateUI(wxEvent& event);
		void OnAboutClick(wxCommandEvent& event);


	private:
		int m_info_bar_timer_couter;
		int m_10_sec_check;
		int m_3_sec_check;
		int m_30_sec_counter;
		bool m_ready_msg;

		wxCriticalSection m_stagehand_thread_CS;    // protects the m_stagehand_thread pointer


	};
}