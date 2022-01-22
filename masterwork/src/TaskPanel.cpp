#include "view/TaskPanel.h"


///////////////////////////////////////////////////////////////////////////

void mw::TaskPanel::OnEnterWindow(wxMouseEvent& event)
{
	this->Highlight();
	event.Skip();
}

void mw::TaskPanel::OnleaveWindow(wxMouseEvent& event)
{
	wxRect task_panel_rect = this->GetScreenRect();
	wxPoint mouse_pos = wxGetMousePosition();
	if (!task_panel_rect.Contains(mouse_pos)) {
		this->SetDarkTheme();
	}	
	event.Skip();
}

void mw::TaskPanel::OnLeftDoubleClick(wxMouseEvent& event)
{
	mw::NewTaskFrame* new_task_frame = new mw::NewTaskFrame(this);
	new_task_frame->SetTask(m_task);
	new_task_frame->CenterOnScreen();
	new_task_frame->Show(true);
	event.Skip();
}

void mw::TaskPanel::OnArchive(wxCommandEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.DeleteTask(m_task);
	event.Skip();
}

void mw::TaskPanel::SetTask(mw::Task task)
{	
	m_task = task;
	m_static_task_name->SetLabelText(m_task.name);
	m_static_task_name->SetToolTip(m_task.description);
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
	this->SetDarkTheme();	
}

mw::TaskPanel::TaskPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* main_sizer = new wxBoxSizer(wxHORIZONTAL);


	wxBoxSizer* bSizer17 = new wxBoxSizer(wxHORIZONTAL);
	m_static_task_name = new wxStaticText(this, wxID_ANY, wxT("Task name"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_task_name->SetFont(wxFont().Bold());
	m_static_task_name->Wrap(-1);
	bSizer17->Add(m_static_task_name, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	m_static_description = new wxStaticText(this, wxID_ANY, wxT("Task description"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_description->Wrap(-1);
	m_static_description->Hide();
	bSizer17->Add(m_static_description, 1, wxALL, 5);

	main_sizer->Add(bSizer17, 1, wxEXPAND, 5);



	wxGridSizer* m_info_grid_sizer;
	m_info_grid_sizer = new wxGridSizer(2, 3, 0, 0);

	m_static_status = new wxStaticText(this, wxID_ANY, wxT("Status: "), wxDefaultPosition, wxDefaultSize, 0);
	m_static_status->Wrap(-1);
	m_info_grid_sizer->Add(m_static_status, 0, wxALL, 5);

	m_static_duedate = new wxStaticText(this, wxID_ANY, wxT("Due date:"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_duedate->Wrap(-1);
	m_info_grid_sizer->Add(m_static_duedate, 0, wxALL, 5);

	m_static_priority = new wxStaticText(this, wxID_ANY, wxT("Priority:"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_priority->Wrap(-1);
	m_info_grid_sizer->Add(m_static_priority, 0, wxALL, 5);

	m_static_last_modified = new wxStaticText(this, wxID_ANY, wxT("Last Modified:"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_last_modified->Wrap(-1);
	m_info_grid_sizer->Add(m_static_last_modified, 0, wxALL, 5);

	main_sizer->Add(m_info_grid_sizer, 1, wxEXPAND | wxALIGN_CENTER_VERTICAL, 5);

	m_archive_task = new wxButton(this, wxID_ANY, wxT("Archive"), wxDefaultPosition, wxDefaultSize, 0);
	main_sizer->Add(m_archive_task, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	this->SetSizer(main_sizer);
	this->SetDarkTheme();

	// Connect Events
	this->Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(TaskPanel::OnEnterWindow));
	this->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(TaskPanel::OnleaveWindow));
	this->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(TaskPanel::OnLeftDoubleClick));
	m_static_task_name->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(TaskPanel::OnLeftDoubleClick), NULL, this);
	m_static_task_name->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(TaskPanel::OnleaveWindow), NULL, this);
	m_static_status->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(TaskPanel::OnLeftDoubleClick), NULL, this);
	m_static_duedate->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(TaskPanel::OnLeftDoubleClick), NULL, this);
	m_static_priority->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(TaskPanel::OnLeftDoubleClick), NULL, this);
	m_static_last_modified->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(TaskPanel::OnLeftDoubleClick), NULL, this);
	m_archive_task->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TaskPanel::OnArchive), NULL, this);

}

mw::TaskPanel::~TaskPanel()
{
	// Disconnect Events
	this->Disconnect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(TaskPanel::OnEnterWindow));
	this->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(TaskPanel::OnleaveWindow));
	this->Disconnect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(TaskPanel::OnLeftDoubleClick));
	m_static_task_name->Disconnect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(TaskPanel::OnLeftDoubleClick), NULL, this);
	m_static_task_name->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(TaskPanel::OnleaveWindow), NULL, this);
	m_static_status->Disconnect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(TaskPanel::OnLeftDoubleClick), NULL, this);
	m_static_duedate->Disconnect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(TaskPanel::OnLeftDoubleClick), NULL, this);
	m_static_priority->Disconnect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(TaskPanel::OnLeftDoubleClick), NULL, this);
	m_static_last_modified->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(TaskPanel::OnLeftDoubleClick), NULL, this);
	m_archive_task->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TaskPanel::OnArchive), NULL, this);
}

void mw::TaskPanel::SetDarkTheme(void)
{
	wxColour white(255, 255, 255);
	wxColour dark(74, 74, 74);
	wxColour buttons_green(0, 136, 135);
	this->SetBackgroundColour(dark);
	m_static_task_name->SetForegroundColour(white);
	m_static_status->SetForegroundColour(white);
	m_static_duedate->SetForegroundColour(white);
	m_static_priority->SetForegroundColour(white);
	m_static_last_modified->SetForegroundColour(white);
	m_archive_task->SetBackgroundColour(buttons_green);
	m_archive_task->SetForegroundColour(white);
	this->Refresh();
}

void mw::TaskPanel::Highlight()
{
	wxColour highlighted_dark(153, 153, 153);
	this->SetBackgroundColour(highlighted_dark);
	this->Refresh();
}
