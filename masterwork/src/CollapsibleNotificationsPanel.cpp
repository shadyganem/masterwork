#include "view/CollapsibleNotificationsPanel.h"

BEGIN_EVENT_TABLE(mw::CollapsibleNotificationsPanel, wxPanel)
	EVT_CUSTOM(mwUpdateUI, COLLAPSIBLE_NOTIFICATIONS_PANEL_ID, mw::CollapsibleNotificationsPanel::OnUpdateUI)
END_EVENT_TABLE()

mw::CollapsibleNotificationsPanel::CollapsibleNotificationsPanel(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxPanel(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	wxBoxSizer* m_main_sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* m_notifications_sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* m_static_title = new wxStaticText(this, wxID_ANY, "Notifications");
	wxColour dark(37, 37, 38);
	wxColour green(0, 136, 135);
	m_static_title->SetBackgroundColour(dark);
	m_static_title->SetForegroundColour(green);
	wxFont font = m_static_title->GetFont();
	m_static_title->SetFont(font.Scale(1.5));

	m_main_sizer->Add(m_static_title, 0, wxALIGN_CENTER | wxTOP , 5);

	m_notifications_window = new mw::NotificationsWindow(this, NOTIFICATIONS_WINDOW_ID, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
	m_notifications_window->SetScrollRate(5, 5);

	m_main_sizer->Add(m_notifications_window, 1, wxALL | wxEXPAND, 0);
	this->SetSizer(m_main_sizer);
}

mw::CollapsibleNotificationsPanel::~CollapsibleNotificationsPanel()
{
}

void mw::CollapsibleNotificationsPanel::OnUpdateUI(wxEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
}
