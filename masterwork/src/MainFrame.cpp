#include "view/MainFrame.h"

wxDEFINE_EVENT(mwUpdateUI, wxCommandEvent);
wxDEFINE_EVENT(mwNotification, wxCommandEvent);

BEGIN_EVENT_TABLE(mw::MainFrame, wxFrame)
	EVT_MENU(MENU_FILE_EXIT_ID, mw::MainFrame::OnExit)
	EVT_MENU(MENU_WINDOW_PROPERTIES_ID, mw::MainFrame::OnProperties)
	EVT_MENU(MENU_FILE_NEW_PROJECT_ID, mw::MainFrame::OnNewProject)
	EVT_MENU(MENU_FILE_NEW_USER_ID, mw::MainFrame::OnNewUser)
	EVT_MENU(MENU_HELP_ABOUT_ID, mw::MainFrame::OnAboutClick)
	EVT_MENU(MENU_WINDOW_REFRESH_ID, mw::MainFrame::OnRefresh)
	EVT_TIMER(MAIN_1SEC_TIMER_ID, mw::MainFrame::On1SecTimer)
	EVT_SEARCH(MAIN_SEARCH_ID, mw::MainFrame::OnSearch)
	EVT_BUTTON(TOP_PANEL_NEW_TASK_ID, mw::MainFrame::OnNewTaskButton)
	EVT_CUSTOM(mwUpdateUI, MAIN_FRAME_ID, mw::MainFrame::OnUpdateUI)
	EVT_CUSTOM(mwNotification, MAIN_FRAME_ID, mw::MainFrame::OnNotification)
END_EVENT_TABLE()

mw::MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, MAIN_FRAME_ID, title, pos, size)
{
	mw::Controller& control = mw::Controller::Get();
	control.RegisterMainFrame(this);
	control.RegisterEventHandler(MAIN_FRAME_ID, this);
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

	m_main_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	m_main_panel->SetBackgroundColour(wxColor(30, 30, 30));
	m_main_ver_sizer->Add(m_main_panel, 1, wxEXPAND);

	// second layer components
	m_main_panel_hor_sizer1 = new wxBoxSizer(wxHORIZONTAL);
	wxSizer* main_panel_ver_sizer1 = new wxBoxSizer(wxVERTICAL);
	wxSizer* main_panel_ver_sizer2 = new wxBoxSizer(wxVERTICAL);
	wxSizer* main_panel_ver_sizer3 = new wxBoxSizer(wxVERTICAL);


	m_search_ctrl = new wxSearchCtrl(m_main_panel, MAIN_SEARCH_ID, wxEmptyString, wxDefaultPosition, wxSize(200, 21));
	m_top_panel = new mw::TopPanel(m_main_panel, TOP_PANEL_ID, wxDefaultPosition, wxSize(600, 21));
	m_top_panel->SetBackgroundColour(m_side_panel_bg);
	m_top_panel->Hide();
	m_side_panel = new mw::SidePanel(m_main_panel, SIDE_PANEL_ID, wxDefaultPosition, wxSize(200, 200));
	m_side_panel->SetBackgroundColour(m_side_panel_bg);
	m_bottom_panel = new mw::BottomPanel(m_main_panel, BOTTOM_PANEL_ID, wxDefaultPosition, wxSize(200, 200));
	m_bottom_panel->SetBackgroundColour(m_side_panel_bg);
	m_bottom_panel->Hide();
	m_work_panel = new mw::WorkPanel(m_main_panel, WORK_PANEL_ID, wxDefaultPosition, wxSize(200, 200));
	m_work_panel->SetBackgroundColour(m_side_panel_bg);

	



	main_panel_ver_sizer1->Add(m_search_ctrl, 0, wxEXPAND | wxBOTTOM | wxTOP, 5);
	main_panel_ver_sizer1->Add(m_side_panel, 1, wxEXPAND, 0);
	//main_panel_ver_sizer2->Add(m_top_panel, 0, wxEXPAND | wxBOTTOM, 5);
	main_panel_ver_sizer2->Add(m_work_panel, 3, wxEXPAND | wxBOTTOM, 5);
	main_panel_ver_sizer2->Add(m_bottom_panel, 1, wxEXPAND, 0);

	m_main_panel_hor_sizer1->Add(main_panel_ver_sizer1, 0, wxEXPAND | wxRIGHT, 5);
	m_main_panel_hor_sizer1->Add(main_panel_ver_sizer2, 1, wxEXPAND, 0);
	m_main_panel_hor_sizer1->Add(main_panel_ver_sizer3, 0, wxEXPAND | wxLEFT, 5);
	m_main_panel->SetSizer(m_main_panel_hor_sizer1);
	m_1sec_timer->Start(1000);

}

mw::MainFrame::~MainFrame()
{
}

void mw::MainFrame::InitMenuBar()
{
	m_menu_bar = new wxMenuBar();
	// TODO: find a way to change the menu bar backgournd color. 
	wxMenu* menu_file = new wxMenu();
	
	wxMenu* file_export = new wxMenu();
	wxMenu* file_new = new wxMenu(); 
	file_new->Append(MENU_FILE_NEW_PROJECT_ID, "Project");
	file_new->Append(MENU_FILE_NEW_USER_ID, "User");
	menu_file->AppendSubMenu(file_new, "New");
	menu_file->Append(wxID_ANY, "Export");
	menu_file->AppendSeparator();
	menu_file->Append(MENU_FILE_EXIT_ID, "Exit");
	wxMenu* menu_window = new wxMenu();
	menu_window->Append(MENU_WINDOW_PROPERTIES_ID, "Properties");
	menu_window->Append(MENU_WINDOW_REFRESH_ID, "Refresh");
	wxMenu* menu_help = new wxMenu();
	menu_help->Append(MENU_HELP_ABOUT_ID, "About MasterWork");
	m_menu_bar->Append(menu_file, "File");
	m_menu_bar->Append(menu_window, "Window");
	m_menu_bar->Append(menu_help, "Help");
	this->SetMenuBar(m_menu_bar);
}

void mw::MainFrame::InitStatusBar()
{
	wxBoxSizer* statusbar_ver_sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* statusbar_hor_sizer = new wxBoxSizer(wxHORIZONTAL);
	mw::Controller& controller = mw::Controller::Get();
	m_status_bar = CreateStatusBar();
	m_status_bar->SetBackgroundColour(m_info_bg);
	m_status_bar_text = new wxStaticText(m_status_bar, wxID_ANY, "", wxPoint(5, 5), wxDefaultSize, wxALIGN_LEFT);
	m_status_bar_text->SetForegroundColour(wxColor(255, 255, 255));
	statusbar_hor_sizer->Add(m_status_bar_text, 1, wxALL, 5);
		

	statusbar_ver_sizer->AddStretchSpacer();
	

	statusbar_ver_sizer->Add(statusbar_hor_sizer, 0, wxALL | wxEXPAND, 0);

	m_status_bar->SetSizer(statusbar_ver_sizer);
	wxString active_user = controller.GetActiveUsername();
	controller.SetStatusBarText("Ready - " + active_user);
}

void mw::MainFrame::InitColorScheme()
{
	m_info_bg = wxColor(0, 122, 204);
	m_err_bg = wxColor(134, 27, 45);
	m_white_fg = wxColor(255, 255, 255);
	m_tool_bar_bg = wxColor(61, 61, 61);
	m_side_panel_bg = wxColor(37, 37, 38);
}

void mw::MainFrame::InitStagehandThread()
{
	m_stagehand_thread = new StagehandThread();
	if (m_stagehand_thread->Run() != wxTHREAD_NO_ERROR)
	{
		delete m_stagehand_thread;
		m_stagehand_thread = NULL;
	}
}

void mw::MainFrame::PauseStagehandThread()
{
	mw::Logger logger;
	if (m_stagehand_thread)         // does the thread still exist?
	{

		if (m_stagehand_thread->Pause() != wxTHREAD_NO_ERROR)
			logger.Error("Can't pause Stagehand thread!");
	}
}

void mw::MainFrame::ResumeStagehandThread()
{
	mw::Logger logger;
	if (m_stagehand_thread)         // does the thread still exist?
	{
		if (m_stagehand_thread->Resume() != wxTHREAD_NO_ERROR)
			logger.Error("Can't Resume Stagehand thread!");
	}
}

void mw::MainFrame::TerminateStagehandThread()
{
	// ending the stagehand thread

	mw::Logger logger;

	if (m_stagehand_thread)         // does the thread still exist?
	{
		if (m_stagehand_thread->Delete() != wxTHREAD_NO_ERROR)
			logger.Error("Can't delete Stagehand thread!");
	}
    
	while (1)
	{
		if (!m_stagehand_thread) 
			break;
		wxThread::This()->Sleep(1);
	}
}

void mw::MainFrame::ShowStutusBarMessage(const wxString& msg)
{
	m_3_sec_check = 0;
	m_status_bar_text->SetLabel(msg);
}

void mw::MainFrame::SetStatusBarBackgrounColor(const wxColor& color)
{
	m_status_bar->SetBackgroundColour(color);
}

void mw::MainFrame::OnExit(wxCommandEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.SetStatusBarText("Cleaning Up...");
	this->TerminateStagehandThread();

	Close();
	event.Skip();
}

void mw::MainFrame::OnProperties(wxCommandEvent& event)
{
	ShowStutusBarMessage("Propeties");
}

void mw::MainFrame::OnRefresh(wxCommandEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RequestUpdateUI();
}

void mw::MainFrame::OnNewProject(wxCommandEvent& event)
{
	mw::NewProjectFrame* new_project_form = new mw::NewProjectFrame(this);
	new_project_form->CenterOnScreen();
	new_project_form->Show(true);
	event.Skip();
}

void mw::MainFrame::OnNewUser(wxCommandEvent& event)
{
	mw::NewUserFrame* new_user_frame = new mw::NewUserFrame(this);
	new_user_frame->CenterOnParent();
	new_user_frame->Show(true);
	event.Skip();
}

// called every 1 second
void mw::MainFrame::On1SecTimer(wxTimerEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
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
		wxString active_user = controller.GetActiveUsername();
		controller.SetStatusBarText("Ready - " + active_user);
		m_3_sec_check = 0;
	}
	else
	{
		m_3_sec_check++;
	}


	// check notifications for all projects every one minute
	if (m_30_sec_counter == 29)
	{
		m_30_sec_counter = 0;
		controller.UpdateNotifications();
	}
	else
	{
		m_30_sec_counter++;
	}
}

void mw::MainFrame::OnNewTaskButton(wxCommandEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
}

void mw::MainFrame::OnSearch(wxCommandEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	wxString search_txt = m_search_ctrl->GetLineText(0);
	m_search_ctrl->Clear();
}

void mw::MainFrame::OnUpdateUI(wxEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	int num_of_notifications;
	controller.GetNumOfNotifications(num_of_notifications);
	ShowStutusBarMessage(controller.GetStatusBarText());
}

void mw::MainFrame::OnNotification(wxEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
}

void mw::MainFrame::OnAboutClick(wxCommandEvent& event)
{
	mw::AboutFrame* m_about_frame = new mw::AboutFrame(m_main_panel);
	m_about_frame->CenterOnParent();
	m_about_frame->Show(true);
	event.Skip();
}