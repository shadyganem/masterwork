#pragma once
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/choice.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/panel.h>
#include "model/Task.h"

#include "controller/Logger.h"
#include "controller/Controller.h"
#include "view/NewTaskFrame.h"

namespace mw
{
	class TaskPanel : public wxPanel
	{
	public:
		wxStaticText* m_static_task_name;
		wxStaticText* m_static_description;
		wxButton* m_archive_task;
		wxButton* m_unarchive_task_button;

		mw::Task m_task;

		wxStaticText* m_static_status;
		wxStaticText* m_static_duedate;
		wxStaticText* m_static_priority;
		wxStaticText* m_static_last_modified;
		mw::NewTaskFrame* m_new_task_frame;
		// TODO: added meta data in the DB for last modified time
		wxStaticText* m_static_lastmodified;

		virtual void OnEnterWindow(wxMouseEvent& event);
		virtual void OnleaveWindow(wxMouseEvent& event);
		virtual void OnLeftDoubleClick(wxMouseEvent& event);
		virtual void OnTaskFrameClose(wxWindowDestroyEvent& event);
		virtual void OnArchive(wxCommandEvent& event);
		virtual void OnUnarchive(wxCommandEvent& event);


		void SetTask(mw::Task task);
		void ResetBackGround();
		void HideArchiveButton();
		void ShowUnarchiveButton();
		void DisableEditing();

		wxBoxSizer* ver_task_sizer;
		wxPanel* m_static_view;
		TaskPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(600, 50), long style = wxTAB_TRAVERSAL);
		~TaskPanel();

	private:
		void SetDarkTheme(void);
		void SetHighlightColours();
		// any class wishing to process wxWidgets events must use this macro
		DECLARE_EVENT_TABLE()
	};
}
