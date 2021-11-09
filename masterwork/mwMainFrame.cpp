#include "mwMainFrame.h"

BEGIN_EVENT_TABLE(mwMainFrame, wxFrame)

END_EVENT_TABLE()


mwMainFrame::mwMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	// initialzing sizers
	m_hor_sizer = new wxBoxSizer(wxHORIZONTAL);
	m_ver_sizer = new wxBoxSizer(wxVERTICAL);

	// initialzing info controls
	m_status_bar = CreateStatusBar();
	m_status_bar->SetBackgroundColour(m_info_bg);

	InitMenuBar();

	m_info_bar = new wxInfoBar(this);
	m_info_bar->SetBackgroundColour(wxColor(100, 200, 400));
	m_ver_sizer->Add(m_info_bar, wxSizerFlags().Expand());
	ShowInfoBarMessage("Welcome to MasterWork");
	this->SetSizer(m_ver_sizer);
}

mwMainFrame::~mwMainFrame()
{
}

void mwMainFrame::InitMenuBar()
{
	m_menu_bar = new wxMenuBar();
	this->SetMenuBar(m_menu_bar);
	wxMenu* menu_file = new wxMenu();
	menu_file->Append(10001, "New");
	menu_file->Append(10004, "Exit");
	m_menu_bar->Append(menu_file, "File");

}

void mwMainFrame::ShowInfoBarMessage(const wxString& msg)
{
	m_info_bar->ShowMessage(msg);
}

void mwMainFrame::ShowStutusBarMessage(const wxString& msg, wxColor& bg_color)
{
}
