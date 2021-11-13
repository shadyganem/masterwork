#pragma once
#include "wx/wx.h"
#include "wx/srchctrl.h"
#include "mwDefines.h"

class mwTopPanel : public wxPanel
{
public:
    mwTopPanel(wxWindow* parent,
        wxWindowID winid = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxTAB_TRAVERSAL | wxNO_BORDER,
        const wxString& name = wxASCII_STR(wxPanelNameStr));
    ~mwTopPanel();

private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()


private:
    void OnNewTaskButton(wxCommandEvent& event);


private:
    wxButton* m_new_task;

};
