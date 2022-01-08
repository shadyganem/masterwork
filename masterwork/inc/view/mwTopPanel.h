#pragma once
#include "wx/wx.h"
#include "wx/srchctrl.h"
#include "mwDefines.h"
#include "controller/mwController.h"

#include "view/NewProjectFrame.h"
#include "view/NewTaskFrame.h"

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


public:
    void OnNewTaskButton(wxCommandEvent& event);
    void OnNewProjectButton(wxCommandEvent& event);

    wxButton* m_new_task;
    wxButton* m_new_project;


private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()



};
