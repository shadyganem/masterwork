#pragma once

#include "wx/wx.h"

namespace mw
{
	class NotificationPanel : public wxPanel
	{
	public:
		NotificationPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(600, 50), long style = wxTAB_TRAVERSAL);
		~NotificationPanel();

	};
}

