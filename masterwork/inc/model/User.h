#pragma once
#include "model\mwModelItem.h"

#include <string>

namespace mw
{
	class User : public mwModelItem
	{
	public:
		User();
		User(std::string username);
		~User();

		int uid;
		std::string username;
		bool is_active;
	};
}


