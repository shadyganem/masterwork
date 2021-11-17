#include "MasterWork.h"

wxIMPLEMENT_APP(MasterWork);

// Application Entry Point
bool MasterWork::OnInit()
{
	// Create the Main Frame
	m_main_frame = new mwMainFrame("MasterWork", wxPoint(50, 50), wxSize(1150, 635));
	m_main_frame->Show(true);
	return true;
}