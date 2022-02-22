#pragma once
#include "wx/collpane.h"
#include "wx/wx.h"
#include <map>


namespace mw
{
	class CollapsibleGroupPane : public wxCollapsiblePane
	{
	public:
		CollapsibleGroupPane(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCP_DEFAULT_STYLE, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxCollapsiblePaneNameStr);
		~CollapsibleGroupPane();
		wxWindow* m_window;
		wxBoxSizer* m_main_sizer;
	};
}
