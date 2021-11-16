#include "view/mwWorkPanel.h"


BEGIN_EVENT_TABLE(mwWorkPanel, wxPanel)
END_EVENT_TABLE()

mwWorkPanel::mwWorkPanel(wxWindow* parent, 
	                     wxWindowID winid, 
	                     const wxPoint& pos, 
	                     const wxSize& size, 
	                     long style, 
	                     const wxString& name) : wxPanel(parent, winid, pos, size, style, name)
{
}

mwWorkPanel::~mwWorkPanel()
{
}
