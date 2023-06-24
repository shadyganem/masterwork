
#include "model/User.h"
#include "model/PasswordHasher.h"

mw::User::User()
{
	this->uid = 0;
	this->is_active = 0;
	this->is_password_protected = 0;
	this->status = mw::User::UserStatus::VALID;
	this->username = "Default User";
	mw::PasswordHasher hasher;
	this->hashed_password = hasher.hashPassword("");
}

mw::User::User(std::string username)
{
	this->uid = 0;
	this->is_active = 0;
	this->is_password_protected = 0;
	this->status = mw::User::UserStatus::VALID;
	this->username = username;
	mw::PasswordHasher hasher;
	this->hashed_password = hasher.hashPassword("");

}

mw::User::~User()
{
}

void mw::User::SetPassword(std::string password)
{
	mw::PasswordHasher hasher;
	this->hashed_password = hasher.hashPassword(password);
}
