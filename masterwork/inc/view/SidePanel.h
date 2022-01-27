#pragma once
#include "wx/wx.h"
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include "controller/Controller.h"
#include <map>
#include "model/mwProject.h"

#include "mwDefines.h"
#include "view/NewProjectFrame.h"
#include "view/Button.h"


namespace mw
{

	class SidePanel : public wxPanel
	{
	public:

		std::map<int, mwProject> m_place_to_project_map;

		wxSplitterWindow* m_splitter1;
		wxPanel* m_panel7;
		wxStaticText* m_projects_text;
		wxPanel* m_panel9;

		wxButton* m_new_project_button;


		std::map<int, mw::User> m_idx_to_user;
		
		wxChoice* m_users_choice;

		wxListBox* m_projects_list;
		void m_splitter1OnIdle(wxIdleEvent&)
		{
			m_splitter1->SetSashPosition(324);
			m_splitter1->Disconnect(wxEVT_IDLE, wxIdleEventHandler(mw::SidePanel::m_splitter1OnIdle), NULL, this);
		}

		void UpdateUsersList();
		void UpdateProjecstList();
		void OnUpdateUI(wxEvent& event);
		virtual void OnItemSelect(wxCommandEvent& event);
		virtual void OnProjectListRightUp(wxCommandEvent& event);
		virtual void OnNewProjectButton(wxCommandEvent& event);
		virtual void OnProjectListMenuClick(wxCommandEvent& evt);
		virtual void OnUserChange(wxCommandEvent& event);
		bool IsProjectSelected();

		SidePanel(wxWindow* parent,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxTAB_TRAVERSAL | wxNO_BORDER,
			const wxString& name = wxASCII_STR(wxPanelNameStr));

		~SidePanel();

	private:
		bool m_is_project_seleted;
	private:
		// any class wishing to process wxWidgets events must use this macro
		DECLARE_EVENT_TABLE()
	};


}