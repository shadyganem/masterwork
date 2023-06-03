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

	m_notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);

	m_tasks_scroll_window = new mw::TasksWindow(m_notebook, TASKS_WINDOW_ID, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_tasks_scroll_window->SetScrollRate(5, 5);
	m_notebook->AddPage(m_tasks_scroll_window, wxT("Tasks"), false);
	m_pageidx_to_pageid_map[0] = TASKS_WINDOW_ID;

	m_reminders_scroll_window = new mw::RemindersWindow(m_notebook, REMINDERS_WINDOW_ID, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_reminders_scroll_window->SetScrollRate(5, 5);
	m_notebook->AddPage(m_reminders_scroll_window, wxT("Reminders"), false);
	m_pageidx_to_pageid_map[1] = REMINDERS_WINDOW_ID;

	m_archive_scroll_window = new mw::ArchiveWindow(m_notebook, ARCHIVE_WINDOW_ID, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_archive_scroll_window->SetScrollRate(5, 5);
	m_notebook->AddPage(m_archive_scroll_window, wxT("Archive"), false);
	m_pageidx_to_pageid_map[2] = ARCHIVE_WINDOW_ID;

	m_ver_sizer->Add(m_notebook, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(m_ver_sizer);
	this->Layout();

	// Connect Events
	m_notebook->Connect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler(mw::WorkPanel::OnPageChanged), NULL, this);
	m_notebook->Connect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING, wxNotebookEventHandler(mw::WorkPanel::OnPageChanging), NULL, this);
}

mw::WorkPanel::~WorkPanel()
{
	// Disconnect Events
	m_notebook->Disconnect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler(mw::WorkPanel::OnPageChanged), NULL, this);
	m_notebook->Disconnect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING, wxNotebookEventHandler(mw::WorkPanel::OnPageChanging), NULL, this);
}

void mw::WorkPanel::OnPageChanged(wxNotebookEvent& event)
{
	event.Skip();
}

void mw::WorkPanel::OnPageChanging(wxNotebookEvent& event)
{
	event.Skip();
}

void mw::WorkPanel::OnUpdateUI(wxEvent& event)
{
	event.Skip();
}

void mw::WorkPanel::OnAppendTask(wxEvent& event)
{
	event.Skip();
}

