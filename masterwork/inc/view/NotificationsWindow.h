#pragma once

#include "wx/wx.h"
#include "mwDefines.h"
#include "controller/Controller.h"
#include "view/NotificationPanel.h"
#include "model/Notification.h"
#include <map>

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

		void Clear();
		virtual void OnUpdateUI(wxEvent& event);

		std::map<mw::NotificationPanel*, mw::Notification> m_notif_panel_to_notif_map;

	private:
		DECLARE_EVENT_TABLE()

	};
}

