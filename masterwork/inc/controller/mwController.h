#pragma once

#include "wx/wx.h"

class mwController
{
public:
	mwController(const mwController&) = delete;
	static mwController& Get()
	{
		static mwController instance;
		return instance;
	}
	// mwController interface
	bool RegisterView();
	bool Search(wxString& search_query);
private:
	mwController() {}
};

