#pragma once
#include <string>
#include <unordered_map>
#include "FileIO/FileManager.h"
#include "Hashing/Hasher.h"
#include "Models/User.h"
#include "Models/UserLockData.h"
#include "Config/Config.h"

class AuthManager {
public:
    AuthManager(FileManager &fm, Hasher &hs, const Config &cfg,
                std::unordered_map<std::string, User> &users,
                std::unordered_map<std::string, UserLockData> &lockoutData);

    bool createUser(const std::string &username, const std::string &password);
    bool loginUser(const std::string &username, const std::string &password);

private:
    FileManager &fileManager;
    Hasher &hasher;
    const Config &config;
    std::unordered_map<std::string, User> &m_users;
    std::unordered_map<std::string, UserLockData> &m_lockoutData;

    void handleFailedAttempt(const std::string &username);
    bool isLockedOut(const std::string &username);
};
