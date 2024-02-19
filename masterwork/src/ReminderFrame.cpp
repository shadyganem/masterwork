#include "view/ReminderFrame.h"
#include <chrono>
#include <ctime>

mw::ReminderFrame::ReminderFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) 
	: wxFrame(parent, id, title, pos, size, style)
{
    m_new_reminder = true;
    // Create input fields and button
    title_input = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    text_input = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_TAB);
    m_save_button = new mw::Button(this, wxID_ANY, wxT("Save"));
    m_cancel_button = new mw::Button(this, wxID_ANY, wxT("Cancel"));

    std::vector<std::string> options = mw::Reminder::GetRepeatOptions();
    wxArrayString wxStringArray;
    wxStringArray.assign(options.begin(), options.end());
    m_repeat_options = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxStringArray, 0);
    m_repeat_options->SetSelection(0);
    
    m_color_picker = new wxColourPickerCtrl(this, wxID_ANY, wxColour(0, 0, 0), wxDefaultPosition, wxDefaultSize, wxCLRP_SHOW_LABEL);

    options.clear();
    options = mw::Reminder::GetAlertTimingOptions();
    wxStringArray.Clear();
    wxStringArray.assign(options.begin(), options.end());

    // Create a wxCheckListBox for multi-selection
    m_alert_timing_checklist_box = new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxStringArray);
    m_alert_timing_checklist_box->Check(0, true);

    options.clear();
    options = mw::Reminder::GetDaysOfTheWeekOptions();
    wxStringArray.Clear();
    wxStringArray.assign(options.begin(), options.end());

    this->m_days_of_the_week = new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxStringArray);
    this->m_days_of_the_week->Hide();
    // Create a dropdown list for selecting the day of the month
    wxString days[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" ,"16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"};
    wxArrayString daysArray(31, days);
    this->m_day_dropdown = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, daysArray, wxCB_DROPDOWN | wxCB_READONLY);
    this->m_day_dropdown->SetSelection(0);
    this->m_day_dropdown->Hide();


    this->m_alert_datepicker = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN | wxDP_SHOWCENTURY);
    this->m_alert_timepicker = new wxTimePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxTP_DEFAULT);

    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&currentTime);

    // Create a vertical sizer to arrange the components
    m_v_sizer = new wxBoxSizer(wxVERTICAL);

    // Group Title and Note using StaticBoxSizer
    wxStaticBoxSizer* title_note_box = new wxStaticBoxSizer(wxVERTICAL, this, "Title and Note");
    title_note_box->Add(new wxStaticText(this, wxID_ANY, wxT("Title:")), 0, wxALL, 5);
    title_note_box->Add(title_input, 0, wxEXPAND | wxALL, 5);
    title_note_box->Add(new wxStaticText(this, wxID_ANY, wxT("Note:")), 0, wxALL, 5);
    title_note_box->Add(text_input, 0, wxEXPAND | wxALL, 5);
    m_v_sizer->Add(title_note_box, 0, wxEXPAND | wxALL, 10);

    // Group Options using StaticBoxSizer
    m_options_box = new wxStaticBoxSizer(wxVERTICAL, this, "Options");
    m_options_box->Add(this->m_repeat_options, 0, wxALL, 5);
    m_options_box->Add(this->m_alert_timepicker, 0, wxALL, 5);
    m_options_box->Add(this->m_alert_datepicker, 0, wxALL, 5);
    m_options_box->Add(this->m_day_dropdown, 0, wxALL, 5);
    m_options_box->Add(this->m_days_of_the_week, 0, wxALL, 5);
    m_options_box->Add(this->m_color_picker, 0, wxALL, 5);
    m_options_box->Add(this->m_alert_timing_checklist_box, 0, wxALL, 5);
    
    m_v_sizer->Add(m_options_box, 0, wxEXPAND | wxALL, 10);

    // Add Save button with centered alignment
    m_v_sizer->Add(m_save_button, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    m_v_sizer->Add(m_cancel_button, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

    // Set the sizer for the frame
    this->SetSizerAndFit(m_v_sizer);

    // Connect the Save button click event to the event handler
    m_save_button->Bind(wxEVT_BUTTON, &mw::ReminderFrame::OnSaveButton, this);
    m_cancel_button->Bind(wxEVT_BUTTON, &mw::ReminderFrame::OnCancelButton, this);
    m_repeat_options->Bind(wxEVT_CHOICE, &mw::ReminderFrame::OnRepeatOptionsChange, this);
    m_alert_timing_checklist_box->Bind(wxEVT_CHECKLISTBOX, &mw::ReminderFrame::OnAlertTimingOptionChanged, this);
}

mw::ReminderFrame::~ReminderFrame()
{
}

void mw::ReminderFrame::SetReminder(const mw::Reminder& reminder)
{
    m_new_reminder = false;
	m_reminder = reminder;
}

void mw::ReminderFrame::OnSaveButton(wxCommandEvent& event)
{
    wxString title = title_input->GetValue();
    wxString text = text_input->GetValue();
    if (!title.IsEmpty())
        m_reminder.title = std::string(title.mb_str());
    m_reminder.text = std::string(text.mb_str());
    m_reminder.status = ReminderStatus::ACTIVE;
    m_reminder.repeat = (mw::ReminderRepeatOptions)m_repeat_options->GetSelection();
    wxArrayInt checklist_selections;
    this->m_alert_timing_checklist_box->GetSelections(checklist_selections);

    wxColor color = m_color_picker->GetColour();
    m_reminder.color = m_reminder.RGBToHexString(color.GetRed(), color.GetGreen(), color.GetBlue());


    int hour = 0, min = 0, sec = 0;
    this->m_alert_timepicker->GetTime(&hour, &min, &sec);
    this->m_reminder.hour = hour;
    this->m_reminder.min = min;
    this->m_reminder.sec = sec;

    wxDateTime date = this->m_alert_datepicker->GetValue();
    this->m_reminder.day = date.GetDay();
    this->m_reminder.month = date.GetMonth();
    this->m_reminder.year = date.GetYear();


    this->GetSelectedDaysOfTheWeek(m_reminder.days_of_week);
    this->GetSelectedAlertTimingOptions(m_reminder.alert_timing);

    if (m_new_reminder == true)
        m_reminder.StampCreationTime();
    mw::Controller& controller = mw::Controller::Get();
    controller.AddReminder(m_reminder);
    this->Close();
}

void mw::ReminderFrame::OnCancelButton(wxCommandEvent& event)
{
    this->Close();
}

void mw::ReminderFrame::OnRepeatOptionsChange(wxCommandEvent& event)
{
    int selected_index = m_repeat_options->GetSelection();

    // for very repeat option there will be a different UI
    switch (selected_index)
    {
    case 0:
        this->m_alert_datepicker->Show(true);
        this->m_days_of_the_week->Hide();
        this->m_day_dropdown->Hide();
        break;
    case 1:
        this->m_days_of_the_week->Show(true);
        this->m_day_dropdown->Hide();
        this->m_alert_datepicker->Hide();
        break;
    case 2:
        this->m_day_dropdown->Show(true);
        this->m_days_of_the_week->Hide();
        this->m_alert_datepicker->Hide();
        break;
    default:
        break;
    }
    this->m_options_box->Layout();
    this->m_v_sizer->Layout();
}

void mw::ReminderFrame::OnAlertTimingOptionChanged(wxCommandEvent& event)
{
    int count = this->m_alert_timing_checklist_box->GetCount();

    int checkedCount = 0;

    // Count the number of checked items
    for (int i = 0; i < count; ++i)
    {
        if (this->m_alert_timing_checklist_box->IsChecked(i))
        {
            checkedCount++;
        }
    }

    if (checkedCount == 0)
    {
        // If no item is selected, prevent unchecking the currently checked item
        int itemIndex = event.GetInt();
        this->m_alert_timing_checklist_box->Check(itemIndex);
    }
}

void mw::ReminderFrame::HideAllRepeatOptions()
{
    
}

void mw::ReminderFrame::GetSelectedDaysOfTheWeek(std::vector<std::string>& selecteds_days)
{
    int item_count = this->m_days_of_the_week->GetCount();
    for (int i = 0; i < item_count; i++) {
        if (this->m_days_of_the_week->IsChecked(i)) {
            selecteds_days.push_back(this->m_days_of_the_week->GetString(i).ToStdString());
        }
    }
}

void mw::ReminderFrame::GetSelectedAlertTimingOptions(std::vector<std::string>& selected)
{
    int item_count = this->m_alert_timing_checklist_box->GetCount();
    for (int i = 0; i < item_count; i++) {
        if (this->m_alert_timing_checklist_box->IsChecked(i)) {
            selected.push_back(this->m_alert_timing_checklist_box->GetString(i).ToStdString());
        }
    }
}

