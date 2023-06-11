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

	wxColour background = controller.m_backgroud_color;
	wxColour foreground = controller.m_forground_color;



	wxToolBar* toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TEXT);


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




	//m_remiders_list_view = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,	wxLC_REPORT | wxLC_VRULES);
	//m_column_to_index_map["Title"] = 0;
	//m_remiders_list_view->InsertColumn(0, "Title", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE_USEHEADER);
	//
	//m_column_to_index_map["Status"] = 1;
	//m_remiders_list_view->InsertColumn(1, "Status", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE_USEHEADER);
	//
	//m_column_to_index_map["Last Update"] = 2;
	//m_remiders_list_view->InsertColumn(2, "Last Update", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE_USEHEADER);


	//m_remiders_list_view->SetBackgroundColour(background);
	//m_remiders_list_view->SetForegroundColour(foreground);

	//m_reminders_sizer->Add(m_remiders_list_view, 0, wxEXPAND | wxALL, 0);

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

	m_reminders_data_view_list->DeleteAllItems();

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
	wxVector<wxVariant> data;
	data.push_back(wxVariant(reminder.title));
	data.push_back(wxVariant(reminder.GetStatus()));
	data.push_back(wxVariant(reminder.GetEndTime()));
	m_reminders_data_view_list->AppendItem(data);
}