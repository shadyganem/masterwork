#pragma once
#include "wx\scrolwin.h"
#include "wx/wx.h"
#include "controller/Controller.h"


namespace mw
{
	class ExpensesWindow : public wxScrolledWindow
	{

	public:
		ExpensesWindow(wxWindow* parent,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxScrolledWindowStyle,
			const wxString& name = wxASCII_STR(wxPanelNameStr));
		~ExpensesWindow();

		virtual void OnUpdateUI(wxEvent& event);
		virtual void OnToolbarButtonClick(wxCommandEvent& event);

	public:

		wxBoxSizer* m_expenses_sizer;

	};
}

