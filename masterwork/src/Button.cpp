#include "view/Button.h"

mw::Button::Button(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name) : wxButton(parent, id, label, pos, size, style, validator, name)
{
	this->Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(Button::OnEnterWindow), NULL, this);
	this->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(Button::OnLeaveWindow), NULL, this);
}

mw::Button::~Button()
{
	this->Disconnect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(Button::OnEnterWindow), NULL, this);
	this->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(Button::OnLeaveWindow), NULL, this);
}

void mw::Button::OnEnterWindow(wxMouseEvent& event)
{
	m_forground_colour = this->GetForegroundColour();
	m_background_colour = this->GetBackgroundColour();
	wxColour parent_backgournd_colour = this->GetParent()->GetBackgroundColour();
	this->SetBackgroundColour(parent_backgournd_colour);
	this->SetForegroundColour(wxColour(255, 255, 255));
	event.Skip();
}

void mw::Button::OnLeaveWindow(wxMouseEvent& event)
{
	this->SetBackgroundColour(m_background_colour);
	this->SetForegroundColour(m_forground_colour);
	event.Skip();
}
