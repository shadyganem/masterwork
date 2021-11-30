#include "view/mwWorkPanel.h"


BEGIN_EVENT_TABLE(mwWorkPanel, wxPanel)
END_EVENT_TABLE()

mwWorkPanel::mwWorkPanel(wxWindow* parent, 
	                     wxWindowID winid, 
	                     const wxPoint& pos, 
	                     const wxSize& size, 
	                     long style, 
	                     const wxString& name) : wxPanel(parent, winid, pos, size, style, name)
{
	this->SetBackgroundColour(wxColour(37, 37, 38));

	m_ver_sizer = new wxBoxSizer(wxVERTICAL);

	m_notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);
	m_tasks_scroll_window = new wxScrolledWindow(m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_tasks_scroll_window->SetScrollRate(5, 5);
	m_tasks_sizer = new wxBoxSizer(wxVERTICAL);

	this->OnUiUpdate();

	m_tasks_scroll_window->SetSizer(m_tasks_sizer);
	m_notebook->AddPage(m_tasks_scroll_window, wxT("Tasks"), false);

	m_ver_sizer->Add(m_notebook, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(m_ver_sizer);
	this->Layout();

	// Connect Events
	m_notebook->Connect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler(mwWorkPanel::OnPageChanged), NULL, this);
	m_notebook->Connect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING, wxNotebookEventHandler(mwWorkPanel::OnPageChanging), NULL, this);
}

void mwWorkPanel::OnPageChanged(wxNotebookEvent& event)
{
	event.Skip();
}

void mwWorkPanel::OnPageChanging(wxNotebookEvent& event)
{
	event.Skip();
}

void mwWorkPanel::OnUiUpdate()
{
	mwTaskPanel* m_task = new mwTaskPanel(m_tasks_scroll_window);
	m_task->SetBackgroundColour(wxColor(240, 240, 240));
	mwTaskPanel* m_task1 = new mwTaskPanel(m_tasks_scroll_window);
	m_task1->SetBackgroundColour(wxColor(240, 240, 240));
	mwTaskPanel* m_task2 = new mwTaskPanel(m_tasks_scroll_window);
	m_task2->SetBackgroundColour(wxColor(240, 240, 240));
	mwTaskPanel* m_task3 = new mwTaskPanel(m_tasks_scroll_window);
	m_task3->SetBackgroundColour(wxColor(240, 240, 240));
	mwTaskPanel* m_task4 = new mwTaskPanel(m_tasks_scroll_window);
	m_task4->SetBackgroundColour(wxColor(240, 240, 240));
	mwTaskPanel* m_task5 = new mwTaskPanel(m_tasks_scroll_window);
	m_task5->SetBackgroundColour(wxColor(240, 240, 240));
	mwTaskPanel* m_task6 = new mwTaskPanel(m_tasks_scroll_window);
	m_task6->SetBackgroundColour(wxColor(240, 240, 240));
	mwTaskPanel* m_task7 = new mwTaskPanel(m_tasks_scroll_window);
	m_task7->SetBackgroundColour(wxColor(240, 240, 240));

	m_tasks_sizer->Add(m_task, 0, wxEXPAND | wxALL, 5);
	m_tasks_sizer->Add(m_task1, 0, wxEXPAND | wxALL, 5);
	m_tasks_sizer->Add(m_task2, 0, wxEXPAND | wxALL, 5);
	m_tasks_sizer->Add(m_task3, 0, wxEXPAND | wxALL, 5);
	m_tasks_sizer->Add(m_task4, 0, wxEXPAND | wxALL, 5);
	m_tasks_sizer->Add(m_task5, 0, wxEXPAND | wxALL, 5);
	m_tasks_sizer->Add(m_task6, 0, wxEXPAND | wxALL, 5);
	m_tasks_sizer->Add(m_task7, 0, wxEXPAND | wxALL, 5);

}

mwWorkPanel::~mwWorkPanel()
{
	// Disconnect Events
	m_notebook->Disconnect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler(mwWorkPanel::OnPageChanged), NULL, this);
	m_notebook->Disconnect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING, wxNotebookEventHandler(mwWorkPanel::OnPageChanging), NULL, this);
}


