#include "view/mwTopPanel.h"

BEGIN_EVENT_TABLE(mwTopPanel, wxPanel)
	EVT_BUTTON(TOP_PANEL_NEW_TASK_ID, mwTopPanel::OnNewTaskButton)
END_EVENT_TABLE()

mwTopPanel::mwTopPanel(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxPanel(parent, winid, pos, size, style, name)
{
	wxSizer* buttons_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxSizer* top_panel_sizer = new wxBoxSizer(wxHORIZONTAL);


	m_new_task = new wxButton(this, TOP_PANEL_NEW_TASK_ID, "New Task", wxDefaultPosition, wxDefaultSize);
	m_new_task->SetBackgroundColour(wxColor(61, 61, 61));
	m_new_task->SetForegroundColour(wxColor(255, 255, 255));
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
	wxString task_name = "new task";
	wxString task_dec = "Test DB";
	controller.AddTask(task_name.ToStdString(), task_dec.ToStdString());
	event.Skip();
}