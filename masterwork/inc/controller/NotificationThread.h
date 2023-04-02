#pragma once
#include "wx/thread.h"
#include "wx/event.h"
#include "controller/Controller.h"
#include "mwDefines.h"

namespace mw
{
	class NotificationThread :public wxThread
	{
    public:

        NotificationThread(wxEvtHandler* parent);

        virtual void* Entry();

    private:
        wxEvtHandler* m_parent;
	};
}


