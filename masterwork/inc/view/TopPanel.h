#pragma once
#include "wx/wx.h"
#include "wx/srchctrl.h"
#include "mwDefines.h"
#include "controller/Controller.h"

#include "view/NewProjectFrame.h"
#include "view/TaskFrame.h"
namespace mw
{
    class TopPanel : public wxPanel
    {
    public:
        TopPanel(wxWindow* parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
            const wxString& name = wxASCII_STR(wxPanelNameStr));
        ~TopPanel();
    public:
        void OnNewTaskButton(wxCommandEvent& event);
        void OnNewProjectButton(wxCommandEvent& event);

        wxButton* m_new_task;
        wxButton* m_new_project;

    private:
        void SetTheme(int theme_id=0);
        // any class wishing to process wxWidgets events must use this macro
        DECLARE_EVENT_TABLE()
    };
}
