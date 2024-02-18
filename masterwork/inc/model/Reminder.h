#pragma once
#include "ModelItem.h"
#include <string>
#include <ctime>
#include <vector>
#include <chrono>
#include "controller/Logger.h"
#include "model/json.hpp"


namespace mw
{
	enum ReminderStatus
	{
		ACTIVE,
		DISABLED,
		INVALID
	};

	enum ReminderRepeatOptions
	{
		ONE_TIME,
		DAYS_OF_WEEK,
		ONCE_A_MONTH
	};

	class Reminder : public ModelItem
	{
	public: 
		Reminder();
		~Reminder();
		void Hash();
		std::string GetStatus();
		std::string GetEndTime();

		std::string RepeatOptionToString(mw::ReminderRepeatOptions option);
		static std::vector<std::string> GetRepeatOptions();
		static std::vector<std::string> GetAlertTimingOptions();
		static std::vector<std::string> GetDaysOfTheWeekOptions();
		static std::vector<std::string> GetAlertMethodOptions();
		virtual std::string dump_json_alert_data();
		virtual void parse_json_alert_data(std::string data);
		
	public:
		int user_uid;
		std::string title;
		bool is_active;
		unsigned long long hash;
		std::string text;
		ReminderStatus status;
		mw::ReminderRepeatOptions repeat;
		int priority;
		time_t start_time;
		time_t end_time;
		time_t reminder_time;
		int ttl;
		std::string color;
		int hour = 0, min = 0, sec = 0;
		int day = 0, month = 1, year = 0;
		std::vector<std::string> days_of_week;
		std::vector<std::string> alert_timing;
	private:
		std::string json_alert_data;
		
	};
}

