#pragma once
#include <string>

class Config {
public:
    void loadConfig(const std::string &configFile);

    std::string getUsersFilePath() const { return usersFilePath; }
    std::string getLockoutFilePath() const { return lockoutFilePath; }
    int getMaxAttempts() const { return maxAttempts; }
    int getLockoutDuration() const { return lockoutDuration; } // in seconds

private:
    std::string usersFilePath = "../data/users.csv";
    std::string lockoutFilePath = "../data/lockout.csv";
    int maxAttempts = 3;
    int lockoutDuration = 600; // 10 minutes
};
