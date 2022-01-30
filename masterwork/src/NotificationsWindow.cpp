#include "view/NotificationsWindow.h"

BEGIN_EVENT_TABLE(mw::NotificationsWindow, wxPanel)
	EVT_CUSTOM(mwUpdateUI, NOTIFICATIONS_WINDOW_ID, mw::NotificationsWindow::OnUpdateUI)
END_EVENT_TABLE()

mw::NotificationsWindow::NotificationsWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxScrolledWindow(parent, winid, pos, size, style, name)
{
}

mw::NotificationsWindow::~NotificationsWindow()
{
}

void mw::NotificationsWindow::OnUpdateUI(wxEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();

}
