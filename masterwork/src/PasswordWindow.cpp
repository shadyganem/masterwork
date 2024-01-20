#include "view/PasswordWindow.h"

BEGIN_EVENT_TABLE(mw::PasswordWindow, wxScrolledWindow)
	EVT_CUSTOM(mwUpdateUI, PASSWORDS_WINDOW_ID, mw::PasswordWindow::OnUpdateUI)
END_EVENT_TABLE()

mw::PasswordWindow::PasswordWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
	: wxScrolledWindow(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_sizer_1 = new wxBoxSizer(wxVERTICAL);

	wxColour background = controller.m_backgroud_color;
	wxColour foreground = controller.m_foreground_color;
	m_toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TEXT);

	wxColour green(0, 136, 135);

	m_new_password_button = new mw::Button(m_toolbar, wxID_ANY, "New Password", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_new_password_button->SetBackgroundColour(background);
	m_new_password_button->SetForegroundColour(green);
	m_toolbar->AddControl(m_new_password_button);

	m_toolbar->SetBackgroundColour(background);
	m_toolbar->SetForegroundColour(foreground);
	m_toolbar->Realize();

	m_sizer_1->Add(m_toolbar, 0, wxEXPAND);


	// instatiating m_reminders_data_view_list

	m_passwords_data_view_list = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_MULTIPLE | wxDV_HORIZ_RULES);

	m_passwords_data_view_list->AppendColumn(new wxDataViewColumn("username", new wxDataViewTextRenderer(), 0, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_passwords_data_view_list->AppendColumn(new wxDataViewColumn("url", new wxDataViewTextRenderer(), 1, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_passwords_data_view_list->AppendColumn(new wxDataViewColumn("notes", new wxDataViewTextRenderer(), 2, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_passwords_data_view_list->AppendColumn(new wxDataViewColumn("password", new wxDataViewTextRenderer(), 3, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));

	m_passwords_data_view_list->SetBackgroundColour(background);
	m_passwords_data_view_list->SetForegroundColour(foreground);

	m_sizer_1->Add(m_passwords_data_view_list, 1, wxEXPAND, 0);

	this->SetBackgroundColour(background);
	this->SetSizer(m_sizer_1);
	this->Layout();

	

	this->Bind(wxEVT_MENU, &mw::PasswordWindow::OnMenuClick, this, wxID_COPY);

	m_new_password_button->Bind(wxEVT_BUTTON, &mw::PasswordWindow::OnNewPasswordButton, this);
	m_passwords_data_view_list->Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &mw::PasswordWindow::OnContextMenu, this);

	controller.RequestUpdateUI(this->GetId());
}

mw::PasswordWindow::~PasswordWindow()
{
}

void mw::PasswordWindow::OnUpdateUI(wxEvent& event)
{
	m_passwords_data_view_list->DeleteAllItems();
	mw::Controller& controller = mw::Controller::Get();
	wxColour background = controller.m_backgroud_color;
	wxColour foreground = controller.m_foreground_color;
	m_toolbar->SetBackgroundColour(background);
	m_toolbar->SetForegroundColour(foreground);


	std::vector<mw::Password> passwords;
	controller.GetPasswordsForActiveUser(passwords);

	for (int i = 0; i < passwords.size(); i++)
	{
		this->AddPassword(passwords[i]);
	}

}

void mw::PasswordWindow::OnNewPasswordButton(wxCommandEvent& event)
{
	mw::NewPasswordFrame* new_password_frame = new mw::NewPasswordFrame(this);
	new_password_frame->Center();
	new_password_frame->Show();
}

void mw::PasswordWindow::OnContextMenu(wxDataViewEvent& event)
{
	
	// Get the mouse position
	wxPoint pos = event.GetPosition();

	// Convert the position to the client coordinates
	wxDataViewItem item;
	wxDataViewColumn* col;
	m_passwords_data_view_list->HitTest(pos, item, col);
	int row = m_passwords_data_view_list->ItemToRow(item);
	wxMenu menu;
	if (col->GetTitle() == "password")
	{
		menu.Append(wxID_COPY, "Copy password To Clipboard");
		m_text_for_copy = m_passwords_data_view_list->GetTextValue(row, event.GetColumn());
		PopupMenu(&menu);
	}

	if (col->GetTitle() == "url")
	{
		menu.Append(wxID_COPY, "Copy url To Clipboard");
		m_text_for_copy = m_passwords_data_view_list->GetTextValue(row, event.GetColumn());
		PopupMenu(&menu);
	}

	if (col->GetTitle() == "username")
	{
		menu.Append(wxID_COPY, "Copy username To Clipboard");
		m_text_for_copy = m_passwords_data_view_list->GetTextValue(row, event.GetColumn());
		PopupMenu(&menu);
	}
	event.Skip();
}

void mw::PasswordWindow::OnMenuClick(wxCommandEvent& event)
{
	mw::Clipboard clipboard;
	clipboard.CopyTextToClipboard(m_text_for_copy);
	m_text_for_copy.clear();
}

void mw::PasswordWindow::AddPassword(mw::Password& password)
{
	wxVector<wxVariant> data;
	data.push_back(wxVariant(password.username));
	data.push_back(wxVariant(password.url));
	data.push_back(wxVariant(password.notes));
	data.push_back(wxVariant(password.encrypted_password));
	m_passwords_data_view_list->AppendItem(data);
}
