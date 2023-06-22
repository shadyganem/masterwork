#include "view/ArchiveWindow.h"
BEGIN_EVENT_TABLE(mw::ArchiveWindow, wxScrolledWindow)
EVT_CUSTOM(mwUpdateUI, ARCHIVE_WINDOW_ID, mw::ArchiveWindow::OnUpdateUI)
END_EVENT_TABLE()

mw::ArchiveWindow::ArchiveWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
	: wxScrolledWindow(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_tasks_sizer = new wxBoxSizer(wxVERTICAL);
	wxColour background = controller.m_backgroud_color;
	wxColour foreground = controller.m_foreground_color;
	wxColour green(0, 136, 135);

	wxToolBar* toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TEXT);
	
	toolbar->SetBackgroundColour(background);
	toolbar->SetForegroundColour(foreground);
	toolbar->Realize();

	m_tasks_sizer->Add(toolbar, 0, wxEXPAND);

	m_tasks_data_view_list = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_MULTIPLE | wxDV_HORIZ_RULES);


	m_tasks_data_view_list->AppendColumn(new wxDataViewColumn("Title", new wxDataViewTextRenderer(), 0, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_tasks_data_view_list->AppendColumn(new wxDataViewColumn("Status", new wxDataViewTextRenderer(), 1, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_tasks_data_view_list->AppendColumn(new wxDataViewColumn("Due Date", new wxDataViewTextRenderer(), 2, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_tasks_data_view_list->AppendColumn(new wxDataViewColumn("Priority", new wxDataViewTextRenderer(), 3, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_tasks_data_view_list->AppendColumn(new wxDataViewColumn("Last Modified", new wxDataViewTextRenderer(), 4, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));


	m_tasks_data_view_list->SetBackgroundColour(background);
	m_tasks_data_view_list->SetForegroundColour(foreground);

	m_tasks_sizer->Add(m_tasks_data_view_list, 1, wxEXPAND, 0);

	this->SetSizer(m_tasks_sizer);

	m_tasks_data_view_list->Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &mw::ArchiveWindow::OnItemContextMenu, this);

	controller.RequestUpdateUI(this->GetId());
}

mw::ArchiveWindow::~ArchiveWindow()
{
}

void mw::ArchiveWindow::OnUpdateUI(wxEvent& event)
{
	m_tasks_data_view_list->DeleteAllItems();
	std::vector<mw::Task> tasks;
	mw::Controller& controller = mw::Controller::Get();
	controller.GetArchiveTasksForActiveProject(tasks);
	for (int i = 0; i < tasks.size(); i++)
	{
		m_index_to_task_map[i] = tasks[i];
		this->AddTask(tasks[i]);
	}
}

void mw::ArchiveWindow::AddTask(mw::Task& task)
{
	wxVector<wxVariant> data;
	data.push_back(wxVariant(task.name));
	data.push_back(wxVariant(task.GetStatus()));
	data.push_back(wxVariant(task.GetDeadline()));
	data.push_back(wxVariant(task.GetPriority()));
	data.push_back(wxVariant(task.GetLastUpdate()));
	m_tasks_data_view_list->AppendItem(data);
}

void mw::ArchiveWindow::OnToolbarButtonClick(wxCommandEvent& event)
{
	int tool_id = event.GetId();

	switch (tool_id) {
	case wxID_NEW:
		// Handle the "New" button click
		break;
	default:
		break;
	}
}

void mw::ArchiveWindow::OnItemContextMenu(wxDataViewEvent& event)
{
	wxDataViewItem item = event.GetItem();
	if (item.IsOk())
	{
		wxMenu menu;
		// using wxID_REMOVE to archive tasks
		menu.Append(wxID_REMOVE, "Unarchive");
		menu.Append(wxID_DELETE, "Delete");
		Bind(wxEVT_MENU, &mw::ArchiveWindow::OnTaskUnarchieveClick, this, wxID_REMOVE);
		Bind(wxEVT_MENU, &mw::ArchiveWindow::OnTaskDeleteClick, this, wxID_DELETE);
		wxPoint pos = event.GetPosition();
		PopupMenu(&menu, pos);
	}
	event.Skip();
}

void mw::ArchiveWindow::OnTaskDeleteClick(wxCommandEvent& event)
{
	int selected_items_count = m_tasks_data_view_list->GetSelectedItemsCount();
	if (selected_items_count == 0)
	{
		return;
	}
	std::vector<mw::Task> tasks_for_deletion;
	mw::Controller& controller = mw::Controller::Get();
	int answer = 0;
	if (selected_items_count == 1)
	{ 
		answer = wxMessageBox("Are you sure you want to permanently delete this task?", "Confirm", wxYES_NO, this);
	}
	else if (selected_items_count > 1)
	{
		answer = wxMessageBox("Are you sure you want to permanently delete all the selected tasks?", "Confirm", wxYES_NO, this);
	}
	

	if (answer == wxYES)
	{
		int row_count = m_tasks_data_view_list->GetItemCount();

		for (int i = 0; i < row_count; i++)
		{
			if (m_tasks_data_view_list->IsRowSelected(i))
			{
				tasks_for_deletion.push_back(m_index_to_task_map[i]);
			}
		}
	}
	controller.DeleteTasks(tasks_for_deletion);
}

void mw::ArchiveWindow::OnTaskUnarchieveClick(wxCommandEvent& event)
{
	if (m_tasks_data_view_list->GetSelectedItemsCount() == 0)
	{
		return;
	}
	std::vector<mw::Task> tasks_for_unarchiving;
	mw::Controller& controller = mw::Controller::Get();

	int row_count = m_tasks_data_view_list->GetItemCount();

	for (int i = 0; i < row_count; i++)
	{
		if (m_tasks_data_view_list->IsRowSelected(i))
		{
			tasks_for_unarchiving.push_back(m_index_to_task_map[i]);
		}
	}
	controller.UnarchiveTasks(tasks_for_unarchiving);
}
