#pragma once

#include "wx/wx.h"

class mwStatusBar : public wxPanel
{
public:
	mwStatusBar(wxWindow* parent,
        wxWindowID winid = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxTAB_TRAVERSAL | wxNO_BORDER,
        const wxString& name = wxASCII_STR(wxPanelNameStr));
	~mwStatusBar();
};

