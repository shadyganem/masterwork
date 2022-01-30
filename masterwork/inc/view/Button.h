#pragma once

#include "wx/wx.h"

namespace mw
{
	class Button : public wxButton
	{
    public:
		Button(wxWindow* parent,
               wxWindowID id,
               const wxString& label = wxEmptyString,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = wxNO_BORDER,
               const wxValidator& validator = wxDefaultValidator,
               const wxString& name = wxASCII_STR(wxButtonNameStr));
		~Button();

        virtual void OnEnterWindow(wxMouseEvent& event);
        virtual void OnLeaveWindow(wxMouseEvent& event);
        void SetHoverColour(wxColour colour);
        wxColour m_hover_colour;
        wxColour m_background_colour;
        wxColour m_forground_colour;

	};
}


