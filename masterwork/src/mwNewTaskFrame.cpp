#include "view/mwNewTaskFrame.h"


mwNewTaskFrame::mwNewTaskFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* m_top_sizer;
	m_top_sizer = new wxBoxSizer(wxVERTICAL);

	m_main_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* m_main_panel_sizer;
	m_main_panel_sizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* m_form_sizer;
	m_form_sizer = new wxBoxSizer(wxVERTICAL);

	m_task_name_static = new wxStaticText(m_main_panel, wxID_ANY, wxT("Task Name"), wxDefaultPosition, wxDefaultSize, 0);
	m_task_name_static->Wrap(-1);
	m_form_sizer->Add(m_task_name_static, 0, wxALL, 5);

	m_task_name = new wxTextCtrl(m_main_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_form_sizer->Add(m_task_name, 0, wxALL | wxEXPAND, 5);

	m_task_description_static = new wxStaticText(m_main_panel, wxID_ANY, wxT("Task Description"), wxDefaultPosition, wxDefaultSize, 0);
	m_task_description_static->Wrap(-1);
	m_form_sizer->Add(m_task_description_static, 0, wxALL, 5);

	m_task_description = new wxTextCtrl(m_main_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_form_sizer->Add(m_task_description, 0, wxALL | wxEXPAND, 5);

	wxBoxSizer* bSizer48;
	bSizer48 = new wxBoxSizer(wxHORIZONTAL);

	m_priority_static = new wxStaticText(m_main_panel, wxID_ANY, wxT("Priority"), wxDefaultPosition, wxDefaultSize, 0);
	m_priority_static->Wrap(-1);
	bSizer48->Add(m_priority_static, 0, wxALL, 5);

	wxString m_priority_choiceChoices[] = { wxT("High"), wxT("Medium"), wxT("Low"), wxT("ShowStopper") };
	int m_priority_choiceNChoices = sizeof(m_priority_choiceChoices) / sizeof(wxString);
	m_priority_choice = new wxChoice(m_main_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_priority_choiceNChoices, m_priority_choiceChoices, 0);
	m_priority_choice->SetSelection(0);
	bSizer48->Add(m_priority_choice, 0, wxALL, 5);

	m_status_static = new wxStaticText(m_main_panel, wxID_ANY, wxT("Status"), wxDefaultPosition, wxDefaultSize, 0);
	m_status_static->Wrap(-1);
	bSizer48->Add(m_status_static, 0, wxALL, 5);

	wxString m_status_choiceChoices[] = { wxT("Not started"), wxT("WIP"), wxT("Canceled"), wxT("Done"), wxT("Blocked") };
	int m_status_choiceNChoices = sizeof(m_status_choiceChoices) / sizeof(wxString);
	m_status_choice = new wxChoice(m_main_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_status_choiceNChoices, m_status_choiceChoices, 0);
	m_status_choice->SetSelection(0);
	bSizer48->Add(m_status_choice, 0, wxALL, 5);

	m_form_sizer->Add(bSizer48, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer(wxHORIZONTAL);

	m_deadline_static = new wxStaticText(m_main_panel, wxID_ANY, wxT("Due Date"), wxDefaultPosition, wxDefaultSize, 0);
	m_deadline_static->Wrap(-1);
	bSizer50->Add(m_deadline_static, 0, wxALL, 5);

	m_hour_spin = new wxSpinCtrl(m_main_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 23, 12);
	bSizer50->Add(m_hour_spin, 0, wxALL, 5);

	m_spinCtrl6 = new wxSpinCtrl(m_main_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 59, 0);
	bSizer50->Add(m_spinCtrl6, 0, wxALL, 5);

	m_datePicker2 = new wxDatePickerCtrl(m_main_panel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT);
	bSizer50->Add(m_datePicker2, 0, wxALL, 5);

	m_form_sizer->Add(bSizer50, 1, wxEXPAND, 5);

	m_main_panel_sizer->Add(m_form_sizer, 10, wxEXPAND, 5);

	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer(wxHORIZONTAL);

	m_done_button = new wxButton(m_main_panel, wxID_ANY, wxT("Done"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer47->Add(m_done_button, 0, wxALL, 5);

	m_cancel_button = new wxButton(m_main_panel, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer47->Add(m_cancel_button, 0, wxALL, 5);

	m_main_panel_sizer->Add(bSizer47, 1, wxEXPAND, 5);

	m_main_panel->SetSizer(m_main_panel_sizer);
	m_main_panel->Layout();
	m_main_panel_sizer->Fit(m_main_panel);
	m_top_sizer->Add(m_main_panel, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(m_top_sizer);
	this->Layout();

	// Connect Events
	m_done_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwNewTaskFrame::OnDoneButton), NULL, this);
	m_cancel_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwNewTaskFrame::OnCancelButton), NULL, this);
}

mwNewTaskFrame::~mwNewTaskFrame()
{
	// Disconnect Events
	m_done_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwNewTaskFrame::OnDoneButton), NULL, this);
	m_cancel_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwNewTaskFrame::OnCancelButton), NULL, this);
}



void mwNewTaskFrame::OnCancelButton(wxCommandEvent& event)
{
	this->Close();
}

void mwNewTaskFrame::OnDoneButton(wxCommandEvent& event)
{

	mwLogger logger;
	mwController& controller = mwController::Get();

	mwTask new_task;
	mwProject proj;
	controller.GetActiveProject(proj);
	new_task.project_uid = proj.uid;


	new_task.name = this->m_task_name->GetLineText(0).ToStdString();
	new_task.description = this->m_task_description->GetLineText(0).ToStdString();

	switch (this->m_priority_choice->GetSelection())
	{
	case 0:
		new_task.priority = mwTask::TaskPriority::HIGH;
		break;
	case 1:
		new_task.priority = mwTask::TaskPriority::MEDIUM;
		break;
	case 2:
		new_task.priority = mwTask::TaskPriority::LOW;
		break;
	case 3:
		new_task.priority = mwTask::TaskPriority::SHOWSTOPPER;
		break;
	default:
		logger.Warning("Could not find a valid selection for the priority. Selecting Medium as a default value");
		new_task.priority = mwTask::TaskPriority::MEDIUM;
		break;
	}

	switch (this->m_status_choice->GetSelection())
	{
	case 0:
		new_task.status = mwTask::TaskStatus::NOTSTARTED;
		break;
	case 1:
		new_task.status = mwTask::TaskStatus::WIP;
		break;
	case 2:
		new_task.status = mwTask::TaskStatus::CANCELED;
		break;
	case 3:
		new_task.status = mwTask::TaskStatus::DONE;
		break;
	case 4:
		new_task.status = mwTask::TaskStatus::BLOCKED;
		break;
	default:
		logger.Warning("Could not find a valid selection for the status. Selecting NotStarted as a default value");
		new_task.status = mwTask::TaskStatus::NOTSTARTED;
		break;
	}


	controller.AddTask(new_task);

	
	this->Close();

}