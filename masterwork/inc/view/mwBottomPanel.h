#pragma once
#include "wx/wx.h"
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <controller/mwLogger.h>


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


    // Virtual event handlers, overide them in your derived class
    virtual void OnPageChaged(wxListbookEvent& event);
    virtual void OnProgrammingFocus(wxFocusEvent& event);
    virtual void OnNotificationsFocus(wxFocusEvent& event);


public:
    wxListbook* m_listbook;
    wxPanel* m_programming;
    wxPanel* m_notification;

private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};
