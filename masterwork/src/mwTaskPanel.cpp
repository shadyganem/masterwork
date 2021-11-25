#include "view/mwTaskPanel.h"


///////////////////////////////////////////////////////////////////////////

mwTaskPanel::mwTaskPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* hor_sizer1;
	hor_sizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* ver_sizer1;
	ver_sizer1 = new wxBoxSizer( wxVERTICAL );
	
	ver_sizer1->SetMinSize( wxSize( 700,-1 ) ); 
	m_taskname = new wxTextCtrl( this, wxID_ANY, wxT("taskname"), wxDefaultPosition, wxDefaultSize, wxTE_LEFT|wxTE_PROCESS_ENTER );
	ver_sizer1->Add( m_taskname, 0, wxALL|wxEXPAND, 5 );
	
	m_richText1 = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	ver_sizer1->Add( m_richText1, 1, wxEXPAND | wxALL, 5 );
	
	hor_sizer1->Add( ver_sizer1, 4, wxEXPAND, 5 );
	
	wxBoxSizer* ver_sizer2;
	ver_sizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("hr"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer9->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_spinCtrl1 = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS, 0, 24, 17 );
	bSizer9->Add( m_spinCtrl1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer7->Add( bSizer9, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("min"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer10->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_spinCtrl3 = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS, 0, 59, 59 );
	bSizer10->Add( m_spinCtrl3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer7->Add( bSizer10, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("sec"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer11->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_spinCtrl2 = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS, 0, 59, 24 );
	bSizer11->Add( m_spinCtrl2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer7->Add( bSizer11, 1, wxEXPAND, 5 );
	
	ver_sizer2->Add( bSizer7, 0, 0, 5 );
	
	m_datePicker1 = new wxDatePickerCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT );
	ver_sizer2->Add( m_datePicker1, 0, wxALL|wxEXPAND, 5 );
	
	hor_sizer1->Add( ver_sizer2, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxString m_choice1Choices[] = { wxT("WIP"), wxT("Not Started"), wxT("Done"), wxT("Blocked") };
	int m_choice1NChoices = sizeof( m_choice1Choices ) / sizeof( wxString );
	m_choice1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1NChoices, m_choice1Choices, 0 );
	m_choice1->SetSelection( 1 );
	bSizer8->Add( m_choice1, 0, wxALL|wxEXPAND|wxALIGN_RIGHT, 5 );
	
	m_delete_task = new wxBitmapButton( this, wxID_ANY, wxBitmap(), wxDefaultPosition, wxSize(25, 25), wxBU_AUTODRAW);
	bSizer8->Add( m_delete_task, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	hor_sizer1->Add( bSizer8, 0, wxEXPAND, 5 );
	
	this->SetSizer( hor_sizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( mwTaskPanel::OnEnterWindow ) );
	this->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( mwTaskPanel::OnleaveWindow ) );
	m_choice1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( mwTaskPanel::OnStatusChanged ), NULL, this );
	m_delete_task->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mwTaskPanel::OnDelete ), NULL, this );
}

mwTaskPanel::~mwTaskPanel()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( mwTaskPanel::OnEnterWindow ) );
	this->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( mwTaskPanel::OnleaveWindow ) );
	m_choice1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( mwTaskPanel::OnStatusChanged ), NULL, this );
	m_delete_task->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mwTaskPanel::OnDelete ), NULL, this );
}