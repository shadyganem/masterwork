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
		COMPLETE,
		DISABLED,
		INVALID
	};

	enum ReminderRepeatOptions
	{
		// remember to update the repeat_option_to_string map to include new items
		ONE_TIME,
		DAYS_OF_WEEK,
		ONCE_A_MONTH
	};

	enum ReminderAlertTiming
	{
		// remember to update the repeat_option_to_string map to include new items
		AT_TIME_OF_EVENT,
		TEN_MINUTES_BEOFORE,
		ONE_HOUR_BEFORE,
		ONE_DAY_BEFORE
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
		virtual bool ready();
		
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
		int hour, min, sec;
		int day, month, year;
		std::vector<std::string> days_of_week;
		std::vector<std::string> alert_timing;
		std::vector<std::string> alert_methods;
		const static std::map<mw::ReminderRepeatOptions, std::string> repeat_option_to_string;
		const static std::map<mw::ReminderStatus, std::string> reminder_status_to_string;
		const static std::map<mw::ReminderAlertTiming, std::string> alert_timing_to_string;
	private:
		bool isTimePassed(int hour, int min, int sec, int day, int month, int year);
		std::string json_alert_data;
		
	};
}

