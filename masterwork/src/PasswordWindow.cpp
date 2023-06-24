#include "view/PasswordWindow.h"

BEGIN_EVENT_TABLE(mw::PasswordWindow, wxScrolledWindow)
	EVT_CUSTOM(mwUpdateUI, PASSWORD_WINDOW_ID, mw::PasswordWindow::OnUpdateUI)
END_EVENT_TABLE()

mw::PasswordWindow::PasswordWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
	: wxScrolledWindow(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_sizer_1 = new wxBoxSizer(wxVERTICAL);

	wxColour background = controller.m_backgroud_color;
	wxColour foreground = controller.m_foreground_color;
	m_toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TEXT);

	wxColour green(0, 136, 135);


	m_toolbar->SetBackgroundColour(background);
	m_toolbar->SetForegroundColour(foreground);
	m_toolbar->Realize();

	m_sizer_1->Add(m_toolbar, 0, wxEXPAND);


	// instatiating m_reminders_data_view_list

	m_passwords_data_view_list = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_MULTIPLE | wxDV_HORIZ_RULES);

	m_passwords_data_view_list->AppendColumn(new wxDataViewColumn("Title", new wxDataViewTextRenderer(), 0, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_passwords_data_view_list->AppendColumn(new wxDataViewColumn("Status", new wxDataViewTextRenderer(), 1, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_passwords_data_view_list->AppendColumn(new wxDataViewColumn("Last Update", new wxDataViewTextRenderer(), 2, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));

	m_passwords_data_view_list->SetBackgroundColour(background);
	m_passwords_data_view_list->SetForegroundColour(foreground);

	m_sizer_1->Add(m_passwords_data_view_list, 1, wxEXPAND, 0);

	this->SetBackgroundColour(background);
	this->SetSizer(m_sizer_1);
	this->Layout();


	controller.RequestUpdateUI(this->GetId());
}

mw::PasswordWindow::~PasswordWindow()
{
}

void mw::PasswordWindow::OnUpdateUI(wxEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	wxColour background = controller.m_backgroud_color;
	wxColour foreground = controller.m_foreground_color;
	m_toolbar->SetBackgroundColour(background);
	m_toolbar->SetForegroundColour(foreground);
}
