#pragma once

#include <ctime>
#include <time.h>
#include <string>

namespace mw
{
	class DateTime
	{
	public:
		DateTime();
		DateTime(unsigned int seconds, unsigned int minutes, unsigned int hours, unsigned int day, unsigned int month, unsigned int year);
		DateTime(std::string& time_str);
		~DateTime();
		double DiffTime(DateTime& time1, DateTime& time2);
		std::time_t m_time_t;
	};
}

