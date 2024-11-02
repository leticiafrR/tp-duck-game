#ifndef SERVER_TIME_MANAGER_
#define SERVER_TIME_MANAGER_

#include <iostream>

#include "../common/timeManager.h"

#define FPS 10
#define PRINT_TEST_OVERFLOW_TICK()                                                                 \
    std::cout << "Too many commds procesed in this tick! It overflowed the time assigned per tick" \
              << std::endl;

class ServerTimeManager: public TimeManager {
private:
    void handleOverflowOfTimeInTick() override { PRINT_TEST_OVERFLOW_TICK(); }

public:
    explicit ServerTimeManager(int targetFPS): TimeManager(targetFPS) {}
};


#endif
