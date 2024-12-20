cmake_minimum_required(VERSION 3.10)
project(SecureAuthCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(SecureAuthCPP
    src/main.cpp
    src/Authentication/AuthManager.cpp
    src/Authentication/AuthUtils.cpp
    src/Hashing/Hasher.cpp
    src/FileIO/FileManager.cpp
    src/Models/User.cpp
    src/Models/UserLockData.cpp
    src/Utils/Logger.cpp
    src/Utils/TimeUtils.cpp
    src/Config/Config.cpp
)

target_link_libraries(SecureAuthCPP OpenSSL::SSL OpenSSL::Crypto)
