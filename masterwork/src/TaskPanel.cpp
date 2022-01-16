#include "view/TaskPanel.h"


///////////////////////////////////////////////////////////////////////////

void mw::TaskPanel::OnEnterWindow(wxMouseEvent& event)
{
	this->SetBackgroundColour(wxColor(153, 180, 209));
	this->Refresh();
	event.Skip();
}

void mw::TaskPanel::OnleaveWindow(wxMouseEvent& event)
{
	wxRect task_panel_rect = this->GetScreenRect();
	wxPoint mouse_pos = wxGetMousePosition();
	if (!task_panel_rect.Contains(mouse_pos)) {
		this->SetBackgroundColour(wxColor(240, 240, 240));
		this->Refresh();
	}	
	event.Skip();
}

void mw::TaskPanel::OnEditTask(wxCommandEvent& event)
{
	mw::NewTaskFrame* new_task_frame = new mw::NewTaskFrame(this);
	new_task_frame->SetTask(m_task);
	new_task_frame->CenterOnScreen();
	new_task_frame->Show(true);
	event.Skip();
}

void mw::TaskPanel::OnDelete(wxCommandEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.DeleteTask(m_task);
	event.Skip();
}

void mw::TaskPanel::SetTask(mw::Task task)
{
	
	m_task = task;
	m_static_task_name->SetLabelText(m_task.name);
	m_static_description->SetLabelText(m_task.description);
	m_static_status->SetLabelText("Status: " + m_task.GetStatus());
	m_static_priority->SetLabelText("Priority: " + m_task.GetPriority());
	wxDateTime deadline(m_task.deadline);
	wxString date = deadline.FormatISODate();
	wxString time = deadline.FormatISOTime();
	m_static_duedate->SetLabelText("Due Date: " + time.ToStdString() + " " + date.ToStdString());
	wxDateTime last_modified(m_task.last_update);
	m_static_last_modified->SetLabelText("Last Modified: " + last_modified.FormatISOTime().ToStdString() + " " + last_modified.FormatISODate().ToStdString());
}

void mw::TaskPanel::ResetBackGround()
{
	this->SetBackgroundColour(wxColor(240, 240, 240));
	this->Refresh();
}

mw::TaskPanel::TaskPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	ver_task_sizer = new wxBoxSizer(wxVERTICAL);

	m_static_view = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer16 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer17 = new wxBoxSizer(wxVERTICAL);

	m_static_task_name = new wxStaticText(m_static_view, wxID_ANY, wxT("Task name"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_task_name->SetFont(wxFont().Bold());
	m_static_task_name->Wrap(-1);
	bSizer17->Add(m_static_task_name, 0, wxALL, 5);

	m_static_description = new wxStaticText(m_static_view, wxID_ANY, wxT("Task description"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_description->Wrap(-1);
	bSizer17->Add(m_static_description, 0, wxALL, 5);

	bSizer16->Add(bSizer17, 1, wxEXPAND, 5);



	wxGridSizer* m_info_grid_sizer;
	m_info_grid_sizer = new wxGridSizer(4, 2, 0, 0);

	m_static_status = new wxStaticText(m_static_view, wxID_ANY, wxT("Status: "), wxDefaultPosition, wxDefaultSize, 0);
	m_static_status->Wrap(-1);
	m_info_grid_sizer->Add(m_static_status, 0, wxALL, 5);

	m_static_duedate = new wxStaticText(m_static_view, wxID_ANY, wxT("Due date:"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_duedate->Wrap(-1);
	m_info_grid_sizer->Add(m_static_duedate, 0, wxALL, 5);

	m_static_priority = new wxStaticText(m_static_view, wxID_ANY, wxT("Priority:"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_priority->Wrap(-1);
	m_info_grid_sizer->Add(m_static_priority, 0, wxALL, 5);

	m_static_last_modified = new wxStaticText(m_static_view, wxID_ANY, wxT("Last Modified:"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_last_modified->Wrap(-1);
	m_info_grid_sizer->Add(m_static_last_modified, 0, wxALL, 5);

	bSizer16->Add(m_info_grid_sizer, 1, wxEXPAND, 5);


	m_edit_task = new wxButton(m_static_view, wxID_ANY, wxT("Edit"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer16->Add(m_edit_task, 0, wxALL, 5);

	m_delete_task = new wxButton(m_static_view, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer16->Add(m_delete_task, 0, wxALL, 5);

	m_static_view->SetSizer(bSizer16);
	m_static_view->Layout();
	bSizer16->Fit(m_static_view);
	ver_task_sizer->Add(m_static_view, 1, wxEXPAND | wxALL, 5);


	this->SetSizer(ver_task_sizer);
	this->Layout();

	// Connect Events
	this->Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(TaskPanel::OnEnterWindow));
	this->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(TaskPanel::OnleaveWindow));
	m_static_view->Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(TaskPanel::OnEnterWindow), NULL, this);
	m_static_view->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(TaskPanel::OnleaveWindow), NULL, this);
	m_edit_task->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TaskPanel::OnEditTask), NULL, this);
	m_delete_task->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TaskPanel::OnDelete), NULL, this);
}

mw::TaskPanel::~TaskPanel()
{
	// Disconnect Events
	this->Disconnect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(TaskPanel::OnEnterWindow));
	this->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(TaskPanel::OnleaveWindow));
	m_static_view->Disconnect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(TaskPanel::OnEnterWindow), NULL, this);
	m_static_view->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(TaskPanel::OnleaveWindow), NULL, this);
	m_edit_task->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TaskPanel::OnEditTask), NULL, this);
	m_delete_task->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TaskPanel::OnDelete), NULL, this);
}