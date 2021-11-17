#pragma once
#include "model\mwModel.h"

#include <string>

class mwUser : public mwModel
{
public:
	mwUser();
	~mwUser();

private:
	std::string m_username;
	int m_id;
};

