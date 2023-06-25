#pragma once

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/timectrl.h>

#include "controller/Logger.h"
#include "controller/Controller.h"
#include "model/Task.h"
#include "model/DateTime.h"


namespace mw
{
    class NewPasswordFrame : public wxFrame
    {

    public:
        NewPasswordFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Password"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(450, 400), long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
        ~NewPasswordFrame();
    };
}


