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
#include "controller/mwController.h"

class mwSidePanel : public wxPanel
{
public:

	wxSplitterWindow* m_splitter1;
	wxPanel* m_panel7;
	wxStaticText* m_projects_text;
	wxPanel* m_panel9;

	wxListBox* m_projects_list;

	void m_splitter1OnIdle(wxIdleEvent&)
	{
		m_splitter1->SetSashPosition(324);
		m_splitter1->Disconnect(wxEVT_IDLE, wxIdleEventHandler(mwSidePanel::m_splitter1OnIdle), NULL, this);
	}


	void UpdateProjecstList();

	mwSidePanel(wxWindow* parent,
                wxWindowID winid = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                const wxString& name = wxASCII_STR(wxPanelNameStr));

    ~mwSidePanel();
};

