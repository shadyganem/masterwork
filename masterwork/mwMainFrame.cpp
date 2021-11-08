#include "mwMainFrame.h"

BEGIN_EVENT_TABLE(mwMainFrame, wxFrame)

END_EVENT_TABLE()


mwMainFrame::mwMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	// initialzing sizers
	m_hor_sizer = new wxBoxSizer(wxHORIZONTAL);
	m_ver_sizer = new wxBoxSizer(wxVERTICAL);

	// initialzing info controls
	m_info_bar = new wxInfoBar(this);
	m_info_bar->SetBackgroundColour(wxColor(100, 200, 400));
	m_ver_sizer->Add(m_info_bar, wxSizerFlags().Expand());
	ShowInfoBarMessage("Welcome to MasterWork");
	
	/*
	mwStatusBar* m_status_bar = new mwStatusBar(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
	m_status_bar->SetBackgroundColour(wxColor(100, 100, 200));
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(m_status_bar, 1, wxEXPAND);
	*/
	this->SetSizer(m_ver_sizer);
}

mwMainFrame::~mwMainFrame()
{
}

void mwMainFrame::ShowInfoBarMessage(const wxString& msg)
{
	m_info_bar->ShowMessage(msg);
}
