#pragma once

#include "wx/wx.h"
#include "mwDefines.h"
#include "controller/Controller.h"


namespace mw
{
	class NotificationsWindow : public wxScrolledWindow
	{
	public:
		NotificationsWindow(wxWindow* parent,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxScrolledWindowStyle,
			const wxString& name = wxASCII_STR(wxPanelNameStr));
		~NotificationsWindow();

		virtual void OnUpdateUI(wxEvent& event);

	private:
		DECLARE_EVENT_TABLE()

	};
}

