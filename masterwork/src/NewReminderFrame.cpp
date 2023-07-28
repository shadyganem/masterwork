#include "view/NewReminderFrame.h"

mw::NewReminderFrame::NewReminderFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) 
	: wxFrame(parent, id, title, pos, size, style)
{
    // Create input fields and button
    title_input = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    text_input = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    save_button = new wxButton(this, wxID_ANY, wxT("Save"));

    // Create a vertical sizer to arrange the components
    wxBoxSizer* v_sizer = new wxBoxSizer(wxVERTICAL);
    v_sizer->Add(new wxStaticText(this, wxID_ANY, wxT("Title:")), 0, wxALL, 5);
    v_sizer->Add(title_input, 0, wxEXPAND | wxALL, 5);
    v_sizer->Add(new wxStaticText(this, wxID_ANY, wxT("Text:")), 0, wxALL, 5);
    v_sizer->Add(text_input, 1, wxEXPAND | wxALL, 5);
    v_sizer->Add(save_button, 0, wxALIGN_RIGHT | wxALL, 5);

    // Set the sizer for the frame
    this->SetSizer(v_sizer);

    // Connect the Save button click event to the event handler
    save_button->Bind(wxEVT_BUTTON, &mw::NewReminderFrame::OnSaveButton, this);

}

mw::NewReminderFrame::~NewReminderFrame()
{
}

void mw::NewReminderFrame::SetReminder(const mw::Reminder& reminder)
{
	m_reminder = reminder;
}

void mw::NewReminderFrame::OnSaveButton(wxCommandEvent& event)
{
    wxString title = title_input->GetValue();
    wxString text = text_input->GetValue();
    m_reminder.title = std::string(title.mb_str());
    m_reminder.text = std::string(text.mb_str());
    m_reminder.status = ReminderStatus::ACTIVE;

    // You can continue setting other reminder properties here
    mw::Logger logger;
    logger.EnableDebug();

    logger.Debug(m_reminder.title);
    logger.DisableDebug();
    
    mw::Controller& controller = mw::Controller::Get();


    controller.AddReminder(m_reminder);

    this->Close();
}

