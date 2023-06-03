#include "view/RemindersWindow.h"

mw::RemindersWindow::RemindersWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxScrolledWindow(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_reminders_sizer = new wxBoxSizer(wxVERTICAL);


	m_remiders_list_view = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,	wxLC_REPORT | wxLC_SINGLE_SEL);
	m_remiders_list_view->InsertColumn(0, "Column 1");
	m_remiders_list_view->InsertColumn(1, "Column 2");

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
	
	


}

void mw::RemindersWindow::OnTaskScrollWindowLeaveWindow(wxMouseEvent& event)
{
}

void mw::RemindersWindow::AddRemider(mw::Reminder& remider)
{

}
