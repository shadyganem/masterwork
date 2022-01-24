#include "view/TaskEditPanel.h"


mw::TaskEditPanel::TaskEditPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) : wxPanel(parent, id, pos, size, style)
{
	this->SetForegroundColour(wxColour(255, 255, 255));
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW));

	wxBoxSizer* m_top_sizer;
	m_top_sizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* m_form_sizer;
	m_form_sizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer(wxHORIZONTAL);

	m_task_name_static = new wxStaticText(this, wxID_ANY, wxT("Task Name"), wxDefaultPosition, wxDefaultSize, 0);
	m_task_name_static->Wrap(-1);
	bSizer65->Add(m_task_name_static, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	m_task_name = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CAPITALIZE);
	bSizer65->Add(m_task_name, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	m_form_sizer->Add(bSizer65, 0, wxEXPAND, 5);

	m_task_description_static = new wxStaticText(this, wxID_ANY, wxT("Task Description"), wxDefaultPosition, wxDefaultSize, 0);
	m_task_description_static->Wrap(-1);
	m_form_sizer->Add(m_task_description_static, 0, wxALL | wxEXPAND, 5);

	m_task_description = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CAPITALIZE | wxTE_MULTILINE | wxTE_RICH);
	m_form_sizer->Add(m_task_description, 1, wxALL | wxEXPAND, 5);

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer(3, 2, 0, 0);

	wxBoxSizer* bSizer48;
	bSizer48 = new wxBoxSizer(wxHORIZONTAL);

	m_priority_static = new wxStaticText(this, wxID_ANY, wxT("Priority"), wxDefaultPosition, wxDefaultSize, 0);
	m_priority_static->Wrap(-1);
	bSizer48->Add(m_priority_static, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	wxString m_priority_choiceChoices[] = { wxT("High"), wxT("Medium"), wxT("Low"), wxT("ShowStopper") };
	int m_priority_choiceNChoices = sizeof(m_priority_choiceChoices) / sizeof(wxString);
	m_priority_choice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_priority_choiceNChoices, m_priority_choiceChoices, 0);
	m_priority_choice->SetSelection(1);
	bSizer48->Add(m_priority_choice, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	gSizer2->Add(bSizer48, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer(wxHORIZONTAL);

	m_status_static = new wxStaticText(this, wxID_ANY, wxT("Status"), wxDefaultPosition, wxDefaultSize, 0);
	m_status_static->Wrap(-1);
	bSizer63->Add(m_status_static, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	wxString m_status_choiceChoices[] = { wxT("Not started"), wxT("WIP"), wxT("Canceled"), wxT("Done"), wxT("Blocked") };
	int m_status_choiceNChoices = sizeof(m_status_choiceChoices) / sizeof(wxString);
	m_status_choice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_status_choiceNChoices, m_status_choiceChoices, 0);
	m_status_choice->SetSelection(0);
	bSizer63->Add(m_status_choice, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	gSizer2->Add(bSizer63, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer(wxHORIZONTAL);

	m_deadline_static = new wxStaticText(this, wxID_ANY, wxT("Due Date"), wxDefaultPosition, wxDefaultSize, 0);
	m_deadline_static->Wrap(-1);
	bSizer50->Add(m_deadline_static, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	m_hour_spin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 23, 12);
	bSizer50->Add(m_hour_spin, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	m_spinCtrl6 = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 59, 0);
	bSizer50->Add(m_spinCtrl6, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	m_datePicker2 = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT);
	bSizer50->Add(m_datePicker2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	gSizer2->Add(bSizer50, 1, wxEXPAND, 5);

	m_form_sizer->Add(gSizer2, 1, wxEXPAND, 5);

	m_top_sizer->Add(m_form_sizer, 10, wxEXPAND, 5);

	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer(wxHORIZONTAL);

	m_done_button = new wxButton(this, wxID_ANY, wxT("Done"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer47->Add(m_done_button, 0, wxALL, 5);

	m_cancel_button = new wxButton(this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer47->Add(m_cancel_button, 0, wxALL, 5);

	m_top_sizer->Add(bSizer47, 0, wxALIGN_RIGHT, 5);

	this->SetSizer(m_top_sizer);
	this->Layout();

	// Connect Events
	m_done_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TaskEditPanel::OnDoneButton), NULL, this);
	m_cancel_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TaskEditPanel::OnCancelButton), NULL, this);
}

mw::TaskEditPanel::~TaskEditPanel()
{
	// Disconnect Events
	m_done_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TaskEditPanel::OnDoneButton), NULL, this);
	m_cancel_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TaskEditPanel::OnCancelButton), NULL, this);
}
