#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <sys/stat.h> // for chmod on UNIX systems

FileManager::FileManager(const std::string &usersPath, const std::string &lockoutPath)
    : usersFilePath(usersPath), lockoutFilePath(lockoutPath) {}

void FileManager::loadUsers(std::unordered_map<std::string, User> &users) {
    std::ifstream file(usersFilePath);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string username, salt, hashedPassword;
        if (std::getline(ss, username, ',') &&
            std::getline(ss, salt, ',') &&
            std::getline(ss, hashedPassword, ',')) {
            users.emplace(username, User(username, salt, hashedPassword));
        }
    }
}

void FileManager::saveUsers(const std::unordered_map<std::string, User> &users) {
    std::ofstream file(usersFilePath, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Failed to open users file for writing.\n";
        return;
    }
    for (const auto &kv : users) {
        file << kv.first << "," << kv.second.getSalt() << "," << kv.second.getHashedPassword() << "\n";
    }
    file.close();
    chmod(usersFilePath.c_str(), S_IRUSR | S_IWUSR);
}

void FileManager::loadLockoutData(std::unordered_map<std::string, UserLockData> &lockoutData) {
    std::ifstream file(lockoutFilePath);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string username;
        int attemptCount;
        std::time_t lastAttempt, lockoutUntil;
        if (ss >> username >> attemptCount >> lastAttempt >> lockoutUntil) {
            lockoutData.emplace(username, UserLockData(attemptCount, lastAttempt, lockoutUntil));
        }
    }
}

void FileManager::saveLockoutData(const std::unordered_map<std::string, UserLockData> &lockoutData) {
    std::ofstream file(lockoutFilePath, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Failed to open lockout file for writing.\n";
        return;
    }
    for (const auto &kv : lockoutData) {
        file << kv.first << " " << kv.second.attemptCount << " "
             << kv.second.lastAttemptTimestamp << " "
             << kv.second.lockoutUntilTimestamp << "\n";
    }
    file.close();
    chmod(lockoutFilePath.c_str(), S_IRUSR | S_IWUSR);
}
