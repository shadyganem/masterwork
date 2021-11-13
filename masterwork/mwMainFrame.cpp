#include "mwMainFrame.h"

BEGIN_EVENT_TABLE(mwMainFrame, wxFrame)
	EVT_MENU(MENU_FILE_EXIT_ID, mwMainFrame::OnExit)
	EVT_MENU(MENU_WINDOW_PROPERTIES_ID, mwMainFrame::OnProperties)
	EVT_TIMER(MAIN_1SEC_Timer_ID, mwMainFrame::On1SecTimer)
END_EVENT_TABLE()

mwMainFrame::mwMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	this->SetBackgroundColour(wxColor(30, 30, 30));
	// first layer components
	m_main_ver_sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(m_main_ver_sizer);
	m_info_bar_timer_couter = 0;
	m_10_sec_check = 0;
	m_1sec_timer = new wxTimer(this, MAIN_1SEC_Timer_ID);
	InitMenuBar();
	InitStatusBar();
	InitToolBar();
	InitInfoBar();
	InitMainPanel();
	m_main_ver_sizer->Add(m_info_bar, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	m_main_ver_sizer->Add(m_main_panel, 1, wxEXPAND);

	// second layer components
	wxSizer* m_main_panel_hor_sizer = new wxBoxSizer(wxHORIZONTAL);
	m_main_panel->SetSizer(m_main_panel_hor_sizer);

	m_side_panel = new mwSidePanel(m_main_panel, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_side_panel->SetBackgroundColour(m_side_panel_bg);
	m_bottom_panel = new mwBottomPanel(m_main_panel, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_bottom_panel->SetBackgroundColour(m_side_panel_bg);
	m_work_panel = new mwWorkPanel(m_main_panel, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_work_panel->SetBackgroundColour(m_side_panel_bg);

	wxSizer* m_main_panel_ver_sizer = new wxBoxSizer(wxVERTICAL);
	m_main_panel_hor_sizer->Add(m_side_panel,1, wxEXPAND | wxRIGHT, 5);
	m_main_panel_hor_sizer->Add(m_main_panel_ver_sizer, 8, wxEXPAND);
	m_main_panel_ver_sizer->Add(m_work_panel, 2, wxEXPAND | wxBOTTOM, 5);
	m_main_panel_ver_sizer->Add(m_bottom_panel, 1, wxEXPAND);

	m_1sec_timer->Start(1000);
}

mwMainFrame::~mwMainFrame()
{
}

void mwMainFrame::InitMenuBar()
{
	m_menu_bar = new wxMenuBar();
	this->SetMenuBar(m_menu_bar);
	wxMenu* menu_file = new wxMenu();
	menu_file->AppendSeparator();
	menu_file->Append(MENU_FILE_EXIT_ID, "Exit");
	wxMenu* menu_window = new wxMenu();
	menu_window->Append(MENU_WINDOW_PROPERTIES_ID, "Properties");
	m_menu_bar->Append(menu_file, "File");
	m_menu_bar->Append(menu_window, "Window");
}

void mwMainFrame::InitStatusBar()
{
	m_status_bar = CreateStatusBar();
	m_status_bar->SetBackgroundColour(m_info_bg);
	m_status_bar_text = new wxStaticText(m_status_bar, wxID_ANY, "", wxPoint(5, 5), wxDefaultSize, wxALIGN_LEFT);
	m_status_bar_text->SetForegroundColour(wxColor(255, 255, 255));
	m_status_bar_text->SetLabel("MasterWork - By Shady Ganem");
}

void mwMainFrame::InitToolBar()
{
	m_tool_bar = CreateToolBar();
	m_tool_bar->SetBackgroundColour(m_tool_bar_bg);
	m_tool_bar->SetBackgroundColour(m_tool_bar_bg);
}

void mwMainFrame::InitInfoBar()
{
	m_info_bar = new wxInfoBar(this);
	m_info_bar->SetBackgroundColour(m_msg_bg);
	m_info_bar->SetForegroundColour(m_white_fg);
	ShowInfoBarMessage("Welcome to MasterWork");
}

void mwMainFrame::InitMainPanel()
{
	m_main_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_main_panel->SetBackgroundColour(wxColor(30, 30, 30));
}

void mwMainFrame::Refresh()
{
}

void mwMainFrame::ShowInfoBarMessage(const wxString& msg)
{
	m_info_bar->Dismiss();
	m_info_bar->SetBackgroundColour(m_msg_bg);
	m_info_bar->Show();
	m_info_bar->ShowMessage(msg);
}

void mwMainFrame::ShowInfoBarInfoMessage(const wxString& msg)
{
	m_info_bar->Dismiss();
	m_info_bar->SetBackgroundColour(m_info_bg);
	m_info_bar->Show();
	m_info_bar->ShowMessage(msg);
}

void mwMainFrame::ShowInfoBarErrorMessage(const wxString& msg)
{
	m_info_bar->Dismiss();
	m_info_bar->SetBackgroundColour(m_info_bg);
	m_info_bar->Show();
	m_info_bar->ShowMessage(msg);
}

void mwMainFrame::ShowStutusBarMessage(const wxString& msg)
{
	m_status_bar_text->SetLabel(msg);
}

void mwMainFrame::SetStatusBarBackgrounColor(const wxColor& color)
{
	m_status_bar->SetBackgroundColour(color);
}

void mwMainFrame::OnExit(wxCommandEvent& evt)
{
	Close();
	evt.Skip();
}

void mwMainFrame::OnProperties(wxCommandEvent& event)
{
	ShowInfoBarInfoMessage("Properties");
	ShowStutusBarMessage("Propeties");
}

void mwMainFrame::On1SecTimer(wxTimerEvent& event)
{
	// This method is called every 1 second
	if (m_info_bar_timer_couter == 2)
	{
		m_info_bar->Dismiss();
		m_info_bar_timer_couter = 0;
	}
	else
	{
		m_info_bar_timer_couter++;
	}

	if (m_10_sec_check == 10)
	{
		ShowInfoBarMessage("MasterWork! - By Shady Ganem");
		m_10_sec_check = 0;
	}
	else
	{ 
		m_10_sec_check++;
	}
		
	ShowStutusBarMessage("MasterWork - By Shady Ganem");
}
