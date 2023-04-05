#pragma once
#include "wx/wx.h"
#include <wx/toolbar.h>
#include "controller/Controller.h"
#include "mwDefines.h"
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <model/Task.h>
#include "mwDefines.h"
#include "wx/event.h"
#include "view/TasksWindow.h"
#include "view/ArchiveWindow.h"
#include "view/RemindersWindow.h"
#include "view/TaskPanel.h"
#include <string>


namespace mw
{
    class WorkPanel : public wxPanel
    {
    public:
        WorkPanel(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER, const wxString& name = wxASCII_STR(wxPanelNameStr));
        ~WorkPanel();

    public:
        std::map<int, int> m_pageidx_to_pageid_map;

        mw::TasksWindow* m_tasks_scroll_window;
        mw::ArchiveWindow* m_archive_scroll_window;
        mw::RemindersWindow* m_reminders_scroll_window;
        wxToolBar* m_tool_bar;
        wxColor m_tool_bar_bg = wxColor(0, 0, 255);
        wxNotebook* m_notebook;
        wxBoxSizer* m_tasks_sizer;
        wxBoxSizer* m_ver_sizer;

        // Virtual event handlers, overide them in your derived class
        virtual void OnPageChanged(wxNotebookEvent& event);
        virtual void OnPageChanging(wxNotebookEvent& event);
        virtual void OnUpdateUI(wxEvent& event);
        virtual void OnAppendTask(wxEvent& event);

    private:
        DECLARE_EVENT_TABLE()

    };

}


