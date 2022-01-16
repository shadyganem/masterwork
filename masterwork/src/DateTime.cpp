#include "model/DateTime.h"

mw::DateTime::DateTime()
{
	std::time(&this->m_time_t);
}

mw::DateTime::DateTime(int seconds, int minutes, int hours, int day, int month, int year)
{
	mw::Logger logger;
	std::tm time;
	time.tm_sec = seconds;
	time.tm_min = minutes;
	time.tm_hour = hours;
	time.tm_mday = day;
	time.tm_mon = month;
	time.tm_year = year - 1900;
	this->m_time_t = std::mktime(&time);
}

mw::DateTime::DateTime(std::string& time_str)
{
}

mw::DateTime::~DateTime()
{
}

double mw::DateTime::DiffTime(DateTime& time1, DateTime& time2)
{
	return std::difftime(time1.m_time_t, time2.m_time_t);
}
