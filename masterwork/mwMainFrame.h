#pragma once

#include "wx/wx.h"
#include "mwStatusBar.h"

class mwMainFrame : public wxFrame
{
public:
	mwMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~mwMainFrame();
private:
	// any class wishing to process wxWidgets events must use this macro
	DECLARE_EVENT_TABLE()
};

