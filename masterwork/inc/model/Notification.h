#pragma once
#include "model/mwModelItem.h"
#include <string>
#include <ctime>
#include <functional>


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
		void SetHashToken(int token);
		void StampLastUpdateTime();
		void UpdateTimeToLive();
		void Hash();
		void Hash(time_t any);


		int uid;
		unsigned long long hash;
		int user_uid;
		int task_uid;
		std::string text;
		std::string details;
		NotificationStatus status;
		int repeat;
		int priority;
		time_t start_time;
		time_t end_time;
		time_t last_update;
		int ttl;
		int color;

	private:
		int hash_token;
	};
}

