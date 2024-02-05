#include "view/TimePicker.h"

mw::TimePicker::TimePicker(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
{
    // Create spin controls for hours, minutes, and seconds
    m_hour_spinctrl = new wxSpinCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 23, 0);
    m_minute_spinctrl = new wxSpinCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 59, 0);
    m_second_spinctrl = new wxSpinCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 59, 0);

    // Set up the sizer
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(m_hour_spinctrl, 0, wxALL, 2);
    sizer->Add(new wxStaticText(this, wxID_ANY, ":"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 0);
    sizer->Add(m_minute_spinctrl, 0, wxALL, 2);
    sizer->Add(new wxStaticText(this, wxID_ANY, ":"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 0);
    sizer->Add(m_second_spinctrl, 0, wxALL, 2);

    SetSizer(sizer);
}

int mw::TimePicker::GetHour() const
{
    return m_hour_spinctrl->GetValue();
}

int mw::TimePicker::GetMinute() const
{
    return m_minute_spinctrl->GetValue();
}

int mw::TimePicker::GetSecond() const
{
    return m_second_spinctrl->GetValue(); 
}

void mw::TimePicker::SetTime(int hour, int minute, int second)
{
    m_hour_spinctrl->SetValue(hour%24);
    m_minute_spinctrl->SetValue(minute%60);
    m_second_spinctrl->SetValue(second%60);
}
