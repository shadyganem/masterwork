#include "mwMainFrame.h"

BEGIN_EVENT_TABLE(mwMainFrame, wxFrame)
	EVT_MENU(MENU_FILE_EXIT_ID, mwMainFrame::OnExit)
	EVT_MENU(MENU_WINDOW_PROPERTIES_ID, mwMainFrame::OnProperties)
	EVT_TIMER(MAIN_1SEC_TIMER_ID, mwMainFrame::On1SecTimer)
	EVT_SEARCH(TOP_PANEL_SERACH_ID, mwMainFrame::OnTopPanelSearch)
END_EVENT_TABLE()

mwMainFrame::mwMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	Maximize();
	this->SetMinSize(wxSize(576, 432));
	this->SetBackgroundColour(wxColor(30, 30, 30));
	// first layer components
	m_main_ver_sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(m_main_ver_sizer);
	m_info_bar_timer_couter = 0;
	m_10_sec_check = 0;
	m_ready_msg;
	m_1sec_timer = new wxTimer(this, MAIN_1SEC_TIMER_ID);
	InitMenuBar();
	InitStatusBar();
	InitInfoBar();
	InitMainPanel();
	m_main_ver_sizer->Add(m_info_bar, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	m_main_ver_sizer->Add(m_main_panel, 1, wxEXPAND);

	// second layer components
	wxSizer* main_panel_ver_sizer1 = new wxBoxSizer(wxVERTICAL);

	wxSizer* main_panel_hor_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxSizer* main_panel_ver_sizer = new wxBoxSizer(wxVERTICAL);
	m_main_panel->SetSizer(main_panel_ver_sizer1);

	m_top_panel = new mwTopPanel(m_main_panel, wxID_ANY, wxDefaultPosition, wxSize(40, 21));
	m_top_panel->SetBackgroundColour(m_side_panel_bg);
	m_side_panel = new mwSidePanel(m_main_panel, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_side_panel->SetBackgroundColour(m_side_panel_bg);
	m_bottom_panel = new mwBottomPanel(m_main_panel, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_bottom_panel->SetBackgroundColour(m_side_panel_bg);
	m_work_panel = new mwWorkPanel(m_main_panel, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_work_panel->SetBackgroundColour(m_side_panel_bg);

	// Order of addition matters
	main_panel_ver_sizer1->Add(m_top_panel, 0, wxEXPAND | wxBOTTOM, 5);
	main_panel_ver_sizer1->Add(main_panel_hor_sizer, 1, wxEXPAND);
	main_panel_hor_sizer->Add(m_side_panel, 1, wxEXPAND | wxRIGHT, 5);
	main_panel_hor_sizer->Add(main_panel_ver_sizer, 8, wxEXPAND);
	main_panel_ver_sizer->Add(m_work_panel, 2, wxEXPAND | wxBOTTOM, 5);
	main_panel_ver_sizer->Add(m_bottom_panel, 1, wxEXPAND);
	m_1sec_timer->Start(1000);
}

mwMainFrame::~mwMainFrame()
{
}

void mwMainFrame::InitMenuBar()
{
	m_menu_bar = new wxMenuBar();
	// TODO: find a way to change the menu bar backgournd color. 
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

void mwMainFrame::OnExit(wxCommandEvent& event)
{
	Close();
	event.Skip();
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
	

	ShowStutusBarMessage("Ready - MasterWork");
}

void mwMainFrame::OnTopPanelSearch(wxCommandEvent& event)
{

	ShowInfoBarInfoMessage("Searching: " + m_top_panel->GetSearchText());
	m_top_panel->ClearSearchText();
}
