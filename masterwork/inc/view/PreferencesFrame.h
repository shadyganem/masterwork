#pragma once

#include "wx/wx.h"
#include <wx/frame.h>
#include "mwDefines.h"

namespace mw
{
	class PreferencesFrame : public wxFrame
	{
	public:
		PreferencesFrame(wxWindow* parent, wxWindowID id = PREFERENCES_FRAME_ID, const wxString& title = wxT("Prefrences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(450, 400), long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
		~PreferencesFrame();
	};
}

