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

	

	this->Bind(wxEVT_MENU, &mw::PasswordWindow::OnMenuCopyClick, this, wxID_COPY);
	this->Bind(wxEVT_MENU, &mw::PasswordWindow::OnMenuDeleteClick, this, wxID_DELETE);
	this->Bind(wxEVT_MENU, &mw::PasswordWindow::OnMenuEditClick, this, wxID_EDIT);

	m_new_password_button->Bind(wxEVT_BUTTON, &mw::PasswordWindow::OnNewPasswordButton, this);
	m_passwords_data_view_list->Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &mw::PasswordWindow::OnContextMenu, this);

	controller.RequestUpdateUI(this->GetId());
}

mw::PasswordWindow::~PasswordWindow()
{
}

void mw::PasswordWindow::OnUpdateUI(wxEvent& event)
{
	m_index_to_password_map.clear();
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
		m_index_to_password_map[i] = passwords[i];
	}
}

void mw::PasswordWindow::OnNewPasswordButton(wxCommandEvent& event)
{
	mw::PasswordFrame* new_password_frame = new mw::PasswordFrame(this);
	new_password_frame->Center();
	new_password_frame->Show();
}

void mw::PasswordWindow::OnContextMenu(wxDataViewEvent& event)
{
	wxDataViewItem selected_item = event.GetItem();
	if (!selected_item.IsOk())
	{
		return;
	}
	int selected_items_count = m_passwords_data_view_list->GetSelectedItemsCount();
	// Get the mouse position
	wxPoint pos = event.GetPosition();

	// Convert the position to the client coordinates
	wxDataViewItem item;
	wxDataViewColumn* col;
	m_passwords_data_view_list->HitTest(pos, item, col);
	int row = m_passwords_data_view_list->ItemToRow(item);

	m_menu_selected_password = m_index_to_password_map[row];
	wxMenu menu;
	if (selected_items_count == 1)
	{
		if (col->GetTitle() == "password")
		{
			menu.Append(wxID_COPY, "Copy password To Clipboard");
			m_text_for_copy = m_menu_selected_password.encrypted_password;
		}

		if (col->GetTitle() == "url")
		{
			menu.Append(wxID_COPY, "Copy url To Clipboard");
			m_text_for_copy = m_passwords_data_view_list->GetTextValue(row, event.GetColumn());
		}

		if (col->GetTitle() == "username")
		{
			menu.Append(wxID_COPY, "Copy username To Clipboard");
			m_text_for_copy = m_passwords_data_view_list->GetTextValue(row, event.GetColumn());
		}
	}

	menu.Append(wxID_EDIT, "Edit");
	menu.Append(wxID_DELETE, "Delete");

	PopupMenu(&menu);
	event.Skip();
}

void mw::PasswordWindow::OnMenuCopyClick(wxCommandEvent& event)
{
	mw::Clipboard clipboard;
	clipboard.CopyTextToClipboard(m_text_for_copy);
	m_text_for_copy.clear();
}

void mw::PasswordWindow::OnMenuDeleteClick(wxCommandEvent& event)
{
	int selected_items_count = m_passwords_data_view_list->GetSelectedItemsCount();
	if (selected_items_count == 0)
	{
		return;
	}
	mw::Controller& controller = mw::Controller::Get();
	int answer = 0;
	if (selected_items_count == 1)
	{
		answer = wxMessageBox("Are you sure you want to permanently delete this password?", "Confirm", wxYES_NO, this);
	}
	else if (selected_items_count > 1)
	{
		answer = wxMessageBox("Are you sure you want to permanently delete all selected passwords?", "Confirm", wxYES_NO, this);
	}

	if (answer == wxYES)
	{
		std::vector<mw::Password> passwords_for_deletion;
		this->GetSelectedPasswords(passwords_for_deletion);
		controller.DeletePasswords(passwords_for_deletion);
	}
}

void mw::PasswordWindow::OnMenuEditClick(wxCommandEvent& event)
{
	std::vector<mw::Password> passwords;
	this->GetSelectedPasswords(passwords);
	
	for (int i = 0; i < passwords.size(); i++)
	{
		mw::PasswordFrame* password_frame = new mw::PasswordFrame(this);
		password_frame->SetPassword(passwords[i]);
		password_frame->Center();
		password_frame->Show();
		
	}
}

void mw::PasswordWindow::AddPassword(mw::Password& password)
{
	wxVector<wxVariant> data;
	data.push_back(wxVariant(password.username));
	data.push_back(wxVariant(password.url));
	data.push_back(wxVariant(password.notes));
	std::string copy = password.encrypted_password;
	std::fill(copy.begin(), copy.end(), '*');
	data.push_back(wxVariant(copy));
	m_passwords_data_view_list->AppendItem(data);
}

void mw::PasswordWindow::GetSelectedPasswords(std::vector<mw::Password>& passwords)
{
	int row_count = m_passwords_data_view_list->GetItemCount();
	for (int i = 0; i < row_count; i++)
	{
		if (m_passwords_data_view_list->IsRowSelected(i))
		{
			passwords.push_back(m_index_to_password_map[i]);
		}
	}
}
