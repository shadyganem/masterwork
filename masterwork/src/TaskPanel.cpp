#include "view/TaskPanel.h"


wxBEGIN_EVENT_TABLE(mw::TaskPanel, wxPanel)
wxEND_EVENT_TABLE()


mw::TaskPanel::TaskPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* m_top_sizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* m_left_sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* m_right_sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* m_main_panel_sizer = new wxBoxSizer(wxHORIZONTAL);

	m_main_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxBoxSizer* bSizer40 = new wxBoxSizer(wxHORIZONTAL);

	m_task_name_static = new wxStaticText(m_main_panel, wxID_ANY, wxT("Task Name"), wxDefaultPosition, wxDefaultSize, 0);
	m_task_name_static->Wrap(-1);
	bSizer40->Add(m_task_name_static, 0, wxALL, 5);

	m_task_name = new wxTextCtrl(m_main_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CAPITALIZE);
	m_default_task_name_background_colour = m_task_name->GetBackgroundColour();
	bSizer40->Add(m_task_name, 1, wxALL, 5);

	m_left_sizer->Add(bSizer40, 0, wxEXPAND, 5);

	m_task_description_static = new wxStaticText(m_main_panel, wxID_ANY, wxT("Task Description"), wxDefaultPosition, wxDefaultSize, 0);
	m_task_description_static->Wrap(-1);
	m_right_sizer->Add(m_task_description_static, 0, wxALL, 5);

	m_task_description = new wxTextCtrl(m_main_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CAPITALIZE | wxTE_MULTILINE | wxTE_RICH);
	m_task_description->SetMaxLength(500);
	m_right_sizer->Add(m_task_description, 1, wxALL | wxEXPAND, 5);

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer(3, 2, 0, 0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxBoxSizer* m_priority_sizer;
	m_priority_sizer = new wxBoxSizer(wxHORIZONTAL);

	m_priority_static = new wxStaticText(m_main_panel, wxID_ANY, wxT("Priority"), wxDefaultPosition, wxDefaultSize, 0);
	m_priority_static->Wrap(-1);
	m_priority_sizer->Add(m_priority_static, 1, wxALL | wxEXPAND, 5);

	wxString m_priority_choiceChoices[] = { wxT("High"), wxT("Medium"), wxT("Low"), wxT("ShowStopper") };
	int m_priority_choiceNChoices = sizeof(m_priority_choiceChoices) / sizeof(wxString);
	m_priority_choice = new wxChoice(m_main_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_priority_choiceNChoices, m_priority_choiceChoices, 0);
	m_priority_choice->SetSelection(1);
	m_priority_sizer->Add(m_priority_choice, 0, wxALL, 5);

	fgSizer1->Add(m_priority_sizer, 0, 0, 5);

	wxBoxSizer* bSizer48;
	bSizer48 = new wxBoxSizer(wxHORIZONTAL);

	m_status_static = new wxStaticText(m_main_panel, wxID_ANY, wxT("Status"), wxDefaultPosition, wxDefaultSize, 0);
	m_status_static->Wrap(-1);
	bSizer48->Add(m_status_static, 0, wxALL, 5);

	wxString m_status_choiceChoices[] = { wxT("Not started"), wxT("WIP"), wxT("Canceled"), wxT("Done"), wxT("Blocked") };
	int m_status_choiceNChoices = sizeof(m_status_choiceChoices) / sizeof(wxString);
	m_status_choice = new wxChoice(m_main_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_status_choiceNChoices, m_status_choiceChoices, 0);
	m_status_choice->SetSelection(0);
	bSizer48->Add(m_status_choice, 0, wxALL, 5);

	fgSizer1->Add(bSizer48, 1, 0, 5);

	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer(wxHORIZONTAL);

	m_deadline_static = new wxStaticText(m_main_panel, wxID_ANY, wxT("Due Date"), wxDefaultPosition, wxDefaultSize, 0);
	m_deadline_static->Wrap(-1);
	bSizer50->Add(m_deadline_static, 0, wxALL, 5);

	//must reset to show the current local time
	m_deadline_timepicker = new wxTimePickerCtrl(m_main_panel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxTP_DEFAULT);
	m_deadline_datepicker = new wxDatePickerCtrl(m_main_panel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
	this->ResetDeadlinePickers();

	bSizer50->Add(m_deadline_timepicker, 0, wxALL, 5);
	bSizer50->Add(m_deadline_datepicker, 0, wxALL, 5);

	fgSizer1->Add(bSizer50, 0, wxEXPAND, 5);

	m_enable_notifications = new wxCheckBox(m_main_panel, wxID_ANY, wxT("Enable Notifications"), wxDefaultPosition, wxDefaultSize, 0);
	m_enable_notifications->Set3StateValue(wxCheckBoxState::wxCHK_CHECKED);
	fgSizer1->Add(m_enable_notifications, 0, wxALL, 5);

	m_left_sizer->Add(fgSizer1, 1, wxEXPAND, 5);
	
	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer(wxHORIZONTAL);

	m_done_button = new wxButton(m_main_panel, wxID_ANY, wxT("Done"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer47->Add(m_done_button, 0, wxALL, 5);

	m_cancel_button = new wxButton(m_main_panel, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer47->Add(m_cancel_button, 0, wxALL, 5);

	m_left_sizer->Add(bSizer47, 0, wxALIGN_RIGHT, 5);

	m_main_panel_sizer->Add(m_left_sizer, 10, wxEXPAND, 5);
	m_main_panel_sizer->Add(m_right_sizer, 10, wxEXPAND, 5);

	m_main_panel->SetSizer(m_main_panel_sizer);
	m_main_panel->Layout();
	m_main_panel_sizer->Fit(m_main_panel);
	m_top_sizer->Add(m_main_panel, 1, wxEXPAND | wxALL, 5);



	m_new_task_timer = new wxTimer(this, wxID_ANY);

	// Bind the timer event to a handler
	Bind(wxEVT_TIMER, &mw::TaskPanel::OnNewTaskTimer, this);

	this->SetTheme();
	this->SetSizer(m_top_sizer);
	this->Layout();

	this->Bind(wxEVT_SIZE, &mw::TaskPanel::OnSize, this);

	m_done_button->Bind(wxEVT_BUTTON, &mw::TaskPanel::OnDoneButton, this);

}

mw::TaskPanel::~TaskPanel()
{
}

void mw::TaskPanel::DisableEditing()
{
	this->Freeze();
	this->Thaw();
}

void mw::TaskPanel::EnableEditing()
{
	this->Thaw();
}

void mw::TaskPanel::SetView(mw::TaskPanelView view)
{
	switch (view)
	{
	case TaskPanelView::DEFAULT:
		this->m_view_state = mw::TaskPanelView::DEFAULT;
		break;
	case TaskPanelView::BOTTOM:
		this->m_view_state = mw::TaskPanelView::BOTTOM;
		break;
	default:
		break;
	}
}

void mw::TaskPanel::OnDoneButton(wxCommandEvent& event)
{
	mw::Logger logger;
	mw::Controller& controller = mw::Controller::Get();

	mw::Project proj;
	controller.GetActiveProject(proj);
	if (proj.uid == 0)
	{
		logger.Warning("Active project UID is 0");
		return;
	}
	m_task.project_uid = proj.uid;

	m_task.name = this->m_task_name->GetLineText(0).ToStdString();


	if (m_task.name.find_first_not_of(" ") == std::string::npos)
	{
		m_task.name = "New Task";
	}

	size_t start = m_task.name.find_first_not_of(" ");
	m_task.name = m_task.name.substr(start);
	size_t end = m_task.name.find_last_not_of(" ");
	m_task.name = m_task.name.substr(0, end + 1);


	int num_of_lines = this->m_task_description->GetNumberOfLines();
	m_task.description.clear();
	for (int i = 0; i < num_of_lines; i++)
	{
		m_task.description += this->m_task_description->GetLineText(i).ToStdString();
		m_task.description += "\n";
	}


	m_task.notification_enabled = (m_enable_notifications->IsChecked() == true) ? true : false;

	this->SetTaskPriority();
	this->SetTaskStatus();
	this->SetTaskDeadline();
	controller.AddTask(m_task);
	this->Close();
	event.Skip();
}

void mw::TaskPanel::OnCancelButton(wxCommandEvent& event)
{
}

void mw::TaskPanel::SetTaskPriority()
{
	mw::Logger logger;
	switch (this->m_priority_choice->GetSelection())
	{
	case 0:
		m_task.priority = mw::Task::TaskPriority::HIGH;
		break;
	case 1:
		m_task.priority = mw::Task::TaskPriority::MEDIUM;
		break;
	case 2:
		m_task.priority = mw::Task::TaskPriority::LOW;
		break;
	case 3:
		m_task.priority = mw::Task::TaskPriority::SHOWSTOPPER;
		break;
	default:
		logger.Warning("Could not find a valid selection for the priority. Selecting Medium as a default value");
		m_task.priority = mw::Task::TaskPriority::MEDIUM;
		break;
	}
}

void mw::TaskPanel::SetTaskStatus()
{
	mw::Logger logger;
	switch (this->m_status_choice->GetSelection())
	{
	case 0:
		m_task.status = mw::Task::TaskStatus::NOTSTARTED;
		break;
	case 1:
		m_task.status = mw::Task::TaskStatus::WIP;
		break;
	case 2:
		m_task.status = mw::Task::TaskStatus::CANCELED;
		break;
	case 3:
		m_task.status = mw::Task::TaskStatus::DONE;
		break;
	case 4:
		m_task.status = mw::Task::TaskStatus::BLOCKED;
		break;
	default:
		logger.Warning("Could not find a valid selection for the status. Selecting NotStarted as a default value");
		m_task.status = mw::Task::TaskStatus::NOTSTARTED;
		break;
	}
}

void mw::TaskPanel::SetTaskDeadline()
{
	mw::Logger logger;
	int day = 0, mon = 1, year = 0;
	int hour = 0, min = 0, sec = 0;
	m_deadline_timepicker->GetTime(&hour, &min, &sec);
	wxDateTime date = m_deadline_datepicker->GetValue();
	day = date.GetDay();
	mon = date.GetMonth();
	year = date.GetYear();
	mw::DateTime deadline(sec, min, hour, day, mon, year);
	m_task.deadline = deadline.m_time_t;
}

void mw::TaskPanel::OnSize(wxSizeEvent& event)
{
	this->Layout();
	event.Skip();
}

void mw::TaskPanel::OnNewTaskTimer(wxTimerEvent& event)
{
	m_task_name->SetBackgroundColour(m_default_task_name_background_colour);
	m_task_name->Refresh();
}


void mw::TaskPanel::ResetDeadlinePickers()
{	
	std::time_t current_time = std::time(nullptr);
	wxDateTime now(current_time);
	m_deadline_timepicker->SetTime(now.GetHour() + 1, 0, 0);
	m_deadline_datepicker->SetValue(current_time);
}

void mw::TaskPanel::SetTheme(void)
{


	mw::Controller& controller = mw::Controller::Get();


	wxColour white(255, 255, 255);
	wxColour background = controller.m_backgroud_color;
	wxColour foreground = controller.m_forground_color;
	wxColour buttons_green(0, 136, 135);
	this->m_main_panel->SetBackgroundColour(background);
	this->m_status_static->SetForegroundColour(foreground);
	this->m_task_name_static->SetForegroundColour(foreground);
	this->m_priority_static->SetForegroundColour(foreground);
	this->m_deadline_static->SetForegroundColour(foreground);
	this->m_task_description_static->SetForegroundColour(foreground);
	this->m_enable_notifications->SetForegroundColour(foreground);
	this->Refresh();
}

void mw::TaskPanel::SetTask(const mw::Task& task)
{
	m_task = task;
	m_task_name->SetBackgroundColour(m_default_task_name_background_colour);
	m_task_name->SetLabelText(task.name);
	m_task_description->SetLabelText(task.description);
	m_priority_choice->Select(m_task.priority);
	m_status_choice->Select(m_task.status);
	wxDateTime deadline(task.deadline);
	m_deadline_datepicker->SetValue(deadline);
	m_deadline_timepicker->SetValue(deadline);
	wxCheckBoxState checkbox_state = (task.notification_enabled == true) ? wxCheckBoxState::wxCHK_CHECKED : wxCheckBoxState::wxCHK_UNCHECKED;
	m_enable_notifications->Set3StateValue(checkbox_state);
}

void mw::TaskPanel::SetNewTask()
{
	this->ClearTask();
	m_task_name->SetBackgroundColour(wxColour(0, 255, 0));
	m_task_name->SetFocus();
	m_new_task_timer->StartOnce(3000);

}

void mw::TaskPanel::ClearTask()
{
	mw::Task new_task;
	this->SetTask(new_task);
	this->ResetDeadlinePickers();
}
