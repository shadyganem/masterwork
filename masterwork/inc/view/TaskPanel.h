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
#include <wx/panel.h>
#include "model/Task.h"

#include <wx/timectrl.h>
#include "controller/Logger.h"
#include "controller/Controller.h"
#include "view/Button.h"

namespace mw
{
	enum TaskPanelView
	{
		DEFAULT,
		BOTTOM,
		RIGHT,
		LEFT
	};

	class TaskPanel : public wxPanel
	{
	public:
		TaskPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(0, 50), long style = wxTAB_TRAVERSAL);
		~TaskPanel();
		void SetTask(const mw::Task& task);
		virtual void ClearTask();
		void DisableEditing();
		void EnableEditing();
		void SetView(mw::TaskPanelView view);
		virtual void OnDoneButton(wxCommandEvent& event);
		virtual void OnCancelButton(wxCommandEvent& event);
		virtual void SetTaskPriority();
		virtual void SetTaskStatus();
		virtual void SetTaskDeadline();
		virtual void OnSize(wxSizeEvent& event);


	public:
		mw::Task m_task;
		mw::TaskPanelView m_view_state;
		wxBoxSizer* ver_task_sizer;
		wxPanel* m_main_panel;
		wxStaticText* m_task_name_static;
		wxTextCtrl* m_task_name;
		wxStaticText* m_task_description_static;
		wxTextCtrl* m_task_description;
		wxStaticText* m_priority_static;
		wxChoice* m_priority_choice;
		wxStaticText* m_status_static;
		wxChoice* m_status_choice;
		wxStaticText* m_deadline_static;
		wxDatePickerCtrl* m_datePicker2;
		wxButton* m_done_button;
		wxButton* m_cancel_button;
		wxTimePickerCtrl* m_deadline_timepicker;
		wxDatePickerCtrl* m_deadline_datepicker;
		wxCheckBox* m_enable_notifications;

	private:
		void SetTheme(void);
		// any class wishing to process wxWidgets events must use this macro
		DECLARE_EVENT_TABLE()
	};
}
