#include "mwStatusBar.h"

mwStatusBar::mwStatusBar(wxWindow* parent, 
                         wxWindowID winid,
                         const wxPoint& pos,
                         const wxSize& size,
                         long style,
                         const wxString& name) 
                         : wxPanel(parent,winid,pos,size,style,name)
{
}

mwStatusBar::~mwStatusBar()
{
}
