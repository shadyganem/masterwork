#include "view/RemindersWindow.h"
#include "view/WorkPanel.h"

BEGIN_EVENT_TABLE(mw::RemindersWindow, wxScrolledWindow)
EVT_CUSTOM(mwUpdateUI, REMINDERS_WINDOW_ID, mw::RemindersWindow::OnUpdateUI)
END_EVENT_TABLE()


mw::RemindersWindow::RemindersWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxScrolledWindow(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_reminders_sizer = new wxBoxSizer(wxVERTICAL);

	wxColour background = controller.m_backgroud_color;
	wxColour foreground = controller.m_foreground_color;
	wxToolBar* toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TEXT);

	wxColour green(0, 136, 135);

	m_new_reminder_button = new mw::Button(toolbar, wxID_ANY, "New Reminder", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_new_reminder_button->SetBackgroundColour(background);
	m_new_reminder_button->SetForegroundColour(green);
	toolbar->AddControl(m_new_reminder_button);


	toolbar->SetBackgroundColour(background);
	toolbar->SetForegroundColour(foreground);
	toolbar->Realize();

	m_reminders_sizer->Add(toolbar, 0, wxEXPAND);


	// instatiating m_reminders_data_view_list

	m_reminders_data_view_list = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_MULTIPLE | wxDV_HORIZ_RULES);

	m_reminders_data_view_list->AppendColumn(new wxDataViewColumn("Title", new wxDataViewTextRenderer(), 0, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_reminders_data_view_list->AppendColumn(new wxDataViewColumn("Status", new wxDataViewTextRenderer(), 1, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_reminders_data_view_list->AppendColumn(new wxDataViewColumn("Last Update", new wxDataViewTextRenderer(), 2, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));

	m_reminders_data_view_list->SetBackgroundColour(background);
	m_reminders_data_view_list->SetForegroundColour(foreground);

	m_reminders_sizer->Add(m_reminders_data_view_list, 1, wxEXPAND, 0);

	this->SetBackgroundColour(background);
	this->SetSizer(m_reminders_sizer);
	this->Layout();
	this->Bind(wxEVT_MENU, &mw::RemindersWindow::OnDeleteReminderClick, this, wxID_DELETE);
	m_new_reminder_button->Bind(wxEVT_BUTTON, &mw::RemindersWindow::OnNewReminderButton, this);
	m_reminders_data_view_list->Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &mw::RemindersWindow::OnContextMenu, this);

	controller.RequestUpdateUI(this->GetId());
}

mw::RemindersWindow::~RemindersWindow()
{
}

void mw::RemindersWindow::OnUpdateUI(wxEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	std::vector<mw::Reminder> reminders;
	controller.GetRemindersForActiveUser(reminders);
	m_reminders_data_view_list->DeleteAllItems();
	for (int i=0; i < reminders.size(); i++) 
	{
		this->AddRemider(reminders[i]);
		m_index_to_reminder_map[i] = reminders[i];
	}

	mw::WorkPanel* parent_work_panel = dynamic_cast<mw::WorkPanel*>(this->GetParent()->GetParent());
	parent_work_panel->UpdateRemindersCount(reminders.size());
}

void mw::RemindersWindow::OnContextMenu(wxDataViewEvent& event)
{
	// Get the mouse position
	wxPoint pos = event.GetPosition();

	// Convert the position to the client coordinates
	wxDataViewItem item;
	wxDataViewColumn* col;
	m_reminders_data_view_list->HitTest(pos, item, col);
	int row = m_reminders_data_view_list->ItemToRow(item);
	wxMenu menu;
	menu.Append(wxID_DELETE, "Delete");
	PopupMenu(&menu);
	event.Skip();
}

void mw::RemindersWindow::OnDeleteReminderClick(wxCommandEvent& event)
{
	int selected_items_count = m_reminders_data_view_list->GetSelectedItemsCount();
	if (selected_items_count == 0)
	{
		return;
	}
	std::vector<mw::Reminder> reminders_for_deletion;
	mw::Controller& controller = mw::Controller::Get();
	int answer = 0;
	if (selected_items_count == 1)
	{
		answer = wxMessageBox("Are you sure you want to permanently delete this reminder?", "Confirm", wxYES_NO, this);
	}
	else if (selected_items_count > 1)
	{
		answer = wxMessageBox("Are you sure you want to permanently delete all the selected reminders?", "Confirm", wxYES_NO, this);
	}

	if (answer == wxYES)
	{
		this->GetSelectedTasks(reminders_for_deletion);
		controller.DeleteReminders(reminders_for_deletion);
	}
}

void mw::RemindersWindow::AddRemider(mw::Reminder& reminder)
{
	wxVector<wxVariant> data;
	data.push_back(wxVariant(reminder.title));
	data.push_back(wxVariant(reminder.GetStatus()));
	data.push_back(wxVariant(reminder.GetLastUpdateTime()));
	m_reminders_data_view_list->AppendItem(data);
}

void mw::RemindersWindow::OnNewReminderButton(wxCommandEvent& event)
{
	mw::NewReminderFrame* new_reminder_frame = new mw::NewReminderFrame(this);
	new_reminder_frame->CenterOnScreen();
	new_reminder_frame->Show(true);
	//Do not propagate to parent. this will result in double handling of the button click
}

void mw::RemindersWindow::GetSelectedTasks(std::vector<mw::Reminder>& reminders)
{
	int row_count = m_reminders_data_view_list->GetItemCount();
	for (int i = 0; i < row_count; i++)
	{
		if (m_reminders_data_view_list->IsRowSelected(i))
		{
			reminders.push_back(m_index_to_reminder_map[i]);
		}
	}
}
