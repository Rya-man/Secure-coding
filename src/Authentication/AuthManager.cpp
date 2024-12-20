#include "AuthManager.h"
#include <iostream>
#include "Utils/TimeUtils.h"

AuthManager::AuthManager(FileManager &fm, Hasher &hs, const Config &cfg,
                         std::unordered_map<std::string, User> &users,
                         std::unordered_map<std::string, UserLockData> &lockoutData)
    : fileManager(fm), hasher(hs), config(cfg), m_users(users), m_lockoutData(lockoutData) {}

bool AuthManager::createUser(const std::string &username, const std::string &password) {
    if (m_users.find(username) != m_users.end()) {
        std::cerr << "User already exists.\n";
        return false;
    }

    std::string salt = hasher.generateSalt(16);
    std::string hashedPass = hasher.hashPassword(salt, password);
    User newUser(username, salt, hashedPass);
    m_users.insert({username, newUser});
    m_lockoutData.insert({username, UserLockData(0,0,0)});
    fileManager.saveUsers(m_users);
    fileManager.saveLockoutData(m_lockoutData);
    return true;
}

bool AuthManager::loginUser(const std::string &username, const std::string &password) {
    auto userIt = m_users.find(username);
    if (userIt == m_users.end()) {
        std::cerr << "Invalid username or password.\n";
        return false;
    }

    if (isLockedOut(username)) {
        std::cerr << "User locked out. Try again later.\n";
        return false;
    }

    std::string computedHash = hasher.hashPassword(userIt->second.getSalt(), password);
    if (computedHash == userIt->second.getHashedPassword()) {
        m_lockoutData[username] = UserLockData(0,0,0);
        fileManager.saveLockoutData(m_lockoutData);
        return true;
    } else {
        handleFailedAttempt(username);
        return false;
    }
}

void AuthManager::handleFailedAttempt(const std::string &username) {
    auto &lockData = m_lockoutData[username];
    lockData.attemptCount++;
    lockData.lastAttemptTimestamp = TimeUtils::getCurrentTime();
    if (lockData.attemptCount >= config.getMaxAttempts()) {
        lockData.lockoutUntilTimestamp = TimeUtils::getCurrentTime() + config.getLockoutDuration();
        std::cerr << "Account locked for 10 minutes.\n";
    }
    fileManager.saveLockoutData(m_lockoutData);
}

bool AuthManager::isLockedOut(const std::string &username) {
    auto it = m_lockoutData.find(username);
    if (it == m_lockoutData.end()) return false;
    return TimeUtils::getCurrentTime() < it->second.lockoutUntilTimestamp;
}

