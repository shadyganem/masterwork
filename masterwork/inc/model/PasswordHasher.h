#pragma once
#include <string>
#include <vector>
#include "bcryptcpp.h"

namespace mw
{
    class PasswordHasher {
    public:
        PasswordHasher();
        ~PasswordHasher();
        std::string hashPassword(const std::string& password);
        bool verifyPassword(const std::string& password, const std::string& hashedPassword);

    private:
        static const int SALT_LENGTH = 16;
        static const int HASH_LENGTH = 32;
        bool generateRandomBytes(void* buffer, size_t size);
    };

};

