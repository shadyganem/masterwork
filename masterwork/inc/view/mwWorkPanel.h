#pragma once
#include "wx/wx.h"
#include <wx/toolbar.h>
#include "controller/mwController.h"
#include "mwDefines.h"
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include "view/mwTaskPanel.h"


class mwWorkPanel : public wxPanel
{
public:
    
	mwWorkPanel(wxWindow* parent,
                wxWindowID winid = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                const wxString& name = wxASCII_STR(wxPanelNameStr));;
	~mwWorkPanel();

public:
    wxToolBar* m_tool_bar;
    wxColor m_tool_bar_bg = wxColor(0, 0, 255);
    wxNotebook* m_notebook;
    wxPanel* m_tasks;
    wxBoxSizer* m_tasks_sizer;

	wxBoxSizer* m_ver_sizer;

	// Virtual event handlers, overide them in your derived class
	virtual void OnPageChanged(wxNotebookEvent& event);
	virtual void OnPageChanging(wxNotebookEvent& event);
    virtual void OnUiUpdate();



private:
    DECLARE_EVENT_TABLE()

};

