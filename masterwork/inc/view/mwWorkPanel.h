#pragma once
#include "wx/wx.h"
#include <wx/toolbar.h>

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
private:
    void InitToolBar();
private:
    wxToolBar* m_tool_bar;
    wxColor m_tool_bar_bg = wxColor(0, 0, 255);


};

