#pragma once
#include "wx/wx.h"

class mwBottomPanel : public wxPanel
{
public:
	mwBottomPanel(wxWindow* parent,
                  wxWindowID winid = wxID_ANY,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                  const wxString& name = wxASCII_STR(wxPanelNameStr));
	~mwBottomPanel();
};
