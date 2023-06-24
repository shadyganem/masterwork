#include "model/PasswordHasher.h"

mw::PasswordHasher::PasswordHasher()
{
}

mw::PasswordHasher::~PasswordHasher()
{
}

std::string mw::PasswordHasher::hashPassword(const std::string& password)
{
	return bcrypt::generateHash(password);
}

bool mw::PasswordHasher::verifyPassword(const std::string& password, const std::string& hashedPassword)
{
	return bcrypt::validatePassword(password, hashedPassword);
}

bool mw::PasswordHasher::generateRandomBytes(void* buffer, size_t size)
{
	return false;
}
