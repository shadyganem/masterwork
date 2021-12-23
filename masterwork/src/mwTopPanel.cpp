#include "view/mwTopPanel.h"

BEGIN_EVENT_TABLE(mwTopPanel, wxPanel)
	EVT_BUTTON(TOP_PANEL_NEW_TASK_ID, mwTopPanel::OnNewTaskButton)
	EVT_BUTTON(TOP_PANEL_NEW_PROJECT_ID, mwTopPanel::OnNewProjectButton)

END_EVENT_TABLE()

mwTopPanel::mwTopPanel(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
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
}

mwTopPanel::~mwTopPanel()
{
}

void mwTopPanel::OnNewTaskButton(wxCommandEvent& event)
{
	mwController& controller = mwController::Get();
	mwTask task;
	mwProject proj;
	controller.GetActiveProject(proj);
	task.name = "new task";
	task.description = "This is a new task";
	task.project_uid = proj.uid;
	controller.AddTask(task);
	event.Skip();
}

void mwTopPanel::OnNewProjectButton(wxCommandEvent& event)
{
	mwNewProject* new_project_form = new mwNewProject(this);
	new_project_form->Show(true);
}
