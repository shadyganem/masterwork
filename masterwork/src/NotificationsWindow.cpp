#include "view/NotificationsWindow.h"

BEGIN_EVENT_TABLE(mw::NotificationsWindow, wxPanel)
	EVT_CUSTOM(mwUpdateUI, NOTIFICATIONS_WINDOW_ID, mw::NotificationsWindow::OnUpdateUI)
END_EVENT_TABLE()

mw::NotificationsWindow::NotificationsWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxScrolledWindow(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_notifications_sizer = new wxBoxSizer(wxVERTICAL);

	this->SetSizer(m_notifications_sizer);
	controller.RequestUpdateUI(winid);
}

mw::NotificationsWindow::~NotificationsWindow()
{
}

void mw::NotificationsWindow::Clear()
{
	std::map<mw::NotificationPanel*, mw::Notification>::iterator it;
	for (it = m_notif_panel_to_notif_map.begin(); it != m_notif_panel_to_notif_map.end(); it++)
	{
		it->first->Destroy();
	}
	m_notif_panel_to_notif_map.clear();
}

void mw::NotificationsWindow::OnUpdateUI(wxEvent& event)
{
	this->Clear();
	mw::Controller& controller = mw::Controller::Get();

	std::vector<mw::Notification> notif_vect;

	controller.GetNotificationsForActiveUser(notif_vect);
	
	mw::NotificationPanel* panel;
	m_notif_panel_to_notif_map.clear();
	for (int i = 0; i < notif_vect.size(); i++)
	{

		panel = new mw::NotificationPanel(this);
		panel->SetNotification(notif_vect[i]);

		m_notifications_sizer->Add(panel, 0, wxEXPAND | wxALL, 1);

		m_notif_panel_to_notif_map[panel] = notif_vect[i];
		this->m_notifications_sizer->Layout();

	}
	this->m_notifications_sizer->Layout();
	wxSize size = this->GetBestVirtualSize();
	this->SetVirtualSize(size);
	event.Skip();
}
