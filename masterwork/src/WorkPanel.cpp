#include "view/WorkPanel.h"


BEGIN_EVENT_TABLE(mw::WorkPanel, wxPanel)
	EVT_CUSTOM(mwUpdateUI, WORK_PANEL_ID, mw::WorkPanel::OnUpdateUI)
END_EVENT_TABLE()

mw::WorkPanel::WorkPanel(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxPanel(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	this->SetBackgroundColour(wxColour(37, 37, 38));

	m_ver_sizer = new wxBoxSizer(wxVERTICAL);

	m_notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);
	m_tasks_scroll_window = new wxScrolledWindow(m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_tasks_scroll_window->SetScrollRate(5, 5);
	m_tasks_sizer = new wxBoxSizer(wxVERTICAL);

	m_tasks_scroll_window->SetSizer(m_tasks_sizer);
	m_notebook->AddPage(m_tasks_scroll_window, wxT("Tasks"), false);

	m_ver_sizer->Add(m_notebook, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(m_ver_sizer);
	this->Layout();

	// Connect Events
	m_notebook->Connect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler(mw::WorkPanel::OnPageChanged), NULL, this);
	m_notebook->Connect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING, wxNotebookEventHandler(mw::WorkPanel::OnPageChanging), NULL, this);
	m_tasks_scroll_window->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::WorkPanel::OnTaskScrollWindowLeaveWindow), NULL, this);
	controller.RequestUpdateUI(this->GetId());
}

mw::WorkPanel::~WorkPanel()
{
	// Disconnect Events
	m_notebook->Disconnect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler(mw::WorkPanel::OnPageChanged), NULL, this);
	m_notebook->Disconnect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING, wxNotebookEventHandler(mw::WorkPanel::OnPageChanging), NULL, this);
	m_tasks_scroll_window->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::WorkPanel::OnTaskScrollWindowLeaveWindow), NULL, this);

}

void mw::WorkPanel::OnPageChanged(wxNotebookEvent& event)
{
	event.Skip();
}

void mw::WorkPanel::OnPageChanging(wxNotebookEvent& event)
{
	event.Skip();
}

void mw::WorkPanel::OnTaskScrollWindowLeaveWindow(wxMouseEvent& event)
{
	std::map<mw::TaskPanel*, mwTask>::iterator it;
	for (it = m_taskpanel_to_task_map.begin(); it != m_taskpanel_to_task_map.end(); ++it)
	{
		it->first->ResetBackGround();
	}
	event.Skip();
}

void mw::WorkPanel::OnUpdateUI(wxEvent& event)
{
	std::map<mw::TaskPanel*, int>::iterator it;
	for (auto const& item : this->m_taskpanel_to_task_map)
	{
		item.first->Destroy();
	}
	std::vector<mwTask> tasks;
	mw::Controller& controller = mw::Controller::Get();
	controller.GetTasksForActiveProject(tasks);
	mw::TaskPanel* task_panel;
	m_taskpanel_to_task_map.clear();
	for (int i = 0; i < tasks.size(); i++)
	{
		task_panel = new mw::TaskPanel(m_tasks_scroll_window);
		task_panel->SetTask(tasks[i]);
		task_panel->SetBackgroundColour(wxColor(240, 240, 240));
		m_taskpanel_to_task_map[task_panel] = tasks[i];
		m_tasks_sizer->Add(task_panel, 0, wxEXPAND | wxALL, 1);
	}
	wxSize size = m_tasks_scroll_window->GetBestVirtualSize();
	m_tasks_scroll_window->SetVirtualSize(size);
	this->m_tasks_sizer->Layout();
}

void mw::WorkPanel::OnAppendTask(wxEvent& event)
{
}

