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
		logger.Debug("from stagehand thread");
	}

	return (wxThread::ExitCode)0;
}
