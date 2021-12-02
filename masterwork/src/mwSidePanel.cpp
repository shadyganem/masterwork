#include "view/mwSidePanel.h"

mwSidePanel::mwSidePanel(wxWindow* parent, 
	                     wxWindowID winid, 
	                     const wxPoint& pos, 
	                     const wxSize& size, 
	                     long style, 
	                     const wxString& name) : wxPanel(parent, winid, pos, size, style, name)
{
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer(wxVERTICAL);

	m_splitter1 = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D);
	m_splitter1->Connect(wxEVT_IDLE, wxIdleEventHandler(mwSidePanel::m_splitter1OnIdle), NULL, this);
	m_panel7 = new wxPanel(m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer(wxVERTICAL);

	m_projects_text = new wxStaticText(m_panel7, wxID_ANY, wxT("Projects"), wxDefaultPosition, wxDefaultSize, 0);
	m_projects_text->Wrap(-1);
	m_projects_text->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));

	bSizer21->Add(m_projects_text, 0, wxALL | wxEXPAND, 5);

	m_listCtrl2 = new wxListCtrl(m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ALIGN_LEFT | wxLC_ALIGN_TOP | wxLC_AUTOARRANGE | wxLC_LIST);
	bSizer21->Add(m_listCtrl2, 1, wxALL | wxEXPAND, 5);

	m_panel7->SetSizer(bSizer21);
	m_panel7->Layout();
	bSizer21->Fit(m_panel7);
	m_panel9 = new wxPanel(m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_splitter1->SplitHorizontally(m_panel7, m_panel9, 324);
	bSizer19->Add(m_splitter1, 1, wxEXPAND, 5);

	this->SetSizer(bSizer19);
	this->Layout();

}

mwSidePanel::~mwSidePanel()
{
}
