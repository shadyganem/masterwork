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

	m_new_task_button = new wxButton(m_tasks_scroll_window, wxID_ANY, "New Task", wxDefaultPosition, wxDefaultSize);
	wxColour buttons_green(0, 136, 135);
	wxColour white(255, 255, 255);
	m_new_task_button->SetBackgroundColour(buttons_green);
	m_new_task_button->SetForegroundColour(white);
	m_tasks_sizer->Add(m_new_task_button, 0, wxALIGN_CENTER, 5);

	m_tasks_scroll_window->SetSizer(m_tasks_sizer);
	m_notebook->AddPage(m_tasks_scroll_window, wxT("Tasks"), false);

	m_ver_sizer->Add(m_notebook, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(m_ver_sizer);
	this->Layout();

	// Connect Events
	this->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::WorkPanel::OnTaskScrollWindowLeaveWindow));
	m_notebook->Connect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler(mw::WorkPanel::OnPageChanged), NULL, this);
	m_notebook->Connect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING, wxNotebookEventHandler(mw::WorkPanel::OnPageChanging), NULL, this);
	m_notebook->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::WorkPanel::OnTaskScrollWindowLeaveWindow), NULL, this);
	m_new_task_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::WorkPanel::OnNewTaskButton), NULL, this);
	controller.RequestUpdateUI(this->GetId());
}

mw::WorkPanel::~WorkPanel()
{
	// Disconnect Events
	this->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::WorkPanel::OnTaskScrollWindowLeaveWindow));
	m_notebook->Disconnect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler(mw::WorkPanel::OnPageChanged), NULL, this);
	m_notebook->Disconnect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING, wxNotebookEventHandler(mw::WorkPanel::OnPageChanging), NULL, this);
	m_notebook->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::WorkPanel::OnTaskScrollWindowLeaveWindow), NULL, this);
	m_new_task_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::WorkPanel::OnNewTaskButton), NULL, this);

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
	std::map<mw::TaskPanel*, mw::Task>::iterator it;
	for (it = m_taskpanel_to_task_map.begin(); it != m_taskpanel_to_task_map.end(); ++it)
	{
		it->first->ResetBackGround();
	}
	event.Skip();
}

void mw::WorkPanel::OnNewTaskButton(wxCommandEvent& event)
{
	mw::NewTaskFrame* new_task_frame = new mw::NewTaskFrame(this);
	new_task_frame->CenterOnScreen();
	new_task_frame->Show(true);
	event.Skip();
}

void mw::WorkPanel::OnUpdateUI(wxEvent& event)
{
	m_new_task_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::WorkPanel::OnNewTaskButton), NULL, this);
	m_new_task_button->Destroy();
	m_new_task_button = new wxButton(m_tasks_scroll_window, wxID_ANY, "New Task", wxDefaultPosition, wxDefaultSize);
	m_new_task_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::WorkPanel::OnNewTaskButton), NULL, this);
	m_new_task_button->SetBackgroundColour(wxColour(0, 136, 135));
	m_new_task_button->SetForegroundColour(wxColour(255, 255, 255));

	std::vector<mw::Task> tasks;
	mw::Controller& controller = mw::Controller::Get();
	controller.GetTasksForActiveProject(tasks);

	std::map<int, bool> found_tasks;
	std::map<mw::TaskPanel*, int>::iterator it;

	for (auto const& item : this->m_taskpanel_to_task_map)
	{
		bool task_found = false;
		for (int i = 0; i < tasks.size(); i++)
		{
			if (item.second.uid == tasks[i].uid)
			{
				task_found = true;
				item.first->SetTask(tasks[i]);
				found_tasks[item.second.uid] = true;
				break;
			}
		}
		if (!task_found)
		{
			item.first->Destroy();
			m_taskpanel_to_task_map.erase(item.first);
		}
	}

	mw::TaskPanel* task_panel;
	
	for (int i = 0; i < tasks.size(); i++)
	{
		if (!found_tasks.count(tasks[i].uid))
		{
			task_panel = new mw::TaskPanel(m_tasks_scroll_window);
			task_panel->SetTask(tasks[i]);
			m_taskpanel_to_task_map[task_panel] = tasks[i];
			m_tasks_sizer->Add(task_panel, 0, wxEXPAND | wxALL, 1);
			
		}
	}
	m_tasks_sizer->Add(m_new_task_button, 0, wxALIGN_CENTER, 5);
	wxSize size = m_tasks_scroll_window->GetBestVirtualSize();
	m_tasks_scroll_window->SetVirtualSize(size);
	this->m_tasks_sizer->Layout();
	this->Refresh();
}

void mw::WorkPanel::OnAppendTask(wxEvent& event)
{
}

