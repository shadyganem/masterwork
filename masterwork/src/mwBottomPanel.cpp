#include "view/mwBottomPanel.h"


BEGIN_EVENT_TABLE(mwBottomPanel, wxPanel)
	
END_EVENT_TABLE()


mwBottomPanel::mwBottomPanel(wxWindow* parent, 
	                         wxWindowID winid, 
	                         const wxPoint& pos, 
	                         const wxSize& size, 
	                         long style, 
	                         const wxString& name) 
	: wxPanel(parent, winid, pos, size, style, name)
{
	wxBoxSizer* m_ver_sizer;
	m_ver_sizer = new wxBoxSizer(wxVERTICAL);

	m_listbook = new wxListbook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDEFAULT);
	m_programming = new wxPanel(m_listbook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_listbook->AddPage(m_programming, wxT("Programming"), false);
	m_notification = new wxPanel(m_listbook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_listbook->AddPage(m_notification, wxT("Notifications"), true);
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
	m_listbook->Connect(wxEVT_COMMAND_LISTBOOK_PAGE_CHANGED, wxListbookEventHandler(mwBottomPanel::OnPageChaged), NULL, this);
	m_programming->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(mwBottomPanel::OnProgrammingFocus), NULL, this);
	m_notification->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(mwBottomPanel::OnNotificationsFocus), NULL, this);
}

mwBottomPanel::~mwBottomPanel()
{
	m_listbook->Disconnect(wxEVT_COMMAND_LISTBOOK_PAGE_CHANGED, wxListbookEventHandler(mwBottomPanel::OnPageChaged), NULL, this);
	m_programming->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(mwBottomPanel::OnProgrammingFocus), NULL, this);
	m_notification->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(mwBottomPanel::OnNotificationsFocus), NULL, this);
}

void mwBottomPanel::OnPageChaged(wxListbookEvent& event)
{
	mwLogger logger;
	wxString pagename = m_listbook->GetPageText(m_listbook->GetSelection());

	logger.Info("page has been changed to " + pagename.ToStdString());
	event.Skip();
}

void mwBottomPanel::OnProgrammingFocus(wxFocusEvent& event)
{
	mwLogger logger;
	logger.Info("OnPrgrammingFocus is called");
	event.Skip();
}

void mwBottomPanel::OnNotificationsFocus(wxFocusEvent& event)
{
	event.Skip();
}
