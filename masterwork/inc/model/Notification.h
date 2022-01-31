#pragma once
#include "model/mwModelItem.h"
#include <string>
#include <ctime>

namespace mw
{
	enum NotificationStatus
	{
		UNREAD,
		READ
	};

	class Notification : public mwModelItem
	{
	public:
		Notification();
		~Notification();
		void SetUid(int uid);
		int GetStatus();
		int GetUid();
		void StampLastUpdateTime();
		void UpdateTimeToLive();


		int uid;
		int user_uid;
		std::string text;
		NotificationStatus status;
		int repeat;
		int priority;
		time_t start_time;
		time_t end_time;
		time_t last_update;
		int ttl;
		int color;
	};
}

