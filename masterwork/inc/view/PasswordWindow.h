#pragma once
#pragma once
#include "wx\scrolwin.h"
#include "controller/Controller.h"
#include "wx/wx.h"
#include "mwDefines.h"
#include <wx/dataview.h>
#include "view/Button.h"
#include "view/PasswordFrame.h"
#include "model/Password.h"
#include "controller/Clipboard.h"


namespace mw
{
    class PasswordWindow : public wxScrolledWindow
    {
	public:
		PasswordWindow(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxScrolledWindowStyle, const wxString& name = wxASCII_STR(wxPanelNameStr));
		~PasswordWindow();

		virtual void OnUpdateUI(wxEvent& event);
		virtual void OnNewPasswordButton(wxCommandEvent& event);
		virtual void OnContextMenu(wxDataViewEvent& event);
		virtual void OnMenuCopyClick(wxCommandEvent& event);
		virtual void OnMenuDeleteClick(wxCommandEvent& event);
		virtual void OnMenuEditClick(wxCommandEvent& event);
		virtual void AddPassword(mw::Password& password);
	private:
		void GetSelectedPasswords(std::vector<mw::Password>& passwords);
	public:

		wxToolBar* m_toolbar;
		std::map<int, mw::Password> m_index_to_password_map;
		wxDataViewListCtrl* m_passwords_data_view_list;
	private:
		mw::Password m_menu_selected_password;
		std::string m_text_for_copy;
		wxMenu* m_password_menu;
		mw::Button* m_new_password_button;
		wxBoxSizer* m_sizer_1;
		std::map<std::string, int> m_column_to_index_map;
	private:
		DECLARE_EVENT_TABLE()
    };
}
