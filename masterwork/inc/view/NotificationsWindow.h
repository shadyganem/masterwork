#pragma once

#include "wx/wx.h"
namespace mw
{

	class NotificationsWindow : public wxScrolledWindow
	{
		NotificationsWindow(wxWindow* parent,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxScrolledWindowStyle,
			const wxString& name = wxASCII_STR(wxPanelNameStr));
		~NotificationsWindow();
	};
}

