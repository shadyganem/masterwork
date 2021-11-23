#pragma once
#include "model\mwModelItem.h"

#include <string>

class mwUser : public mwModelItem
{
public:
	mwUser();
	~mwUser();

	int uid;
	std::string username;
	bool is_active;
};

