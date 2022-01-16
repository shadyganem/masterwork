#pragma once

#include <ctime>
#include <time.h>
#include <string>
#include "controller/Logger.h"

namespace mw
{
	class DateTime
	{
	public:
		DateTime();
		DateTime(int seconds, int minutes, int hours, int day, int month, int year);
		~DateTime();
		double DiffTime(DateTime& time1, DateTime& time2);
		std::time_t m_time_t;
	};
}

