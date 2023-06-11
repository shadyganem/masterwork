#include "view/ExpensesWindow.h"

mw::ExpensesWindow::ExpensesWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxScrolledWindow(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_expenses_sizer = new wxBoxSizer(wxVERTICAL);
	wxColour background = controller.m_backgroud_color;
	wxColour foreground = controller.m_forground_color;
	wxColour green(0, 136, 135);

	wxToolBar* toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TEXT);
	toolbar->SetBackgroundColour(background);
	toolbar->SetForegroundColour(foreground);
	toolbar->Realize();

	m_expenses_sizer->Add(toolbar, 0, wxEXPAND);

	this->SetSizer(m_expenses_sizer);

	toolbar->Bind(wxEVT_TOOL, &mw::ExpensesWindow::OnToolbarButtonClick, this);
	controller.RequestUpdateUI(winid);
}

mw::ExpensesWindow::~ExpensesWindow()
{

}

void mw::ExpensesWindow::OnUpdateUI(wxEvent& event)
{
}

void mw::ExpensesWindow::OnToolbarButtonClick(wxCommandEvent& event)
{
}
