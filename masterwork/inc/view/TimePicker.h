#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>

namespace mw 
{

    class TimePicker : public wxPanel 
    {
    public:
        TimePicker(wxWindow* parent, wxWindowID id = wxID_ANY);

        int GetHour() const; 
        int GetMinute() const; 
        int GetSecond() const; 
        void SetTime(int hour, int minute, int seconds);

    private:
        wxSpinCtrl* m_hour_spinctrl;
        wxSpinCtrl* m_minute_spinctrl;
        wxSpinCtrl* m_second_spinctrl;
    };

}
