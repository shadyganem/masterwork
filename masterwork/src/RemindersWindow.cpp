#include "view/RemindersWindow.h"

BEGIN_EVENT_TABLE(mw::RemindersWindow, wxScrolledWindow)
EVT_CUSTOM(mwUpdateUI, REMINDERS_WINDOW_ID, mw::RemindersWindow::OnUpdateUI)
END_EVENT_TABLE()


mw::RemindersWindow::RemindersWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxScrolledWindow(parent, winid, pos, size, style, name)
{



	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_reminders_sizer = new wxBoxSizer(wxVERTICAL);

	
	m_remiders_list_view = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,	wxLC_REPORT | wxLC_VRULES);
	m_column_to_index_map["Title"] = 0;
	m_remiders_list_view->InsertColumn(0, "Title", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE_USEHEADER);
	
	m_column_to_index_map["Status"] = 1;
	m_remiders_list_view->InsertColumn(1, "Status", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE_USEHEADER);
	
	m_column_to_index_map["Last Update"] = 2;
	m_remiders_list_view->InsertColumn(2, "Last Update", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE_USEHEADER);


	wxColour background = controller.m_backgroud_color;
	wxColour forground = controller.m_forground_color;
	m_remiders_list_view->SetBackgroundColour(background);
	m_remiders_list_view->SetForegroundColour(forground);

	m_reminders_sizer->Add(m_remiders_list_view, 0, wxEXPAND | wxALL, 0);

	this->SetBackgroundColour(background);
	this->SetSizer(m_reminders_sizer);
	this->Layout();

	this->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::RemindersWindow::OnTaskScrollWindowLeaveWindow), NULL, this);
	controller.RequestUpdateUI(this->GetId());
}

mw::RemindersWindow::~RemindersWindow()
{
	this->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::RemindersWindow::OnTaskScrollWindowLeaveWindow));

}

void mw::RemindersWindow::OnUpdateUI(wxEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();



	std::vector<mw::Reminder> reminders;
	controller.GetRemindersForActiveUser(reminders);


	m_remiders_list_view->DeleteAllItems();

	for (int i=0; i < reminders.size(); i++) 
	{
		this->AddRemider(reminders[i]);
	}

}

void mw::RemindersWindow::OnTaskScrollWindowLeaveWindow(wxMouseEvent& event)
{
}

void mw::RemindersWindow::AddRemider(mw::Reminder& reminder)
{
	mw::Logger logger;

	logger.EnableDebug();

	logger.Debug(reminder.title);

	logger.Disable();
	wxListItem list_item;
	list_item.SetId(m_remiders_list_view->GetItemCount());

	list_item.SetColumn(0);
	list_item.SetText(reminder.title);
	m_remiders_list_view->InsertItem(list_item);

	list_item.SetText(std::to_string(reminder.status));
	list_item.SetColumn(1);
	m_remiders_list_view->SetItem(list_item);


	// Convert the epoch timestamp to a struct tm
	std::tm* timeinfo = std::localtime(&reminder.last_update);

	// Format the date and time as a string
	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
	std::string last_update = buffer;

	list_item.SetText(last_update);
	list_item.SetColumn(2);
	m_remiders_list_view->SetItem(list_item);


}