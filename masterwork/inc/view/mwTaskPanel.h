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
#include "model/mwTask.h"

#include "controller/mwLogger.h"
#include "controller/mwController.h"
#include "view/mwNewTaskFrame.h"

class mwTaskPanel : public wxPanel
{
public:
	wxStaticText* m_static_task_name;
	wxStaticText* m_static_description;
	wxButton* m_edit_task;
	wxButton* m_delete_task;

	mwTask m_task;

	virtual void OnEnterWindow(wxMouseEvent& event);
	virtual void OnleaveWindow(wxMouseEvent& event);
	virtual void OnEditTask(wxCommandEvent& event);
	virtual void OnStatusChanged(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDelete(wxCommandEvent& event);
	void SetTask(mwTask task);

	int m_uid;
	int m_parent_uid;
	wxBoxSizer* ver_task_sizer;
	wxPanel* m_static_view;
	wxPanel* m_edit_view;
	mwTaskPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(600, 100), long style = wxTAB_TRAVERSAL);
	~mwTaskPanel();
};