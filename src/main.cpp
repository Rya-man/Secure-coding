#include <iostream>
#include "Config/Config.h"
#include "FileIO/FileManager.h"
#include "Hashing/Hasher.h"
#include "Authentication/AuthManager.h"
#include "Utils/Logger.h"

int main() {
    // Load configuration (paths, lockout durations, etc.)
    Config config;
    config.loadConfig("config.json"); // Assume config.json or defaults

    // Initialize FileManager and load existing users & lockout data
    FileManager fileManager(config.getUsersFilePath(), config.getLockoutFilePath());
    std::unordered_map<std::string, User> users;
    std::unordered_map<std::string, UserLockData> lockoutData;
    fileManager.loadUsers(users);
    fileManager.loadLockoutData(lockoutData);

    // Initialize Hasher (for hashing passwords)
    Hasher hasher;

    // Initialize AuthManager with in-memory data
    AuthManager authManager(fileManager, hasher, config, users, lockoutData);

    std::cout << "Enter Password: ";
    std::string password;
    std::getline(std::cin, password);

    // Hash the input password as a demonstration
    std::string hashResult = hasher.hashPassword(hasher.generateSalt(16), password);

    std::cout << "Hashed password: " << hashResult << std::endl;

    return 0;
}
