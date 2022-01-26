#include "view/TasksWindow.h"

BEGIN_EVENT_TABLE(mw::TasksWindow, wxScrolledWindow)
	EVT_CUSTOM(mwUpdateUI, TASKS_WINDOW_ID, mw::TasksWindow::OnUpdateUI)
END_EVENT_TABLE()

mw::TasksWindow::TasksWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxScrolledWindow(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_tasks_sizer = new wxBoxSizer(wxVERTICAL);

	m_new_task_button = new wxButton(this, wxID_ANY, "New Task", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_new_task_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::TasksWindow::OnNewTaskButton), NULL, this);
	wxColour dark(37, 37, 38);
	wxColour green(0, 136, 135);

	m_new_task_button->SetBackgroundColour(dark);
	m_new_task_button->SetForegroundColour(green);
	m_tasks_sizer->Add(m_new_task_button, 0, wxALIGN_CENTER, 5);

	this->SetSizer(m_tasks_sizer);

	this->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::TasksWindow::OnTaskScrollWindowLeaveWindow), NULL, this);

	controller.RequestUpdateUI(this->GetId());
}

mw::TasksWindow::~TasksWindow()
{
	this->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::TasksWindow::OnTaskScrollWindowLeaveWindow));
}

void mw::TasksWindow::OnUpdateUI(wxEvent& event)
{
	m_new_task_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::TasksWindow::OnNewTaskButton), NULL, this);
	m_new_task_button->Destroy();
	m_new_task_button = new wxButton(this, wxID_ANY, "New Task", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_new_task_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::TasksWindow::OnNewTaskButton), NULL, this);
	wxColour dark(37, 37, 38);
	wxColour green(0, 136, 135);
	m_new_task_button->SetBackgroundColour(dark);
	m_new_task_button->SetForegroundColour(green);

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
			task_panel = new mw::TaskPanel(this);
			task_panel->SetTask(tasks[i]);
			m_taskpanel_to_task_map[task_panel] = tasks[i];
			m_tasks_sizer->Add(task_panel, 0, wxEXPAND | wxALL, 1);
		}
	}
	m_tasks_sizer->Add(m_new_task_button, 0, wxALIGN_CENTER, 5);
	wxSize size = this->GetBestVirtualSize();
	this->SetVirtualSize(size);
	this->m_tasks_sizer->Layout();
	this->Refresh();
}

void mw::TasksWindow::OnNewTaskButton(wxCommandEvent& event)
{
	mw::NewTaskFrame* new_task_frame = new mw::NewTaskFrame(this);
	new_task_frame->CenterOnScreen();
	new_task_frame->Show(true);
	event.Skip();
}

void mw::TasksWindow::OnTaskScrollWindowLeaveWindow(wxMouseEvent& event)
{
	std::map<mw::TaskPanel*, mw::Task>::iterator it;
	for (it = m_taskpanel_to_task_map.begin(); it != m_taskpanel_to_task_map.end(); ++it)
	{
		it->first->ResetBackGround();
	}
	event.Skip();
}
