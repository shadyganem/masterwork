#include "view/ArchiveWindow.h"
BEGIN_EVENT_TABLE(mw::ArchiveWindow, wxScrolledWindow)
EVT_CUSTOM(mwUpdateUI, ARCHIVE_WINDOW_ID, mw::ArchiveWindow::OnUpdateUI)
END_EVENT_TABLE()

mw::ArchiveWindow::ArchiveWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxScrolledWindow(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_tasks_sizer = new wxBoxSizer(wxVERTICAL);

	this->SetSizer(m_tasks_sizer);

	this->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::ArchiveWindow::OnTaskScrollWindowLeaveWindow), NULL, this);

	controller.RequestUpdateUI(this->GetId());
}

mw::ArchiveWindow::~ArchiveWindow()
{
	this->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::ArchiveWindow::OnTaskScrollWindowLeaveWindow));
}

void mw::ArchiveWindow::OnUpdateUI(wxEvent& event)
{
	mw::Logger logger;
	logger.SetLogLevel(mw::LogLevel::DEBUG);
	std::vector<mw::Task> tasks;
	mw::Controller& controller = mw::Controller::Get();
	controller.GetArchiveTasksForActiveProject(tasks);


	logger.SetLogLevel(mw::LogLevel::DISABLE);

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
			task_panel->HideArchiveButton();
			task_panel->ShowUnarchiveButton();
			task_panel->DisableEditing();
			task_panel->SetTask(tasks[i]);
			m_taskpanel_to_task_map[task_panel] = tasks[i];
			m_tasks_sizer->Add(task_panel, 0, wxEXPAND | wxALL, 1);
		}
	}
	wxSize size = this->GetBestVirtualSize();
	this->SetVirtualSize(size);
	this->m_tasks_sizer->Layout();
	this->Refresh();
}

void mw::ArchiveWindow::OnTaskScrollWindowLeaveWindow(wxMouseEvent& event)
{
	std::map<mw::TaskPanel*, mw::Task>::iterator it;
	for (it = m_taskpanel_to_task_map.begin(); it != m_taskpanel_to_task_map.end(); ++it)
	{
		it->first->ResetBackGround();
	}
	event.Skip();
}