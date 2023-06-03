#include "view/RemindersWindow.h"

mw::RemindersWindow::RemindersWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxScrolledWindow(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_reminders_sizer = new wxBoxSizer(wxVERTICAL);


	m_remiders_list_view = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,	wxLC_REPORT | wxLC_VRULES);
	m_remiders_list_view->InsertColumn(0, "Title");
	m_remiders_list_view->InsertColumn(1, "Status");
	m_remiders_list_view->InsertColumn(2, "Last Update");
	m_remiders_list_view->SetAlternateRowColour(wxColour(37, 37, 60));

	wxColour background = controller.m_backgroud_color;
	m_remiders_list_view->SetBackgroundColour(background);

	m_reminders_sizer->Add(m_remiders_list_view, 0, wxEXPAND | wxALL, 1);

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
	wxListItem list_item;
	list_item.SetColumn(0);
	list_item.SetText(reminder.title);
	m_remiders_list_view->InsertItem(list_item);

	list_item.SetText(std::to_string(reminder.status));
	list_item.SetColumn(1);
	m_remiders_list_view->SetItem(list_item);


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
