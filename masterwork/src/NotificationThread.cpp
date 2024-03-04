#include "controller/NotificationThread.h"
#include <wx/notifmsg.h>

mw::NotificationThread::NotificationThread(wxEvtHandler* parent): wxThread(wxTHREAD_DETACHED), m_parent(parent)
{

}

void* mw::NotificationThread::Entry()
{
    mw::Logger logger;
    logger.EnableDebug();
    logger.Debug("started the notification thread");
    // This will run in a seperate thread. 
    mw::Controller& controller = mw::Controller::Get();
    std::vector<mw::Reminder> reminders; 
    controller.GetRemindersForActiveUser(reminders);

    wxNotificationMessage::MSWUseToasts();

    for (size_t i = 0; i < reminders.size(); ++i)
    {
        if (reminders[i].ready())
        {
            controller.UpdateRreminder(reminders[i]);
            wxNotificationMessage notification(reminders[i].title, reminders[i].text);
            notification.Show();
        }
    }

    logger.Debug("ended the notification thread");

    logger.DisableDebug();

    wxThreadEvent* event = new wxThreadEvent(wxEVT_THREAD, NOTIFICATION_THREAD_EVENT_ID);
    m_parent->QueueEvent(event);
    return NULL;
}
