#pragma once
#include <iostream>
#include <string>


namespace mw
{
    class PasswordEncryptor {
    private:
        static const int key_size = 32;
        static const int iv_size = 16;
        unsigned char key[key_size];
        unsigned char iv[iv_size];

    public:
        PasswordEncryptor();

        virtual std::string encrypt(const std::string& password);

        virtual std::string decrypt(const std::string& encrypted_password);
    };
}


