#include "view/NewReminderFrame.h"

mw::NewReminderFrame::NewReminderFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) 
	: wxFrame(parent, id, title, pos, size, style)
{
}

mw::NewReminderFrame::~NewReminderFrame()
{
}

void mw::NewReminderFrame::SetReminder(mw::Reminder& reminder)
{
	m_reminder = reminder;
}
