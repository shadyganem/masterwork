#pragma once
#include <wx/thread.h>
#include "controller/Logger.h"
#include <chrono>
#include <thread>


namespace mw
{
	class StagehandThread : public wxThread
	{
	public:
		StagehandThread() : wxThread(wxTHREAD_DETACHED)	{}
		~StagehandThread();
	protected:
		virtual wxThread::ExitCode Entry();
	};
}

