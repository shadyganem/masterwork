
#include "model/User.h"

mw::User::User()
{
	this->uid = 0;
	this->is_active = 0;
	this->status = mw::User::UserStatus::VALID;
	this->username = "Default User";
}

mw::User::User(std::string username)
{
	this->uid = 0;
	this->is_active = 0;
	this->status = mw::User::UserStatus::VALID;
	this->username = username;
}

mw::User::~User()
{
}
