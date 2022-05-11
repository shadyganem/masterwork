#include "MasterWork.h"
wxIMPLEMENT_APP(MasterWork);

// Application Entry Point
bool MasterWork::OnInit()
{
	wxSingleInstanceChecker* m_checker = new wxSingleInstanceChecker;
	if (m_checker->IsAnotherRunning())
	{
		delete m_checker; // OnExit() won't be called if we return false
		m_checker = NULL;
		return false;
	}
	mw::Controller& controller = mw::Controller::Get();

	controller.Init();
	// Create the Main Frame
	m_main_frame = new mw::MainFrame("MasterWork", wxPoint(50, 50), wxSize(1150, 635));
	m_main_frame->Show(true);
	return true;
}