#pragma once

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/frame.h>

#include "controller/Controller.h"
#include "model/Project.h"
#include <string>

namespace mw
{
	class NewProjectFrame : public wxFrame
	{
	private:
		mw::Project m_project;
	protected:
		wxPanel* m_main_form;
		wxStaticText* m_project_name_static_name;
		wxTextCtrl* m_project_name_textbox;
		wxButton* m_button2;
		wxButton* m_cancel_button;

		virtual void OnDoneButton(wxCommandEvent& event);
		virtual void OnCancelButton(wxCommandEvent& event);

	public:
		NewProjectFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New Project"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(450, 176), long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
		~NewProjectFrame();
		void SetProject(mw::Project& project);

	};
}