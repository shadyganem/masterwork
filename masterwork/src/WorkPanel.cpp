#include "view/WorkPanel.h"


BEGIN_EVENT_TABLE(mw::WorkPanel, wxPanel)
	EVT_CUSTOM(mwUpdateUI, WORK_PANEL_ID, mw::WorkPanel::OnUpdateUI)
END_EVENT_TABLE()

mw::WorkPanel::WorkPanel(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxPanel(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	wxColour back_groud_color = controller.m_backgroud_color;

	this->SetBackgroundColour(back_groud_color);

	m_ver_sizer = new wxBoxSizer(wxVERTICAL);

	m_pages_notbook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP | wxAUI_NB_TAB_MOVE | wxAUI_NB_TAB_SPLIT);

	// Adding tasks window
	m_tasks_scroll_window = new mw::TasksWindow(m_pages_notbook, TASKS_WINDOW_ID, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_tasks_scroll_window->SetScrollRate(5, 5);
	m_pages_notbook->AddPage(m_tasks_scroll_window, "Tasks", false);
	m_pageidx_to_pageid_map[0] = TASKS_WINDOW_ID;

	// Adding reminders window
	m_reminders_scroll_window = new mw::RemindersWindow(m_pages_notbook, REMINDERS_WINDOW_ID, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_reminders_scroll_window->SetScrollRate(5, 5);
	m_pages_notbook->AddPage(m_reminders_scroll_window, wxT("Reminders"), false);
	m_pageidx_to_pageid_map[1] = REMINDERS_WINDOW_ID;

	// Adding passwords window
	m_password_scroll_window = new mw::PasswordWindow(m_pages_notbook, PASSWORDS_WINDOW_ID, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_password_scroll_window->SetScrollRate(5, 5);
	m_pages_notbook->AddPage(m_password_scroll_window, "Passwords", false);
	m_pageidx_to_pageid_map[2] = PASSWORDS_WINDOW_ID;

	// Adding archive window
	m_archive_scroll_window = new mw::ArchiveWindow(m_pages_notbook, ARCHIVE_WINDOW_ID, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_archive_scroll_window->SetScrollRate(5, 5);
	m_pages_notbook->AddPage(m_archive_scroll_window, wxT("Archived"), false);
	m_pageidx_to_pageid_map[3] = ARCHIVE_WINDOW_ID;

	m_ver_sizer->Add(m_pages_notbook, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(m_ver_sizer);
	this->Layout();

}

mw::WorkPanel::~WorkPanel()
{
}

void mw::WorkPanel::OnUpdateUI(wxEvent& event)
{
	event.Skip();
}

void mw::WorkPanel::UpdateTasksCount(int count)
{
	int page_index = m_pages_notbook->GetPageIndex(m_tasks_scroll_window);
	std::stringstream ss;
	ss << "Tasks (" << count << ")";

	m_pages_notbook->SetPageText(page_index, ss.str());
	this->Layout();
}

void mw::WorkPanel::UpdateRemindersCount(int count)
{
	int page_index = m_pages_notbook->GetPageIndex(m_reminders_scroll_window);
	std::stringstream ss;
	ss << "Reminders (" << count << ")";

	m_pages_notbook->SetPageText(page_index, ss.str());
	this->Layout();
}
