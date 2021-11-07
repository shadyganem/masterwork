#include "CApp.h"

wxIMPLEMENT_APP(CApp);

CApp::CApp()
{

}

CApp::~CApp()
{

}

bool CApp::OnInit()
{
	// Application Entry Point
	m_main_frame = new CMainFrame("MasterWork", wxPoint(50, 50), wxSize(500, 500));
	m_main_frame->Show();
	return true;
}