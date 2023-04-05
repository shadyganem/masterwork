#include "view/RemindersWindow.h"

mw::RemindersWindow::RemindersWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_tasks_sizer = new wxBoxSizer(wxVERTICAL);

	this->SetSizer(m_tasks_sizer);

	this->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::RemindersWindow::OnTaskScrollWindowLeaveWindow), NULL, this);

	controller.RequestUpdateUI(this->GetId());
}

mw::RemindersWindow::~RemindersWindow()
{
	this->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::RemindersWindow::OnTaskScrollWindowLeaveWindow));

}

void mw::RemindersWindow::OnUpdateUI(wxEvent& event)
{
}

void mw::RemindersWindow::OnTaskScrollWindowLeaveWindow(wxMouseEvent& event)
{
}
