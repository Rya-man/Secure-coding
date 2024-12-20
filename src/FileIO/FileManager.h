#pragma once
#include <string>
#include <unordered_map>
#include "Models/User.h"
#include "Models/UserLockData.h"

class FileManager {
public:
    FileManager(const std::string &usersPath, const std::string &lockoutPath);
    void loadUsers(std::unordered_map<std::string, User> &users);
    void saveUsers(const std::unordered_map<std::string, User> &users);
    void loadLockoutData(std::unordered_map<std::string, UserLockData> &lockoutData);
    void saveLockoutData(const std::unordered_map<std::string, UserLockData> &lockoutData);

private:
    std::string usersFilePath;
    std::string lockoutFilePath;
};
