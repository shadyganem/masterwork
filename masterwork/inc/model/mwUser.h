#pragma once
#include "model\mwModelItem.h"

#include <string>

class mwUser : public mwModelItem
{
public:
	mwUser();
	~mwUser();

private:
	std::string m_username;
	int m_id;
};

