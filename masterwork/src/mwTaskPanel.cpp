#include "view/mwTaskPanel.h"


///////////////////////////////////////////////////////////////////////////

void mwTaskPanel::OnEnterWindow(wxMouseEvent& event)
{
	this->SetBackgroundColour(wxColor(153, 180, 209));
	this->Refresh();
	event.Skip();
}

void mwTaskPanel::OnleaveWindow(wxMouseEvent& event)
{
	wxRect task_panel_rect = this->GetScreenRect();
	wxPoint mouse_pos = wxGetMousePosition();
	if (!task_panel_rect.Contains(mouse_pos)) {
		this->SetBackgroundColour(wxColor(240, 240, 240));
		this->Refresh();
	}	
	event.Skip();
}

void mwTaskPanel::OnEditTask(wxCommandEvent& event)
{
	mwNewTaskFrame* new_task_frame = new mwNewTaskFrame(this);
	new_task_frame->SetTask(m_task);
	new_task_frame->Show(true);
	event.Skip();
}

void mwTaskPanel::OnDelete(wxCommandEvent& event)
{
	mwController& controller = mwController::Get();
	controller.DeleteTask(m_task);
	event.Skip();
}

void mwTaskPanel::SetTask(mwTask task)
{
	m_task = task;
	m_static_task_name->SetLabelText(m_task.name);
	m_static_description->SetLabelText(m_task.description);
}

mwTaskPanel::mwTaskPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	ver_task_sizer = new wxBoxSizer(wxVERTICAL);

	m_static_view = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer16 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer17 = new wxBoxSizer(wxVERTICAL);

	m_static_task_name = new wxStaticText(m_static_view, wxID_ANY, wxT("Task name"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_task_name->Wrap(-1);
	bSizer17->Add(m_static_task_name, 0, wxALL, 5);

	m_static_description = new wxStaticText(m_static_view, wxID_ANY, wxT("Task description"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_description->Wrap(-1);
	bSizer17->Add(m_static_description, 0, wxALL, 5);

	bSizer16->Add(bSizer17, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer(wxVERTICAL);

	bSizer16->Add(bSizer18, 1, wxEXPAND, 5);

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
	this->Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(mwTaskPanel::OnEnterWindow));
	this->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mwTaskPanel::OnleaveWindow));
	m_static_view->Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(mwTaskPanel::OnEnterWindow), NULL, this);
	m_static_view->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mwTaskPanel::OnleaveWindow), NULL, this);
	m_edit_task->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwTaskPanel::OnEditTask), NULL, this);
	m_delete_task->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwTaskPanel::OnDelete), NULL, this);
}

mwTaskPanel::~mwTaskPanel()
{
	// Disconnect Events
	this->Disconnect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(mwTaskPanel::OnEnterWindow));
	this->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mwTaskPanel::OnleaveWindow));
	m_static_view->Disconnect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(mwTaskPanel::OnEnterWindow), NULL, this);
	m_static_view->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mwTaskPanel::OnleaveWindow), NULL, this);
	m_edit_task->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwTaskPanel::OnEditTask), NULL, this);
	m_delete_task->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwTaskPanel::OnDelete), NULL, this);
}