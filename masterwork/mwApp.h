#pragma once
#include "wx/wx.h"
#include "mwMainFrame.h"
#include "wx/image.h"
#include "wx/xrc/xmlres.h"


class mwApp : public wxApp
{
public:
	mwApp();
	~mwApp();
	virtual bool OnInit();
private:
	mwMainFrame* m_main_frame = nullptr;
	const wxString m_app_name = wxString("MasterWork");
};

