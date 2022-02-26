#include "Controller/StagehandThread.h"

mw::StagehandThread::~StagehandThread()
{
}

wxThread::ExitCode mw::StagehandThread::Entry()
{
	mw::Logger logger;
	while (!TestDestroy())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	return (wxThread::ExitCode)0;
}
