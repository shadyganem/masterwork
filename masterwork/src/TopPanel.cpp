#include "view/TopPanel.h"

BEGIN_EVENT_TABLE(mw::TopPanel, wxPanel)
	EVT_BUTTON(TOP_PANEL_NEW_TASK_ID, mw::TopPanel::OnNewTaskButton)
	EVT_BUTTON(TOP_PANEL_NEW_PROJECT_ID, mw::TopPanel::OnNewProjectButton)

END_EVENT_TABLE()

mw::TopPanel::TopPanel(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxPanel(parent, winid, pos, size, style, name)
{
	wxSizer* buttons_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxSizer* top_panel_sizer = new wxBoxSizer(wxHORIZONTAL);
	m_new_project = new wxButton(this, TOP_PANEL_NEW_PROJECT_ID, "New Project", wxDefaultPosition, wxDefaultSize);
	m_new_task = new wxButton(this, TOP_PANEL_NEW_TASK_ID, "New Task", wxDefaultPosition, wxDefaultSize);
	buttons_sizer->Add(this->m_new_project, 0, wxRIGHT, 3);
	buttons_sizer->Add(m_new_task, 0, wxRIGHT, 3);
	top_panel_sizer->Add(buttons_sizer);
	SetSizer(top_panel_sizer);
	this->SetTheme();
}

mw::TopPanel::~TopPanel()
{
}

void mw::TopPanel::OnNewTaskButton(wxCommandEvent& event)
{
	mw::NewTaskFrame* new_task_frame = new mw::NewTaskFrame(this);
	new_task_frame->CenterOnScreen();
	new_task_frame->Show(true);
	event.Skip();
}

void mw::TopPanel::OnNewProjectButton(wxCommandEvent& event)
{
	mw::NewProjectFrame* new_project_form = new mw::NewProjectFrame(this);
	new_project_form->CenterOnScreen();
	new_project_form->Show(true);
	event.Skip();
}

void mw::TopPanel::SetTheme(int theme_id)
{
	wxColour buttons_green(0, 136, 135);
	wxColour white(255, 255, 255);
	m_new_project->SetBackgroundColour(buttons_green);
	m_new_project->SetForegroundColour(white);
	m_new_task->SetBackgroundColour(buttons_green);
	m_new_task->SetForegroundColour(white);
}
