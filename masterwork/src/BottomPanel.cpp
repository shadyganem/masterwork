#include "view/BottomPanel.h"


BEGIN_EVENT_TABLE(mw::BottomPanel, wxPanel)
	
END_EVENT_TABLE()


mw::BottomPanel::BottomPanel(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxPanel(parent, winid, pos, size, style, name)
{
	this->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW));

	wxBoxSizer* m_ver_sizer;
	m_ver_sizer = new wxBoxSizer(wxVERTICAL);

	m_listbook = new wxListbook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_DEFAULT);
	m_listbook->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));

	m_notification_panel = new wxScrolledWindow(m_listbook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_notification_panel->SetScrollRate(5, 5);
	m_notification_panel->SetForegroundColour(wxColour(255, 255, 255));
	m_notification_panel->SetBackgroundColour(wxColour(37, 37, 38));

	wxBoxSizer* m_notifications_top_sizer;
	m_notifications_top_sizer = new wxBoxSizer(wxVERTICAL);

	m_notifications_text = new wxStaticText(m_notification_panel, wxID_ANY, wxT("Notifications are shown here!"), wxDefaultPosition, wxDefaultSize, 0);
	m_notifications_text->Wrap(-1);
	m_notifications_top_sizer->Add(m_notifications_text, 1, wxALL | wxEXPAND, 5);

	m_notification_panel->SetSizer(m_notifications_top_sizer);
	m_notification_panel->Layout();
	m_notifications_top_sizer->Fit(m_notification_panel);
	m_listbook->AddPage(m_notification_panel, wxT("notifications"), true);
	m_programming_panel = new wxScrolledWindow(m_listbook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_programming_panel->SetScrollRate(5, 5);
	m_listbook->AddPage(m_programming_panel, wxT("programming"), false);
#ifndef __WXGTK__ // Small icon style not supported in GTK
	wxListView* m_listbookListView = m_listbook->GetListView();
	long m_listbookFlags = m_listbookListView->GetWindowStyleFlag();
	m_listbookFlags = (m_listbookFlags & ~wxLC_ICON) | wxLC_SMALL_ICON;
	m_listbookListView->SetWindowStyleFlag(m_listbookFlags);
#endif

	m_ver_sizer->Add(m_listbook, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(m_ver_sizer);
	this->Layout();

	// Connect Events
	m_listbook->Connect(wxEVT_COMMAND_LISTBOOK_PAGE_CHANGED, wxListbookEventHandler(mw::BottomPanel::OnPageChaged), NULL, this);
}

mw::BottomPanel::~BottomPanel()
{
	m_listbook->Disconnect(wxEVT_COMMAND_LISTBOOK_PAGE_CHANGED, wxListbookEventHandler(mw::BottomPanel::OnPageChaged), NULL, this);
	m_programming_panel->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(mw::BottomPanel::OnProgrammingFocus), NULL, this);
	m_notification_panel->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(mw::BottomPanel::OnNotificationsFocus), NULL, this);
}

void mw::BottomPanel::OnPageChaged(wxListbookEvent& event)
{
	mwLogger logger;
	wxString pagename = m_listbook->GetPageText(m_listbook->GetSelection());

	logger.Info("page has been changed to " + pagename.ToStdString());
	event.Skip();
}

void mw::BottomPanel::OnProgrammingFocus(wxFocusEvent& event)
{
	mwLogger logger;
	logger.Info("OnPrgrammingFocus is called");
	event.Skip();
}

void mw::BottomPanel::OnNotificationsFocus(wxFocusEvent& event)
{
	event.Skip();
}
