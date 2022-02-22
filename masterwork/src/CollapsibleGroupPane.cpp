#include "view/CollapsibleGroupPane.h"

mw::CollapsibleGroupPane::CollapsibleGroupPane(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name) 
	: wxCollapsiblePane(parent, id, label, pos, size, style, validator, name)
{
	m_window = this->GetPane();
	m_main_sizer = new wxBoxSizer(wxVERTICAL);

	m_window->SetSizer(m_main_sizer);
	m_main_sizer->SetSizeHints(m_window);
}

mw::CollapsibleGroupPane::~CollapsibleGroupPane()
{
}
