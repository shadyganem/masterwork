#pragma once
#include "model/mwModelItem.h"
#include <string>
#include <ctime>

class mwNotification : public mwModelItem
{
public:
	enum NotificationStatus
	{
		Unread,
		Read
	};
public:
	mwNotification();
	~mwNotification();
	void SetUid(int uid);
	int GetStatus();
	int GetUid();

	int uid;
	int user_uid;
	std::string text;
	NotificationStatus status;
	int priority;
	time_t start_time;
	time_t end_time;
	time_t ttl;
	int red;
	int green;
	int blue;
};

