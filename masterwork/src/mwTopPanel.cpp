#include "mwTopPanel.h"

BEGIN_EVENT_TABLE(mwTopPanel, wxPanel)
	EVT_SEARCH(TOP_PANEL_SERACH_ID, mwTopPanel::OnTopPanelSearch)
END_EVENT_TABLE()

mwTopPanel::mwTopPanel(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxPanel(parent, winid, pos, size, style, name)
{
	wxSizer* top_panel_sizer = new wxBoxSizer(wxVERTICAL);
	m_search_ctrl = new wxSearchCtrl(this, TOP_PANEL_SERACH_ID);
	top_panel_sizer->Add(m_search_ctrl, 1, wxALIGN_RIGHT);
	this->SetSizer(top_panel_sizer);
}

mwTopPanel::~mwTopPanel()
{
}

wxString mwTopPanel::GetSearchText()
{
	return m_search_ctrl->GetLineText(0);
}

void mwTopPanel::ClearSearchText()
{
	m_search_ctrl->Clear();
}

void mwTopPanel::OnTopPanelSearch(wxCommandEvent& event)
{
	event.Skip();
}

