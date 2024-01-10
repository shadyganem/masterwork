#include "MasterWork.h"
wxIMPLEMENT_APP(MasterWork);

// Application Entry Point
bool MasterWork::OnInit()
{
	wxSingleInstanceChecker* checker = new wxSingleInstanceChecker;
	if (checker->IsAnotherRunning())
	{
		delete checker; // OnExit() won't be called if we return false therefore it is important to delete the checker object.
		checker = NULL;
		return false;
	}
	mw::Controller& controller = mw::Controller::Get();

	controller.Init();
	// first Login
	mw::LoginFrame* login = new mw::LoginFrame(NULL);
	login->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MasterWork::OnLogin, this);
	login->Show(true);
	return true;
}

void MasterWork::OnLogin(wxCommandEvent& event)
{
	// Create the Main Frame
	m_main_frame = new mw::MainFrame("MasterWork", wxPoint(50, 50), wxSize(1150, 635));
	m_main_frame->Show(true);
}
