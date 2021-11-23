#include "model/mwNotification.h"

mwNotification::mwNotification()
{
	uid = 0;
	user_uid = 0;
	text = "";
	status = mwNotification::Unread;
}

mwNotification::~mwNotification()
{
}

void mwNotification::SetUid(int id)
{
	uid = id;
}

int mwNotification::GetStatus()
{
	return this->status;
}

