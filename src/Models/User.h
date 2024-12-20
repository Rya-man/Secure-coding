#pragma once
#include <string>

class User {
public:
    User() = default;
    User(const std::string &uname, const std::string &s, const std::string &hp)
        : username(uname), salt(s), hashedPassword(hp) {}

    const std::string& getUsername() const { return username; }
    const std::string& getSalt() const { return salt; }
    const std::string& getHashedPassword() const { return hashedPassword; }

private:
    std::string username;
    std::string salt;
    std::string hashedPassword;
};
