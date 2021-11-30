#include "view/mwTaskPanel.h"


///////////////////////////////////////////////////////////////////////////

void mwTaskPanel::OnEnterWindow(wxMouseEvent& event)
{
	//this->SetBackgroundColour(wxColor(0, 31, 51));
	this->Refresh();
	event.Skip();
}

void mwTaskPanel::OnleaveWindow(wxMouseEvent& event)
{
    //this->SetBackgroundColour(wxColor(240, 240, 240));
	this->Refresh();
	event.Skip();
}

void mwTaskPanel::OnEditTask(wxCommandEvent& event)
{
	m_static_view->Hide();
	m_edit_view->Show();
	ver_task_sizer->Layout();
	event.Skip();
}

void mwTaskPanel::OnSaveTask(wxCommandEvent& event)
{
	m_edit_view->Hide();
	m_static_view->Show();
	ver_task_sizer->Layout();
	event.Skip();
}

mwTaskPanel::mwTaskPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	ver_task_sizer = new wxBoxSizer(wxVERTICAL);

	m_static_view = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer(wxVERTICAL);

	m_staticText5 = new wxStaticText(m_static_view, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText5->Wrap(-1);
	bSizer17->Add(m_staticText5, 0, wxALL, 5);

	m_staticText41 = new wxStaticText(m_static_view, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText41->Wrap(-1);
	bSizer17->Add(m_staticText41, 0, wxALL, 5);

	bSizer16->Add(bSizer17, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer(wxVERTICAL);

	bSizer16->Add(bSizer18, 1, wxEXPAND, 5);

	m_edit_task = new wxButton(m_static_view, wxID_ANY, wxT("Edit"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer16->Add(m_edit_task, 0, wxALL, 5);

	m_static_view->SetSizer(bSizer16);
	m_static_view->Layout();
	bSizer16->Fit(m_static_view);
	ver_task_sizer->Add(m_static_view, 1, wxEXPAND | wxALL, 5);

	m_edit_view = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_edit_view->Hide();

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* ver_sizer1;
	ver_sizer1 = new wxBoxSizer(wxVERTICAL);

	ver_sizer1->SetMinSize(wxSize(700, -1));
	m_taskname = new wxTextCtrl(m_edit_view, wxID_ANY, wxT("taskname"), wxDefaultPosition, wxDefaultSize, wxTE_LEFT | wxTE_PROCESS_ENTER);
	ver_sizer1->Add(m_taskname, 0, wxALL | wxEXPAND, 5);

	m_richText1 = new wxRichTextCtrl(m_edit_view, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1, -1), 0 | wxVSCROLL | wxHSCROLL | wxNO_BORDER | wxWANTS_CHARS);
	ver_sizer1->Add(m_richText1, 1, wxEXPAND | wxALL, 5);

	bSizer13->Add(ver_sizer1, 4, wxEXPAND, 5);

	wxBoxSizer* ver_sizer2;
	ver_sizer2 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxVERTICAL);

	m_staticText2 = new wxStaticText(m_edit_view, wxID_ANY, wxT("hr"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	bSizer9->Add(m_staticText2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_spinCtrl1 = new wxSpinCtrl(m_edit_view, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(45, -1), wxSP_ARROW_KEYS, 0, 24, 17);
	bSizer9->Add(m_spinCtrl1, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	bSizer7->Add(bSizer9, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer(wxVERTICAL);

	m_staticText4 = new wxStaticText(m_edit_view, wxID_ANY, wxT("min"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText4->Wrap(-1);
	bSizer10->Add(m_staticText4, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_spinCtrl3 = new wxSpinCtrl(m_edit_view, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(45, -1), wxSP_ARROW_KEYS, 0, 59, 59);
	bSizer10->Add(m_spinCtrl3, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	bSizer7->Add(bSizer10, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer(wxVERTICAL);

	m_staticText3 = new wxStaticText(m_edit_view, wxID_ANY, wxT("sec"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	bSizer11->Add(m_staticText3, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_spinCtrl2 = new wxSpinCtrl(m_edit_view, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(45, -1), wxSP_ARROW_KEYS, 0, 59, 24);
	bSizer11->Add(m_spinCtrl2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	bSizer7->Add(bSizer11, 1, wxEXPAND, 5);

	ver_sizer2->Add(bSizer7, 0, 0, 5);

	m_datePicker1 = new wxDatePickerCtrl(m_edit_view, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT);
	ver_sizer2->Add(m_datePicker1, 0, wxALL | wxEXPAND, 5);

	bSizer13->Add(ver_sizer2, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxVERTICAL);

	wxString m_choice1Choices[] = { wxT("WIP"), wxT("Not Started"), wxT("Done"), wxT("Blocked") };
	int m_choice1NChoices = sizeof(m_choice1Choices) / sizeof(wxString);
	m_choice1 = new wxChoice(m_edit_view, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1NChoices, m_choice1Choices, 0);
	m_choice1->SetSelection(1);
	bSizer8->Add(m_choice1, 0, wxALL | wxEXPAND | wxALIGN_RIGHT, 5);

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer(wxHORIZONTAL);

	m_delete_task = new wxBitmapButton(m_edit_view, wxID_ANY, wxBitmap(), wxDefaultPosition, wxSize(25, 25), wxBU_AUTODRAW);
	bSizer15->Add(m_delete_task, 0, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

	m_save_task = new wxBitmapButton(m_edit_view, wxID_ANY, wxBitmap(), wxDefaultPosition, wxSize(25, 25), wxBU_AUTODRAW);
	bSizer15->Add(m_save_task, 0, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

	bSizer8->Add(bSizer15, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);

	bSizer13->Add(bSizer8, 0, wxEXPAND, 5);

	m_edit_view->SetSizer(bSizer13);
	m_edit_view->Layout();
	bSizer13->Fit(m_edit_view);
	ver_task_sizer->Add(m_edit_view, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(ver_task_sizer);
	this->Layout();

	// Connect Events
	this->Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(mwTaskPanel::OnEnterWindow));
	this->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mwTaskPanel::OnleaveWindow));
	m_edit_task->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwTaskPanel::OnEditTask), NULL, this);
	m_choice1->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(mwTaskPanel::OnStatusChanged), NULL, this);
	m_delete_task->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwTaskPanel::OnDelete), NULL, this);
	m_save_task->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwTaskPanel::OnSaveTask), NULL, this);
}

mwTaskPanel::~mwTaskPanel()
{
	// Disconnect Events
	this->Disconnect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(mwTaskPanel::OnEnterWindow));
	this->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mwTaskPanel::OnleaveWindow));
	m_edit_task->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwTaskPanel::OnEditTask), NULL, this);
	m_choice1->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(mwTaskPanel::OnStatusChanged), NULL, this);
	m_delete_task->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwTaskPanel::OnDelete), NULL, this);
	m_save_task->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwTaskPanel::OnSaveTask), NULL, this);
}