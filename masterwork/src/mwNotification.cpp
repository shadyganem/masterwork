#include "model/Notification.h"

mw::Notification::Notification()
{
	uid = 0;
	user_uid = 0;
	text = "";
	status = mw::NotificationStatus::UNREAD;
}

mw::Notification::~Notification()
{
	uid = 0;
	user_uid = 0;
	text = "";
	status = mw::NotificationStatus::UNREAD;
}

void mw::Notification::SetUid(int id)
{
	uid = id;
}

int mw::Notification::GetStatus()
{
	return this->status;
}

