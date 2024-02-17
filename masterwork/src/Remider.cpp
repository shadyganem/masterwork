#include "model/Reminder.h"
#include "model/json.hpp"

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
	switch (option) {
	case mw::ReminderRepeatOptions::DONT_REPEAT:
		return "Don't Repeat";
	case mw::ReminderRepeatOptions::EVERYDAY:
		return "Every Day";
	case mw::ReminderRepeatOptions::EVERY_MONTH:
		return "Every Month";
	case mw::ReminderRepeatOptions::EVERY_YEAR:
		return "Every Year";
	default:
		return "Unknown Repeat Option";
	}
}

std::vector<std::string> mw::Reminder::GetRepeatOptions()
{
	std::vector<std::string> options;
	options.push_back("One-Time");
	options.push_back("Specific Days of the Week");
	options.push_back("Once a Month");
	options.push_back("Bi-Weekly");	
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

	j["type"] = "specific time";
	j["hour"] = std::to_string(1);

	return j.dump();
}

void mw::Reminder::parse_json_alert_data(std::string data)
{
	mw::Logger logger;
	try {
		this->json_alert_data = data;
		nlohmann::json j = nlohmann::json::parse(this->json_alert_data);

		std::string type = j["type"];
		
	}
	catch (const nlohmann::json::parse_error&) {
		; // If parsing fails, the JSON is invalid
		logger.Error("Error while parsing json string");
		this->status = mw::ReminderStatus::INVALID;
	}
}

