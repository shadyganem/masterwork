#include "view/ReminderFrame.h"

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
    options = mw::Reminder::GetAlertOptions();
    wxStringArray.Clear();
    wxStringArray.assign(options.begin(), options.end());

    // Create a wxCheckListBox for multi-selection
    m_alert_options_checklist_box = new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxStringArray);

    // Create a vertical sizer to arrange the components
    m_v_sizer = new wxBoxSizer(wxVERTICAL);

    // Group Title and Note using StaticBoxSizer
    wxStaticBoxSizer* titleNoteBox = new wxStaticBoxSizer(wxVERTICAL, this, "Title and Note");
    titleNoteBox->Add(new wxStaticText(this, wxID_ANY, wxT("Title:")), 0, wxALL, 5);
    titleNoteBox->Add(title_input, 0, wxEXPAND | wxALL, 5);
    titleNoteBox->Add(new wxStaticText(this, wxID_ANY, wxT("Note:")), 0, wxALL, 5);
    titleNoteBox->Add(text_input, 0, wxEXPAND | wxALL, 5);
    m_v_sizer->Add(titleNoteBox, 0, wxEXPAND | wxALL, 10);

    // Group Options using StaticBoxSizer
    m_options_box = new wxStaticBoxSizer(wxVERTICAL, this, "Options");
    m_options_box->Add(m_repeat_options, 0, wxALL, 5);
    m_options_box->Add(m_color_picker, 0, wxALL, 5);
    m_options_box->Add(m_alert_options_checklist_box, 0, wxALL, 5);


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
    m_reminder.repeat = m_repeat_options->GetSelection();
    wxArrayInt checklist_selections;
    m_alert_options_checklist_box->GetSelections(checklist_selections);

    wxColor color = m_color_picker->GetColour();
    m_reminder.color = m_reminder.RGBToHexString(color.GetRed(), color.GetGreen(), color.GetBlue());
    // You can continue setting other reminder properties here
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

    if (selected_index == 2)
    {
        this->m_color_picker->Hide();
    }
    else
    {
        this->m_color_picker->Show(true);
    }

    this->m_v_sizer->Layout();


}

void mw::ReminderFrame::HideAllRepeatOptions()
{
    
}

