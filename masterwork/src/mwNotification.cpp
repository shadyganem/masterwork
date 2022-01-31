#include "model/Notification.h"

mw::Notification::Notification()
{
	uid = 0;
	user_uid = 0;
	text = "";
	status = mw::NotificationStatus::UNREAD;
	std::time(&this->start_time);
	std::time(&this->last_update);
	color = -1;
}

mw::Notification::~Notification()
{
}

void mw::Notification::SetUid(int id)
{
	uid = id;
}

int mw::Notification::GetStatus()
{
	return this->status;
}

int mw::Notification::GetUid()
{
	return this->uid;
}

void mw::Notification::StampLastUpdateTime()
{
	std::time(&this->last_update);
}

void mw::Notification::UpdateTimeToLive()
{
	
}



