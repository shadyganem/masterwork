#include "view/mwMainFrame.h"

wxDEFINE_EVENT(mwUpdateUI, wxCommandEvent);
wxDEFINE_EVENT(mwNotification, wxCommandEvent);

BEGIN_EVENT_TABLE(mwMainFrame, wxFrame)
	EVT_MENU(MENU_FILE_EXIT_ID, mwMainFrame::OnExit)
	EVT_MENU(MENU_WINDOW_PROPERTIES_ID, mwMainFrame::OnProperties)
	EVT_TIMER(MAIN_1SEC_TIMER_ID, mwMainFrame::On1SecTimer)
	EVT_SEARCH(MAIN_SEARCH_ID, mwMainFrame::OnSearch)
	EVT_BUTTON(TOP_PANEL_NEW_TASK_ID, mwMainFrame::OnNewTaskButton)
	EVT_CUSTOM(mwUpdateUI, MAIN_FRAME_ID, mwMainFrame::OnUpdateUI)
	EVT_CUSTOM(mwNotification, MAIN_FRAME_ID, mwMainFrame::OnNotification)
END_EVENT_TABLE()

mwMainFrame::mwMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, MAIN_FRAME_ID, title, pos, size)
{
	mwController& control = mwController::Get();
	control.RegisterMainFrame(this);
	Maximize();
	this->SetMinSize(wxSize(576, 432));
	this->SetBackgroundColour(wxColor(30, 30, 30));
	// first layer components
	wxSizer* m_main_ver_sizer = new wxBoxSizer(wxVERTICAL);
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
	wxSizer* main_panel_hor_sizer1 = new wxBoxSizer(wxHORIZONTAL);
	wxSizer* main_panel_ver_sizer1 = new wxBoxSizer(wxVERTICAL);
	wxSizer* main_panel_ver_sizer2 = new wxBoxSizer(wxVERTICAL);

	m_search_ctrl = new wxSearchCtrl(m_main_panel, MAIN_SEARCH_ID, wxEmptyString, wxDefaultPosition, wxSize(200, 21));
	m_top_panel = new mwTopPanel(m_main_panel, wxID_ANY, wxDefaultPosition, wxSize(600, 21));
	m_top_panel->SetBackgroundColour(m_side_panel_bg);
	m_side_panel = new mwSidePanel(m_main_panel, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_side_panel->SetBackgroundColour(m_side_panel_bg);
	m_bottom_panel = new mwBottomPanel(m_main_panel, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_bottom_panel->SetBackgroundColour(m_side_panel_bg);
	m_work_panel = new mwWorkPanel(m_main_panel, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_work_panel->SetBackgroundColour(m_side_panel_bg);

	main_panel_ver_sizer1->Add(m_search_ctrl, 0, wxEXPAND | wxBOTTOM, 5);
	main_panel_ver_sizer1->Add(m_side_panel, 1, wxEXPAND, 0);
	main_panel_hor_sizer1->Add(main_panel_ver_sizer1, 0, wxEXPAND | wxRIGHT, 5);
	main_panel_ver_sizer2->Add(m_top_panel, 0, wxEXPAND | wxBOTTOM, 5);
	main_panel_ver_sizer2->Add(m_work_panel, 3, wxEXPAND | wxBOTTOM, 5);
	main_panel_ver_sizer2->Add(m_bottom_panel, 1, wxEXPAND, 0);

	main_panel_hor_sizer1->Add(main_panel_ver_sizer2, 1, wxEXPAND, 0);
	m_main_panel->SetSizer(main_panel_hor_sizer1);
	m_1sec_timer->Start(1000);
}

mwMainFrame::~mwMainFrame()
{
}

void mwMainFrame::InitMenuBar()
{
	m_menu_bar = new wxMenuBar();
	// TODO: find a way to change the menu bar backgournd color. 
	wxMenu* menu_file = new wxMenu();
	menu_file->Append(MENU_FILE_NEW_ID, "New");
	menu_file->AppendSeparator();
	menu_file->Append(MENU_FILE_EXIT_ID, "Exit");
	wxMenu* menu_window = new wxMenu();
	menu_window->Append(MENU_WINDOW_PROPERTIES_ID, "Properties");
	m_menu_bar->Append(menu_file, "File");
	m_menu_bar->Append(menu_window, "Window");
	this->SetMenuBar(m_menu_bar);
}

void mwMainFrame::InitStatusBar()
{
	mwController& controller = mwController::Get();
	m_status_bar = CreateStatusBar();
	m_status_bar->SetBackgroundColour(m_info_bg);
	m_status_bar_text = new wxStaticText(m_status_bar, wxID_ANY, "", wxPoint(5, 5), wxDefaultSize, wxALIGN_LEFT);
	m_status_bar_text->SetForegroundColour(wxColor(255, 255, 255));
	controller.SetStatusBarText("Ready - MasterWork");
}

void mwMainFrame::InitInfoBar()
{
	m_info_bar = new wxInfoBar(this);
	m_info_bar->SetBackgroundColour(m_err_bg);
	m_info_bar->SetForegroundColour(m_white_fg);
	ShowInfoBarInfoMessage("Welcome to MasterWork");
}

void mwMainFrame::InitMainPanel()
{
	m_main_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_main_panel->SetBackgroundColour(wxColor(30, 30, 30));
}

void mwMainFrame::InitColorScheme()
{
	m_info_bg = wxColor(0, 122, 204);
	m_err_bg = wxColor(134, 27, 45);
	m_white_fg = wxColor(255, 255, 255);
	m_tool_bar_bg = wxColor(61, 61, 61);
	m_side_panel_bg = wxColor(37, 37, 38);
}

void mwMainFrame::ShowInfoBarInfoMessage(const wxString& msg)
{
	m_info_bar_timer_couter = 0;
	m_info_bar->Dismiss();
	m_info_bar->SetBackgroundColour(m_info_bg);
	m_info_bar->Show();
	m_info_bar->ShowMessage(msg);
}

void mwMainFrame::ShowInfoBarErrorMessage(const wxString& msg)
{
	m_info_bar_timer_couter = 0;
	m_info_bar->Dismiss();
	m_info_bar->SetBackgroundColour(m_err_bg);
	m_info_bar->Show();
	m_info_bar->ShowMessage(msg);
}

void mwMainFrame::ShowStutusBarMessage(const wxString& msg)
{
	m_3_sec_check = 0;
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

// called every 1 second
void mwMainFrame::On1SecTimer(wxTimerEvent& event)
{
	mwController& controller = mwController::Get();
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
		controller.SetInfoBarText("MasterWork! - By Shady Ganem");
		m_10_sec_check = 0;
	}
	else
	{ 
		m_10_sec_check++;
	}

	if (m_3_sec_check == 3)
	{
		controller.SetStatusBarText("Ready - MasterWork!");
		m_3_sec_check = 0;
	}
	else
	{
		m_3_sec_check++;
	}
}

void mwMainFrame::OnNewTaskButton(wxCommandEvent& event)
{
	mwController& controller = mwController::Get();
}

void mwMainFrame::OnSearch(wxCommandEvent& event)
{
	mwController& controller = mwController::Get();
	wxString seach_txt = m_search_ctrl->GetLineText(0);
	ShowInfoBarInfoMessage("Searching: " + m_search_ctrl->GetLineText(0));
	m_search_ctrl->Clear();
}

void mwMainFrame::OnUpdateUI(wxEvent& event)
{
	mwController& controller = mwController::Get();
	ShowStutusBarMessage(controller.GetStatusBarText());
}

void mwMainFrame::OnNotification(wxEvent& event)
{
	mwController& controller = mwController::Get();
	ShowInfoBarInfoMessage(controller.GetInfoBarText());
}
