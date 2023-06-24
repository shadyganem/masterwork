#pragma once
#include "model\ModelItem.h"

#include <string>

namespace mw
{
	class User : public ModelItem
	{
	public:
		enum UserStatus
		{
			VALID,
			DELETED = -1

		};
		User();
		User(std::string username);
		~User();

		int status;
		std::string username;
		bool is_active;
		std::string hashed_password;
		bool is_password_protected;
	};
}


