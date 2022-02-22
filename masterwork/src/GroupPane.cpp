#include "view/GroupPane.h"

mw::CollapsibleGroupPane::CollapsibleGroupPane(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name) 
	: wxCollapsiblePane(parent, id, label, pos, size, style, validator, name)
{
}

mw::CollapsibleGroupPane::~CollapsibleGroupPane()
{
}
