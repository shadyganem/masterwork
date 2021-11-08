#include "mwMainFrame.h"

BEGIN_EVENT_TABLE(mwMainFrame, wxFrame)

END_EVENT_TABLE()


mwMainFrame::mwMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	mwStatusBar* m_status_bar = new mwStatusBar(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
	m_status_bar->SetBackgroundColour(wxColor(100, 100, 200));
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(m_status_bar, 1, wxEXPAND);
}

mwMainFrame::~mwMainFrame()
{
}