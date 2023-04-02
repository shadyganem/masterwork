#include "controller/NotificationThread.h"


mw::NotificationThread::NotificationThread(wxEvtHandler* parent): wxThread(wxTHREAD_DETACHED), m_parent(parent)
{

}

void* mw::NotificationThread::Entry()
{
    // This will run in a seperate thread. 

    mw::Controller& controller = mw::Controller::Get();
    wxThreadEvent* event = new wxThreadEvent(wxEVT_THREAD, NOTIFICATION_THREAD_EVENT_ID);
    m_parent->QueueEvent(event);
    return NULL;
}
