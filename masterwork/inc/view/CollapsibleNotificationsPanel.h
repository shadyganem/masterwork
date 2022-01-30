#pragma once
#include "wx/wx.h"
#include "controller/Controller.h"
#include "view/NotificationsWindow.h"
#include "mwDefines.h"

namespace mw
{
	class CollapsibleNotificationsPanel : public wxPanel
	{
	public:
		CollapsibleNotificationsPanel(wxWindow* parent,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxTAB_TRAVERSAL | wxNO_BORDER,
			const wxString& name = wxASCII_STR(wxPanelNameStr));
		~CollapsibleNotificationsPanel();

		wxBoxSizer* m_notifications_sizer;
		
		mw::NotificationsWindow* m_notifications_window;

		virtual void OnUpdateUI(wxEvent& event);


	private:
		DECLARE_EVENT_TABLE()
	};
}
