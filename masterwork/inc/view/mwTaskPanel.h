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

#include "controller/mwLogger.h"

class mwTaskPanel : public wxPanel
{
private:
	wxBitmap* m_delete_bitmap;
	wxStaticText* m_staticText5;
	wxStaticText* m_staticText41;
	wxButton* m_edit_task;
	wxTextCtrl* m_taskname;
	wxRichTextCtrl* m_richText1;
	wxStaticText* m_staticText2;
	wxSpinCtrl* m_spinCtrl1;
	wxStaticText* m_staticText4;
	wxSpinCtrl* m_spinCtrl3;
	wxStaticText* m_staticText3;
	wxSpinCtrl* m_spinCtrl2;
	wxDatePickerCtrl* m_datePicker1;
	wxChoice* m_choice1;
	wxBitmapButton* m_delete_task;
	wxBitmapButton* m_save_task;

	virtual void OnEnterWindow(wxMouseEvent& event);
	virtual void OnleaveWindow(wxMouseEvent& event);
	virtual void OnEditTask(wxCommandEvent& event);
	virtual void OnStatusChanged(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDelete(wxCommandEvent& event);
	virtual void OnSaveTask(wxCommandEvent& event);


public:
	int m_uid;
	int m_parent_uid;
	wxBoxSizer* ver_task_sizer;
	wxPanel* m_static_view;
	wxPanel* m_edit_view;
	mwTaskPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(600, 100), long style = wxTAB_TRAVERSAL);
	~mwTaskPanel();
};