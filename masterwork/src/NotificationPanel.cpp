#include "view/NotificationPanel.h"

mw::NotificationPanel::NotificationPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) : wxPanel(parent, id, pos, size, style)
{
	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer(wxHORIZONTAL);

	m_static_notification = new wxStaticText(this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_notification->Wrap(-1);
	bSizer39->Add(m_static_notification, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	m_dismiss_button = new mw::Button(this, wxID_ANY, wxT("X"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT | wxNO_BORDER);
	m_dismiss_button->SetHoverColour(wxColor(255, 0, 0));
	//m_dismiss_button->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), 74, 90, 92, false, wxEmptyString));

	bSizer39->Add(m_dismiss_button, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	this->SetSizer(bSizer39);
	this->SetTheme();

	this->Layout();

	// Connect Events
	m_dismiss_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NotificationPanel::OnDismiss), NULL, this);

}

mw::NotificationPanel::~NotificationPanel()
{
	m_dismiss_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NotificationPanel::OnDismiss), NULL, this);
}

void mw::NotificationPanel::OnDismiss(wxCommandEvent& event)
{
	mw::Controller &controller = mw::Controller::Get();
	m_notification.DecrementRepeat();
	controller.UpdateNotification(m_notification);
}

void mw::NotificationPanel::SetNotification(mw::Notification& notification)
{
	m_notification = notification;

	m_static_notification->SetLabel(m_notification.text);
}

void mw::NotificationPanel::SetTheme()
{
	wxColour green(0, 136, 135);
	this->SetBackgroundColour(wxColor(74, 74, 74));
	m_dismiss_button->SetBackgroundColour(wxColor(74, 74, 74));
	m_dismiss_button->SetForegroundColour(green);
	m_static_notification->SetBackgroundColour(wxColor(74, 74, 74));
	m_static_notification->SetForegroundColour(wxColor(255, 255, 255));

}
