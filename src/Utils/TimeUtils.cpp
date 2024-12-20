#include "TimeUtils.h"
#include <ctime>

std::time_t TimeUtils::getCurrentTime() {
    return std::time(nullptr);
}
