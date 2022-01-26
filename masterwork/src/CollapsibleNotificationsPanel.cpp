#include "view/CollapsibleNotificationsPanel.h"

mw::CollapsibleNotificationsPanel::CollapsibleNotificationsPanel(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxPanel(parent, winid, pos, size, style, name)
{

	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
}

mw::CollapsibleNotificationsPanel::~CollapsibleNotificationsPanel()
{
}
