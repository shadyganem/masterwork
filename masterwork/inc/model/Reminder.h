#pragma once
#include "ModelItem.h"
#include <string>
#include <ctime>

namespace mw
{
	class Reminder :	public ModelItem
	{
	public: 
		Reminder();
		~Reminder();

		std::time_t start_time;
		std::string name;
		int uid;
		int user_uid;
		int status;
		bool is_active;
	};
}

