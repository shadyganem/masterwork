#pragma once
#include "wx/wx.h"
#include "view/MainFrame.h"
#include "wx/image.h"
#include "wx/xrc/xmlres.h"
#include <wx/snglinst.h>
#include "view/LoginFrame.h"


class MasterWork : public wxApp
{
public:
	virtual bool OnInit();

private:
	void OnLogin(wxCommandEvent& event);
	mw::MainFrame* m_main_frame = nullptr;
	wxSingleInstanceChecker m_checker;
};
