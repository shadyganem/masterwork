#include "view/NewReminderFrame.h"

mw::NewReminderFrame::NewReminderFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) 
	: wxFrame(parent, id, title, pos, size, style)
{
    // Create input fields and button
    titleInput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    textInput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    save_button = new wxButton(this, wxID_ANY, wxT("Save"));

    // Create a vertical sizer to arrange the components
    wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Title:")), 0, wxALL, 5);
    vSizer->Add(titleInput, 0, wxEXPAND | wxALL, 5);
    vSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Text:")), 0, wxALL, 5);
    vSizer->Add(textInput, 1, wxEXPAND | wxALL, 5);
    vSizer->Add(save_button, 0, wxALIGN_RIGHT | wxALL, 5);

    // Set the sizer for the frame
    this->SetSizer(vSizer);

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
    wxString title = titleInput->GetValue();
    wxString text = textInput->GetValue();
    m_reminder.title = std::string(title.mb_str());
    m_reminder.text = std::string(text.mb_str());
    m_reminder.status = ReminderStatus::ACTIVE;

    // You can continue setting other reminder properties here



    this->Close();
}

