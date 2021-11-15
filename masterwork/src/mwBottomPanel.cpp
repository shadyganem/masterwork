#include "view/mwBottomPanel.h"


BEGIN_EVENT_TABLE(mwBottomPanel, wxPanel)
	
END_EVENT_TABLE()


mwBottomPanel::mwBottomPanel(wxWindow* parent, 
	                         wxWindowID winid, 
	                         const wxPoint& pos, 
	                         const wxSize& size, 
	                         long style, 
	                         const wxString& name) 
	: wxPanel(parent, winid, pos, size, style, name)
{


}

mwBottomPanel::~mwBottomPanel()
{
}
