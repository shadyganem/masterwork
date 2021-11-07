#pragma once

#include "wx/wx.h"

class CMainFrame : public wxFrame
{
public:
	CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~CMainFrame();
};

