#include "mwWorkPanel.h"

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

void mwWorkPanel::InitToolBar()
{
	m_tool_bar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_tool_bar->SetBackgroundColour(m_tool_bar_bg);
}
