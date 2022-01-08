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
	mwNewTaskFrame* new_task_frame = new mwNewTaskFrame(this);
	new_task_frame->Show(true);
	event.Skip();
}

void mwTopPanel::OnNewProjectButton(wxCommandEvent& event)
{
	mw::NewProjectFrame* new_project_form = new mw::NewProjectFrame(this);
	new_project_form->CenterOnParent();
	new_project_form->Show(true);
	event.Skip();
}
