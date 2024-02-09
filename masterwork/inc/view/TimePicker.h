#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "model/DateTime.h"


namespace mw 
{

    class TimePicker : public wxPanel 
    {
    public:
        TimePicker(wxWindow* parent, wxWindowID id = wxID_ANY);

        int GetHour() const; 
        int GetMinute() const; 
        int GetSecond() const; 
        time_t GetTime();
        void SetTime(int hour, int minute, int seconds);
        void SetTime(time_t time);

    private:
        wxSpinCtrl* m_hour_spinctrl;
        wxSpinCtrl* m_minute_spinctrl;
        wxSpinCtrl* m_second_spinctrl;
    };

}
