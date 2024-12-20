#pragma once
#include <ctime>

struct UserLockData {
    int attemptCount;
    std::time_t lastAttemptTimestamp;
    std::time_t lockoutUntilTimestamp;

    UserLockData(int ac, std::time_t lat, std::time_t lut)
        : attemptCount(ac), lastAttemptTimestamp(lat), lockoutUntilTimestamp(lut) {}
    UserLockData() : attemptCount(0), lastAttemptTimestamp(0), lockoutUntilTimestamp(0) {}
};
