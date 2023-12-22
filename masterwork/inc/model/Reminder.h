#pragma once
#include "ModelItem.h"
#include <string>
#include <ctime>
#include <vector>

namespace mw
{
	enum ReminderStatus
	{
		ACTIVE,
		DISABLED
	};

	enum ReminderRepeatOptions
	{
		DONT_REPEAT,
		EVERYDAY,
		EVERY_MONTH,
		EVERY_YEAR
	};

	class Reminder : public ModelItem
	{
	public: 
		Reminder();
		~Reminder();
		void Hash();
		std::string GetStatus();
		std::string GetEndTime();

		std::string RepateOptionToString(mw::ReminderRepeatOptions option);
		static std::vector<std::string> GetRepeatOptions();
		
	public:
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
		std::string color;
	};
}

