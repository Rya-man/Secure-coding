#pragma once
#include <string>

class Hasher {
public:
    std::string generateSalt(size_t length);
    std::string hashPassword(const std::string &salt, const std::string &password);

private:
    std::string bytesToHex(const unsigned char *bytes, size_t length);
};
