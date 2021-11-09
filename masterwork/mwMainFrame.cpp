#include "mwMainFrame.h"

BEGIN_EVENT_TABLE(mwMainFrame, wxFrame)
	EVT_MENU(OPEN_ID, mwMainFrame::OnOpen)
	EVT_MENU(EXIT_ID, mwMainFrame::OnExit)
	EVT_TIMER(TIMER_ID, mwMainFrame::OnTimer)
END_EVENT_TABLE()


mwMainFrame::mwMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	// first layer components
	m_main_ver_sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(m_main_ver_sizer);
	m_timer = new wxTimer(this, TIMER_ID);
	InitMenuBar();
	InitStatusBar();
	InitToolBar();
	InitInfoBar();
	InitMainPanel();
	m_main_ver_sizer->Add(m_info_bar, 0, wxEXPAND);
	m_main_ver_sizer->Add(m_main_panel, 1, wxEXPAND);

	// second layer components
	wxSizer* m_main_panel_hor_sizer = new wxBoxSizer(wxHORIZONTAL);
	m_main_panel->SetSizer(m_main_panel_hor_sizer);

	// initialzing panels
	wxPanel* m_side_panel;
	wxPanel* m_bottom_panel;	
	wxPanel* m_work_panel;

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

	m_timer->Start(3000);
}

mwMainFrame::~mwMainFrame()
{
}

void mwMainFrame::InitMenuBar()
{
	m_menu_bar = new wxMenuBar();
	this->SetMenuBar(m_menu_bar);
	wxMenu* menu_file = new wxMenu();
	menu_file->Append(OPEN_ID, "New");
	menu_file->Append(EXIT_ID, "Exit");
	m_menu_bar->Append(menu_file, "File");
}

void mwMainFrame::InitStatusBar()
{
	m_status_bar = CreateStatusBar();
	m_status_bar->SetBackgroundColour(m_info_bg);
}

void mwMainFrame::InitToolBar()
{
	m_tool_bar = CreateToolBar();
	m_tool_bar->SetBackgroundColour(m_tool_bar_bg);
}

void mwMainFrame::InitInfoBar()
{
	m_info_bar = new wxInfoBar(this);
	m_info_bar->SetBackgroundColour(wxColor(134, 27, 45));
	ShowInfoBarMessage("Welcome to MasterWork");
}

void mwMainFrame::InitMainPanel()
{
	m_main_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_main_panel->SetBackgroundColour(wxColor(30, 30, 30));
}

void mwMainFrame::ShowInfoBarMessage(const wxString& msg)
{
	m_info_bar->ShowMessage(msg);
}

void mwMainFrame::ShowInfoBarInfoMessage(const wxString& msg)
{
	m_info_bar->SetBackgroundColour(m_info_bg);
	m_info_bar->ShowMessage(msg);
}

void mwMainFrame::ShowInfoBarErrorMessage(const wxString& msg)
{
	m_info_bar->SetBackgroundColour(m_info_bg);
	m_info_bar->ShowMessage(msg);
}

void mwMainFrame::ShowStutusBarMessage(const wxString& msg, wxColor& bg_color)
{
}

void mwMainFrame::OnExit(wxCommandEvent& evt)
{
	Close();
	evt.Skip();
}

void mwMainFrame::OnOpen(wxCommandEvent& evt)
{
}

void mwMainFrame::OnTimer(wxTimerEvent& event)
{
	m_info_bar->Dismiss();
}
