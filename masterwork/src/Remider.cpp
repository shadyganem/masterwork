#include "model/Reminder.h"

std::map<mw::ReminderRepeatOptions, std::string> mw::Reminder::repeat_option_to_string = {
	{mw::ReminderRepeatOptions::ONE_TIME, "One-Time"},
	{mw::ReminderRepeatOptions::DAYS_OF_WEEK, "Specific Days of the Week"},
	{mw::ReminderRepeatOptions::ONCE_A_MONTH, "Once a Month"}
};

std::map<mw::ReminderStatus, std::string> mw::Reminder::reminder_status_to_string = {
	{mw::ReminderStatus::ACTIVE, "Active"},
	{mw::ReminderStatus::COMPLETE, "Complete"},
	{mw::ReminderStatus::DISABLED, "Disabled"},
	{mw::ReminderStatus::INVALID, "Invalid"}
};

std::map<mw::ReminderAlertTiming, std::string> mw::Reminder::alert_timing_to_string = {
	{mw::ReminderAlertTiming::AT_TIME_OF_EVENT, "At time of event"},
	{mw::ReminderAlertTiming::TEN_MINUTES_BEOFORE, "10 Minutes Before"},
	{mw::ReminderAlertTiming::ONE_HOUR_BEFORE, "1 Hour Before"},
	{mw::ReminderAlertTiming::ONE_DAY_BEFORE, "1 Day Before"}	
};

std::map<std::string, mw::ReminderAlertTiming> mw::Reminder::string_to_alert_timing = {
	{"At time of event", mw::ReminderAlertTiming::AT_TIME_OF_EVENT},
	{"10 Minutes Before", mw::ReminderAlertTiming::TEN_MINUTES_BEOFORE},
	{"1 Hour Before", mw::ReminderAlertTiming::ONE_HOUR_BEFORE},
	{"1 Day Before", mw::ReminderAlertTiming::ONE_DAY_BEFORE}
};

std::map<mw::ReminderAlertMethod, std::string> mw::Reminder::alert_method_to_string = {
	{mw::ReminderAlertMethod::POPUP_NOTIFICATION, "Pop-Up Notificiation"},
	{mw::ReminderAlertMethod::EMAIL_NOTIFICATION, "Email Notificiation"},
	{mw::ReminderAlertMethod::SMS_MESSAGE, "SMS Message"}
};

std::map<std::string, mw::ReminderAlertMethod> mw::Reminder::string_to_alert_method = {
	{"Pop-Up Notificiation" ,mw::ReminderAlertMethod::POPUP_NOTIFICATION},
	{"Email Notificiation", mw::ReminderAlertMethod::EMAIL_NOTIFICATION},
	{"SMS Message", mw::ReminderAlertMethod::SMS_MESSAGE}
};

mw::Reminder::Reminder()
{
	this->StampCreationTime();
	this->title = "New Reminder";
	this->json_alert_data = "{}";
	this->alert_methods.push_back(mw::ReminderAlertMethod::POPUP_NOTIFICATION);
}

mw::Reminder::~Reminder()
{
}

void mw::Reminder::Hash()
{
	this->hash = 0;
}

std::string mw::Reminder::GetStatus()
{
	std::string status_string;
	auto iter = this->reminder_status_to_string.find(this->status);
	if (iter != this->reminder_status_to_string.end()) {
		return iter->second;
	}
	else {
		return "N/A";
	}
}

std::string mw::Reminder::GetEndTime()
{
	return this->ConvertTimeToString(this->end_time);
}

std::string mw::Reminder::RepeatOptionToString(mw::ReminderRepeatOptions option)
{
	auto iter = repeat_option_to_string.find(option);
	if (iter != repeat_option_to_string.end()) {
		return iter->second;
	}
	else {
		return "N/A"; 
	}
}

std::vector<std::string> mw::Reminder::GetRepeatOptions()
{
	std::vector<std::string> options;
	for (const auto& pair : mw::Reminder::repeat_option_to_string) 
	{
		options.push_back(pair.second);
	}
	return options;
}

std::vector<std::string> mw::Reminder::GetAlertTimingOptions()
{
	std::vector<std::string> options;
	for (const auto& pair : mw::Reminder::alert_timing_to_string)
	{
		options.push_back(pair.second);
	}
	return options;
}

std::vector<std::string> mw::Reminder::GetDaysOfTheWeekOptions()
{
	std::vector<std::string> options;
	options.push_back("Sunday");
	options.push_back("Monday");
	options.push_back("Tuesday");
	options.push_back("Wednesday");
	options.push_back("Thursday");
	options.push_back("Friday");
	options.push_back("Saturday");
	return options;
}

std::vector<std::string> mw::Reminder::GetAlertMethodOptions()
{
	std::vector<std::string> options;
	options.push_back("Pop-Up Notificiation");
	options.push_back("Email Notification");
	options.push_back("SMS message");
	return options;
}

std::string mw::Reminder::dump_json_alert_data()
{
	nlohmann::json j;

	j["repeat_type"] = this->repeat;
	j["hour"] = this->hour;
	j["min"] = this->min;
	j["sec"] = this->sec;
	j["alert_timing"] = this->alert_timing;
	j["alert_methods"] = this->alert_methods;
	switch (this->repeat)
	{
	case mw::ReminderRepeatOptions::ONE_TIME:	
		j["year"] = this->year;
		j["month"] = this->month;
		j["day"] = this->day;
		break;
	case mw::ReminderRepeatOptions::DAYS_OF_WEEK:
		j["days_of_week"] = this->days_of_week;
		break;
	case mw::ReminderRepeatOptions::ONCE_A_MONTH:
		break;
	default:
		break;
	}

	return j.dump();
}

void mw::Reminder::parse_json_alert_data(std::string data)
{
	mw::Logger logger;
	logger.EnableDebug();
	try {
		this->json_alert_data = data;
		nlohmann::json j = nlohmann::json::parse(this->json_alert_data);

		this->repeat = j["repeat_type"];
		this->hour = j["hour"];
		this->min = j["min"];
		this->sec = j["sec"];
		this->alert_timing = j["alert_timing"];
		std::vector<int> temp_vec = j["alert_methods"];
		this->alert_methods.clear();
		for (int i = 0; i < temp_vec.size(); i++)
		{
			this->alert_methods.push_back((mw::ReminderAlertMethod)temp_vec[i]);
		}
		switch (this->repeat)
		{
		case mw::ReminderRepeatOptions::ONE_TIME:
			this->year = j["year"];
			this->month = j["month"];
			this->day = j["day"];
			break;
		case mw::ReminderRepeatOptions::DAYS_OF_WEEK:
			this->days_of_week = j["days_of_week"];
			break;
		case mw::ReminderRepeatOptions::ONCE_A_MONTH:
			break;
		default:
			break;
		}
	}
	catch (const std::exception& e) {
		; // If parsing fails, the JSON is invalid
		logger.Error("The exception is: " + std::string(e.what()));

		this->status = mw::ReminderStatus::INVALID;
	}
}

bool mw::Reminder::isTimePassed(int hour, int min, int sec, int day, int month, int year) 
{
	// Get the current time
	auto currentTime = std::chrono::system_clock::now();
	std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);

	std::tm currentTimeInfo;
	if (localtime_s(&currentTimeInfo, &currentTimeT) != 0) {
		// Handle error if localtime_s fails
		throw std::runtime_error("Failed to get local time");
	}

	// Create a std::tm object for the provided date and time
	std::tm targetTimeInfo = {};
	targetTimeInfo.tm_hour = hour;
	targetTimeInfo.tm_min = min;
	targetTimeInfo.tm_sec = sec;
	targetTimeInfo.tm_mday = day;
	targetTimeInfo.tm_mon = month - 1; // Month is 0-based in std::tm
	targetTimeInfo.tm_year = year - 1900; // Year is years since 1900 in std::tm

	// Convert the target time to a time_t object
	std::time_t targetTimeT = std::mktime(&targetTimeInfo);

	// Compare the target time with the current time
	if (targetTimeT < currentTimeT)
		return true;
	return false;
}


bool mw::Reminder::ready()
{
	switch (repeat) {
	case ONE_TIME:
		if (isTimePassed(hour, min, sec, day, month, year))
		{
			this->status = mw::ReminderStatus::COMPLETE;
			return true;
		}
		break;
	case DAYS_OF_WEEK:
		// Handle DAYS_OF_WEEK option
		break;
	case ONCE_A_MONTH:
		// Handle ONCE_A_MONTH option
		break;
	default:
		// Handle default case (if needed)
		break;
	}
	
	return false;
}


