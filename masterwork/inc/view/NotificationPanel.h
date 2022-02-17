#pragma once

#include "wx/wx.h"
#include "view/Button.h"
#include "model/Notification.h"
#include "controller/Controller.h"

namespace mw
{
	class NotificationPanel : public wxPanel
	{
	public:
		NotificationPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(150, 50), long style = wxTAB_TRAVERSAL);
		~NotificationPanel();
		virtual void OnDismiss(wxCommandEvent& event);
		virtual void SetNotification(mw::Notification& notification);

	public:
		mw::Notification m_notification;
		mw::Button* m_dismiss_button;
		wxStaticText* m_static_notification;
		void SetTheme();


	};
}

