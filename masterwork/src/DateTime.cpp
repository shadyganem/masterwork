#include "model/DateTime.h"

mw::DateTime::DateTime()
{
	std::time(&this->m_time_t);
}

mw::DateTime::DateTime(unsigned int seconds, unsigned int minutes, unsigned int hours, unsigned int day, unsigned int month, unsigned int year)
{
	std::tm time;
	time.tm_sec = (int)seconds;
	time.tm_min = (int)minutes;
	time.tm_hour = (int)hours;
	time.tm_mday = (int)day;
	time.tm_mon = (int)month;
	time.tm_year = (int)year - 1900;
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
