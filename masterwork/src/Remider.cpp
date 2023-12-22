#include "model/Reminder.h"

mw::Reminder::Reminder()
{
	this->StampCreationTime();
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
	default:
		status_string = "N/A";
		break;
	}
	return status_string;

}

std::string mw::Reminder::GetEndTime()
{

	// Convert the epoch timestamp to a struct tm
	std::tm timeinfo;


	#ifdef _WIN32
		localtime_s(&timeinfo, &this->end_time);
	#else
		localtime_r(&now, &localTime);

	#endif

	// Format the date and time as a string
	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeinfo);
	std::string end_time = buffer;
	return end_time;
}

std::string mw::Reminder::RepateOptionToString(mw::ReminderRepeatOptions option)
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
	options.push_back("Don't Repeat");
	options.push_back("Every Day");
	options.push_back("Every 30 Days");
	options.push_back("Every Year");
	return options;
}

