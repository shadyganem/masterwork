#include "view/mwWorkPanel.h"


BEGIN_EVENT_TABLE(mwWorkPanel, wxPanel)
END_EVENT_TABLE()

mwWorkPanel::mwWorkPanel(wxWindow* parent, 
	                     wxWindowID winid, 
	                     const wxPoint& pos, 
	                     const wxSize& size, 
	                     long style, 
	                     const wxString& name) : wxPanel(parent, winid, pos, size, style, name)
{
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
	m_notebook->Connect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler(mwWorkPanel::OnPageChanged), NULL, this);
	m_notebook->Connect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING, wxNotebookEventHandler(mwWorkPanel::OnPageChanging), NULL, this);
}

void mwWorkPanel::OnPageChanged(wxNotebookEvent& event)
{
	event.Skip();
}

void mwWorkPanel::OnPageChanging(wxNotebookEvent& event)
{
	event.Skip();
}

void mwWorkPanel::OnUpdateUI()
{
	mwLogger logger;
	logger.Info("updating worker panel ui");
	std::vector<mwTask> tasks;
	mwController& controller = mwController::Get();
	controller.GetTasksForActiveProject(tasks);
	logger.Info("before carshing");
	mwTaskPanel* task_panel;
	m_taskpanel_to_task_map.clear();
	for (int i = 0; i < tasks.size(); i++)
	{
		task_panel = new mwTaskPanel(m_tasks_scroll_window);
		task_panel->SetBackgroundColour(wxColor(240, 240, 240));
		m_taskpanel_to_task_map[task_panel] = tasks[i];
		m_tasks_sizer->Add(task_panel, 0, wxEXPAND | wxALL, 1);
	}
	this->m_tasks_sizer->Layout();
}

mwWorkPanel::~mwWorkPanel()
{
	// Disconnect Events
	m_notebook->Disconnect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler(mwWorkPanel::OnPageChanged), NULL, this);
	m_notebook->Disconnect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING, wxNotebookEventHandler(mwWorkPanel::OnPageChanging), NULL, this);
}


