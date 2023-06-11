#pragma once
#include "ModelItem.h"
#include <string>
#include <ctime>

namespace mw
{
	enum ReminderStatus
	{
		ACTIVE,
		DISABLED
	};

	class Reminder :	public ModelItem
	{
	public: 
		Reminder();
		~Reminder();
		void Hash();
		std::string GetStatus();
		std::string GetEndTime();

	public:
		int uid;
		int user_uid;
		std::string title;
		bool is_active;
		unsigned long long hash;
		std::string text;
		ReminderStatus status;
		int repeat;
		int priority;
		time_t start_time;
		time_t end_time;
		int ttl;
		int color;
	};
}

