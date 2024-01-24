#include "view/Button.h"

mw::Button::Button(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name) : wxButton(parent, id, label, pos, size, style, validator, name)
{
	m_hover_colour = wxColour(255, 255, 255);
	this->Bind(wxEVT_ENTER_WINDOW, &mw::Button::OnEnterWindow, this, NULL);
	this->Bind(wxEVT_LEAVE_WINDOW, &mw::Button::OnLeaveWindow, this, NULL);
}

mw::Button::~Button()
{
}

void mw::Button::OnEnterWindow(wxMouseEvent& event)
{
	m_forground_colour = this->GetForegroundColour();
	m_background_colour = this->GetBackgroundColour();
	wxColour parent_backgournd_colour = this->GetParent()->GetBackgroundColour();
	this->SetBackgroundColour(parent_backgournd_colour);
	this->SetForegroundColour(m_hover_colour);
	event.Skip();
}

void mw::Button::OnLeaveWindow(wxMouseEvent& event)
{
	this->SetBackgroundColour(m_background_colour);
	this->SetForegroundColour(m_forground_colour);
	event.Skip();
}

void mw::Button::SetHoverColour(wxColour colour)
{
	m_hover_colour = colour;
}
