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
	m_tasks = new wxPanel(m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL | wxVSCROLL);
	m_tasks->SetBackgroundColour(wxColour(37, 37, 38));

	m_notebook->AddPage(m_tasks, wxT("Tasks"), false);

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

mwWorkPanel::~mwWorkPanel()
{
	// Disconnect Events
	m_notebook->Disconnect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler(mwWorkPanel::OnPageChanged), NULL, this);
	m_notebook->Disconnect(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING, wxNotebookEventHandler(mwWorkPanel::OnPageChanging), NULL, this);
}
