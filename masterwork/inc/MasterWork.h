#pragma once
#include "wx/wx.h"
#include "view/MainFrame.h"
#include "wx/image.h"
#include "wx/xrc/xmlres.h"


class MasterWork : public wxApp
{
public:
	virtual bool OnInit();
private:
	mw::MainFrame* m_main_frame = nullptr;
	const wxString m_app_name = wxString("MasterWork");
};

