#include "mwApp.h"

wxIMPLEMENT_APP(mwApp);

mwApp::mwApp()
{

}

mwApp::~mwApp()
{

}

// Application Entry Point
bool mwApp::OnInit()
{
	// Load XML Based Resources
	/*
	wxImage::AddHandler(new wxGIFHandler);
	wxXmlResource::Get()->InitAllHandlers();
	wxXmlResource::Get()->Load("xrc\resources.xrc");
	*/
	// Create the Main Frame
	m_main_frame = new mwMainFrame("MasterWork", wxPoint(50, 50), wxSize(1150, 635));
	m_main_frame->Show(true);
	return true;
}