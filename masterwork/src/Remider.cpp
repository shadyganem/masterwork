#include "model/Reminder.h"

mw::Reminder::Reminder()
{
	this->StampCreationTime();
	this->title = "New Reminder";
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
	options.push_back("Once a Year");
	options.push_back("Bi-Weekly");
	options.push_back("Quarterly");
	// TODO: implement the custom option
	//options.push_back("Custom");
	return options;
}

std::vector<std::string> mw::Reminder::GetAlertOptions()
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

