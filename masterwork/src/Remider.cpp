#include "model/Reminder.h"

const std::map<mw::ReminderRepeatOptions, std::string> mw::Reminder::repeat_option_to_string = {
	{mw::ReminderRepeatOptions::ONE_TIME, "One-Time"},
	{mw::ReminderRepeatOptions::DAYS_OF_WEEK, "Specific Days of the Week"},
	{mw::ReminderRepeatOptions::ONCE_A_MONTH, "Once a Month"}
};

mw::Reminder::Reminder()
{
	this->StampCreationTime();
	this->title = "New Reminder";
	this->json_alert_data = "{}";
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
	switch (this->status)
	{
	case ReminderStatus::ACTIVE:
		status_string = "Active";
		break;
	case ReminderStatus::DISABLED:
		status_string = "Disabled";
		break;
	case ReminderStatus::INVALID:
		status_string = "Invalid";
		break;
	default:
		status_string = "N/A";
		break;
	}
	return status_string;
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
	options.push_back("One-Time");
	options.push_back("Specific Days of the Week");
	options.push_back("Once a Month");
	// TODO: implement the custom option
	//options.push_back("Custom");
	return options;
}

std::vector<std::string> mw::Reminder::GetAlertTimingOptions()
{
	std::vector<std::string> options;
	options.push_back("At time of event");
	options.push_back("10 minutes before");
	options.push_back("1 hour before");
	options.push_back("1 day before");
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

