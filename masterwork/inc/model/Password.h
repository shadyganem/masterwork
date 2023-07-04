#pragma once
#include "model/ModelItem.h"
#include <ctime>

namespace mw
{
	class Password :
		public ModelItem
	{
	public:
		Password();
		~Password();

		virtual bool DecryptPassword();

	public:
		int uid;
		int user_uid;
		std::string username;
		std::string password;
		std::string encrypted_password;
		std::string url;
		std::string notes;
		std::time_t start_time;
		std::time_t end_time;
		int red;
		int green;
		int blue;
		int color;

	};
}

