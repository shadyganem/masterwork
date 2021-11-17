#pragma once
#include "wx/wx.h"
#include <wx/toolbar.h>
#include "controller/mwController.h"
#include "mwDefines.h"


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

private:
    DECLARE_EVENT_TABLE()

};

