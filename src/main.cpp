#include <iostream>
#include "Config/Config.h"
#include "FileIO/FileManager.h"
#include "Hashing/Hasher.h"
#include "Authentication/AuthManager.h"
#include "Utils/Logger.h"

int main() {
    // Load configuration
    Config config;
    config.loadConfig("config.json");

    // Initialize FileManager and load user data
    FileManager fileManager(config.getUsersFilePath(), config.getLockoutFilePath());
    std::unordered_map<std::string, User> users;
    std::unordered_map<std::string, UserLockData> lockoutData;
    fileManager.loadUsers(users);
    fileManager.loadLockoutData(lockoutData);

    // Initialize Hasher
    Hasher hasher;

    // Initialize AuthManager
    AuthManager authManager(fileManager, hasher, config, users, lockoutData);

    // Main Loop
    while (true) {
        std::cout << "1. Register User\n2. Login User\n3. Exit\nChoose an option: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::string username, password;
            std::cout << "Enter Username: ";
            std::getline(std::cin, username);
            std::cout << "Enter Password: ";
            std::getline(std::cin, password);

            if (authManager.createUser(username, password)) {
                std::cout << "User registered successfully!\n";
            } else {
                std::cout << "Failed to register user.\n";
            }
        } else if (choice == 2) {
            std::string username, password;
            std::cout << "Enter Username: ";
            std::getline(std::cin, username);
            std::cout << "Enter Password: ";
            std::getline(std::cin, password);

            if (authManager.loginUser(username, password)) {
                std::cout << "Login successful!\n";
            } else {
                std::cout << "Login failed.\n";
            }
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
